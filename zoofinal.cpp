#include "zoofinal.h"

Zoo::~Zoo() 
{
    for (auto s : staff)
    {
        delete s;
    }
}
vector<Animal>& Zoo::getAnimals() 
{
    return animals;
}
vector<Staff*>& Zoo::getStaffList() 
{
    return staff;
}
vector<Habitat>& Zoo::getHabitats() 
{
    return habitats;
}
vector<Food>& Zoo::getFoods()
{
    return foods;
}
vector<Visitor>& Zoo::getVisitors() 
{
    return visitors;
}
void Zoo::addAnimal(const Animal& a)
{
    animals.push_back(a);
}
void Zoo::addStaff(Staff* s)
{
    staff.push_back(s);
}
void Zoo::addHabitat(const Habitat& h)
{
    habitats.push_back(h);
}
void Zoo::addVisitor(const Visitor& v) 
{
    visitors.push_back(v);
}
void Zoo::addFood(const Food& f) 
{
    foods.push_back(f);
}

Animal::Animal(string name, int a, string id, string sp, char g, string t, string health, string hID, string sID)
{
    this->animalName = name;
    this->animalAge = a;
    this->animalID = id;
    this->species = sp;
    this->gender = g;
    this->type = t;
    this->healthStatus = health;
    this->habitatID = hID;
    this->staffID = sID;
}

ostream& operator<<(ostream& output, const Animal& a)
{
    output << "Animal ID: " << a.animalID << endl
           << "Name: " << a.animalName << endl
           << "Age: " << a.animalAge << endl
           << "Species: " << a.species << endl
           << "Gender: " << a.gender << endl
           << "Type: " << a.type << endl
           << "Health Status: " << a.healthStatus << endl
           << "Habitat ID: " << a.habitatID << endl
           << "Staff ID: " << a.staffID << endl;
    return output;
}

string Animal::getAnimalID() { return animalID; }

void Animal::setHealthStatus(const string& newStatus)
{
    healthStatus = newStatus;
}

void Animal::addNewAnimal(vector<Animal>& animals)
{
    cout << "Enter details for the new animal:\n";
    string name, id, species, type, health, habitatID, staffID;
    int age;
    char gender;
    cout << "Animal ID: ";
    cin >> id;
    cout << "Animal Name: ";
    cin >> name;
    cout << "Age: ";
    cin >> age;
    cout << "Species: ";
    cin >> species;
    cout << "Gender (M/F): ";
    cin >> gender;
    cout << "Type (Carnivore/Herbivore/Omnivore): ";
    cin >> type;
    cout << "Health Status: ";
    cin >> health;
    cout << "Habitat ID: ";
    cin >> habitatID;
    cout << "Staff ID: ";
    cin >> staffID;
    Animal newAnimal(name, age, id, species, gender, type, health, habitatID, staffID);
    animals.push_back(newAnimal);
    cout << "Animal successfully added to the zoo!\n";
}

Habitat::Habitat(string habitatID, string type, int maxCapacity, vector<string> assignedAnimals, double size)
{
    this->habitatID = habitatID;
    this->type = type;
    this->maxCapacity = maxCapacity;
    this->assignedAnimals = assignedAnimals;
    this->size = size;
}

ostream& operator<<(ostream& output, const Habitat& h)
{
    output << "Habitat ID: " << h.habitatID << endl
           << "Type: " << h.type << endl
           << "Max Capacity: " << h.maxCapacity << endl
           << "Size: " << h.size << " sq.m" << endl
           << "Assigned Animals: ";
    if (h.assignedAnimals.empty())
        output << "None";
    else
    {
        for (const auto& animal : h.assignedAnimals)
            output << animal << " ";
    }
    output << endl;
    return output;
}

Staff::Staff(string n, string i, int a, double s, string c)
{
    this->name = n;
    this->id = i;
    this->age = a;
    this->salary = s;
    this->contactNo = c;
}

string Staff::getStaffID() { return (id); }

void Staff::display()
{
    cout << "Name: " << name
         << "\nID: " << id
         << "\nAge: " << age
         << "\nSalary: " << salary
         << "\nContact: " << contactNo << endl;
}

AnimalCareStaff::AnimalCareStaff(string n, string i, int a, double s, string c, vector<string> skills) : Staff(n, i, a, s, c), skilledAnimals(skills) {}

void AnimalCareStaff::display()
{
    Staff::display();
    cout << "Skilled Animals: ";
    for (const auto &a : skilledAnimals)
    {
        cout << a << " ";
    }
    cout << endl;
}

Keeper::Keeper(string n, string i, int a, double s, string c, vector<string> skills, string sh) : AnimalCareStaff(n, i, a, s, c, skills), shift(sh) {}

void Keeper::display()
{
    cout << "\nKeeper\n";
    AnimalCareStaff::display();
    cout << "Shift: " << shift << endl;
}

Vet::Vet(string n, string i, int a, double s, string c, vector<string> skills, vector<string> certs) : AnimalCareStaff(n, i, a, s, c, skills), certifications(certs) {}

void Vet::display()
{
    cout << "\nVet\n";
    AnimalCareStaff::display();
    cout << "Certifications: ";
    for (const auto &c : certifications)
        cout << c << " ";
    cout << endl;
}

AdminStaff::AdminStaff(string n, string i, int a, double s, string c, string dept) : Staff(n, i, a, s, c), department(dept) {}

void AdminStaff::display()
{
    cout << "\nAdmin Staff\n";
    Staff::display();
    cout << "Department: " << department << endl;
}

SecurityStaff::SecurityStaff(string n, string i, int a, double s, string c, bool arm) : Staff(n, i, a, s, c), armed(arm) {}

void SecurityStaff::display()
{
    cout << "\nSecurity Staff\n";
    Staff::display();
    cout << "Armed: " << (armed ? "Yes" : "No") << endl;
}

Food::Food(string foodID, string foodName, vector<string> consumingAnimals, int quantityAvailable, string unit, int costPerUnit)
{
    this->foodID = foodID;
    this->foodName = foodName;
    this->consumingAnimals = consumingAnimals;
    this->quantityAvailable = quantityAvailable;
    this->unit = unit;
    this->costPerUnit = costPerUnit;
}

ostream& operator<<(ostream& output, const Food& f)
{
    output << "Food ID: " << f.foodID << endl
           << "Food Name: " << f.foodName << endl
           << "Quantity Available: " << f.quantityAvailable << " " << f.unit << endl
           << "Cost per Unit: " << f.costPerUnit << endl
           << "Consuming Animals: ";
    if (f.consumingAnimals.empty())
        output << "None";
    else
    {
        for (const auto& animal : f.consumingAnimals)
            output << animal << " ";
    }
    output << endl;
    return output;
}

string Food::getFoodID()  { return foodID; }

vector<string> Food::getConsumingAnimals() {return consumingAnimals;}

void Food::reduceQuantity(int used)
 {
    if (used <= quantityAvailable)
        quantityAvailable -= used;
    else 
    {
        cout << "Warning: Tried to reduce more than available stock!\n";
        quantityAvailable = 0;
    }
}

void Food::restockFood(vector<Food>& foods)
{
    string fid, fname, unit;
    int qty, cost;
    vector<string> consumers;
    cout << "Enter Food ID: ";
    cin >> fid;
    cout << "Enter Food Name: ";
    cin >> fname;
    cout << "Enter Quantity Available: ";
    cin >> qty;
    cout << "Enter Unit (kg/ltr etc.): ";
    cin >> unit;
    cout << "Enter Cost per Unit: ";
    cin >> cost;
    Food f1(fid, fname, consumers, qty, unit, cost);
    foods.push_back(f1);
    cout << "Food Restocked Successfully!\n";
}

Visitor::Visitor(string ticketID, string visitorName, int visitorAge,
                 vector<int> visitDate, pair<int,int> visitTime)
{
    this->ticketID = ticketID;
    this->visitorName = visitorName;
    this->visitorAge = visitorAge;
    this->visitDate = visitDate;
    this->visitTime = visitTime;
}

string Visitor::getTicketID() { return ticketID; }

ostream& operator<<(ostream& output, const Visitor& v)
{
    output << "Ticket ID: " << v.ticketID << endl
           << "Name: " << v.visitorName << endl
           << "Age: " << v.visitorAge << endl
           << "Visit Date: ";
    for (size_t i = 0; i < v.visitDate.size(); ++i)
    {
        output << v.visitDate[i];
        if (i != v.visitDate.size() - 1)
            output << "-";
    }
    output << endl
           << "Visit Time: " << v.visitTime.first << ":00 - "
                             << v.visitTime.second << ":00" << endl;
    return output;
}

void Visitor::bookTicket(vector<Visitor>& visitors)
{
    string name2;
    int age2;
    vector<int> date2;
    pair<int,int> time2;
    int num;
    string tID2 = "V";
    cout << "Enter the following details to book a ticket: \n";
    cout << "Enter your Name: ";
    cin >> name2;
    cout << "Enter your Age: ";
    cin >> age2;
    cout << "Enter Date of visit (DD MM YYYY): ";
    for (int i = 0; i < 3; i++) {
        cin >> num;
        date2.push_back(num);
    }
    cout << "Enter Visit Time: (Start): ";
    cin >> time2.first;
    cout << "Enter Visit Time: (End): ";
    cin >> time2.second;
    tID2 += to_string(visitors.size() + 1);
    Visitor v1(tID2, name2, age2, date2, time2);
    visitors.push_back(v1);
    cout << "Ticket Successfully Booked!\n";
}

Finance::Finance(int totalRevenue, int totalExpenses, int donationsReceived, int staffSalaries, int foodCost, int habitatMaintenance, int misc)
{
    this->totalRevenue = totalRevenue;
    this->totalExpenses = totalExpenses;
    this->donationsReceived = donationsReceived;
    this->staffSalaries = staffSalaries;
    this->foodCost = foodCost;
    this->habitatMaintenance = habitatMaintenance;
    this->misc = misc;
}

ostream& operator<<(ostream& output, const Finance& f)
{
    output << "Total Revenue: " << f.totalRevenue << endl
    << "Total Expenses: " << f.totalExpenses << endl
    << "Donations Received: " << f.donationsReceived << endl
    << "Staff Salaries: " << f.staffSalaries << endl
    << "Food Cost: " << f.foodCost << endl
    << "Habitat Maintenance: " << f.habitatMaintenance << endl  
    << "Miscellaneous Expenditure: " << f.misc << endl;
    return output;
}

void Finance::updateFinance(int revenue, int expense)
{
    totalRevenue += revenue;
    totalExpenses += expense;
}

void viewTicketDetails(const vector<Visitor>& visitors, const string& tID1)
{
    bool flag = false;
    for (const auto &i : visitors)
    {
        if (i.ticketID == tID1)
        {
            cout << "Ticket Details Found\n";
            flag = true;
            cout << i;
            break;
        }
    }
    if (flag == false)
        cout << "Ticket Details Not Found\n";
}
