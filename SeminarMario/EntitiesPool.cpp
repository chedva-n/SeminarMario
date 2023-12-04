#include "EntitiesPool.h"

EntitiesPool::EntitiesPool(std::string const& animationsPath) :_pool(10), _isInUse(10) {
	for (size_t i = 0; i <10; i++)
	{
		_pool[i] = createSlime(animationsPath);
		_isInUse[i] = false;
	}
}
void EntitiesPool::insert(EntityPtr whom)
{
	_pool.push_back(whom);
	_isInUse.push_back(false);
}

EntityPtr EntitiesPool::getNext()
{
	if(!_pool.size())
		throw std::exception("dont have entities in the pool");
	for (int i = 0; i < _isInUse.size(); i++)
	{
		if (!_isInUse[i]) {
				_isInUse[i] = true;
				return _pool[i];
		}
				
	}

	throw std::exception("all entities are in use");
}

void EntitiesPool::returnEntity(EntityPtr toFree)
{
	for (int i = 0; i < _pool.size(); i++)
	{
		if (_pool[i]==toFree) {
			_isInUse[i] = false;
		}

	}
}
