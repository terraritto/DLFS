#pragma once
#include <Siv3D.hpp>
#include <NumCpp.hpp>

class FuncBase
{
public:
	virtual void Process(nc::NdArray<float>& results) const = 0;
};

class FuncSigmoid : public FuncBase
{
public:
	void Process(nc::NdArray<float>& results) const override
	{
		for (auto& value : results)
		{
			value = 1.0f / (1.0f + Exp(-value));
		}
	}
};

class FuncSoftmax : public FuncBase
{
public:
	void Process(nc::NdArray<float>& results) const override
	{
		const auto maxValue = results.max();
		results = results - maxValue;

		// 合計を計算
		auto temp = results; 
		for (auto& value : temp) { value = Exp(value); }
		auto sum = temp.sum();

		// softmaxを適用
		for (auto& value : results)
		{
			value = Exp(value) / sum[0];
		}
	}
};
