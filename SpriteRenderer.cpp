#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(b2Body* _object, Sprite* _sprite) {
	bdy_object = _object;
	spr_object = _sprite;

	SpritePos = bdy_object->GetPosition();

	// Dimensiones maximas
	dims.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dims.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);

	for (b2Fixture* f = bdy_object->GetFixtureList(); f; f = f->GetNext()) {
		dims = f->GetAABB(0);
	}

	spr_object->setOrigin(spr_object->getTexture()->getSize().x / 2.0f, spr_object->getTexture()->getSize().y / 2.0f);
	spr_object->setPosition(SpritePos.x, SpritePos.y);
	spr_object->setRotation(rad2deg(bdy_object->GetAngle()));
	spr_object->setScale(dims.GetExtents().x * 2.0f / spr_object->getTexture()->getSize().x, dims.GetExtents().y * 2.0f / spr_object->getTexture()->getSize().y);
}

void SpriteRenderer::Draw(RenderWindow* _window) {
	SpritePos = bdy_object->GetPosition();

	spr_object->setPosition(SpritePos.x, SpritePos.y);
	spr_object->setRotation(rad2deg(bdy_object->GetAngle()));

	_window->draw(*spr_object);
}

float SpriteRenderer::rad2deg(float rads) {
	return rads * 180 / 3.14f;
}
