#pragma once
#include "Delegate.h"

class Timer
{
	template <class T, typename...TArgs>
	TimerHandle CreateTimer(T* object, void (T::* method)(TArgs... params)) {
		if (object!=nullptr) {
			return nullptr;
		}
		
	}
};

template <class T,typename ...TArgs>
class TimerDelegate 
{
	
};

//template<typename... TArgs>
class TimerHandle {
private:
	bool m_isActive = false;
	bool m_ShouldRepeat= false;
	unsigned int delayTime=0;

	//template<class T, typename ...TArgs>
	//IDelegateInvokable<TArgs...> m_del;
public:
	template<class T, typename ...TArgs>
	TimerHandle(TimerDelegate<T, TArgs...> del);

	void Stop();
	void Start(float Delay, bool bRepeating);

	bool GetIsActive() { return m_isActive; }
protected:
	void Execute();
};

template<class T, typename ...TArgs>
inline TimerHandle::TimerHandle(TimerDelegate<T, TArgs...> del)
{
	
}
