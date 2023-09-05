#include "Ragdoll.h"

Ragdoll::Ragdoll(Vector2f pos, b2World& World) {

	b2PolygonShape shp_rag[6];

	shp_rag[0].SetAsBox(0.1, 0.1);
	shp_rag[1].SetAsBox(0.2, 0.4);
	shp_rag[2].SetAsBox(0.07, 0.3);
	shp_rag[3].SetAsBox(0.07, 0.3);
	shp_rag[4].SetAsBox(0.07, 0.4);
	shp_rag[5].SetAsBox(0.07, 0.4);

	//x = 50.0, y = 90.0

	//Posicionando el ragdoll
	// Cabeza
	bdyDef_rag[0].position = b2Vec2(pos.x, pos.y + 0.1f);
	// Cuerpo
	bdyDef_rag[1].position = b2Vec2(pos.x, pos.y + 0.65f);
	// Brazo Izq
	bdyDef_rag[2].position = b2Vec2(pos.x - 0.32f, pos.y + 0.5f);
	// Brazo Der
	bdyDef_rag[3].position = b2Vec2(pos.x + 0.32f, pos.y + 0.5f);
	// Pierna Izq
	bdyDef_rag[4].position = b2Vec2(pos.x - 0.09f, pos.y + 1.5f); 
	// Pierna Der
	bdyDef_rag[5].position = b2Vec2(pos.x + 0.09f, pos.y + 1.5f); 

	//Definimos al radgoll
	for (int i = 0; i < 6; i++) {
		bdyDef_rag[i].type = b2_dynamicBody;
		bdy_rag[i] = World.CreateBody(&bdyDef_rag[i]);
	}

	for (int i = 0; i < 6; i++) {
		fixDef_rag[i].shape = &shp_rag[i];
		fixDef_rag[i].density = 0.1f;
		fixDef_rag[i].friction = 0.5f;
		fixDef_rag[i].restitution = 0.1f;

		fix_rag[i] = bdy_rag[i]->CreateFixture(&fixDef_rag[i]);
	}

	// Definimos sus resortes

	// 1: Cabeza + Torso
	jointRagDef[0].Initialize(bdy_rag[0], bdy_rag[1], b2Vec2(bdy_rag[0]->GetPosition().x, bdy_rag[0]->GetPosition().y + 0.08),
		b2Vec2(bdy_rag[1]->GetPosition().x, bdy_rag[1]->GetPosition().y - 0.38));
	// 2: Brazo Der + Torso
	jointRagDef[1].Initialize(bdy_rag[1], bdy_rag[2], b2Vec2(bdy_rag[1]->GetPosition().x + 0.18, bdy_rag[1]->GetPosition().y - 0.38),
		b2Vec2(bdy_rag[2]->GetPosition().x - 0.05, bdy_rag[2]->GetPosition().y - 0.28));
	// 3: : Brazo Izq + Torso
	jointRagDef[2].Initialize(bdy_rag[1], bdy_rag[3], b2Vec2(bdy_rag[1]->GetPosition().x - 0.18, bdy_rag[1]->GetPosition().y - 0.38),
		b2Vec2(bdy_rag[3]->GetPosition().x + 0.05, bdy_rag[3]->GetPosition().y - 0.28));
	// 4: Pierna Der + Torso
	jointRagDef[3].Initialize(bdy_rag[1], bdy_rag[4], b2Vec2(bdy_rag[1]->GetPosition().x + 0.09, bdy_rag[1]->GetPosition().y + 0.38),
		b2Vec2(bdy_rag[4]->GetPosition().x, bdy_rag[4]->GetPosition().y - 0.38));
	// 5: Pierna Izq + Torso
	jointRagDef[4].Initialize(bdy_rag[1], bdy_rag[5], b2Vec2(bdy_rag[1]->GetPosition().x + 0.09, bdy_rag[1]->GetPosition().y + 0.38),
		b2Vec2(bdy_rag[5]->GetPosition().x, bdy_rag[5]->GetPosition().y - 0.38));

	for (int i = 0; i < 5; i++) {
		jointRagDef[i].damping = 0.3f;
		jointRagDef[i].stiffness = 0.9f;
		jointRagDef[i].collideConnected = true;
		jointRagDef[i].length = 0.00025f;
		jointRag[i] = (b2DistanceJoint*)World.CreateJoint(&jointRagDef[i]);
	}

	for (int i = 0; i < 6; i++) {
		shape_rag[i] = new RectangleShape;
	}

	shape_rag[0]->setFillColor(Color::Color(0, 200, 0));
	shape_rag[1]->setFillColor(Color::Yellow);
	shape_rag[2]->setFillColor(Color::Red);
	shape_rag[3]->setFillColor(Color::Red);
	shape_rag[4]->setFillColor(Color::Blue);
	shape_rag[5]->setFillColor(Color::Blue);

	for (int i = 0; i < 6; i++) {
		ragd[i] = new Object(bdy_rag[i], shape_rag[i]);
	}

}

float Ragdoll::rad2deg(float radians) {
	return radians * 180 / 3.1415;
}

void Ragdoll::Draw(RenderWindow* _window) {
	for (int i = 0; i < 6; i++) {
		ragd[i]->Draw(_window);
	}
}

void Ragdoll::applyForce(Vector2f _mousePos) {
	for (int i = 0; i < 6; i++) {
		bdy_rag[i]->ApplyForceToCenter(b2Vec2(_mousePos.x * 10, _mousePos.y * 10), false);
	}
}

//FloatRect Clone::getCloneBounds() {
//	FloatRect CloneBounds;
//	for (int i = 0; i < 6; i++) {
//		CloneBounds = shape_rag[i]->getGlobalBounds();
//	}
//	return CloneBounds;
//}

Vector2f Ragdoll::GetPosition(int i) {
	b2Vec2 ClonePos = bdy_rag[i]->GetPosition();
	return Vector2f(ClonePos.x, ClonePos.y);
}

Vector2f Ragdoll::GetSize(int i) const {
	b2PolygonShape* shape = static_cast<b2PolygonShape*>(fix_rag[i]->GetShape());
	b2Vec2 size = shape->m_vertices[2] - shape->m_vertices[0];
	return Vector2f(size.x, size.y);
}
