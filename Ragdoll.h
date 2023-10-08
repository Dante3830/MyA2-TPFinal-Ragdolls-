#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include <box2d/box2d.h>
#include "Object.h"
#include <list>
using namespace sf;
using namespace std;

class Ragdoll {
private:
	// Definiendo al ragdoll y sus partes
	RectangleShape* shapeRag[6];
	Object* ragdollParts[6];

	// Definiendo al cuerpo y fixture del ragdoll
	b2Body* bdy_Rag[6];
	b2BodyDef bdyDef_Rag[6];
	b2Fixture* fix_Rag[6];
	b2FixtureDef FixDef_Rag[6];

	// Definimos sus resortes
	b2DistanceJoint* jointRag[5];
	b2DistanceJointDef jointRagDef[5];

public:
	// Constructor
	Ragdoll(Vector2f pos, b2World& phyWorld);

	// Dibuja el objeto ragdoll
	void Draw(RenderWindow* wnd);

	// Aplica la fuerza al cañón para disparar
	void applyForce(Vector2f _mousePos);

	// Devuelve el Bounding Box del Ragdoll
	FloatRect getRagdollBounds(int i);

	// Devuelve la posición del ragdoll
	Vector2f getPosition(int i);

	// Transforma los radianes en grados
	float radToDeg(float degrees);

};