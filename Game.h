#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Ragdoll.h"
#include "SpriteRenderer.h"
#include "HUDController.h"
using namespace std;
using namespace sf;

class Game {
private:
	// Ventana del juego
	RenderWindow* window;
	
	// Alto y ancho de la ventana
	int height;
	int width;

	// Controlador de la HUD
	HUDController* hudController;

	// Mundo del juego
	b2World* world;

	// Posición en X e Y de la caja fija
	float coordenadaX_cajaFija = 53.5f;
	float coordenadaY_cajaFija = 99.f;

	//variables del juego
	float frameTime;
	float offsetX_cajas;
	float offsetY_cajas;

	// FPS del juego
	int fps;

	// Nivel del juego
	int level;

	// Estado del juego
	int state;
	// 0 = Menú principal
	// 1 = Juego
	// 2 = Salida
	// 3 = Victoria
	// 4 = Derrota
	// 5 = Juego completado
	// 6 = Reiniciar juego

	// Eventos y cámara
	Event* evt;
	View* camera;

	// Reloj y tiempos
	Clock* clock;
	Time* time1;
	float time2;
	float waitTime;

	// Verifica si se puede disparar ragdolls
	bool ragdollOn;

	// Opción seleccionada
	int selectedOption;

	// Ragdolls del juego
	Ragdoll* ragdolls[5];

	// Cantidad de ragdolls
	int ragdollQuantity;

	// OBJETOS DEL JUEGO
	// Cañón
	Texture* canyonTex;
	Sprite* canyonSpr;
	b2Body* canyonBody;
	b2BodyDef canyonBodyDef;
	b2Fixture* canyonFix;
	b2FixtureDef canyonFixDef;
	RectangleShape* canyonFig;
	SpriteRenderer* canyonSR;
	
	// Piso
	Texture* groundTex;
	Sprite* groundSpr;
	b2Body* groundBody;
	b2BodyDef groundBodyDef;
	b2Fixture* groundFix;
	b2FixtureDef groundFixDef;
	RectangleShape* groundFig;
	SpriteRenderer* groundSR;

	// Obstáculo 1
	Texture* obstacle1Tex;
	Sprite* obstacle1Spr;
	b2Body* obstacle1Body;
	b2BodyDef obstacle1BodyDef;
	b2Fixture* obstacle1Fix;
	b2FixtureDef obstacle1FixDef;
	Object* obstacle1Object;
	RectangleShape* obstacle1Fig;
	SpriteRenderer* obstacle1SR;

	// Obstáculo 2
	Texture* obstacle2Tex;
	Sprite* obstacle2Spr;
	b2Body* obstacle2Body;
	b2BodyDef obstacle2BodyDef;
	b2Fixture* obstacle2Fix;
	b2FixtureDef obstacle2FixDef;
	Object* obstacle2Object;
	RectangleShape* obstacle2Fig;
	SpriteRenderer* obstacle2SR;

	// Péndulo
	b2DistanceJoint* pendulumBoxJoint;
	b2DistanceJointDef pendulumBoxJointDef;

	// Caja 1 del péndulo
	Texture* pendulumBox1Tex;
	Sprite* pendulumBox1Spr;
	b2Body* pendulumBox1Body;
	b2BodyDef pendulumBox1BodyDef;
	b2Fixture* pendulumBox1Fix;
	b2FixtureDef pendulumBox1FixDef;
	RectangleShape* pendulumBox1Fig;
	SpriteRenderer* pendulumBox1SR;

	// Caja 2 del péndulo
	Texture* pendulumBox2Tex;
	Sprite* pendulumBox2Spr;
	b2Body* pendulumBox2Body;
	b2BodyDef pendulumBox2BodyDef;
	b2Fixture* pendulumBox2Fix;
	b2FixtureDef pendulumBox2FixDef;
	RectangleShape* pendulumBox2Fig;
	SpriteRenderer* pendulumBox2SR;

	// Caja de victoria
	Texture* victoryBoxTex;
	Sprite* victoryBoxSpr;
	b2Body* victoryBoxBody;
	b2BodyDef victoryBoxBodyDef;
	b2Fixture* victoryBoxFix;
	b2FixtureDef victoryBoxFixDef;
	Object* victoryBoxObject;
	RectangleShape* victoryBoxFig;
	SpriteRenderer* victoryBoxSR;

	// Caja que sostiene la de victoria
	Texture* holdBoxTex;
	Sprite* holdBoxSpr;
	b2Body* holdBoxBody;
	b2BodyDef holdBoxBodyDef;
	b2Fixture* holdBoxFix;
	b2FixtureDef holdBoxFixDef;
	Object* holdBoxObject;
	RectangleShape* holdBoxFig;
	SpriteRenderer* holdBoxSR;

	// Verifica si la caja de victoria está en el piso
	bool isVictoryBoxOnTheFloor;

public:

	// Constructor de la clase
	Game(int _height, int _width, string _title);

	// Inicia los elementos
	void InitElements();

	// Inicia el juego
	void GameStart();

	// Inicia la cámara
	void SetZoom(Vector2f _center, Vector2f _size, Vector2f _offset);

	// Inicia las físicas
	void InitPhysics();

	// Inicia los sprites
	void InitSprites();

	// Inicia objetos
	void InitObjects();

	// Bucle del juego
	void Loop();

	// Reacciona según como esté el int "state"
	void StateOfTheGame();

	// Procesa los menú
	void ConditionGame();

	// Procesa eventos
	void ProssesEvent();

	// Controla movimiento del cañón
	void UpdateCanyon();

	// Controla la cantidad de ragdolls disparados
	void UpdateRagdoll();

	// Actualiza la física
	void UpdatePhysics();

	// Selecciona la primera opción
	void SelectUp();

	// Selecciona la segunda opción
	void SelectDown();

	//Controla el cambio de nivel de juego
	void CheckColission();

	// Dibuja los elementos del juego
	void DrawTheGame();

	// Convierte los grados a radianes
	float DegToRad(float _degrees);

};