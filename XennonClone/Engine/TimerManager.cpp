#include "TimerManager.h"

std::vector<TimerHandle*> TimerManager::m_handles = {};

TimerHandle* TimerManager::CreateTimer(void(*function)(), float time, bool binfinite, bool bAutoStart)
{
	//TimerHandle* newtimer = new TimerHandle(time,function,binfinite,bAutoStart);
	//m_handles.push_back(newtimer);
	//return newtimer;
	return nullptr;
}

void TimerManager::UpdateHandles(float deltaTime)
{
	for (auto t : m_handles) {
		if (t) {
			t->Update(deltaTime);
		}
	}
}

void TimerManager::DestroyTimer(TimerHandle* timer)
{
	if (!timer)return;
	for (int i = 0; i < m_handles.size(); ++i)
	{
		if (m_handles[i] == timer)
		{
			m_handles.erase(m_handles.begin() + i);
			return;
		}
	}
}

void TimerHandle::OnActivateFunction()
{
	func();
	if (m_IsInfinite) {
		m_currentTime = m_time;
	}
	else {
		TimerManager::DestroyTimer(this);
	}
}

void TimerHandle::Start()
{
	m_currentTime = m_time;
}

void TimerHandle::Update(float delta)
{
	if (!m_IsActive) return;
	m_currentTime -= delta;
	if (m_currentTime<=0.f) {
		OnActivateFunction();
	}
}

void TimerHandle::SetTime(float counttime)
{
	m_time = counttime;
	m_currentTime = counttime; //RESETS TIME, should it? hmm
}

void TimerHandle::SetFunction(void(*function)())
{
	func = function;
}

void TimerHandle::Deactivate()
{
	m_IsActive = false;
	m_currentTime = m_time;
}

void TimerHandle::Activate()
{
	m_IsActive = true;
}

void TimerHandle::Reset()
{
	m_currentTime = m_time;
}
