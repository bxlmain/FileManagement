#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


int main1() {

    setlocale(LC_ALL, "Russian");

    string filePath;
    string searchWord;
    string word;
    int count = 0;

    cout << "Введите путь к файлу: ";
    cin >> filePath;

    cout << "Введите слово для поиска: ";
    cin >> searchWord;

    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла." << endl;
        return 1;
    }

    while (file >> word) {
        if (word == searchWord) {
            ++count;
        }
    }

    file.close();

    cout << "Слово \\"" << searchWord << \\"" встречается в файле " << count << " раз." << endl;

    return 0;
}


struct Book {
    string id;
    string author;
    string title;
    int pages;
};

void printMenu() {

    setlocale(LC_ALL, "Russian");
    
    cout << "1. Добавить новую книгу" << endl;
    cout << "2. Просмотреть все книги" << endl;
    cout << "3. Удалить книгу" << endl;
    cout << "4. Найти книгу" << endl;
    cout << "5. Редактировать книгу" << endl;
    cout << "6. Выйти" << endl;
}

vector<Book> readBooksFromFile(const string& filename) {
    vector<Book> books;
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            Book book;
            istringstream iss(line);
            iss >> book.id >> book.author >> book.title >> book.pages;
            books.push_back(book);
        }
        file.close();
    }
    return books;
}

void writeBooksToFile(const vector<Book>& books, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const Book& book : books) {
            file << book.id << " " << book.author << " " << book.title << " " << book.pages << endl;
        }
        file.close();
    }
}

void addBook(vector<Book>& books) {
    Book newBook;
    cout << "Введите ID книги: ";
    cin >> newBook.id;
    cout << "Введите автора книги: ";
    cin.ignore();
    getline(cin, newBook.author);
    cout << "Введите название книги: ";
    getline(cin, newBook.title);
    cout << "Введите количество страниц: ";
    cin >> newBook.pages;
    books.push_back(newBook);
    cout << "Книга успешно добавлена!" << endl;
}

void viewBooks(const vector<Book>& books) {
    if (books.empty()) {
        cout << "Каталог книг пуст." << endl;
    }
    else {
        cout << "Список книг:" << endl;
        for (const Book& book : books) {
            cout << "ID: " << book.id << endl;
            cout << "Автор: " << book.author << endl;
            cout << "Название: " << book.title << endl;
            cout << "Количество страниц: " << book.pages << endl;
            cout << endl;
        }
    }
}

void deleteBook(vector<Book>& books) {
    string bookID;
    cout << "Введите ID книги, которую нужно удалить: ";
    cin >> bookID;
    int index = -1;
    for (int i = 0; i < books.size(); i++) {
        if (books[i].id == bookID) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        books.erase(books.begin() + index);
        cout << "Книга успешно удалена!" << endl;
    }
    else {
        cout << "Книга с таким ID не найдена." << endl;
    }
}

void searchBook(const vector<Book>& books) {
    string bookID;
    cout << "Введите ID книги, которую надо найти: ";
    cin >> bookID;
    bool found = false;
    for (const Book& book : books) {
        if (book.id == bookID) {
            cout << "Книга найдена:" << endl;
            cout << "ID: " << book.id << endl;
            cout << "Автор: " << book.author << endl;
            cout << "Название: " << book.title << endl;
            cout << "Количество страниц: " << book.pages << endl;
            cout << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Книга с таким ID не найдена." << endl;
    }
}

void editBook(vector<Book>& books) {
    string bookID;
    cout << "Введите ID книги, которую нужно отредактировать: ";
    cin >> bookID;
    int index = -1;
    for (int i = 0; i < books.size(); i++) {
        if (books[i].id == bookID) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        Book& book = books[index];
        cout << "Текущая информация о книге:" << endl;
        cout << "ID: " << book.id << endl;
        cout << "Автор: " << book.author << endl;
        cout << "Название: " << book.title << endl;
        cout << "Количество страниц: " << book.pages << endl;
        cout << endl;
        cout << "Введите новую информацию о книге:" << endl;
        cout << "Введите новый ID: ";
        cin >> book.id;
        cout << "Введите нового автора: ";
        cin.ignore();
        getline(cin, book.author);
        cout << "Введите новое название: ";
        getline(cin, book.title);
        cout << "Введите новое количество страниц: ";
        cin >> book.pages;
        cout << "Книга успешно отредактирована!" << endl;
    }
    else {
        cout << "Книга с таким ID не найдена." << endl;
    }
}

int main() {
    vector<Book> books = readBooksFromFile("books.txt");

    int choice;
    do {
        printMenu();
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook(books);
            break;
        case 2:
            viewBooks(books);
            break;
        case 3:
            deleteBook(books);
            break;
        case 4:
            searchBook(books);
            break;
        case 5:
            editBook(books);
            break;
        case 6:
            writeBooksToFile(books, "books.txt");
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 6);

    return 0;
}
