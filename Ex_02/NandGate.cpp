#include "NandGate.h"

namespace DLFS::EX02
{
	NandGate::NandGate()
		: m_weight({ -0.5, -0.5 })
		, m_bias(0.7)
	{
	}

	bool NandGate::Evaluate(const Vec2 value)
	{
		double result = Dot(value, m_weight) + m_bias;
		return result > 0.0;
	}

	Vec2 NandGate::GetDecisionBoundary(const double x)
	{
		return Vec2{ x, -(x * m_weight.x + m_bias) / m_weight.y };
	}
}
