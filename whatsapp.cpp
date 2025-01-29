// Create a whats app as following
#define getType
// Users have contacts and can chat with any contact
// Messaging in text audio and video
// Users can see the status of all the contacts
// Users can post status
// Users have contacts and can chat with any contact
// Messaging in text audio and video
// Users can see the status of all the contacts
// Users can post status
// Users have contacts and can chat with any contact
// Messaging in text audio and video
// Users can see the status of all the contacts
// Users can post status
// Users have contacts and can chat with any contact
// Messaging in text audio and video
// Users can see the status of all the contacts
// Users can post status

// Status can be text and image


#include <iostream>
#include <vector>
#include <string>
using namespace std;

// DIFFERENT GENDER TYPES
enum GenderType
{
    MALE,
    FEMALE
};


// Derived TextMessage

// HUMAN CLASS FOR USER AND ADMIN
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

    virtual ~Human() {}
};

// USER CLASS INHERITED FROM HUMAN
class User : public Human
{
    bool isOnline;

public:
    User(string name, bool isOnline, GenderType typeOfGender) : Human(name, typeOfGender) {
        this->isOnline = isOnline;
    }

    //GETTERS AND SETTERS
    string getName()
    {
        return name;
    }

    bool getIsOnline()
    {
        return isOnline;
    }

    void setIsOnline(bool isOnline)
    {
        this->isOnline = isOnline;
    }
};

//Contact Manager class
class ContactManagement
{
    public:
    //ADD CONTACT TO USER CONTACT LIST
    void addContact(User* user,User* contact,unordered_map<User*,vector<User*>>& contacts){
        if(user==contact){
            cout<<"User cannot add himself as contact "<<endl;//base case to handle the edge 
            return;
        }
       contacts[user].push_back(contact);
    }

    //REMOVE CONTACT FROM USER CONTACT LIST
    void removeContact(User* user,User* contact,unordered_map<User*,vector<User*>>& contacts){
        for(auto it=contacts[user].begin();it!=contacts[user].end();++it){
            if((*it)==contact){
                contacts[user].erase(it);
                return;
            }
        }
    }

    //SHOW CONTACTS OF USER
    void showContacts(unordered_map<User*,vector<User*>>& contacts){
        for(auto it:contacts){
            cout<<it.first->getName()<<" contacts are - ";
            for(auto it1:it.second){
                cout<<it1->getName()<<" ";
            }
            cout<<endl;
        }
    }

};
class TextMessage  {
    string text;
   
};

class AudioMessage  {
    string audio;

};

class VideoMessage{
    string avdfile;
}

class ChatManagement
{
    public:
void sendMessage(User* sender, User* receiver, Message* message, unordered_map<User*, vector<User*>>& contacts) {
        if ()
        }

        // Dynamic Casting
        if (dynamic_cast<TextMessage*>(message)) {
            //call test msg 
        } 
        else if (dynamic_cast<AudioMessage*>(message)) {
           //o messages
        } 
        else if (dynamic_cast<VideoMessage*>(message)) {
           //call video sg
        } 
        else {
            cout << "Unknown message type" << endl;
        }
    }
;

class Status{
    string status;
    string type;
    public:
   if (status.type=="audio")
   {
    //call status audio
   }
   

    //GETTERS
    string getStatus(){
        return status;
    }

    //GETTERS
    string getImage(){
        return image;
    }
};

// Base Status Class 
class Status {
 protected:
    string content;
 public:
    Status(string text) : content(text) {}
    virtual ~Status() {}
    virtual string getType() = 0;
    virtual string getContent() { return content; }
};

// Derived TextStatus
class TextStatus : public Status {
public:
    TextStatus(string text) : Status(text) {}
    string  const override { return "Text"; }
};

// Derived AudioStatus
class AudioStatus : public Status {
public:
    AudioStatus(string audio) : Status(audio) {}
    string getType() const override { return "Audio"; }
};

// Derived VideoStatus
class VideoStatus : public Status {
public:
    VideoStatus(string video) : Status(video) {}
    string getType() const override { return "Video"; }
};

// Status Management Class
class StatusManagement {
public:
    // ADD STATUS TO USER
    void addStatus(User* user, unordered_map<User*, Status*>& statusMap, string text, string type = "Text") {
        if (statusMap[user]) {
            delete statusMap[user];  // Clean up previous status
        }

        if (type == "Audio") {
            statusMap[user] = new AudioStatus(text);
        }
        else if (type == "Video") {
            statusMap[user] = new VideoStatus(text);
        } 
        else {
            statusMap[user] = new TextStatus(text);
        }

        cout << user->getName() << " added " << type << " status: " << text << endl;
    }
}
//User Management class
class UserManagement
{
public:
    //ADD USER TO USER LIST
    void addUser(User *user, vector<User *> &users)//user wale db me add hora ha
    {
            users.push_back(user);
            return;
    }

    //SHOW USER DETAILS
    void showUserDetails(vector<User *> &users)
    {
        for (auto &it : users)
        {
            cout << it->getName() << endl;
        }
    }
};

//Whatsapp class
class Whatsapp{
    public:

    //ALL DB
    vector<User*> users;
    unordered_map<User*,vector<User*>> contacts;
    unordered_map<User*,Status*> status;
    
    ContactManagement contactManagement;
    ChatManagement chatManagement;
    StatusManagement statusManagement;   
    UserManagement userManagement;
};

void testSystem()
{   
    //CREATING OBJECT OF WHATSAPP
    Whatsapp whatsapp;

    //CREATING USERS
    User* user1=new User("User1",1,MALE);
    User* user2=new User("User2",1,FEMALE);
    User* user3=new User("User3",1,MALE);
    User* user4=new User("User4",1,FEMALE);
    User* user5=new User("User5",1,MALE);
    User* user6=new User("User6",1,FEMALE);

    //ADDING USERS TO WHATSAPP
    whatsapp.userManagement.addUser(user1,whatsapp.users);
    whatsapp.userManagement.addUser(user2,whatsapp.users);
    whatsapp.userManagement.addUser(user3,whatsapp.users);
    whatsapp.userManagement.addUser(user4,whatsapp.users);
    whatsapp.userManagement.addUser(user5,whatsapp.users);
    whatsapp.userManagement.addUser(user6,whatsapp.users);

    //ADDING CONTACTS
    whatsapp.contactManagement.addContact(user1,user2,whatsapp.contacts);
    whatsapp.contactManagement.addContact(user1,user3,whatsapp.contacts);
    whatsapp.contactManagement.addContact(user1,user4,whatsapp.contacts);
    whatsapp.contactManagement.addContact(user2,user5,whatsapp.contacts);

   

    whatsapp.chatManagement.sendMessage(user1,user2,"Hello",whatsapp.contacts);
    whatsapp.statusManagement.addStatus(user2,whatsapp.status,"Hello","image");
    whatsapp.statusManagement.addStatus(user3,whatsapp.status,"Hello-3","image");
    whatsapp.statusManagement.viewStatus(user1,whatsapp.contacts,whatsapp.status);


}

int main()
{
    
    testSystem();
    return 0;
}