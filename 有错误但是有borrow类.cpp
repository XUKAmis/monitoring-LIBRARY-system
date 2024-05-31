#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;


class Book {
	public:
		Book();////默认构造函数
		Book(int nBookID, string strBookName, string strAuthor, string strPub, int nBookprice, int nLeftNum);
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
		friend istream &operator>>(istream &in, Book &book);

	protected:// 用protected可以让派生类访问
		int    nBookID;			//图书编号
		string strBookName;		//名称
		string strAuthor;		//作者
		int  nBookPrice;		//价格
		string strPub;			//出版社
		int    nLeftNum;		//余量
};

//派生类books：
class ScienceBook: public Book {
	public:
		void ShowMe() {
			cout << "Science Book - ID: " << nBookID << ", Name: " << strBookName << ", Price: " << nBookPrice << ", Author: " <<
			     strAuthor << ", Publisher: " << strPub << ", LeftNum: " << nLeftNum << endl;
		}
};

class SocialBook: public Book {
	public:
		void ShowMe() {
			cout << "Social Book - ID: " << nBookID << ", Name: " << strBookName << ", Price: " << nBookPrice << ", Author: " <<
			     strAuthor << ", Publisher: " << strPub << ", LeftNum: " << nLeftNum << endl;
		}
};

class ForeignBook: public Book {
	private:
		string strBookLan;
	public:
		void ShowMe() {
			cout << "Science Book - ID: " << nBookID << ", Name: " << strBookName << ", Price: " << nBookPrice << ", Author: " <<
			     strAuthor << ", Publisher: " << strPub << ", Language: " << strBookLan << ", LeftNum: " << nLeftNum << endl;
		}
		friend istream &operator>>(istream &in, ForeignBook &book) {
			cout << "Enter Language: ";
			in >> book.strBookLan;
			in >> static_cast<Book &>(book);
			return in;
		}
};

class Library {
	private:
		vector<Book *> books; //vector容器实现books的不同类存储

	public:
		void Add(Book *book) {
			books.push_back(book);
		}

		void Lend(int bookId, int quantity) {
			for (auto &book : books) {
				if (book->GetBookID() == bookId) {
					if (book->GetLeftNum() >= quantity) {
						book->SetLeftNum(book->GetLeftNum() - quantity) ;
						cout << "Book(s) successfully lent out!" << endl;
						return;
					} else {
						cout << "Insufficient LeftNum!" << endl;
						return;
					}
				}
			}
			cout << "Book not found!" << endl;
		}

		void Return(int bookId, int quantity) {
			for (auto &book : books) {
				if (book->GetBookID() == bookId) {
					book->SetLeftNum(book->GetLeftNum() - quantity);
					cout << "Book(s) successfully returned!" << endl;
					return;
				}
			}
			cout << "Book not found!" << endl;
		}

		void Search(int bookId) {
			for (auto &book : books) {
				if (book->GetBookID() == bookId) {
					book->ShowMe();
					return;
				}
			}
			cout << "Book not found!" << endl;
		}
};

Book::Book() {

};

Book::Book(int nBookID, string strBookName, string strAuthor, string strPub, int nBookPrice, int nLeftNum) {
	nBookID = nBookID;
	strBookName = strBookName;
	nBookPrice = nBookPrice;
	strAuthor = strAuthor;
	strPub = strPub;
	nLeftNum = nLeftNum;
}

Book::~Book() {
}

int Book::GetBookID() {
	return nBookID;
}

void Book::SetBookID(int nID) {
	nBookID = nID;
}

void Book::SetBookName(string strName) {
	strBookName = strName;
}

string Book::GetAuthor() {
	return strAuthor;
}

void Book::SetAuthor(string strAuthor) {
	strAuthor = strAuthor;
}

int  Book::GetBookPrice() {
	return nBookPrice;
}

void Book::SetBookPrice(int nPrice) {
	nBookPrice = nPrice;
}

string Book::GetPub() {
	return strPub;
}

void Book::SetPub(string strPub) {
	strPub = strPub;
}

int Book::GetLeftNum() {
	return nLeftNum;
}

void Book::SetLeftNum(int nLeftNum) {
	nLeftNum = nLeftNum;
}

istream &operator>>(istream &in, Book &book) {////重载>>函数
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



int main() {
	Library library;

	// Test adding books
	ScienceBook sciBook;
	cout << "Enter details for a Science Book:" << endl;
	cin >> sciBook;
	library.Add(&sciBook);

	library.Lend(123, 2);

	library.Return(123, 1);

	library.Search(123);


	return 0;
}

