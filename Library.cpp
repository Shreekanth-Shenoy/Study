#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Book {
public:
    Book(std::string title, std::string author) : title(title), author(author), available(true) {}

    std::string getTitle() const {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }

    bool isAvailable() const {
        return available;
    }

    void setAvailable(bool status) {
        available = status;
    }

private:
    std::string title;
    std::string author;
    bool available;
};

class User {
public:
    User(std::string name) : name(name) {}

    std::string getName() const {
        return name;
    }

    std::vector<std::string> getBorrowedBooks() const {
        return borrowedBooks;
    }

    void borrowBook(const std::string& bookTitle) {
        borrowedBooks.push_back(bookTitle);
    }

    void returnBook(const std::string& bookTitle) {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), bookTitle);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }

private:
    std::string name;
    std::vector<std::string> borrowedBooks;
};

class Library {
public:
    static Library& getInstance() {
        static Library instance;
        return instance;
    }

    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAvailableBooks() const {
        std::cout << "Available Books:\n";
        for (const auto& book : books) {
            if (book.isAvailable()) {
                std::cout << book.getTitle() << " by " << book.getAuthor() << "\n";
            }
        }
    }

    void searchBooksByAuthor(const std::string& author) const {
        std::cout << "Books by " << author << ":\n";
        for (const auto& book : books) {
            if (book.getAuthor() == author) {
                std::cout << book.getTitle() << "\n";
            }
        }
    }

    void displayBorrowedBooks(const User& user) const {
        std::cout << user.getName() << "'s Borrowed Books:\n";
        for (const auto& bookTitle : user.getBorrowedBooks()) {
            std::cout << bookTitle << "\n";
        }
    }

    void borrowBook(const std::string& title, User& user) {
        for (auto& book : books) {
            if (book.getTitle() == title && book.isAvailable()) {
                book.setAvailable(false);
                user.borrowBook(title);
                std::cout << user.getName() << " has borrowed " << book.getTitle() << "\n";
                return;
            }
        }
        std::cout << "Book not available.\n";
    }

    void returnBook(const std::string& title, User& user) {
        for (auto& book : books) {
            if (book.getTitle() == title && !book.isAvailable()) {
                book.setAvailable(true);
                user.returnBook(title);
                std::cout << user.getName() << " has returned " << book.getTitle() << "\n";
                return;
            }
        }
        std::cout << "Invalid book title or book already available.\n";
    }

private:
    Library() {} // private constructor for singleton pattern
    std::vector<Book> books;
    std::vector<User> users;
};

int main() {
    Library& library = Library::getInstance();

    Book book1("The Catcher in the Rye", "J.D. Salinger");
    Book book2("To Kill a Mockingbird", "Harper Lee");

    User user1("Alice");
    User user2("Bob");

    library.addBook(book1);
    library.addBook(book2);
    library.addUser(user1);
    library.addUser(user2);

    library.displayAvailableBooks();
    library.searchBooksByAuthor("J.D. Salinger");

    library.borrowBook("The Catcher in the Rye", user1);
    library.borrowBook("To Kill a Mockingbird", user2);

    library.displayBorrowedBooks(user1);
    library.displayBorrowedBooks(user2);

    library.returnBook("The Catcher in the Rye", user1);
    library.displayAvailableBooks();

    return 0;
}
