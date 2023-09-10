#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(b2Body* _object, Sprite* _sprite) {
	Bdy_Object = _object;
	Spr_Object = _sprite;

	SpritePos = Bdy_Object->GetPosition();

	// Dimensiones maximas
	Dims.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	Dims.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);

	for (b2Fixture* f = Bdy_Object->GetFixtureList(); f; f = f->GetNext()) {
		Dims = f->GetAABB(0);
	}

	Spr_Object->setOrigin(Spr_Object->getTexture()->getSize().x / 2.0f, Spr_Object->getTexture()->getSize().y / 2.0f);
	Spr_Object->setPosition(SpritePos.x, SpritePos.y);
	Spr_Object->setRotation(RadToDeg(Bdy_Object->GetAngle()));
	Spr_Object->setScale(Dims.GetExtents().x * 2.0f / Spr_Object->getTexture()->getSize().x, Dims.GetExtents().y * 2.0f / Spr_Object->getTexture()->getSize().y);
}

void SpriteRenderer::Draw(RenderWindow* _window) {
	SpritePos = Bdy_Object->GetPosition();

	Spr_Object->setPosition(SpritePos.x, SpritePos.y);
	Spr_Object->setRotation(RadToDeg(Bdy_Object->GetAngle()));

	_window->draw(*Spr_Object);
}

float SpriteRenderer::RadToDeg(float _radians) {
	return _radians * 180 / 3.14f;
}
