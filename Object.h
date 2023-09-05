#pragma once
#include "SFML/Graphics.hpp"
#include <box2d/box2d.h>
using namespace sf;
using namespace std;

enum EnumRagdoll{ground, canyon, dynamicBox, stoppedBox};

class Ragdoll {
private:
	// Objetos del ragdoll
	b2Body* bdy_ragdoll;
	RectangleShape* fig_ragdoll;

	// Dimensiones y posición del ragdoll
	b2AABB dims;
	b2Vec2 pos;

	EnumRagdoll type;

public:
	// Constructor de la clase
	Ragdoll(b2Body* _body, RectangleShape* _figure);

	// Dibuja todas las partes del cuerpo del ragdoll
	void Draw(RenderWindow* window);

	// Devuelve el bounding box de la figura
	FloatRect BoxRagdoll();

	// Convierte los radianes en grados
	float rad2deg(float rads);

};
