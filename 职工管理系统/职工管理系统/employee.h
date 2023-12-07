#pragma once  
#include <iostream>
#include <string>
using namespace std;
#include "worker.h" //子类 要包含 父类的头文件

//普通职工类，在头文件中只做 [声明]
class Employee :public Worker
{
public:

	//构造函数
	Employee(int id, string name, int dId);

	//显示个人信息
	virtual void showInfo();//子类重写父类中的虚函数，引发多态

	//获取岗位名称
	virtual string getDeptName();
};