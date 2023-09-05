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

class Clone {
private:
	// Definiendo al ragdoll y sus partes
	RectangleShape* shape_rag[6];
	Ragdoll* ragd[6];

	// Definiendo al cuerpo y fixture del ragdoll
	b2Body* bdy_rag[6];
	b2BodyDef bdyDef_rag[6];
	b2Fixture* fix_rag[6];
	b2FixtureDef fixDef_rag[6];

	// Definimos sus resortes
	b2DistanceJoint* jointRag[5];
	b2DistanceJointDef jointRagDef[5];

public:
	// Constructor
	Clone(Vector2f pos, b2World& phyWorld);

	// Dibuja el objeto ragdoll
	void Draw(RenderWindow* wnd);

	// Aplica la fuerza al cañón para disparar
	void applyForce(Vector2f _mousePos);

	//FloatRect getCloneBounds();

	Vector2f GetPosition(int i);

	Vector2f GetSize(int i) const;

	// Transforma los radianes en grados
	float rad2deg(float grados);

};
