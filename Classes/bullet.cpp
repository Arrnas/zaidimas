#include "bullet.h"
#include "HelloWorldScene.h"
bullet::bullet(string passName,
	int passX,int passY,
	HelloWorld * th,CCPoint point,b2World *_world,int id):world(_world),that(th),ID(id)
{
	_sprite = CCSprite::spriteWithSpriteFrameName(passName.c_str());
	th->addChild(_sprite);
	// Create ball body and shape
	b2BodyDef boxBodyDef;
	boxBodyDef.type = b2_dynamicBody;
	boxBodyDef.userData = this;
	boxBodyDef.bullet = true;
	boxBodyDef.position.Set(passX/PTM_RATIO, passY/PTM_RATIO);
	_body = _world->CreateBody(&boxBodyDef);

	b2PolygonShape boxDef;
	boxDef.SetAsBox(3/PTM_RATIO,1/PTM_RATIO);
	 
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &boxDef;
	boxShapeDef.density = 1.0f;
	boxShapeDef.friction = 1.0f;
	boxShapeDef.restitution = 0.1f;
	_body->CreateFixture(&boxShapeDef);
	_body->ApplyLinearImpulse(b2Vec2(point.x/PTM_RATIO,point.y/PTM_RATIO),_body->GetPosition());

}
bullet::~bullet()
{ 
	that->removeChild(_sprite,true); 
	world->DestroyBody(_body);
}