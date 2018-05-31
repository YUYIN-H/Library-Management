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

