#pragma once
#include "SFML/Graphics.hpp"
#include <box2d/box2d.h>
using namespace sf;
using namespace std;

class SpriteRenderer {
private:
	// Define los objetos
	b2Body* bdy_object;
	Sprite* spr_object;

	// Dimensiones
	b2AABB dims;

	// Posicion
	b2Vec2 SpritePos;

public:
	// Constructor
	SpriteRenderer(b2Body* _object, Sprite* _sprite);

	// Dibuja los objetos que recibe
	void Draw(RenderWindow* _window);

	// Convierte radianes en grados
	float rad2deg(float _radianes);
};
