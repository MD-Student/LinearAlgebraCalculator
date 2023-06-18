#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include "MyVector.h"
#include <cmath>
#include <vector>
using namespace std;
#define eps 1e-6
//默认构造函数
Matrix::Matrix() {
	row = 0;
	column = 0;
	data = nullptr;
}
// 构造函数
Matrix::Matrix(int r, int c) {
	row = r;
	column = c;
	cout << "请在下方输入矩阵：" << endl;
	/*data的类型为double** 也就是指向double*的指针，
	* 也就可以理解成是存储double*的数组，因此data中存储的元素
	* 就是每一行数组的首地址。
	*/
	data = new double* [r]; //row
	for (int i = 0; i < r; i++)
	{
		data[i] = new double[c]; //column
		for (int j = 0; j < c; j++)
		{
			cin >> data[i][j];
		}
	}
}

// 不需要用户手动输入的构造函数（深拷贝）
Matrix::Matrix(int r, int c, double** matrixData) {
	row = r;
	column = c;
	data = new double* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new double[column];
		for (int j = 0; j < column; j++)
		{
			data[i][j] = matrixData[i][j];
		}
	}
}

//复制构造函数（深拷贝）
Matrix::Matrix(const Matrix& mat) {
	//默认的复制构造函数是浅拷贝，不会创建出新的data数组，因此需要重写复制构造函数
	row = mat.row;
	column = mat.column;
	data = new double* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new double[column];
		for (int j = 0; j < column; j++)
		{
			data[i][j] = mat.data[i][j];
		}
	}
}

//零矩阵构造函数
Matrix::Matrix(int r, int c, SpecialMatrix type)
{
	row = r;
	column = c;
	data = new double* [r];
	if (type == Matrix::NullMatrix)
	{
		//构造r*c零矩阵
		for (int i = 0; i < r; i++)
		{
			data[i] = new double[c];
			for (int j = 0; j < c; j++)
			{
				data[i][j] = 0;
			}
		}
	}
}

//析构函数
Matrix::~Matrix() {
	delete[] data;
	//data数组是用new动态创建的，进行显式释放
}

//赋值运算符重载
Matrix& Matrix::operator=(const Matrix& other) {
	//编译器默认创建的赋值运算符为浅层拷贝，会造成严重的内存冲突
	row = other.row;
	column = other.column;
	data = new double* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new double[column];
		for (int j = 0; j < column; j++)
		{
			data[i][j] = other.data[i][j];
		}
	}
	return *this;
}

// 加法重载
Matrix Matrix::operator+ (const Matrix& other) const {
	if (row == other.row && column == other.column)
	{
		double** nData = new double* [row];
		for (int i = 0; i < row; i++)
		{
			nData[i] = new double[column];
			for (int j = 0; j < column; j++)
			{
				nData[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return Matrix(row, column, nData);
		//todo 内训泄露
	}
	else {
		cerr << "矩阵不同型，无法进行加法运算！" << endl;
		// 返回前者
		return *this;
	}
}

// +=运算符重载
Matrix& Matrix::operator+= (const Matrix& other) {
	*this = *this + other;
	return *this;
}

// 乘法重载
Matrix Matrix::operator* (const Matrix& other) const {
	// this右乘一个矩阵
	// a*b b*c 得到一个a*c的矩阵
	if (column == other.row)
	{
		double** nData = new double* [row];
		// 新矩阵数据初始化
		for (int i = 0; i < row; i++)
		{
			nData[i] = new double[other.column];
		}
		// 计算新矩阵数据
		for (int i = 0; i < row; i++)
		{
			MyVector v1(column, data[i]);
			for (int j = 0; j < other.column; j++) {
				/*新矩阵第i行第j列的数据是左矩阵第i行与右矩阵第j列内积
				C++二维数组并不能直接取出来某一列数据，因此需要手动提取
				如果进行转置之后取第j行，复杂度为n平方，所以选择遍历一次
				第j列，复杂度为n*/
				double* rightColumn = new double[other.row];
				for (int i2 = 0; i2 < other.row; i2++)
				{
					rightColumn[i2] = other.data[i2][j];
				}
				//进行向量内积运算
				MyVector v2(other.row, rightColumn);
				nData[i][j] = v1 * v2;
			}
		}
		return Matrix(row, other.column, nData);
	}
	else {
		cerr << "矩阵无法进行乘法运算！" << endl;
		// 返回前者
		return *this;
	}
}

//*=运算符重载
Matrix& Matrix::operator*= (const Matrix& other) {
	*this = *this * other;
	return *this;
}

//减法运算符重载
Matrix Matrix::operator-(const Matrix& other) const
{
	if (row == other.row && column == other.column)
	{
		double** nData = new double* [row];
		for (int i = 0; i < row; i++)
		{
			nData[i] = new double[column];
			for (int j = 0; j < column; j++)
			{
				nData[i][j] = data[i][j] - other.data[i][j];
			}
		}
		return	Matrix(row, column, nData);
	}
	else {
		cerr << "矩阵不同型，无法相减！" << endl;
		return *this;
	}
}

//-=运算符重载
Matrix& Matrix::operator-=(const Matrix& other)
{
	*this = *this - other;
	return *this;
}

//右侧数乘运算符重载
Matrix Matrix::operator* (const double& other) const {
	double** nData = new double* [row];
	for (int i = 0; i < row; i++)
	{
		nData[i] = new double[column];
		for (int j = 0; j < column; j++) {
			nData[i][j] = data[i][j] * other;
		}
	}
	return Matrix(row, column, nData);
}

//右侧数乘*=重载
Matrix& Matrix::operator*= (const double& other) {
	*this = *this * other;
	return *this;
}

//左侧数乘运算符重载(非成员函数)
Matrix operator* (const double k, const Matrix& mat) {
	//之所以使用友元函数，是因为友元函数能够直接访问类中的私有成员，避免了设置
	//多个接口的麻烦
	return (mat * k);
}

Matrix operator*= (const double k, Matrix& mat) {
	//上网查询资料得知，友元函数无法访问this指针，所以只能直接操作该实例对象
	for (int i = 0; i < mat.row; i++)
	{
		for (int j = 0; j < mat.column; j++) {
			mat.data[i][j] *= k;
		}
	}
	return mat;
}

//打印矩阵
void Matrix::printMatrix() {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++) {
			if (fabs(data[i][j]) < eps) {
				cout << setw(12) << 0;
			}
			else {
				cout << setw(12) << data[i][j];
			}			
		}
		cout << endl;
	}
}

// 矩阵转置
Matrix Matrix::transpose() {
	// 第i j个元素，就是转置之后第j i个元素

	//初始化新矩阵数据
	double** nData = new double* [column];
	for (int i = 0; i < column; i++)
	{
		nData[i] = new double[row];
	}
	//填入数据
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++) {
			nData[j][i] = data[i][j];
		}
	}
	//返回转置矩阵
	return Matrix(column, row, nData);
}

//对换变换
//行对换变换用内联函数实现，减小函数调用开销
Matrix& Matrix::rowInterchange(int r1, int r2) {
	//创建临时行
	// FIXME 内联函数老是报错。。。
	//对行的操作没有使用循环，因此可以用内联函数
	double* tmp = new double[column];
	tmp = data[r1];
	data[r1] = data[r2];
	data[r2] = tmp;
	//之所以在改变了原矩阵对象的情况下还返回一个矩阵指针
	//是为了方便这个函数调用当成右值
	return *this;
}

Matrix& Matrix::columnInterchange(int c1, int c2) {
	//创建临时列
	double tmp = 0;
	for (int i = 0; i < row; i++)
	{
		//遍历c1列的数据并存储到tmp中
		tmp = data[i][c1];
		//c1列的数据更新为c2列
		data[i][c1] = data[i][c2];
		//c2列存储之前的c1列数据
		data[i][c2] = tmp;
		//复杂度为O（n）
	}
	return *this;
}

//倍乘变换
Matrix& Matrix::rowMultiplyScalar(int r, double k) {
	//给第r行的每一个数都乘上k
	for (int i = 0; i < column; i++)
	{
		data[r][i] *= k;
	}
	return *this;
}
Matrix& Matrix::columnMultiplyScalar(int c, double k) {
	//给第c列的每一个数都乘上k
	for (int i = 0; i < row; i++)
	{
		data[i][c] *= k;
	}
	return *this;
}

//倍加变化
//r1倍乘k之后加到r2上
Matrix& Matrix::rowAddMultiplyScalar(int r1, double k, int r2) {
	//先将r1行倍乘k，再加到r2行上
	for (int i = 0; i < column; i++)
	{
		data[r2][i] += data[r1][i] * k;
	}
	return *this;
}
Matrix& Matrix::columnAddMultiplyScalar(int c1, double k, int c2) {
	//先将第c1列倍乘k，再加到c2列
	for (int i = 0; i < row; i++)
	{
		data[i][c2] += data[i][c1] * k;
	}
	return *this;
}

//高斯消元法计算阶梯型矩阵
Matrix Matrix::getEchelonForm() {
	//创建一个新的矩阵
	Matrix tmp = *this;
	//高斯消元法，进行row-1次循环即可得到阶梯型矩阵
	int rFlag = 0, cFlag = 0;//为了排除一列全为0的情况，设置处理区域左上角元素索引
	for (; rFlag < row - 1; cFlag++)
	{
		//首先找出第一列中的最大元素，并将其交换到首行
		//QUESTION 找出最大元素的原因是之后将下面行置0的操作都需要用这个数，选用最大的数得第一行，误差更小
		int biggestRow = rFlag;//假设操作区域的第一行(rFlag)为最大
		for (int i = rFlag + 1; i < row; i++)
		{

			if (fabs(tmp.data[i][cFlag]) > fabs(tmp.data[rFlag][cFlag]))
			{
				biggestRow = i;
			}
		}
		//将最大元素交换到首行
		tmp.rowInterchange(rFlag, biggestRow);
		if (tmp.data[rFlag][cFlag] == 0)
		{
			//如果全部为0，直接执行下一次操作，此时rFlag没有移动，只有cFlag+1
			continue;
		}
		//将首行首元素置为1
		tmp.rowMultiplyScalar(rFlag, 1 / tmp.data[rFlag][cFlag]);
		//将首列其他元素全部置为0
		for (int i = rFlag + 1; i < row; i++)
		{
			//此时rFlag行（首行）已经置为1
			tmp.rowAddMultiplyScalar(rFlag, -tmp.data[i][cFlag], i);
		}
		rFlag++;
	}
	return tmp;
}

//矩阵求秩
int Matrix::getRank() {
	//利用高斯消元法进行求秩
	bool endFlag = false;
	int freeVarible = 0;
	Matrix echelonForm = this->getEchelonForm();
	//统计阶梯型矩阵中的全零行，即自由变量个数
	for (int i = row - 1; i >= 0; i--)
	{
		//自下而上统计，减小循环次数
		for (int j = 0; j < column; j++)
		{
			if (!(fabs(echelonForm.data[i][j]) < eps))
			{
				endFlag = true;
				break;
			}
		}
		if (endFlag)
		{
			break;
		}
		else {
			freeVarible++;
		}
	}
	return row - freeVarible;
}

//返回data数组的地址
double** Matrix::getMatrixData() const
{
	return data;
}

void Matrix::setMatrixData(double** newDataAddress)
{
	delete[] data;
	data = newDataAddress;
}

//魔法输入(实现无需预知形状的输入)
Matrix MatrixCin() {
	vector<double> container;//临时存储输入
	int column = 0; //即每行元素的个数
	double tmp;
	//读入第一行数据
	cout << "请输入m*n矩阵：（最后一行输入e终止）" << endl;
	do {
		cin >> tmp;
		container.push_back(tmp);
		column++;
	} while (cin.get() != '\n');

	//列数已经确定，读入后续行
	string firstChar;
	while (1) {
		cin >> firstChar;
		if (firstChar == "e")
		{
			break;
		}
		else {
			//如果firstChat不为e，则读入一行
			container.push_back(atof(firstChar.data()));
			//此时，下一个读入应该是空格
			while (cin.get() != '\n') {
				cin >> tmp;
				container.push_back(tmp);
			}
		}
	}
	int row = container.size() / column;
	int cnt = 0;
	double** nData = new double* [row];
	for (int i = 0; i < row; i++)
	{
		nData[i] = new double[column];
		for (int j = 0; j < column; j++)
		{
			nData[i][j] = container.at(cnt);
			cnt++;
		}
	}
	return Matrix(row, column, nData);
}
