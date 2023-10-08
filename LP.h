// LP = Level Processor (Procesador de niveles)
#pragma once
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
using namespace sf;
using namespace std;

//Nombre del juego, Play = 1, Exit = 2
#define MENU 2

class LP {
private:
	// Ventana
	RenderWindow* window;

	// Texturas y sprites para los niveles
	Texture* levelTex[7];
	Sprite* levelSpr[7];

	// Texto para el menú
	Text* main[MENU];
	// Texto para cada nivel de juego
	Text* levelTxt;
	// Texto que muestra cantidad de ragdolls
	Text* ragdollsTxt;
	// Mensaje del juego
	Text* messageTxt;
	// Texto play
	Text* exitTxt;

	// Fuente de letra a utilizar
	Font* font;

	// Selector del menú
	int selectedItem;
	
	// Ancho y alto de la ventana
	int width;
	int height;
	
	// Estado del juego
	int gameState;
	
	// Elementos
	int items;

public:

	// Constructor de la clase
	LP(RenderWindow* _window, int _width, int _height);

	// Inicializa las texturas y textos
	void initTextAndSprites();

	// Mueve el selector hacia arriba
	void moveUpMenu();

	// Mueve el selector hacia abajo
	void moveDownMenu();

	// Dibuja las texturas y texto
	void Draw(RenderWindow* _window, int _state, int _level, int _ragdolls);

};