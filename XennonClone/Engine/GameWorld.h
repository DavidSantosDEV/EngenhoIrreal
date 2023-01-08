#include "Log.h"
#include "InstanceCounter.h"
#include <vector>

class GameEngine;
class GameObject;

class GameWorld 
{
private:
	static void AddObjectToEngine(GameObject* obj);


public:
	void Init(GameEngine* myEngine);

	static GameWorld* GetWorld() {return m_World;}

	virtual void Start() {};
	virtual void Update(float deltaTime) {};

	template <typename T, typename... TArgs> static T* InstantiateObject(TArgs&&... mArgs) {
		T* newObject = new T(std::forward<TArgs>(mArgs)...);
		if (static_cast<GameObject*>(newObject)) 
		{
			GameWorld::AddObjectToEngine(newObject); //Cheesy way to not have engine included
			newObject->Start();
			return newObject;
		}
		LOG_ERROR("Can't instantiate Non GameObject types");
		return nullptr;
	}

	static void DestroyObject(GameObject* Object);

	static GameObject* FindObjectWithTag(std::string tag);
	static std::vector<GameObject*> FindAllObjectsWithTag(std::string tag);

	template <typename T>
	static std::vector<T*> FindAllObjectsOfType() {
		std::vector<GameObject*> objs = GetAllEngineObjects();
		std::vector<T*> objsC;
		for (auto ob : objs) {
			T* casted = dynamic_cast<T*>(ob);
			if (casted) {
				objsC.push_back(casted);
			}
		}
		return objsC;
	}

	template <typename T>
	static T* FindObjectOfType() {
		std::vector<GameObject*> objs = GetAllEngineObjects();
		std::vector<T*> objsC;
		for (auto ob : objs) {
			T* casted = dynamic_cast<T*>(ob);
			if (casted) {
				return casted;
			}
		}
		return nullptr;
	}


protected:

	std::vector<GameObject*> GetAllEngineObjects();

	static GameWorld* m_World;
	static GameEngine* m_Engine;
};