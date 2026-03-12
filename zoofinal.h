#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Animal;
class Staff;
class Habitat;
class Food;
class Visitor;

class Zoo 
{
private:
    vector<Animal> animals;
    vector<Staff*> staff;
    vector<Habitat> habitats;
    vector<Food> foods;
    vector<Visitor> visitors;
public:
    vector<Animal>& getAnimals();
    vector<Staff*>& getStaffList();
    vector<Habitat>& getHabitats();
    vector<Food>& getFoods();
    vector<Visitor>& getVisitors();
    void addAnimal(const Animal& a);
    void addStaff(Staff* s);
    void addHabitat(const Habitat& h);
    void addVisitor(const Visitor& v);
    void addFood(const Food& f);
    ~Zoo();
};

class Animal
{
private:
    string animalName;
    int animalAge;
    string animalID;  
    string species;
    char gender;
    string type;
    string healthStatus;
    string habitatID;
    string staffID;
public:
    Animal(string animalName = "Unknown",
           int animalAge = 0,
           string animalID = "A0",
           string species = "Unknown",
           char gender = 'U',
           string type = "Undefined",
           string healthStatus = "Healthy",
           string habitatID = "None",
           string staffID = "None");
    friend ostream& operator<<(ostream&, const Animal&);
    string getAnimalID();
    void setHealthStatus(const string&);
    void addNewAnimal(vector<Animal>& animals);
};

class Habitat
{
private:
    string habitatID;  
    string type;
    int maxCapacity;
    vector<string> assignedAnimals;
    double size;
public:
    Habitat(string habitatID = "H0",
            string type = "Generic",
            int maxCapacity = 0,
            vector<string> assignedAnimals = {},
            double size = 0.0);
    friend ostream& operator<<(ostream&, const Habitat&);
};

class Staff 
{
protected:
    string name;
    string id;
    int age;
    double salary;
    string contactNo;   
public:
    Staff(string n = "Unknown", string i = "0", int a = 0, double s = 0.0, string c = "0");
    virtual void display();
    string getName() const { return name; }
    string getID() const { return id; }               
    int getAge() const { return age; }
    double getSalary() const { return salary; }
    string getContact() const { return contactNo; }
    virtual string getStaffID();
    virtual ~Staff() {}
};

class AnimalCareStaff : public Staff 
{
protected:
    vector<string> skilledAnimals;
public:
    AnimalCareStaff(string n = "Unknown", string i = "0", int a = 0, double s = 0.0, string c = "0", vector<string> skills = {});
    void display() override;
};

class Keeper : public AnimalCareStaff 
{
private:
    string shift;   
public:
    Keeper(string n, string i, int a, double s, string c, vector<string> skills, string sh);
    void display() override;
};

class Vet : public AnimalCareStaff 
{
private:
    vector<string> certifications;
public:
    Vet(string n, string i, int a, double s, string c, vector<string> skills, vector<string> certs);
    void display() override;
};

class AdminStaff : public Staff 
{
private:
    string department;
public:
    AdminStaff(string n, string i, int a, double s, string c, string dept);
    void display() override;
};

class SecurityStaff : public Staff 
{
private:
    bool armed;
public:
    SecurityStaff(string n, string i, int a, double s, string c, bool arm);
    void display() override;
};

class Food
{
private:
    string foodID; 
    string foodName;
    vector<string> consumingAnimals; 
    int quantityAvailable;
    string unit;
    int costPerUnit;
public:
    Food(string foodID = "F0",
         string foodName = "GenericFood",
         vector<string> consumingAnimals = {},
         int quantityAvailable = 0,
         string unit = "kg",
         int costPerUnit = 0);
    friend ostream& operator<<(ostream&, const Food&);
    string getFoodID();
    vector<string> getConsumingAnimals();
    void reduceQuantity(int);
    void restockFood(vector<Food>& foods);
};

class Visitor
{
private:
    string ticketID;    
    string visitorName;
    int visitorAge;
    vector<int> visitDate; 
    pair<int,int> visitTime;  
public:
    Visitor(string ticketID = "V0",
            string visitorName = "Guest",
            int visitorAge = 0,
            vector<int> visitDate = {1, 1, 2026},   
            pair<int,int> visitTime = {10, 12});   
    friend ostream& operator<<(ostream&, const Visitor&);
    friend void viewTicketDetails(const vector<Visitor>& visitors, const string& tID1);
    void bookTicket(vector<Visitor>& visitors);
    string getTicketID(); 
};

class Finance
{
private:
    int totalRevenue;
    int totalExpenses;
    int donationsReceived;
    int staffSalaries;
    int foodCost;
    int habitatMaintenance; 
    int misc;   
public:
    Finance(int totalRevenue = 0,
            int totalExpenses = 0,
            int donationsReceived = 0,
            int staffSalaries = 0,
            int foodCost = 0,
            int habitatMaintenance = 0,
            int misc = 0);
    friend ostream& operator<<(ostream&, const Finance&);
    void updateFinance(int,int);
};


