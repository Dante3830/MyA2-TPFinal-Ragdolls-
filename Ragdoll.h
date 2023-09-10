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

enum RagdollBodyPart { Head = 0, Torso = 1, LeftArm = 2, RightArm = 3, LeftLeg = 4, RightLeg = 5};

class Ragdoll {
private:
	// Definiendo al ragdoll y sus partes
	RectangleShape* shape_rag[6];
	Object* ragd[6];

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
	Ragdoll(Vector2f pos, b2World& phyWorld);

	// Dibuja el objeto ragdoll
	void Draw(RenderWindow* wnd);

	// Aplica la fuerza al cañón para disparar
	void ApplyForce(Vector2f _mousePos);

	//FloatRect getCloneBounds();

	// Devuelve la posicion del ragdoll
	Vector2f GetPosition(int i);

	// Devuelve el tamanio
	Vector2f GetSize(int i) const;

	// Transforma los radianes en grados
	float RadToDeg(float degrees);

};
