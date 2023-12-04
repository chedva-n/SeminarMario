#pragma once
#include "Entities.h"
#include "CreateEntities.h"
class AppleEntity:public Entity
{
public:
	bool _isDraw;
 
public:
	AppleEntity():Entity(CreateApple()),_isDraw(false){}
	virtual void onNotify(Event const& e) override;
	virtual void reset(cv::Point const& TL);
	bool checkCollision(std::shared_ptr< Entity> other);
	void draw(cv::Mat& canvas);
	virtual bool isDraw();
};
typedef std::shared_ptr< Entity> EntityPtr;
