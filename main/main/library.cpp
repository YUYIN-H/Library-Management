#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "library.h"
#define FILENAME "Book_info.txt"


/*-----------load�����������ļ�������ֵΪ����ָ�룩��β�巨��������----------*/
BOOK_LIST load(void)
{
	BOOK_LIST head, new_node, tail;		/*ͷָ�롢�½ڵ�ָ�롢βָ��*/
	
	FILE *fp;			

	head = NULL;
	tail = NULL;

	if (fopen_s(&fp, FILENAME, "rb") == 1)		//�ж��ļ��Ƿ��
	{
		printf("Can not open the file %s\n", FILENAME);
		return head;
	}
	else
	{
		while (!feof(fp))		//feof()�������ж�ָ���Ƿ��Ѿ������ļ�β��
		{
			new_node = (BOOK_LIST)malloc(sizeof(BOOK));
			if (!new_node) {
				printf("Out of memory.\n");
				exit(1);
			}

			//��ȡͼ����Ϣ
			fscanf_s(fp, "%d%s%s%s%s%d", &new_node->num, new_node->name, 40, new_node->author, 20, new_node->publish, 40, new_node->publish_date, 20, &new_node->status);
			new_node->next = NULL;

			//��������β�巨��
			if (head == NULL)
				head = new_node;
			else
				tail->next = new_node;

			tail = new_node;

			printf("%d%s%s%s%s%d\n", new_node->num, new_node->name, new_node->author, new_node->publish, new_node->publish_date, new_node->status);
			//�������Ϊ�˲��������Ƿ񴴽��ɹ������ӡ����Ļ�ϣ����Ҫɾ��

		}
		fclose(fp);
		return(head);
	}
}



/*-------------data_to_file()������������д���ļ������ã�---------------*/
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
		//fprintf(fp, "���\t����\t\t\t����\t\t������\t\t\t����ʱ��\t\t\t����״̬\n");
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




/*-----�鿴������Ϣdisplay_user_info----*/
void display_user_info(void) {

}

/*-----�޸��û�����modify_password--------*/
void modify_password(void)
{

}

/*����auth_password_a������Ա������֤*/
void auth_password_a(void)
{

}

/*����auth_password_u���û�������֤*/
void auth_password_u(void)         //��֤�ɹ�����1��ʧ�ܷ���0
{

}

/*����input��¼��ͼ����Ϣ*/
BOOK_LIST input(BOOK_LIST head)
{
	BOOK_LIST temp, p, marker;		/*temp:�½ڵ�ָ��; ������ǽڵ�ָ��*/
	marker = NULL;

	temp = (BOOK_LIST)malloc(sizeof(BOOK));
	if (!temp){
		printf("Out of memory.\n");
		exit(1);
	}

	//¼������
	printf("\n\n\t��ţ�");
	scanf_s("%d", &temp->num);
	getchar();
	printf("\n\t������");
	gets_s(temp->name);
	fflush(stdin);
	printf("\n\t���ߣ�");
	gets_s(temp->author);
	fflush(stdin);
	printf("\n\t�����磺");
	gets_s(temp->publish);
	fflush(stdin);
	printf("\n\t����ʱ��(��ʽ��1970-01-01)��");
	gets_s(temp->publish_date);
	fflush(stdin);
	temp->status = 0;

	//���½ڵ�������������˳��
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
	printf("\n�Ƿ񱣴棿(Y/N)");


	//����������д���ļ�
	if (getchar() == 'Y')
	{
		data_to_file(head);
		printf("����ɹ���");
	}
	return head;
}

/*����search_book�������������������ţ����в���*/
void search_book(void)
{

}


/*����display_all���鿴����ͼ����Ϣ*/
void display_all(void)
{

}

/*--------------------ɸѡͼ��------------------*/
/*����display_unborrowed���鿴����δ�����鼮��Ϣ*/

void display_unborrowed(BOOK_LIST head)
{
	BOOK_LIST p;
	p = head;
	int flag = 0;

	printf("%-10s%-25s%-20s%-20s%-20s\n", "���", "����", "����", "������", "����ʱ��");
	while (p != NULL) {
		if (p->status == 0)
		{
			printf("%-10d%-25s%-20s%-20s%-20s\n", p->num, p->name, p->author, p->publish, p->publish_date);
			flag = 1;
		}
		p = p->next;
	}
	if (flag == 0)
		printf("����ͼ����ѽ����");
}


/*����display_borrowed���鿴�����ѽ���ͼ����Ϣ*/
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
		printf("û�н����ͼ�飡");
}

/*-------------------����ͼ��-------------------*/
/*����borrow_book������ͼ��*/
void borrow_book(void)
{

}

/*-------------------�޸�ͼ��-------------------*/
/*����change_book_info���޸�ͼ����Ϣ*/
void change_book_info(void) {

}

/*-------------------ɾ��ͼ��-------------------*/
/*����delete_book��ɾ��ͼ����Ϣ*/
BOOK_LIST delete_book(BOOK_LIST head) 
{
	BOOK_LIST current, p;		/*��ɾ���ڵ㡢ǰһ���ڵ�*/
	int choice;
	int temp_num;				/*Ҫɾ�����鼮���*/
	char temp_name[40];			/*Ҫɾ�����鼮����*/

	printf("\n-------------ɾ��ͼ��------------\n\n");
	printf("          1�������ɾ��\n");
	printf("          2��������ɾ��\n\n");
	printf("---------------------------------\n");

	printf("\n\t��ѡ��ɾ���ķ�ʽ��");
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 1:
	{
		printf("������Ҫɾ���鼮�ı�ţ�");
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
			printf("���޴��飡");

		break;
	}
	case 2:
	{
		printf("������Ҫɾ���鼮���ƣ�");
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
			printf("���޴��飡");
	}
	}
	data_to_file(head);
	return head;
}



