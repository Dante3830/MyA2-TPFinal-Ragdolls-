#pragma once
#include "SFML/Graphics.hpp"
#include <box2d/box2d.h>
using namespace sf;
using namespace std;

class Object {
private:
	// Objetos del ragdoll
	b2Body* bdyObject;
	RectangleShape* figObject;

	// Dimensiones y posición del ragdoll
	b2AABB dims;
	b2Vec2 pos;

public:
	// Constructor de la clase
	Object(b2Body* _body, RectangleShape* _figure);

	// Dibuja todas las partes del cuerpo del ragdoll
	void Draw(RenderWindow* window);

	// Devuelve el bounding box de la figura
	FloatRect BoxObject();

	// Convierte los radianes en grados
	float RadToDeg(float _radians);

};