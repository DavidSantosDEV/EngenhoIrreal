#pragma once
#include <vector>
#include <memory>
#include "Log.h"
#include <array>
#include "InstanceCounter.h"
#include "Transform.h"

class GameWorld;

class GameObject
{
public:

	GameObject();
	GameObject(Transform transform);
	GameObject(Vector2D position, Vector2D scale);

	~GameObject();

	virtual void Start();
	virtual void Update(float deltaTime);

	/* Called right before the GameObject is destroyed */
	virtual void OnDestroyed();

	Transform _Transform;

protected:
	std::vector<std::shared_ptr<class Component>> m_Components;
	std::array<class Component*, 32> m_ComponentsHashMap = std::array<class Component *, 32>();

	std::vector<std::string> m_objectTags;

	bool m_WasInitialized = false;
	bool m_pendingDestroy = false;

public:
/* Component-Derived System */
#pragma region ComponentSystem

	// Represents the ID of each component
	using ComponentID = std::size_t;

	inline ComponentID GetComponentID()
	{
		static ComponentID lastComponentID = 0;
		return lastComponentID++;
	}

	template <typename T> inline ComponentID GetComponentID() noexcept
	{
		static ComponentID typeID = GetComponentID();
		return typeID;
	}

	template <typename T, typename... TArgs> T* AddComponent(TArgs&&... mArgs)
	{
		T* newComponent = new T(std::forward<TArgs>(mArgs)...);
		newComponent->SetOwnerGameObject(this);

		// Smart pointer to be deleted when component is deleted from GO
		std::unique_ptr<Component> componentPtr{ newComponent };

		m_Components.emplace_back(std::move(componentPtr));
		m_ComponentsHashMap[GetComponentID<T>()] = newComponent;

		newComponent->Start();
		InstanceCounter::AddComponentCount();

		return newComponent;
	}

	template <typename T> T* GetComponent()
	{
		auto componentFound = m_ComponentsHashMap[GetComponentID<T>()];
		return static_cast<T*>(componentFound);
	}

	inline std::vector<std::shared_ptr<Component>> GetAllComponents() { return m_Components; }


#pragma endregion

public:
	bool HasTag(std::string tag);
	bool HasTag(const char* tag);
	void AddTag(const char* tag);

	std::vector<std::string> GetTags() { return m_objectTags; }

	inline bool GetWasInitialized() const { return m_WasInitialized; }

	inline Transform* GetTransform() { return &_Transform; }

	void SetPendingDestroy() { m_pendingDestroy = true; }

	bool IsPendingDestroy() { return m_pendingDestroy; }

	/* Only called if GameObject has CollisionComponent*/
	virtual void OnBeginCollision(GameObject* other){};
	/* Only called if GameObject has CollisionComponent*/
	virtual void OnEndCollision(GameObject* other){};
	/* Only called if GameObject has CollisionComponent*/
	virtual void OnTriggerEnter(GameObject* other){};
	/* Only called if GameObject has CollisionComponent*/
	virtual void OnTriggerExit(GameObject* other){};

	/*Only called if GameObject has AnimationComponent */
	//virtual void OnAnimationEnd() {};

	/* Called when the GameObject is inside the screen area */
	virtual void OnBecameVisible() {};
	/* Called when the GameObject is outside the screen area */
	virtual void OnBecameHidden() {};

};

