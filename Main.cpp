#include <Siv3D.hpp>
#include "ExecuteManager.h"

void Main()
{
	ExecuteManager manager;

	while (System::Update())
	{
		manager.Update();
	}
}
