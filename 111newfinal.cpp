#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;
/// @brief ///////////////////////////////////////////////////////////////////////////////////////BOOK的基类定义
class Books {
public:
    string bookID;       //图书编号////用public方便后续访问
    string title;        //书名
    double price;        //价格
    string author;       //作者
    string publisher;    //出版社
    int stock;           //库存
 
    /// @brief //
    /// @param id 
    /// @param t 
    /// @param p 
    /// @param a 
    /// @param pub 
    /// @param s 
    Books(string id, string t, double p, string a, string pub, int s)
        : bookID(id), title(t), price(p), author(a), publisher(pub), stock(s) {}
    /// @brief /////////
    ///////虚函数实现ShowMe后续重载////////////
    virtual void ShowMe() = 0;

    /// @brief //////
    /// @param in 
    /// @param book 
    /// @return 
    /////////////////重载了输入流可以直接对内容进行修改////////////////////////////////////////
    friend istream& operator>>(istream& in, Books& book) {
        cout << "Enter Book ID: ";
        in >> book.bookID;
        cout << "Enter Book Title: ";
        in.ignore();
        getline(in, book.title);
        cout << "Enter Author: ";
        getline(in, book.author);
        cout << "Enter Publisher: ";
        getline(in, book.publisher);
        cout << "Enter Price: ";
        in >> book.price;
        cout << "Enter Stock: ";
        in >> book.stock;
        return in;
    }

};

/////////////////////////////////////////////
/// @brief //////////////共有继承派生类///////
////////////////////////////////////////////
class ScienceBook : public Books {
public:
    ScienceBook(string id, string t, double p, string a, string pub, int s)
        : Books(id, t, p, a, pub, s) {}

    void ShowMe() override {
        cout << "Book ID: " << bookID << ", Title: " << title << ", Science Book" << endl;
    }
};


class SocialBook : public Books {
public:
    SocialBook(string id, string t, double p, string a, string pub, int s)
        : Books(id, t, p, a, pub, s) {}

    void ShowMe() override {
        cout << "Book ID: " << bookID << ", Title: " << title << ", Social Science Book" << endl;
    }
};


class ForeignBook : public Books {
public:
    string language;

    ForeignBook(string id, string t, double p, string a, string pub, int s, string lang)
        : Books(id, t, p, a, pub, s), language(lang) {}

    void ShowMe() override {
        cout << "Book ID: " << bookID << ", Title: " << title << ", Language: " << language << ", Foreign Book" << endl;
    }
};


/// @brief ///////////////////////////////////////
//////////////////////////////////////////////////
///////////////////LIBRARY类书写/////////////////////
class Library {
private:
    vector<Books*> books;    ///////////用vector容器实现对书的类不同而分开存储。基类book*可以识别后续派生类

public:
///////////////////////////////////////////ADD//////////////////////////////////////
    void Add(Books* book) {
        for (auto& b : books) {      ///////用auto代替迭代器更简单////////
            if (b->bookID == book->bookID) {
                b->stock += book->stock;
                return;
            }
        }
        books.push_back(book);
    }
/////////////////////////////////////////////////LEND////////////////////////////////
    bool Lend(string id, int quantity) {
        for (auto& b : books) {
            if (b->bookID == id && b->stock >= quantity) {
                b->stock -= quantity;
                cout << "Lended " << quantity << " book(s)." << endl;
                return true;
            }
        }
        cout << "Book not available." << endl;
        return false;
    }
///////////////////////////////////////////////RETURN///////////////////////////////////////
    void Return(string id, int quantity) {
        for (auto& b : books) {
            if (b->bookID == id) {
                b->stock += quantity;
                return;
            }
        }
    }
//////////////////////////////////////////////SEARCH////////////////////////////////////////
    void Search(string id) {
        for (auto& b : books) {
            if (b->bookID == id) {
                b->ShowMe();
                cout << "Stock: " << b->stock << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }
/////////////////////////////////////////////SAVEBOOKS////////////////////////////////////////
    void SaveBooks() {
        ofstream file("library.txt");      
        for (auto& b : books) {
            file << b->bookID << "," << b->title << "," << b->price << "," << b->author << "," << b->publisher << "," << b->stock << endl;
        }
        file.close();
    }
/////////////////////////////////////////////LOARDBOOKS///////////////////////////////////////
    void LoadBooks() {
        ifstream file("library.txt");
        string line, id, title, author, publisher;
        double price;
        int stock;

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, title, ',');
            ss >> price;
            ss.ignore();
            getline(ss, author, ',');
            getline(ss, publisher, ',');
            ss >> stock;
            ss.ignore();
            Add(new ScienceBook(id, title, price, author, publisher, stock)); // Default to ScienceBook for simplicity
        }
        file.close();
    }
};

int main() {   
    ///////////////////////////根据提示输入对应字符/////////////////////////////////
    cout << "*********************DESIGNED BY CUI******************************" << endl;
    cout << "*****************************************************************" << endl;
    cout << "Welcome to the Library Management System" << endl;
    cout << "Here are the available commands:" << endl;
    cout << " 1. Enter 'add' to add books." << endl;
    cout << " 2. Enter 'lend' to lend books." << endl;
    cout << " 3. Enter 'return' to return books." << endl;
    cout << " 4. Enter 'search' to search for a specific book." << endl;
    cout << " 5. Enter 'save' to save the current library state to a file." << endl;
    cout << " 6. Enter 'quit' to exit the program." << endl;
    cout << "*****************************************************************" << endl;
    Library lib;
    lib.LoadBooks();

    string command;
    while (true) {
        cout << "\nPlease enter a command: ";    ///////输入对应string达成响应/////////
        cin >> command;

        if (command == "add") {
            string id, title, author, publisher, type;
            double price;
            int stock;
            cout << "Enter book type (science/social/foreign): ";////限制只允许这几个输入/////
            cin >> type;
            cout << "Enter book ID: ";
            cin >> id;
            cout << "Enter title: ";
            cin.ignore();
            getline(cin, title); /////getline捕获输入流////////
            cout << "Enter author: ";
            getline(cin, author);
            cout << "Enter publisher: ";
            getline(cin, publisher);
            cout << "Enter price: ";
            cin >> price;
            cout << "Enter stock: ";
            cin >> stock;
            //////////健壮性体现/////////////////////////

            if (type == "science") {
                lib.Add(new ScienceBook(id, title, price, author, publisher, stock));
            } else if (type == "social") {
                lib.Add(new SocialBook(id, title, price, author, publisher, stock));
            } else {
                cout << "Invalid book type entered." << endl;
            }
            ///////////////////////////////////
        } else if (command == "lend") {
            string id;
            int quantity;
            cout << "Enter book ID to lend: ";
            cin >> id;
            cout << "Enter quantity: ";
            cin >> quantity;
            lib.Lend(id, quantity);
            //////////////////////////////////////////////
        } else if (command == "return") {
            string id;
            int quantity;
            cout << "Enter book ID to return: ";
            cin >> id;
            cout << "Enter quantity: ";
            cin >> quantity;
            lib.Return(id, quantity);
            ///////////////////////////////////////////////
        } else if (command == "search") {
            string id;
            cout << "Enter book ID to search: ";
            cin >> id;
            lib.Search(id);
            /////////////////////////////////////////////////
        } else if (command == "save") {
            lib.SaveBooks();
            cout << "Library data saved." << endl;
            /////////////////////////////////////////////////
        } else if (command == "quit") {
            cout << "Exiting program." << endl;
            break;
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }

    return 0;
}