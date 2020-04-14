#include <iostream>
#include "worker.h"
#include <string>
using namespace std;


int main()
{
	/*Worker *worker = new Employee(1,"asd",1);
	worker->showInfo();
	delete worker;*/

	/*Worker *worker = new Manager(2,"asaead",2);
	worker->showInfo();
	delete worker;*/

	/*Worker *worker = new Boss(3,"aadssdsadd",3);
	worker->showInfo();
	delete worker;*/

	WorkerManage wm;

	int select=0;
	while(true)
	{
		wm.Show_Menu();
		cout<<"请输入您的选择"<<endl;
		cin>>select;
		switch(select)
		{
		case 1: wm.Add_Emp() ; //1.添加
			break;
		case 2: wm.show_Emp() ;//2.显示
			break;
		case 3: wm.del_Emp() ;  //3.删除
			break;
		case 4: wm.mod_Emp() ;//  4.修改
			break;
		case 5:   wm.find_Emp();// 5.查找
			break;
		case 6:wm.sort_Emp() ; //6.排序
			break;
		case 7: wm.clean_Emp(); //7.清空
			break;
		case 0: wm.ExitSystem();  //0.退出
			break;
		default:
			cout<<"操作错误,请重新输入"<<endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}
