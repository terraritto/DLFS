#include "Sigmoid.h"

namespace DLFS::EX03
{
	Array<Vec2> Sigmoid::GetValues()
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

	void Sigmoid::Function(float& value) const
	{
		value = 1.0f / (1.0f + Exp(-value));
	}
}
