#pragma once
#include "../Base/ExecutorBase.h"

namespace DLFS::EX02
{
	class Ex02Executor : public ExecutorBase
	{
	public:
		virtual void Initialize() override;

	private:
		void ANDGateSample();
		void NANDGateSample();
		void ORGateSample();
		void XORGateSample();

	private:
		void DrawAxis();
		Vec2 ConvertPoint(const Vec2& value);
		Vec2 InvertPoint(const Vec2& value);

	private:
		static constexpr int MIN_X_VALUE = -10;
		static constexpr int MIN_Y_VALUE = -10;
		static constexpr int MAX_X_VALUE = 10;
		static constexpr int MAX_Y_VALUE = 10;
	};
}
