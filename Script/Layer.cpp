#include"Layer.h"
#include"ActivationFunction.h"
#include <iostream>
#include "Network.h"

Layer::Layer(int beforeLayerSize, int layerSize, const std::string& activition) :
	w(beforeLayerSize, layerSize),
	b(1, layerSize),
	aLast(1, beforeLayerSize),
	z(1, layerSize),
	dz(1, layerSize),
	mActivitionFunc(activition),
	mLayerSize(layerSize),
	dw(beforeLayerSize, layerSize),
	db(1, layerSize),
	dbSum(1, layerSize),
	daLast(1, beforeLayerSize),
	dwSum(beforeLayerSize, layerSize)
{
	RandomMat(w, -5, 5);
	RandomMat(b, -5, 5);
}

Martix Layer::Feedforward(Martix& a)
{
	aLast = a;
	z = a * w + b;
	if (mActivitionFunc == "relu")
	{
		for (int i = 0; i < mLayerSize; i++)
		{
			z.At(0, i) = Relu(z.At(0, i));
        }
	}
	else if (mActivitionFunc == "tanh")
	{
		for (int i = 0; i < mLayerSize; i++)
		{
			z.At(0, i) = Tanh(z.At(0, i));
		}
	}
	else if (mActivitionFunc == "sigmoid")
	{
		for (int i = 0; i < mLayerSize; i++)
		{
			z.At(0, i) = Sigmoid(z.At(0, i));
		}
	}
	else if (mActivitionFunc == "softmax")
	{
		long double sum = 0;
		for (int i = 0; i < mLayerSize; i++)
		{
			sum += exp(z.At(0, i));
		}
		for (int i = 0; i < mLayerSize; i++)
		{
			z.At(0, i) = Softmax(z.At(0, i), sum);
		}
	}
	else
	{
		throw("未知的函数类型");
	}
	return z;
}

Martix Layer::BackPropagation(Martix& da)
{

	if (mActivitionFunc == "relu")
	{
		for (int i = 0; i < z.GetCols(); i++)
		{
			dz.At(0, i) = dRelu(z.At(0, i)) * da.At(0, i);
		}
	}
	else if (mActivitionFunc == "tanh")
	{
		for (int i = 0; i < z.GetCols(); i++)
		{
			dz.At(0, i) = dTanh(z.At(0, i)) * da.At(0, i);
		}
	}
	else if (mActivitionFunc == "sigmoid")
	{
		for (int i = 0; i < z.GetCols(); i++)
		{
			dz.At(0, i) = dSigmoid(z.At(0, i)) * da.At(0, i);
		}
	}
	

	for (auto i = 0; i < dw.GetCols(); i++)
	{
		for (auto j = 0; j < dw.GetRows(); j++)
		{
			dw.At(j, i) = -aLast.At(0, j) * dz.At(0, i);
		}
	}

	dwSum += dw;

	for (int i = 0; i < db.GetCols(); i++)
	{
		db.At(0, i) = -1 * dz.At(0, i);
	}

	dbSum += db;

	for (int i = 0; i < dz.GetCols(); i++)
	{
		for (int j = 0; j < aLast.GetCols(); j++)
		{
			daLast.At(0, j) += w.At(j, i) * dz.At(0, i);
		}
	}
	return daLast;
}
