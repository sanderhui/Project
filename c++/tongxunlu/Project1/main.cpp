#include <iostream>
#include <string>
using namespace std;

#define MAX 1000
struct People
{
	string pName;
	bool gender;
	int age;
	int phone;
	string addr;
};

struct Books
{
	struct People peopleArray[MAX];
	int m_Size;
};


void showMenu()
{
	cout<<"***************************"<<endl;
	cout<<"****    1.添加联系人   ****"<<endl;
	cout<<"****    2.显示联系人   ****"<<endl;
	cout<<"****    3.删除联系人   ****"<<endl;
	cout<<"****    4.查找联系人   ****"<<endl;
	cout<<"****    5.修改联系人   ****"<<endl;
	cout<<"****    6.清空联系人   ****"<<endl;
	cout<<"****    0.退出         ****"<<endl;
	cout<<"***************************"<<endl;
}

void addPeople(Books * book)
{
	if (book->m_Size==MAX)
	{
		cout<<"通讯录已满，无法添加"<<endl;
		return ;
	}
	else
	{
		cout<<"输入姓名："<<endl;
		cin>>book->peopleArray[book->m_Size].pName;
		cout<<"输入性别(0为女，1为男)："<<endl;
		int gender;
		cin>>gender;
		book->peopleArray[book->m_Size].gender = gender==0?0:1;
		cout<<"输入年龄（0-100）："<<endl;

		cin>>book->peopleArray[book->m_Size].age;
		cout<<"输入电话："<<endl;
		cin>>book->peopleArray[book->m_Size].phone;
		cout<<"输入地址："<<endl;
		cin>>book->peopleArray[book->m_Size].addr;
		book->m_Size ++;
		cout<<"添加成功"<<endl;
		system("pause");
		system("cls");//清屏
	}
}

void show(Books * book)
{
	if (book->m_Size==0)
	{
		cout<<"通讯录为空"<<endl;
	}
	else
	{
		for (int i=0;i<book->m_Size;i++)
		{
			cout<<"姓名："<<book->peopleArray[i].pName<<"\t";
			cout<<"年龄："<<book->peopleArray[i].age<<"\t";
			cout<<"性别："<<book->peopleArray[i].gender<<"\t";
			cout<<"电话："<<book->peopleArray[i].phone<<"\t";
			cout<<"住址："<<book->peopleArray[i].addr<<endl;
		}
	}
	system("pause");
	system("cls");//清屏
}

int  isExist(Books * book,string name)
{
	if(book->m_Size==0)
	{
		cout<<"通讯录为空"<<endl;
		return -1;
	}
	else
	{
		for (int i=0;i<book->m_Size;i++)
		{
			if (book->peopleArray[i].pName==name)
			{
				return i;
			}
		}
		return -1;
	}
}

void delPeople(Books * book)
{
	cout<<"请输入您要删除的联系人名字："<<endl;
	string name;
	cin>>name;
	int ret = isExist(book,name);
	if (ret==-1)
	{
		cout<<"查无此人"<<endl;
		system("pause");
		system("cls");//清屏
	}
	else
	{
		cout<<"查到此人的信息"<<endl;
		cout<<"姓名："<<book->peopleArray[ret].pName<<"\t";
		cout<<"年龄："<<book->peopleArray[ret].age<<"\t";
		cout<<"性别："<<book->peopleArray[ret].gender<<"\t";
		cout<<"电话："<<book->peopleArray[ret].phone<<"\t";
		cout<<"住址："<<book->peopleArray[ret].addr<<endl;
		for (int i=ret;i<book->m_Size;i++)
		{
			book->peopleArray[i] = book->peopleArray[i+1];
		}
		book->m_Size--;
		cout<<"删除成功"<<endl;
		system("pause");
		system("cls");//清屏
	}
}


void findPeople(Books * book)
{
	cout<<"请输入您要查找的联系人名字："<<endl;
	string name;
	cin>>name;
	int ret = isExist(book,name);
	if (ret==-1)
	{
		cout<<"查无此人"<<endl;
		system("pause");
		system("cls");//清屏
	}
	else
	{
		cout<<"查到此人的信息"<<endl;
		cout<<"姓名："<<book->peopleArray[ret].pName<<"\t";
		cout<<"年龄："<<book->peopleArray[ret].age<<"\t";
		cout<<"性别："<<book->peopleArray[ret].gender<<"\t";
		cout<<"电话："<<book->peopleArray[ret].phone<<"\t";
		cout<<"住址："<<book->peopleArray[ret].addr<<endl;

		system("pause");
		system("cls");//清屏
	}
}
void verifyPeople(Books * book)
{
	cout<<"请输入您要修改的联系人名字："<<endl;
	string name;
	cin>>name;
	int ret = isExist(book,name);
	if (ret==-1)
	{
		cout<<"查无此人"<<endl;
		system("pause");
		system("cls");//清屏
	}
	else
	{
		cout<<"查到此人的信息"<<endl;
		cout<<"姓名："<<book->peopleArray[ret].pName<<"\t";
		cout<<"年龄："<<book->peopleArray[ret].age<<"\t";
		cout<<"性别："<<book->peopleArray[ret].gender<<"\t";
		cout<<"电话："<<book->peopleArray[ret].phone<<"\t";
		cout<<"住址："<<book->peopleArray[ret].addr<<endl;


		cout<<"输入新的姓名："<<endl;
		cin>>book->peopleArray[ret].pName;
		cout<<"输入新的性别(0为女，1为男)："<<endl;
		int gender;
		cin>>gender;
		book->peopleArray[ret].gender = gender==0?0:1;
		cout<<"输入新的年龄（0-100）："<<endl;

		cin>>book->peopleArray[ret].age;
		cout<<"输入新的电话："<<endl;
		cin>>book->peopleArray[ret].phone;
		cout<<"输入新的地址："<<endl;
		cin>>book->peopleArray[ret].addr;
		cout<<"修改成功"<<endl;
		system("pause");
		system("cls");//清屏
	}
}

void clearPeople(Books *book)
{
	book->m_Size = 0;
	cout<<"通讯录已清空"<<endl;
	system("pause");
	system("cls");//清屏
}
int main()
{
	Books book;
	book.m_Size=0;
	int select = 0;
	while(true)
	{
		showMenu();
		cin>>select;
		switch(select)
		{
		case 1:  addPeople(&book); //1.添加联系人
			break;
		case 2:  show(&book);//2.显示联系人
			break;
		case 3:  delPeople(& book);  //3.删除联系人
			break;
		case 4:  findPeople(&book);//  4.查找联系人
			break;
		case 5:   verifyPeople(&book);// 5.修改联系人
			break;
		case 6: clearPeople(&book); //6.清空联系人
			break;
		case 0:  //0.退出
			cout<<"欢迎下次使用!"<<endl;
			system("pause");
			return 0;
			break;
		default:
			cout<<"操作错误,请重新输入"<<endl;
			break;
		}
	}

	system("pause");
	return 0;
}
