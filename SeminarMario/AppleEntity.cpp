#include "AppleEntity.h"
#include "Config.h"
#include <Windows.h>

void AppleEntity::onNotify(Event const& e)
{
	if (e.sender == EventSenders::SENDER_KEYBOARD
		&&
		e.type == EventTypes::EVENT_KEY_PRESSED
		&&
		e.code == EventCodes::KEY_THROW)
	{
		std::cout << "creat apple!!!!!";
		_isDraw = true;
		_state->getPhysics()->getTL();
	//	reset(hero->getState()->getPhysics()->getTL());
	}
	if (e.sender == EventSenders::SENDER_ENTITY_STATE
		&&
		e.type == EventTypes::EVENT_PHYSICS
		&&
		e.code == EventCodes::APPLE_OUT_RANGE ||
		e.sender == EventSenders::SENDER_ENTITY_STATE
		&&
		e.type == EventTypes::EVENT_PHYSICS
		&&
		e.code == EventCodes::COLLISION_APPLE_ENEMY)
	{
		_isDraw = false;
	}
}

void AppleEntity::reset(cv::Point const& TL)
{
	Entity::reset(TL);
}

bool AppleEntity::checkCollision(std::shared_ptr<Entity> other)
{
	if (this->_state->getPhysics()->checkCollision(other->getState()->getPhysics())) {
		std::cout << "apple collition slime!!!!" << std::endl;
		_state->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::COLLISION_APPLE_ENEMY });
		this->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::COLLISION_APPLE_ENEMY });
		return true;
	}
	if (this->_state->getPhysics()->getTL().x >= GetSystemMetrics(SM_CXFULLSCREEN))
		_state->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::APPLE_OUT_RANGE });
	return false;
}

void AppleEntity::draw(cv::Mat& canvas)
{
	_state->draw(canvas);
}

bool AppleEntity::isDraw()
{
	return _isDraw;
}
