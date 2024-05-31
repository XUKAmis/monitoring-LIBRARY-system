//图书类Books:
#include <iostream>
#include <string>
#include <ctime>
#include <vector> 
#include <fstream>
using namespace std;
#pragma once
class Book
{
public:
    Book();////默认构造函数
    Book(int nBookID, string strBookName, string strAuthor, string strPub,int nBookprice, int nLeftNum);
	int GetBookID();
	void SetBookID(int nID);
	string GetBookName();
	void SetBookName(string strName);
	string GetAuthor();
	void SetAuthor(string strAuthor);
	int  GetBookPrice();
	void SetBookPrice(int nPrice);
	string GetPub();
	void SetPub(string strPub);
	int GetLeftNum();
	void SetLeftNum(int nLeftNum);
    virtual void ShowMe() = 0;
    ~Book();
     friend istream& operator>>(istream& in, Book& book);

protected:// 用protected可以让派生类访问
	int    nBookID;			//图书编号
	string strBookName;		//名称
	string strAuthor;		//作者
	int  nBookPrice;		//价格
	string strPub;			//出版社
	int    nLeftNum;		//余量
};
//派生类books：
class ScienceBook:public Book{
public:
    void ShowMe(){
        cout << "Science Book - ID: " << nBookID << ", Name: " << strBookName << ", Price: " << nBookPrice << ", Author: " << strAuthor << ", Publisher: " << strPub << ", LeftNum: " << nLeftNum << endl;
    }
};

class SocialBook:public Book{
public:
    void ShowMe(){
        cout << "Social Book - ID: " << nBookID << ", Name: " << strBookName << ", Price: " << nBookPrice << ", Author: " << strAuthor << ", Publisher: " << strPub << ", LeftNum: " << nLeftNum << endl;
    }
};

class ForeignBook:public Book{
private:
    string strBookLan;
public:
    void ShowMe(){
        cout << "Science Book - ID: " << nBookID << ", Name: " << strBookName << ", Price: " << nBookPrice << ", Author: " << strAuthor << ", Publisher: " << strPub <<", Language: "<< strBookLan<< ", LeftNum: " << nLeftNum << endl;
    }
    friend istream& operator>>(istream& in, ForeignBook& book){
        cout << "Enter Language: ";
        in >> book.strBookLan;
        in >> static_cast<Book&>(book);
        return in;
    }
};

