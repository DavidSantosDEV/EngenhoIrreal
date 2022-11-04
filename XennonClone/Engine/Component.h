#pragma once
class Component
{
public:
	virtual void Start();
	virtual void Update();

protected:
	class GameObject* m_OwnerGameObject = nullptr;

public:
	inline void SetOwnerGameObject(class GameObject* gameObject) { m_OwnerGameObject = gameObject; }
	inline GameObject* GetOwner() { return m_OwnerGameObject; }
};

