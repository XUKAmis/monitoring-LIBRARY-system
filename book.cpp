#include "book.h"
#include <iostream>
using namespace std;
Book::Book(){

};
Book::Book(int nBookID, string strBookName, string strAuthor, string strPub,int nBookPrice,int nLeftNum)
{
	nBookID = nBookID;
	strBookName = strBookName;
    nBookPrice = nBookPrice;
	strAuthor = strAuthor;
	strPub = strPub;
	nLeftNum = nLeftNum;
}

Book::~Book()
{
}

int Book::GetBookID()
{
	return nBookID;
}

void Book::SetBookID(int nID)
{
	nBookID = nID;
}

void Book::SetBookName(string strName)
{
	strBookName = strName;
}

string Book::GetAuthor()
{
	return strAuthor;
}

void Book::SetAuthor(string strAuthor)
{
	strAuthor = strAuthor;
}

int  Book::GetBookPrice()
{
	return nBookPrice;
}

void Book::SetBookPrice(int nPrice)
{
	nBookPrice = nPrice;
}

string Book::GetPub()
{
	return strPub;
}

void Book::SetPub(string strPub)
{
	strPub = strPub;
}
int Book::GetLeftNum()
{
	return nLeftNum;
}

void Book::SetLeftNum(int nLeftNum)
{
	nLeftNum = nLeftNum;
}

istream& operator>>(istream& in, Book& book) {////重载>>函数
    cout << "Enter Book ID: ";
    in >> book.nBookID;
    cout << "Enter Book Name: ";
    in >> book.strBookName;
    cout << "Enter Price: ";
    in >> book. nBookPrice;
    cout << "Enter Author: ";
    in >> book.strAuthor;
    cout << "Enter Publisher: ";
    in >> book.strPub;
    cout << "Enter Store: ";
    in >> book.nLeftNum;

    return in;
}

