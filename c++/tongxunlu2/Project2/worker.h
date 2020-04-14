#pragma once
#include <iostream>
#include <string>
#include <fstream>

#define FILENAME "emp.txt"
using namespace std;

class Worker
{
public:
	virtual void showInfo()=0;
	virtual string getName()=0;
	int m_id;
	string m_Name;
	int  m_DeptId;
};

class WorkerManage
{
public:
	WorkerManage();
	void Show_Menu(); //展示
	void ExitSystem();//退出
	void Add_Emp();
	void save();
	int getEmpNum();
	void init_Emp();
	void del_Emp();
	void sort_Emp();
	void mod_Emp();
	void find_Emp();
	void clean_Emp();
	int isExist(int id);
	int m_Num;
	void show_Emp();
	Worker * * m_Emp;
	bool FileisEmpty;
	~WorkerManage();
};




class Employee:public Worker
{
public:
	Employee(int id,string name,int did);
	virtual void showInfo();
	virtual string getName();
};
class Manager:public Worker
{
public:
	Manager(int id,string name,int did);
	virtual void showInfo();
	virtual string getName();
};
class Boss:public Worker
{
public:
	Boss(int id,string name,int did);
	virtual void showInfo();
	virtual string getName();
};
