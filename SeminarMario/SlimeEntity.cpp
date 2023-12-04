#include "SlimeEntity.h"

using namespace cv;
using namespace std;

EntityStatePtr CreateSlimeEnemy(std::string const& animationFolder)
{
	AnimationPtr animation(new Animation(animationFolder));
	bool isCyclic = true;
	animation->resizeImg();
	IGraphicsComponentPtr graphicsPtr(
		new SingleAnimationGraphics(animation, isCyclic));

	IPhysicsComponentPtr physicsPtr =
			make_shared<FixedWidgetPhysics>();

	return make_shared<EntityState>(graphicsPtr, physicsPtr);
}
EntityPtr createSlime(std::string const& rootAnimationsFolder)
{
	auto slime = CreateSlimeEnemy(rootAnimationsFolder);
	EntityPtr slimeEntity(new Entity(slime));
	return slimeEntity;
}
