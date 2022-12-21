#include "Timer.h"
#include "TimerManager.h"
#include <chrono>

TimerHandle::~TimerHandle()
{
	delete m_del;
}

void TimerHandle::Stop()
{
	m_isActive = false;
	//Stop Thread
}

void TimerHandle::Start(float Delay /*Time in seconds*/, bool bRepeating)
{
	if (m_isActive)return;

	delayTime = MathHelper::Abs(Delay);

	m_isActive = true;
	m_ShouldRepeat = bRepeating;
	m_workerThread = std::thread(&TimerHandle::DelayTask, this);
}

void TimerHandle::DelayTask()
{
	LOG_ERROR("Timer")
	std::this_thread::sleep_for(std::chrono::milliseconds(delayTime * 1000));
	TimerManager::AddHandleToExecution(this);
	m_workerThread.detach();
}



void TimerHandle::Execute()
{
	LOG("Timer Ticked");
	//using namespace std::literals::chrono_literals;
	m_del->Execute();
	m_isActive = m_ShouldRepeat;
	if (m_isActive) {
		m_workerThread = std::thread(&TimerHandle::DelayTask, this);
	}
	else {
		delete this;
	}
}

