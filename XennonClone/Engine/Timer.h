#pragma once
#include "Delegate.h"
#include <thread>
#include <chrono>
#include "MathHelper.h"
#include "Log.h"
//template<typename... TArgs>

class ITimerDelegateInvokable {
public:
	virtual void Execute() = 0;
};

class BaseHandle {

};

template<class TObject>
class TimerHandle : public BaseHandle {
private:
	bool m_isActive = false;
	bool m_ShouldRepeat= false;
	unsigned int delayTime=0;

	std::thread worker;

	SimpleDelegateMember<TObject>* m_del;
	//template<class T, typename ...TArgs>
	//IDelegateInvokable<TArgs...> m_del;
public:
	void Set(SimpleDelegateMember<TObject>* del, float Timed, bool bRepeating);
	void Stop();
	void Start(float Delay, bool bRepeating);

	bool GetIsActive() { return m_isActive; }
protected:
	void Execute();
};

template<class TObject>
void TimerHandle<TObject>::Set(SimpleDelegateMember<TObject>* del, float Timed, bool bRepeating)
{
	m_del = del;
	delayTime = MathHelper::Abs(Timed);
	m_ShouldRepeat = bRepeating;
}
template<class TObject>
void TimerHandle<TObject>::Stop()
{
	m_isActive = false;
	//Stop Thread
}

template<class TObject>
void TimerHandle<TObject>::Start(float Delay /*Time in seconds*/, bool bRepeating)
{
	if (m_isActive)return;

	delayTime =  MathHelper::Abs(Delay);

	m_isActive = true;
	m_ShouldRepeat = bRepeating;
	worker = std::thread(&TimerHandle::Execute, this);
}


template<class TObject>
void TimerHandle<TObject>::Execute()
{
	LOG("Timer Ticked");
	//using namespace std::literals::chrono_literals;
	std::this_thread::sleep_for(std::chrono::milliseconds(delayTime * 1000));
	//Execute
	m_del->Execute();
	m_isActive = m_ShouldRepeat;
	worker.detach();
	if (m_isActive) {
		worker = std::thread(&TimerHandle::Execute, this);
	}
	else {
		delete m_del;
		delete this;
	}
}
