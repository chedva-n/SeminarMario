#include "Animation.h"
#include <opencv2/opencv.hpp>
#include "Timer.h"
#include "HeroEntity.h"
#include <Windows.h>
#include "SlimeEntity.h"
#include "LivesEntity.h"
#include "AppleEntity.h"
#include "EntitiesPool.h"
#include "Config.h"
#include <random>

using namespace cv;
using namespace std;

int main()
{
	Mat background = imread(R"(../Animations/background.png)", IMREAD_UNCHANGED);
	resize(background, background, cv::Size(GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN)));
	auto slimesPool = new EntitiesPool(R"(../Animations/SlimeOrange)");
	EntityPtr slime(slimesPool->getNext());
	slime->reset(Point(background.size().width * 2 / 3, background.size().height * 6 / 8 + 80));
	EntityPtr hero = createHero(R"(../Animations/Hero)");
	hero->reset(Point(background.size().width / 2, background.size().height * 2 / 3));
	/*EntityPtr shelf(new ShelfEntity());
	shelf->draw(background);
	hero->Register(shelf);*/

	EntityPtr heartPtr(new LivesEntity());
	hero->Register(heartPtr);

	EntityPtr score(new ScoreEntity());
	hero->Register(score);

	auto apple(new AppleEntity());
	
	//hero->Register((EntityPtr)apple);
	apple->getState()->Register((EntityPtr)apple);

	Timer timer(100);
	timer.Register(slime);
	timer.Register(hero);
	timer.Register((EntityPtr)apple);
	apple->Register(heartPtr);

	bool isToExit = false;
	while (false == isToExit)
	{
		Mat canvas = background.clone();
		timer.tick();
		for (auto i = 0; i < slimesPool->_pool.size(); i++)
		{
			if (slimesPool->_isInUse[i]) {
				slimesPool->_pool[i]->draw(canvas);
				//if have collision with this slime
				hero->checkCollision(slimesPool->_pool[i]);
				if (apple->checkCollision(slimesPool->_pool[i])) {
                    //slimesPool->_isInUse[i] = false;
					//slimesPool->getNext()->reset(Point(background.size().width * ((double)(rand() % 100) + 1) / 10001, background.size().height * 6 / 8 + 80));
				}
				srand(time(0));

				// for loop to check that we get different values on every iteration
			//	for (int i = 1; i < 11; i++) {

					// typecasting the random value obtained into a double and then dividing it
					// with INT_MAX
				cout << ((double)(rand() % 100) + 1) / 10001 << endl;
			//	}
			}
		}
		hero->draw(canvas);
		if (!apple->_isDraw) {
			apple->reset(hero->getState()->getPhysics()->getTL());
		}
		if (apple->_isDraw) {
			apple->getState()->getPhysics()->update(apple->getState()->getPhysics()->getCollisionMask());
            apple->draw(canvas);
		}
		//hero->checkCollision(shelf);
		heartPtr->draw(canvas);
		score->draw(canvas);
		imshow("test", canvas);
	}

	return 0;
}

