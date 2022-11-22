#include "Log.h"
#include "InstanceCounter.h"

class GameEngine;
class GameObject;

class GameWorld 
{
public:
	void Init(GameEngine* myEngine);

	static GameWorld* GetWorld() {return m_World;}

	GameWorld();
	~GameWorld();

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;

	template <typename T, typename... TArgs> static T* InstantiateObject(TArgs&&... mArgs) {
		T* newObject = new T(std::forward(mArgs)...);
		if (static_cast<GameObject*>(newObject)) 
		{
			newObject->Start();
			InstanceCounter::AddObjectCount();
			return newObject;
		}
		LOG_ERROR("Can't instantiate Non GameObject types");
		return nullptr;
	}

	static void DestroyObject(GameObject* Object);

	static GameObject* FindObjectWithTag(std::string tag);

protected:
	static GameWorld* m_World;

	static GameEngine* m_Engine;
};