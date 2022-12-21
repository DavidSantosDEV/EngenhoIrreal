#pragma once
#include "Delegate.h"
#include <thread>
#include "MathHelper.h"
#include "Log.h"
//template<typename... TArgs>

class BaseHandle {
public:
	virtual void Stop() = 0;
	virtual void Start(float delay, bool bRepeating) = 0;

	virtual bool GetIsActive() = 0;

	virtual void Execute() = 0;
};


class TimerHandle : public BaseHandle {
private:
	bool m_isActive = false;
	bool m_ShouldRepeat= false;
	unsigned int delayTime=0;

	class std::thread m_workerThread;

	ISimpleDelegateInvoker* m_del;
public:
	~TimerHandle();

	template<class TObject>
	void Set(SimpleDelegateMember<TObject>* del, float Timed, bool bRepeating);

	virtual void Stop() override;
	virtual void Start(float Delay, bool bRepeating) override;
	virtual bool GetIsActive() override { return m_isActive; }

	bool GetShouldRepeat() { return m_ShouldRepeat; }
	void SetShouldRepeat(bool val) { m_ShouldRepeat = val; }

	virtual void Execute() override;
protected:
	void DelayTask();
};

template<class TObject>
void TimerHandle::Set(SimpleDelegateMember<TObject>* del, float Timed, bool bRepeating)
{
	m_del = del;
	delayTime = MathHelper::Abs(Timed);
	m_ShouldRepeat = bRepeating;
}

