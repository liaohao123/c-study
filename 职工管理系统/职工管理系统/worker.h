#pragma once  
#include <iostream>
#include <string>
using namespace std;

//抽象职工类，Worker包含：普通员工，经理，老板
class Worker
{
public:

	//显示个人信息
	virtual void showInfo() = 0;

	//获取岗位名称
	virtual string getDeptName() = 0;

	int m_Id;//职工编号
	string m_Name;//职工姓名
	int m_DeptId;//部门编号: 1. 普通员工  2. 经理   3. 老板
};