#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
	marker = NULL;

	temp = (BOOK_LIST)malloc(sizeof(BOOK));
	if (!temp){
		printf("Out of memory.\n");
		exit(1);
	}

	//录入数据
	printf("\n\n\t书号：");
	scanf_s("%d", &temp->num);
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
	printf("\n\t出版时间(格式：1970-01-01)：");
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
	printf("\n是否保存？(Y/N)");


	//将链表数据写入文件
	if (getchar() == 'Y')
	{
		data_to_file(head);
		printf("保存成功。");
	}
	return head;
}

/*函数search_book：进入后输入书名或书号，进行查找*/
void search_book(void)
{

}


/*函数display_all：查看所有图书信息*/
void display_all(void)
{

}

/*--------------------筛选图书------------------*/
/*函数display_unborrowed：查看所有未借阅书籍信息*/

void display_unborrowed(BOOK_LIST head)
{
	BOOK_LIST p;
	p = head;
	int flag = 0;

	printf("%-10s%-25s%-20s%-20s%-20s\n", "书号", "书名", "作者", "出版社", "出版时间");
	while (p != NULL) {
		if (p->status == 0)
		{
			printf("%-10d%-25s%-20s%-20s%-20s\n", p->num, p->name, p->author, p->publish, p->publish_date);
			flag = 1;
		}
		p = p->next;
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

	while (p != NULL) {
		if (p->status == 1) 
		{
			printf("%-10d%-25s%-20s%-20s%-20s\n", p->num, p->name, p->author, p->publish, p->publish_date);
			flag = 0;
		}
		p = p->next;
	}
	if (flag == 1)
		printf("没有借出的图书！");
}

/*-------------------借阅图书-------------------*/
/*函数borrow_book：借阅图书*/
void borrow_book(void)
{

}

/*-------------------修改图书-------------------*/
/*函数change_book_info：修改图书信息*/
void change_book_info(void) {

}

/*-------------------删除图书-------------------*/
/*函数delete_book：删除图书信息*/
BOOK_LIST delete_book(BOOK_LIST head) 
{
	BOOK_LIST current, p;		/*被删除节点、前一个节点*/
	int choice;
	int temp_num;				/*要删除的书籍编号*/
	char temp_name[40];			/*要删除的书籍名称*/

	printf("\n-------------删除图书------------\n\n");
	printf("          1、按书号删除\n");
	printf("          2、按书名删除\n\n");
	printf("---------------------------------\n");

	printf("\n\t请选择删除的方式：");
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 1:
	{
		printf("请输入要删除书籍的编号：");
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
		}
		else
			printf("查无此书！");

		break;
	}
	case 2:
	{
		printf("请输入要删除书籍名称：");
		gets_s(temp_name);

		current = head;
		while (strcpy_s(current->name, temp_name) == 0 && current->next != NULL)
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
		}
		else
			printf("查无此书！");
	}
	}
	data_to_file(head);
	return head;
}



