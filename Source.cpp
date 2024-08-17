
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;
template <typename T>
struct Martyr {
    int Age;
    T Name;
    T Gender;
    T Eventlocation;
    T dateOfDeath;
    Martyr* next;

    Martyr(int age, const T& name, T gender, const T& eventLocation, const T& dateOfDeath)
        : Age(age), Name(name), Gender(gender), Eventlocation(eventLocation), dateOfDeath(dateOfDeath), next(nullptr) {}

    Martyr() : Age(0), next(nullptr) {}

    Martyr& operator=(const Martyr& other) {
        if (this != &other) {
            Age = other.Age;
            Name = other.Name;
            Gender = other.Gender;
            Eventlocation = other.Eventlocation;
            dateOfDeath = other.dateOfDeath;
            
        }
        return *this;
    }
};


template <typename T>
struct Vector {
    Martyr<T>* head;
    Vector() : head(nullptr) {}
};

template <typename T>
struct Stack {
    Martyr<T>* top;
};

template <typename T>
struct Location {
    T Name;
    Vector<T> vector;
    Stack<T> stack;
    Location* next;

    Location() : vector(), stack(), next(nullptr) {}
};


template <typename T>
void deleteVector(Vector<T>& v) {
    Martyr<T>* p = v.head;
    Martyr<T>* q;

    while (p) {
        q = p->next;
        delete p;
        p = q;
    }

    v.head = nullptr;
}

template <typename T>
void deleteStack(Stack<T>& s) {
    Martyr<T>* p = s.top;
    Martyr<T>* q;

    while (p) {
        q = p->next;
        delete p;
        p = q;
    }

    s.top = nullptr;
}
template <typename T>
bool operator <(T a, T b) {
    return a < b;
}
template <typename T>
bool operator >(T a, T b) {
    return a > b;
}

template <typename T>
Location<T>* createNodeforLocation(const T& name) {
    Location<T>* newLoc = new Location<T>;
    newLoc->Name = name;
    newLoc->vector.head = nullptr;
    newLoc->stack.top = nullptr;
    newLoc->next = nullptr;
    return newLoc;
}


template <typename T>
Location<T>* insertLocationRecord(Location<T>*& head, const T& name) {
    Location<T>* newLoc = createNodeforLocation(name);

    Location<T>* p = head;
    Location<T>* z = nullptr;

    while (p && p->Name < name) {
        z = p;
        p = p->next;
    }

    if (!z) {
        newLoc->next = head;
        head = newLoc;
    }
    else {
        newLoc->next = p;
        z->next = newLoc;
    }

    return head;
}

template <typename T>
void updateLocation(Location<T>*& head, const T& updateName) {
    Location<T>* p = head;

    while (p && p->Name != updateName) {
        p = p->next;
    }

    if (p) {
        cout << "please insert update location  name    " << updateName << ":" << endl;
        cin >> p->Name;
        cout << "Updated  !" << endl;
    }
    else {
        cout << " cant update ! " << endl;
    }
}


template <typename T>
void deleteLocation(Location<T>*& head, const T& deletedName) {
    Location<T>* p = head; // p point to current location
    Location<T>* q = nullptr; // q point to previous location

    while (p && p->Name != deletedName) {
        q = p;
        p = p->next;
    }

    if (p) {
        if (!q) {
            head = p->next;
        }
        else {
            q->next = p->next;
        }

        deleteVector(p->vector);
        deleteStack(p->stack);

        delete p;

        cout << deletedName << " the location is now deleted " << endl;
    }
    else {
        cout << "there is no location with this name ! " << endl;
    }
}

template <typename T>
Location<T>* searchforLocation(Location<T>* head, const T& name) {
    Location<T>* p = head;

    while (p && p->Name != name) {
        p = p->next;
    }

    return p;
}

Martyr<string>* CreateNodeforMartyr(const string& name, int age, const string& Eventloc, const string& Dofdeath, char gender) {
    Martyr<string>* newMart = new Martyr<string>;

    newMart->Name = name;
    newMart->Age = age;
    newMart->Eventlocation = Eventloc;
    newMart->dateOfDeath = Dofdeath;
    newMart->Gender = gender;
    newMart->next = nullptr;

    return newMart;
}

template <typename T>
void deleteMartyrFromLocation(Location<T>* loc) {
    T martyrName;
    cout << "Enter the name of the martyr to delete: ";
    cin >> martyrName;


    Martyr<T>* currentMartyrFromVector = loc->vector.head;
    Martyr<T>* prevMartyrInVector = nullptr;

    while (currentMartyrFromVector && currentMartyrFromVector->Name != martyrName) {
        prevMartyrInVector = currentMartyrFromVector;
        currentMartyrFromVector = currentMartyrFromVector->next;
    }

    if (currentMartyrFromVector) {
        if (!prevMartyrInVector) {
            loc->vector.head = currentMartyrFromVector->next;
        }
        else {
            prevMartyrInVector->next = currentMartyrFromVector->next;
        }


        Martyr<T>* currentMartyrInStack = loc->stack.top;
        Martyr<T>* prevMartyrInStack = nullptr;

        while (currentMartyrInStack && currentMartyrInStack->Name != martyrName) {
            prevMartyrInStack = currentMartyrInStack;
            currentMartyrInStack = currentMartyrInStack->next;
        }

        if (currentMartyrInStack) {
            if (!prevMartyrInStack) {
                loc->stack.top = currentMartyrInStack->next;
            }
            else {
                prevMartyrInStack->next = currentMartyrInStack->next;
            }

            delete currentMartyrFromVector;
            delete currentMartyrInStack;

            cout << martyrName << " Martyr deleted" << endl;
        }
        else {
            cout << "Martyr not in stack  " << endl;
        }
    }
    else {
        cout << "we cant find Maryr" << endl;
    }
}


template <typename T>
void insertMartyr(Vector<T>& v, Martyr<T>* newMartyr) {
    Martyr<T>* p = v.head;
    Martyr<T>* q = nullptr;

    while (p && p->Name < newMartyr->Name) {
        q = p;
        p = p->next;
    }

    if (!q) {
        newMartyr->next = v.head;
        v.head = newMartyr;
    }
    else {
        newMartyr->next = p;
        q->next = newMartyr;
    }
}

template <typename T>
Martyr<T>* insertNewMartyrRecord(Location<T>* location) {
    Martyr<T>* newMartyr = nullptr;

    T martyrName;
    int martyrAge;
    T martyrLocation;
    T martyrDateOfDeath;
    char martyrGender;

    cout << " **********    MARTYR INFORMATION     ********** :    " << endl;
    cout << " Name of Martyr: " << endl;
    cin >> martyrName;
    cout << " Martyr Age: " << endl;
    cin >> martyrAge;
    cout << " Event Location: " << endl;
    cin >> martyrLocation;
    cout << " Date of Death: " << endl;
    cin >> martyrDateOfDeath;
    cout << " Martyr Gender: " << endl;
    cin >> martyrGender;

    newMartyr = CreateNodeforMartyr(martyrName, martyrAge, martyrLocation, martyrDateOfDeath, martyrGender);

   insertMartyr<T>(location->vector, newMartyr); 


    return newMartyr;
}

template <typename T>
void updateMartyrInfo(Vector<T>& v) {
    T martyrName;
    int martyrAge;
    T martyrLocation;
    T martyrDateOfDeath;
    char martyrGender;

    cout << "insert the name of martyr to update: ";
    cin >> martyrName;

    Martyr<T>* M = v.head;
    Martyr<T>* previous = nullptr;

    while (M && M->Name != martyrName) {
        previous = M;
        M = M->next;
    }

    if (M) {
        cout << "    insert updated Martyr information   " << endl;;
        cout << "Updated Name: ";
        cin >> martyrName;
        cout << "Updated Age: ";
        cin >> martyrAge;
        cout << "Updated Event Location: ";
        cin >> martyrLocation;
        cout << "Updated Date of Death: ";
        cin >> martyrDateOfDeath;
        cout << "Updated Gender: ";
        cin >> martyrGender;

       
        M->Name = martyrName;
        M->Age = martyrAge;
        M->Eventlocation = martyrLocation;
        M->dateOfDeath = martyrDateOfDeath;
        M->Gender = martyrGender;

        cout << "Martyr information updated " << endl;
    }
    else {
        cout << "we can't find this martyr " << endl;
    }
}

template <typename T>
void SearchMartyr(const Vector<T>& v, const T& name) {
    Martyr<T>* p = v.head;

    while (p && p->Name != name) {
        p = p->next;
    }

    if (p) {
        cout << "Martyr information that you search about :" << endl;
        cout << "Martyr Name: " << p->Name << endl;
        cout << "Martyr Age: " << p->Age << endl;
        cout << "Martyr Event Location: " << p->Eventlocation << endl;
        cout << "Martyr Date of Death: " << p->dateOfDeath << endl;
        cout << "Martyr Gender: " << p->Gender << endl;
    }
    else {
        cout << "we cant fint this Martyr that you search about it " << endl;
    }
}


void displayMartyrsMenu() {
    cout << "Martyrs Menu:" << endl;
    cout << "1. Insert a New Martyr Record" << endl;
    cout << "2. Update a Martyr Record" << endl;
    cout << "3. Delete a Martyr Record" << endl;
    cout << "4. Search for a Martyr by Name" << endl;
}

void martyrsMenu(Location<string>* location) {
    int choice = 0;
    string searchName;

    while (choice != 4) {
        displayMartyrsMenu();
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            insertNewMartyrRecord(location);
            break;
        case 2:
            updateMartyrInfo(location->vector);
            break;
        case 3:
            deleteMartyrFromLocation(location);
            break;
        case 4:
            cout << "Enter the name of the martyr to search: ";
            cin >> searchName;
            SearchMartyr(location->vector, searchName);
            break;
        
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}



template <typename T>
void viewMartyrsInformation(const Vector<T>& vector) {
    Martyr<T>* currentMartyr = vector.head;

    while (currentMartyr) {
        cout << "Name: " << currentMartyr->Name << ", Age: " << currentMartyr->Age
            << ", Event Location: " << currentMartyr->Eventlocation
            << ", Date of Death: " << currentMartyr->dateOfDeath
            << ", Gender: " << currentMartyr->Gender << endl;

        currentMartyr = currentMartyr->next;
    }
}


template <typename T>
void viewMartyrsInformationFromStack(const Stack<T>& stack) {
    Martyr<T>* currentMartyr = stack.top;

    while (currentMartyr) {
        cout << "Name: " << currentMartyr->Name << ", Age: " << currentMartyr->Age
            << ", Event Location: " << currentMartyr->Eventlocation
            << ", Date of Death: " << currentMartyr->dateOfDeath
            << ", Gender: " << currentMartyr->Gender << endl;

        currentMartyr = currentMartyr->next;
    }
}
template <typename T>
int countMartyrsOnDate(const Vector<T>& vector, const T& date) {
    int count = 0;

    if (vector.head) {
        Martyr<T>* currentMartyr = vector.head;

        while (currentMartyr) {

            if (currentMartyr->dateOfDeath == date) {
                count++;
            }
            currentMartyr = currentMartyr->next;
        }
    }

    return count;
}

template <typename T>
void findMinMartyrsDate(const Location<T>& locationData, T& minDate) {
    int minMartyrs = INT_MAX;
    Martyr<T>* currentMartyr = locationData.stack.top;

    if (!currentMartyr) {
        minDate = "No martyrs in the stack";
        return;
    }

    while (currentMartyr) {
        int martyrsCount = countMartyrsOnDate(locationData.vector, currentMartyr->dateOfDeath);

        if (martyrsCount < minMartyrs) {
            minMartyrs = martyrsCount;
            minDate = currentMartyr->dateOfDeath;
        }

        currentMartyr = currentMartyr->next;
    }
}


template <typename T>
int countMartyrsInLocation(const Location<T>* location) {
    int count = 0;

    Martyr<T>* currentMartyr = location->vector.head;

    while (currentMartyr) {
        count++;
        currentMartyr = currentMartyr->next;
    }

    return count;
}

template <typename T>
void generateAndDisplayStatisticsReport(const Location<T>* loc) {
    int numberOfMartyrs = countMartyrsInLocation(loc);

    cout << "     Statistics Report for the Selected Location:   " << endl;

    cout << "a.The numbers of martyrs in the selected location. : " << numberOfMartyrs << endl;

    cout << "b. Print the Martyrs’ full information in that location.:" << endl;
    viewMartyrsInformation(loc->vector);

    cout << "c.Traverse the stack(i.e., start from the latest date back to the earliest) and print the Martyrs full information :" << endl;
    viewMartyrsInformationFromStack(loc->stack);

    T minDate;
    findMinMartyrsDate(*loc, minDate);
    cout << "d.	Report the date that had the minimum number of martyrs. " << minDate << endl;
}

template <typename T>
void readDataFromCSV(const string& filePath, Location<T>*& head) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Cannot opening the file " << filePath << "'" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t i = 0;
        while (i < line.length()) {
            string token = "";
            while (i < line.length() && line[i] != ',') {
                if (line[i] != '\0' && line[i] != ' ') {
                    token += line[i];
                }
                i++;
            }


            string filteredToken = "";
            for (char c : token) {
                if (c != '\0') {
                    filteredToken += c;
                }
            }


            Martyr<T>* newMartyr = CreateNodeforMartyr(filteredToken, 0, "palestenian location", "2023-01-01", '\0');


            if (!head) {

                head = createNodeforLocation(filteredToken); 
            }
            else {

                if (!head->vector.head) {
                    head->vector.head = newMartyr;
                }
                else {
                   insertMartyr(head->vector, newMartyr);
                }
            }

            i++;
        }
    }

    file.close();
}

template <typename T>
void saveToFile(const Location<T>* head, const char* filename) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "cant opening " << endl;
        return;
    }

    const Location<T>* currentLocation = head;

    while (currentLocation) {
        outFile << "Location: " << currentLocation->Name << endl;

        Martyr<T>* currentMartyr = currentLocation->vector.head;
        while (currentMartyr) {
            outFile << "Martyr: " << currentMartyr->Name << "," << currentMartyr->Age << ","<< currentMartyr->Eventlocation << ","<< currentMartyr->dateOfDeath << "," << currentMartyr->Gender << endl;

            currentMartyr = currentMartyr->next;
        }

        currentLocation = currentLocation->next;
    }

    outFile.close();
    cout << "the data saved in file " << endl;
}

int main()
{
    Location<string>* head = nullptr;

    readDataFromCSV("btselem.csv", head);
    int choice;
    cout << "Location Menu:" << endl;
    cout << "1. Option to insert new location record" << endl;
    cout << "2. Option to update an existing location" << endl;
    cout << "3. Option to delete an existing location" << endl;
    cout << "4. Option to search for a location record" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
    case 1: {
        string name;
        cout << "Please insert name of the new location: ";
        cin >> name;
        insertLocationRecord(head, name);
        break;
    }
    case 2: {
        string name;
        cout << "Please insert name of the location to update: ";
        cin >> name;
        updateLocation(head, name);
        break;
    }
    case 3: {
        string name;
        cout << "Please insert name of the location to delete: ";
        cin >> name;
        deleteLocation(head, name);
        break;
    }
    case 4: {
        int cho;
        cout << "11. Martyrs Menu" << endl;
        cout << "21. Statistics Report" << endl;
        cout << "Enter your choice: ";

        cin >> cho;

        if (cho == 11) {
            martyrsMenu(head);
        }
        else if (cho == 21) {
            generateAndDisplayStatisticsReport(head);
        }
        else {
            cout << "Invalid choice." << endl;
        }
        break;
    }

    default:
        cout << "Invalid choice." << endl;
    }   
    char save;
    cout << "Do you want to save the changes to the file?" << endl;
    cout << "a. Yes i want to save" << endl;
    cout << "b. No i dont want" << endl;
    cout << "Enter your choice: ";
    cin >> save;

    if (save == 'a' || save == 'A') {

        saveToFile(head, "btselem.csv");
        cout << "Changes saved to the file." << endl;
    }
    else {
        cout << "Changes not saved." << endl;
    }
  

    return 0;
}




