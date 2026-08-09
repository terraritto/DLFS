#pragma once
#include <Siv3D.hpp>

namespace DLFS::EX02
{
	class OrGate
	{
	public:
		OrGate();

		bool Evaluate(const Vec2 value);
		Vec2 GetDecisionBoundary(const double x);

	protected:
		Vec2 m_weight;
		double m_bias;
	};
}
