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
	Texture* level_tex[5];
	Sprite* level_spr[5];

	Text* main[MENU];	//instancia texto para el menu
	Text* level;		//texto para cada nivel de juego			
	Text* ragdolls;		//intancia texto par amostrar cantidad de ragdoll
	// Mensaje del juego
	Text* message;
	Text* exit;			//texto play

	// Fuente de letra a utilizar
	Font* font;

	// Variables
	int selectedItem;
	// Ancho y alto de la ventana
	int width;
	int height;
	// Estado del juego
	int gameState;
	// Elementos
	int items;

public:
	// Constructor
	LP(RenderWindow* _window, int _width, int _height);

	// Inicializa las texturas y textos
	void InitTextAndLevels();

	//Mueve el selector hacia arriba
	void MoveUpMenu();

	//Mueve el selector hacia abajo
	void MoveDownMenu();

	// Dibuja las texturas y texto
	void Draw(RenderWindow* _window, int _state, int _level, int _Ragdolls);
};
