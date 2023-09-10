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

const float coordenateX_stoppedBox = 50.5f;	//define posición en x de la cajaFija 
const float coordenateY_stoppedBox = 99.f;	//define posición en y de la cajaFija 

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
	Ragdoll* ragdolls[6];

	int RagdollCount;

	// Suelo
	// Creando el suelo
	b2Body* Bdy_Ground;
	b2BodyDef BdyGrd_Def;
	b2Fixture* Fix_Ground;
	b2FixtureDef FixGrd_Def;
	// Forma del suelo
	RectangleShape* Fig_Ground;
	// Estableciendo suelo
	Ragdoll* Ground;
	// Textura y sprite
	Texture* Ground_Tex;
	Sprite* Ground_Spr;
	SpriteRenderer* _Ground;

	// Cañón
	// Creando el cañón
	b2Body* Bdy_Canyon;
	b2BodyDef BdyCnyn_Def;
	b2Fixture* Fix_Canyon;
	b2FixtureDef FixCnyn_Def;
	// Forma del cañón
	RectangleShape* Fig_Canyon;
	// Estableciendo cañón
	Ragdoll* Canyon;
	// Textura y sprite
	Texture* Canyon_Tex;
	Sprite* Canyon_Spr;
	SpriteRenderer* _Canyon;

	// Creando la caja de victoria
	b2Body* Bdy_VictoryBox;
	b2BodyDef BdyVicBox_Def;
	b2Fixture* Fix_VictoryBox;
	b2FixtureDef FixVicBox_Def;
	// Forma de las cajas fijas
	Ragdoll* VictoryBox;
	// Estableciendo cajas fijas
	RectangleShape* Fig_VictoryBox;
	// Textura y sprite
	Texture* VictoryBox_Tex;
	Sprite* VictoryBox_Spr;
	SpriteRenderer* _VictoryBox;
	
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
	bool RagdollOn;

	// Ragdolls
	Ragdoll* RagdollNumber[5];

	bool Collission;

public:
	// Constructor
	Game(int _width, int _height, string _title);

	// Inicia el juego
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
	void GameState();

	// Procesa cosas del menú
	void CheckWinningCondition();

	// Procesa los eventos externos
	void DoEvents();

	// Controla movimiento del arma
	void UpdateCanyon();

	// Controla cantidad de ragdolls disparados
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
	float DegToRad(float degrees);
};
