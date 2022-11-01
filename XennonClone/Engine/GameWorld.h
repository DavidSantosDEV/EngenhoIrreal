
class GameEngine;
class GameObject;

class GameWorld {

protected:
	GameEngine* m_Engine;

public:
	void Init(GameEngine* myEngine);

	GameWorld();
	//GameWorld(GameEngine* Engine);
	~GameWorld();

	GameObject* InstantiateObject();
	void RemoveObject(GameObject* Object);

	virtual void Start() = 0;
	virtual void Update() = 0;
};