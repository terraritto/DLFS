#pragma once
#include <Siv3D.hpp>
#include <NumCpp.hpp>

namespace DLFS::EX03
{
	class ReLU
	{
	public:
		Array<Vec2> GetValues();

	protected:
		void Function(float& value) const;
	};
}
