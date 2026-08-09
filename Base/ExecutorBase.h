#pragma once
#include <Siv3D.hpp>

class ExecutorBase
{
public:
	void Execute(int index);
	ListBoxState& GetBoxState() { return m_boxState; }
	virtual void Initialize() = 0;

	void SetCanvas(Image* image) { m_image = image; }

protected:
	Array<std::function<void()>> m_functions;
	ListBoxState m_boxState;
	Image* m_image;
};
