#include "XorGate.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NandGate.h"

namespace DLFS::EX02
{
	XorGate::XorGate()
	{
	}

	bool XorGate::Evaluate(const Vec2 value)
	{
		NandGate nandGate;
		AndGate andGate;
		OrGate orGate;

		Vec2 medium = { nandGate.Evaluate(value), orGate.Evaluate(value) };
		return andGate.Evaluate(medium);
	}
}

