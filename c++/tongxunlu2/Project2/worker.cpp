#include "worker.h"

WorkerManage::WorkerManage()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	if (!ifs.is_open())
	{
		cout<<"文件不存在"<<endl;
		this->m_Num=0;
		this->m_Emp = NULL;
		this->FileisEmpty=true;
		ifs.close();
		return;
	}
	char ch;
	ifs>>ch;
	if(ifs.eof())
	{
		cout<<"文件为空"<<endl;
		this->m_Num=0;
		this->m_Emp = NULL;
		this->FileisEmpty=true;
		ifs.close();
		return;
	}
	int num=this->getEmpNum();
	cout<<"职工人数为："<<num<<endl;
	this->m_Num=num;
	this->FileisEmpty=false;
	this->m_Emp = new Worker *[this->m_Num];
	this->init_Emp();
	for(int i=0;i<this->m_Num;i++)
	{
		cout<<"职工编号："<<this->m_Emp[i]->m_id<<" "
			<<"职工姓名："<<this->m_Emp[i]->m_Name<<" "
			"职工岗位："<<this->m_Emp[i]->m_DeptId<<endl;
	}

}
void WorkerManage::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	int id;
	string name;
	int did;
	int index=0;
	while(ifs>>id&&ifs>>name&&ifs>>did)
	{
		Worker *worker = NULL;
		if(did==1)
		{
			worker = new Employee(id,name,did);
		}
		else if(did=2)
		{
			worker = new Manager(id,name,did);
		}
		else
		{
			worker = new Boss(id,name,did);
		}
		this->m_Emp[index]=worker;
		index++;
	}
	ifs.close();
}
void WorkerManage::show_Emp()
{
	if(this->FileisEmpty)
	{
		cout<<"文件不存在或者为空"<<endl;
	}
	else
	{
		for(int i=0;i<this->m_Num;i++)
		{
			this->m_Emp[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
void WorkerManage::del_Emp()
{
	if(this->FileisEmpty)
	{
		cout<<"文件不存在或者记录为空"<<endl;
	}
	else
	{
		cout<<"请输入想要删除的编号"<<endl;
		int id = 0;
		cin>>id;
		int index = this->isExist(id);
		if(index!=-1)
		{

			for(int i = index;i<this->m_Num;i++)
			{
				this->m_Emp[i]=this->m_Emp[i+1];

			}
			this->m_Num--;
			this->save();
			cout<<"删除成功"<<endl;
		}
		else
		{
			cout<<"删除失败，未找到该员工"<<endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManage::mod_Emp()
{
	if(this->FileisEmpty)
	{
		cout<<"文件不存在或者记录为空"<<endl;
	}
	else
	{
		cout<<"请输入想要修改的编号"<<endl;
		int id = 0;
		cin>>id;
		int index = this->isExist(id);
		if(index!=-1)
		{
			delete this->m_Emp[index];
			int newId=0;
			string newName="";
			int dSelect = 0;
			cout<<"查到："<<id<<"号职工，请输入新职工号"<<endl;
			cin>>newId;
			cout<<"请输入新职工姓名"<<endl;
			cin>>newName;
			cout<<"请输入新的职工岗位"<<endl;
			cout<<"1.普通员工"<<endl;
			cout<<"2.经理"<<endl;
			cout<<"3.老板"<<endl;
			cin>>dSelect;
			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId,newName,1);
				break;
			case 2:
				worker = new Manager(newId,newName,2);
				break;
			case 3:
				worker = new Boss(newId,newName,3);
				break;
			default:
				break;
			}
			this->m_Emp[index]=worker;
			this->save();
			cout<<"修改成功"<<endl;
		}
		else
		{
			cout<<"修改失败，未找到该员工"<<endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManage::find_Emp()
{
	if(this->FileisEmpty)
	{
		cout<<"文件不存在或者记录为空"<<endl;
	}
	else
	{
		cout<<"请输入想要查找的方式"<<endl;
		cout<<"1.按编号查找"<<endl;
		cout<<"2.按姓名查找"<<endl;
		int select = 0;
		cin>>select;
		if (select==1)
		{
			int id;
			cout<<"请输入你想要查找的id"<<endl;
			cin>>id;
			int index = this->isExist(id);
			if(index!=-1)
			{
				cout<<"查找成功！该职工信息如下："<<endl;
				this->m_Emp[index]->showInfo();
			}
			else
			{
				cout<<"查找失败，无此人"<<endl;
			}
		}
		else if(select==2)
		{
			string name;
			cout<<"请输入想要查找的姓名："<<endl;
			cin>>name;
			bool flag =false;
			for (int i=0;i<this->m_Num;i++)
			{
				if(this->m_Emp[i]->m_Name==name)
				{
					cout<<"查找成功"<<this->m_Emp[i]->m_id<<"号职工信息如下"<<endl;
					this->m_Emp[i]->showInfo();
					flag=true;
				}
			}
			if(flag==false)
			{
				cout<<"查找失败，无此人"<<endl;
			}
		}
		else
		{
			cout<<"输入选项有误！"<<endl;
		}

	}
	system("pause");
	system("cls");
}

void WorkerManage::sort_Emp()
{
	if(this->FileisEmpty)
	{
		cout<<"文件不存在或者记录为空"<<endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout<<"请选择排序的方式"<<endl;
		cout<<"1.id升序"<<endl;
		cout<<"2.id降序"<<endl;
		int select = 0;
		cin>>select;
		for (int i=0;i<this->m_Num;i++)
		{
			int MinOrMax  = i;
			for(int j=i+1;j<this->m_Num;j++)
			{
				if(select == 1)
				{
					if(this->m_Emp[MinOrMax]->m_id>this->m_Emp[j]->m_id)
					{
						MinOrMax = j;

					}
				}
				else
				{
					if(this->m_Emp[MinOrMax]->m_id<this->m_Emp[j]->m_id)
					{
						MinOrMax = j;

					}
				}
			}
			if (i!=MinOrMax)
			{
				Worker *temp = this->m_Emp[i];
				this->m_Emp[i] =  this->m_Emp[MinOrMax];
				this->m_Emp[MinOrMax] = temp;

			}

		}

		cout<<"排序成功，排序结果为："<<endl;
		this->save();
		this->show_Emp();


	}

}
int WorkerManage::isExist(int id)
{
	int index =-1;
	for(int i=0;i<this->m_Num;i++)
	{
		if(this->m_Emp[i]->m_id==id)
		{
			index=i;
			break;
		}
	}
	return index;
}
void WorkerManage::Show_Menu()
{
	cout<<"****************************"<<endl;
	cout<<"****    1.添加职工信息   ****"<<endl;
	cout<<"****    2.显示职工信息   ****"<<endl;
	cout<<"****    3.删除职工信息   ****"<<endl;
	cout<<"****    4.修改职工信息   ****"<<endl;
	cout<<"****    5.查找职工信息   ****"<<endl;
	cout<<"****    6.按照编号排序   ****"<<endl;
	cout<<"****    7.清空所有文档   ****"<<endl;
	cout<<"****    0.退出          ****"<<endl;
	cout<<"***************************"<<endl;
	cout<<endl;
}
void WorkerManage::Add_Emp()
{
	cout<<"请输入添加职工的数量："<<endl;
	int addNum=0;
	cin>>addNum;
	if(addNum>0)
	{
		int newSize = this->m_Num+addNum;
		Worker ** newSpace = new Worker*[newSize];
		if(this->m_Emp !=NULL)
		{
			for(int i=0;i<this->m_Num;i++)
			{
				newSpace[i] = this->m_Emp[i];
			}
		}
		for(int i=0;i<addNum;i++)
		{
			int id;
			string name;
			int dSelect;
			cout<<"请选择第"<<i+1<<"个新职工编号"<<endl;
			cin>>id;
			cout<<"请选择第"<<i+1<<"个新职工姓名"<<endl;
			cin>>name;
			cout<<"请选择第"<<i+1<<"个新职工的岗位"<<endl;
			cout<<"1.普通职工"<<endl;
			cout<<"2.经理"<<endl;
			cout<<"3.老板"<<endl;
			cin>>dSelect;
			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id,name,1);
				break;
			case 2:
				worker = new Manager(id,name,2);
				break;
			case 3:
				worker = new Boss(id,name,3);
				break;
			default:
				break;
			}
			newSpace[this->m_Num+i]=worker;

		}
		delete []this->m_Emp;
		this->m_Emp = newSpace;
		this->m_Num= newSize;
		this->FileisEmpty=false;
		cout<<"添加成功"<<addNum<<"名职工"<<endl;
		this->save();

	}


	else
	{
		cout<<"输入错误！"<<endl;
	}
	system("pause");
	system("cls");
}
int WorkerManage::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	int id;
	string name;
	int did;
	int num=0;
	while(ifs>>id&&ifs>>name&&ifs>>did)
	{
		num++;
	}
	return num;
}
void WorkerManage::save()
{
	ofstream ofs;
	ofs.open(FILENAME,ios::out);
	for(int i =0;i<this->m_Num;i++)
	{
		ofs<<this->m_Emp[i]->m_id<<" "
			<<this->m_Emp[i]->m_Name<<" "
			<<this->m_Emp[i]->m_DeptId<<endl;
	}
	ofs.close();
}

void WorkerManage::ExitSystem()
{
	cout<<"欢迎下次使用!"<<endl;
	system("pause");
	exit(0);
}
void WorkerManage::clean_Emp()
{
	cout<<"确认清空？"<<endl;
	cout<<"1.确认"<<endl;
	cout<<"2.取消"<<endl;
	int select =0;
	cin>>select;
	if(select==1)
	{
		ofstream ofs(FILENAME,ios::trunc);
		ofs.close();
		if (this->m_Emp!=NULL)
		{
			for(int i =0;i<this->m_Num;i++)
			{
				delete this->m_Emp[i];
				this->m_Emp[i]=NULL;
			}
			delete []this->m_Emp;
			this->m_Emp = NULL;
			this->m_Num=0;
			this->FileisEmpty=true;
		}
		cout<<"清空成功"<<endl;
	}
	system("pause");
	system("cls");
}
WorkerManage::~WorkerManage()
{
	if(this->m_Emp !=NULL)
	{
		for(int i =0;i<this->m_Num;i++)
		{
			delete this->m_Emp[i];
		}
		delete []this->m_Emp;
		this->m_Emp = NULL;
	}
}


Employee::Employee(int id,string name,int did)
{
	this->m_id=id;
	this->m_Name=name;
	this->m_DeptId=did;
}
void Employee::showInfo()
{
	cout<<"员工编号："<<this->m_id
		<<"\t员工姓名："<<this->m_Name
		<<"\t岗位："<<this->getName()
		<<"\t岗位职责:完成经理交代的任务"<<endl;

}
string Employee::getName()
{
	return string( "普通员工");
}


Manager::Manager(int id,string name,int did)
{
	this->m_id=id;
	this->m_Name=name;
	this->m_DeptId=did;
}
void Manager::showInfo()
{
	cout<<"员工编号："<<this->m_id
		<<"\t员工姓名："<<this->m_Name
		<<"\t岗位："<<this->getName()
		<<"\t岗位职责:完成老板交代的任务，并下达给员工"<<endl;

}
string Manager::getName()
{
	return string( "经理");
}


Boss::Boss(int id,string name,int did)
{
	this->m_id=id;
	this->m_Name=name;
	this->m_DeptId=did;
}
void Boss::showInfo()
{
	cout<<"员工编号："<<this->m_id
		<<"\t员工姓名："<<this->m_Name
		<<"\t岗位："<<this->getName()
		<<"\t岗位职责:管理所有事物"<<endl;

}
string Boss::getName()
{
	return string( "老板");
}
