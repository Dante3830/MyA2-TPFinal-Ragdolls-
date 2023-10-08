#include "Ragdoll.h"

Ragdoll::Ragdoll(Vector2f pos, b2World& World) {

	// Definiendo las figuras de las diferentes partes del ragdoll
	b2PolygonShape shp_rag[6];

	// Cabeza
	shp_rag[0].SetAsBox(0.1, 0.1);
	
	// Torso
	shp_rag[1].SetAsBox(0.2, 0.4);
	
	// Brazos
	shp_rag[2].SetAsBox(0.07, 0.3);
	shp_rag[3].SetAsBox(0.07, 0.3);
	
	// Piernas
	shp_rag[4].SetAsBox(0.07, 0.4);
	shp_rag[5].SetAsBox(0.07, 0.4);

	//x = 50.0, y = 90.0

	//Posicionando el ragdoll
	// Cabeza
	bdyDef_Rag[0].position = b2Vec2(pos.x, pos.y + 0.1f);
	// Torso
	bdyDef_Rag[1].position = b2Vec2(pos.x, pos.y + 0.65f);
	// Brazo Izq
	bdyDef_Rag[2].position = b2Vec2(pos.x - 0.32f, pos.y + 0.5f);
	// Brazo Der
	bdyDef_Rag[3].position = b2Vec2(pos.x + 0.32f, pos.y + 0.5f);
	// Pierna Izq
	bdyDef_Rag[4].position = b2Vec2(pos.x - 0.09f, pos.y + 1.5f); 
	// Pierna Der
	bdyDef_Rag[5].position = b2Vec2(pos.x + 0.09f, pos.y + 1.5f); 

	//Definimos al radgoll
	for (int i = 0; i < 6; i++) {
		bdyDef_Rag[i].type = b2_dynamicBody;
		bdy_Rag[i] = World.CreateBody(&bdyDef_Rag[i]);

		FixDef_Rag[i].shape = &shp_rag[i];
		FixDef_Rag[i].density = 0.1f;
		FixDef_Rag[i].friction = 0.5f;
		FixDef_Rag[i].restitution = 0.1f;

		fix_Rag[i] = bdy_Rag[i]->CreateFixture(&FixDef_Rag[i]);
	}

	// Definimos sus resortes

	// 1: Cabeza + Torso
	jointRagDef[0].Initialize(bdy_Rag[0], bdy_Rag[1], b2Vec2(bdy_Rag[0]->GetPosition().x, bdy_Rag[0]->GetPosition().y + 0.08),
		b2Vec2(bdy_Rag[1]->GetPosition().x, bdy_Rag[1]->GetPosition().y - 0.38));
	// 2: Brazo Der + Torso
	jointRagDef[1].Initialize(bdy_Rag[1], bdy_Rag[2], b2Vec2(bdy_Rag[1]->GetPosition().x + 0.18, bdy_Rag[1]->GetPosition().y - 0.38),
		b2Vec2(bdy_Rag[2]->GetPosition().x - 0.05, bdy_Rag[2]->GetPosition().y - 0.28));
	// 3: : Brazo Izq + Torso
	jointRagDef[2].Initialize(bdy_Rag[1], bdy_Rag[3], b2Vec2(bdy_Rag[1]->GetPosition().x - 0.18, bdy_Rag[1]->GetPosition().y - 0.38),
		b2Vec2(bdy_Rag[3]->GetPosition().x + 0.05, bdy_Rag[3]->GetPosition().y - 0.28));
	// 4: Pierna Der + Torso
	jointRagDef[3].Initialize(bdy_Rag[1], bdy_Rag[4], b2Vec2(bdy_Rag[1]->GetPosition().x + 0.09, bdy_Rag[1]->GetPosition().y + 0.38),
		b2Vec2(bdy_Rag[4]->GetPosition().x, bdy_Rag[4]->GetPosition().y - 0.38));
	// 5: Pierna Izq + Torso
	jointRagDef[4].Initialize(bdy_Rag[1], bdy_Rag[5], b2Vec2(bdy_Rag[1]->GetPosition().x + 0.09, bdy_Rag[1]->GetPosition().y + 0.38),
		b2Vec2(bdy_Rag[5]->GetPosition().x, bdy_Rag[5]->GetPosition().y - 0.38));

	// Definiendo la física de los joints
	for (int i = 0; i < 5; i++) {
		jointRagDef[i].damping = 0.3f;
		jointRagDef[i].stiffness = 0.9f;
		jointRagDef[i].collideConnected = true;
		jointRagDef[i].length = 0.00025f;
		jointRag[i] = (b2DistanceJoint*)World.CreateJoint(&jointRagDef[i]);
	}

	for (int i = 0; i < 6; i++) {
		shapeRag[i] = new RectangleShape;
	}

	// Definiendo los colores de cada parte
	shapeRag[0]->setFillColor(Color::Color(0, 200, 0));
	shapeRag[1]->setFillColor(Color::Yellow);
	shapeRag[2]->setFillColor(Color::Red);
	shapeRag[3]->setFillColor(Color::Red);
	shapeRag[4]->setFillColor(Color::Blue);
	shapeRag[5]->setFillColor(Color::Blue);

	for (int i = 0; i < 6; i++) {
		ragdollParts[i] = new Object(bdy_Rag[i], shapeRag[i]);
	}

}

void Ragdoll::Draw(RenderWindow* _window) {
	for (int i = 0; i < 6; i++) {
		ragdollParts[i]->Draw(_window);
	}
}

void Ragdoll::applyForce(Vector2f _mousePos) {
	for (int i = 0; i < 6; i++) {
		bdy_Rag[i]->ApplyForceToCenter(b2Vec2(_mousePos.x * 10, _mousePos.y * 10), false);
	}
}

FloatRect Ragdoll::getRagdollBounds(int i) {
	FloatRect RagdollBox = shapeRag[i]->getGlobalBounds();
	return RagdollBox;
}

Vector2f Ragdoll::getPosition(int i) {
	Vector2f RagdollPos = Vector2f (shapeRag[i]->getPosition());
	return RagdollPos;
}

float Ragdoll::radToDeg(float radians) {
	return radians * 180 / 3.1415;
}