#include <iostream>
#include <SFML/System.hpp>
#include "Game.h"

Game::Game(int _height, int _width, string _title): width(_height), height(_width) {
	// Asignar ventana
	window = new RenderWindow(VideoMode(width, height), _title);
	fps = 60;
	frameTime = 1.0f / fps;
	window->setFramerateLimit(fps);
	window->setVisible(true);

	InitElements();

	GameStart();
}

void Game::InitElements() {
	// Inicializa eventos, tiempo y cámara
	evt = new Event;
	time1 = new Time;
	clock = new Clock;

	// Inicializa HUDController
	hudController = new HUDController(window, width, height);

	//variables del juego
	level = 1;
	state = 0;
	selectedOption = 1;

	//variables de objetos
	isVictoryBoxOnTheFloor = false;
	ragdollQuantity = 0;
	ragdollOn = false;

	//variables de tiempo
	time2 = 0.f;
	waitTime = 0.f;

	// Inicializa la cámara
	SetZoom({ 19.f,19.f }, { 12.f, 12.f }, { 33.f, 77.f });
}

void Game::GameStart() {
	// Inicia las físicas
	InitPhysics();

	// Inicia los sprites
	InitSprites();

	// Inicia los objetos
	InitObjects();

	// Inicia bucle del juego
	Loop();
}

void Game::SetZoom(Vector2f _center, Vector2f _size, Vector2f _offset) {
	// Asigno cámara y defino tamaño y posición
	camera = new View({ _center }, { _size });
	camera->move({ _offset });
	window->setView(*camera);
}

void Game::InitPhysics() {
	// Inicializa mundo del juego con la gravedad estándar
	world = new b2World(b2Vec2(0.0f, 9.8f));

	if (level == 1) {
		//Inicializa obstaculo
		obstacle1BodyDef.type = b2_staticBody;
		obstacle1BodyDef.position = b2Vec2(51.f, 101.f);
		obstacle1Body = world->CreateBody(&obstacle1BodyDef);

		b2PolygonShape shp_obstaculo1;
		shp_obstaculo1.SetAsBox(0.5f, 2.0f);

		obstacle1FixDef.shape = &shp_obstaculo1;
		obstacle1FixDef.density = 1.f;
		obstacle1FixDef.restitution = 0.1f;
		obstacle1FixDef.friction = 0.3f;
		obstacle1Fix = obstacle1Body->CreateFixture(&obstacle1FixDef);
	}
	else if (level == 2) {
		//Inicializa obstaculo 1
		obstacle1BodyDef.type = b2_dynamicBody;
		obstacle1BodyDef.position = b2Vec2(50.f, 95.6f);
		obstacle1Body = world->CreateBody(&obstacle1BodyDef);

		b2PolygonShape shp_obstaculo1;
		shp_obstaculo1.SetAsBox(0.8f, 0.8f);

		obstacle1FixDef.shape = &shp_obstaculo1;
		obstacle1FixDef.density = 0.2f;
		obstacle1FixDef.restitution = 0.1f;
		obstacle1FixDef.friction = 0.3f;
		obstacle1Fix = obstacle1Body->CreateFixture(&obstacle1FixDef);


		//Inicializa obstaculo 2
		obstacle2BodyDef.type = b2_dynamicBody;
		obstacle2BodyDef.position = b2Vec2(50.f, 98.f);
		obstacle2Body = world->CreateBody(&obstacle2BodyDef);

		b2PolygonShape shp_obstaculo2;
		shp_obstaculo2.SetAsBox(0.8f, 0.8f);

		obstacle2FixDef.shape = &shp_obstaculo2;
		obstacle2FixDef.density = 0.2f;
		obstacle2FixDef.restitution = 0.1f;
		obstacle2FixDef.friction = 0.3f;
		obstacle1Fix = obstacle2Body->CreateFixture(&obstacle2FixDef);
	}
	else if (level == 3) {
		//Inicializa obstaculo 1
		pendulumBox1BodyDef.type = b2_staticBody;
		pendulumBox1BodyDef.position = b2Vec2(51.3f, 96.f);
		pendulumBox1Body = world->CreateBody(&pendulumBox1BodyDef);

		b2PolygonShape pendulumBox1Shape;
		pendulumBox1Shape.SetAsBox(0.6f, 0.6f);

		pendulumBox1FixDef.shape = &pendulumBox1Shape;
		pendulumBox1FixDef.density = 1.f;
		pendulumBox1FixDef.restitution = 0.1f;
		pendulumBox1FixDef.friction = 0.3f;
		pendulumBox1Fix = pendulumBox1Body->CreateFixture(&pendulumBox1FixDef);

		//Inicializa obstaculo 2
		pendulumBox2BodyDef.type = b2_dynamicBody;
		pendulumBox2BodyDef.position = b2Vec2(51.3f, 98.f);
		pendulumBox2Body = world->CreateBody(&pendulumBox2BodyDef);

		b2PolygonShape pendulumBox2Shape;
		pendulumBox2Shape.SetAsBox(0.6f, 0.6f);

		pendulumBox2FixDef.shape = &pendulumBox2Shape;
		pendulumBox2FixDef.density = 1.f;
		pendulumBox2FixDef.restitution = 0.1f;
		pendulumBox2FixDef.friction = 0.3f;
		pendulumBox2Fix = pendulumBox2Body->CreateFixture(&pendulumBox2FixDef);

		// Inicializar joint (resorte) entre las dos cajas del péndulo
		pendulumBoxJointDef.Initialize(pendulumBox1Body, pendulumBox2Body, b2Vec2(pendulumBox1Body->GetPosition().x, pendulumBox1Body->GetPosition().y), b2Vec2(pendulumBox2Body->GetPosition().x, pendulumBox2Body->GetPosition().y));

		pendulumBoxJointDef.damping = 0.1f;
		pendulumBoxJointDef.stiffness = 0.1f;
		pendulumBoxJointDef.length = 5.f;
		pendulumBoxJointDef.collideConnected = true;
		pendulumBoxJoint = (b2DistanceJoint*)world->CreateJoint(&pendulumBoxJointDef);
	}

	// Inicializa cañón
	canyonBodyDef.type = b2_staticBody;
	canyonBodyDef.position = b2Vec2(48.f, 100.2f);
	canyonBody = world->CreateBody(&canyonBodyDef);

	b2PolygonShape canyonShape;
	canyonShape.SetAsBox(1.2f, 1.0f);

	canyonFixDef.shape = &canyonShape;
	canyonFixDef.density = 1.f;
	canyonFixDef.restitution = 0.1f;
	canyonFixDef.friction = 0.3f;
	canyonFix = canyonBody->CreateFixture(&canyonFixDef);

	// Inicializa caja de victoria
	victoryBoxBodyDef.type = b2_dynamicBody;
	victoryBoxBodyDef.position = b2Vec2(53.5f, 98.5f);
	victoryBoxBody = world->CreateBody(&victoryBoxBodyDef);

	b2PolygonShape shape_cajaMovil;
	shape_cajaMovil.SetAsBox(0.5f, 0.5f);

	victoryBoxFixDef.shape = &shape_cajaMovil;
	victoryBoxFixDef.density = 1.f;
	victoryBoxFixDef.restitution = 0.0f;
	victoryBoxFixDef.friction = 0.3f;

	victoryBoxFix = victoryBoxBody->CreateFixture(&victoryBoxFixDef);

	// Inicializa caja de apoyo
	holdBoxBodyDef.type = b2_staticBody;
	holdBoxBodyDef.position = b2Vec2(53.5f, 99.f);
	holdBoxBody = world->CreateBody(&holdBoxBodyDef);

	b2PolygonShape holdBoxShape;
	holdBoxShape.SetAsBox(0.5f, 0.5f);

	holdBoxFixDef.shape = &holdBoxShape;
	holdBoxFixDef.density = 1.f;
	holdBoxFixDef.restitution = 0.0f;
	holdBoxFixDef.friction = 0.3f;

	holdBoxFix = holdBoxBody->CreateFixture(&holdBoxFixDef);

	// Inicializa el Suelo
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position = b2Vec2(50.f, 102.f);
	groundBody = world->CreateBody(&groundBodyDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(10.f, 0.8f);

	groundFixDef.shape = &groundShape;
	groundFixDef.restitution = 0.f;
	groundFixDef.friction = 0.3f;
	groundFixDef.density = 1.f;
	groundFix = groundBody->CreateFixture(&groundFixDef);

}

void Game::InitSprites() {

	if (level == 1) {
		// Obstáculo
		obstacle1Tex = new Texture;
		obstacle1Tex->loadFromFile("Assets/StoppedBox.png");
		obstacle1Spr = new Sprite;
		obstacle1Spr->setTexture(*obstacle1Tex);

		obstacle1Fig = new RectangleShape;

	}
	else if (level == 2) {
		// Obstáculo 1
		obstacle1Tex = new Texture;
		obstacle1Tex->loadFromFile("Assets/StoppedBox.png");
		obstacle1Spr = new Sprite;
		obstacle1Spr->setTexture(*obstacle1Tex);

		obstacle1Fig = new RectangleShape;

		// Obstáculo 2
		obstacle2Tex = new Texture;
		obstacle2Tex->loadFromFile("Assets/StoppedBox.png");
		obstacle2Spr = new Sprite;
		obstacle2Spr->setTexture(*obstacle2Tex);

		obstacle2Fig = new RectangleShape;
	}
	else if (level == 3)
	{
		// Caja 1
		pendulumBox1Tex = new Texture;
		pendulumBox1Tex->loadFromFile("Assets/StoppedBox.png");
		pendulumBox1Spr = new Sprite;
		pendulumBox1Spr->setTexture(*pendulumBox1Tex);

		pendulumBox1Fig = new RectangleShape;

		// Caja 2
		pendulumBox2Tex = new Texture;
		pendulumBox2Tex->loadFromFile("Assets/StoppedBox.png");
		pendulumBox2Spr = new Sprite;
		pendulumBox2Spr->setTexture(*pendulumBox2Tex);

		pendulumBox2Fig = new RectangleShape;
	}

	// Cañón
	canyonTex = new Texture;
	canyonTex->loadFromFile("Assets/Canyon.png");
	canyonSpr = new Sprite;
	canyonSpr->setTexture(*canyonTex);

	canyonFig = new RectangleShape;

	// Caja de victoria
	victoryBoxTex = new Texture;
	victoryBoxTex->loadFromFile("Assets/Target.png");
	victoryBoxSpr = new Sprite;
	victoryBoxSpr->setTexture(*victoryBoxTex);

	holdBoxFig = new RectangleShape;
	victoryBoxFig = new RectangleShape;

	// Caja que sostiene la de victoria
	holdBoxTex = new Texture;
	holdBoxTex->loadFromFile("Assets/StoppedBox.png");
	holdBoxSpr = new Sprite;
	holdBoxSpr->setTexture(*holdBoxTex);

	// Piso
	groundTex = new Texture;
	groundTex->loadFromFile("Assets/Ground.png");
	groundSpr = new Sprite;
	groundSpr->setTexture(*groundTex);

	groundFig = new RectangleShape;

}

void Game::InitObjects() {
	// Obstáculos de los niveles
	if (level == 1) {
		obstacle1SR = new SpriteRenderer(obstacle1Body, obstacle1Spr);
	}
	else if (level == 2) {
		obstacle1SR = new SpriteRenderer(obstacle1Body, obstacle1Spr);
		obstacle2SR = new SpriteRenderer(obstacle2Body, obstacle2Spr);
	}
	else if (level == 3) {
		pendulumBox1SR = new SpriteRenderer(pendulumBox1Body, pendulumBox1Spr); 
		pendulumBox2SR = new SpriteRenderer(pendulumBox2Body, pendulumBox2Spr);
	}

	// Cañón
	canyonSR = new SpriteRenderer(canyonBody, canyonSpr);

	// Cajas de victoria y de apoyo
	victoryBoxSR = new SpriteRenderer(victoryBoxBody, victoryBoxSpr);
	holdBoxSR = new SpriteRenderer(holdBoxBody, holdBoxSpr);

	// Piso
	groundSR = new SpriteRenderer(groundBody, groundSpr);
	
}

void Game::Loop() {
	// Mientras la ventana esté abierta,
	while (window->isOpen()) {
		// Procesa los eventos
		ProssesEvent();

		// Dibuja los elementos del juego
		DrawTheGame();

		// Chequea el estado del juego
		StateOfTheGame();
	}
}

void Game::StateOfTheGame() {
	// Si el estado del juego es 1 (juego)
	if (state == 1) {
		*time1 = clock->getElapsedTime();
		if (time2 + frameTime < time1->asSeconds()) {
			time2 = time1->asSeconds();

			// Actualiza las físicas
			UpdatePhysics();

			// Chequea las colisiones
			CheckColission();

			// Chequea las condiciones del juego
			ConditionGame();
		}
	}

	// Si el jugador decide reiniciar el juego, se abrirá una nueva partida
	if (state == 6) {
		window->close();
		new Game(800, 600, "TP Final MyAII - Dante Rizzi");
	}
}

void Game::ConditionGame() {
	// Si la caja de victoria está en el piso,
	if (isVictoryBoxOnTheFloor) {

		// Pasar al estado de victoria y al nivel siguiente
		state = 3;
		level++;

		// Si el nivel es mayor a tres, mostrar pantalla de juego completado
		if (level > 3) {
			state = 5;
		}
		else {
			// De lo contrario, abrir un nuevo nivel con la caja y ragdolls desactivados
			isVictoryBoxOnTheFloor = false;
			ragdollQuantity = 0;
			GameStart();
		}
	}
}

void Game::ProssesEvent() {
	// Atención a los eventos
	while (window->pollEvent(*evt)) {
		switch (evt->type) {
		// Cerrar ventana
		case Event::Closed:
			window->close();
			break;
		// Si el mouse se mueve, se actualiza la posición del cañón
		case Event::MouseMoved:
			UpdateCanyon();
			break;
		// Si el usuario hace click izquierdo, se dispara el ragdoll
		case Event::MouseButtonPressed:
			UpdateRagdoll();
			break;
		case Event::KeyPressed:
			// Seleccionar primera opción
			if (evt->key.code == Keyboard::Up) {
				SelectUp();
			}
			else if (evt->key.code == Keyboard::Down) {
				// Seleccionar segunda opción
				SelectDown();
			}
			else if (evt->key.code == Keyboard::Enter) {
				switch (state) {
				// Menú principal
				case 0:
					// Play (jugar)
					if (selectedOption == 1) {
						// Juego
						state = 1;
					}
					// Exit (salir)
					else if (selectedOption == 2) {
						// Pantalla de salida
						state = 2;
					}
					else {
						state = 0;
					}
					break;
				// Victoria 
				case 3:
					// Next level (siguiente nivel)
					if (selectedOption == 1) {
						// Juego
						state = 1;
					}
					// Restart game (reiniciar juego)
					else if (selectedOption == 2) {
						// Cerrar juego y abrir uno nuevo
						state = 6;
					}
					break;
				// Derrota
				case 4:
					// Restart level (reiniciar nivel)
					if (selectedOption == 1) {
						// Juego
						state = 1;
					}
					// Restart game (reiniciar juego)
					else if (selectedOption == 2) {
						// Cerrar juego y abrir uno nuevo
						state = 6;
					}
					else {
						state = 0;
					}
					break;
				}
			}				
		}
	}
}

void Game::UpdateCanyon() {
	Vector2i positionMouse;
	Vector2f positionMouseCoordinates;
	positionMouse = Mouse::getPosition(*window);
	positionMouseCoordinates = window->mapPixelToCoords(positionMouse);

	// Actualiza la posición del cañón según la posición del mouse
	canyonBody->SetTransform(canyonBody->GetPosition(), atan2f(positionMouseCoordinates.y - canyonBody->GetPosition().y, positionMouseCoordinates.x - canyonBody->GetPosition().x));
}

void Game::UpdateRagdoll() {
	Vector2i positionMouse;
	Vector2f positionMouseCoordinates;
	positionMouse = Mouse::getPosition(*window);
	positionMouseCoordinates = window->mapPixelToCoords(positionMouse);

	// Si hay menos de 5 ragdolls disparados, los ragdolls aún se podrán disparar hacia la posición del mouse
	if (ragdollQuantity < 5 && level > 0) {
		ragdollOn = true;

		if (!isVictoryBoxOnTheFloor) {
			if (ragdollQuantity < 5) {
				ragdolls[ragdollQuantity] = new Ragdoll({ canyonBody->GetPosition().x + 0.5f, canyonBody->GetPosition().y - 2.f }, *world);
				ragdolls[ragdollQuantity]->ApplyForce({ positionMouseCoordinates.x - canyonBody->GetPosition().x, positionMouseCoordinates.y - canyonBody->GetPosition().y });
				ragdollQuantity++;
			}
		}
	}
}

void Game::UpdatePhysics() {
	world->Step(frameTime, 8, 8);
	world->ClearForces();
	world->DebugDraw();
}

void Game::SelectUp() {
	if (selectedOption == 2) {
		selectedOption = (selectedOption - 1);
		hudController->SelectUp();
	}
	else if (selectedOption == 1) {
		hudController->SelectUp();
	}
}

void Game::SelectDown() {
	if (selectedOption == 1) {
		selectedOption = (selectedOption + 1);
		hudController->SelectDown();
	}
	else if (selectedOption == 2) {
		hudController->SelectDown();
	}
}

void Game::CheckColission() {
	// Cajas de colisión de la caja de victoria, su apoyo y el suelo
	FloatRect victoryBoxBounds = victoryBoxSpr->getGlobalBounds();
	FloatRect holdBoxBounds = holdBoxSpr->getGlobalBounds();
	FloatRect groundBounds = groundSpr->getGlobalBounds();

	// Si la caja de victoria no se cae de su apoyo, no está en el suelo
	if (victoryBoxBounds.intersects(holdBoxBounds)) {
		isVictoryBoxOnTheFloor = false;
	}
	else if (victoryBoxBounds.intersects(groundBounds)) {
		isVictoryBoxOnTheFloor = true;
	}
	else if (!victoryBoxBounds.intersects(holdBoxBounds)) {
		isVictoryBoxOnTheFloor = true;
	}
}

void Game::DrawTheGame() {
	
	// Limpia la ventana
	window->clear();

	// Envia a dibujar al controller
	hudController->Draw(window, state, level, ragdollQuantity);

	// Si el estado del juego es 1 (nivel)
	if (state == 1) {

		// Dibujar el arma y el piso
		groundSR->Draw(window);
		canyonSR->Draw(window);

		// Dibujar caja de victoria y su apoyo
		victoryBoxSR->Draw(window);
		holdBoxSR->Draw(window);		

		// Dibujar los ragdolls
		for (int i = 0; i < ragdollQuantity; i++) {
			if (!ragdolls[i] || ragdollOn) {
				ragdolls[i]->Draw(*window);
			}
		}

		// Dibujar los obstáculos dependiendo del nivel
		if (level == 1) {
			obstacle1SR->Draw(window);
		}
		else if (level == 2) {
			obstacle1SR->Draw(window);
			obstacle2SR->Draw(window);
		}
		else if (level == 3) {
			pendulumBox1SR->Draw(window);
			pendulumBox2SR->Draw(window);
		}
	}

	window->display();
}

float Game::DegToRad(float _degrees) {
	return _degrees * 3.1416f / 180;
}
