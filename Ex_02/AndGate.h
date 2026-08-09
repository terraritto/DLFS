#pragma once
#include <Siv3D.hpp>

namespace DLFS::EX02
{
	class AndGate
	{
	public:
		AndGate();

		bool Evaluate(const Vec2 value);
		Vec2 GetDecisionBoundary(const double x);

	protected:
		Vec2 m_weight;
		double m_bias;
	};
}
