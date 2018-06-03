// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include "library.h"


int main()
{
	int index = 0;		/*选择序号,区分用户与管理员的身份*/

	printf("\n\n");
	printf("+------------------欢迎进入图书管理系统-------------------+\n");
	printf("|                                                         |\n");
	printf("|                        1.用户模式                       |\n");
	printf("|                        2.管理员模式                     |\n");
	printf("|                        3.退出系统                       |\n");
	printf("|                                                         |\n");
	printf("+---------------------------------------------------------+\n");

	printf("    输入序号进入对应功能 :\n");
	printf("->");
	scanf_s("%d", &index);

	switch (index) {
	case 1:
		system("cls");
		auth_password_u();			/*用户密码验证*/
		user_menu();				/*打印用户界面*/
		break;
	case 2:
		system("cls");
		auth_password_a();			/*管理员密码验证*/
		admin_menu();				/*打印管理员界面*/
		break;
	case 3:
		exit(0);
	}

	return 0;
}

	
/*用户界面函数user_menu：打印用户选择界面*/
void user_menu(void)
{
	int choice = 0;
	printf("+---------------------------------------------------------+\n");
	printf("|                        用户界面                         |\n");
	printf("+---------------------------------------------------------+\n");
	printf("|                                                         |\n");
	printf("|                        1.查看图书信息                   |\n");
	printf("|                        2.借阅书籍                       |\n");
	printf("|                        3.查看个人信息                   |\n");
	printf("|                        4.修改密码                       |\n");
	printf("|                        5.退出系统                       |\n");
	printf("|                                                         |\n");
	printf("+---------------------------------------------------------+\n\n");

	printf("    输入序号进入对应功能 :\n");
	printf("->");
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 1:
		system("cls");
		display_book_info();
		break;
	case 2:
		system("cls");
		borrow_book();
		break;
	case 3:
		system("cls");
		display_user_info();
		break;
	case 4:
		system("cls");
		modify_password();
		break;
	case 5:
		exit(0);
	}
}


/*-----查看图书信息选择界面display：打印查看界面-----*/
void display_book_info(void)
{
	int choice = 0;

	printf("+---------------------------------------------------------+\n");
	printf("|                                                         |\n");
	printf("|                     1.查看所有图书信息                  |\n");
	printf("|                     2.查看已借阅图书信息                |\n");
	printf("|                     3.查看未借阅图书信息                |\n");
	printf("|                     4.返回上一界面                      |\n");
	printf("|                     5.退出系统                          |\n");
	printf("|                                                         |\n");
	printf("+---------------------------------------------------------+\n");

	printf("    输入序号进入对应功能 :\n");
	printf("->");
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 1:
		system("cls");
		display_all();
		break;
	case 2:
		system("cls");
		display_borrowed();
		break;
	case 3:
		system("cls");
		display_unborrowed();
		break;
	case 4:
		system("cls");
		user_menu();
		break;
	case 5:
		exit(0);
	}
}


/*----------管理员界面函数admin_menu：打印管理员界面-------------*/
void admin_menu(void)
{
	int choice = 0;
	printf("+---------------------------------------------------------+\n");
	printf("|                     管理员界面                          |\n");
	printf("+---------------------------------------------------------+\n");
	printf("|                                                         |\n");
	printf("|                     1.查找图书                          |\n");
	printf("|                     2.查看图书信息                      |\n");
	printf("|                     3.修改图书信息                      |\n");
	printf("|                     4.录入图书                          |\n");
	printf("|                     5.删除图书                          |\n");
	printf("|                     6.修改密码                          |\n");
	printf("|                     7.退出系统                          |\n");
	printf("|                                                         |\n");
	printf("+---------------------------------------------------------+\n\n");

	printf("    输入序号进入对应功能 :\n");
	printf("->");
	scanf_s("%d", &choice);
	switch (choice)
	{
	case 1:
		system("cls");
		search_book();
		break;
	case 2:
		system("cls");
		display_book_info();
		break;
	case 3:
		system("cls");
		change_book_info();
		break;
	case 4:
		system("cls");
		input();
		break;
	case 5:
		system("cls");
		delete_book();
		break;
	case 6:
		system("cls");
		modify_password();
		break;
	case 7:
		exit(0);
	}
}