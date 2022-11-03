class GameEngine;
class GameObject;
#include "GameEngine.h"
#include "Log.h"

class GameWorld 
{
public:
	void Init(GameEngine* myEngine);

	GameWorld();
	~GameWorld();

	GameObject* InstantiateObject();
	void CallRemoveObjectFromStack(GameObject* gameObject);

	virtual void Start() = 0;
	virtual void Update() = 0;

	template <typename T, typename... TArgs> T* InstantiateObject(TArgs&&... mArgs) {
		T* newObject = new T(std::forward(mArgs)...);
		if (static_cast<GameObject*>(newObject)) {
			if (m_Engine) {
				m_Engine->AddGameObjectToStack(newObject);
			}
			return newObject;
		}
		LOG_ERROR("Can't instantiate Non GameObject types");
		return nullptr;
	}

protected:
	static GameEngine* m_Engine;
};