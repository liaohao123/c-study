#pragma once  
#include <iostream>
#include <string>
using namespace std;

//����ְ���࣬Worker��������ͨԱ���������ϰ�
class Worker
{
public:

	//��ʾ������Ϣ
	virtual void showInfo() = 0;

	//��ȡ��λ����
	virtual string getDeptName() = 0;

	int m_Id;//ְ�����
	string m_Name;//ְ������
	int m_DeptId;//���ű��: 1. ��ͨԱ��  2. ����   3. �ϰ�
};