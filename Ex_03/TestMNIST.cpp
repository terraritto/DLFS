#include "TestMNIST.h"

namespace DLFS::EX03
{
	TestMNIST::TestMNIST()
		: m_baseURL(U"https://ossci-datasets.s3.amazonaws.com/mnist/")
	{
		m_resourceDir = FileSystem::CurrentDirectory() + U"Resource/";

		m_keyFileMap[TRAIN_IMAGE] = U"train-images-idx3-ubyte.gz";
		m_keyFileMap[TRAIN_LABEL] = U"train-labels-idx1-ubyte.gz";
		m_keyFileMap[TEST_IMAGE] = U"t10k-images-idx3-ubyte.gz";
		m_keyFileMap[TEST_LABEL] = U"t10k-labels-idx1-ubyte.gz";
	}

	bool TestMNIST::Initialize()
	{
		// Resourceフォルダの生成
		if (FileSystem::Exists(m_resourceDir))
		{
			FileSystem::CreateDirectories(m_resourceDir);
		}

		if (!DownloadMNIST()) { return false; }

		if (!LoadData()) { return false; }

		return true;
	}

	void TestMNIST::Process(Array<double>& result)
	{
		ClearPrint();

		auto sceneSize = Scene::Size();
		result.resize(sceneSize.x * sceneSize.y, 1.0);

		constexpr int xOffset = 300;
		const int xPlaceNum = (sceneSize.x - xOffset) / 28;
		const int yPlaceNum = (sceneSize.y) / 28;

		// Testデータを試しに描画してみる
		for (auto y = 0; y < yPlaceNum; y++)
		{
			for (auto x = 0; x < xPlaceNum; x++)
			{
				auto data = m_trainImages.row(y * xPlaceNum + x);
				data.reshape(28, 28);

				auto basePoint = xOffset + x * 28;
				basePoint += sceneSize.x * 28 * y;
				for (int r = 0; r < 28; r++)
				{
					for (int c = 0; c < 28; c++)
					{
						result[basePoint + (c + r * sceneSize.x)] = data.row(r)[c];
					}
				}
			}
		}

		// Testのラベルも列枚に描画してみる
		Array<unsigned> labels;
		for (auto y = 0; y < yPlaceNum; y++)
		{
			for (auto x = 0; x < xPlaceNum; x++)
			{
				auto data = m_trainLabels.column(y * xPlaceNum + x);
				labels.push_back(data[0]);
			}

			Print << labels;
			labels.clear();
		}
	}

	bool TestMNIST::DownloadMNIST()
	{
		for (auto& [key, value] : m_keyFileMap)
		{
			auto filePath = m_resourceDir + value;

			// ファイルがある場合はすでにダウンロードされてる
			if (FileSystem::Exists(filePath)) { continue; }

			// MNISTをダウンロード
			auto downloadUrl = m_baseURL + value;
			if (!SimpleHTTP::Save(downloadUrl, filePath))
			{
				return false;
			}

			// gzはダメっぽい...
			/*
			// gzを開く
			BinaryReader reader = BinaryReader{ filePath };
			if (!reader) { return false; }

			// gzを取得
			size_t dataSize = reader.size();
			Blob compressedData{ dataSize };
			reader.read(compressedData.data(), dataSize);

			// 解凍
			Blob decompressedData;
			if (!Zlib::Decompress(compressedData, decompressedData))
			{
				return false;
			}

			// 解凍が成功してるなら保存
			auto saveFile = m_resourceDir + key;
			if (BinaryWriter writer{ saveFile })
			{
				writer.write(decompressedData.data(), decompressedData.size());
			}
			*/
		}

		return true;
	}

	bool TestMNIST::LoadData()
	{
		auto filePath = m_resourceDir + TRAIN_IMAGE + IMAGE_EXTENSION;
		if (!LoadImageData(filePath, m_trainImages)) { return false; }

		filePath = m_resourceDir + TRAIN_LABEL + LABEL_EXTENSION;
		if (!LoadLabelData(filePath, m_trainLabels)) { return false; }

		filePath = m_resourceDir + TEST_IMAGE + IMAGE_EXTENSION;
		if (!LoadImageData(filePath, m_testImages)) { return false; }

		filePath = m_resourceDir + TEST_LABEL + LABEL_EXTENSION;
		if (!LoadLabelData(filePath, m_testLabels)) { return false; }

		return true;
	}

	bool TestMNIST::LoadImageData(const String& path, nc::NdArray<float>& data)
	{		
		BinaryReader reader = BinaryReader{ path };
		if (!reader) { return false; }

		auto reverse = [](int32 i)
		{
				// Convert from c4 c3 c2 c1 to c1 c2 c3 c4
				unsigned char c1, c2, c3, c4;

				c1 = i & 255;
				c2 = (i >> 8) & 255;
				c3 = (i >> 16) & 255;
				c4 = (i >> 24) & 255;

				return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
		};

		int32 imageNum, row, col;

		reader.skip(4); // MagicNumber
		reader.read(&imageNum, 4); imageNum = reverse(imageNum);
		reader.read(&row, 4); row = reverse(row);
		reader.read(&col, 4); col = reverse(col);

		data.resizeFast(imageNum, row * col);
		for (int j = 0; j < row * col * imageNum; j++)
		{
			unsigned char v;
			reader.read(&v, 1);
			data[j] = v;
		}

		return true;
	}

	bool TestMNIST::LoadLabelData(const String& path, nc::NdArray<unsigned>& data)
	{
		BinaryReader reader = BinaryReader{ path };
		if (!reader) { return false; }

		auto reverse = [](int32 i)
			{
				// Convert from c4 c3 c2 c1 to c1 c2 c3 c4
				unsigned char c1, c2, c3, c4;

				c1 = i & 255;
				c2 = (i >> 8) & 255;
				c3 = (i >> 16) & 255;
				c4 = (i >> 24) & 255;

				return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
			};

		int32 labelNum;

		reader.skip(4); // MagicNumber
		reader.read(&labelNum, 4); labelNum = reverse(labelNum);

		data.resizeFast(1, labelNum);
		for (int j = 0; j < labelNum; j++)
		{
			unsigned char v;
			reader.read(&v, 1);
			data[j] = v;
		}

		return true;
	}
}
