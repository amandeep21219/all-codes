

using namespace std;

class Book {
private:
    int bookId;
    string barcode;
    string title;
    int authorId;


public:
    Book(int id, string code, string name, int author)
        : bookId(id), barcode(code), title(name), authorId(author) {}

    int getBookId() { return bookId; }
    string getTitle() { return title; }
};

class User {
private:
    int userId;
    int college;
    vector<int> takenBooks;
    vector<int> returnedBooks;

public:
    User(int id, int roll) : userId(id), college(roll) {}

    void takeBook(int bookId) { takenBooks.push_back(bookId); }
    void returnBook(int bookId) {
        returnedBooks.push_back(bookId);
        takenBooks.erase(remove(takenBooks.begin(), takenBooks.end(), bookId), takenBooks.end());
    }

     vector<int> getTakenBooks() { return takenBooks; }
};

class LibraryManager {
private:
    unordered_map<int, Book> books;                 // Map of bookId to Book object
    unordered_map<int, User> users;                 // Map of userId to User object
    unordered_map<int, vector<int>> rackBookMap;    // Map of rackNo to list of bookIds

public:
    void addBook(int id, string barcode, string title, int authorId, int rackNo) {
        books[id] = Book(id, barcode, title, authorId);
        rackBookMap[rackNo].push_back(id);
    }

    void addUser(int userId, int rollNo) { users[userId] = User(userId, rollNo); }

    Book* findBook(int bookId) {
        if (books.find(bookId) != books.end()) {
            return &books[bookId];
        }
        return NULL;
    }

    bool isBookAvailable(int bookId) {
        for ( auto [rackNo, bookList] : rackBookMap) {
            if (find(bookList.begin(), bookList.end(), bookId) != bookList.end()) {
                return true;
            }
        }
        return false;
    }

    void issueBook(int userId, int bookId) {
        if (users.find(userId) != users.end() && books.find(bookId) != books.end()) {
            if (isBookAvailable(bookId)) {
                users[userId].takeBook(bookId);
                for (auto [rackNo, bookList] : rackBookMap) {
                    auto it = find(bookList.begin(), bookList.end(), bookId);
                    if (it != bookList.end()) {
                        bookList.erase(it);  // Remove the book from the rack
                        break;
                    }
                }
                cout << "Book issued " << endl;
            } else {
                cout << "Book isnt available" << endl;
            }
        } else {
            cout << "Invalid user or book " << endl;
        }
    }

    void returnBook(int userId, int bookId, int rackNo, int daysLate) {
        if (users.find(userId) != users.end() && books.find(bookId) != books.end() && rackBookMap.find(rackNo) != rackBookMap.end()) {
            users[userId].returnBook(bookId);
            rackBookMap[rackNo].push_back(bookId);  // Add the book back to the rack
            calculateFine(daysLate);
            cout << "Book returned successfully" << endl;
        } else {
            cout << "Invalid user, book, or rack ID" << endl;
        }
    }

    void calculateFine(int daysLate) {
        int finePerDay = 5;  // Fine per day in currency units
        if (daysLate > 0) {
            cout << "Fine for late return: " << daysLate * finePerDay << endl;
        } else {
            cout << "No fine." << endl;
        }
    }
};

int main() {
    LibraryManager manager;

    // Adding books
    manager.addBook(1, "BC101", "C++ Programming", 101, 5);
    manager.addBook(2, "BC102", "Data Structures", 102, 10);

    // Adding users
    manager.addUser(1, 10101);
    manager.addUser(2, 10102);

    // Issue and return operations
    manager.issueBook(1, 1); // User 1 takes Book 1
    manager.issueBook(2, 1); // User 2 tries to take Book 1 (not available)
    manager.returnBook(1, 1, 5, 3); // User 1 returns Book 1 to Rack 5 after 3 days late
    manager.issueBook(2, 1); // User 2 takes Book 1 after it is returned

    return 0;
}
