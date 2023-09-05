#include "Object.h"

Ragdoll::Ragdoll(b2Body* _body, RectangleShape* _figure): bdy_ragdoll(_body), fig_ragdoll(_figure) 
{
	pos = _body->GetPosition();

	dims.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dims.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);

	for (b2Fixture* i = bdy_ragdoll->GetFixtureList(); i; i = i->GetNext()) {
		dims = i->GetAABB(0);
	}

	fig_ragdoll->setSize({ dims.GetExtents().x * 2, dims.GetExtents().y * 2 });
	fig_ragdoll->setOrigin(fig_ragdoll->getSize().x / 2.f, fig_ragdoll->getSize().y / 2.f);
	fig_ragdoll->setPosition(pos.x, pos.y);
	fig_ragdoll->setRotation(rad2deg(bdy_ragdoll->GetAngle()));
}

void Ragdoll::Draw(RenderWindow* window) {
	pos = bdy_ragdoll->GetPosition();
	fig_ragdoll->setPosition(pos.x, pos.y);
	fig_ragdoll->setRotation(rad2deg(bdy_ragdoll->GetAngle()));
	window->draw(*fig_ragdoll);
}

FloatRect Ragdoll::BoxRagdoll() {
	FloatRect boundingBox = fig_ragdoll->getGlobalBounds();
	return boundingBox;
}

float Ragdoll::rad2deg(float rads) {
	return rads * 180 / 3.1415f;
}
