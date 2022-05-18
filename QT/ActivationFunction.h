#pragma once
#include<cmath>
#include<algorithm>
#include<unordered_map>
#include<functional>
#include<string>

long double inline Relu(long double x)
{
	return std::max(0.0L, x);
}

long double inline Tanh(long double x)
{
	return tanh(x);
}

long double inline Sigmoid(long double x)
{
	return 1L / 1L + exp(-x);
}

long double inline Softmax(long double x, long double sum)
{
	return exp(x) / sum;
}

long double inline dRelu(long double x)
{
	if (x <= 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

long double inline dTanh(long double x)
{
	return 1 - pow(tanh(x), 2);
}

long double inline dSigmoid(long double x)
{
	return Sigmoid(x) * (1 - Sigmoid(x));
}

long double inline dSoftmax(long double x, long double sum)
{
	return exp(x) / sum;
}


