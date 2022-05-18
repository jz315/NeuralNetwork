#pragma once
#include<vector>
#include"Matrix.h"
long double inline CrossEntropy(Martix& x, Martix& y)
{
	if (x.GetCols() == y.GetCols())
	{
		long double sum = 0;
		for (int i = 0; i < x.GetCols(); i++)
		{
			sum += -y.At(0, i) * log(x.At(0, i));
		}
		return sum;
	}
	else
	{
		throw("无法计算");
	}
}

long double inline dCrossEntropy(Martix& x, std::vector<long double>& y)
{
	long double sum = 0;
	for (int i = 0; i < x.GetCols(); i++)
	{
		sum += -y[i] * 1 / (x.At(0, i));
	}
	return sum;
}