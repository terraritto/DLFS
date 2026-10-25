#pragma once
#include <Siv3D.hpp>
#include <NumCpp.hpp>
#include "TestMNIST.h"

namespace DLFS::EX03
{
	class NeuralMNIST
	{
	public:
		bool Initialize();
		void Process();

	protected:
		bool LoadWeight();

	protected:
		std::map<String, nc::NdArray<float>> m_weightMap;
		FilePath m_weightPath;
		TestMNIST m_mnist;
	};
}
