#pragma once
#include "Base/ExecutorBase.h"

class ExecuteManager
{
public:
	ExecuteManager();
	void Update();

protected:
	void Initialize();

protected:
	Array<std::shared_ptr<ExecutorBase>> m_executors;

	int m_executorIndex = 0;
	int m_funcIndex = 0;

	Image m_image;
	DynamicTexture m_texture;

	bool m_isDisplayUi;
};
