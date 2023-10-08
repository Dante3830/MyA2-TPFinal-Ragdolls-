#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(b2Body* _body, Sprite* _sprite) : bdyObject(_body), sprObject(_sprite)
{
	// Obtener posicion del objeto con sprite
	spritePos = bdyObject->GetPosition();

	// Dimensiones maximas
	dims.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dims.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);

	for (b2Fixture* f = bdyObject->GetFixtureList(); f; f = f->GetNext()) {
		dims = f->GetAABB(0);
	}

	sprObject->setOrigin(sprObject->getTexture()->getSize().x / 2.0f, sprObject->getTexture()->getSize().y / 2.0f);
	sprObject->setPosition(spritePos.x, spritePos.y);
	sprObject->setRotation(radToDeg(bdyObject->GetAngle()));
	sprObject->setScale(dims.GetExtents().x * 2.0f / sprObject->getTexture()->getSize().x, dims.GetExtents().y * 2.0f / sprObject->getTexture()->getSize().y);
}

void SpriteRenderer::Draw(RenderWindow* _window) {
	// Obtener posición y rotación del objeto a dibujar
	spritePos = bdyObject->GetPosition();

	sprObject->setPosition(spritePos.x, spritePos.y);
	sprObject->setRotation(radToDeg(bdyObject->GetAngle()));

	// Y luego mostrar en pantalla
	_window->draw(*sprObject);
}

float SpriteRenderer::radToDeg(float radians) {
	return radians * 180 / 3.14f;
}