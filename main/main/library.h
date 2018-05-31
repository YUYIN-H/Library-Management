#pragma once

/************结构体定义************/


/*---------------------------图书信息---------------------------*/
typedef struct book_node {

	int num;                  //   图书序号   
	char book_name[50];              //   图书名称    
	char book_auther[50];            //     作者      
	char publish[50];                   //出版社  

	struct date {
		int year, month, day;
	} publish_date;      //出版日期（年、月、日）  

	char status[10];                    //借阅状态（两种状态：已借阅、未借阅）
	struct book_node *next;     //     节点

} book;


/*-----------------------用户信息---------------------*/
typedef struct _reader {
	int id;             //账号   
	int password;       //密码  
	book borrowed;		//已借阅书籍
	struct _reader *next;
}reader;

