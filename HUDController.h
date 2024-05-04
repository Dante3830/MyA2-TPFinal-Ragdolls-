#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#define OPTION 2
using namespace sf;
using namespace std;

class HUDController {
private:

	// Ventana
	RenderWindow* window;

	// Alto y ancho de la ventana
	int height;
	int width;

	// Selector del menú
	int selectedOption;

	// Estado del juego
	int state;

	// Texturas y sprites para los niveles
	Texture* levelTex[7];
	Sprite* levelSpr[7];

	// Fuente de letra del juego
	Font* font;
	
	// Texto del menú, nivel, salida, mensaje y cantidad de ragdolls
	Text* select[OPTION];
	Text* levelTxt;		
	Text* exitTxt;
	Text* messageTxt;
	Text* ragdollQuantityTxt;

public:

	// Constructor de la clase
	HUDController(RenderWindow* _window, int _height, int _width);

	// Inicia los sprites y textos
	void InitSpritesAndTexts();

	// Dibuja el HUD en pantalla
	void Draw(RenderWindow* _window, int _state, int _level, int _ragdollsQuantity);

	// Elige la primera opción
	void SelectUp();

	// Elige la segunda opción
	void SelectDown();
};
