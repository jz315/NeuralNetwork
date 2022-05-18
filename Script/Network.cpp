#include<iostream>
#include "Network.h"
#include"LossFunction.h"
#include<algorithm>
#include"json.hpp"
using namespace nlohmann;
Network::Network():
	mDecay(nullptr)
{
	std::ios::sync_with_stdio(false);
}

Network::~Network()
{
}

void Network::Train(std::vector<std::vector<long double>>& x, std::vector<std::vector<long double>>& y, int epochs, int batchSize)
{
	
	if (x.size() == y.size() && mIsOption)
	{
		int sampleSize = x.size();
		int iteration = x.size() / batchSize;
		std::cout << "Start Training" << "\n";

		for (int i = 0; i < epochs; i++)
		{
			mSuccessSum = 0;
			for (int j = 0; j < iteration; j++)
			{
				mLossSum = 0;
				for (int k = 0; k < batchSize; k++)
				{
					Input(x[j * batchSize + k], y[j * batchSize + k], i * sampleSize + j * batchSize + k + 1);
				}
				std::cout << (j + 1) * batchSize <<"/"<<sampleSize << " Loss:" << mLossSum / (batchSize) << " Accuracy:" << mSuccessSum / ((j + 1) * batchSize) << "\n";
				UpdateParameters();
			}
		}
	}
}

Martix Network::Feedforward(Martix& input)
{
	Martix& mat = input;
	for (auto& layer : mLayers)
	{
		mat = layer.Feedforward(mat);
	}
	return mat;
}

void Network::BackPropagation(Martix& x, Martix& y,int times)
{
	long double step = mDecay->GetLearningRate(times);
	auto lastLayer = (mLayers.end() - 1);
	
	if (mLoss == "cross-entropy")
	{
		mLossSum += CrossEntropy(x, y);
	}

	if (mLoss == "cross-entropy" && lastLayer->GetActivitionFuncName() == "softmax")
	{
		lastLayer->dz = step * (x - y);
	}
	
	for (auto i = 0; i < lastLayer->dw.GetCols(); i++)
	{
		for (auto j = 0; j < lastLayer->dw.GetRows(); j++)
		{
			lastLayer->dw.At(j, i) = -lastLayer->aLast.At(0, j) * lastLayer->dz.At(0, i);
		}
	}

	lastLayer->dwSum += lastLayer->dw;

	for (int i = 0; i < x.GetCols(); i++)
	{
		lastLayer->db.At(0, i) = -lastLayer->dz.At(0, i);
	}

	lastLayer->dbSum += lastLayer->db;

	for (int i = 0; i < lastLayer->dz.GetCols(); i++)
	{
		for (int j = 0; j < lastLayer->daLast.GetCols(); j++)
		{
			lastLayer->daLast.At(0, j) = lastLayer->w.At(j, i) * lastLayer->dz.At(0, i);
		}
	}

	Martix& mat = lastLayer->dz;
	for (auto iter = lastLayer; iter != mLayers.begin(); iter--)
	{
		mat = iter->BackPropagation(mat);
	}
}

void Network::Input(std::vector<long double>& input, std::vector<long double>& y, int times)
{
	Martix in(1, mInputSize);
	if (input.size() == mInputSize)
	{
		in.GetData()[0] = input;
	}

	Martix label(1, y.size());
	label.GetData()[0] = y;

	Feedforward(in);
	BackPropagation(in,label, times);
	ComputeAccuracy(in,y);
}

void Network::Evaluate(std::vector<long double>& input, std::vector<long double>& y)
{
	Martix in(1, mInputSize);
	in.GetData()[0] = input;

	Feedforward(in);
	ComputeAccuracy(in, y);
}

void Network::ComputeAccuracy(Martix& in, std::vector<long double>& y)
{
	long double maxNum = 0;
	int pos = 0, realPos= 0;

	for (int i = 0; i < in.GetCols(); i++)
	{
		if (in.At(0, i) > maxNum)
		{
			pos = i;
			maxNum = in.At(0, i);
		}
	}

	if (y[pos] == 1)
	{
		mSuccessSum++;
	}
}

void Network::UpdateParameters()
{
	for (auto iter = mLayers.end() - 1; iter != mLayers.begin(); iter--)
	{
		iter->w += iter->dwSum;
		iter->b += iter->dbSum;

		iter->dbSum.Clear();
		iter->dwSum.Clear();
	}
}

void Network::Test(std::vector<std::vector<long double> >& x, std::vector<std::vector<long double>>& y)
{
	mSuccessSum = 0;

	std::cout << "Start Testing" << std::endl;
	
	if (x.size() == y.size())
	{
		for (int k = 0; k < x.size(); k++)
		{
			Evaluate(x[k], y[k]);
		}
	}
	std::cout << "Test Accuracy:" << mSuccessSum / x.size() << "\n";
}

void Network::AddLayer(int size, const std::string& func)
{
	if (func == "input")
	{
		mInputSize = size;
	}
	else
	{
		if (mDepth == 0)
		{
			mLayers.emplace_back(Layer(mInputSize, size, func));
		}
		else
		{
			mLayers.emplace_back(Layer(mLayers[mDepth - 1].GetLayerSize(), size, func));
		}
		mDepth++;
	}
}

void Network::Options(const std::string& loss, Decay* decay)
{
	mIsOption = true;
	mDecay = decay;
	mLoss = loss;
}

auto Network::Eval(std::vector<long double>& x)
{
	Martix in(1, mInputSize);
	if (x.size() == mInputSize)
	{
		in.GetData()[0] = x;
	}
	return Feedforward(in);
}

void Network::Save(const std::string& fileName)
{
	json doc = {
		{"inputSize",mInputSize}
	};
	json layers = json::array();
	
	for (int i = 0; i < mLayers.size(); i++)
	{
		auto& layer = mLayers[i];

		json layerObj = json::object();
		layerObj.push_back({ "layerSize", layer.mLayerSize });
		layerObj.push_back({ "lastLayerSize",layer.aLast.GetCols() });
		layerObj.push_back({ "activation",layer.mActivitionFunc });
		json matArray = json::array();
		for (int j = 0; j < layer.w.GetRows(); j++)
		{
			json matRow = json::array();
			for (int k = 0; k < layer.w.GetCols(); k++)
			{
				matRow.push_back(layer.w.At(j,k));
			}
			matArray.push_back(matRow);
		}
		layerObj.push_back({ "w", matArray });

		json matArray1 = json::array();
		for (int j = 0; j < 1; j++)
		{
			json matRow = json::array();
			for (int k = 0; k < layer.b.GetCols(); k++)
			{
				matRow.push_back(layer.b.At(j, k));
			}
			matArray1.push_back(matRow);
		}
		layerObj.push_back({ "b", matArray1 });

		layers.push_back(layerObj);
	}

	doc.push_back({ "layers",layers });

	std::ofstream(fileName) << doc;
	
}

void Network::Load(const std::string& fileName)
{
	json doc;
	std::ifstream(fileName) >> doc;
	AddLayer(doc["inputSize"].get<int>(), "input");

	json& layers = doc["layers"];
	for (int i = 0; i < layers.size(); i++)
	{
		auto& layer = layers.at(i);
		int lastLayerSize = layer["lastLayerSize"].get<int>();
		int layerSize = layer["layerSize"].get<int>();
		
		Martix matW(lastLayerSize, layerSize);
		Martix matB(1, layerSize);

		AddLayer(layer["layerSize"].get<int>(), layer["activation"].get<std::string>());

		auto& jsonMatW = layer["w"];
		for (int j = 0; j < lastLayerSize; j++)
		{
			for (int k = 0; k < layerSize; k++)
			{
				matW.At(j, k) = jsonMatW.at(j).at(k).get<long double>();
			}
		}
		mLayers[i].w = matW;

		auto& jsonMatB = layer["b"];
		for (int j = 0; j < 1; j++)
		{
			for (int k = 0; k < layerSize; k++)
			{
				matB.At(j, k) = jsonMatB.at(j).at(k).get<long double>();
			}
		}
		mLayers[i].b = matB;
	}
	
}
