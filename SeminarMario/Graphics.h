#pragma once
#include <opencv2/opencv.hpp>
#include "Animation.h"

class IGraphicsComponent
{
public:
	
	virtual cv::Mat getCollisionMask() = 0;
	virtual void draw(cv::Mat & canvas, cv::Point const & topLeft) = 0;
	virtual void reset(int code = 0) = 0;
	virtual bool update() = 0;
};

typedef std::shared_ptr<IGraphicsComponent> IGraphicsComponentPtr;

class SingleAnimationGraphics : public IGraphicsComponent
{
protected:
	AnimationPtr _animation;
	int _currFrameIdx;
	bool _isCyclic;

public:
	SingleAnimationGraphics(AnimationPtr animPtr, bool isCyclic);

public:
	virtual cv::Mat getCollisionMask();
	virtual void draw(cv::Mat& canvas, cv::Point const& topLeft);
	virtual void reset(int code = 0) override;
	virtual bool update();
};



class LivesGraphics : public IGraphicsComponent
{
protected:
	Frame _singleLife; 
	int _livesCount; 

public:
	LivesGraphics() :_singleLife(Frame(R"(../Animations/heart.png)")), _livesCount(4){
		resize(_singleLife.image, _singleLife.image, cv::Size(80, 60));
		resize(_singleLife.mask, _singleLife.mask, cv::Size(80, 60));
	}

public:
	virtual cv::Mat getCollisionMask();
	virtual void draw(cv::Mat& canvas, cv::Point const& topLeft);
	virtual void reset(int code=0) override;
	virtual bool update();
};

void exampleOfPutText();
class ScoresGraphics : public IGraphicsComponent
{
private:
	float _fontScale;
	int _score;
	int _fontFace;

public:
	ScoresGraphics(float fontScale, int score,int fontFace):_fontScale(fontScale), _score(score), _fontFace(fontFace) {}
	virtual cv::Mat getCollisionMask();
	virtual void draw(cv::Mat& canvas, cv::Point const& topLeft);
	virtual void reset(int code = 0) override;
	virtual bool update();

};
class AppleGraphics :public IGraphicsComponent
{
protected:
	Frame _apple;

public:
	AppleGraphics():_apple(Frame(R"(../Animations/apple.png)")){

		resize(_apple.image, _apple.image, cv::Size(55.5, 80.5));
		resize(_apple.mask, _apple.mask, cv::Size(55.5, 80.5));
	}
	virtual cv::Mat getCollisionMask();
	virtual void draw(cv::Mat& canvas, cv::Point const& topLeft);
	virtual void reset(int code = 0) override;
	virtual bool update();
};
class ShelfGraphics :public IGraphicsComponent {
protected:
	Frame _shelf;

public:
	ShelfGraphics() :_shelf(Frame(R"(../Animations/wall.png)")) {

		resize(_shelf.image, _shelf.image, cv::Size(180, 70));
		resize(_shelf.mask, _shelf.mask, cv::Size(180, 70));
	}
	virtual cv::Mat getCollisionMask();
	virtual void draw(cv::Mat& canvas, cv::Point const& topLeft);
	virtual void reset(int code = 0) override;
	virtual bool update();
};

