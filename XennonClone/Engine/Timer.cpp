//#include "Timer.h"
//#include <thread>
//#include <chrono>
//#include "MathHelper.h"
//#include "Log.h"
//
//void TimerHandle::Stop()
//{
//	m_isActive = false;
//	//Stop Thread
//}
//
//
//void TimerHandle::Start(float Delay /*Time in seconds*/, bool bRepeating)
//{
//	if (m_isActive)return;
//
//	delayTime =1000 * MathHelper::Abs(Delay);
//
//	m_isActive = true;
//	m_ShouldRepeat = bRepeating;
//	do{
//		std::thread worker(&TimerHandle::Execute, this);
//		worker.join();
//		
//		m_isActive = m_ShouldRepeat;
//	}while (m_isActive);
//}
//
//using namespace std::literals::chrono_literals;
//void TimerHandle::Execute()
//{
//	//using namespace std::literals::chrono_literals;
//	std::this_thread::sleep_for( std::chrono::milliseconds(delayTime) );
//
//	//Execute
//	LOG("Timer Ticked");
//}
