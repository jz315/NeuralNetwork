#pragma once
#include<cmath>
#include<vector>
#include<random>
#include<ostream>
template<typename T>
class BasicMartix
{
public:
	//行和列
	BasicMartix();
	BasicMartix(int row, int col);
	BasicMartix(std::vector<std::vector<T> >mat);

	~BasicMartix();

	template<typename _T>
	friend BasicMartix<_T> operator+(const BasicMartix<_T>& a, const BasicMartix<_T>& b)
	{
		if (a.mCols == b.mCols && a.mRows == b.mRows)
		{
			BasicMartix<_T> out(a.mRows, a.mCols);
			for (int i = 0; i < a.mRows; i++)
			{
				for (int j = 0; j < a.mCols; j++)
				{
					out.mMat[i][j] = a.mMat[i][j] + b.mMat[i][j];
				}
			}
			return out;
		}
		else
		{
			throw("两个矩阵不是同行矩阵");
		}
	}

	template<typename _T>
	friend BasicMartix<_T> operator-(const BasicMartix<_T>& a, const BasicMartix<_T>& b)
	{
		if (a.mCols == b.mCols && a.mRows == b.mRows)
		{
			BasicMartix<_T> out(a.mRows, a.mCols);
			for (int i = 0; i < a.mRows; i++)
			{
				for (int j = 0; j < a.mCols; j++)
				{
					out.mMat[i][j] = a.mMat[i][j] - b.mMat[i][j];
				}
			}
			return out;
		}
		else
		{
			throw("两个矩阵不是同行矩阵");
		}
	}

	template<typename _T>
	friend BasicMartix<_T> operator*(const BasicMartix<_T>& a, const BasicMartix<_T>& b)
	{
		if (a.mCols == b.mRows)
		{
			BasicMartix<_T> out(a.mRows, b.mCols);
			for (int i = 0; i < a.mRows; i++)
			{
				for (int j = 0; j < b.mCols; j++)
				{
					for (int k = 0; k < b.mRows; k++)
					{
						out.mMat[i][j] += a.mMat[i][k] * b.mMat[k][j];
					}
				}
			}
			return out;
		}
		else
		{
			throw("两个矩阵无法相乘");
		}
	}

	template<typename _T>
	friend BasicMartix<_T> operator*(const BasicMartix<_T>& a, long double b)
	{
		BasicMartix<_T> out(a.mRows, a.mCols);
		for (int i = 0; i < a.mRows; i++)
		{
			for (int j = 0; j < a.mCols; j++)
			{
				out.mMat[i][j] = a.mMat[i][j] * b;
			}
		}
		return out;
	}
	
	template<typename _T>
	friend BasicMartix<_T> operator*(long double b ,const BasicMartix<_T>& a)
	{
		return a* b;
	}

	template<typename _T>
	friend BasicMartix<_T> operator/(const BasicMartix<_T>& a, long double b)
	{
		BasicMartix<_T> out(a.mRows, a.mCols);
		for (int i = 0; i < a.mRows; i++)
		{
			for (int j = 0; j < a.mCols; j++)
			{
				out.mMat[i][j] = a.mMat[i][j] / b;
			}
		}
		return out;
	}

	BasicMartix<T> operator*=(const BasicMartix<T>&a);
	BasicMartix<T> operator+=(const BasicMartix<T>&a);
	BasicMartix<T> operator-=(const BasicMartix<T>&a);
	BasicMartix<T> operator*=(long double a);
	BasicMartix<T> operator/=(long double a);
	
	const int GetRows() const{ return mRows; }
	const int GetCols() const{ return mCols; }

	auto& GetData() { return mMat; }

	auto& At(int row, int col);
	void SetSize(int row, int col);

	//所有元素归零
	void Clear();

	template<typename _T>
	friend std::ostream& operator << (std::ostream& out, const BasicMartix<_T>& mat)
	{
		for (int i = 0; i < mat.mRows; i++)
		{
			for (int j = 0; j < mat.mCols; j++)
			{
				out << mat.mMat[i][j] << " ";
			}
			out << std::endl;
		}
		return out;
	}
private:
	std::vector<std::vector<T> >mMat;
	int mRows, mCols;
};

template<typename T>
inline BasicMartix<T>::BasicMartix():
	mCols(0),
	mRows(0)
{
}

template<typename T>
inline BasicMartix<T>::BasicMartix(int row, int col):
	mRows(row),
	mCols(col)
{
	mMat.resize(row);
	for (int i = 0; i < row; i++)
	{
		mMat[i].resize(col);
	}
}

template<typename T>
inline BasicMartix<T>::BasicMartix(std::vector<std::vector<T>> mat)
{
	mRows = mat.size();
	mCols = mat[0].size();

	mMat = mat;
}

template<typename T>
inline BasicMartix<T>::~BasicMartix()
{

}

template<typename T>
inline BasicMartix<T> BasicMartix<T>::operator*=(const BasicMartix<T>& a)
{
	*this = *this * a;
	return *this;
}

template<typename T>
inline BasicMartix<T> BasicMartix<T>::operator+=(const BasicMartix<T>& a)
{
	*this = *this + a;
	return *this;
}

template<typename T>
inline BasicMartix<T> BasicMartix<T>::operator-=(const BasicMartix<T>& a)
{
	*this = *this - a;
	return *this;
}

template<typename T>
inline BasicMartix<T> BasicMartix<T>::operator*=(long double a)
{
	*this = *this * a;
	return *this;
}

template<typename T>
inline BasicMartix<T> BasicMartix<T>::operator/= (long double a)
{
	*this = *this / a;
	return *this;
}

template<typename T>
inline auto& BasicMartix<T>::At(int row, int col)
{
	if (row >= 0 && col >= 0 && row < mRows && col < mCols)
	{
		auto iter = mMat.begin() + row;
		auto out = iter->begin() + col;
		return *out;
	}
	else
	{
		throw("行和列是非法的");
	}
}

template<typename T>
inline void BasicMartix<T>::SetSize(int row, int col)
{
	mRows = row;
	mCols = col;
	mMat.resize(row);
	for (int i = 0; i < row; i++)
	{
		mMat[i].resize(col);
	}
}

template<typename T>
inline void BasicMartix<T>::Clear()
{
	auto i = mMat.begin();
	for (; i != mMat.end(); i++)
	{
		std::fill(i->begin(), i->end(), 0);
	}
}

typedef BasicMartix<long double> Martix;
typedef BasicMartix<int> IntMartix;

void RandomMat(Martix& mat, long double a, long double b);
