#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// Message class to handle text, audio, and video messages
class Message {
public:
    virtual void display() = 0;
};

class TextMessage : public Message {
private:
    string text;
public:
    TextMessage(string txt) : text(txt) {}
    void display() override {
        cout << "Text: " << text << endl;
    }
};

class AudioMessage : public Message {
private:
    string audioFile;
public:
    AudioMessage(string audio) : audioFile(audio) {}
    void display() override {
        cout << "Audio: " << audioFile << endl;
    }
};

class VideoMessage : public Message {
private:
    string videoFile;
public:
    VideoMessage(string video) : videoFile(video) {}
    void display() override {
        cout << "Video: " << videoFile << endl;
    }
};

// Status class to handle text and image statuses
class Status {
public:
    virtual void display() = 0;
};

class TextStatus : public Status {
private:
    string text;
public:
    TextStatus(string txt) : text(txt) {}
    void display() override {
        cout << "Status Text: " << text << endl;
    }
};

class ImageStatus : public Status {
private:
    string imageFile;
public:
    ImageStatus(string img) : imageFile(img) {}
    void display() override {
        cout << "Status Image: " << imageFile << endl;
    }
};


// User class to handle user details and contacts
class User {
private:
    int userId;
    string name;
    vector<User*> contacts;
    vector<Message*> messages;
    vector<Status*> statuses;

public:
    User(int id, string uname) : userId(id), name(uname) {}

    void addContact(User* contact) {
        contacts.push_back(contact);
    }

    void sendMessage(User* contact, Message* message) {
        contact->receiveMessage(message);
    }

    void receiveMessage(Message* message) {
        messages.push_back(message);
    }

    void postStatus(Status* status) {
        statuses.push_back(status);
    }

    void viewStatuses() {
        for (auto status : statuses) {
            status->display();
        }
    }

    void displayMessages() {
        for (auto message : messages) {
            message->display();
        }
    }
};

int main() {
   