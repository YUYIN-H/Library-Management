#pragma once

/************�ṹ�嶨��************/


/*---------------------------ͼ����Ϣ---------------------------*/
typedef struct book_node {

	int num;                  //   ͼ�����   
	char book_name[50];              //   ͼ������    
	char book_auther[50];            //     ����      
	char publish[50];                   //������  

	struct date {
		int year, month, day;
	} publish_date;      //�������ڣ��ꡢ�¡��գ�  

	char status[10];                    //����״̬������״̬���ѽ��ġ�δ���ģ�
	struct book_node *next;     //     �ڵ�

} book;


/*-----------------------�û���Ϣ---------------------*/
typedef struct _reader {
	int id;             //�˺�   
	int password;       //����  
	book borrowed;		//�ѽ����鼮
	struct _reader *next;
}reader;


/*************��������************/

/*-----------�û����溯��user_menu����ӡ�û�ѡ�����-------------*/
void user_menu(void);

/*-----�鿴ͼ����Ϣѡ�����display_book_info����ӡ�鿴����-----*/
void display_book_info(void);

/*-----�鿴������Ϣdisplay_user_info----*/
void display_user_info(void);

/*-----�޸�����modify_password--------*/
void modify_password(void);

/*----------����Ա���溯��admin_menu����ӡ����Ա����-------------*/
void admin_menu(void);

/*--------------------������֤----------------------*/
/*����auth_password_a������Ա������֤*/
void auth_password_a(void);

/*����auth_password_u���û�������֤*/
void auth_password_u(void);          //��֤�ɹ�����1��ʧ�ܷ���0


/*--------------------ͼ����Ϣ¼��--------------------*/
/*����input��¼��ͼ����Ϣ*/
void input(void);


/*--------------------�鿴ͼ����Ϣ--------------------*/
/*����search_by_name���������鿴ͼ����Ϣ*/
void search_by_name(void);

/*����search_by_number������Ų鿴ͼ����Ϣ*/
void search_by_number(void);

/*����display_all���鿴����ͼ����Ϣ*/
void display_all(void);

/*--------------------ɸѡͼ��------------------*/
/*����display_unborrowed���鿴����δ�����鼮��Ϣ*/
void display_unborrowed(void);
/*����display_borrowed���鿴�����ѽ���ͼ����Ϣ*/
void display_borrowed(void);

/*-------------------����ͼ��-------------------*/
/*����borrow_book������ͼ��*/
void borrow_book(void);

/*-------------------�޸�ͼ��-------------------*/
/*����change_book_info���޸�ͼ����Ϣ*/
void change_book_info(void);

/*-------------------ɾ��ͼ��-------------------*/
/*����delete_book��ɾ��ͼ����Ϣ*/
void delete_book(void);




