#include "Game.h"

Game::Game(int _width, int _height, string _title) : width(_width), height(_height)
{
	wnd = new RenderWindow(VideoMode(width, height), _title);
	fps = 60;
	frameTime = 1.0f / fps;
	wnd->setFramerateLimit(fps);
	wnd->setVisible(true);

	b2PolygonShape shp_rag[6];

	InitGame();
}

float Game::deg2rad(float degrees) {
	return degrees * 3.1415 / 180;
}

void Game::InitGame() {
	InitElements();
	InitPhysics();
	InitTextures();
	Loop();
}

void Game::InitElements() {
	// Inicia reloj, tiempo y eventos
	clock = new Clock;
	time1 = new Time;
	evt = new Event;

	// Inicia procesador de niveles
	levelProcessor = new LP(wnd, width, height);

	// Para las cajas
	offSetX = 0.0f;
	offSetY = 0.0f;

	level = 1;
	state = 0;
	selectedObject = 1;

	//floorBoxes = 0;
	ragdolls = 0;
	Ragdoll_On = false;

	// Tiempos
	wait = 0.0f;
	time2 = 0.0f;

	SetZoom({ 19.f,19.f }, { 12.f, 12.f }, { 33.f, 77.f });

	collission = false;
}

void Game::SetZoom(Vector2f _Center, Vector2f _Size, Vector2f _Position) {
	// Inicia la cámara
	camera = new View({_Center},{_Size});
	// Posicion de la cámara
	camera->move({_Position});
	// Asignamos la cámara
	wnd->setView(*camera);
}

void Game::InitPhysics() {
	// Inicializamos el mundo con la gravedad por defecto
	World = new b2World(b2Vec2(0.0f, 9.8f));

	// Creamos un piso y lo posicionamos
	bdygrd_def.type = b2_staticBody;
	bdygrd_def.position = b2Vec2(50.0f, 104.0f);
	bdy_ground = World->CreateBody(&bdygrd_def);

	b2PolygonShape shp_grnd;
	shp_grnd.SetAsBox(50.f, 2.5f);

	fixgrd_def.shape = &shp_grnd;
	fixgrd_def.density = 1.0f;
	fixgrd_def.restitution = 0.0f;
	fixgrd_def.friction = 0.3f;

	fix_ground = bdy_ground->CreateFixture(&fixgrd_def);

	// Creando el cañon
	bdycnyn_def.type = b2_staticBody;
	bdycnyn_def.position = b2Vec2(47.f, 100.f);
	bdy_canyon = World->CreateBody(&bdycnyn_def);

	b2PolygonShape shp_cnyn;
	shp_cnyn.SetAsBox(0.8f, 0.8f);

	fixcnyn_def.shape = &shp_cnyn;
	fixcnyn_def.density = 1.f;
	fixcnyn_def.restitution = 0.1f;
	fixcnyn_def.friction = 0.3f;

	fix_canyon = bdy_canyon->CreateFixture(&fixcnyn_def);

	// Caja de victoria
	bdyVicBox_def.type = b2_dynamicBody;
	bdyVicBox_def.position = b2Vec2(55.f, 101.f);
	bdy_victoryBox = World->CreateBody(&bdyVicBox_def);

	b2PolygonShape shp_VicBox;
	shp_VicBox.SetAsBox(0.5f, 0.5f);

	fixVicBox_def.shape = &shp_VicBox;
	fixVicBox_def.density = 1.f;
	fixVicBox_def.restitution = 0.1f;
	fixVicBox_def.friction = 0.1f;

	fix_victoryBox = bdy_victoryBox->CreateFixture(&fixVicBox_def);
	
}

void Game::InitTextures() {
	// Texturizando en cañón
	canyon_tex = new Texture;
	canyon_tex->loadFromFile("Assets/Canyon.png");
	canyon_spr = new Sprite;
	canyon_spr->setTexture(*canyon_tex);

	fig_canyon = new RectangleShape();

	_canyon = new SpriteRenderer(bdy_canyon, canyon_spr);

	// Texturizando el piso
	ground_tex = new Texture;
	ground_tex->loadFromFile("Assets/Ground.png");
	ground_spr = new Sprite;
	ground_spr->setTexture(*ground_tex);

	fig_ground = new RectangleShape();

	_ground = new SpriteRenderer(bdy_ground, ground_spr);

	// Texturizando la caja de victoria
	VictoryBox_tex = new Texture;
	VictoryBox_tex->loadFromFile("Assets/VictoryBox.png");
	VictoryBox_spr = new Sprite;
	VictoryBox_spr->setTexture(*VictoryBox_tex);

	fig_victoryBox = new RectangleShape();

	_victoryBox = new SpriteRenderer(bdy_victoryBox, VictoryBox_spr);
}

void Game::SelectPlay() {
	if (selectedObject == 2) {
		selectedObject = (selectedObject - 1);
		levelProcessor->MoveUpMenu();
	}
	else if (selectedObject == 1) {
		levelProcessor->MoveUpMenu();
	}
}

void Game::SelectExit() {
	if (selectedObject == 1) {
		selectedObject = (selectedObject + 1);
		levelProcessor->MoveDownMenu();
	}
	else if (selectedObject == 2) {
		levelProcessor->MoveDownMenu();
	}
}

void Game::UpdatePhysics() {
	World->Step(frameTime, 8, 8);
	World->ClearForces();
	World->DebugDraw();
}

void Game::UpdateCanyon() {
	Vector2i mousePos;
	Vector2f mousePosCoord;
	mousePos = Mouse::getPosition(*wnd);
	mousePosCoord = wnd->mapPixelToCoords(mousePos);

	bdy_canyon->SetTransform(bdy_canyon->GetPosition(), atan2f(mousePosCoord.y - bdy_canyon->GetPosition().y, mousePosCoord.x - bdy_canyon->GetPosition().x));
}

void Game::UpdateRagdoll() {
	Vector2i mousePos;
	Vector2f mousePosCoord;
	mousePos = Mouse::getPosition(*wnd);
	mousePosCoord = wnd->mapPixelToCoords(mousePos);

	if (level > 0 && ragdolls < 5) {
		Ragdoll_On = true;

		if (ragdolls < 5) {
			RagdollNumber[ragdolls] = new Ragdoll({ bdy_canyon->GetPosition().x + 0.5f, bdy_canyon->GetPosition().y - 2.f }, *World);
			RagdollNumber[ragdolls]->ApplyForce({ mousePosCoord.x - bdy_canyon->GetPosition().x, mousePosCoord.y - bdy_canyon->GetPosition().y });
			ragdolls++;
		}

	}
}

void Game::DoEvents() {
	
	while (wnd->pollEvent(*evt)) {
		switch (evt->type) {
		// Cierra la ventana
		case Event::Closed:
			wnd->close();
			break;
		
		case Event::KeyPressed:
			//if (Keyboard::isKeyPressed(Keyboard::Left)) {
			//	bdy_canyon->SetTransform(bdy_canyon->GetPosition(), bdy_canyon->GetAngle() + deg2rad(3));
			//}
			//else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			//	bdy_canyon->SetTransform(bdy_canyon->GetPosition(), bdy_canyon->GetAngle() + deg2rad(-3));
			//}
			if (evt->key.code == Keyboard::Up) {
				SelectPlay();
			}
			else if (evt->key.code == Keyboard::Down) {
				SelectExit();
			}
			else if (evt->key.code == Keyboard::Enter) {

				switch (state)
				{
				case 0:

					if (selectedObject == 1) {
						state = 1;
					}
					else if (selectedObject == 2) {
						state = 2;
					}
					else {
						state = 0;
					}
					break;

				case 3:

					if (selectedObject == 1) {
						state = 1;
					}
					else if (selectedObject == 2) {
						state = 6;
					}
					else {
						state = 0;
					}
					break;

				case 4:

					if (selectedObject == 1) {
						state = 1;
					}
					else if (selectedObject == 2) {
						state = 6;
					}
					else {
						state = 0;
					}
					break;
				}

			}
			break;

		// Si el cursor se mueve, la posicion del canon cambia
		case Event::MouseMoved:
			UpdateCanyon();
			break;

		// Si se hace clic, dispara ragdoll
		case Event::MouseButtonPressed:
			UpdateRagdoll();
			break;


		}

	}
}

void Game::Loop() {
	while (wnd->isOpen()) {
		// Mientras la ventana esté abierta, 
		// se realizará el siguiente recorrido:
		
		DoEvents();

		DrawTheGame();
		
		gameStateCond();
	}
}

void Game::gameStateCond() {
	if (state == 1) {
		*time1 = clock->getElapsedTime();
		if (time2 + frameTime < time1->asSeconds()) {
			time2 = time1->asSeconds();

			UpdatePhysics();

			CheckCollitions();

			Conditions();
		}
	}

	if (state == 6) {
		wnd->close();
		new Game(800, 600, "TP Final - MyA2 - Dante Rizzi");
	}
}

void Game::Conditions() {
	if (collission == true) {
		level++;
		state = 3;

		if (state == 3) {
			state = 5;
		}
		else {
			ragdolls = 0;
			offSetX = 0;
			offSetY = 0;
			InitGame();
		}
	}
}

void Game::CheckCollitions() {

	for (int i = 0; i < ragdolls; i++) {
		// Bounding box de la caja de victoria
		FloatRect victoryBounds = fig_victoryBox->getGlobalBounds();

		const Vector2f ragdollPos = RagdollNumber[i]->GetPosition(i);
		const Vector2f ragdollSize = RagdollNumber[i]->GetSize(i);
		FloatRect ragdollBounds = FloatRect(ragdollPos, ragdollSize);

		if (victoryBounds.intersects(ragdollBounds)) {
			collission = true;
		}

	}
	//
	/**/
	
}

void Game::DrawTheGame() {
	wnd->clear();
	
	// Dibuja la escena
	levelProcessor->Draw(wnd, state, level, ragdolls);

	// Cuando comienza el juego
	if (state == 1) {
		levelProcessor->Draw(wnd, state, level, ragdolls);

		_ground->Draw(wnd);
		_canyon->Draw(wnd);
		_victoryBox->Draw(wnd);

		for (int i = 0; i < ragdolls; i++) {
			if (!RagdollNumber[i] || Ragdoll_On == true) {
				RagdollNumber[i]->Draw(wnd);
			}
		}
	}

	wnd->display();
}
