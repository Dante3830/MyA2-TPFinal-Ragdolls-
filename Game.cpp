#include "Game.h"

Game::Game(int _width, int _height, string _title) : width(_width), height(_height)
{
	// Inicializando los componentes de la ventana
	window = new RenderWindow(VideoMode(width, height), _title);
	fps = 60;
	frameTime = 1.0f / fps;
	window->setFramerateLimit(fps);
	window->setVisible(true);

	initElements();
	gameStart();
}

float Game::degToRad(float degrees) {
	return degrees * 3.1415 / 180;
}

void Game::gameStart() {
	initPhysics();
	initTextures();
	Loop();
}

void Game::initElements() {
	// Inicia reloj, tiempo y evtos
	clock = new Clock();
	time1 = new Time();
	evt = new Event();

	// Inicia procesador de niveles
	levelProcessor = new LP(window, width, height);

	// Para las cajas
	//offSetX = 0.0f;
	//offSetY = 0.0f;

	level = 1;
	state = 0;
	selectedObject = 1;

	floorBoxes = 0;
	ragdollCount = 0;
	ragdollOn = false;

	// Tiempos
	wait = 0.0f;
	time2 = 0.0f;

	// Cámara
	setZoom({ 19.f,19.f }, { 12.f, 12.f }, { 33.f, 77.f });
}

void Game::setZoom(Vector2f _focus, Vector2f _size, Vector2f _position) {
	// Inicia la cámara
	camera = new View({_focus},{_size});
	// Posicion de la cámara
	camera->move({_position});
	// Asignamos la cámara
	window->setView(*camera);
}

void Game::initPhysics() {
	// Inicializamos el mundo con la gravedad por defecto
	world = new b2World(b2Vec2(0.0f, 9.8f));

	// Creamos un piso y lo posicionamos
	BdyGrd_Def.type = b2_staticBody;
	BdyGrd_Def.position = b2Vec2(50.0f, 104.0f);
	Bdy_Ground = world->CreateBody(&BdyGrd_Def);

	b2PolygonShape shp_grnd;
	shp_grnd.SetAsBox(50.f, 2.5f);

	FixGrd_Def.shape = &shp_grnd;
	FixGrd_Def.density = 1.0f;
	FixGrd_Def.restitution = 0.0f;
	FixGrd_Def.friction = 0.3f;

	Fix_Ground = Bdy_Ground->CreateFixture(&FixGrd_Def);

	// Creando el cañon
	BdyCnyn_Def.type = b2_staticBody;
	BdyCnyn_Def.position = b2Vec2(47.f, 100.f);
	Bdy_Canyon = world->CreateBody(&BdyCnyn_Def);

	b2PolygonShape shp_cnyn;
	shp_cnyn.SetAsBox(0.8f, 0.8f);

	FixCnyn_Def.shape = &shp_cnyn;
	FixCnyn_Def.density = 1.f;
	FixCnyn_Def.restitution = 0.1f;
	FixCnyn_Def.friction = 0.3f;

	Fix_Canyon = Bdy_Canyon->CreateFixture(&FixCnyn_Def);


	// Inicializar caja quieta
	BdyStpBox_Def.type = b2_staticBody;
	BdyStpBox_Def.position = b2Vec2(StoppedBox_X + offsetX_boxes, StoppedBox_Y + offsetY_boxes);
	Bdy_StoppedBox = world->CreateBody(&BdyStpBox_Def);

	b2PolygonShape Shape_StoppedBox;
	Shape_StoppedBox.SetAsBox(0.4f, 0.4f);

	FixStpBox_Def.shape = &Shape_StoppedBox;
	FixStpBox_Def.density = 1.f;
	FixStpBox_Def.restitution = 0.0f;
	FixStpBox_Def.friction = 0.3f;

	Fix_StpBox = Bdy_StoppedBox->CreateFixture(&FixStpBox_Def);


	// Inicializar caja de victoria
	float X_VictoryBox = StoppedBox_X;
	float Y_VictoryBox = StoppedBox_Y - 0.45f;
	BdyVicBox_Def.type = b2_dynamicBody;
	BdyVicBox_Def.position = b2Vec2(X_VictoryBox, Y_VictoryBox);
	Bdy_VictoryBox = world->CreateBody(&BdyVicBox_Def);

	b2PolygonShape Shape_VictoryBox;
	Shape_VictoryBox.SetAsBox(0.5f, 0.5f);
	
	FixVicBox_Def.shape = &Shape_VictoryBox;
	FixVicBox_Def.density = 0.5f;
	FixVicBox_Def.restitution = 0.0f;
	FixVicBox_Def.friction = 0.3f;

	Fix_VictoryBox = Bdy_VictoryBox->CreateFixture(&FixVicBox_Def);

	for (int i = 0; i < 3; i++) {

	}

	if (level == 1) {
		// Creando los obstáculos del primer nivel
		BdyObstacle_Def.type = b2_staticBody;
		BdyObstacle_Def.position = b2Vec2(52.f, 100.5f);
		Bdy_Obstacle = world->CreateBody(&BdyObstacle_Def);

		b2PolygonShape Shape_Obstacle;
		Shape_Obstacle.SetAsBox(1.f, 1.45f);

		FixObstacle_Def.shape = &Shape_Obstacle;
		FixObstacle_Def.density = 1.f;
		FixObstacle_Def.restitution = 0.f;
		FixObstacle_Def.friction = 0.3f;

		Fix_Obstacle = Bdy_Obstacle->CreateFixture(&FixObstacle_Def);
	}
	else if (level == 3)
	{
		// Creando los obstáculos del segundo nivel

		/*
		for (int i = 0; i < 3; i++) {
			BdyObstacle_Def[i].type = b2_staticBody;
			BdyObstacle_Def[0].position = b2Vec2(52.f, 100.5f);
			BdyObstacle_Def[1].position = b2Vec2(52.f, 97.f);
			BdyObstacle_Def[2].position = b2Vec2(52.f, 95.f);

			Bdy_Obstacle[i] = world->CreateBody(&BdyObstacle_Def[i]);
			
			b2PolygonShape Shape_Obstacle[3];
			Shape_Obstacle[0].SetAsBox(1.f, 1.45f);
			Shape_Obstacle[1].SetAsBox(1.f, 1.45f);
			Shape_Obstacle[2].SetAsBox(0.5f, 0.5f);

			FixObstacle_Def[i].shape = &Shape_Obstacle[i];
			FixObstacle_Def[i].density = 1.f;
			FixObstacle_Def[i].restitution = 0.f;
			FixObstacle_Def[i].friction = 0.3f;

			Fix_Obstacle[i] = Bdy_Obstacle[i]->CreateFixture(&FixObstacle_Def[i]);
		}
		*/


	}
	else if (level == 5) {
		// Creando los obstáculos del tercer (y último) nivel
		/*BdyObstacle_Def.type = b2_staticBody;
		BdyObstacle_Def.position = b2Vec2(52.f, 100.f);
		Bdy_Obstacle = world->CreateBody(&BdyObstacle_Def);

		b2PolygonShape Shape_Obstacle;
		Shape_Obstacle.SetAsBox(1.f, 1.5f);

		FixObstacle_Def.shape = &Shape_Obstacle;
		FixObstacle_Def.density = 1.f;
		FixObstacle_Def.restitution = 0.f;
		FixObstacle_Def.friction = 0.3f;

		Fix_Obstacle = Bdy_Obstacle->CreateFixture(&FixObstacle_Def);*/
	}
	

}

void Game::initTextures() {
	// Texturizando en cañón
	Canyon_Tex = new Texture;
	Canyon_Tex->loadFromFile("Assets/Canyon.png");
	Canyon_Spr = new Sprite;
	Canyon_Spr->setTexture(*Canyon_Tex);

	Fig_Canyon = new RectangleShape(Vector2f(0.8f, 0.8f));

	SR_Canyon = new SpriteRenderer(Bdy_Canyon, Canyon_Spr);


	// Texturizando el piso
	Ground_Tex = new Texture;
	Ground_Tex->loadFromFile("Assets/Ground.png");
	Ground_Spr = new Sprite;
	Ground_Spr->setTexture(*Ground_Tex);

	Fig_Ground = new RectangleShape(Vector2f(50.f, 2.5f));

	SR_Ground = new SpriteRenderer(Bdy_Ground, Ground_Spr);


	// Texturizando la caja quieta
	StoppedBox_Tex = new Texture;
	StoppedBox_Tex->loadFromFile("Assets/CommonBox.png");
	StoppedBox_Spr = new Sprite;
	StoppedBox_Spr->setTexture(*StoppedBox_Tex);

	Fig_VictoryBox = new RectangleShape;

	SR_StoppedBox = new SpriteRenderer(Bdy_StoppedBox, StoppedBox_Spr);


	// Texturizando caja de victoria
	VictoryBox_Tex = new Texture;
	VictoryBox_Tex->loadFromFile("Assets/VictoryBox.png");
	VictoryBox_Spr = new Sprite;
	VictoryBox_Spr->setTexture(*VictoryBox_Tex);

	Fig_VictoryBox = new RectangleShape;

	SR_VictoryBox = new SpriteRenderer(Bdy_VictoryBox, VictoryBox_Spr);


	// Texturizando obstáculos
	//for (int i = 0; i < 3; i++) {
		Obstacle_Tex = new Texture;
		Obstacle_Tex->loadFromFile("Assets/CommonBox.png");
		Obstacle_Spr = new Sprite;
		Obstacle_Spr->setTexture(*Obstacle_Tex);

		Fig_Obstacle = new RectangleShape;

		SR_Obstacle = new SpriteRenderer(Bdy_Obstacle, Obstacle_Spr);
	//}

}

void Game::selectUp() {
	if (selectedObject == 2) {
		selectedObject = (selectedObject - 1);
		levelProcessor->moveUpMenu();
	}
	else if (selectedObject == 1) {
		levelProcessor->moveUpMenu();
	}
}

void Game::selectDown() {
	if (selectedObject == 1) {
		selectedObject = (selectedObject + 1);
		levelProcessor->moveDownMenu();
	}
	else if (selectedObject == 2) {
		levelProcessor->moveDownMenu();
	}
}

void Game::updatePhysics() {
	world->Step(frameTime, 8, 8);
	world->ClearForces();
	world->DebugDraw();
}

void Game::updateCanyon() {
	Vector2i mousePos;
	Vector2f mousePosCoord;
	mousePos = Mouse::getPosition(*window);
	mousePosCoord = window->mapPixelToCoords(mousePos);

	Bdy_Canyon->SetTransform(Bdy_Canyon->GetPosition(), 
		atan2f(mousePosCoord.y - Bdy_Canyon->GetPosition().y, 
		 mousePosCoord.x - Bdy_Canyon->GetPosition().x));
}

void Game::updateRagdoll() {
	Vector2i mousePos;
	Vector2f mousePosCoord;
	mousePos = Mouse::getPosition(*window);
	mousePosCoord = window->mapPixelToCoords(mousePos);

	if (level > 0 && ragdollCount < 5) {
		ragdollOn = true;

		if (ragdollCount < 5) {
			ragdollNumber[ragdollCount] = new Ragdoll({ Bdy_Canyon->GetPosition().x + 0.5f, Bdy_Canyon->GetPosition().y - 2.f }, *world);
			ragdollNumber[ragdollCount]->applyForce({ mousePosCoord.x - Bdy_Canyon->GetPosition().x, 
													  mousePosCoord.y - Bdy_Canyon->GetPosition().y });
			ragdollCount++;
		}

	}
}

void Game::doEvents() {
	
	while (window->pollEvent(*evt)) {
		switch (evt->type) {
		// Cierra la ventana
		case Event::Closed:
			window->close();
			break;

		// Si el cursor se mueve, la posicion del canon cambia
		case Event::MouseMoved:
			updateCanyon();
			break;

		// Si se hace clic, dispara ragdoll
		case Event::MouseButtonPressed:
			updateRagdoll();

			/*if ((ragdollNumber == 0) && (FloorBoxes == 0)) {
				state = 4;
			}*/
			
			break;

		case Event::KeyPressed:
			if (evt->key.code == Keyboard::Up) {
				selectUp();
			}
			else if (evt->key.code == Keyboard::Down) {
				selectDown();
			}
			else if (evt->key.code == Keyboard::Enter) {

				// Seleccionar opción actual
				switch (state)
				{
					// Inicio del juego (menú principal)
				case 0:

					if (selectedObject == 1) {
						state = 1;
						printf("Ganar Nivel");
					}
					else if (selectedObject == 2) {
						state = 2;
					}
					else {
						state = 0;
					}
					break;

					// Ganar nivel
				case 3:

					if (selectedObject == 1) {
						state = 1;
						level++;
						printf("Ganar Nivel");
					}
					else if (selectedObject == 2) {
						state = 6;
					}
					else {
						state = 0;
					}
					break;

				// Perder nivel
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
			//break;
		}

	}
}

void Game::Loop() {
	// Mientras la ventana esté abierta, 
	// se realizará el siguiente recorrido:
	while (window->isOpen()) {
		// Recibir los eventos del teclado y mouse
		doEvents();

		// Dibujar los elementos del juego
		drawTheGame();
		
		// Chequear el estado del juego 
		gameState();
	}
}

void Game::gameState() {
	if (state == 1) {
		*time1 = clock->getElapsedTime();
		if (time2 + frameTime < time1->asSeconds()) {
			time2 = time1->asSeconds();

			updatePhysics();

			checkCollisions();

			checkWinningCondition();
		}
	}

	if (state == 6) {
		window->close();
		new Game(800, 600, "TP Final - MyA2 - Dante Rizzi");
	}
}

void Game::checkCollisions() {

	// Toma los global bounds de cada uno de los objetos...
	FloatRect VictoryBounds = VictoryBox_Spr->getGlobalBounds();
	FloatRect StoppedBounds = StoppedBox_Spr->getGlobalBounds();
	FloatRect GroundBounds = Ground_Spr->getGlobalBounds();

	//... y cuando colisionen con el piso, activará la 
	// condicion de victoria de cada nivel
	if (VictoryBounds.intersects(StoppedBounds)) {
		floorBoxes = 0;
	}
	else if (VictoryBounds.intersects(GroundBounds)) {
		floorBoxes = 1;
	}
	else if (!VictoryBounds.intersects(StoppedBounds)) {
		floorBoxes = 1;
	}

}

void Game::checkWinningCondition() {
	// Cuando la caja de victoria esté en el piso,
	if (floorBoxes == 1) {
		
		// El jugador pasará al siguiente nivel
		level++;
		state = 3;
		printf("Ganar Nivel");

		// Si el jugador supera los TRES niveles, se da la condicion de victoria del juego
		// (Está en "> 5" por el tema de los sprites)
		if (level > 5) {
			state = 5;
		}
		else {
			// De no ser así, se vuelve a iniciar el nivel
			ragdollCount = 0;
			floorBoxes = 0;

			gameStart();
		}
	}

	/*
	if (floorBoxes < 1 && ragdollCount == 5)
	{
		/*
			si el ragdoll4 no es nulo => verdadero
				if (ragdoll4 intercepto con el piso) o (ragdoll4 interpecto a otro ragdoll) o (ragdoll4 salió fuera de pantalla) => verdadero
					gamestate = 4 (perdiste, repetir el nivel)
					modificar variables
					Iniciar el jeugo
		

		if (ragdolls[4] != NULL)
		{
			Vector2f positionCoordRagdoll = Vector2f(ragdolls[4]->GetPosition(4));
			Vector2i positionPixelRagdoll = window->mapCoordsToPixel(positionCoordRagdoll);

			FloatRect boxRagdoll4 = ragdolls[4]->GetRagdollBounds(4);
			FloatRect box_suelo = Ground_Spr->getGlobalBounds();

			bool Ragdoll4SobreOtroRagdoll = false;

			cout << positionPixelRagdoll.x << " " << positionPixelRagdoll.y << endl;

			if (positionPixelRagdoll.x < 0.f || positionPixelRagdoll.x > 800.f || positionPixelRagdoll.y < 0.f)
			{
				cout << "ragdoll fuera de pantalla" << endl;
			}
			if (boxRagdoll4.intersects(box_suelo))
			{
				cout << "ragdoll en el suelo" << endl;
			}

			/*for (int i = 0; i < ragdollCount; i++)
			{
			Ragdoll4SobreOtroRagdoll = boxRagdoll4.intersects(ragdolls[0]->GetRagdollBounds(0));
			if (Ragdoll4SobreOtroRagdoll)
			{
				cout << "ragdoll arriba de otro " << 0 << endl;
			}
			//}

			
			gamestate = 4;
			for (int i = 0; i < ragdollCount; i++)
			{
				ragdoll[i] = NULL;
			}

			FloorBoxes = 0;
			ragdollCount = 0;
			offsetX_boxes = 0;
			offsetY_boxes = 0;
			InitGame();

		}
	}*/
}

void Game::drawTheGame() {
	window->clear();
	
	// Dibuja la escena
	levelProcessor->Draw(window, state, level, ragdollCount);

	// Cuando comienza el juego
	if (state == 1) {

		// Dibujar cañón y piso
		SR_Ground->Draw(window);
		SR_Canyon->Draw(window);

		// Dibujar caja de victoria y caja quieta
		SR_StoppedBox->Draw(window);
		SR_VictoryBox->Draw(window);

		// Dibujar obstáculos dependiendo del nivel
		if (level == 1) {
			// Primer nivel
			SR_Obstacle->Draw(window);

		} else if (level == 3) {
			// Segundo nivel
			
			//_Obstacle[0]->Draw(window);
			//_Obstacle[1]->Draw(window);
			//_Obstacle[2]->Draw(window);

		} else if (level == 5) {
			// Tercer nivel

			//_Obstacle[0]->Draw(window);

		}

		for (int i = 0; i < ragdollCount; i++) {
			if (!ragdollNumber[i] || ragdollOn) {
				ragdollNumber[i]->Draw(window);
			}
		}
	}

	window->display();
}