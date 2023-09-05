#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Box2D/Box2D.h"
#include "Object.h"
#include "Ragdoll.h"
#include "LP.h"
#include "SpriteRenderer.h"
#include <list>
using namespace sf;
using namespace std;

const float coordenadaX_cajaFija = 50.5f;	//define posición en x de la cajaFija 
const float coordenadaY_cajaFija = 99.f;	//define posición en y de la cajaFija 

class Game {
private:
	// Propiedades de la ventana
	RenderWindow* wnd;
	Color clearColor;
	int width;
	int height;

	// Mundo del juego
	b2World* World;

	// Procesan los eventos, así como la cámara
	Event* evt;
	View* camera;
	Clock* clock;
	Time* time1;

	// Tiempo de frame
	float frameTime;
	float time2;
	float wait;
	int fps;

	int level;
	int state;
	LP* levelProcessor;
	int selectedObject;

	float offSetX;
	float offSetY;

	// Creando los ragdolls
	Ragdoll* ragd[6];

	int ragdolls;

	// Suelo
	// Creando el suelo
	b2Body* bdy_ground;
	b2BodyDef bdygrd_def;
	b2Fixture* fix_ground;
	b2FixtureDef fixgrd_def;
	// Forma del suelo
	RectangleShape* fig_ground;
	// Estableciendo suelo
	Ragdoll* Ground;
	// Textura y sprite
	Texture* ground_tex;
	Sprite* ground_spr;
	SpriteRenderer* _ground;

	// Cañón
	// Creando el cañón
	b2Body* bdy_canyon;
	b2BodyDef bdycnyn_def;
	b2Fixture* fix_canyon;
	b2FixtureDef fixcnyn_def;
	// Forma del cañón
	RectangleShape* fig_canyon;
	// Estableciendo cañón
	Ragdoll* Canyon;
	// Textura y sprite
	Texture* canyon_tex;
	Sprite* canyon_spr;
	SpriteRenderer* _canyon;

	// Creando la caja de victoria
	b2Body* bdy_victoryBox;
	b2BodyDef bdyVicBox_def;
	b2Fixture* fix_victoryBox;
	b2FixtureDef fixVicBox_def;
	// Forma de las cajas fijas
	Ragdoll* VictoryBox;
	// Estableciendo cajas fijas
	RectangleShape* fig_victoryBox;
	// Textura y sprite
	Texture* VictoryBox_tex;
	Sprite* VictoryBox_spr;
	SpriteRenderer* _victoryBox;
	
	/*
	// Cajas dinámicas/fijas
	// Creando las cajas dinamicas
	b2Body* bdy_dynmcBox[3];
	b2BodyDef bdyDnmBox_def[3];
	b2Fixture* fix_dynmcBox[3];
	b2FixtureDef fixDnmBox_def[3];
	// Forma de las cajas fijas
	Ragdoll* DynamicBox;
	// Estableciendo cajas fijas
	RectangleShape* shp_dynmcBox[3];
	// Textura y sprite
	Texture* DynamicBox_tex[3];
	Sprite* DynamicBox_spr[3];
	// Instancia resortes para caja móvil
	b2DistanceJoint* jnt_dynmcBox;
	b2DistanceJointDef jnt_dynmcBoxDef;
	// Cantidad de cajas en el piso
	int floorBoxes;*/

	// Activa si hay ragdoll o no
	bool Ragdoll_On;

	// Ragdolls
	Ragdoll* RagdollNumber[5];

	bool collission;

public:
	// Constructor
	Game(int _width, int _height, string _title);

	//
	void InitGame();

	// Inicia los elementos del juego
	void InitElements();

	// Setea la cámara
	void SetZoom(Vector2f _Focus, Vector2f _Size, Vector2f _Position);

	// Inicia las físicas del juego
	void InitPhysics();

	// Inicia las texturas de los objetos
	void InitTextures();

	// Loop principal del juego
	void Loop();

	// Controla la variable 
	void gameStateCond();

	// Procesa cosas del menú
	void Conditions();

	// Procesa los eventos externos
	void DoEvents();

	// Controla movimiento del arma
	void UpdateCanyon();

	// Controla cantidad de ragdoll disparados
	void UpdateRagdoll();

	// Actualiza las físicas
	void UpdatePhysics();

	// Mueve el selector hacia arriba
	void SelectPlay();

	// Mueve el selector hacia abajo
	void SelectExit();

	// Chequea las colisiones entre objetos
	void CheckCollitions();

	// Dibujar elementos del juego
	void DrawTheGame();

	// Convierte los grados en radianes
	float deg2rad(float degrees);
};
