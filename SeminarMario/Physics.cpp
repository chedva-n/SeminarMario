#include "Physics.h"
#include <algorithm>

using namespace cv;
using namespace std;
/// //////////////////////////////////////////

// @2: Read this function and try to understand what it does. Use Image Watch !
bool checkPixelLevelCollision(IPhysicsComponent const* first, IPhysicsComponentPtr const& other)
{
	cv::Mat const& mask_First = first->getCollisionMask();
	cv::Mat const& mask_Other = other->getCollisionMask();
	if (mask_Other.empty() || mask_First.empty())
		return false;

	Point TL_first = first->getTL();
	Point TL_other = other->getTL();
	
	// ROI = Reagion of Interest
	Rect firstROI(TL_first, TL_first + Point(mask_First.size()));
	Rect othersROI(TL_other, TL_other + Point(mask_Other.size()));
	Rect intersection = firstROI & othersROI;
	if (intersection.empty())
		return false;

	Rect intersection_RelativeToMe(
		intersection.tl() - TL_first, intersection.br() - TL_first);

	Rect intersection_RelativeToOther(
		intersection.tl() - TL_other, intersection.br() - TL_other);

	Mat myMaskROI = mask_First(intersection_RelativeToMe);
	Mat othersMaskROI = mask_Other(intersection_RelativeToOther);
	Mat whereMeAndOtherIntersect = myMaskROI.mul(othersMaskROI);

	return countNonZero(whereMeAndOtherIntersect);
}

/// //////////////////////////////////////////
#pragma region FixedWidgetPhysics

FixedWidgetPhysics::FixedWidgetPhysics()
	:_topLeft(0,0), _mask()
{
}

void FixedWidgetPhysics::reset(cv::Point const& tl)
{
	cout << tl << endl;
	_topLeft = tl;
}

bool FixedWidgetPhysics::update(cv::Mat const& collisionMask)
{
	_mask = collisionMask;
	return false;
}

bool FixedWidgetPhysics::checkCollision(IPhysicsComponentPtr const& other) const
{
	return checkPixelLevelCollision(this, other);
}

cv::Point const& FixedWidgetPhysics::getTL() const
{
	return _topLeft;
}

cv::Point const& FixedWidgetPhysics::getVelocity() const
{
	return cv::Point(0, 0);
}

cv::Mat const& FixedWidgetPhysics::getCollisionMask() const
{
	return _mask;
}

#pragma endregion

#pragma region ConstVelocityPhysics

ConstVelocityPhysics::ConstVelocityPhysics(cv::Point const& velocity) :_currTL(0, 0), 
_velocity(velocity)
{
}

void ConstVelocityPhysics::reset(cv::Point const& tl)
{
	_currTL = tl;
}
bool ConstVelocityPhysics::update(cv::Mat const& collisionMask)
{
	_mask = collisionMask;
	_currTL += _velocity;
	return false;
}
cv::Mat const& ConstVelocityPhysics::getCollisionMask() const
{
	return _mask;
}
bool ConstVelocityPhysics::checkCollision(IPhysicsComponentPtr const& other) const
{
	return checkPixelLevelCollision(this, other);
}
cv::Point const& ConstVelocityPhysics::getTL() const
{
	return _currTL;
}
cv::Point const& ConstVelocityPhysics::getVelocity() const
{
	return _velocity;
}
#pragma endregion


#pragma region JumpPhysics






JumpPhysics::JumpPhysics(int horizontalVelocity, int initialVerticalVelocity, int gravity,int finishHight):
	_initialJumpVelocity(horizontalVelocity,-(initialVerticalVelocity)),_gravity(gravity)
{
	//_initialJumpVelocity = horizontalVelocity, -(initialVerticalVelocity);
	_finishJump = finishHight;
}

void JumpPhysics::reset(cv::Point const& tl)
{

	_jumpStartTL = tl;
	_currTL = tl;
	_currVelocity = _initialJumpVelocity;
}

bool JumpPhysics::update(cv::Mat const& collisionMask)
{
	_mask = collisionMask;
	_currTL += _currVelocity;
	_currVelocity.y += _gravity;
	if (_currTL.y > _finishJump) {
		_currTL.y = _finishJump;
		return true;
	}
	return false;
}

cv::Mat const& JumpPhysics::getCollisionMask() const
{
	return _mask;
}

bool JumpPhysics::checkCollision(IPhysicsComponentPtr const& other) const
{
	return checkPixelLevelCollision(this,other);
}
cv::Point const& JumpPhysics::getTL() const
{
	return _currTL;
}
cv::Point const& JumpPhysics::getVelocity() const
{
	return _currVelocity;
}
#pragma endregion

NonCollidingPhysicsDecorator::NonCollidingPhysicsDecorator(IPhysicsComponentPtr base)
	:_base(base)
{
}

void NonCollidingPhysicsDecorator::reset(cv::Point const& tl)
{
	_base->reset(tl);
}

bool NonCollidingPhysicsDecorator::update(cv::Mat const& collisionMask)
{
	return _base->update(collisionMask);
}

cv::Mat const& NonCollidingPhysicsDecorator::getCollisionMask() const
{
	return Mat();
}

bool NonCollidingPhysicsDecorator::checkCollision(std::shared_ptr<IPhysicsComponent> const& other) const
{
	//return _base->checkCollision(other);
	return false;
}

cv::Point const& NonCollidingPhysicsDecorator::getTL() const
{
	return _base->getTL();
}

cv::Point const& NonCollidingPhysicsDecorator::getVelocity() const
{
	return cv::Point(0, 0);
}

void BoundedPhysicsDecorator::reset(cv::Point const& tl)
{
	_currTL = tl;
	_base->reset(tl);
}

bool BoundedPhysicsDecorator::update(cv::Mat const& collisionMask)
{
	bool flag = _base->update(collisionMask);
	test();
	return flag;
}

cv::Mat const& BoundedPhysicsDecorator::getCollisionMask() const
{
	return _base->getCollisionMask();
}

bool BoundedPhysicsDecorator::checkCollision(IPhysicsComponentPtr const& other) const
{
	return _base->checkCollision(other);
}

cv::Point const& BoundedPhysicsDecorator::getTL() const
{
	return _currTL;
}

cv::Point const& BoundedPhysicsDecorator::getVelocity() const
{
	return cv::Point(0, 0);
}

void BoundedPhysicsDecorator::test()
{
	_currTL = _base->getTL();
	//right side
	if (_base->getTL().x > _bounds.x + _bounds.width - _base->getCollisionMask().size().width) 
		_currTL.x = _base->getTL().x % _bounds.width;
	//left side
	if (_base->getTL().x <= 0)
		_currTL.x = _bounds.width + _base->getTL().x % _bounds.width;
}


