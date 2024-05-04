#pragma once
#include "SFML/Graphics.hpp"
#include <box2d/box2d.h>
using namespace sf;
using namespace std;

class SpriteRenderer {
private:
	// Define los objetos
	b2Body* bdyObject;
	Sprite* sprObject;

	// Dimensiones
	b2AABB dims;

	// Posicion
	b2Vec2 spritePos;

public:
	// Constructor
	SpriteRenderer(b2Body* _body, Sprite* _sprite);

	// Dibuja los objetos que recibe
	void Draw(RenderWindow* _window);

	// Convierte los radianes en grados
	float RadToDeg(float _radians);
};