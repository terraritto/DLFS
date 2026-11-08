#pragma once
#include "../Base/ExecutorBase.h"

namespace DLFS::EX03
{
	class Ex03Executor : public ExecutorBase
	{
	public:
		virtual void Initialize() override;

	private:
		void StepFunctionSample();
		void SigmoidFunctionSample();
		void SigmoidStepCompare();
		void ReLUSample();
		void TestMNISTSample();
		void NeuralMNISTSample();
		void NeuralMNISTBatchSample();

	private:
		void DrawAxis();
		Vec2 ConvertPoint(const Vec2& value);

		void InitAxisValue(Vec2 X, Vec2 Y);

	private:
		float MIN_X_VALUE = -6;
		float MIN_Y_VALUE = -0.1;
		float MAX_X_VALUE = 6;
		float MAX_Y_VALUE = 1.2;
	};
}
