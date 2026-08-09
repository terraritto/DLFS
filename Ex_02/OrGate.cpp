#include "OrGate.h"

namespace DLFS::EX02
{
	OrGate::OrGate()
		: m_weight({ 0.5, 0.5 })
		, m_bias(-0.2)
	{
	}

	bool OrGate::Evaluate(const Vec2 value)
	{
		double result = Dot(value, m_weight) + m_bias;
		return result > 0.0;
	}

	Vec2 OrGate::GetDecisionBoundary(const double x)
	{
		return Vec2{ x, -(x * m_weight.x + m_bias) / m_weight.y };
	}
}
