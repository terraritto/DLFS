#include "NeuralMNISTBatch.h"
#include "Base/FuncUtil.h"

namespace DLFS::EX03
{
	bool NeuralMNISTBatch::Initialize()
	{
		if (!m_mnist.Initialize()) { return false; }

		if (!LoadWeight()) { return false; }

		return true;
	}

	void NeuralMNISTBatch::Process(int BatchSize)
	{
		ClearPrint();

		const auto& testImages = m_mnist.GetTestImages();
		const auto& testLabels = m_mnist.GetTestLabels();

		FuncSigmoid sigmoid;
		FuncSoftmax softmax;

		int count = 0;

		for (int i = 0; i < testImages.numRows(); i+= BatchSize)
		{
			auto data = testImages(nc::Slice(i, i+BatchSize), testImages.cSlice());
			data /= 255.0f;

			data = data.dot(m_weightMap[U"W1"]) + m_weightMap[U"b1"];
			sigmoid.Process(data);
			data = data.dot(m_weightMap[U"W2"]) + m_weightMap[U"b2"];
			sigmoid.Process(data);
			data = data.dot(m_weightMap[U"W3"]) + m_weightMap[U"b3"];
			softmax.Process(data);

			auto maxIndex = data.argmax(nc::Axis::COL);
			auto label = testLabels(0, nc::Slice(i, i + BatchSize));
			for (int i = 0; i < maxIndex.size(); i++)
			{
				count += maxIndex[i] == label[i];
			}
		}

		Print << U"Accuracy: " << Format(static_cast<float>(count) / testImages.numRows());
	}

	bool NeuralMNISTBatch::LoadWeight()
	{
		m_weightPath = FileSystem::CurrentDirectory() + U"Resource/Ex03/sample_weight.json";

		const auto json = JSON::Load(m_weightPath);
		if (!json)
		{
			Logger << U"Json File Load Failed: " << m_weightPath;
			return false;
		}

		// bias
		const Array<String> biasNameList = { U"b1", U"b2", U"b3" };
		for (const auto& biasName : biasNameList)
		{
			nc::NdArray<float> bs;
			const auto data = json[biasName];
			bs.resizeFast(1, data.size());
			for (int i = 0; const auto& bias : json[biasName])
			{
				bs[i] = (bias.value.get<float>());
				i++;
			}
			m_weightMap[biasName] = bs;
		}

		// weight
		const Array<String> weightNameList = { U"W1", U"W2", U"W3" };
		for (const auto& weightName : weightNameList)
		{
			nc::NdArray<float> ws;
			const auto data = json[weightName];
			ws.resizeFast(data.size(), data[0].size());
			for (int i = 0; const auto& weightKey : data)
			{
				for (int j = 0; const auto& weight : weightKey.value)
				{
					ws[j + i * ws.numCols()] = weight.value.get<float>();
					j++;
				}
				i++;
			}
			m_weightMap[weightName] = ws;
		}

		return true;
	}
}
