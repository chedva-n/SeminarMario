#include "Graphics.h"
#include <algorithm>
#include "AppleEntity.h"

using namespace cv;
using namespace std;

//////////////////////////////////////////////////

SingleAnimationGraphics::SingleAnimationGraphics(AnimationPtr animPtr, bool isCyclic)
	:_animation(animPtr), _currFrameIdx(0)
	, _isCyclic(isCyclic)
{
}


cv::Mat SingleAnimationGraphics::getCollisionMask()
{
	return _animation->getFrame(_currFrameIdx).mask;
}

void SingleAnimationGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
	drawFrame(_animation->getFrame(_currFrameIdx), canvas, topLeft);
}

void SingleAnimationGraphics::reset(int code)
{
	_currFrameIdx = 0;
}

bool SingleAnimationGraphics::update()
{
	bool hasFinished = (_currFrameIdx == _animation->numFrames() - 1);
	if (_isCyclic)
		_currFrameIdx = (_currFrameIdx + 1) % _animation->numFrames();
	else
		_currFrameIdx = min<int>(_currFrameIdx + 1, (int)_animation->numFrames() - 1);

	return hasFinished;
}


//////////////////////////////////////////////////

void exampleOfPutText()
{
	Mat image = imread(R"(../Animations/background.png)", IMREAD_UNCHANGED);
	string text = "score: ";
	int score = 465;
	string moreText = to_string(score);
	text = text + moreText;
	Point topLeft(50, 50);
	int fontFace = FONT_HERSHEY_SIMPLEX; // normal size sans - serif font
	// other options for fontFace:
	FONT_HERSHEY_PLAIN;// small size sans - serif font
	FONT_HERSHEY_DUPLEX;// normal size sans - serif font(more complex than FONT_HERSHEY_SIMPLEX)
	FONT_HERSHEY_COMPLEX; // normal size serif font
	FONT_HERSHEY_TRIPLEX; //normal size serif font(more complex than FONT_HERSHEY_COMPLEX)
	FONT_HERSHEY_COMPLEX_SMALL; //smaller version of FONT_HERSHEY_COMPLEX
	FONT_HERSHEY_SCRIPT_SIMPLEX; //hand - writing style font
	FONT_HERSHEY_SCRIPT_COMPLEX;// more complex variant of FONT_HERSHEY_SCRIPT_SIMPLEX
	double fontScale = 2; // Font scale factor that is multiplied by the font-specific base size.
	Scalar color(/*Blue between 0...255 =*/0,/*Green between 0...255 =*/0,/*Red between 0...255 =*/255);
	int thickness = 2;
	int lineType = FILLED;
	// other options for line type:
	LINE_4; LINE_8; LINE_AA;

	// finally:
	putText(image, text, topLeft, fontFace, fontScale, color, thickness, lineType);

	imshow("test", image);
	waitKey();//waiting forever till some key is hit.
}

#pragma region LivesGraphics

cv::Mat LivesGraphics::getCollisionMask()
{
	return _singleLife.mask;
}

void LivesGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
	auto pointToDrow = cv::Point(1400, 20);
	for (int i = 0; i < _livesCount; i++)
	{
		drawFrame(_singleLife, canvas, pointToDrow);
		pointToDrow.x -= 80;
	}
}

void LivesGraphics::reset(int code) {
	//add heart
	if (code > 0) {
		_livesCount++;
	}
	//to decrease
	else if(_livesCount>0){
		_livesCount--;
	}
}



bool LivesGraphics::update()
{
	return false;
}

#pragma endregion
cv::Mat ScoresGraphics::getCollisionMask()
{
	return cv::Mat();
}
void ScoresGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
	string text;
	if (_score <= 0) {
		text = "game over!!!!!!";
		int fontFace = FONT_HERSHEY_COMPLEX;
		double fontScale = 6;
		Scalar color(/*Blue between 0...255 =*/0,/*Green between 0...255 =*/0,/*Red between 0...255 =*/100);
		int thickness = 20;
		int lineType = FILLED;
		putText(canvas, text, cv::Point(20, 400), fontFace, fontScale, color, thickness, lineType);

	}

	text = "score: ";
	int score = _score;
	string moreText = to_string(score);
	text = text + moreText;
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 2;
	Scalar color(0,0,255);
	int thickness = 2;
	int lineType = FILLED;
	putText(canvas, text, cv::Point(50, 50), _fontFace, _fontScale, color, thickness, lineType);

}
void ScoresGraphics::reset(int code) {
	if (_score != 0)
		_score -= 50;
}

bool ScoresGraphics::update()
{
	return false;
}

cv::Mat AppleGraphics::getCollisionMask()
{
	return _apple.mask;
}

void AppleGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
		drawFrame(_apple, canvas, topLeft);
}

void AppleGraphics::reset(int code)
{
}

bool AppleGraphics::update()
{
	return false;
}

cv::Mat ShelfGraphics::getCollisionMask()
{
	return cv::Mat();
}

void ShelfGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
	drawFrame(_shelf, canvas, cv::Point(600,688));
}

void ShelfGraphics::reset(int code)
{
}

bool ShelfGraphics::update()
{
	return false;
}
