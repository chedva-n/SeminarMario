#pragma once
#include "Entities.h"

class LivesEntity:public Entity
{
	
public:
	LivesEntity();

	virtual void onNotify(Event const& e) override;
	virtual void reset(cv::Point const& TL);
	bool checkCollision(std::shared_ptr< Entity> other);
	void draw(cv::Mat& canvas);
};

class ScoreEntity :public Entity {
public:
	ScoreEntity();
	virtual void onNotify(Event const& e) override;
	virtual void reset(cv::Point const& TL);
	bool checkCollision(std::shared_ptr< Entity> other);
	void draw(cv::Mat& canvas);
};

class ShelfEntity :public Entity {
public:
	ShelfEntity();
	virtual void onNotify(Event const& e) override;
	virtual void reset(cv::Point const& TL);
	bool checkCollision(std::shared_ptr< Entity> other);
	void draw(cv::Mat& canvas);
};
