#include "zoofinal.cpp"
#include <unordered_map>
using namespace std;

bool staffExists(Zoo &zoo, const string &sid)
{
    auto &slist = zoo.getStaffList();
    for (auto sPtr : slist)
        if (sPtr->getStaffID() == sid)
            return true;
    return false;
}
bool visitorExists(Zoo &zoo, const string &vid)
{
    auto &vlist = zoo.getVisitors();
    for (auto &v : vlist)
        if (v.getTicketID() == vid)
            return true;
    return false;
}
bool authenticate(unordered_map<string,string> &credentials, const string &id, const string &pwd)
{
    auto it = credentials.find(id);
    if (it == credentials.end())
        return false;
    return it->second == pwd;
}

int main()
{
    cout << "Welcome to Zoo Management System!\n";
    int ch, ch1, ch2, ch3, ch4;
    string tID1, loggedVisitorID = "", loggedStaffID = "";
    Finance financeObj(500000,200000,30000,120000,25000,30000,5000);
    Zoo zoo;
    //Sample Data
    zoo.addStaff(new Keeper("Ravi", "S101", 35, 25000, "9876543210", {"Lions", "Tigers"}, "Morning"));
    zoo.addStaff(new Vet("Dr. Meera", "S102", 40, 50000, "9123456780", {"Elephants"}, {"Surgery", "Wildlife"}));
    zoo.addStaff(new AdminStaff("Anil", "S103", 45, 30000, "7894561230", "Finance"));
    zoo.addStaff(new SecurityStaff("Karan", "S104", 30, 20000, "9991112220", true));

    zoo.addHabitat(Habitat("H1", "Savannah", 5, {"A1"}, 500.0));
    zoo.addHabitat(Habitat("H2", "Rainforest", 3, {"A2"}, 300.0));
    zoo.addHabitat(Habitat("H3", "Jungle", 4, {"A3"}, 800.0));

    zoo.addAnimal(Animal("Leo", 5, "A1", "Lion", 'M', "Carnivore", "Healthy", "H1", "S101"));
    zoo.addAnimal(Animal("Sheera", 4, "A2", "Tiger", 'F', "Carnivore", "Healthy", "H1", "S101"));
    zoo.addAnimal(Animal("Dumbo", 10, "A3", "Elephant", 'M', "Herbivore", "Injured", "H2", "S102"));

    zoo.addFood(Food("F1", "Meat", {"A1", "A2"}, 200, "kg", 150));
    zoo.addFood(Food("F2", "Bananas", {"A3"}, 300, "kg", 40));
    zoo.addFood(Food("F3", "Fish", {"A2"}, 100, "kg", 120));

    zoo.addVisitor(Visitor("V1", "Rohan", 22, {21, 11, 2025}, {10, 12}));
    zoo.addVisitor(Visitor("V2", "Aditi", 30, {20, 11, 2025}, {14, 16}));
    zoo.addVisitor(Visitor("V3", "Sam", 18, {19, 11, 2025}, {9, 11}));

    unordered_map<string,string> credentials;

    credentials["S101"] = "pass101";
    credentials["S102"] = "pass102";
    credentials["S103"] = "pass103";
    credentials["S104"] = "pass104";

    credentials["V1"] = "v1pass";
    credentials["V2"] = "v2pass";
    credentials["V3"] = "v3pass";

    credentials["MGR"] = "admin123";
    credentials["FS1"] = "food123";

    do
    {
        cout << "\nMenu for Entering the Role: \n1 - Visitor \n2 - Staff \n3 - Food Supplier \n4 - Manager \n5 - Exit \nEnter Your Choice: ";
        cin >> ch;

        switch(ch)
        {
            case 1:
            {
                int haveAcct = 0;
                cout << "Do you have a Visitor account? 1 - YES , 2 - NO : ";
                cin >> haveAcct;

                bool visitorAuth = false;
                string vid, vpass;

                if (haveAcct == 1)
                {
                    cout << "Enter Visitor ID: ";
                    cin >> vid;
                    cout << "Enter Password: ";
                    cin >> vpass;

                    if ( visitorExists(zoo, vid) && authenticate(credentials, vid, vpass) )
                    {
                        cout << "Login Successful. Welcome Visitor " << vid << "!\n";
                        visitorAuth = true;
                        loggedVisitorID = vid;
                    }
                    else
                    {
                        cout << "Login Failed. Returning to Role Menu.\n";
                        visitorAuth = false;
                    }
                }
                else
                {
                    cout << "You chose to book ticket first. Proceed to booking.\n";
                    Visitor temp;
                    temp.bookTicket(zoo.getVisitors());

                    string newTid = zoo.getVisitors().back().getTicketID();
                    string pwd;
                    cout << "Your Ticket ID is: " << newTid << endl;
                    cout << "Set a password for this Ticket ID (so you can login later): ";
                    cin >> pwd;
                    credentials[newTid] = pwd;

                    cout << "Account created. Use Ticket ID and your password to login next time.\n";
                    visitorAuth = true;
                    loggedVisitorID = newTid;
                }

                if (!visitorAuth)
                    break;

                cout << "\nMenu for Visitor:\n1 - Book Ticket\n2 - View Ticket\n3 - View Animals\n4 - Exit\nEnter Your Choice: ";
                cin >> ch1;

                switch(ch1)
                {
                    case 1:
                    {
                        Visitor temp;
                        temp.bookTicket(zoo.getVisitors());
                        break;
                    }

                    case 2:
                        if (loggedVisitorID != "")
                            viewTicketDetails(zoo.getVisitors(), loggedVisitorID);
                        else
                        {
                            cout << "Enter Ticket ID to obtain details: ";
                            cin >> tID1;
                            viewTicketDetails(zoo.getVisitors(), tID1);
                        }
                        break;

                    case 3:
                    {
                        auto &animals = zoo.getAnimals();
                        if (animals.empty())
                            cout << "No animals are currently present in the Zoo\n";
                        else
                        {
                            int count = 1;
                            cout << "Animals currently present in the Zoo: \n";
                            for (const auto &i : animals)
                            {
                                cout << "Animal No " << count << endl;
                                cout << i << endl;
                                count++;
                            }
                        }
                        break;
                    }

                    case 4:
                        cout << "Exiting the Visitor Menu\n";
                        break;

                    default:
                        cout << "Enter Valid Choice!\n";
                }

                break;
            }
            case 2:
            {
                string sid, spass;
                cout << "Enter Staff ID: ";
                cin >> sid;
                cout << "Enter Password: ";
                cin >> spass;

                if (!staffExists(zoo, sid))
                {
                    cout << "No staff found with ID: " << sid << ". Returning to Role Menu.\n";
                    break;
                }
                if (!authenticate(credentials, sid, spass))
                {
                    cout << "Authentication failed. Returning to Role Menu.\n";
                    break;
                }

                cout << "Login Successful. Welcome Staff " << sid << "!\n";
                loggedStaffID = sid;

                cout << "\nMenu for Staff:\n1 - View Animals\n2 - View Staff Details\n3 - Update Animal Health Status\n4 - View available Food Stock\n5 - Exit\nEnter Your Choice: ";
                cin >> ch2;

                switch(ch2)
                {
                    case 1:
                    {
                        auto &animals = zoo.getAnimals();
                        if (animals.empty())
                            cout << "No animals are currently present in the Zoo\n";
                        else
                        {
                            cout << "Animals currently present in the Zoo: \n";
                            for (const auto &i : animals)
                                cout << i << endl;
                        }
                        break;
                    }

                    case 2:
                    {
                        string sID = loggedStaffID;

                        auto &staffList = zoo.getStaffList();
                        bool found = false;
                        for (auto sPtr : staffList)
                        {
                            if (sPtr->getStaffID() == sID)
                            {
                                sPtr->display();
                                found = true;
                                break;
                            }
                        }
                        if (!found)
                            cout << "No staff found with ID: " << sID << endl;

                        break;
                    }

                    case 3:
                    {
                        string aID, newStatus;
                        cout << "Enter Animal ID to update health status: ";
                        cin >> aID;

                        auto &animals = zoo.getAnimals();
                        bool found = false;

                        for (auto &a : animals)
                        {
                            if (a.getAnimalID() == aID)
                            {
                                cout << "Enter new Health Status: ";
                                cin >> newStatus;
                                a.setHealthStatus(newStatus);
                                cout << "Health status updated successfully.\n";
                                found = true;
                                break;
                            }
                        }

                        if (!found)
                            cout << "Animal with ID " << aID << "not found.\n";

                        break;
                    }

                    case 4:
                    {
                        auto &foods = zoo.getFoods();
                        cout << "\nAvailable Food Stock:\n";
                        if (foods.empty())
                            cout << "No food items available.\n";
                        else
                            for (const auto &f : foods)
                                cout << f << endl;
                        break;
                    }

                    case 5:
                        cout << "Exiting the Staff Menu.\n";
                        break;

                    default:
                        cout << "Enter a valid choice!\n";
                }
                break;
            }
            case 3:
            {
                string fsid, fspass;
                cout << "Enter Food Supplier ID: ";
                cin >> fsid;
                cout << "Enter Password: ";
                cin >> fspass;

                if (!authenticate(credentials, fsid, fspass))
                {
                    cout << "Authentication failed or supplier ID not found. Returning to Role Menu.\n";
                    break;
                }

                cout << "Login Successful. Welcome Food Supplier " << fsid << "!\n";

                cout << "\nMenu for Food Supplier:\n1 - View available Food Stock\n2 - Restock Food Items\n3 - View Animals consuming Particular Food\n4 - Update Food Quantity\n5 - Exit\nEnter Your Choice: ";
                cin >> ch3;

                auto &foods = zoo.getFoods();
                auto &animals = zoo.getAnimals();

                switch(ch3)
                {
                    case 1:
                        if (foods.empty())
                            cout << "No food items available.\n";
                        else
                            for (const auto &f : foods)
                                cout << f << endl;
                        break;

                    case 2:
                    {
                        Food temp;
                        temp.restockFood(foods);
                        break;
                    }

                    case 3:
                    {
                        string fid;
                        cout << "Enter Food ID to view consuming animals: ";
                        cin >> fid;

                        bool found = false;
                        for (auto &f : foods)
                        {
                            if (f.getFoodID() == fid)
                            {
                                cout << "Animals consuming " << fid << ":\n";
                                for (const auto &a : f.getConsumingAnimals())
                                    cout << "- " << a << endl;
                                found = true;
                                break;
                            }
                        }

                        if (!found)
                            cout << "Food ID not found.\n";

                        break;
                    }

                    case 4:
                    {
                        string fid;
                        int usedQty;
                        cout << "Enter Food ID: ";
                        cin >> fid;
                        cout << "Enter Quantity used: ";
                        cin >> usedQty;

                        bool updated = false;
                        for (auto &f : foods)
                        {
                            if (f.getFoodID() == fid)
                            {
                                f.reduceQuantity(usedQty);
                                cout << "Stock updated successfully.\n";
                                updated = true;
                                break;
                            }
                        }

                        if (!updated)
                            cout << "Food not found.\n";

                        break;
                    }

                    case 5:
                        cout << "Exiting Food Supplier Menu.\n";
                        break;

                    default:
                        cout << "Enter a valid choice!\n";
                }

                break;
            }
            case 4:
            {
                string mid, mpass;
                cout << "Enter Manager ID: ";
                cin >> mid;
                cout << "Enter Password: ";
                cin >> mpass;

                if (!authenticate(credentials, mid, mpass))
                {
                    cout << "Authentication failed. Returning to Role Menu.\n";
                    break;
                }

                cout << "Login Successful. Welcome Manager " << mid << "!\n";

                cout << "\nMenu for Manager:\n1 - View Total Finance Report\n2 - View All Staff Details\n3 - Add New Animal\n4 - Update Finance Data\n5 - Exit\nEnter Your Choice: ";
                cin >> ch4;

                switch(ch4)
                {
                    case 1:
                        cout << "\nFinance Overview:\n";
                        cout << financeObj;
                        break;

                    case 2:
                    {
                        auto &staffList = zoo.getStaffList();
                        if (staffList.empty())
                            cout << "No staff records available.\n";
                        else
                            for (auto sPtr : staffList)
                                sPtr->display();
                        break;
                    }

                    case 3:
                    {
                        Animal temp;
                        temp.addNewAnimal(zoo.getAnimals());
                        break;
                    }

                    case 4:
                    {
                        int addRev, addExp;
                        cout << "Enter additional revenue to add: ";
                        cin >> addRev;
                        cout << "Enter additional expenses to add: ";
                        cin >> addExp;

                        financeObj.updateFinance(addRev, addExp);
                        cout << "Finance updated successfully.\n";
                        break;
                    }

                    case 5:
                        cout << "Exiting Manager Menu.\n";
                        break;

                    default:
                        cout << "Enter a valid choice!\n";
                }

                break;
            }

            case 5:
                cout << "Exiting the Role Menu\n";
                break;

            default:
                cout << "Enter Valid Choice!\n";
        }

    } while(ch != 5);

    cout << "Thank You for using the Zoo Management System\nHave a Great Day!\n";
    return 0;
}
