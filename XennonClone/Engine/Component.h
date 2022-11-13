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
	inline GameObject* GetOwnerGameObject() { return m_OwnerGameObject; }
};

