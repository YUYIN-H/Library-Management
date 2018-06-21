#pragma once

/************�ṹ�嶨��************/


/*---------------------------ͼ����Ϣ---------------------------*/

/*----------ͼ��ڵ�------------*/
typedef struct book_node {

	int num;						//ͼ�����   
	char name[40];             //ͼ������    
	char author[20];           //����      
	char publish[40];               //������  
	char publish_date[20];				//�������ڣ��ꡢ�¡��գ�  
	int status;						//����״̬������״̬���ѽ���Ϊ1��δ����Ϊ0��
	struct book_node *next;			//�ڵ�ָ��
} BOOK;

typedef BOOK *BOOK_LIST;		//������������ָ��Ϊ BOOK_LIST



/*-----------------------�û���Ϣ---------------------*/
/*---------�û��ڵ�----------*/
typedef struct reader_node {
	int id;					//�˺�   
	int password;			//����  
	BOOK borrowed;			//�ѽ����鼮
	struct reader *next;
} READER;

typedef READER *READER_LIST;		//������������ָ��Ϊ READER_LIST




/*************��������************/

/*-----------load�����������ļ�----------*/
BOOK_LIST load(void);

/*-----------�û����溯��user_menu����ӡ�û�ѡ�����-------------*/
void user_menu(BOOK_LIST head);

/*-----�鿴ͼ����Ϣѡ�����display_book_info����ӡ�鿴����-----*/
void display_book_info(BOOK_LIST head);

/*-----�鿴������Ϣdisplay_user_info----*/
void display_user_info(void);

/*-----�޸��û�����modify_password--------*/
void modify_password(void);

/*----------����Ա���溯��admin_menu����ӡ����Ա����-------------*/
void admin_menu(BOOK_LIST head);

/*--------------------������֤----------------------*/
/*����auth_password_a������Ա������֤*/
void auth_password_a(void);

/*����auth_password_u���û�������֤*/
void auth_password_u(void);          //��֤�ɹ�����1��ʧ�ܷ���0


/*--------------------ͼ����Ϣ¼��--------------------*/
/*����input��¼��ͼ����Ϣ*/
BOOK_LIST input(BOOK_LIST head);


/*--------------------����ͼ��------------------------*/
/*����search_book�������������������ţ����в���*/
void search_book(BOOK_LIST head);
/*----����search_by_num������Ų�ѯ----*/
BOOK_LIST search_by_num(BOOK_LIST head);
/*----����search_by_num����������ѯ----*/
void search_by_name(BOOK_LIST head);

/*����display_all���鿴����ͼ����Ϣ*/
void display_all(BOOK_LIST head);

/*--------------------ɸѡͼ��------------------*/
/*����display_unborrowed���鿴����δ�����鼮��Ϣ*/
void display_unborrowed(BOOK_LIST head);
/*����display_borrowed���鿴�����ѽ���ͼ����Ϣ*/
void display_borrowed(BOOK_LIST head);

/*-------------------����ͼ��-------------------*/
/*����borrow_book������ͼ��*/
void borrow_book(BOOK_LIST head);

/*-------------------�޸�ͼ��-------------------*/
/*����change_book_info���޸�ͼ����Ϣ*/
void change_book_info(BOOK_LIST head);

/*-------------------ɾ��ͼ��-------------------*/
/*����delete_book��ɾ��ͼ����Ϣ*/
void delete_book(BOOK_LIST head);



/*-------------����������д���ļ�---------------*/
BOOK_LIST data_to_file(BOOK_LIST head);
