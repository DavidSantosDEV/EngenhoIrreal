#pragma once
class Component
{
public:
	virtual void Start();
	virtual void Update(float deltatime);
protected:
	class GameObject* m_OwnerGameObject = nullptr;

public:
	inline void SetOwnerGameObject(class GameObject* gameObject) { m_OwnerGameObject = gameObject; }

	GameObject* const GetOwnerGameObject() { return m_OwnerGameObject; }
};

