#include "workerManager.h"


// WorkerManager 的构造函数，用于读取文件
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//1、文件不存在
	if (!ifs.is_open())
	{
		//初始化属性
		this->m_EmpNum = 0;//初始化记录人数
		this->m_EmpArray = NULL;//初始化数组指针
		this->m_FileIsEmpty = true;//初始化文件标志是否为空
		ifs.close();
		return; //直接返回 main 函数
	}

	//2、文件存在，数据为空
	char ch;
	ifs >> ch;//先读一个字符，如果读到的字符是eof,说明文件已经读到头
	if (ifs.eof())  //文件结束符
	{
		//初始化属性
		this->m_EmpNum = 0;//初始化记录人数
		this->m_EmpArray = NULL;//初始化数组指针
		this->m_FileIsEmpty = true;//初始化文件标志是否为空
		ifs.close();
		return; //直接返回 main 函数
	}

	//3、文件存在，数据不为空
	int num = this->m_getEmpNum();//统计文件中的职工人数
	this->m_EmpNum = num;  //把文件中的人数传给数组的--当前职工人数

	//开辟一个 this->m_EmpNum 个大小的空间，将文件中的数据 存放在数组中
	this->m_EmpArray = new Worker * [this->m_EmpNum];// Worker * 返回一个 Worker **
	this->init_Emp();
}

//展示菜单****************************************************************************
void WorkerManager::Show_Menu()
{
	cout << "******************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！*********" << endl;
	cout << "************* 0.退出管理程序 *************" << endl;
	cout << "************* 1.增加职工信息 *************" << endl;
	cout << "************* 2.显示职工信息 *************" << endl;
	cout << "************* 3.删除职工信息 *************" << endl;
	cout << "************* 4.修改职工信息 *************" << endl;
	cout << "************* 5.查找职工信息 *************" << endl;
	cout << "************* 6.按照编号排序 *************" << endl;
	cout << "************* 7.清空所有文档 *************" << endl;
	cout << "******************************************" << endl;
	cout << endl;
}

//0、退出系统*****************************************************************************
void WorkerManager::ExitSystem()
{
	//退出系统的常用套路
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);//exit(0) 表示程序正常退出,exit⑴/exit(-1）表示程序异常退出。
}

//1、添加职工**********************************************************************************
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工的数量：" << endl;
	int addNum = 0;
	cin >> addNum;//用户要添加的人数
	if (addNum > 0)
	{
		//添加新人之前首先要 开辟新空间

		//先计算新空间大小
		int newSize = this->m_EmpNum + addNum;

		//在堆区开辟出新空间，用 newSpace 接收。如果开辟在栈区，数组用一次就完了，所以要开辟在堆区
		Worker** newSpace = new Worker * [newSize];//用一个数组把父类指针Worker * 保存住，在堆区开辟 newSize 个空间大小

		//将原空间下的内容拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];//如果一开始职工人数不为空，先拷贝到新空间中
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//职工编号
			string name;
			int dSelect;//职工岗位

			cout << "请输入第 " << i + 1 << " 个新职工编号:  " << endl;
			cin >> id;
			cout << "请输入第 " << i + 1 << " 个新职工姓名:  " << endl;
			cin >> name;
			cout << "请选择该职工岗位: " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;//由于有不同的职工，所以指针设置成空，用来指向不同的职工
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}
			//将创建的职工信息，保存到新空间中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有空间  -------   原有空间中的信息前面已经拷贝到newSpace中，所以尽管释放旧空间
		delete[] this->m_EmpArray;
		//更改新空间的指向
		this->m_EmpArray = newSpace;
		//更新 新的职工人数
		this->m_EmpNum = newSize;
		//更新 职工不为空标志 ----  一旦添加职工后，标志就不为空
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加 " << addNum << " 名新职工" << endl;

		//调用保存文件函数,将职工信息保存到文件 empFile.txt 中
		this->save();
	}
	else
	{
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");
}

//保存文件  把职工信息写进文件中**************************************************************
void WorkerManager::save()//在添加职工成功后 调用保存，写进文件中
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//将每个人的信息写进文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << "  "
			<< this->m_EmpArray[i]->m_Name << "  "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}


//统计文件中的人数*************************************************************************
int WorkerManager::m_getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数  读取到三个信息之后 num++
		num++;
	}
	return num;
}

//初始化员工 ,也就是读文件中的职工信息 *****************************************************
void WorkerManager::init_Emp()  //功能：在添加新数据时，将以前的数据先拷贝到数组中
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		//根据从文件中读取到的 不同的部门Id ， 来创建不同的对象，
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else
		{
			worker = new Boss(id, name, dId);
		}

		//读取的数据存放在数组中
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}


//2、显示职工***************************************************************************
void WorkerManager::Show_Emp()
{

	if (this->m_FileIsEmpty)//这是后面的功能实现 都要先进行的工作
	{
		cout << "文件不存在或文件为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用接口，显示已有的职工信息
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

//3、删除职工，按照编号删除职工***********************************************************************
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入要删除的职工编号： " << endl;
		int id = 0;
		cin >> id;
		//IsExist(id) 返回职工所在数组中的位置
		int index = this->IsExist(id);//注意！假如要找第二个人，他在数组中的下标位置是 1 ，而不是 2,此时的 index=1

		if (index != -1)
		{
			//本质是 数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}

			this->m_EmpNum--;//更新数组中记录人员个数

			//同步更新到文件中
			this->save();

			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，查无此人！" << endl;
		}
	}

	system("pause");
	system("cls");
}

//职工是否存在，存在 返回职工所在数组中的位置，不存在返回 -1  ****************************************
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;//i 就代表职工的编号
			break;//找到职工的编号，就不再寻找
		}
	}
	return index; //找到了 返回 i ，没找到(不存在) 返回 -1
}

//4、修改职工****************************************************************************************
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)//1.先检查 文件是否存在
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入要修改的职工编号： " << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);  //2.再查职工 职工是否存在
		if (ret != -1)//职工存在，进行修改操作，赋予新的 id, name, 岗位
		{
			//先释放原来堆区的数据
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到：" << id << "号职工 " << "  请输入新职工编号： " << endl;
			cin >> newId;
			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请选择该职工岗位: " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;//由于有不同的职工，所以指针设置成空，用来指向不同的职工
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;

			}

			//更新数据 到数组中
			this->m_EmpArray[ret] = worker;

			cout << "修改成功！" << endl;

			//同步更新到文件中
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人！" << endl;
		}
	}

	system("pause");
	system("cls");
}

//5、查找职工***********************************************************************************
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按职工姓名查找" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//按编号查找
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				//找到该职工，显示一下
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人！" << endl;
			}

		}
		else if (select == 2)
		{
			//按姓名查找
			string name;
			cout << "请输入要查找的姓名：" << endl;
			cin >> name;
			//加入 判断是否查到 的标志
			bool flag = false;   // bool 只返回 true 和 false！

			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功！该职工信息如下：" << endl;

					this->m_EmpArray[i]->showInfo();//显示信息

					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else
		{
			cout << "输入选项有误！" << endl;
		}
	}

	system("pause");
	system("cls");
}


//6、排序职工***********************************************************************************
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minORmax = i;//声明最小值 或 最大值 的下标

			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序排序
				{
					if (this->m_EmpArray[minORmax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minORmax = j;//把最小值的下标给 minOrmax，让该下标的数与第i个数互换
					}
				}
				else  //降序
				{
					if (this->m_EmpArray[minORmax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minORmax = j;//把最大值的下标给 minOrmax
					}
				}
			}

			//判断一开始认定的 最小值或最大值是不是计算的最小值或最大值，如果不是，交换数据。
			if (i != minORmax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minORmax];
				this->m_EmpArray[minORmax] = temp;
			}
		}

		cout << "排序成功！排序后的结果为：" << endl;
		this->save(); //排序后的结果保存到文件中
		this->Show_Emp();//展示所有职工信息
	}
}


//7、清空文件*********************************************************************************
void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//清空文件  要在文件中清除 ios::trunc
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);// ios::trunc 如果文件已存在则先删除该文件
		ofs.clear();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)//经过添加职工步骤后，此时的 this->m_EmpArray 指向的是新空间。
	{
		//删除堆区的每个职工对象
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		//最后把数组置空
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}