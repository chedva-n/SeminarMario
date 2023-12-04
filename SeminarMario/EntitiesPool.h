#pragma once

#include "Entities.h"
#include <vector>
#include "SlimeEntity.h"

// Object Pool Design Pattern
class EntitiesPool
{
public:
	std::vector<EntityPtr> _pool;
	std::vector<bool> _isInUse;

	
	EntitiesPool(std::string const& animationsPath);
	void insert(EntityPtr whom);
	EntityPtr getNext();
	void returnEntity(EntityPtr toFree);

};
typedef std::shared_ptr< Entity> EntityPtr;
