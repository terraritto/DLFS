#pragma once

#include <Siv3D.hpp>
#include <NumCpp.hpp>

namespace DLFS::EX03
{
	class TestMNIST
	{
	public:
		TestMNIST();

		bool Initialize();
		void Process(Array<double>& result);

		auto& GetTrainImages() const { return m_trainImages; }
		auto& GetTrainLabels() const { return m_trainLabels; }
		auto& GetTestImages() const { return m_testImages; }
		auto& GetTestLabels() const { return m_testLabels; }

	protected:
		bool DownloadMNIST();
		bool LoadData();
		bool LoadImageData(const String& path, nc::NdArray<float>& data);
		bool LoadLabelData(const String& path, nc::NdArray<unsigned>& data);

	protected:
		String m_baseURL;
		FilePath m_resourceDir;
		std::map<String, String> m_keyFileMap;

		nc::NdArray<float> m_trainImages;
		nc::NdArray<unsigned> m_trainLabels;
		nc::NdArray<float> m_testImages;
		nc::NdArray<unsigned> m_testLabels;

	protected:
		const String TRAIN_IMAGE = U"TrainImage";
		const String TRAIN_LABEL = U"TrainLabel";
		const String TEST_IMAGE = U"TestImage";
		const String TEST_LABEL = U"TestLabel";
		const String IMAGE_EXTENSION = U".idx3-ubyte";
		const String LABEL_EXTENSION = U".idx1-ubyte";
	};
}
