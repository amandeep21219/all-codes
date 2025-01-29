#include <iostream>
#include <string>
using namespace std;

// Base class
class MP {
protected:
    string name;
    string constituency;
    float spending;
    float spendingLimit;

public:
    // Constructor MP
    MP(string n, string c, float limit) 
        : name(n), constituency(c), spending(0), spendingLimit(limit) {}

    // Return the constituency 
    string getConstituency() {
        return constituency;
    }

    // Simulate spending
    void spend(float amount) {
        spending += amount;
    }

    // Display MP info
    virtual void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Constituency: " << constituency << endl;
        cout << "Spending: " << spending << " INR (Limit: " << spendingLimit << " INR)" << endl;
    }

    

};

// Derived class Minister
class Minister : public MP {
public:
    // Constructor 
    Minister(string n, string c) : MP(n, c, 1000000) {} // Limit set to 10 lakhs

    // Override displayInfo for Minister-specific details
    void displayInfo() override {
        MP::displayInfo();
        cout << "Role: Cabinet Minister" << endl;
    }
};

// Derived class PM
class PM : public MP {
public:
    // Constructor 
    PM(string n, string c) : MP(n, c, 10000000) {} // Limit set to 1 cr

    // Display PM-specific details
    void displayInfo() override {
        MP::displayInfo();
        cout << "Role: Prime Minister" << endl;
    }

    // PM grants permission for arrests
    bool giveArrestPermission() {
        return true;
    }
};

// Simplified Commissioner Class
class Commissioner {
public:
    // Simplified canArrest logic
    void canArrest(MP* mp, bool isPM, bool isMinister, bool pmPermission = false) {
        if (isPM) {
            cout << mp->getConstituency() << ": Cannot arrest the Prime Minister." << endl;
        } else if (isMinister) {
            if (pmPermission) {
                cout << mp->getConstituency() << ": Minister can be arrested with PM's permission." << endl;
            } else {
                cout << mp->getConstituency() << ": Minister cannot be arrested without PM's permission." << endl;
            }
        } else {
            cout << mp->getConstituency() << ": MP can be arrested without permission." << endl;
        }
    }
};

// Main function
int main() {
    // Create objects
    MP mp1("Bhagwant Mann", "Punjab", 100000); // Limit set to 1 lakh
    Minister minister("Bikram Singh Majithia", "PP");
    PM pm("Narendra Modi", "Gujarat");

    // Simulate spending
    mp1.spend(150000); // Exceeds limit
    minister.spend(500000); // Within limit
    pm.spend(15000000); // Exceeds limit

    // Display information
    cout << "MP Details:" << endl;
    mp1.displayInfo();
    cout << endl;

    cout << "Minister Details:" << endl;
    minister.displayInfo();
    cout << endl;

    cout << "Prime Minister Details:" << endl;
    pm.displayInfo();
    cout << endl;

    // Commissioner and test arrest
    Commissioner commissioner;
    commissioner.canArrest(&mp1, false, false); // MP
    commissioner.canArrest(&minister, false, true, pm.giveArrestPermission()); // Minister
    commissioner.canArrest(&pm, true, false); // PM

    return 0;
}
