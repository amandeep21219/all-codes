

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;


enum GenderType
{
    MALE,
    FEMALE
};

// class book for book details
class Book
{
protected:
    string title;
    string author;
    string subject;
    string publicationDate;
    string barCode;

public:
    Book(string title, string author, string subject, string publicationDate, string barCode)
    {
        this->title = title;
        this->author = author;
        this->subject = subject;
        this->publicationDate = publicationDate;
        this->barCode = barCode;
    }

    //GETTERS AND SETTERS
    string getTitle()
    {
        return title;
    }

    string getAuthor()
    {
        return author;
    }

    string getSubject()
    {
        return subject;
    }

    string getPublicationDate()
    {
        return publicationDate;
    }

    
    string getBarCode()
    {
        return barCode;
    }

    //VERIFY BARCODE
    bool verifyBarCode(string barCode)
    {
        return this->barCode == barCode;
    }
};

//HUMAN CLASS FOR DEFINING THE HUMANS
class Human
{
protected:
    string name;
    GenderType typeOfGender;

public:
    Human(string name, GenderType typeOfGender)
    {
        this->name = name;
        this->typeOfGender = typeOfGender;
    }

     
};

//USER CLASS INHERITED FROM HUMAN
class User : public Human
{
    string barCode;//user barcode 

public:
    User(string name, string barCode, GenderType typeOfGender) : Human(name, typeOfGender) {
        this->barCode = barCode;
    }

    //GETTERS AND SETTERS
    string getName()
    {
        return name;
    }

    string getBarCode()
    {
        return barCode;
    }

    //VERIFYING THE BAR CODES
    bool verifyBarCode(string barCode)
    {
        return this->barCode == barCode;
    }
};

//ADMIN CLASS INHERITED FROM USER
class Admin : public User
{
public:
    Admin(string name, string barCode, GenderType typeOfGender) : User(name, barCode, typeOfGender) {}
};

//BOOK MANAGEMENT CLASS
class UserManagement
{
public:

    //ADD USER AFTER CHECKING WHETHER ADMIN IS ADDING OR NOT
    void addUser(Human *admin, User *user, vector<User *> &users)
    {
        if (dynamic_cast<Admin *>(admin))
        {
            users.push_back(user);
            return;
        }
        cout << "Only admin can add user" << endl;
    }

    //SHOW USER DETAILS FROM USER DB
    void showUserDetails(vector<User *> &users)
    {
        for (auto &it : users)
        {
            cout << it->getName() << endl;
        }
    }
};

//BOOK CLASS
class BookManagement
{
public:
    //ADD BOOK AFTER CHECKING WHETHER ADMIN IS ADDING OR NOT
    void addBook(Human *admin, Book *book, vector<Book *> &books)
    {
        if (dynamic_cast<Admin *>(admin))
        {
            books.push_back(book);
            return;
        }
        cout << "Only admin can add book" << endl;
    }

    //SHOW BOOK DETAILS FROM BOOK DB
    void showBookDetails(vector<Book *> &books)
    {
        for (auto &it : books)
        {
            cout << it->getTitle() << endl;
        }
    }

    //SEARCH BOOK BY TITLE  
    void searchBookByTitle(string title, vector<Book *> &books)
    {
        for (auto &book : books)
        {
            if (book->getTitle() == title)
            {
                cout << "Found book:" << title << "by" << book->getAuthor() << "." << endl;
                return;
            }
        }
        cout << "No book found with title '" << title << "'." << endl;
    }

    //SEARCH BOOK BY AUTHOR
    void searchBookByAuthor(string author, vector<Book *> &books)
    {
        bool found = false;
        for (auto &book : books)
        {
            if (book->getAuthor() == author)
            {
                found = true;
                cout << "Books by '" << author << "': " << book->getTitle() << endl;
            }
        }

        if (!found)
        {
            cout << "No book found with author: " << author << endl;
        }
    }

    //SEARCH BOOK BY PUBLICATION DATE
    void searchBookByPublicationDate(string publicationDate, vector<Book *> &books)
    {
        bool found = false;
        for (auto &book : books)
        {
            if (book->getPublicationDate() == publicationDate)
            {
                found = true;
                cout << "Books by '" << publicationDate << "': " << book->getTitle() << endl;
            }
        }
        if (!found)
        {
            cout << "No book found with publication date: " << publicationDate << endl;
        }
    }


    //Assigning book to a user having subscription
    void checkOutBook(User user, Book *book, unordered_map<Book *, pair<User *, int>> &assigned, unordered_map<User *, bool> &subscriptionDB, unordered_map<User *, int> &numberOfBooksCheckedOut,vector<Book> &books, int allowedDays = 10,int maxBookAllowed=5)
    {      
        //CHECKING IF BOOK IS REGISTERED IN THE LIBRARY
       if(find(books.begin(),books.end(),book)==books.end()){
           cout<<"Book not registered in the library"<<endl;
           return;
       }
        //CHECKING IF BOOK IS ALREADY ASSIGNED
        if (assigned.find(book) != assigned.end())
        {
            cout << "Book already assigned" << endl;
            return;
        }
        //CHECKING IF USER HAS SUBSCRIPTION
        if ((subscriptionDB.find(user) == subscriptionDB.end()) || (!subscriptionDB[user]))
        {
            cout << "User not subscribed" << endl;
            return;
        }
        //CHECKING IF USER HAS REACHED MAX BOOK LIMIT
        if (numberOfBooksCheckedOut.find(user) != numberOfBooksCheckedOut.end() && numberOfBooksCheckedOut[user] >= maxBookAllowed)
        {
            cout << "Maximum books limit reached" << endl;
            return;
        }
        numberOfBooksCheckedOut[user]++;
        assigned[book] = {user, allowedDays};
        cout << "Book assigned" << endl;
    }

    //Submitting book to library by user
    void checkInBook(User *user, Book *book, unordered_map<Book *, pair<User *, int>> &assigned,unordered_map<User *, int> &numberOfBooksCheckedOut)
    {
        //CHECKING IF BOOK IS ASSIGNED
        if (assigned.find(book) == assigned.end())
        {
            cout << "Book was not assigned to anyone" << endl;
            return;
        }
        //CHECKING IF BOOK IS ASSIGNED TO USER
        if (assigned[book].first != user)
        {
            cout << "Book was not assigned to this user" << endl;
            return;
        }
        //CHECKING IF FINE IS TO BE PAID
        if (assigned[book].second < 0)
        {
            cout << "Fine to be paid" << endl;
        }
        numberOfBooksCheckedOut[user]--;
        assigned.erase(book);
        cout << "Book unassigned" << endl;
    }

    
  

    
}
;
//SUBSCRIPTION MANAGEMENT CLASS
class SubscriptionManagement
{
public:

    //Add subscription for user
    void addSubscription(User *user, unordered_map<User *, bool> &subscriptionDB)
    {
        subscriptionDB[user] = true;
        cout << user->getName() << " subscribed" << endl;
    }

    //Remove subscription for user
    void removeSubscription(User *user, unordered_map<User *, bool> &subscriptionDB)
    {
        subscriptionDB[user] = false;
        cout << user->getName() << " unsubscribed" << endl;
    }

    //Check if user has subscription
    bool checkSubscription(User *user, unordered_map<User *, bool> &subscriptionDB)
    {   
        //CHECKING IF USER HAS SUBSCRIPTION
        if (subscriptionDB.find(user) != subscriptionDB.end())
        {
            return subscriptionDB[user];
        }
        return false;
    }

};

//RACK MANAGEMENT CLASS
class RackManagement
{
public:
    //Add book to rack
    void addRack(Book *book, int rackNumber, unordered_map<Book *, int> &rack)
    {
        rack[book] = rackNumber;
        cout << "Book added in rack number " << rackNumber << endl;
    }

    //Remove book from rack
    void removeRack(Book *book, unordered_map<Book *, int> &rack)
    {
        rack.erase(book);
        cout << "Book removed from rack" << endl;
    }

    //Show rack details
    void showRackDetails(unordered_map<Book *, int> &rack)
    {
        for (auto &it : rack)
        {
            cout << it.first->getTitle() << " is in rack number " << it.second << endl;
        }
    }
};

//LIBRARY MANAGEMENT CLASS
class LibraryManagement
{
public:
    //DIFFERENT DATABASES FOR LIBRARY MANAGEMENT
    vector<User *> users;
    vector<Book *> books;
    unordered_map<User *, bool> subscriptionDB;
    unordered_map<Book *, pair<User *, int>> assigned; // pair - number of days
    unordered_map<Book *, int> rack;
    unordered_map<User *, vector<Book *>> reserve;
    unordered_map<User *, int> numberOfBooksCheckedOut;

    //DIFFERENT MANAGEMENT CLASSES
    UserManagement userManagement;
    BookManagement bookManagement;
    SubscriptionManagement subscriptionManagement;
    RackManagement rackManagement;

    
};

//TEST CASES
void testLibraryManagementSystem()
{
    LibraryManagement library;

    // Test Case 1: Add users to the library
    User *user1 = new User("aaa1", "U001", MALE);
    User *user2 = new User("bbb1", "U002", FEMALE);
    Admin *admin = new Admin("Admin", "A001", MALE);
    library.userManagement.addUser(admin, user1, library.users);
    library.userManagement.addUser(admin, user2, library.users);
    // library.userManagement.addUser(user1, user2, library.users);   // Only admin can add user - will not add user
    // library.userManagement.showUserDetails(library.users);

    // Test Case 2: Add books to the library
    // string title, string author, string subject, string publicationDate, string ISBN, string barCode
    Book *book1 = new Book("Title-1","Utkarsh","Subject-1","Publication-1","B001");
    Book *book2 = new Book("Title-2","Tanishka","Subject-2","Publication-2","B002");
    Book *book3 = new Book("Title-3","Author-3","Subject-1","Publication-3","B003");
    Book *book4 = new Book("Title-4","Author-4","Subject-2","Publication-4","B004");
    Book *book5 = new Book("Title-5","Author-5","Subject-3","Publication-5","B005");
    Book *book6 = new Book("Title-6","Author-6","Subject-1","Publication-6","B006");

    // library.bookManagement.addBook(uer1, book1, library.books); // Only admin can add book - will not add book
    library.bookManagement.addBook(admin, book1, library.books);
    library.bookManagement.addBook(admin, book2, library.books);
    library.bookManagement.addBook(admin, book3, library.books);
    library.bookManagement.addBook(admin, book4, library.books);
    library.bookManagement.addBook(admin, book5, library.books);
    library.bookManagement.addBook(admin, book6, library.books);
    
    library.subscriptionManagement.addSubscription(user1, library.subscriptionDB);
    library.subscriptionManagement.addSubscription(user2, library.subscriptionDB);
    

    // 
    library.bookManagement.checkOutBook(user1, book1, library.assigned, library.subscriptionDB, library.numberOfBooksCheckedOut,library.books);
    library.bookManagement.checkOutBook(user1, book2, library.assigned, library.subscriptionDB, library.numberOfBooksCheckedOut,library.books);
    library.bookManagement.checkOutBook(user1, book3, library.assigned, library.subscriptionDB, library.numberOfBooksCheckedOut,library.books);
    library.bookManagement.checkOutBook(user2, book4, library.assigned, library.subscriptionDB, library.numberOfBooksCheckedOut,library.books);
    library.bookManagement.checkOutBook(user2, book5, library.assigned, library.subscriptionDB, library.numberOfBooksCheckedOut,library.books);
    library.bookManagement.checkOutBook(user1, book6, library.assigned, library.subscriptionDB, library.numberOfBooksCheckedOut,library.books);

    
     
  
}

int main()
{
    
    testLibraryManagementSystem();
    return 0;
}