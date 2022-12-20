#pragma once
#include <vector>
#include <iostream>
#include "Timer.h"



//Timer manager so User can manage timers easily
//tbh it should be a different thread...
class TimerManager
{
private:
	//static std::vector<ISimpleDelegateInvoker> m_holder;
public:
	template <class T>
	static BaseHandle* CreateTimer(T* obj, void (T::* method)(), float time, bool binfinite, bool bAutoStart)
	{
		SimpleDelegateMember<T>* del = new SimpleDelegateMember<T>(obj, method);
		//m_holder.push_back(dynamic_cast<ISimpleDelegateInvoker>(del.get()));
		TimerHandle<T>* handle = new TimerHandle<T>();
		handle->Set(del, time, binfinite);
		if (bAutoStart)handle->Start(time, binfinite);
		return handle;
	}

	//static void DestroyTimer(TimerHandle timer);
};
