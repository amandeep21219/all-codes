#include <iostream>
#include <string>
using namespace std;

// Base class 
class Inverter {
protected:
    string name;
    float current;
    float operatingVoltage;

public:
    // Constructor
    Inverter(string n, float c, float v) : name(n), current(c), operatingVoltage(v) {}

    //  power rating method
    float getPowerRating() {
        return current * operatingVoltage;
    }

    // information of the inverter
    virtual void displayInfo() {
        cout << "Inverter's Name: " << name << endl;
        cout << "Power Rating: " << getPowerRating() << " Watts" <<endl;
    }
};

// Derived class for Solar Inverters
class SolarInverter : public Inverter {
private:
    bool hasBattery;
    bool gridOn;

public:
    // Constructor Solar Inverters
    SolarInverter(string n, float c, float v, bool battery, bool grid)
        : Inverter(n, c, v), hasBattery(battery), gridOn(grid) {}

    // displayInfo to show additional solar inverter details
    void displayInfo(){
        cout << "Solar Panels: Present" << endl;
        cout << "Battery: " << (hasBattery ? "Yes" : "No") <<endl;
        cout << "GRID On: " << (gridOn ? "Yes" : "No") << endl;
    }
};

// Class for Non-Solar Inverters
class HomeInverter : public Inverter {
public:
    // Constructor Home Inverter
    HomeInverter(string n, float c, float v) : Inverter(n, c, v) {}

    // Display  details for Home Inverters
    void displayInfo() {
        std::cout << "Battery: Yes" << std::endl;
    }
};


int main() {
    
    SolarInverter pcu("PCU", 10, 240, true, false); SolarInverter* pcu =new  SolarInverter()
    
    //  Solar Inverter without battery, with GRID On
    SolarInverter gti("GTI", 15, 230, false, true);
    
    //  Solar Inverter with battery, no GRID On 
    SolarInverter regalia("Regalia", 12, 220, true, false);
    
    //  Non-solar Home Inverter
    HomeInverter zelio("Zelio", 12, 220);
    
    //  Non-solar Home Inverter
    HomeInverter icruze("iCruze", 20, 240);

    // Display information for each inverter
   cout << "PCU Details:" << endl;
    pcu.displayInfo();
    cout <<endl;

    cout << "GTI Details:" << endl;
    gti.displayInfo();
    cout << endl;

    cout << "Regalia Details:" << endl;
    regalia.displayInfo();
    cout << std::endl;

    cout << "Zelio Details:" << endl;
    zelio.displayInfo();
    cout << endl;

   cout << "iCruze Details:" << endl;
    icruze.displayInfo();
   cout << endl;

    return 0;
}