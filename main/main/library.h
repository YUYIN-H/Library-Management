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


/*************函数声明************/

/*-----------用户界面函数user_menu：打印用户选择界面-------------*/
void user_menu(void);

/*-----查看图书信息选择界面display_book_info：打印查看界面-----*/
void display_book_info(void);

/*-----查看个人信息display_user_info----*/
void display_user_info(void);

/*-----修改密码modify_password--------*/
void modify_password(void);

/*----------管理员界面函数admin_menu：打印管理员界面-------------*/
void admin_menu(void);

/*--------------------密码验证----------------------*/
/*函数auth_password_a：管理员密码验证*/
void auth_password_a(void);

/*函数auth_password_u：用户密码验证*/
void auth_password_u(void);          //验证成功返回1，失败返回0


/*--------------------图书信息录入--------------------*/
/*函数input：录入图书信息*/
void input(void);


/*--------------------查看图书信息--------------------*/
/*函数search_by_name：按书名查看图书信息*/
void search_by_name(void);

/*函数search_by_number：按书号查看图书信息*/
void search_by_number(void);

/*函数display_all：查看所有图书信息*/
void display_all(void);

/*--------------------筛选图书------------------*/
/*函数display_unborrowed：查看所有未借阅书籍信息*/
void display_unborrowed(void);
/*函数display_borrowed：查看所有已借阅图书信息*/
void display_borrowed(void);

/*-------------------借阅图书-------------------*/
/*函数borrow_book：借阅图书*/
void borrow_book(void);

/*-------------------修改图书-------------------*/
/*函数change_book_info：修改图书信息*/
void change_book_info(void);

/*-------------------删除图书-------------------*/
/*函数delete_book：删除图书信息*/
void delete_book(void);




