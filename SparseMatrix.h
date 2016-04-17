#pragma once
#include<iostream>
#include<vector>
#include<assert.h>


using namespace std;

//三元组的定义
template<class T>
struct  Triple
{
public:
	Triple()
	{}
	Triple(const T& d,size_t row=0,size_t col=0)
		:_value(d)
		,_row(row)
		,_col(col)
	{}
public:
	T _value;
	size_t _row;
	size_t _col;
};


template<class T>
class SparseMatrix
{
public:
	//无参构造函数
	SparseMatrix()
	{}


	SparseMatrix(const T* a, size_t row, size_t col, const T& invalid)
		:_rowSize(row)
		, _colSize(col)
		,_invalid(invalid)
	{
		//行遍历
		for (size_t i = 0; i < row; i++)
		{
			//列遍历
			for (size_t j = 0; j < col; j++)
			{
				if (a[i*col + j] != invalid)
				{
					_a.push_back(Triple<T>(a[i*col + j], i, j));//不能通过数组创建，但是可以通过数组形式访问
				}
			}
		}
	}

	//打印稀疏矩阵
	void Display()
	{
		size_t index = 0;
		for (size_t i = 0; i < _rowSize; i++)
		{
			for (size_t j = 0; j < _colSize; j++)
			{
				if (index<_a.size()
					&&_a[index]._row == i
					&&_a[index]._col == j)
				{
					cout << _a[index]._value << " ";
					index++;
				}
				else
				{
					cout << _invalid << " ";
				}
			}
			cout << endl;
		}
	}

	//列转置
	SparseMatrix<T> Transport()
	{
		SparseMatrix<T> result;
		//行列size互换
		result._rowSize = _colSize;
		result._colSize = _rowSize;
		result._invalid = _invalid;
		
		//按照列扫描
		for (size_t j = 0; j < _colSize; j++)
		{
			//在三元组数组中找到相同列的元素
			for (size_t index = 0; index < _a.size(); index++)
			{
				if (_a[index]._col == j)
				{
					result._a.push_back(Triple<T>(_a[index]._value, _a[index]._col, _a[index]._row));//按照列优先的顺序存到压缩数组中
				}
			}
		}
		return result;
	}

	//快速转置
	SparseMatrix<T> FastTransport()
	{
		assert(_a.size() < 0);
		SparseMatrix<T> result;
		//行列size互换
		result._rowSize = _colSize;
		result._colSize = _rowSize;
		result._invalid = _invalid;

		//建立rowCounts和rowStart
		int* rowCounts = new int[_colSize];
		int* rowStart = new int[_colSize];
		memset(rowCounts, 0, sizeof(int)*_colSize);
		memset(rowStart, 0, sizeof(int)*_colSize);

		result._a.resize(_a.size());
		//result._a.reserve(_a.size());
		//初始化
		for (size_t i = 0; i < _colSize; i++)
		{
			rowCounts[_a[i]._col]++;
		}
		rowStart[0] = 0;
		for (size_t i = 1; i < _colSize; i++)
		{
			rowStart[i] = rowCounts[i - 1] + rowStart[i - 1];
		}

		//快速转置
		size_t index = 0;
		Triple<T> tmp;
		while (index < _a.size())
		{
			int row = _a[index]._col;//行数
			int rowIndex = rowStart[row];//当前行的起始位置

			//交换行和列
			tmp._value = _a[index]._value;
			tmp._row = _a[index]._col;
			tmp._col = _a[index]._row;

			result._a[rowIndex] = tmp;
			rowStart[row]++;
			index++;
		}
		delete[] rowCounts;
		delete[] rowStart;
		return result;

	}
private:
	vector<Triple<T>> _a;//三元组类型的顺序表
	size_t _rowSize;//行数
	size_t _colSize;//列数
	T _invalid;//非法值
};

