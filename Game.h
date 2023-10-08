#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include <list>
#include "Ragdoll.h"
#include "LP.h"
#include "SpriteRenderer.h"
using namespace sf;
using namespace std;

class Game {
private:
	// Propiedades de la ventana
	RenderWindow* window;
	Color clearColor;
	int width;
	int height;

	float offsetX_boxes;	//offset de las cajas, se alejan en x según incrementan el nivel
	float offsetY_boxes;	//offset de las cajas, se alejan en Y según incrementan el nivel

	// Mundo del juego
	b2World* world;

	// Procesan los eventos, así como la cámara y el reloj
	Event* evt;
	View* camera;
	Clock* clock;

	// Tiempo de frame
	float frameTime;
	Time* time1;
	float time2;
	int fps;

	// Tiempo de espera del nivel
	float wait;

	// Posición en X e Y de la caja quieta
	float StoppedBox_X = 55.5f;
	float StoppedBox_Y = 99.f;

	// Nivel del juego
	int level;

	// Estado del juego
	int state;

	// Procesador del nivel (gráficos y textos)
	LP* levelProcessor;

	// Objeto seleccionado del menú
	int selectedObject;

	// Creando los ragdolls
	Ragdoll* ragdolls[6];

	// Cuenta la cantidad de ragdolls disponibles para disparar
	int ragdollCount;

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
	SpriteRenderer* SR_Ground;

	// Cañón
	// Creando el cañón que dispara los ragdolls
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
	SpriteRenderer* SR_Canyon;

	// CAJA QUIETA
	// Creando la caja quieta que sostiene la de victoria
	b2Body* Bdy_StoppedBox;
	b2BodyDef BdyStpBox_Def;
	b2Fixture* Fix_StpBox;
	b2FixtureDef FixStpBox_Def;
	// Forma de las caja quieta
	Ragdoll* StoppedBox;
	// Estableciendo caja fija
	RectangleShape* Fig_StoppedBox;
	// Textura y sprite
	Texture* StoppedBox_Tex;
	Sprite* StoppedBox_Spr;
	SpriteRenderer* SR_StoppedBox;

	// CAJA DE VICTORIA
	// Creando la caja de victoria
	b2Body* Bdy_VictoryBox;
	b2BodyDef BdyVicBox_Def;
	b2Fixture* Fix_VictoryBox;
	b2FixtureDef FixVicBox_Def;
	// Forma de la caja de victoria
	Ragdoll* VictoryBox;
	// Estableciendo caja de victoria
	RectangleShape* Fig_VictoryBox;
	// Textura y sprite
	Texture* VictoryBox_Tex;
	Sprite* VictoryBox_Spr;
	SpriteRenderer* SR_VictoryBox;

	// OBSTÁCULOS
	// Creando las cajas de obstáculos
	b2Body* Bdy_Obstacle;
	b2BodyDef BdyObstacle_Def;
	b2Fixture* Fix_Obstacle;
	b2FixtureDef FixObstacle_Def;
	// Forma de la caja de victoria
	Ragdoll* Obstacle;
	// Estableciendo caja de victoria
	RectangleShape* Fig_Obstacle;
	// Textura y sprite
	Texture* Obstacle_Tex;
	Sprite* Obstacle_Spr;
	SpriteRenderer* SR_Obstacle;

	// Instancia resortes para caja móvil
	//b2DistanceJoint* Jnt_StoppedBox;
	//b2DistanceJointDef Jnt_StoppedBoxDef;

	// Cantidad de cajas en el piso
	int floorBoxes;

	// Activa si hay ragdoll o no
	bool ragdollOn;

	// Ragdolls
	Ragdoll* ragdollNumber[5];

public:
	// Constructor
	Game(int _width, int _height, string _title);

	// Inicia el juego
	void gameStart();

	// Inicia los elementos del juego
	void initElements();

	// Setea la cámara
	void setZoom(Vector2f _focus, Vector2f _size, Vector2f _position);

	// Inicia las físicas del juego
	void initPhysics();

	// Inicia las texturas de los objetos
	void initTextures();

	// Loop principal del juego
	void Loop();

	// Controla la variable 
	void gameState();

	// Procesa cosas del menú
	void checkWinningCondition();

	// Procesa los eventos externos
	void doEvents();

	// Controla movimiento del arma
	void updateCanyon();

	// Controla cantidad de ragdolls disparados
	void updateRagdoll();

	// Actualiza las físicas
	void updatePhysics();

	// Mueve el selector hacia arriba
	void selectUp();

	// Mueve el selector hacia abajo
	void selectDown();

	// Chequea las colisiones entre objetos
	void checkCollisions();

	// Dibujar elementos del juego
	void drawTheGame();

	// Convierte los grados en radianes
	float degToRad(float degrees);
};