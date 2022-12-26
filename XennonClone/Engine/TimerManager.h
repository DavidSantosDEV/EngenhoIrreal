#pragma once
#include <vector>
#include <iostream>
#include "Timer.h"

//Timer manager so User can manage timers easily
//tbh it should be a different thread...
class TimerManager
{
private:

	static std::vector<TimerHandle*> m_CreatedHandles;
	static std::vector<TimerHandle*> m_ExecutionRow;
public:
	template <class T>
	static TimerHandle* CreateTimer(T* obj, void (T::* method)(), float time, bool binfinite, bool bAutoStart)
	{
		SimpleDelegateMember<T>* del = new SimpleDelegateMember<T>(obj, method);
		//m_holder.push_back(dynamic_cast<ISimpleDelegateInvoker>(del.get()));
		TimerHandle* handle = new TimerHandle();
		handle->Set(del, time, binfinite);
		if (bAutoStart)handle->Start(time, binfinite);
		m_CreatedHandles.push_back(handle);
		return handle;
	}

	static void ExecuteHandles();

	static void AddHandleToExecution(TimerHandle* handle);

	template<class T>
	static void StopTimerWith(T* obj, void (T::* method)());
private:
	static void __InternalRemoveHandle(TimerHandle* handle);


	//static void DestroyTimer(TimerHandle timer);
};

template<class T>
inline void TimerManager::StopTimerWith(T* obj, void(T::* method)())
{
	for (int i = 0; i < m_CreatedHandles.size();++i) {
		ISimpleDelegateInvoker* del = m_CreatedHandles[i]->GetDelegateInvoker();
		SimpleDelegateMember<T>* delCasted = dynamic_cast<SimpleDelegateMember<T>*>(del);
		if (delCasted) {
			if (delCasted->Equals(obj, method)) {
				m_CreatedHandles[i]->Stop();
			}
		}
	}
}
