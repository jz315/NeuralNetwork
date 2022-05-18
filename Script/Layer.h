#pragma once
#include"Matrix.h"
#include<string>
class Layer
{
public:
	friend class Network;

	Layer(int beforeLayerSize, int layerSize, const std::string& activition);

	Martix Feedforward(Martix& a);
	Martix BackPropagation(Martix& da);

	auto GetLayerSize() { return mLayerSize; }
	auto& GetActivitionFuncName() { return mActivitionFunc; }
private:
	Martix aLast, w, b, z;
	Martix dz;
	Martix dw;
	Martix db;
	Martix daLast;
	Martix dbSum, dwSum;
	std::string mActivitionFunc;
	int mLayerSize;
};