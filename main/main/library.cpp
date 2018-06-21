#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include "library.h"
#define FILENAME "Book_info.txt"


/*-----------load函数：加载文件（返回值为链表指针）（尾插法创建链表）----------*/
BOOK_LIST load(void)
{
	BOOK_LIST head, new_node, tail;		/*头指针、新节点指针、尾指针*/
	
	FILE *fp;			

	head = NULL;
	tail = NULL;

	if (fopen_s(&fp, FILENAME, "rb") == 1)		//判断文件是否打开
	{
		printf("Can not open the file %s\n", FILENAME);
		return head;
	}
	else
	{
		while (!feof(fp))		//feof()：用来判断指针是否已经到达文件尾部
		{
			new_node = (BOOK_LIST)malloc(sizeof(BOOK));
			if (!new_node) {
				printf("Out of memory.\n");
				exit(1);
			}

			//读取图书信息
			fscanf_s(fp, "%d%s%s%s%s%d", &new_node->num, new_node->name, 40, new_node->author, 20, new_node->publish, 40, new_node->publish_date, 20, &new_node->status);
			new_node->next = NULL;

			//创建链表（尾插法）
			if (head == NULL)
				head = new_node;
			else
				tail->next = new_node;

			tail = new_node;

			printf("%d%s%s%s%s%d\n", new_node->num, new_node->name, new_node->author, new_node->publish, new_node->publish_date, new_node->status);
			//此条语句为了测试链表是否创建成功，会打印在屏幕上，最后要删掉

		}
		fclose(fp);
		return(head);
	}
}

/*-------------data_to_file()：将链表数据写入文件（共用）---------------*/
BOOK_LIST data_to_file(BOOK_LIST head)
{
	FILE *fp;
	BOOK_LIST p;

	if (fopen_s(&fp, FILENAME, "w") == 1)
	{
		printf("Can not open the file %s\n", FILENAME);
		return head;
	}
	else
	{
		//fprintf(fp, "书号\t书名\t\t\t作者\t\t出版社\t\t\t出版时间\t\t\t借阅状态\n");
		for (p = head; p != NULL; p = p->next)
		{
			fprintf(fp, "\n%-10d", p->num);
			fprintf(fp, "%-25s", p->name);
			fprintf(fp, "%-20s", p->author);
			fprintf(fp, "%-20s", p->publish);
			fprintf(fp, "%-15s", p->publish_date);
			fprintf(fp, "%5d", p->status);
		}
	}
	fclose(fp);
	return head;
}




/*-----查看个人信息display_user_info----*/
void display_user_info(void) {

}

/*-----修改用户密码modify_password--------*/
void modify_password(void)
{

}

/*函数auth_password_a：管理员密码验证*/
void auth_password_a(void)
{

}

/*函数auth_password_u：用户密码验证*/
void auth_password_u(void)         //验证成功返回1，失败返回0
{

}

/*函数input：录入图书信息*/
BOOK_LIST input(BOOK_LIST head)
{
	BOOK_LIST temp, p, marker;		/*temp:新节点指针; 两个标记节点指针*/
	BOOK_LIST q;		/*遍历，查重*/
	marker = NULL;

	temp = (BOOK_LIST)malloc(sizeof(BOOK));
	if (!temp){
		printf("Out of memory.\n");
		exit(1);
	}

	//录入数据
	printf("\n   -----------------图书信息录入-----------------");
	printf("\n\n\t书号：");
	scanf_s("%d", &temp->num);

	for (q = head; q != NULL; q = q->next)
	{
		if (temp->num == q->num)
		{
			printf("\n  该编号已存在!");
			Sleep(500);
			system("cls");
			return head;
		}
	}
	getchar();
	printf("\n\t书名：");
	gets_s(temp->name);
	fflush(stdin);
	printf("\n\t作者：");
	gets_s(temp->author);
	fflush(stdin);
	printf("\n\t出版社：");
	gets_s(temp->publish);
	fflush(stdin);
	printf("\n\t出版时间(1970-01-01)：");
	gets_s(temp->publish_date);
	fflush(stdin);
	temp->status = 0;
	
	//将新节点插入链表（按书号顺序）
	p = head;
	while (p != NULL && p->num < temp->num)
	{
		marker = p;
		p = p->next;
	}

	if (p == head)
	{
		temp->next = head;
		head = temp;
	}
	else
	{
		temp->next = marker->next;
		marker->next = temp;
	}
	printf("\n 是否保存？(Y/N)");


	//将链表数据写入文件
	if (getchar() == 'Y')
	{
		data_to_file(head);
		printf("\n\n\t保存成功。\n");
	}
	Sleep(500);
	system("cls");
	return head;
}



/*函数search_book：进入后输入书名或书号，进行查找*/
void search_book(BOOK_LIST head)
{
	int choice;
	
	printf("\n\n");
	printf("       + -------------查询图书------------+\n");
	printf("       |                                  |\n");
	printf("       |           1、按书号查询          |\n");
	printf("       |           2、按书名查询          |\n");
	printf("       |           3、返回                |\n");
	printf("       |                                  |\n");
	printf("       +----------------------------------+\n");
	printf("\n\t请选择查询的方式：");
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 1:
		search_by_num(head);
		break;
	case 2:
		search_by_name(head);
		break;
	case 3:
		system("cls");
		return;
	}
}

/*----函数search_by_num：按书号查询----*/
BOOK_LIST search_by_num(BOOK_LIST head)
{
	BOOK_LIST p;
	int flag = 0;
	int temp_num;				/*要查询的书籍编号*/

	printf("\n  请输入要查询书籍的编号：");
	scanf_s("%d", &temp_num);

	for (p = head; p != NULL; p = p->next)
	{
		if (p->num == temp_num)
		{
			printf("\n\n");
			printf("             图书信息\n");
			printf("-------------------------------\n");
			printf("    编号：%d\n", p->num);
			printf("    书名：%s\n", p->name);
			printf("    作者：%s\n", p->author);
			printf("    出版社：%s\n", p->publish);
			printf("    出版时间：%s\n", p->publish_date);
			printf("-------------------------------\n");
			flag = 1;		//表明已经找到图书（编号唯一，故可停止查询）
		}
	}
	if (flag == 0)
	{
		printf("查无此书！");
		Sleep(500);
		system("cls");
		return head;
	}
	printf("\n  输入Q返回：");
	getchar();
	if (getchar() == 'Q')
	{
		system("cls");
		return head;
	}
}

/*----函数search_by_num：按书名查询----*/
void search_by_name(BOOK_LIST head)
{

	BOOK_LIST p;
	int flag = 0;
	char book_name[40];			/*要查询的书籍名称*/
	BOOK_LIST book_same_name[10] = { 0 };	//链表指针数组

	int i = 0, j;

	printf("\n  请输入要查询图书的名称：");
	getchar();
	gets_s(book_name);

	for (p = head; p != NULL; p = p->next)
	{
		if (strcmp(p->name, book_name) == 0)
		{
			book_same_name[i] = p;
			i++;
		}			//将同名图书放在一个数组里
	}
	if (i == 0)
	{
		printf("\n  查无此书！");
		Sleep(500);
		system("cls");
		return;
	}
	else
	{
		printf("\n\n\n一共搜索到%d本图书\n", i);
		printf("------------------------------------------------\n");
		printf("%-10s%-25s%-20s%-20s%-20s\n", "书号", "书名", "作者", "出版社", "出版时间");
		for (j = 0; j < i; j++)
		{
			printf("%-10d%-25s%-20s%-20s%-20s\n", book_same_name[j]->num, book_same_name[j]->name, book_same_name[j]->author, book_same_name[j]->publish, book_same_name[j]->publish_date);
		}
		printf("--------------------------------------------------\n");
	}
	printf("\n  输入Q返回：");
	getchar();
	if (getchar() == 'Q')
	{
		system("cls");
		return;
	}
}


/*函数display_all：查看所有图书信息*/
void display_all(BOOK_LIST head)
{
	BOOK_LIST p;
	printf("\n");
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf(" |%-10s%-25s%-20s%-20s%-20s|\n", "书号", "书名", "作者", "出版社", "出版时间");
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	for(p = head; p != NULL; p = p->next)
		printf(" |%-10d%-25s%-20s%-20s%-20s|\n", p->num, p->name, p->author, p->publish, p->publish_date);
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf("\n\n");
	printf("   输入Q返回：");
	
	fflush(stdin);
	getchar();
	if (getchar() == 'Q')
	{
		system("cls");
		display_book_info(head);
	}	
}

/*--------------------筛选图书------------------*/
/*函数display_unborrowed：查看所有未借阅书籍信息*/

void display_unborrowed(BOOK_LIST head)
{
	BOOK_LIST p;
	p = head;
	int flag = 0;

	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf(" |%-10s%-25s%-20s%-20s%-20s|\n", "书号", "书名", "作者", "出版社", "出版时间");
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	while (p != NULL) {
		if (p->status == 0)
		{
			printf(" |%-10d%-25s%-20s%-20s%-20s|\n", p->num, p->name, p->author, p->publish, p->publish_date);
			flag = 1;
		}
		p = p->next;
	}
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf("\n\n");
	printf("   输入Q返回：");

	fflush(stdin);
	getchar();
	if (getchar() == 'Q')
	{
		system("cls");
		display_book_info(head);
	}

	if (flag == 0)
		printf("所有图书均已借出！");
}


/*函数display_borrowed：查看所有已借阅图书信息*/
void display_borrowed(BOOK_LIST head)
{
	BOOK_LIST p;
	p = head;
	int flag = 1;

	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf(" |%-10s%-25s%-20s%-20s%-20s|\n", "书号", "书名", "作者", "出版社", "出版时间");
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	while (p != NULL) {
		if (p->status == 1) 
		{
			printf(" |%-10d%-25s%-20s%-20s%-20s|\n", p->num, p->name, p->author, p->publish, p->publish_date);
			flag = 0;
		}
		p = p->next;
	}
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf("\n\n");
	printf("   输入Q返回：");

	fflush(stdin);
	getchar();
	if (getchar() == 'Q')
	{
		system("cls");
		display_book_info(head);
	}
	if (flag == 1)
		printf("没有借出的图书！");
}

/*-------------------借阅图书-------------------*/
/*函数borrow_book：借阅图书*/
void borrow_book(BOOK_LIST head)
{
	BOOK_LIST p;
	int choice;
	int book_num;
	char book_name[40];
	BOOK_LIST book_same_name[10] = { 0 };	//链表指针数组

	int i = 0, j;
	int index;		//同名书籍序号

	printf("+------------------------------+\n");
	printf("|            借阅图书          |\n");
	printf("+------------------------------+\n");
	printf("|          1.按书号借阅        |\n");
	printf("|          2.按书名借阅        |\n");
	printf("|          3.返回              |\n");
	printf("|          4.退出              |\n");
	printf("+------------------------------+\n");
	printf("\n  --> ");
	scanf_s("%d", &choice);
	printf("\n");
	if (choice > 0 && choice <= 4)
	{
		switch (choice)
		{
		case 1:
			p = search_by_num(head);
			//printf("请输入要借阅书籍的编号：");
			//scanf_s("%d", &book_num);

			//for (p = head; p != NULL; p = p->next)
			//{
			//	if (p->num == book_num)
			//	{
			//		printf("\n\n----------------------------\n");
			//		printf("             图书信息\n");
			//		printf("----------------------------\n");
			//		printf("    编号：%d\n", p->num);
			//		printf("    书名：%s\n", p->name);
			//		printf("    作者：%s\n", p->author);
			//		printf("    出版社：%s\n", p->publish);
			//		printf("    出版时间：%s\n", p->publish_date);
			//		printf("-----------------------------\n");
			getchar();
			printf("\n是否借阅（Y/N）?");
			if (getchar() == 'Y')
			{
				p->status = 1;
				data_to_file(head);
				printf("借阅成功");
			}
				//else
				//{
				//	system("cls");
				//	borrow_book(head);
				//}
			break;
		case 2:
			printf("请输入要借阅的书籍名称：");
			gets_s(book_name);

			for (p = head; p != NULL; p = p->next)
			{
				if (strcmp(p->name, book_name) == 0)
				{
					book_same_name[i] = p;
					i++;
				}			//将同名图书放在一个数组里
			}
			if (i == 0)
			{
				printf("没有该图书。");
				system("cls");
				borrow_book(head);
			}
			else
			{
				printf("\n\n\n一共搜索到%d本图书\n", i);
				printf("------------------------------------------------\n");
				printf("%-10s%-25s%-20s%-20s%-20s%-20s\n", "书号", "书名", "作者", "出版社", "出版时间", "序号");
				for (j = 0; j < i; j++)
				{
					printf("%-10d%-25s%-20s%-20s%-20s%-20d\n", book_same_name[j]->num, book_same_name[j]->name, book_same_name[j]->author, book_same_name[j]->publish, book_same_name[j]->publish_date, j + 1);
				}
				printf("--------------------------------------------------\n");

				printf("请选择要借阅的书籍序号：\n");
				scanf_s("%d", &index);

				if (index > 0 && index <= i)
				{
					book_same_name[index - 1]->status = 1;
					data_to_file(head);
				}
				else
					printf("输入错误");
			}
			break;
		case 3:
			system("cls");
			user_menu(head);
			break;
		case 4:
			exit(0);

		}
	}
}

/*-------------------修改图书-------------------*/
/*函数change_book_info：修改图书信息*/
void change_book_info(BOOK_LIST head)
{
	BOOK_LIST p;
	int choice1, choice2;
	int flag = 0;

	printf("\n\n");
	printf("     +------------------------------+\n");
	printf("     |         修改图书信息         |\n");
	printf("     +------------------------------+\n");
	printf("     |         1.按书名查找         |\n");
	printf("     |         2.按书号查找         |\n");
	printf("     |         3.返回               |\n");
	printf("     |         4.退出               |\n");
	printf("     +------------------------------+");
	printf("\n\t-->");
	scanf_s("%d", &choice1);

	if (choice1 > 0 && choice1 <= 4)
	{
		switch (choice1) {
		case 1:
			system("cls");
			char temp_name[40];			/*要查询的书籍名称*/

			printf("\n\n       请输入要查询书籍的名称：");
			getchar();
			gets_s(temp_name);

			printf("\n  请选择要修改的内容\n");
			printf("            +-------------------------+\n");
			printf("            |          1.书名         |\n");
			printf("            |          2.作者         |\n");
			printf("            |          3.出版社       |\n");
			printf("            |          4.出版时间     |\n");
			printf("            +-------------------------+\n");
			printf("            |          5.返回         |\n");
			printf("            |          6.退出         |\n");
			printf("            +-------------------------+");

			printf("\n-->");
			scanf_s("%d", &choice2);

			for (p = head; p != NULL; p = p->next)
			{
				if (strcmp(p->name, temp_name) == 0)
				{
					flag = 1;
					switch (choice2)
					{
					case 1:
						printf("原信息为：%s\n\n", p->name);
						printf("修改为：");
						getchar();
						gets_s(p->name);
						data_to_file(head);
						printf("修改成功！");
						break;
					case 2:
						printf("原信息为：%s\n\n", p->author);
						printf("修改为：");
						getchar();
						gets_s(p->author);
						data_to_file(head);
						printf("修改成功！");
						break;
					case 3:
						printf("原信息为：%s\n\n", p->publish);
						printf("修改为：");
						getchar();
						gets_s(p->publish);
						data_to_file(head);
						printf("修改成功！");
						break;
					case 4:
						printf("原信息为：%s\n\n", p->publish_date);
						printf("修改为：");
						getchar();
						gets_s(p->publish_date);
						data_to_file(head);
						printf("修改成功！");
						break;
					case 5:
						change_book_info(head);
						break;
					case 6:
						exit(0);
					}
				}
			}
			if (flag == 0)
				printf("查无此书！");
			break;
		case 2:
			system("cls");
			int temp_num;				/*要查询的书籍编号*/

			printf("\n\n   请输入要查询书籍的编号：");
			scanf_s("%d", &temp_num);

			printf("\n  请选择要修改的内容\n");
			printf("            +-------------------------+\n");
			printf("            |          1.书名         |\n");
			printf("            |          2.作者         |\n");
			printf("            |          3.出版社       |\n");
			printf("            |          4.出版时间     |\n");
			printf("            +-------------------------+\n");
			printf("            |          5.返回         |\n");
			printf("            |          6.退出         |\n");
			printf("            +-------------------------+");

			printf("\n-->");
			scanf_s("%d", &choice2);

			for (p = head; p != NULL; p = p->next)
			{
				if (p->num == temp_num)
				{
					switch (choice2)
					{
					case 1:
						printf("原信息为：%s\n", p->name);
						printf("修改为：");
						getchar();
						gets_s(p->name);
						break;
					case 2:
						printf("原信息为：%s\n", p->author);
						printf("修改为：");
						getchar();
						gets_s(p->author);
						break;
					case 3:
						printf("原信息为：%s\n", p->publish);
						printf("修改为：");
						getchar();
						gets_s(p->publish);
						break;
					case 4:
						printf("原信息为：%s\n", p->publish_date);
						printf("修改为：");
						getchar();
						gets_s(p->publish_date);
						break;
					case 5:
						change_book_info(head);
						break;
					case 6:
						exit(0);
					}
					data_to_file(head);
					printf("修改成功！\n");
					flag = 1;		//表明已经找到图书（编号唯一，故可停止查询）
				}
			}
			if (flag == 0)
				printf("查无此书！");

			Sleep(800);
			system("cls");
			change_book_info(head);
			break;
		case 3:
			system("cls");
			return;
			break;
		case 4:
			exit(0);
		}
	}
	else 
	{
		printf("输入有误！请重新输入");
		system("cls");
		change_book_info(head);
	}
	Sleep(1000);
	system("cls");
	change_book_info(head);
}

/*-------------------删除图书-------------------*/
/*函数delete_book：删除图书信息*/
void delete_book(BOOK_LIST head) 
{
	BOOK_LIST current, p;		/*被删除节点、前一个节点*/
	int choice;
	int temp_num;				/*要删除的书籍编号*/
	char temp_name[40];			/*要删除的书籍名称*/

	printf("\n\n");
	printf("  +------------删除图书-------------+\n");
	printf("  |                                 |\n");
	printf("  |          1、按书号删除          |\n");      
	printf("  |          2、按书名删除          |\n");  
	printf("  |                                 |\n");
	printf("  +---------------------------------+\n");
	printf("  |          3、返回                |\n");
	printf("  |          4、退出系统            |\n");
	printf("  +---------------------------------+\n");

	printf("\n  请选择删除的方式：");
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 1:
		printf("\n  请输入要删除书籍的编号：");
		scanf_s("%d", &temp_num);

		current = head;
		while (current->num != temp_num && current->next != NULL)
		{
			p = current;
			current = current->next;
		}
		if (current->num == temp_num)
		{
			if (current == head)
				head = current->next;
			else
				p->next = current->next;

			free(current);
			printf("\n  删除成功！");
		}
		else
			printf("\n  查无此书！");

		break;

	case 2:
		printf("\n  请输入要删除书籍名称：");
		getchar();
		gets_s(temp_name);

		current = head;
		while (strcmp(current->name, temp_name) != 0 && current->next != NULL)
		{
			p = current;
			current = current->next;
		}
		if (strcpy_s(current->name, temp_name) == 0)
		{
			if (current == head)
				head = current->next;
			else
				p->next = current->next;

			free(current);
			printf("\n  删除成功！");
		}
		else
			printf("\n  查无此书！");
		break;
	case 3:
		system("cls");
		return;
		break;
	case 4:
		exit(0);
	}
	//将链表数据写入文件
	data_to_file(head);
	Sleep(500);
	system("cls");
}



