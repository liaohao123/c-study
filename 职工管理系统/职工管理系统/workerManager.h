#pragma once  //��ֹͬһ��ͷ�ļ���������include�����
#include <iostream>
#include <string>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"//���ļ�·�� �궨��

class WorkerManager
{
public:

	WorkerManager();//���캯��   .h����������.cpp��ʵ�ֳ�ʼ��

	void Show_Menu();//չʾ�˵�

	void ExitSystem();//0���˳�ϵͳ

	int m_EmpNum;//��¼��ǰ ְ������  

	Worker** m_EmpArray;//ְ������ָ�� 

	void Add_Emp();//1�����ְ��

	void save();//�����ļ�����ְ����Ϣд���ļ���

	bool m_FileIsEmpty;//��־�ļ��Ƿ�Ϊ�գ����Ϊ�ղ��ٽ��к������ɾ���Ȳ�����ֻ���� true �� false

	int m_getEmpNum();//ͳ�� �ļ��е�����

	void init_Emp();//��ʼ��ְ�������ļ��е�ְ����Ϣ

	void Show_Emp();//2����ʾְ��

	void Del_Emp();//3��ɾ��ְ�������ձ��ɾ��ְ��

	int IsExist(int id);//ְ���Ƿ���ڣ����� ����ְ�����������е�λ�ã������ڷ���-1

	void Mod_Emp();//4���޸�ְ��

	void Find_Emp();//5������ְ��

	void Sort_Emp();//6������ְ��

	void Clean_File();//7������ļ�

	~WorkerManager();//��������
};