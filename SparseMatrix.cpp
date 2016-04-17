# SparseMatrix
稀疏矩阵的压缩
#include "SparseMatrix.h"

void TestSparseMatrix()
{
	int array[6][5] = 
	{ {1,0,3,0,5},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{2,0,4,0,6},
	{0,0,0,0,0},
	{0,0,0,0,0} };

	SparseMatrix<int> sp((int*)array, 6, 5, 0);
	sp.Display();
	cout << endl;
	sp.Transport().Display();
	cout << endl;
	sp.FastTransport().Display();
}
int main()
{
	TestSparseMatrix();
	getchar();
	return 0;
}
