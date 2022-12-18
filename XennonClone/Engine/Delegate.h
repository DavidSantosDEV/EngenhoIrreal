#pragma once
#include <vector>

//Simple interface (Abstract)
template <typename ...TArgs>
class IDelegateInvokable {
public:
    virtual void Broadcast(TArgs... params) = 0;
};

template<class TObject, typename... TArgs>
class DelegateToMember: public IDelegateInvokable<TArgs...> 
{

public:
    typedef void (TObject::* SpecializedDelegateOneParam)(TArgs... params); //Define the method type

    DelegateToMember(TObject* target, SpecializedDelegateOneParam method); //Constructor

    //Perhaps it only works with public functions, a shortcomming but will do for now
    void Broadcast(TArgs... params) override{
        if (m_target != nullptr) {
            (m_target->*m_Method)(params...); //Call method on target
        }
    }

    bool Equals(TObject* object, SpecializedDelegateOneParam method) {
        return m_target == object && method == m_Method;
    }

private:
    TObject* m_target;
    SpecializedDelegateOneParam m_Method;
};


//Constructor declaration
template<class TObject, typename... TArgs>
DelegateToMember<TObject, TArgs...>::DelegateToMember(TObject* target, SpecializedDelegateOneParam method) : m_target(target), m_Method(method) {};

template <typename... TArgs>
class Delegate {
private:

    //Attached Objects and Functions
    std::vector<IDelegateInvokable<TArgs...>*> m_Attached;

public:

    ~Delegate();

    template <class T>
    void Add(T* object, void (T::* method)(TArgs... params));

    template <class T>
    void Remove(T* object, void (T::* method)(TArgs... params));

    //Empty all attached functions
    void Clear() {
        for (int i = 0; i < m_Attached.size(); ++i) {
            /*IDelegateInvokable<TArgs...> invokable =*/ 
            delete m_Attached[i];
            m_Attached.erase(m_Attached.begin() + i);
            //delete invokable;
        }
    }

    void Broadcast(TArgs ... params) {
        
        for (int i = 0; i < m_Attached.size();++i) {
            IDelegateInvokable<TArgs...>* member = m_Attached[i];
            member->Broadcast(params...);
        }
    }
};

template <typename ... TArgs>
Delegate<TArgs...>::~Delegate() {
    Clear();
}


template <typename ... TArgs>
template <class T>
void Delegate<TArgs...>::Add(T* object, void (T::* method)(TArgs... params)) {
    //Throw exception if the object is null
    if (object==nullptr) {
        throw new std::exception;
    }
    IDelegateInvokable<TArgs...>* member = new DelegateToMember<T, TArgs...>(object, method);
    m_Attached.push_back(member);
}
template <typename ... TArgs>
template <class T>
void Delegate<TArgs...>::Remove(T* object, void (T::* method)(TArgs... params)) {
    for (int i = 0; i < m_Attached.size();++i) {
        IDelegateInvokable<TArgs...> invokable = m_Attached[i];
        DelegateToMember<T, TArgs...>* castedInvokable = dynamic_cast<DelegateToMember<T, TArgs...>*>(invokable);
        if (castedInvokable != nullptr && castedInvokable->Equals(object,method)) {
            m_Attached.erase(m_Attached.begin()+i);
            delete invokable;
        }
    }
}

