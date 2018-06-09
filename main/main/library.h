#pragma once

/************结构体定义************/


/*---------------------------图书信息---------------------------*/

/*----------图书节点------------*/
typedef struct book_node {

	int num;						//图书序号   
	char name[40];             //图书名称    
	char author[20];           //作者      
	char publish[40];               //出版社  
	char publish_date[20];				//出版日期（年、月、日）  
	int status;						//借阅状态（两种状态：已借阅为1、未借阅为0）
	struct book_node *next;			//节点指针
} BOOK;

typedef BOOK *BOOK_LIST;		//重新命名链表指针为 BOOK_LIST



/*-----------------------用户信息---------------------*/
/*---------用户节点----------*/
typedef struct reader_node {
	int id;					//账号   
	int password;			//密码  
	BOOK borrowed;			//已借阅书籍
	struct reader *next;
} READER;

typedef READER *READER_LIST;		//重新命名链表指针为 READER_LIST




/*************函数声明************/

/*-----------load函数：加载文件----------*/
BOOK_LIST load(void);

/*-----------用户界面函数user_menu：打印用户选择界面-------------*/
void user_menu(BOOK_LIST head);

/*-----查看图书信息选择界面display_book_info：打印查看界面-----*/
void display_book_info(BOOK_LIST head);

/*-----查看个人信息display_user_info----*/
void display_user_info(void);

/*-----修改用户密码modify_password--------*/
void modify_password(void);

/*----------管理员界面函数admin_menu：打印管理员界面-------------*/
void admin_menu(BOOK_LIST head);

/*--------------------密码验证----------------------*/
/*函数auth_password_a：管理员密码验证*/
void auth_password_a(void);

/*函数auth_password_u：用户密码验证*/
void auth_password_u(void);          //验证成功返回1，失败返回0


/*--------------------图书信息录入--------------------*/
/*函数input：录入图书信息*/
BOOK_LIST input(BOOK_LIST head);


/*--------------------查找图书------------------------*/
/*函数search_book：进入后输入书名或书号，进行查找*/
void search_book(void);

/*函数display_all：查看所有图书信息*/
void display_all(void);

/*--------------------筛选图书------------------*/
/*函数display_unborrowed：查看所有未借阅书籍信息*/
void display_unborrowed(BOOK_LIST head);
/*函数display_borrowed：查看所有已借阅图书信息*/
void display_borrowed(BOOK_LIST head);

/*-------------------借阅图书-------------------*/
/*函数borrow_book：借阅图书*/
void borrow_book(void);

/*-------------------修改图书-------------------*/
/*函数change_book_info：修改图书信息*/
void change_book_info(void);

/*-------------------删除图书-------------------*/
/*函数delete_book：删除图书信息*/
BOOK_LIST delete_book(BOOK_LIST head);



/*-------------将链表数据写入文件---------------*/
BOOK_LIST data_to_file(BOOK_LIST head);
