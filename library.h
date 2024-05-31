#include "book.h"
#include <fstream>
using namespace std;

class Library {
private:
    vector<Book*> books;//vector容器实现books的不同类存储

public:
    void Add(Book* book) {
        books.push_back(book);
    }

    void Lend(int bookId, int quantity) {
        for (auto& book : books) {
            if (book->GetBookID() == bookId) {
                if (book->GetLeftNum() >= quantity) {
                    book->SetLeftNum(book->GetLeftNum()- quantity) ;
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
        for (auto& book : books) {
            if (book->GetBookID() == bookId) {
                book->SetLeftNum(book->GetLeftNum()- quantity);
                cout << "Book(s) successfully returned!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    void Search(int bookId) {
        for (auto& book : books) {
            if (book->GetBookID() == bookId) {
                book->ShowMe();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
};
