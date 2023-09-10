#pragma once
#include "SFML/Graphics.hpp"
#include <box2d/box2d.h>
using namespace sf;
using namespace std;

enum EnumRagdoll{Ground, Canyon, DynamicBox, stoppedBox};

class Object {
private:
	// Objetos del ragdoll
	b2Body* Bdy_Object;
	RectangleShape* Fig_Object;

	// Dimensiones y posición del ragdoll
	b2AABB Dims;
	b2Vec2 Pos;

	EnumRagdoll Type;

public:
	// Constructor de la clase
	Object(b2Body* _body, RectangleShape* _figure);

	// Dibuja todas las partes del cuerpo del ragdoll
	void Draw(RenderWindow* window);

	// Devuelve el bounding box de la figura
	FloatRect BoxObject();

	// Convierte los radianes en grados
	float RadToDeg(float rads);

};
