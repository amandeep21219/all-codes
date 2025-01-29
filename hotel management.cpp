
// Enums
 class Facilities {
    Breakfast,// we can add new facilites from here
    Buffet,
    washing,
    pet;

    ,lunch;
};

 class Role {
    User,
    Agent,// three types of role
    Administrator
};



// FeedBackService Class
class FeedBackService {
public:
    void feedback() {
        cout << "Please provide feedback";//generate feedback
    }
};

// Room Class defiende with id 
class Room {
private:
    int roomId;
    int rate;
    

public:
    Room(int roomId, int price )
        : roomId(roomId), rate(price) {}

    int getPrice()  { return price; }
     

    string toString()  {
        return "Room { price: " + to_string(price) + ", category: " +  " }";
    }
};

// User Class
class User {
private:
    string name;
    string id;
    Role role;// adding things

public:
    User(string name, Role role, string id)
        : name(name), role(role), id(id) {}

    string getName()  { return name; }
    string getId()  { return id; }
    Role getRole()  { return role; }

    string toString() {
        return "User { name: " + name + ", id: " + id + ", role: " + to_string((role)) + " }";
    }
};

// Hotel Class
class Hotel {
private:
    string hotelName;
    int hotelId;
    string location;
    vector<Room*> rooms;
    unordered_map<string, bool> facilities;

public:
    Hotel(string hotelName, int hotelId, string loc, unordered_map<string, bool> facilities)
        : hotelName(hotelName), hotelId(hotelId), loc(location), facilities(facilities) {}

    string getHotelName()  { return hotelName; }
    int getHotelId()  { return hotelId; }
    string getLocation()  { return location; }
    vector<Room*> getRooms()  { return rooms; }
    unordered_map<string, bool> getFacilities() { return facilities; }
};

// HotelRoomManagement Class
class HotelRoomManagement {
private:
    FeedBackService feedBackService;//will take feedbacks ,add rooms , 
    vector<Room*> rooms;
    unordered_map<Room*, string> reservedRooms;

public:
    

    void addRoom(Room* room) {
        rooms.push_back(room);
    }

    void removeRoom(Room* room) {
        rooms.erase(remove(rooms.begin(), rooms.end(), room), rooms.end());
    }

    vector<Room*> getAllRooms() const {
        return rooms;
    }

    void releaseRoom(User* user, Room* room) {
        if (user->getRole() == Role::User) {
            rooms.push_back(room);
            reservedRooms.erase(room);
        }
    }

    unordered_map<Room*, string> getAllReservations()  {
        return reservedRooms;
    }

    void bookHotelRoom(User* user, Room* room) {
        if (user->getRole() == Role::User) {//user can book it role dekho
            cout << "Room reserved by user: " << user->getName() << "\n";
            feedBackService.feedback();
            reservedRooms[room] = user->getId();
            removeRoom(room);
        } else {
            cout << "Only users can book\n";
        }
    }

    Room* getRoom(int id)  {
        return rooms[id];
    }
};

// HotelsManagement Class
class HotelsManagement {
private:
    HotelRoomManagement hotelRoomManagement;
    unordered_map<Hotel*, vector<Room*>> hotels;

public:
    void removeHotel(Hotel* hotel, User* user) {
        if (user->getRole() == Role::Administrator) {
            hotels.erase(hotel);
        } else {
            cout << "Only admin can remove, sorry";
        }
    }

    void updateHotel(Hotel* hotel, User* user, vector<Room*> rooms) {
        if (user->getRole() == Role::Administrator) {//if role admin then can update the things
            hotels[hotel] = rooms;
        }
    }

    void addHotel(Hotel* hotel, vector<Room*> rooms, User* user) {
        if (user->getRole() == Role::Agent) {
          if ( agetapproval());//if role is agent can request to remove hotel 
              {hotels[hotel] = rooms;}
        }
    }

private:
    bool getapproval() {
       return true;
    }

public:
    vector<Room*> hotelRoomsByLocation(User* user, string hotelName)  {
       vector<Room*> searchResultRooms;
        for ( auto& entry : hotels) {
            Hotel* hotel = entry.first;
            vector<Room*>& rooms = entry.second;
            if (hotel->getName() == hotelName) {
                searchResultRooms.insert(searchResultRooms.end(), rooms.begin(), rooms.end());
            }
        }
        return searchResultRooms;
    }
};

// UserManagement Class
class UserManagement {
private:
    HotelRoomManagement hotelRoomManagement;
    vector<User*> userList;//

public:
    UserManagement() {
        userList = vector<User*>();
    }

    void addUser(User* user) {
        userList.push_back(user);
    }

    void removeUser(User* user) {
        userList.erase(remove(userList.begin(), userList.end(), user), userList.end());
    }

    vector<User*> getAllUsers() {
        return userList;
    }

    bool userHasReservation(User* user) {
        auto allUser = hotelRoomManagement.getAllReservations();
        for (const auto& entry : allUser) {
            if (entry.second == user->getId()) return true;
        }
        return false;
    }

   
       
        
    
};

int main() 
   