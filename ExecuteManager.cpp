#include "ExecuteManager.h"
#include "Ex_02/Ex02Executor.h"
#include "Ex_03/Ex03Executor.h"

ExecuteManager::ExecuteManager()
	: m_executorIndex(0)
	, m_funcIndex(0)
	, m_isDisplayUi(true)
{
	Initialize();
}

void ExecuteManager::Initialize()
{
	m_image = Image{ s3d::Scene::Size(), s3d::Scene::GetBackground() };
	m_texture = DynamicTexture{ s3d::Scene::Size(), s3d::Scene::GetBackground() };

	m_executors.push_back(std::make_shared<DLFS::EX02::Ex02Executor>());
	m_executors.push_back(std::make_shared<DLFS::EX03::Ex03Executor>());

	for (auto& executor : m_executors)
	{
		executor->Initialize();
	}
}

void ExecuteManager::Update()
{
	// 描画
	{
		m_texture.draw();
	}

	if (m_isDisplayUi)
	{
		// 実行リストボックス
		auto& executor = m_executors[m_executorIndex];
		auto& boxState = executor->GetBoxState();
		SimpleGUI::ListBox(boxState, Vec2{ 300,100 }, 300);

		// 実行
		if (SimpleGUI::Button(U"Execute", Vec2{ 300, 50 }))
		{
			if (boxState.selectedItemIndex)
			{
				ClearPrint();
				executor->SetCanvas(&m_image);
				executor->Execute(static_cast<int>(*boxState.selectedItemIndex));

				m_texture.fill(m_image);
			}
		}

		if (SimpleGUI::Button(U"Prev", Vec2{ 420, 50 }))
		{
			m_executorIndex--;
			m_executorIndex = m_executorIndex < 0 ? m_executors.size() - 1 : m_executorIndex;
		}

		if (SimpleGUI::Button(U"Next", Vec2{ 510, 50 }))
		{
			m_executorIndex++;
			m_executorIndex = m_executors.size() - 1 < m_executorIndex ? 0 : m_executorIndex;
		}
	}

	if (KeyF.down())
	{
		m_isDisplayUi = !m_isDisplayUi;
	}
}
