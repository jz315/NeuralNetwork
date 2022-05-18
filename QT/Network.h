#pragma once
#include"Layer.h"
#include"Decay.h"
#include<fstream>
#include"Matrix.h"


class Network
{
public:
	friend class Layer;

	Network();
	~Network();

	void Train(std::vector<std::vector<long double> >& x, std::vector<std::vector<long double>>& y, int epochs, int batchSize);
	
	void Test(std::vector<std::vector<long double> >& x, std::vector<std::vector<long double>>& y);

	void AddLayer(int size, const std::string& func);
	
	void Options(const std::string& loss, Decay* decay);

	Martix Eval(std::vector<long double>&x);

	void Save(const std::string& fileName);

	void Load(const std::string& fileName);
private:
	Martix Feedforward(Martix& input);
	void BackPropagation(Martix& x, Martix& y,int times);
	void Input(std::vector<long double>&input, std::vector<long double>& y, int times);

	void Evaluate(std::vector<long double>& input, std::vector<long double>& y);
	void ComputeAccuracy(Martix& in, std::vector<long double>& y);
	void UpdateParameters();

	std::vector<Layer>mLayers;
	
	std::string mLoss;

	int mInputSize = 0, mOutputSize = 0, mDepth = 0, mBatchSize = 1;

	Decay* mDecay;

	long double mSuccessSum = 0, mRight = 0;

	std::fstream mStream;

	bool mIsOption = false;

	long double mLossSum = 0;
	/*
	std::vector<Martix>a;
	std::vector<Martix>w;
	std::vector<Martix>w;
	std::vector<Martix>b;
	std::vector<Martix>dw;
	std::vector<Martix>db;
	std::vector<Martix>dwSum;
	std::vector<Martix>dbSum;
	*/
};