#include "Object.h"

Object::Object(b2Body* _body, RectangleShape* _figure) : bdyObject(_body), figObject(_figure)
{
	// Obtener posicion del objeto
	pos = bdyObject->GetPosition();

	// Dimensiones maximas
	dims.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dims.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);

	for (b2Fixture* i = bdyObject->GetFixtureList(); i; i = i->GetNext()) {
		dims = i->GetAABB(0);
	}

	figObject->setSize({ dims.GetExtents().x * 2, dims.GetExtents().y * 2 });
	figObject->setOrigin(figObject->getSize().x / 2.f, figObject->getSize().y / 2.f);
	figObject->setPosition(pos.x, pos.y);
	figObject->setRotation(RadToDeg(bdyObject->GetAngle()));
}

void Object::Draw(RenderWindow* window) {
	// Obtiene la posicion y rotación del objeto
	pos = bdyObject->GetPosition();
	figObject->setPosition(pos.x, pos.y);
	figObject->setRotation(RadToDeg(bdyObject->GetAngle()));

	// Y luego lo muestra en pantalla
	window->draw(*figObject);
}

FloatRect Object::BoxObject() {
	FloatRect BoundingBox = figObject->getGlobalBounds();
	return BoundingBox;
}

float Object::RadToDeg(float _radians) {
	return _radians * 180 / 3.1416f;
}