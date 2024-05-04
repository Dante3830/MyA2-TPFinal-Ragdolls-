#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include <list>
#include "Object.h"
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
	void Draw(RenderWindow& wnd);

	// Aplica la fuerza al ragdoll a disparar
	void ApplyForce(Vector2f _mousePos);

	// Devuelve el Bounding Box del Ragdoll
	FloatRect GetRagdollBounds(int i);

	// Devuelve la posición del ragdoll
	Vector2f GetPosition(int i);

	// Transforma los radianes en grados
	float RadToDeg(float _radians);

};