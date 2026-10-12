#include "ReLU.h"

namespace DLFS::EX03
{
	Array<Vec2> ReLU::GetValues()
	{
		auto dataX = nc::arange<float>(-5.0f, 5.0f, 0.1f);
		auto dataY = dataX;

		for (auto& value : dataY)
		{
			Function(value);
		}

		Array<Vec2> result{ dataX.size() };

		for (int i = 0; i < dataX.size(); i++)
		{
			result[i] = { dataX[i], dataY[i] };
		}

		return result;
	}

	void ReLU::Function(float& value) const
	{
		value = Max(0.0f, value);
	}
}
