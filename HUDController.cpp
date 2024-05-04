#include "HUDController.h"
#include "Game.h"

HUDController::HUDController(RenderWindow* _window, int _height, int _width): height(_height), width(_width) {
	// Asignar ventana, objeto y estado
	window = new RenderWindow;
	window = _window;
	state = 0;
	selectedOption = 1;

	InitSpritesAndTexts();
}

void HUDController::InitSpritesAndTexts() {
	// Asignando cada sprite de cada nivel
	for (int i = 0; i < 7; i++) {
		levelTex[i] = new Texture;
		levelSpr[i] = new Sprite;

		levelTex[i]->loadFromFile("Assets/level" + to_string(i) + ".png");

		levelSpr[i]->setTexture(*levelTex[i]);
		levelSpr[i]->setScale(0.015f, 0.020f);
		levelSpr[i]->setPosition(46.f, 90.f);
	}

	// Asignando fuente de letra
	font = new Font;
	font->loadFromFile("Assets/ParadeGroovy.ttf");

	// ASIGNANDO CONFIGURACIÓN A CADA TEXTO
	// Opción uno
	select[0] = new Text;
	select[0]->setFont(*font);
	select[0]->setScale(0.015f, 0.020f);
	select[0]->setCharacterSize(70);
	select[0]->setPosition(Vector2f(50.f, 95.f));
	select[0]->setFillColor(Color::Blue);

	// Opción dos
	select[1] = new Text;
	select[1]->setFont(*font);
	select[1]->setScale(0.015f, 0.020f);
	select[1]->setCharacterSize(70);
	select[1]->setPosition(Vector2f(50.f, 97.f));
	select[1]->setFillColor(Color::Black);

	// Cantidad de ragdolls
	ragdollQuantityTxt = new Text;
	ragdollQuantityTxt->setFont(*font);
	ragdollQuantityTxt->setScale(0.015f, 0.020f);
	ragdollQuantityTxt->setCharacterSize(30);
	ragdollQuantityTxt->setPosition(46.5f, 90.2f);
	ragdollQuantityTxt->setFillColor(Color::White);

	// Nivel
	levelTxt = new Text;
	levelTxt->setFont(*font);
	levelTxt->setScale(0.015f, 0.020f);
	levelTxt->setPosition(56.f, 90.2f);
	levelTxt->setCharacterSize(30);
	levelTxt->setFillColor(Color::Blue);

	// Mensaje
	messageTxt = new Text;
	messageTxt->setFont(*font);
	messageTxt->setScale(0.015f, 0.020f);
	messageTxt->setPosition(50.f, 91.f);
	messageTxt->setCharacterSize(70);

	// Salida
	exitTxt = new Text;
	exitTxt->setFont(*font);
	exitTxt->setScale(0.015f, 0.020f);
	exitTxt->setPosition(50.f, 96.f);
	exitTxt->setCharacterSize(30);
}

void HUDController::Draw(RenderWindow* _window, int _state, int _level, int _ragdollsQuantity) {
	switch (_state) {
	// Menú principal
	case 0:
		select[0]->setString("Play");
		select[1]->setString("Exit");

		_window->draw(*levelSpr[0]);

		for (int i = 0; i < OPTION; i++) {
			_window->draw(*select[i]);
		}
		break;
	// Exit
	case 2:
		exitTxt->setFillColor(Color::Black);
		exitTxt->setString("See you!");

		_window->draw(*levelSpr[0]);
		_window->draw(*exitTxt);
		break;
	// Victoria
	case 3:
		messageTxt->setFillColor(Color::Yellow);
		messageTxt->setString("Level clear!");
		select[0]->setString("Next level");
		select[1]->setString("Restart game");
		
		if (_level == 2) {
			_window->draw(*levelSpr[2]);
		} else if (_level == 3) {
			_window->draw(*levelSpr[4]);
		}
		
		_window->draw(*messageTxt);

		for (int i = 0; i < OPTION; i++) {
			_window->draw(*select[i]);
		}
		break;
	// Derrota
	case 4:
		messageTxt->setFillColor(Color::Yellow);
		messageTxt->setString("Level lost...");
		select[0]->setString("Restart level");
		select[1]->setString("Restart game");

		if (_level == 1) {
			_window->draw(*levelSpr[2]);
		}
		else if (_level == 2) {
			_window->draw(*levelSpr[4]);
		}

		_window->draw(*messageTxt);
		for (int i = 0; i < OPTION; i++) {
			_window->draw(*select[i]);
		}
		break;
	// Juego completado (fin del tercer nivel)
	case 5:
		messageTxt->setFillColor(Color::Green);
		messageTxt->setString("YOU WIN!!!");
		messageTxt->setPosition(50.f, 94.f);
		messageTxt->setCharacterSize(100);

		_window->draw(*levelSpr[6]);
		_window->draw(*messageTxt);
		break;
	}

	// Dibujar interfaz de usuario durante los niveles
	if (_state == 1 && _level <= 3) {
		if (_level == 1) {
			_window->draw(*levelSpr[1]);
		} else if (_level == 2) {
			_window->draw(*levelSpr[3]);
		} else if (_level == 3) {
			_window->draw(*levelSpr[5]);
		}

		ragdollQuantityTxt->setString("Ammunition: " + to_string(5 - _ragdollsQuantity));
		levelTxt->setString("Level " + to_string(_level));

		_window->draw(*ragdollQuantityTxt);
		_window->draw(*levelTxt);
	}
}

void HUDController::SelectUp() {
	select[0]->setFillColor(Color::Blue);
	select[1]->setFillColor(Color::Black);
}

void HUDController::SelectDown() {
	select[0]->setFillColor(Color::Black);
	select[1]->setFillColor(Color::Blue);
}