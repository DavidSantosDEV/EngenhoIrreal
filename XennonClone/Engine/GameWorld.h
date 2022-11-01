class GameEngine;
class GameObject;

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

protected:
	GameEngine* m_Engine = nullptr;
};