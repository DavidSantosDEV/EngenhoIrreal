#pragma once
class Component
{
public:
	virtual void Start();
	virtual void Update(float deltatime);
protected:
	class GameObject* m_OwnerGameObject = nullptr;

	bool m_IsPendingKill = false;
	bool m_isActive = true;
public:
	inline void SetOwnerGameObject(class GameObject* gameObject) { m_OwnerGameObject = gameObject; }

	bool GetIsPendingKill() { return m_IsPendingKill; }
	void SetPendingKill() { m_IsPendingKill=true; }

	GameObject* const GetOwnerGameObject() { return m_OwnerGameObject; }

	virtual void OnDestroyed() {};

	virtual void SetActive(bool bVal) { m_isActive = bVal; }

	bool GetIsActive() { return m_isActive; }
};

