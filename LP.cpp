#include "LP.h"

LP::LP(RenderWindow* _window, int _width, int _height): window(_window), width(_width), height(_height)
{
	window = new RenderWindow;
	selectedItem = 1;
	gameState = 0;

	InitTextAndLevels();
}

void LP::InitTextAndLevels() {
	for (int i = 0; i < 5; i++) {
		level_tex[i] = new Texture;
		level_spr[i] = new Sprite;

		level_tex[i]->loadFromFile("Assets/level" + to_string(i) + ".png");
		level_spr[i]->setTexture(*level_tex[i]);
		level_spr[i]->setScale(0.015f, 0.020f);
		level_spr[i]->setPosition(46.f, 90.f);
	}

	font = new Font;
	font->loadFromFile("Assets/ParadeGroovy.ttf");

	main[0] = new Text;
	main[0]->setFont(*font);
	main[0]->setScale(0.015f, 0.020f);
	main[0]->setCharacterSize(60);
	main[0]->setPosition(Vector2f(51.0f, 95.0f));
	main[0]->setFillColor(Color::Red);

	main[1] = new Text;
	main[1]->setFont(*font);
	main[1]->setScale(0.015f, 0.020f);
	main[1]->setCharacterSize(60);
	main[1]->setPosition(Vector2f(51.0f, 97.0f));
	main[1]->setFillColor(Color::Black);

	ragdolls = new Text;
	ragdolls->setFont(*font);
	ragdolls->setScale(0.015f, 0.020f);
	ragdolls->setCharacterSize(30);
	ragdolls->setPosition(Vector2f(46.5f, 90.0f));
	ragdolls->setFillColor(Color::Black);

	level = new Text;
	level->setFont(*font);
	level->setScale(0.015f, 0.020f);
	level->setCharacterSize(30);
	level->setPosition(Vector2f(56.0f, 90.0f));
	level->setFillColor(Color::Red);

	message = new Text;
	message->setFont(*font);
	message->setScale(0.015f, 0.020f);
	message->setCharacterSize(30);
	message->setPosition(Vector2f(50.0f, 98.0f));
	
	exit = new Text;
	exit->setFont(*font);
	exit->setScale(0.015f, 0.020f);
	exit->setCharacterSize(30);
	exit->setPosition(Vector2f(50.0f, 96.0f));
}

void LP::MoveUpMenu() {
	main[0]->setFillColor(Color::Red);
	main[1]->setFillColor(Color::Black);
}

void LP::MoveDownMenu() {
	main[0]->setFillColor(Color::Black);
	main[1]->setFillColor(Color::Red);
}

void LP::Draw(RenderWindow* _window, int _state, int _level, int _Ragdolls) {
	switch (_state) {
	case 0:
		main[0]->setString("Play");
		main[1]->setString("Exit");

		_window->draw(*level_spr[0]);
		_window->draw(*main[0]);
		_window->draw(*main[1]);
		break;
	//case 2:
		//
		//break;
	case 3:
		message->setFillColor(Color::Yellow);
		message->setString("LEVEL CLEAR");
		main[0]->setString("Next Level");
		main[1]->setString("Reset game");

		_window->draw(*level_spr[4]);
		_window->draw(*message);
		_window->draw(*main[0]);
		_window->draw(*main[1]);
		break;
	case 4:
		message->setFillColor(Color::Yellow);
		message->setString("LEVEL LOST");
		main[0]->setString("Try again");
		main[1]->setString("Reset game");

		_window->draw(*level_spr[4]);
		_window->draw(*message);
		_window->draw(*main[0]);
		_window->draw(*main[1]);
		break;
	case 5:
		message->setString("YOU WIN!!");
		message->setFillColor(Color::Green);
		_window->draw(*level_spr[0]);
		_window->draw(*message);
		break;
	}

	if (_state >= 1 && _state <= 3) {
		_window->draw(*level_spr[_level]);

		ragdolls->setString("Lasting Ragdolls: " + to_string(5 - _Ragdolls));
		_window->draw(*ragdolls);

		level->setString("Level " + to_string(_level));
		_window->draw(*level);
	}
}
