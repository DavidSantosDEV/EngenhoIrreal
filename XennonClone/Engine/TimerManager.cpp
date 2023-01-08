#include "TimerManager.h"
#include <mutex>

std::vector<TimerHandle*> TimerManager::m_ExecutionRow;
std::vector<TimerHandle*> TimerManager::m_CreatedHandles;

static std::mutex m_HandlesMutex;

void TimerManager::ExecuteHandles()
{
	std::lock_guard<std::mutex> lock(m_HandlesMutex);
	for (int i = 0; i < m_ExecutionRow.size();++i) {
		if (m_ExecutionRow[i]->GetIsActive()) {
			m_ExecutionRow[i]->Execute();
		}
		else {
			TimerHandle* handle = m_ExecutionRow[i];
			__InternalRemoveHandle(handle);
			delete handle;
		}
		m_ExecutionRow.erase(m_ExecutionRow.begin() + i);		
	}
}

void TimerManager::AddHandleToExecution(TimerHandle* handle)
{
	std::lock_guard<std::mutex> lock(m_HandlesMutex);
	if (handle!=nullptr) {
		m_ExecutionRow.push_back(handle);
	}
}

void TimerManager::__InternalRemoveHandle(TimerHandle* handle)
{
	if (!handle)return;
	for (int i = 0; i < m_CreatedHandles.size();++i) {
		if (m_CreatedHandles[i] == handle) {
			m_CreatedHandles.erase(m_CreatedHandles.begin() + i);
			return;
		}

	}
}
