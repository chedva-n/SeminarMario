#include "AppleEntity.h"
#include "CreateEntities.h"

using namespace cv;
using namespace std;

EntityStatePtr CreateApple()
{
	IGraphicsComponentPtr graphicsPtr(new AppleGraphics());
	IPhysicsComponentPtr physicsPtr(new JumpPhysics(50, -10, 6,705));
	EntityStatePtr state = make_shared<EntityState>(graphicsPtr, physicsPtr);
	 state->getPhysics()->update(Frame(R"(../Animations/apple.png)").mask);
	return state;
}

EntityStatePtr CreateLivesState()
{
	IGraphicsComponentPtr graphicsPtr(
		new LivesGraphics);

	IPhysicsComponentPtr physicsPtr =
		make_shared<NonCollidingPhysicsDecorator>(
			make_shared<FixedWidgetPhysics>());

	return make_shared<EntityState>(graphicsPtr, physicsPtr);
}

EntityStatePtr CreateScoreState()
{
	IGraphicsComponentPtr graphicsPtr(
		new ScoresGraphics(1, 200, FONT_HERSHEY_DUPLEX));

	IPhysicsComponentPtr physicsPtr =
		make_shared<NonCollidingPhysicsDecorator>(
			make_shared<FixedWidgetPhysics>());

	return make_shared<EntityState>(graphicsPtr, physicsPtr);
}

EntityStatePtr CreateShelf()
{
	IGraphicsComponentPtr graphicsPtr(new ShelfGraphics());
	IPhysicsComponentPtr physicsPtr =
		make_shared<NonCollidingPhysicsDecorator>(
			make_shared<FixedWidgetPhysics>());
	EntityStatePtr state = make_shared<EntityState>(graphicsPtr, physicsPtr);
	state->getPhysics()->update(Frame(R"(../Animations/wall.png)").mask);
	return state;
}
