#pragma once  //防止同一个头文件被包含（include）多次
#include <iostream>
#include <string>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"//把文件路径 宏定义

class WorkerManager
{
public:

	WorkerManager();//构造函数   .h中声明，在.cpp中实现初始化

	void Show_Menu();//展示菜单

	void ExitSystem();//0、退出系统

	int m_EmpNum;//记录当前 职工人数  

	Worker** m_EmpArray;//职工数组指针 

	void Add_Emp();//1、添加职工

	void save();//保存文件，将职工信息写进文件中

	bool m_FileIsEmpty;//标志文件是否为空，如果为空不再进行后面添加删除等操作，只返回 true 和 false

	int m_getEmpNum();//统计 文件中的人数

	void init_Emp();//初始化职工，读文件中的职工信息

	void Show_Emp();//2、显示职工

	void Del_Emp();//3、删除职工，按照编号删除职工

	int IsExist(int id);//职工是否存在，存在 返回职工所在数组中的位置，不存在返回-1

	void Mod_Emp();//4、修改职工

	void Find_Emp();//5、查找职工

	void Sort_Emp();//6、排序职工

	void Clean_File();//7、清空文件

	~WorkerManager();//析构函数
};