#pragma once
#include <Siv3D.hpp>

namespace DLFS::EX02
{
	class XorGate
	{
	public:
		XorGate();

		bool Evaluate(const Vec2 value);
	};
}
