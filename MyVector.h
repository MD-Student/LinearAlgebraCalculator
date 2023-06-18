#pragma once
//前向引用声明
class MyVector {
	//向量还是不要继承矩阵类了
private:
	int row;//分量个数
	double* data;//向量分量数组
public:
	//构造函数
	//向量是n行1列
	MyVector(int r, double* components);
	//向量内积乘法重载
	double operator* (const MyVector& other) const;
};