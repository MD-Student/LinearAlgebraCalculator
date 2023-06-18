#include "Matrix.h"
#include "SquareMatrix.h"
#include "Determinant.h"
#include <iostream>
using namespace std;

//测试代码
//int main() {
//	SquareMatrix mat(3);
//	SquareMatrix adj = mat.getAdjoint();
//	adj.printMatrix();
//	SquareMatrix inv = mat.test(adj);
//	inv.printMatrix();
//	return 0;
//}

//打印菜单
void printMenu(Matrix* ptr = nullptr) {
	system("cls");//清屏
	cout << "*************欢迎使用线性代数计算器*******************" << endl;
	cout << endl;
	cout << "*************请选择功能(-1为退出)*************" << endl;
	cout << endl;
	cout << " *****************行列式类******************" << endl;
	cout << endl;
	cout << "1.行列式求值" << endl;
	cout << "2.行列式转换为上三角形式" << endl;
	cout << endl;
	cout << " *****************矩阵类******************" << endl;
	cout << endl;
	cout << "3.矩阵求秩" << endl;
	cout << "4.矩阵求转置" << endl;
	cout << "5.矩阵乘法" << endl;
	cout << "6.矩阵的幂运算" << endl;
	cout << "7.矩阵求阶梯型(高斯消元)" << endl;
	cout << endl;
	cout << " *****************方阵类******************" << endl;
	cout << endl;
	cout << "8.方阵求伴随矩阵" << endl;
	cout << "9.方阵求逆" << endl;
	cout << "10.求解线性变换过渡矩阵" << endl;
	cout << endl;
	cout << "******************************************" << endl;
}

//菜单程序
int main() {
	int item = -1;
	Matrix* savedMatrixPointer = nullptr;
	bool saveMatrix = false; //是否保存当前矩阵
	do
	{
		printMenu();
		cout << "选择：";
		cin >> item;
		switch (item)
		{
		case 1:
		{
			system("cls");
			cout << "行列式求值：" << endl;
			Determinant det = DeterminantCin();
			cout << "该行列式的值为：" << det.calculate() << endl;
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			cout << "将行列式转换为上三角形式：" << endl;
			Determinant det = DeterminantCin();
			cout << "该行列式的上三角形式为：" << endl;
			det.upperTriangle().printDet();
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			cout << "矩阵求秩：" << endl;
			Matrix m1 = MatrixCin();
			cout << "矩阵的秩为：" << m1.getRank() << endl;
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			cout << "矩阵求转置：" << endl;
			Matrix m1 = MatrixCin();
			cout << "该矩阵的转置为：" << endl;
			Matrix m2 = m1.transpose();
			m2.printMatrix();
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			cout << "请输入第一个矩阵" << endl;
			Matrix m1 = MatrixCin();
			cout << "请输入第二个矩阵" << endl;
			Matrix m2 = MatrixCin();
			cout << "两矩阵乘积为：" << endl;
			(m1 * m2).printMatrix();
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			cout << "矩阵幂运算：" << endl;
			int exponent = 0;
			Matrix mat = MatrixCin();
			cout << "请输入幂指数：";
			cin >> exponent;
			Matrix result = mat;
			for (int i = 1; i < exponent; i++)
			{
				result *= mat;
			}
			cout << "运算结果为：" << endl;
			result.printMatrix();
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			cout << "矩阵求阶梯型(高斯消元)" << endl;
			Matrix mat = MatrixCin();
			mat.getEchelonForm().printMatrix();
			system("pause");
			break;
		}
		case 8:
		{
			system("cls");
			cout << "方阵求伴随矩阵：" << endl;
			SquareMatrix mat = SquareMatrixCin();
			cout << "该方阵的伴随矩阵为：" << endl;
			mat.getAdjoint().printMatrix();
			system("pause");
			break;
		}
		case 9:
		{
			system("cls");
			cout << "方阵求逆：" << endl;
			SquareMatrix mat = SquareMatrixCin();
			SquareMatrix inv = mat.getInverse();
			cout << "该方阵的逆矩阵为：" << endl;
			inv.printMatrix();
			system("pause");
			break;
		}
		case 10:
		{
			system("cls");
			cout << "求解线性变换过渡矩阵：" << endl;
			cout << "请输入原矩阵：" << endl;
			SquareMatrix matA = SquareMatrixCin();
			cout << "请输入变换后矩阵：" << endl;
			SquareMatrix matB = SquareMatrixCin();
			SquareMatrix invA = matA.getInverse();
			SquareMatrix transMat = MultiplySMatrix(invA, matB);
			transMat.printMatrix();
			system("pause");
			break;
		}
		}
	} while (item != -1);
	return 0;
}
