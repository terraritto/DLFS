#include "ExecutorBase.h"

void ExecutorBase::Execute(int index)
{
	auto& func = m_functions[index];
	func();
}
