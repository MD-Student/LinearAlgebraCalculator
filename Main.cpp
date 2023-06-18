#include "Matrix.h"
#include "SquareMatrix.h"
#include "Determinant.h"
#include <iostream>
using namespace std;

//���Դ���
//int main() {
//	SquareMatrix mat(3);
//	SquareMatrix adj = mat.getAdjoint();
//	adj.printMatrix();
//	SquareMatrix inv = mat.test(adj);
//	inv.printMatrix();
//	return 0;
//}

//��ӡ�˵�
void printMenu(Matrix* ptr = nullptr) {
	system("cls");//����
	cout << "*************��ӭʹ�����Դ���������*******************" << endl;
	cout << endl;
	cout << "*************��ѡ����(-1Ϊ�˳�)*************" << endl;
	cout << endl;
	cout << " *****************����ʽ��******************" << endl;
	cout << endl;
	cout << "1.����ʽ��ֵ" << endl;
	cout << "2.����ʽת��Ϊ��������ʽ" << endl;
	cout << endl;
	cout << " *****************������******************" << endl;
	cout << endl;
	cout << "3.��������" << endl;
	cout << "4.������ת��" << endl;
	cout << "5.����˷�" << endl;
	cout << "6.�����������" << endl;
	cout << "7.�����������(��˹��Ԫ)" << endl;
	cout << endl;
	cout << " *****************������******************" << endl;
	cout << endl;
	cout << "8.������������" << endl;
	cout << "9.��������" << endl;
	cout << "10.������Ա任���ɾ���" << endl;
	cout << endl;
	cout << "******************************************" << endl;
}

//�˵�����
int main() {
	int item = -1;
	Matrix* savedMatrixPointer = nullptr;
	bool saveMatrix = false; //�Ƿ񱣴浱ǰ����
	do
	{
		printMenu();
		cout << "ѡ��";
		cin >> item;
		switch (item)
		{
		case 1:
		{
			system("cls");
			cout << "����ʽ��ֵ��" << endl;
			Determinant det = DeterminantCin();
			cout << "������ʽ��ֵΪ��" << det.calculate() << endl;
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			cout << "������ʽת��Ϊ��������ʽ��" << endl;
			Determinant det = DeterminantCin();
			cout << "������ʽ����������ʽΪ��" << endl;
			det.upperTriangle().printDet();
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			cout << "�������ȣ�" << endl;
			Matrix m1 = MatrixCin();
			cout << "�������Ϊ��" << m1.getRank() << endl;
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			cout << "������ת�ã�" << endl;
			Matrix m1 = MatrixCin();
			cout << "�þ����ת��Ϊ��" << endl;
			Matrix m2 = m1.transpose();
			m2.printMatrix();
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			cout << "�������һ������" << endl;
			Matrix m1 = MatrixCin();
			cout << "������ڶ�������" << endl;
			Matrix m2 = MatrixCin();
			cout << "������˻�Ϊ��" << endl;
			(m1 * m2).printMatrix();
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			cout << "���������㣺" << endl;
			int exponent = 0;
			Matrix mat = MatrixCin();
			cout << "��������ָ����";
			cin >> exponent;
			Matrix result = mat;
			for (int i = 1; i < exponent; i++)
			{
				result *= mat;
			}
			cout << "������Ϊ��" << endl;
			result.printMatrix();
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			cout << "�����������(��˹��Ԫ)" << endl;
			Matrix mat = MatrixCin();
			mat.getEchelonForm().printMatrix();
			system("pause");
			break;
		}
		case 8:
		{
			system("cls");
			cout << "������������" << endl;
			SquareMatrix mat = SquareMatrixCin();
			cout << "�÷���İ������Ϊ��" << endl;
			mat.getAdjoint().printMatrix();
			system("pause");
			break;
		}
		case 9:
		{
			system("cls");
			cout << "�������棺" << endl;
			SquareMatrix mat = SquareMatrixCin();
			SquareMatrix inv = mat.getInverse();
			cout << "�÷���������Ϊ��" << endl;
			inv.printMatrix();
			system("pause");
			break;
		}
		case 10:
		{
			system("cls");
			cout << "������Ա任���ɾ���" << endl;
			cout << "������ԭ����" << endl;
			SquareMatrix matA = SquareMatrixCin();
			cout << "������任�����" << endl;
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
