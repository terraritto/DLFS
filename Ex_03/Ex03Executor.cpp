#include "Ex03Executor.h"
#include "NeuralMNIST.h"
#include "NeuralMNISTBatch.h"
#include "ReLU.h"
#include "Sigmoid.h"
#include "StepFunction.h"
#include "TestMNIST.h"

namespace DLFS::EX03
{
	void Ex03Executor::Initialize()
	{
		m_functions.push_back([&]() { StepFunctionSample(); });
		m_functions.push_back([&]() { SigmoidFunctionSample(); });
		m_functions.push_back([&]() { SigmoidStepCompare(); });
		m_functions.push_back([&]() { ReLUSample(); });
		m_functions.push_back([&]() { TestMNISTSample(); });
		m_functions.push_back([&]() { NeuralMNISTSample(); });
		m_functions.push_back([&]() { NeuralMNISTBatchSample(); });

		m_boxState = ListBoxState
		{
			{
				U"StepFunction",
				U"Sigmoid",
				U"SigmoidStepCompare",
				U"ReLU",
				U"TestMNIST",
				U"NeuralMNIST",
				U"NeuralMNISTBatch",
			}
		};
	}

	void Ex03Executor::StepFunctionSample()
	{
		m_image->fill(Palette::White);

		InitAxisValue({ -6, 6 }, { -0.1,1.2 });
		DrawAxis();

		{
			StepFunction func;
			auto result = func.GetValues();

			for (int i = 0; i < result.size() - 1; i++)
			{
				Vec2 left = result[i];
				Vec2 right = result[i+1];

				left = ConvertPoint(left); right = ConvertPoint(right);
				Line{ left, right }.overwrite(*m_image, Palette::Green);
			}
		}
	}

	void Ex03Executor::SigmoidFunctionSample()
	{
		m_image->fill(Palette::White);

		InitAxisValue({ -6, 6 }, { -0.1,1.2 });
		DrawAxis();

		{
			Sigmoid func;
			auto result = func.GetValues();

			for (int i = 0; i < result.size() - 1; i++)
			{
				Vec2 left = result[i];
				Vec2 right = result[i + 1];

				left = ConvertPoint(left); right = ConvertPoint(right);
				Line{ left, right }.overwrite(*m_image, Palette::Green);
			}
		}
	}

	void Ex03Executor::SigmoidStepCompare()
	{
		m_image->fill(Palette::White);

		InitAxisValue({ -6, 6 }, { -0.1,1.2 });
		DrawAxis();

		{
			StepFunction func;
			auto result = func.GetValues();

			for (int i = 0; i < result.size() - 1; i++)
			{
				Vec2 left = result[i];
				Vec2 right = result[i + 1];

				left = ConvertPoint(left); right = ConvertPoint(right);
				Line{ left, right }.overwrite(*m_image, Palette::Red);
			}
		}

		{
			Sigmoid func;
			auto result = func.GetValues();

			for (int i = 0; i < result.size() - 1; i++)
			{
				Vec2 left = result[i];
				Vec2 right = result[i + 1];

				left = ConvertPoint(left); right = ConvertPoint(right);
				Line{ left, right }.overwrite(*m_image, Palette::Green);
			}
		}
	}

	void Ex03Executor::ReLUSample()
	{
		m_image->fill(Palette::White);

		InitAxisValue({ -6, 6 }, { -0.1,6.0 });
		DrawAxis();

		{
			ReLU func;
			auto result = func.GetValues();

			for (int i = 0; i < result.size() - 1; i++)
			{
				Vec2 left = result[i];
				Vec2 right = result[i + 1];

				left = ConvertPoint(left); right = ConvertPoint(right);
				Line{ left, right }.overwrite(*m_image, Palette::Green);
			}
		}
	}

	void Ex03Executor::TestMNISTSample()
	{
		TestMNIST mnist;
		if (!mnist.Initialize()) { return; }

		Array<double> result;
		mnist.Process(result);

		m_image->fill(Palette::White);

		InitAxisValue({ -6, 6 }, { -0.1,6.0 });
		DrawAxis();

		{
			for (int h = 0; h < m_image->height(); h++)
			{
				for (int w = 0; w < m_image->width(); w++)
				{
					double value = result[w + m_image->width() * h] / 255.0;
					(*m_image)[h][w] = ColorF{ value, value, value, 1.0 };
				}
			}
		}
	}

	void Ex03Executor::NeuralMNISTSample()
	{
		NeuralMNIST mnist;
		mnist.Initialize();
		mnist.Process();
	}

	void Ex03Executor::NeuralMNISTBatchSample()
	{
		NeuralMNISTBatch mnist;
		mnist.Initialize();
		mnist.Process(100);
	}

	void Ex03Executor::DrawAxis()
	{
		Vec2 left = ConvertPoint({ MIN_X_VALUE, 0 });
		Vec2 right = ConvertPoint({ MAX_X_VALUE, 0 });
		Vec2 top = ConvertPoint({ 0, MAX_Y_VALUE });
		Vec2 bottom = ConvertPoint({ 0, MIN_Y_VALUE });

		Line{ left, right }.overwrite(*m_image, Palette::Black);
		Line{ top, bottom }.overwrite(*m_image, Palette::Black);
	}

	Vec2 Ex03Executor::ConvertPoint(const Vec2& value)
	{
		Vec2 result;
		result.x = (value.x - MIN_X_VALUE) / (MAX_X_VALUE - MIN_X_VALUE) * Scene::Size().x;
		result.y = (MAX_Y_VALUE - value.y) / (MAX_Y_VALUE - MIN_Y_VALUE) * Scene::Size().y;
		return result;
	}

	void Ex03Executor::InitAxisValue(Vec2 X, Vec2 Y)
	{
		MIN_X_VALUE = X.x; MAX_X_VALUE = X.y;
		MIN_Y_VALUE = Y.x; MAX_Y_VALUE = Y.y;
	}
}
