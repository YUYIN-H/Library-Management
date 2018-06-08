#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "library.h"
#define FILENAME "123.txt"


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
		}
		fclose(fp);
		return(head);
	}
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
	FILE *fp;
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
		marker->next = temp;
		temp->next = marker;
	}
	printf("\n�Ƿ񱣴棿(Y/N)");


	//����������д���ļ�
	if (getchar() == 'Y')
	{
		fflush(stdin);
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
				fprintf(fp, "%-10d", p->num);
				fprintf(fp, "%-25s", p->name);
				fprintf(fp, "%-20s", p->author);
				fprintf(fp, "%-20s", p->publish);
				fprintf(fp, "%-15s", p->publish_date);
				fprintf(fp, "%-5d\n", p->status);
			}
				
		}
		fclose(fp);
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
}
	/*
	BOOK_LIST p;
	p = head;
	int flag = 0;

	printf("%-30s%-40s%-30s%-50s%-40s\n", "���", "����", "����", "������", "����ʱ��");
	while (p != NULL) {
		if (p->status == 0)
		{
			printf("%-30d%-40s%-30s%-50s%d��%d��%d��\n", p->num, p->name, p->author, p->publish, p->publish_date);
			flag = 1;
		}
		p = p->next;
	}
	if (flag == 0)
		printf("����ͼ����ѽ����");
}

*/


/*����display_borrowed���鿴�����ѽ���ͼ����Ϣ*/
void display_borrowed()
{

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
void delete_book(void) 
{

}
