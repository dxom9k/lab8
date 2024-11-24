#include <iostream>
#include <fstream>
#include <cstring>
#include<windows.h>
using namespace std;

const int MAX_BOOKS = 100;
const int MAX_LENGTH = 100;

struct Book {
    char author[MAX_LENGTH];
    char title[MAX_LENGTH];
    int copies;
    double price;
    int year;
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Book books[MAX_BOOKS];
    int bookCount = 0;

    ifstream textFile("books.txt");


    while (!textFile.eof() && bookCount < MAX_BOOKS) {
        textFile.getline(books[bookCount].author, MAX_LENGTH);
        textFile.getline(books[bookCount].title, MAX_LENGTH);
        textFile >> books[bookCount].copies;
        textFile >> books[bookCount].price;
        textFile >> books[bookCount].year;
        textFile.ignore();  
        bookCount++;
    }
    textFile.close();

    int maxCopiesIndex = 0;
    for (int i = 1; i < bookCount; i++) {
        if (books[i].copies > books[maxCopiesIndex].copies) {
            maxCopiesIndex = i;
        }
    }

    cout << "Книга з найбільшим тиражем:" << endl;
    cout << "Автор: " << books[maxCopiesIndex].author << endl;
    cout << "Назва: " << books[maxCopiesIndex].title << endl;
    cout << "Тираж: " << books[maxCopiesIndex].copies << endl;
    cout << "Ціна: " << books[maxCopiesIndex].price << endl;
    cout << "Рік видання: " << books[maxCopiesIndex].year << endl;

 
    ofstream binaryFile("books.bin", ios::binary);

    for (int i = 0; i < bookCount; i++) {
        size_t authorLength = strlen(books[i].author);
        binaryFile.write(reinterpret_cast<const char*>(&authorLength), sizeof(authorLength));
        binaryFile.write(books[i].author, authorLength);

        size_t titleLength = strlen(books[i].title);
        binaryFile.write(reinterpret_cast<const char*>(&titleLength), sizeof(titleLength));
        binaryFile.write(books[i].title, titleLength);

        binaryFile.write(reinterpret_cast<const char*>(&books[i].copies), sizeof(books[i].copies));
        binaryFile.write(reinterpret_cast<const char*>(&books[i].price), sizeof(books[i].price));
        binaryFile.write(reinterpret_cast<const char*>(&books[i].year), sizeof(books[i].year));
    }

    binaryFile.close();

    return 0;
}
