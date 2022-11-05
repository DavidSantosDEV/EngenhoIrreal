#pragma once
#include <vector>
#include <memory>
#include "Log.h"
#include <array>
#include "Transform.h"

class GameWorld;

class GameObject
{
public:

	GameObject();
	~GameObject();

	virtual void Start();
	virtual void Update(float deltaTime);

protected:
	std::vector<std::shared_ptr<class Component>> m_Components;
	std::array<class Component*, 32> m_ComponentsHashMap = std::array<class Component *, 32>();

	bool m_WasInitialized = false;

	Transform m_Transform;
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

	template <typename T, typename... TArgs> T& AddComponent(TArgs&&... mArgs)
	{
		T* newComponent = new T(std::forward<TArgs>(mArgs)...);
		newComponent->SetOwnerGameObject(this);

		// Smart pointer to be deleted when component is deleted from GO
		std::unique_ptr<Component> componentPtr{ newComponent };

		m_Components.emplace_back(std::move(componentPtr));
		m_ComponentsHashMap[GetComponentID<T>()] = newComponent;

		newComponent->Start();

		return *newComponent;
	}

	template <typename T> T& GetComponent()
	{
		auto componentFound = m_ComponentsHashMap[GetComponentID<T>()];
		return *static_cast<T*>(componentFound);
	}

#pragma endregion

public:
	inline bool GetWasInitialized() const { return m_WasInitialized; }

	inline Transform* GetTransform() { return &m_Transform; }
};

