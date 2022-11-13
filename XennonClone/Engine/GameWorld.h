#include "Log.h"

class GameEngine;
class GameObject;

class GameWorld 
{
public:
	void Init(GameEngine* myEngine);

	GameWorld();
	~GameWorld();

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;

	template <typename T, typename... TArgs> static T* InstantiateObject(TArgs&&... mArgs) {
		T* newObject = new T(std::forward(mArgs)...);
		if (static_cast<GameObject*>(newObject)) 
		{
			newObject->Start();
			return newObject;
		}
		LOG_ERROR("Can't instantiate Non GameObject types");
		return nullptr;
	}

protected:
	static GameEngine* m_Engine;
};