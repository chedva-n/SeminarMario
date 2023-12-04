#include "LivesEntity.h"
#include "Entities.h"
#include "Config.h"
#include "CreateEntities.h"
#include "EntitiesPool.h"
using namespace cv;
using namespace std;

LivesEntity::LivesEntity():Entity(CreateLivesState()){}

void LivesEntity::onNotify(Event const& e)
{
	if (e.sender == EventSenders::SENDER_ENTITY_STATE
		&&
		e.type == EventTypes::EVENT_PHYSICS
		&&
		e.code == EventCodes::COLLISION_WITH_ENEMY )
	{
		_state->getGraphics()->reset(-1);
		cout << "Collision!!!!" << endl;
	}
	if (e.sender == EventSenders::SENDER_ENTITY_STATE
		&&
		e.type == EventTypes::EVENT_PHYSICS
		&&
		e.code == EventCodes::COLLISION_APPLE_ENEMY) {
		_state->getGraphics()->reset(1);
	}
	auto newStateCandidate = _state->tryModifyState(e);
	
	if (newStateCandidate)
	{
		newStateCandidate->reset(_state->getPhysics()->getTL());
		_state = newStateCandidate;
	}
}

void LivesEntity::reset(cv::Point const& TL)
{
	_state->reset(TL);
}

bool LivesEntity::checkCollision(std::shared_ptr<Entity> other)
{
	return false;
}



void LivesEntity::draw(cv::Mat& canvas)
{
	_state->draw(canvas);
}

ScoreEntity::ScoreEntity() :Entity(CreateScoreState())
{
	
}

void ScoreEntity::onNotify(Event const& e)
{
	if (e.sender == EventSenders::SENDER_ENTITY_STATE
		&&
		e.type == EventTypes::EVENT_PHYSICS
		&&
		e.code == EventCodes::COLLISION_WITH_ENEMY) {

		_state->getGraphics()->reset();
	}
}

void ScoreEntity::reset(cv::Point const& TL)
{
	_state->reset(TL);
}

bool ScoreEntity::checkCollision(std::shared_ptr<Entity> other)
{
	return false;
}




void ScoreEntity::draw(cv::Mat& canvas)
{
	_state->draw(canvas);
}

ShelfEntity::ShelfEntity() :Entity(CreateShelf())
{
}

void ShelfEntity::onNotify(Event const& e)
{
}

void ShelfEntity::reset(cv::Point const& TL)
{
}

bool ShelfEntity::checkCollision(std::shared_ptr<Entity> other)
{
	//if (this->_state->getPhysics()->checkCollision(other->_state->getPhysics())) {
	//	// notify for hero
	//	_state->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::COLLISION_WITH_SELF });
	//	//this->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::COLLISION_WITH_SELF });
	//	return true;
	//}
	return false;
}

void ShelfEntity::draw(cv::Mat& canvas)
{
	_state->draw(canvas);
}
