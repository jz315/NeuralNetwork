#include "Matrix.h"

void RandomMat(Martix& mat, long double a, long double b)
{
	std::default_random_engine e;
	std::uniform_real_distribution<long double> u(a, b);
	for (int i = 0; i < mat.GetRows(); i++)
	{
		for (int j = 0; j < mat.GetCols(); j++)
		{
			mat.At(i, j) = u(e);
		}
	}
}
