#include "workerManager.h"


// WorkerManager �Ĺ��캯�������ڶ�ȡ�ļ�
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//1���ļ�������
	if (!ifs.is_open())
	{
		//��ʼ������
		this->m_EmpNum = 0;//��ʼ����¼����
		this->m_EmpArray = NULL;//��ʼ������ָ��
		this->m_FileIsEmpty = true;//��ʼ���ļ���־�Ƿ�Ϊ��
		ifs.close();
		return; //ֱ�ӷ��� main ����
	}

	//2���ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;//�ȶ�һ���ַ�������������ַ���eof,˵���ļ��Ѿ�����ͷ
	if (ifs.eof())  //�ļ�������
	{
		//��ʼ������
		this->m_EmpNum = 0;//��ʼ����¼����
		this->m_EmpArray = NULL;//��ʼ������ָ��
		this->m_FileIsEmpty = true;//��ʼ���ļ���־�Ƿ�Ϊ��
		ifs.close();
		return; //ֱ�ӷ��� main ����
	}

	//3���ļ����ڣ����ݲ�Ϊ��
	int num = this->m_getEmpNum();//ͳ���ļ��е�ְ������
	this->m_EmpNum = num;  //���ļ��е��������������--��ǰְ������

	//����һ�� this->m_EmpNum ����С�Ŀռ䣬���ļ��е����� �����������
	this->m_EmpArray = new Worker * [this->m_EmpNum];// Worker * ����һ�� Worker **
	this->init_Emp();
}

//չʾ�˵�****************************************************************************
void WorkerManager::Show_Menu()
{
	cout << "******************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ��*********" << endl;
	cout << "************* 0.�˳�������� *************" << endl;
	cout << "************* 1.����ְ����Ϣ *************" << endl;
	cout << "************* 2.��ʾְ����Ϣ *************" << endl;
	cout << "************* 3.ɾ��ְ����Ϣ *************" << endl;
	cout << "************* 4.�޸�ְ����Ϣ *************" << endl;
	cout << "************* 5.����ְ����Ϣ *************" << endl;
	cout << "************* 6.���ձ������ *************" << endl;
	cout << "************* 7.��������ĵ� *************" << endl;
	cout << "******************************************" << endl;
	cout << endl;
}

//0���˳�ϵͳ*****************************************************************************
void WorkerManager::ExitSystem()
{
	//�˳�ϵͳ�ĳ�����·
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);//exit(0) ��ʾ���������˳�,exit��/exit(-1����ʾ�����쳣�˳���
}

//1�����ְ��**********************************************************************************
void WorkerManager::Add_Emp()
{
	cout << "���������ְ����������" << endl;
	int addNum = 0;
	cin >> addNum;//�û�Ҫ��ӵ�����
	if (addNum > 0)
	{
		//�������֮ǰ����Ҫ �����¿ռ�

		//�ȼ����¿ռ��С
		int newSize = this->m_EmpNum + addNum;

		//�ڶ������ٳ��¿ռ䣬�� newSpace ���ա����������ջ����������һ�ξ����ˣ�����Ҫ�����ڶ���
		Worker** newSpace = new Worker * [newSize];//��һ������Ѹ���ָ��Worker * ����ס���ڶ������� newSize ���ռ��С

		//��ԭ�ռ��µ����ݿ������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];//���һ��ʼְ��������Ϊ�գ��ȿ������¿ռ���
			}
		}

		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id;//ְ�����
			string name;
			int dSelect;//ְ����λ

			cout << "������� " << i + 1 << " ����ְ�����:  " << endl;
			cin >> id;
			cout << "������� " << i + 1 << " ����ְ������:  " << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ: " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;
			Worker* worker = NULL;//�����в�ͬ��ְ��������ָ�����óɿգ�����ָ��ͬ��ְ��
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
			//��������ְ����Ϣ�����浽�¿ռ���
			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ�пռ�  -------   ԭ�пռ��е���Ϣǰ���Ѿ�������newSpace�У����Ծ����ͷžɿռ�
		delete[] this->m_EmpArray;
		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;
		//���� �µ�ְ������
		this->m_EmpNum = newSize;
		//���� ְ����Ϊ�ձ�־ ----  һ�����ְ���󣬱�־�Ͳ�Ϊ��
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ���� " << addNum << " ����ְ��" << endl;

		//���ñ����ļ�����,��ְ����Ϣ���浽�ļ� empFile.txt ��
		this->save();
	}
	else
	{
		cout << "��������" << endl;
	}

	system("pause");
	system("cls");
}

//�����ļ�  ��ְ����Ϣд���ļ���**************************************************************
void WorkerManager::save()//�����ְ���ɹ��� ���ñ��棬д���ļ���
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//��ÿ���˵���Ϣд���ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << "  "
			<< this->m_EmpArray[i]->m_Name << "  "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}


//ͳ���ļ��е�����*************************************************************************
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
		//ͳ������  ��ȡ��������Ϣ֮�� num++
		num++;
	}
	return num;
}

//��ʼ��Ա�� ,Ҳ���Ƕ��ļ��е�ְ����Ϣ *****************************************************
void WorkerManager::init_Emp()  //���ܣ������������ʱ������ǰ�������ȿ�����������
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
		//���ݴ��ļ��ж�ȡ���� ��ͬ�Ĳ���Id �� ��������ͬ�Ķ���
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

		//��ȡ�����ݴ����������
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}


//2����ʾְ��***************************************************************************
void WorkerManager::Show_Emp()
{

	if (this->m_FileIsEmpty)//���Ǻ���Ĺ���ʵ�� ��Ҫ�Ƚ��еĹ���
	{
		cout << "�ļ������ڻ��ļ�Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//���ö�̬���ýӿڣ���ʾ���е�ְ����Ϣ
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

//3��ɾ��ְ�������ձ��ɾ��ְ��***********************************************************************
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "������Ҫɾ����ְ����ţ� " << endl;
		int id = 0;
		cin >> id;
		//IsExist(id) ����ְ�����������е�λ��
		int index = this->IsExist(id);//ע�⣡����Ҫ�ҵڶ����ˣ����������е��±�λ���� 1 �������� 2,��ʱ�� index=1

		if (index != -1)
		{
			//������ ����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}

			this->m_EmpNum--;//���������м�¼��Ա����

			//ͬ�����µ��ļ���
			this->save();

			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ����޴��ˣ�" << endl;
		}
	}

	system("pause");
	system("cls");
}

//ְ���Ƿ���ڣ����� ����ְ�����������е�λ�ã������ڷ��� -1  ****************************************
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;//i �ʹ���ְ���ı��
			break;//�ҵ�ְ���ı�ţ��Ͳ���Ѱ��
		}
	}
	return index; //�ҵ��� ���� i ��û�ҵ�(������) ���� -1
}

//4���޸�ְ��****************************************************************************************
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)//1.�ȼ�� �ļ��Ƿ����
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ����ţ� " << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);  //2.�ٲ�ְ�� ְ���Ƿ����
		if (ret != -1)//ְ�����ڣ������޸Ĳ����������µ� id, name, ��λ
		{
			//���ͷ�ԭ������������
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽��" << id << "��ְ�� " << "  ��������ְ����ţ� " << endl;
			cin >> newId;
			cout << "��������������" << endl;
			cin >> newName;

			cout << "��ѡ���ְ����λ: " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;
			Worker* worker = NULL;//�����в�ͬ��ְ��������ָ�����óɿգ�����ָ��ͬ��ְ��
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

			//�������� ��������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ���" << endl;

			//ͬ�����µ��ļ���
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}

	system("pause");
	system("cls");
}

//5������ְ��***********************************************************************************
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2����ְ����������" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//����Ų���
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				//�ҵ���ְ������ʾһ��
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}

		}
		else if (select == 2)
		{
			//����������
			string name;
			cout << "������Ҫ���ҵ�������" << endl;
			cin >> name;
			//���� �ж��Ƿ�鵽 �ı�־
			bool flag = false;   // bool ֻ���� true �� false��

			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;

					this->m_EmpArray[i]->showInfo();//��ʾ��Ϣ

					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}

	system("pause");
	system("cls");
}


//6������ְ��***********************************************************************************
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minORmax = i;//������Сֵ �� ���ֵ ���±�

			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//��������
				{
					if (this->m_EmpArray[minORmax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minORmax = j;//����Сֵ���±�� minOrmax���ø��±�������i��������
					}
				}
				else  //����
				{
					if (this->m_EmpArray[minORmax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minORmax = j;//�����ֵ���±�� minOrmax
					}
				}
			}

			//�ж�һ��ʼ�϶��� ��Сֵ�����ֵ�ǲ��Ǽ������Сֵ�����ֵ��������ǣ��������ݡ�
			if (i != minORmax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minORmax];
				this->m_EmpArray[minORmax] = temp;
			}
		}

		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save(); //�����Ľ�����浽�ļ���
		this->Show_Emp();//չʾ����ְ����Ϣ
	}
}


//7������ļ�*********************************************************************************
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//����ļ�  Ҫ���ļ������ ios::trunc
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);// ios::trunc ����ļ��Ѵ�������ɾ�����ļ�
		ofs.clear();

		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)//�������ְ������󣬴�ʱ�� this->m_EmpArray ָ������¿ռ䡣
	{
		//ɾ��������ÿ��ְ������
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		//���������ÿ�
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}