#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include "library.h"
#define FILENAME "Book_info.txt"
#define FILENAME2 "Reader_info.txt"

extern char ID[20];          /*��¼�û�����ID*/

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
			fscanf_s(fp, "%d%s%s%s%s%d%s", &new_node->num, new_node->name, 40, new_node->author, 20, new_node->publish, 40, new_node->publish_date, 20, &new_node->status, new_node->readerID, 20);
			new_node->next = NULL;

			//��������β�巨��
			if (head == NULL)
				head = new_node;
			else
				tail->next = new_node;

			tail = new_node;
			/*printf("%d%s%s%s%s%d%s\n", new_node->num, new_node->name, new_node->author, new_node->publish, new_node->publish_date, new_node->status, new_node->readerID);
			�������Ϊ�˲��������Ƿ񴴽��ɹ������ӡ����Ļ�ϣ����Ҫɾ��*/
		}
		fclose(fp);
		return(head);
	}
}

/*-----------load2���������ض����ļ�������ֵΪ����ָ�룩��β�巨��������----------*/
READER_LIST load2(void)
{
	READER_LIST head, new_node, tail;		/*ͷָ�롢�½ڵ�ָ�롢βָ��*/

	FILE *fp;

	head = NULL;
	tail = NULL;

	if (fopen_s(&fp, FILENAME2, "rb") == 1)		//�ж��ļ��Ƿ��
	{
		printf("Can not open the file %s\n", FILENAME2);
		return head;
	}
	else
	{
		while (!feof(fp))		//feof()�������ж�ָ���Ƿ��Ѿ������ļ�β��
		{
			new_node = (READER_LIST)malloc(sizeof(READER));
			if (!new_node) {
				printf("Out of memory.\n");
				exit(1);
			}

			//��ȡ������Ϣ
			fscanf_s(fp, "%s%s", new_node->id, 20, new_node->password, 20);
			new_node->next = NULL;

			//��������β�巨��
			if (head == NULL)
				head = new_node;
			else
				tail->next = new_node;

			tail = new_node;
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
		for (p = head; p != NULL; p = p->next)
		{
			fprintf(fp, "\n%-10d", p->num);
			fprintf(fp, "%-25s", p->name);
			fprintf(fp, "%-20s", p->author);
			fprintf(fp, "%-20s", p->publish);
			fprintf(fp, "%-15s", p->publish_date);
			fprintf(fp, "%-5d", p->status);
			fprintf(fp, "%10s", p->readerID);
		}
	}
	fclose(fp);
	return head;
}

/*-------------data_to_file2()������������д���ļ������ã�---------------*/
READER_LIST data_to_file2(READER_LIST head2)
{
	FILE *fp;
	READER_LIST p;

	if (fopen_s(&fp, FILENAME2, "w") == 1)
	{
		printf("Can not open the file %s\n", FILENAME2);
		return head2;
	}
	else
	{
		//fprintf(fp, "�˺�\t����\t");
		for (p = head2; p != NULL; p = p->next)
		{
			fprintf(fp, "\n%-19s", p->id);
			fprintf(fp, "%19s", p->password);
		}
	}
	fclose(fp);
	return head2;
}


/*-----�鿴������Ϣdisplay_user_info----*/
void display_user_info(READER_LIST head2, BOOK_LIST head)
{
	READER_LIST p;

	for (p = head2; p != NULL; p = p->next)
	{
		if (strcmp(p->id, ID) == 0)
		{
			printf("\n  %sͬѧ, �����ĵ��鼮���£�\n\n", p->id);
			break;
		}
	}

	BOOK_LIST q;
	q = head;
	int flag = 0;
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf(" |  %-10s%-25s%-20s%-20s%-20s|\n", "���", "����", "����", "������", "����ʱ��");
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	while (q != NULL) {
		if (q->status == 1)
		{
			if (strcmp(q->readerID, ID) == 0)		
				printf(" |  %-10d%-25s%-20s%-20s%-20s|\n", q->num, q->name, q->author, q->publish, q->publish_date);
			flag = 1;
		}
		q = q->next;
	}
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf("\n");
	if (flag == 0)
		printf("  Ŀǰû�н����κ��鼮.");
	printf("\n");
	printf("   ����Q���أ�");

	fflush(stdin);
	getchar();
	if (getchar() == 'Q')
	{
		system("cls");
		return;
	}
}


/*-----�޸��û�����modify_password_u--------*/
READER_LIST modify_password(READER_LIST head2)
{
	READER_LIST p;

	for (p = head2; p != NULL; p = p->next)
	{
		if (strcmp(p->id, ID) == 0)
		{
			printf("\n\n  ԭ����Ϊ��%s\n\n", p->password);
			printf("\n  �޸�Ϊ��");                                        //��֤�޸���Ϣ��ԭ��Ϣ�Ƿ���ͬ����
			getchar();
			gets_s(p->password);
			data_to_file2(head2);
			printf("\n\n  �޸ĳɹ���");
			break;
		}
	}
	Sleep(500);
	system("cls");
	return head2;
}


/*����input��¼��ͼ����Ϣ*/
BOOK_LIST input(BOOK_LIST head)
{
	BOOK_LIST temp, p, marker;		/*temp:�½ڵ�ָ��; ������ǽڵ�ָ��*/
	BOOK_LIST q;		/*����������*/
	marker = NULL;

	temp = (BOOK_LIST)malloc(sizeof(BOOK));
	if (!temp){
		printf("Out of memory.\n");
		exit(1);
	}

	//¼������
	printf("\n   -----------------ͼ����Ϣ¼��-----------------");
	printf("\n\n\t��ţ�");
	scanf_s("%d", &temp->num);

	for (q = head; q != NULL; q = q->next)
	{
		if (temp->num == q->num)
		{
			printf("\n  �ñ���Ѵ���!");
			Sleep(500);
			system("cls");
			return head;
		}
	}
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
	printf("\n\t����ʱ��(1970-01-01)��");
	gets_s(temp->publish_date);
	fflush(stdin);
	temp->status = 0;
	strcpy_s(temp->readerID , "-");
	
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
	printf("\n �Ƿ񱣴棿(Y/N)");


	//����������д���ļ�
	if (getchar() == 'Y')
	{
		data_to_file(head);
		printf("\n\n\t����ɹ���\n");
	}
	Sleep(500);
	system("cls");
	return head;
}

/*����search_book�������������������ţ����в���*/
void search_book(BOOK_LIST head)
{
	int choice;
	
	printf("\n\n");
	printf("       + -------------��ѯͼ��------------+\n");
	printf("       |                                  |\n");
	printf("       |           1������Ų�ѯ          |\n");
	printf("       |           2����������ѯ          |\n");
	printf("       |           3������                |\n");
	printf("       |                                  |\n");
	printf("       +----------------------------------+\n");
	printf("\n\t��ѡ���ѯ�ķ�ʽ��");
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

/*----����search_by_num������Ų�ѯ----*/
void search_by_num(BOOK_LIST head)
{
	BOOK_LIST p;
	int flag = 0;
	int temp_num;				/*Ҫ��ѯ���鼮���*/

	printf("\n  ������Ҫ��ѯ�鼮�ı�ţ�");
	scanf_s("%d", &temp_num);

	for (p = head; p != NULL; p = p->next)
	{
		if (p->num == temp_num)
		{
			printf("\n\n");
			printf("             ͼ����Ϣ\n");
			printf("  -------------------------------\n");
			printf("      ��ţ�%d\n", p->num);
			printf("      ������%s\n", p->name);
			printf("      ���ߣ�%s\n", p->author);
			printf("      �����磺%s\n", p->publish);
			printf("      ����ʱ�䣺%s\n", p->publish_date);
			printf("  -------------------------------\n");
			flag = 1;		//�����Ѿ��ҵ�ͼ�飨���Ψһ���ʿ�ֹͣ��ѯ��
			break;
		}
	}
	if (flag == 0)
	{
		printf("���޴��飡");
		Sleep(500);
		system("cls");
		return;
	}
	printf("\n  ����Q���أ�");
	getchar();
	if (getchar() == 'Q')
	{
		system("cls");
		return;
	}
}

/*----����search_by_name����������ѯ----*/
void search_by_name(BOOK_LIST head)
{

	BOOK_LIST p;
	int flag = 0;
	char book_name[40];			/*Ҫ��ѯ���鼮����*/

	p = NULL;


	printf("\n  ������Ҫ��ѯͼ������ƣ�");
	getchar();
	gets_s(book_name);

	for (p = head; p != NULL; p = p->next)
	{
		if (strcmp(p->name, book_name) == 0)
		{
			printf("\n\n");
			printf("             ͼ����Ϣ\n");
			printf("  -------------------------------\n");
			printf("      ��ţ�%d\n", p->num);
			printf("      ������%s\n", p->name);
			printf("      ���ߣ�%s\n", p->author);
			printf("      �����磺%s\n", p->publish);
			printf("      ����ʱ�䣺%s\n", p->publish_date);
			printf("  -------------------------------\n");
			flag = 1;		//�����Ѿ��ҵ�ͼ�飨���Ψһ���ʿ�ֹͣ��ѯ��
			break;
		}
	}
	if (flag == 0)
	{
		printf("���޴��飡");
		Sleep(500);
		system("cls");
		return;
	}
	printf("\n  ����Q���أ�");
	getchar();
	if (getchar() == 'Q')
	{
		system("cls");
		return;
	}
}

/*����display_all���鿴����ͼ����Ϣ*/
void display_all(BOOK_LIST head)
{
	BOOK_LIST p;
	printf("\n");
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf(" |  %-10s%-25s%-20s%-20s%-20s|\n", "���", "����", "����", "������", "����ʱ��");
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	for(p = head; p != NULL; p = p->next)
		printf(" |  %-10d%-25s%-20s%-20s%-20s|\n", p->num, p->name, p->author, p->publish, p->publish_date);
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf("\n\n");
	printf("   ����Q���أ�");
	
	fflush(stdin);
	getchar();
	if (getchar() == 'Q')
	{
		system("cls");
		return;
	}	
}

/*����display_unborrowed���鿴����δ�����鼮��Ϣ*/
void display_unborrowed(BOOK_LIST head)
{
	BOOK_LIST p;
	p = head;
	int flag = 0;

	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf(" |  %-10s%-25s%-20s%-20s%-20s|\n", "���", "����", "����", "������", "����ʱ��");
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	while (p != NULL) {
		if (p->status == 0)
		{
			printf(" |  %-10d%-25s%-20s%-20s%-20s|\n", p->num, p->name, p->author, p->publish, p->publish_date);
			flag = 1;
		}
		p = p->next;
	}
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf("\n\n");

	if (flag == 0)
		printf("   ����ͼ����ѽ����\n");

	printf("   ����Q���أ�");
	fflush(stdin);
	getchar();
	if (getchar() == 'Q')
	{
		system("cls");
		display_book_info(head);
	}
}

/*����display_borrowed���鿴�����ѽ���ͼ����Ϣ*/
void display_borrowed(BOOK_LIST head)
{
	BOOK_LIST p;
	p = head;
	int flag = 1;

	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf(" |  %-10s%-25s%-20s%-20s%-20s|\n", "���", "����", "����", "������", "����ʱ��");
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	while (p != NULL) {
		if (p->status == 1) 
		{
			printf(" |  %-10d%-25s%-20s%-20s%-20s|\n", p->num, p->name, p->author, p->publish, p->publish_date);
			flag = 0;
		}
		p = p->next;
	}
	printf(" +-----------------------------------------------------------------------------------------------+\n");
	printf("\n\n");
	if (flag == 1)
		printf("   û�н����ͼ�飡\n");

	printf("   ����Q���أ�");
	fflush(stdin);
	getchar();
	if (getchar() == 'Q')
	{
		system("cls");
		display_book_info(head);
	}

}

/*-------------------����ͼ��-------------------*/
/*����borrow_book������ͼ��*/
void borrow_book(BOOK_LIST head)
{
	BOOK_LIST p;
	int choice;
	int book_num;
	char book_name[40];
	BOOK_LIST book_same_name[10] = { 0 };	//����ָ������

	int i = 0;
	int flag = 0;


	printf("+------------------------------+\n");
	printf("|            ����ͼ��          |\n");
	printf("+------------------------------+\n");
	printf("|          1.����Ž���        |\n");
	printf("|          2.����������        |\n");
	printf("|          3.����              |\n");
	printf("|          4.�˳�              |\n");
	printf("+------------------------------+\n");
	printf("\n  --> ");
	scanf_s("%d", &choice);
	printf("\n");
	if (choice > 0 && choice <= 4)
	{
		switch (choice)
		{
		case 1:
			printf("\n ������Ҫ�����鼮�ı�ţ�");
			scanf_s("%d", &book_num);

			for (p = head; p != NULL; p = p->next)
			{
				if (p->num == book_num)
				{
					flag = 1;
					break;
				}
					
			}
			if (flag == 0)
			{
				printf("���޴��飡");
				Sleep(500);
				system("cls");
				return;
			}
			else
			{
				if (p->status == 1)
				{
					printf("\n �����Ѿ������");
					Sleep(500);
					system("cls");
					return;
				}
				else
				{
					printf("\n\n----------------------------\n");
					printf("             ͼ����Ϣ\n");
					printf("----------------------------\n");
					printf("    ��ţ�%d\n", p->num);
					printf("    ������%s\n", p->name);
					printf("    ���ߣ�%s\n", p->author);
					printf("    �����磺%s\n", p->publish);
					printf("    ����ʱ�䣺%s\n", p->publish_date);
					printf("-----------------------------\n");

					getchar();
					printf("\n  �Ƿ���ģ�Y/N��?  ");
					if (getchar() == 'Y')
					{
						p->status = 1;
						strcpy_s(p->readerID, ID);
						data_to_file(head);
						printf("\n  ���ĳɹ���");
						Sleep(500);
						system("cls");
						return;
					}
					else
						return;
				}
			}
			break;
		case 2:
			printf("\n ������Ҫ���ĵ��鼮���ƣ�");
			getchar();
			gets_s(book_name);

			for (p = head; p != NULL; p = p->next)
			{
				if (strcmp(p->name, book_name) == 0)
					break;
			}
			if (p->status == 1)
			{
				printf("\n �����Ѿ������");
				Sleep(500);
				system("cls");
				return;
			}
			else
			{
				printf("\n\n----------------------------\n");
				printf("             ͼ����Ϣ\n");
				printf("----------------------------\n");
				printf("    ��ţ�%d\n", p->num);
				printf("    ������%s\n", p->name);
				printf("    ���ߣ�%s\n", p->author);
				printf("    �����磺%s\n", p->publish);
				printf("    ����ʱ�䣺%s\n", p->publish_date);
				printf("-----------------------------\n");

				printf("\n  �Ƿ���ģ�Y/N��?  ");
				if (getchar() == 'Y')
				{
					p->status = 1;
					strcpy_s(p->readerID, ID);
					data_to_file(head);
					printf("\n  ���ĳɹ���");
					Sleep(500);
					system("cls");
					return;
				}
				else
				{
					system("cls");
					return;
				}
			}
			break;
		case 3:
			system("cls");
			return;
		case 4:
			exit(0);
		}
	}
}

/*-------------------�޸�ͼ��-------------------*/
/*����change_book_info���޸�ͼ����Ϣ*/
void change_book_info(BOOK_LIST head)
{
	BOOK_LIST p;
	int choice1, choice2;
	int flag = 0;
	BOOK_LIST book_same_name[10] = { 0 };	//����ָ������

	printf("\n\n");
	printf("     +------------------------------+\n");
	printf("     |         �޸�ͼ����Ϣ         |\n");
	printf("     +------------------------------+\n");
	printf("     |         1.����������         |\n");
	printf("     |         2.����Ų���         |\n");
	printf("     |         3.����               |\n");
	printf("     |         4.�˳�               |\n");
	printf("     +------------------------------+");
	printf("\n\t-->");
	scanf_s("%d", &choice1);

	if (choice1 > 0 && choice1 <= 4)
	{
		switch (choice1) {
		case 1:
			system("cls");
			char temp_name[40];			/*Ҫ��ѯ���鼮����*/

			printf("\n\n       ������Ҫ��ѯ�鼮�����ƣ�");
			getchar();
			gets_s(temp_name);

			printf("\n  ��ѡ��Ҫ�޸ĵ�����\n");
			printf("            +-------------------------+\n");
			printf("            |          1.����         |\n");
			printf("            |          2.����         |\n");
			printf("            |          3.������       |\n");
			printf("            |          4.����ʱ��     |\n");
			printf("            +-------------------------+\n");
			printf("            |          5.����         |\n");
			printf("            |          6.�˳�         |\n");
			printf("            +-------------------------+");

			printf("\n\n     -->");
			scanf_s("%d", &choice2);

			for (p = head; p != NULL; p = p->next)
			{
				if (strcmp(p->name, temp_name) == 0)
				{
					flag = 1;
					switch (choice2)
					{
					case 1:
						printf("\n ԭ��ϢΪ��%s\n\n", p->name);
						printf("\n �޸�Ϊ��");
						getchar();
						gets_s(p->name);
						data_to_file(head);
						printf("\n\n  �޸ĳɹ���");
						break;
					case 2:
						printf("\n ԭ��ϢΪ��%s\n\n", p->author);
						printf("\n �޸�Ϊ��");
						getchar();
						gets_s(p->author);
						data_to_file(head);
						printf("\n\n  �޸ĳɹ���");
						break;
					case 3:
						printf("\n ԭ��ϢΪ��%s\n\n", p->publish);
						printf("\n �޸�Ϊ��");
						getchar();
						gets_s(p->publish);
						data_to_file(head);
						printf("\n\n  �޸ĳɹ���");
						break;
					case 4:
						printf("\n ԭ��ϢΪ��%s\n\n", p->publish_date);
						printf("\n �޸�Ϊ��");
						getchar();
						gets_s(p->publish_date);
						data_to_file(head);
						printf("\n\n  �޸ĳɹ���");
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
				printf("���޴��飡");
			break;
		case 2:
			system("cls");
			int temp_num;				/*Ҫ��ѯ���鼮���*/

			printf("\n\n   ������Ҫ��ѯ�鼮�ı�ţ�");
			scanf_s("%d", &temp_num);

			printf("\n  ��ѡ��Ҫ�޸ĵ�����\n");
			printf("            +-------------------------+\n");
			printf("            |          1.����         |\n");
			printf("            |          2.����         |\n");
			printf("            |          3.������       |\n");
			printf("            |          4.����ʱ��     |\n");
			printf("            +-------------------------+\n");
			printf("            |          5.����         |\n");
			printf("            |          6.�˳�         |\n");
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
						printf("ԭ��ϢΪ��%s\n", p->name);
						printf("�޸�Ϊ��");
						getchar();
						gets_s(p->name);
						break;
					case 2:
						printf("ԭ��ϢΪ��%s\n", p->author);
						printf("�޸�Ϊ��");
						getchar();
						gets_s(p->author);
						break;
					case 3:
						printf("ԭ��ϢΪ��%s\n", p->publish);
						printf("�޸�Ϊ��");
						getchar();
						gets_s(p->publish);
						break;
					case 4:
						printf("ԭ��ϢΪ��%s\n", p->publish_date);
						printf("�޸�Ϊ��");
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
					printf("�޸ĳɹ���\n");
					flag = 1;		//�����Ѿ��ҵ�ͼ�飨���Ψһ���ʿ�ֹͣ��ѯ��
				}
			}
			if (flag == 0)
				printf("���޴��飡");

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
		printf("������������������");
		system("cls");
		change_book_info(head);
	}
	Sleep(1000);
	system("cls");
	return;
}

/*-------------------ɾ��ͼ��-------------------*/
/*����delete_book��ɾ��ͼ����Ϣ*/
BOOK_LIST delete_book(BOOK_LIST head) 
{
	BOOK_LIST current, p;		/*��ɾ���ڵ㡢ǰһ���ڵ�*/
	int choice;
	int temp_num;				/*Ҫɾ�����鼮���*/
	char temp_name[40];			/*Ҫɾ�����鼮����*/
	BOOK_LIST book_same_name[10] = { 0 };	//����ָ������

	printf("\n\n");
	printf("  +------------ɾ��ͼ��-------------+\n");
	printf("  |                                 |\n");
	printf("  |          1�������ɾ��          |\n");      
	printf("  |          2��������ɾ��          |\n");  
	printf("  |                                 |\n");
	printf("  +---------------------------------+\n");
	printf("  |          3������                |\n");
	printf("  |          4���˳�ϵͳ            |\n");
	printf("  +---------------------------------+\n");

	printf("\n  ��ѡ��ɾ���ķ�ʽ��");
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 1:
		printf("\n  ������Ҫɾ���鼮�ı�ţ�");
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
			printf("\n  ɾ���ɹ���");
		}
		else
			printf("\n  ���޴��飡");
		break;
	case 2:
		printf("\n  ������Ҫɾ���鼮���ƣ�");
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
			printf("\n  ɾ���ɹ���");
		}
		else
			printf("\n  ���޴��飡");
		break;
	case 3:
		system("cls");
		return head;
		break;
	case 4:
		exit(0);
	}
	//����������д���ļ�
	data_to_file(head);
	Sleep(500);
	system("cls");
	return head;
}



