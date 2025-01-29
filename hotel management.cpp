// Test-OOPs
// Hotel Management system
// Problem Statement :
// Application for Hotel reservation. We will take the selection criteria from user and display the hotels list for user basing on the criteria. User can book
// the room if there is availability of the rooms in that particular hotel. There are three different types of user roles for the application they are
//  administrator , hotel agent and normal user. Following are the actions provided for each user.

// Normal user :
// Can register for the site
// Can modify the self details.
// Search the hotel details basing on the criteria.
// Book the hotel room
// Hotel Agent:
// Can register for the site
// Can add/update the details of the hotel.
// Adminstrator:
// Will approve the new hotel details added to the application
// Can delete the user/hotel details.
// Minimal Features :
// Adding Hotel information such as hotel name, location, number of rooms , facilities etc. to the database
// Listing the hotels based on different criteria selected by the user.
// User able to select a hotel and book a room.
// Booking permitted only if there are rooms available
// Displaying the reservation status.
// Registration of users.
// Update user details.
// Modify hotel details.
// Approval of the details entered by the hotel agent.
// Delete user/hotel details by admin
// Additional Features:
// Taking Feedback from user.
// Rating the hotels based on the feedback.
// Goals:
// To complete the hotel booking flow, registration of the users, adding details of the hotels.


// Deliverables:
// Minimal Features and additional features provided if time permits.
// Out of scope:
// We are not embedding payment gateway in the current application we will try if time permits after completion of additional features.

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

//HUMAN BASE CLASS
class Human
{
protected:
    string name;
    string email;
    int mobile;

public:
    Human(string name, string email, int mobile)
    {
        this->name = name;
        this->email = email;
        this->mobile = mobile;
    }

    //GETTERS AND SETTERS
    string getName()
    {
        return name;
    }

    string getEmail()
    {
        return email;
    }

    int getMobile()
    {
        return mobile;
    }

    virtual ~Human() {}
};

class User : public Human
{
public:
    User(string name, string email, int mobile) : Human(name, email, mobile)
    {
    }

    //UPDATING USER DETAILS
    void modifyDetails(string name, string email, int mobile)
    {
        this->name = name;
        this->email = email;
        this->mobile = mobile;
    }
};

//HOTEL AGENT CLASS INHERITED FROM HUMAN
class HotelAgent : public Human
{
public:
    HotelAgent(string name, string email, int mobile) : Human(name, email, mobile)
    {
    }
};

//HOTEL ADMIN CLASS INHERITED FROM HUMAN
class Administrator : public Human
{
public:
    Administrator(string name, string email, int mobile) : Human(name, email, mobile)
    {
    }
};

//ENUMS FOR FACILITIES OF HOTELS
enum FacilityType
{
    WIFI,
    SWIMMING_POOL,
    GYM,
    RESTAURANT,
    BAR,
    SPA
};

//HOTEL CLASS FOR EACH HOTEL
class Hotel
{
protected:
    string hotelName;
    string location;
    int numberOfRooms;
    int roomsBooked;
    vector<FacilityType> facilities;
    static int id;
    int uniqueId;

public:
    Hotel(string hotelName, string location, int numberOfRooms, vector<FacilityType> facilities)
    {
        id++;
        this->hotelName = hotelName;
        this->location = location;
        this->numberOfRooms = numberOfRooms;
        this->facilities = facilities;
        uniqueId = id;
    }

    //GETTERS AND SETTERS
    int getID()
    {
        return uniqueId;
    }

    string getLocation()
    {
        return location;
    }

    int getRoomsAvailable()
    {
        return numberOfRooms - roomsBooked;
    }

    //CHECKING FOR WHETHER FACILITY IS AVAILABLE OR NOT
    bool isFacilityAvailable(FacilityType facility)
    {
        if (find(facilities.begin(), facilities.end(), facility) != facilities.end())
        {
            return true;
        }
        return false;
    }

    string getHotelName()
    {
        return hotelName;
    }

    void bookRoom(int numberOfRooms)
    {
        roomsBooked += numberOfRooms;
    }

    //UPDATING THE USER DETAILS
    void updateDetails(string hotelName, int numberOfRooms, vector<FacilityType> facilities)
    {
        this->hotelName = hotelName;
        this->numberOfRooms = numberOfRooms;
        this->facilities = facilities;
    }

    //CHANGING FROM ENUM TO STRING FOR THE FACILITY
    string enumToString(FacilityType facility)
    {
        switch (facility)
        {
        case WIFI:
            return "WIFI";
        case SWIMMING_POOL:
            return "SWIMMING_POOL";
        case GYM:
            return "GYM";
        case RESTAURANT:
            return "RESTAURANT";
        case BAR:
            return "BAR";
        case SPA:
            return "SPA";
        }
    }

    //FOR SHOWING THE DETAILS OF THE FACILITIES
    void showFacilities()
    {

        for (auto &it : facilities)
        {
            cout << enumToString(it) << " ";
        }
    }
};

//INITIALISING THE STATIC VARIABLE
int Hotel::id = 0;

//FOR HANDLING THE USER RELATED THINGS
class UserManagement
{
public:
    //ADDING THE USER IN THE SITE
    void addUser(string name, string email, int phone, vector<User *> &users)
    {
        users.push_back(new User(name, email, phone));
        // cout<<name<<" added successfully"<<endl;
    }

    //SHOWING THE DETAILS OF ALL THE USERS IN THE SITE
    void showUserDetails(vector<User *> &users)
    {
        cout << endl
             << "Users are: " << endl;
        for (auto &it : users)
        {
            cout << it->getName() << endl;
        }
    }

    //UPDATING THE USER DETAILS
    void updateUserDetails(User *user, string name, string email, int phone)
    {
        user->modifyDetails(name, email, phone);
    }

    //SEARCHING THE HOTELS BASED ON THE CONDITIONS INPUT BY THE USER
    void search(string location, int numberOfRooms, vector<FacilityType> facilitiesRequired, unordered_map<HotelAgent *, vector<Hotel *>> hotelsApproved)
    {
        bool foundData = false;
        for (auto &it : hotelsApproved)
        {
            for (auto &hotel : it.second)
            {
                if (hotel->getLocation() == location && hotel->getRoomsAvailable() >= numberOfRooms)
                {
                    bool found = true;
                    for (auto &facility : facilitiesRequired)
                    {
                        if (!hotel->isFacilityAvailable(facility))
                        {
                            found = false;
                            break;
                        }
                    }
                    if (found)
                    {
                        foundData = true;
                        cout << "Id:" << hotel->getID() << "   HotelName:" << hotel->getHotelName() << "   RoomAvailable:" << hotel->getRoomsAvailable() << endl;
                    }
                }
            }
        }

        if (foundData == false)
        {
            cout << "No search results available" << endl;
        }
    }

    //FUNCTION FOR BOOKING THE HOTELS BY THE USER
    void bookHotel(User *user, int id, int numberOfRooms, unordered_map<Hotel *, User *> hotelBookings, unordered_map<HotelAgent *, vector<Hotel *>> hotelsApproved)
    {
        for (auto &it : hotelsApproved)
        {
            for (auto &hotel : it.second)
            {
                if (hotel->getID() == id)
                {
                    if (hotel->getRoomsAvailable() >= numberOfRooms)
                    {
                        hotelBookings[hotel] = user;
                        hotel->bookRoom(numberOfRooms);
                        cout << "Rooms booked successfully" << endl;
                    }
                    else
                    {
                        cout << "Rooms not available" << endl;
                    }
                    break;
                }
            }
            cout << endl;
        }
    }
};

//AGENTMANAGEMENT CLASS FOR HANDLING ALL THE FUNCTIONS RELATED TO THE AGENT
class AgentManagement
{
public:
    //ADDING THE AGENT IN THE SITE
    void addAgent(string name, string email, int phone, vector<HotelAgent *> &agents)
    {
        agents.push_back(new HotelAgent(name, email, phone));
        // cout<<name<<" added successfully"<<endl;
    }

    //ADDING THE HOTEL IN THE SYSTEM
    void addHotel(Hotel *hotel, HotelAgent *agent, unordered_map<HotelAgent *, vector<Hotel *>> &hotelsToBeApproved)
    {
        hotelsToBeApproved[agent].push_back(hotel);
    }

    //UPDATING THE HOTEL DETAILS
    void updateHotelDetails(Hotel *hotel, HotelAgent *agent, string hotelName, int numberOfRooms, vector<FacilityType> facilities, unordered_map<HotelAgent *, vector<Hotel *>> &hotelsToBeApproved, unordered_map<HotelAgent *, vector<Hotel *>> &hotelsApproved)
    {
        bool found = false;
        for (auto &it : hotelsToBeApproved[agent])
        {
            if (it == hotel)
            {
                found = true;
                break;
            }
        }
        for (auto &it : hotelsApproved[agent])
        {
            if (it == hotel)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            hotel->updateDetails(hotelName, numberOfRooms, facilities);
        }
        else
        {
            cout << "Hotel does not belong to this agent" << endl;
        }
    }

    //SHOW ALL THE HOTEL DETAILS
    void showHotelDetails(unordered_map<HotelAgent *, vector<Hotel *>> hotelsToBeApproved, unordered_map<HotelAgent *, vector<Hotel *>> hotelsApproved)
    {
        cout << "Hotels to be approved: " << endl;
        for (auto &it : hotelsToBeApproved)
        {
            cout << "Agent: " << it.first->getName() << endl;
            for (auto &hotel : it.second)
            {
                cout << hotel->getHotelName() << "  TotalRooms:" << hotel->getRoomsAvailable() << "  Facilities:";
                hotel->showFacilities();
                cout << "  Location:";
                cout << hotel->getLocation();
                cout << endl;
            }
            cout << endl;
        }

        cout << "Hotels approved: " << endl;
        for (auto &it : hotelsApproved)
        {
            cout << "Agent: " << it.first->getName() << endl;
            for (auto &hotel : it.second)
            {
                cout << hotel->getHotelName() << "  TotalRooms:" << hotel->getRoomsAvailable() << "  Facilities:";
                hotel->showFacilities();
                cout << "  Location:";
                cout << hotel->getLocation();
                cout << endl;
            }
            cout << endl;
        }
    }
};

//ADMIN CLASS FOR HANDLING ALL THE ADMIN RELATED FEATURES
class AdminManagement
{
public:
    //VERIFYING THE HOTELS ADDED BY THE AGENTS
    void verifyHotel(Human *admin, Hotel *hotel, HotelAgent *agent, unordered_map<HotelAgent *, vector<Hotel *>> &hotelsToBeApproved, unordered_map<HotelAgent *, vector<Hotel *>> &hotelsApproved)
    {
        if (dynamic_cast<Administrator *>(admin))
        {
            bool found = false;
            for (auto &it : hotelsToBeApproved[agent])
            {
                if (it == hotel)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {   //ADDING THE HOTEL TO APPROVED DB FROM NOT APPROVED DB
                hotelsToBeApproved[agent].erase(remove(hotelsToBeApproved[agent].begin(), hotelsToBeApproved[agent].end(), hotel), hotelsToBeApproved[agent].end());
                hotelsApproved[agent].push_back(hotel);
                cout << "Hotel verified" << endl;
            }
            else
            {
                cout << "Hotel not found" << endl;
            }
        }
        else
        {
            cout << "Only admin can approve the hotel" << endl;
        }
    }

    //DELETING THE USER FROM THE SITE
    void deleteUser(Human *admin, User *user, vector<User *> &users)
    {
        if (dynamic_cast<Administrator *>(admin))
        {
            users.erase(remove(users.begin(), users.end(), user), users.end());
            cout << "User deleted" << endl;
        }
        else
        {
            cout << "Only admin can delete the user" << endl;
        }
    }

    //DELETING THE HOTEL FROM THE DB
    void deleteHotel(Human *admin, Hotel *hotel, HotelAgent *agent, unordered_map<HotelAgent *, vector<Hotel *>> &hotelsToBeApproved, unordered_map<HotelAgent *, vector<Hotel *>> &hotelsApproved)
    {
        if (dynamic_cast<Administrator *>(admin))
        {
            bool found = false;
            for (auto &it : hotelsToBeApproved[agent])
            {
                if (it == hotel)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {
                hotelsToBeApproved[agent].erase(remove(hotelsToBeApproved[agent].begin(), hotelsToBeApproved[agent].end(), hotel), hotelsToBeApproved[agent].end());
                cout << "Hotel deleted" << endl;
                return;
            }

            for (auto &it : hotelsApproved[agent])
            {
                if (it == hotel)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {
                hotelsApproved[agent].erase(remove(hotelsApproved[agent].begin(), hotelsApproved[agent].end(), hotel), hotelsApproved[agent].end());
                cout << "Hotel deleted" << endl;
                return;
            }

            cout << "Hotel not found" << endl;
        }
        else
        {
            cout << "Only admin can delete the hotel" << endl;
        }
    }
};


//RATING MANAGEMENT CLASS FOR HANDLING ALL THE RATING RELATED THINGS
class RatingManagement{
    public:
    unordered_map<Hotel*,pair<float,float> > ratings; // total rating, total user

    //FUNCTION FOR SHOWING THE RATING OF ALL THE HOTELS AVAILABLE
    void showRating(){
        for(auto &it:ratings){
            cout<<"Rating of "<<it.first->getHotelName()<<" is "<<it.second.first/it.second.second<<endl;
        }
    }

    //FUNCTION FOR ADDING THE RATING IN THE DB
    void addRating(int id,unordered_map<HotelAgent *, vector<Hotel *>> hotelsApproved,int ratingByUser){
        for(auto &it:hotelsApproved){
            for(auto &hotel:it.second){
                if(hotel->getID()==id){
                    ratings[hotel].first+=ratingByUser;
                    ratings[hotel].second++;
                }
            }
        }
    }



};

//HOTEL MANAGEMENT CLASS 
class HotelManagement
{
public:
    vector<User *> users; // all the users
    vector<HotelAgent *> agent;

    unordered_map<Hotel *, User *> hotelBookings;
    unordered_map<HotelAgent *, vector<Hotel *>> hotelsApproved;
    unordered_map<HotelAgent *, vector<Hotel *>> hotelsToBeApproved;

    UserManagement userManagement;
    AgentManagement agentManagement;
    AdminManagement adminManagement;
    RatingManagement ratingManagement;

    
};

void testLibraryManagementSystem()
{
    HotelManagement hotelManagement;

    // Test Case 1: Add users to the hotel site
    // name,email,phone,vector<User *> &users
    hotelManagement.userManagement.addUser("user-1", "abc-1@gmail.com", 1234567890, hotelManagement.users);
    hotelManagement.userManagement.addUser("user-2", "abc-1@gmail.com", 1234567890, hotelManagement.users);
    hotelManagement.userManagement.addUser("user-3", "abc-1@gmail.com", 1234567890, hotelManagement.users);
    hotelManagement.userManagement.addUser("user-4", "abc-1@gmail.com", 1234567890, hotelManagement.users);
    hotelManagement.userManagement.addUser("user-5", "abc-1@gmail.com", 1234567890, hotelManagement.users);

    // Test Case 2: Add agents to the hotel site
    // name,email,phone,vector<HotelAgent *> &agents
    hotelManagement.agentManagement.addAgent("agent-1", "agent-1@gmail.com", 1234567890, hotelManagement.agent);
    hotelManagement.agentManagement.addAgent("agent-2", "agent-2@gmail.com", 1234567890, hotelManagement.agent);
    hotelManagement.agentManagement.addAgent("agent-3", "agent-3@gmail.com", 1234567890, hotelManagement.agent);
    hotelManagement.agentManagement.addAgent("agent-4", "agent-4@gmail.com", 1234567890, hotelManagement.agent);
    hotelManagement.agentManagement.addAgent("agent-5", "agent-5@gmail.com", 1234567890, hotelManagement.agent);

    // Test Case 3: Modify user deatils
    //  User *user, string name, string email, int phone
    //  hotelManagement.userManagement.updateUserDetails(hotelManagement.users[0],"user-update-1","abc-1@gmail.com",1234567890);

    // Test Case 4: Create hotel
    Hotel *hotel1 = new Hotel("Hotel-1", "Delhi", 10, {WIFI, SWIMMING_POOL});
    Hotel *hotel2 = new Hotel("Hotel-2", "Delhi", 20, {WIFI, SWIMMING_POOL, GYM});
    Hotel *hotel3 = new Hotel("Hotel-3", "Hyderabad", 30, {WIFI, SWIMMING_POOL, GYM, RESTAURANT});
    Hotel *hotel4 = new Hotel("Hotel-4", "Pune", 40, {WIFI, SWIMMING_POOL, GYM, RESTAURANT, BAR});
    Hotel *hotel5 = new Hotel("Hotel-5", "Delhi", 50, {WIFI, SWIMMING_POOL, GYM, RESTAURANT, BAR, SPA});

    // Test Case 5: Add hotel by agent
    hotelManagement.agentManagement.addHotel(hotel1, hotelManagement.agent[0], hotelManagement.hotelsToBeApproved);
    hotelManagement.agentManagement.addHotel(hotel2, hotelManagement.agent[1], hotelManagement.hotelsToBeApproved);
    hotelManagement.agentManagement.addHotel(hotel3, hotelManagement.agent[2], hotelManagement.hotelsToBeApproved);
    hotelManagement.agentManagement.addHotel(hotel4, hotelManagement.agent[3], hotelManagement.hotelsToBeApproved);
    hotelManagement.agentManagement.addHotel(hotel5, hotelManagement.agent[4], hotelManagement.hotelsToBeApproved);
    // WIFI, SWIMMING_POOL, GYM, RESTAURANT, BAR, SPA

    // Test Case 6: Update hotel details
    //  hotelManagement.agentManagement.updateHotelDetails(hotel1,hotelManagement.agent[0],"Hotel-1",20,{},hotelManagement.hotelsToBeApproved,hotelManagement.hotelsApproved);

    // Test Case 8: Create admin
    //  name, email, mobile
    Administrator *admin1 = new Administrator("Admin-1", "ad-1@gmail.com", 1234567890);
    Administrator *admin2 = new Administrator("Admin-2", "ad-1@gmail.com", 1234567890);
    Administrator *admin3 = new Administrator("Admin-3", "ad-1@gmail.com", 1234567890);

    // Test Case 7: Approve hotel by admin
    //  hotelManagement.adminManagement.verifyHotel(hotelManagement.agent[0],hotel1,hotelManagement.agent[0],hotelManagement.hotelsToBeApproved,hotelManagement.hotelsApproved);  //only admin can approve
    hotelManagement.adminManagement.verifyHotel(admin1, hotel1, hotelManagement.agent[0], hotelManagement.hotelsToBeApproved, hotelManagement.hotelsApproved);
    hotelManagement.adminManagement.verifyHotel(admin1, hotel2, hotelManagement.agent[1], hotelManagement.hotelsToBeApproved, hotelManagement.hotelsApproved);
    hotelManagement.adminManagement.verifyHotel(admin1, hotel5, hotelManagement.agent[4], hotelManagement.hotelsToBeApproved, hotelManagement.hotelsApproved);
    // hotelManagement.adminManagement.verifyHotel(admin1,hotel1,hotelManagement.agent[0],hotelManagement.hotelsToBeApproved,hotelManagement.hotelsApproved);

    // Test Case 9: Delete user by admin
    //  hotelManagement.adminManagement.deleteUser(hotelManagement.users[0],hotelManagement.users[0],hotelManagement.users);  //only admin can delete
    //  hotelManagement.adminManagement.deleteUser(admin1,hotelManagement.users[3],hotelManagement.users);

    // Test Case 10: Delete hotel by admin
    //  hotelManagement.adminManagement.deleteHotel(admin1,hotel1,hotelManagement.agent[1],hotelManagement.hotelsToBeApproved,hotelManagement.hotelsApproved);  //only admin can delete
    //  hotelManagement.adminManagement.deleteHotel(admin1,hotel1,hotelManagement.agent[0],hotelManagement.hotelsToBeApproved,hotelManagement.hotelsApproved);  //only admin can delete

    // Test Case 11: Search hotel
    hotelManagement.userManagement.search("Delhi", 10, {WIFI}, hotelManagement.hotelsApproved);

    // Test Case 12: Book hotel
    //  User* user,int id, int numberOfRooms, unordered_map<Hotel*,User*> hotelBookings
    // hotelManagement.userManagement.bookHotel(hotelManagement.users[0], 2, 5, hotelManagement.hotelBookings, hotelManagement.hotelsApproved);

    // hotelManagement.userManagement.search("Delhi", 16, {WIFI}, hotelManagement.hotelsApproved);


    // hotelManagement.agentManagement.showHotelDetails(hotelManagement.hotelsToBeApproved,hotelManagement.hotelsApproved);
    // hotelManagement.userManagement.showUserDetails(hotelManagement.users);

    //Test Case 13: Rating Management
    hotelManagement.ratingManagement.addRating(2,hotelManagement.hotelsApproved,5);
    hotelManagement.ratingManagement.addRating(2,hotelManagement.hotelsApproved,3);
    cout<<endl;
    hotelManagement.ratingManagement.showRating();

}

int main()
{
    
    testLibraryManagementSystem();
    return 0;
}