#include "LP.h"

LP::LP(RenderWindow* _window, int _width, int _height): width(_width), height(_height)
{
	window = new RenderWindow;
	window = _window;
	selectedItem = 1;
	gameState = 0;

	initTextAndSprites();
}

void LP::initTextAndSprites() {
	for (int i = 0; i < 7; i++) {
		levelTex[i] = new Texture;
		levelSpr[i] = new Sprite;

		levelTex[i]->loadFromFile("Assets/level" + to_string(i) + ".png");

		levelSpr[i]->setTexture(*levelTex[i]);
		levelSpr[i]->setScale(0.015f, 0.020f);
		levelSpr[i]->setPosition(46.f, 90.f);
	}

	font = new Font;
	font->loadFromFile("Assets/ParadeGroovy.ttf");

	main[0] = new Text;
	main[0]->setFont(*font);
	main[0]->setScale(0.015f, 0.020f);
	main[0]->setCharacterSize(60);
	main[0]->setPosition(Vector2f(50.0f, 95.0f));
	main[0]->setFillColor(Color::Red);

	main[1] = new Text;
	main[1]->setFont(*font);
	main[1]->setScale(0.015f, 0.020f);
	main[1]->setCharacterSize(60);
	main[1]->setPosition(Vector2f(50.0f, 97.0f));
	main[1]->setFillColor(Color::Black);

	ragdollsTxt = new Text;
	ragdollsTxt->setFont(*font);
	ragdollsTxt->setScale(0.015f, 0.020f);
	ragdollsTxt->setCharacterSize(30);
	ragdollsTxt->setPosition(Vector2f(46.5f, 90.0f));
	ragdollsTxt->setFillColor(Color::Black);

	levelTxt = new Text;
	levelTxt->setFont(*font);
	levelTxt->setScale(0.015f, 0.020f);
	levelTxt->setCharacterSize(30);
	levelTxt->setPosition(Vector2f(56.0f, 90.0f));
	levelTxt->setFillColor(Color::Red);

	messageTxt = new Text;
	messageTxt->setFont(*font);
	messageTxt->setScale(0.015f, 0.020f);
	messageTxt->setCharacterSize(80);
	messageTxt->setPosition(Vector2f(50.0f, 93.0f));
	
	exitTxt = new Text;
	exitTxt->setFont(*font);
	exitTxt->setScale(0.015f, 0.020f);
	exitTxt->setCharacterSize(30);
	exitTxt->setPosition(Vector2f(50.0f, 96.0f));

}

void LP::moveUpMenu() {
	main[0]->setFillColor(Color::Red);
	main[1]->setFillColor(Color::Black);
}

void LP::moveDownMenu() {
	main[0]->setFillColor(Color::Black);
	main[1]->setFillColor(Color::Red);
}

void LP::Draw(RenderWindow* _window, int _state, int _level, int _ragdolls) {

	switch (_state) {
	// Menú principal
	case 0:
		main[0]->setString("Play");
		main[1]->setString("exit");

		_window->draw(*levelSpr[0]);
		_window->draw(*main[0]);
		_window->draw(*main[1]);
		break;

	// Menú de salida
	case 2:
		exitTxt->setFillColor(Color::Black);
		exitTxt->setString("Goodbye");

		_window->draw(*levelSpr[0]);
		_window->draw(*exitTxt);
		break;
	
	// Victoria del nivel
	case 3:
		messageTxt->setFillColor(Color::Yellow);
		messageTxt->setString("LEVEL CLEAR");
		main[0]->setString("Next level");
		main[1]->setString("Reset game");

		_window->draw(*levelSpr[_level]);
		_window->draw(*messageTxt);
		_window->draw(*main[0]);
		_window->draw(*main[1]);

		break;

	// Derrota del nivel
	case 4:
		messageTxt->setFillColor(Color::Yellow);
		messageTxt->setString("LEVEL LOST");
		main[0]->setString("Try again");
		main[1]->setString("Reset game");

		_window->draw(*levelSpr[_level]);
		_window->draw(*messageTxt);
		_window->draw(*main[0]);
		_window->draw(*main[1]);
		break;

	// Victoria del juego
	case 5:
		messageTxt->setString("YOU WIN!!!");
		messageTxt->setFillColor(Color::Green);
		messageTxt->setCharacterSize(200);
		messageTxt->setPosition(Vector2f(47.0f, 93.0f));
		_window->draw(*levelSpr[6]);
		_window->draw(*messageTxt);
		break;
	}

	if (_state == 1 && _level <= 5) {
		_window->draw(*levelSpr[_level]);

		ragdollsTxt->setString("Lasting ragdolls: " + to_string(5 - _ragdolls));
		_window->draw(*ragdollsTxt);

		if (_level == 5) {
			levelTxt->setString("level " + to_string(_level - 2));
		}
		else if (_level == 3) {
			levelTxt->setString("level " + to_string(_level - 1));
		}
		else {
			levelTxt->setString("level " + to_string(_level));
		}

		_window->draw(*levelTxt);
	}
}