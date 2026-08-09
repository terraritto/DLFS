#include "Ex02Executor.h"
#include "AndGate.h"
#include "NandGate.h"
#include "OrGate.h"
#include "XorGate.h"

namespace DLFS::EX02
{
	void Ex02Executor::Initialize()
	{
		m_functions.push_back([&]() { ANDGateSample(); });
		m_functions.push_back([&]() { NANDGateSample(); });
		m_functions.push_back([&]() { ORGateSample(); });
		m_functions.push_back([&]() { XORGateSample(); });

		m_boxState = ListBoxState
		{
			{
				U"AND Gate",
				U"NAND Gate",
				U"OR Gate",
				U"XOR Gate"
			}
		};
	}

	void Ex02Executor::ANDGateSample()
	{
		m_image->fill(s3d::Scene::GetBackground());

		AndGate andGate;

		DrawAxis();

		{
			// 決定境界
			Vec2 left = andGate.GetDecisionBoundary(MIN_X_VALUE);
			Vec2 right = andGate.GetDecisionBoundary(MAX_X_VALUE);

			left = ConvertPoint(left); right = ConvertPoint(right);
			Line{ left, right }.overwrite(*m_image, Palette::Green);
		}

		{
			// 分類データ
			Array<Vec2> points = { {0,0},{0,1},{1,0},{1,1} };

			for (const auto& point : points)
			{
				bool result = andGate.Evaluate(point);
				Vec2 convert = ConvertPoint(point);
				Circle{ convert, 5 }.overwrite(*m_image, result ? Palette::Red : Palette::Blue);
			}
		}
	}

	void Ex02Executor::NANDGateSample()
	{
		m_image->fill(s3d::Scene::GetBackground());

		NandGate nandGate;

		DrawAxis();

		{
			// 決定境界
			Vec2 left = nandGate.GetDecisionBoundary(MIN_X_VALUE);
			Vec2 right = nandGate.GetDecisionBoundary(MAX_X_VALUE);

			left = ConvertPoint(left); right = ConvertPoint(right);
			Line{ left, right }.overwrite(*m_image, Palette::Green);
		}

		{
			// 分類データ
			Array<Vec2> points = { {0,0},{0,1},{1,0},{1,1} };

			for (const auto& point : points)
			{
				bool result = nandGate.Evaluate(point);
				Vec2 convert = ConvertPoint(point);
				Circle{ convert, 5 }.overwrite(*m_image, result ? Palette::Red : Palette::Blue);
			}
		}
	}

	void Ex02Executor::ORGateSample()
	{
		m_image->fill(s3d::Scene::GetBackground());

		OrGate orGate;

		DrawAxis();

		{
			// 決定境界
			Vec2 left = orGate.GetDecisionBoundary(MIN_X_VALUE);
			Vec2 right = orGate.GetDecisionBoundary(MAX_X_VALUE);

			left = ConvertPoint(left); right = ConvertPoint(right);
			Line{ left, right }.overwrite(*m_image, Palette::Green);
		}

		{
			// 分類データ
			Array<Vec2> points = { {0,0},{0,1},{1,0},{1,1} };

			for (const auto& point : points)
			{
				bool result = orGate.Evaluate(point);
				Vec2 convert = ConvertPoint(point);
				Circle{ convert, 5 }.overwrite(*m_image, result ? Palette::Red : Palette::Blue);
			}
		}
	}

	void Ex02Executor::XORGateSample()
	{
		m_image->fill(s3d::Scene::GetBackground());

		XorGate xorGate;

		DrawAxis();

		{
			// 決定境界
			auto size = Scene::Size();
			for (int x = 0; x < size.x; x++)
			{
				for (int y = 0; y < size.y; y++)
				{
					Vec2 p = InvertPoint({ x,y });
					if (xorGate.Evaluate(p))
					{
						(*m_image)[y][x] = Palette::Green;
					}
				}
			}
		}

		{
			// 分類データ
			Array<Vec2> points = { {0,0},{0,1},{1,0},{1,1} };

			for (const auto& point : points)
			{
				bool result = xorGate.Evaluate(point);
				Vec2 convert = ConvertPoint(point);
				Circle{ convert, 5 }.overwrite(*m_image, result ? Palette::Red : Palette::Blue);
			}
		}
	}

	void Ex02Executor::DrawAxis()
	{
		Vec2 left = ConvertPoint({ MIN_X_VALUE, 0 });
		Vec2 right = ConvertPoint({ MAX_X_VALUE, 0 });
		Vec2 top = ConvertPoint({ 0, MAX_Y_VALUE });
		Vec2 bottom = ConvertPoint({ 0, MIN_Y_VALUE });

		Line{ left, right }.overwrite(*m_image, Palette::White);
		Line{ top, bottom }.overwrite(*m_image, Palette::White);
	}

	Vec2 Ex02Executor::ConvertPoint(const Vec2& value)
	{
		Vec2 result;
		result.x = (value.x - MIN_X_VALUE)  / (MAX_X_VALUE - MIN_X_VALUE) * Scene::Size().x;
		result.y = (MAX_Y_VALUE - value.y)  / (MAX_Y_VALUE - MIN_Y_VALUE) * Scene::Size().y;
		return result;
	}

	Vec2 Ex02Executor::InvertPoint(const Vec2& value)
	{
		Vec2 result;
		result.x = value.x * (MAX_X_VALUE - MIN_X_VALUE) / Scene::Size().x + MIN_X_VALUE;
		result.y = MAX_Y_VALUE - value.y * (MAX_Y_VALUE - MIN_Y_VALUE) / Scene::Size().y;
		return result;
	}
}
