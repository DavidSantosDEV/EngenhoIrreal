#pragma once
#include <vector>
#include <iostream>
#include "Timer.h"

//Timer manager so User can manage timers easily
//tbh it should be a different thread...
class TimerManager
{
private:
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

		return handle;
	}

	static void ExecuteHandles();

	static void AddHandleToExecution(TimerHandle* handle);

	//static void DestroyTimer(TimerHandle timer);
};
