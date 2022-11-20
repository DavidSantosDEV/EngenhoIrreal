#pragma once
#include <vector>
#include <iostream>

typedef void (*TimerFunction)();

class TimerHandle {
	
	bool m_IsActive = false;
	
	TimerFunction func = nullptr;
	
	float m_time = 0.f;
	float m_currentTime =0.f;

	bool m_IsInfinite = false;
	
	void OnActivateFunction();

public:
	template <typename T>
	TimerHandle(float countTime, void(*function)(), bool bInfinite,bool bAutoStart) 
	{
		func = function;
		m_time = countTime;
		m_IsActive = bAutoStart;
		m_IsInfinite = bInfinite;
	}

	void Start();
	void Update(float delta);

	void SetTime(float counttime);
	void SetFunction(void (*function)());
	void Deactivate();
	void Activate();
	void Reset();

	bool GetIsActive() { return m_IsActive; }
};

//Timer manager so User can manage timers easily
//tbh it should be a different thread...
class TimerManager
{
	static std::vector<TimerHandle*> m_handles;

public:
	static TimerHandle* CreateTimer(void(*function)(),float time,bool binfinite, bool bAutoStart);

	static void UpdateHandles(float deltaTime);

	static void DestroyTimer(TimerHandle* timer);

};
