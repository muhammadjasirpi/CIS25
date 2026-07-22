#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string diagnosis;
};

struct User {
    string username;
    string password;
    bool isAdmin;
};

vector<User> loadUsers(const string& filename) {
    vector<User> users;
    ifstream fin(filename);
    if (!fin) return users;
    string u, p;
    int adminFlag;
    while (getline(fin, u)) {
        getline(fin, p);
        fin >> adminFlag;
        fin.ignore();
        users.push_back({u, p, adminFlag});
    }
    fin.close();
    return users;
}

void saveUsers(const vector<User>& users, const string& filename) {
    ofstream fout(filename);
    for (const auto& user : users) {
        fout << user.username << endl;
        fout << user.password << endl;
        fout << user.isAdmin << endl;
    }
    fout.close();
}

int userLogin(const vector<User>& users) {
    string u, p;
    cout << "=== User Login ===\n";
    cout << "Username: ";
    getline(cin, u);
    cout << "Password: ";
    getline(cin, p);
    for (unsigned i = 0; i < users.size(); ++i) {
        if (users[i].username == u && users[i].password == p) {
            cout << "Login successful!\n";
            return i;
        }
    }
    cout << "Login failed!\n";
    return -1;
}

void addUser(vector<User>& users, bool isAdmin) {
    string u, p;
    cout << "\n=== Add User ===\n";
    cout << "Enter new username: ";
    getline(cin, u);
    for (const auto& user : users) {
        if (user.username == u) {
            cout << "Username already exists!\n";
            return;
        }
    }
    cout << "Enter new password: ";
    getline(cin, p);
    int adminFlag = 0;
    if (isAdmin) {
        cout << "Is this user an admin? (1 for yes, 0 for no): ";
        cin >> adminFlag; cin.ignore();
    }
    users.push_back({u, p, adminFlag});
    cout << "User added.\n";
}

void changeUserInfo(vector<User>& users, int userIndex) {
    cout << "\n=== Change User Information ===\n";
    cout << "1. Change username\n2. Change password\n";
    cout << "Enter your choice: ";
    int choice; cin >> choice; cin.ignore();
    if (choice == 1) {
        string newUser;
        cout << "Enter new username: ";
        getline(cin, newUser);
        for (const auto& user : users) {
            if (user.username == newUser) {
                cout << "Username already exists!\n";
                return;
            }
        }
        users[userIndex].username = newUser;
        cout << "Username updated.\n";
    } else if (choice == 2) {
        string newPass;
        cout << "Enter new password: ";
        getline(cin, newPass);
        users[userIndex].password = newPass;
        cout << "Password updated.\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

void adminEditUser(vector<User>& users) {
    cout << "\n=== Edit User Information (Admin) ===\n";
    cout << "Available users:\n";
    for (unsigned i = 0; i < users.size(); ++i) {
        cout << i+1 << ". " << users[i].username << (users[i].isAdmin ? " [Admin]" : "") << endl;
    }
    cout << "Select user number to edit: ";
    int index; cin >> index; cin.ignore();
    if (index < 1 || index > (int)users.size()) {
        cout << "Invalid user index.\n";
        return;
    }
    --index;
    cout << "1. Change username\n2. Change password\n3. Change admin status\n";
    cout << "Enter your choice: ";
    int choice; cin >> choice; cin.ignore();
    if (choice == 1) {
        string newUser;
        cout << "Enter new username: ";
        getline(cin, newUser);
        for (const auto& user : users) {
            if (user.username == newUser) {
                cout << "Username already exists!\n";
                return;
            }
        }
        users[index].username = newUser;
        cout << "Username updated.\n";
    } else if (choice == 2) {
        string newPass;
        cout << "Enter new password: ";
        getline(cin, newPass);
        users[index].password = newPass;
        cout << "Password updated.\n";
    } else if (choice == 3) {
        int adminFlag;
        cout << "Enter new admin status (1=admin, 0=user): ";
        cin >> adminFlag; cin.ignore();
        users[index].isAdmin = adminFlag;
        cout << "Admin status updated.\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

void pressEnter() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void loadPatients(Patient*& patients, int& count, int& capacity, const string& filename) {
    ifstream fin(filename);
    count = 0;
    if (!fin) return;
    while (fin >> patients[count].id) {
        fin.ignore();
        getline(fin, patients[count].name);
        fin >> patients[count].age;
        fin.ignore();
        getline(fin, patients[count].gender);
        getline(fin, patients[count].diagnosis);
        count++;
        if (count == capacity) {
            capacity *= 2;
            Patient* temp = new Patient[capacity];
            for (int i = 0; i < count; ++i) temp[i] = patients[i];
            delete[] patients;
            patients = temp;
        }
    }
    fin.close();
}

void savePatients(Patient* patients, int count, const string& filename) {
    ofstream fout(filename);
    for (int i = 0; i < count; i++) {
        fout << patients[i].id << endl;
        fout << patients[i].name << endl;
        fout << patients[i].age << endl;
        fout << patients[i].gender << endl;
        fout << patients[i].diagnosis << endl;
    }
    fout.close();
}

void sortPatients(Patient* patients, int count) {
    sort(patients, patients + count, [](const Patient& a, const Patient& b) {
        return a.id < b.id;
    });
}

int binarySearch(Patient* patients, int count, int id) {
    int left = 0, right = count - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (patients[mid].id == id)
            return mid;
        else if (patients[mid].id < id)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void addPatient(Patient*& patients, int& count, int& capacity) {
    if (count == capacity) {
        capacity *= 2;
        Patient* temp = new Patient[capacity];
        for (int i = 0; i < count; ++i) temp[i] = patients[i];
        delete[] patients;
        patients = temp;
    }
    Patient p;
    cout << "\n=== Add New Patient ===\n";
    cout << "Enter Patient ID (integer): ";
    while (!(cin >> p.id)) {
        cout << "Invalid input. Enter integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, p.name);
    cout << "Enter Age: ";
    while (!(cin >> p.age) || p.age < 0) {
        cout << "Invalid input. Enter non-negative integer for age: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    cout << "Enter Gender: ";
    getline(cin, p.gender);
    cout << "Enter Diagnosis: ";
    getline(cin, p.diagnosis);
    patients[count++] = p;
    sortPatients(patients, count);
    cout << "Patient added successfully.\n";
}

bool isCritical(const Patient& p) {
    string diag = p.diagnosis;
    transform(diag.begin(), diag.end(), diag.begin(), ::tolower);
    return (diag.find("critical") != string::npos ||
            diag.find("emergency") != string::npos ||
            p.age < 1 || p.age > 90);
}

void displayPatients(Patient* patients, int count) {
    if (count == 0) {
        cout << "No patients found.\n";
        return;
    }
    cout << "\n=== Patient Records ===\n";
    for (int i = 0; i < count; ++i) {
        cout << "ID: " << patients[i].id
             << ", Name: " << patients[i].name
             << ", Age: " << patients[i].age
             << ", Gender: " << patients[i].gender
             << ", Diagnosis: " << patients[i].diagnosis;
        if (isCritical(patients[i])) {
            cout << "  [ALERT!]";
        }
        cout << endl;
    }
}

void searchPatient(Patient* patients, int count) {
    int id;
    cout << "\nEnter patient ID to search: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    int idx = binarySearch(patients, count, id);
    if (idx != -1) {
        cout << "Patient found:\n";
        cout << "ID: " << patients[idx].id << ", Name: " << patients[idx].name
             << ", Age: " << patients[idx].age << ", Gender: " << patients[idx].gender
             << ", Diagnosis: " << patients[idx].diagnosis;
        if (isCritical(patients[idx])) cout << "  [ALERT!]";
        cout << endl;
    } else {
        cout << "Patient not found.\n";
    }
}

void updatePatient(Patient* patients, int count) {
    int id;
    cout << "\nEnter patient ID to update: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    int idx = binarySearch(patients, count, id);
    if (idx != -1) {
        cout << "Updating patient " << patients[idx].name << " (ID: " << patients[idx].id << ")\n";
        cin.ignore();
        cout << "Enter new name (current: " << patients[idx].name << "): ";
        getline(cin, patients[idx].name);
        cout << "Enter new age (current: " << patients[idx].age << "): ";
        while (!(cin >> patients[idx].age) || patients[idx].age < 0) {
            cout << "Invalid input. Enter non-negative integer for age: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        cout << "Enter new gender (current: " << patients[idx].gender << "): ";
        getline(cin, patients[idx].gender);
        cout << "Enter new diagnosis (current: " << patients[idx].diagnosis << "): ";
        getline(cin, patients[idx].diagnosis);
        cout << "Patient updated successfully.\n";
    } else {
        cout << "Patient not found.\n";
    }
}

void deletePatient(Patient*& patients, int& count, Patient*& releasedPatients, int& releasedCount, int& releasedCapacity) {
    int id;
    cout << "\nEnter patient ID to delete/release: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    int idx = binarySearch(patients, count, id);
    if (idx != -1) {
        cout << "Patient found: " << patients[idx].name << " (ID: " << patients[idx].id << ")\n";
        cout << "Confirm deletion and move to released patients? (1=yes, 0=no): ";
        int confirm;
        while (!(cin >> confirm)) {
            cout << "Invalid input. Enter 1 or 0: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        
        if (confirm == 1) {
            if (releasedCount == releasedCapacity) {
                releasedCapacity *= 2;
                Patient* temp = new Patient[releasedCapacity];
                for (int i = 0; i < releasedCount; ++i) {
                    temp[i] = releasedPatients[i];
                }
                delete[] releasedPatients;
                releasedPatients = temp;
            }
            
            releasedPatients[releasedCount++] = patients[idx];
            sortPatients(releasedPatients, releasedCount);
            
            for (int i = idx; i < count - 1; ++i) {
                patients[i] = patients[i + 1];
            }
            count--;
            
            cout << "Patient released and moved to released patients list.\n";
        } else {
            cout << "Deletion cancelled.\n";
        }
    } else {
        cout << "Patient not found.\n";
    }
}

void displayReleasedPatients(Patient* releasedPatients, int releasedCount) {
    if (releasedCount == 0) {
        cout << "No released patients found.\n";
        return;
    }
    cout << "\n=== Released Patient Records ===\n";
    for (int i = 0; i < releasedCount; ++i) {
        cout << "ID: " << releasedPatients[i].id
             << ", Name: " << releasedPatients[i].name
             << ", Age: " << releasedPatients[i].age
             << ", Gender: " << releasedPatients[i].gender
             << ", Diagnosis: " << releasedPatients[i].diagnosis << endl;
    }
}

void searchReleasedPatient(Patient* releasedPatients, int releasedCount) {
    int id;
    cout << "\nEnter patient ID to search in released patients: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    int idx = binarySearch(releasedPatients, releasedCount, id);
    if (idx != -1) {
        cout << "Released patient found:\n";
        cout << "ID: " << releasedPatients[idx].id << ", Name: " << releasedPatients[idx].name
             << ", Age: " << releasedPatients[idx].age << ", Gender: " << releasedPatients[idx].gender
             << ", Diagnosis: " << releasedPatients[idx].diagnosis << endl;
    } else {
        cout << "Patient not found in released records.\n";
    }
}

void readmitPatient(Patient*& patients, int& count, int& capacity, Patient*& releasedPatients, int& releasedCount) {
    int id;
    cout << "\nEnter released patient ID to re-admit: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    int idx = binarySearch(releasedPatients, releasedCount, id);
    if (idx != -1) {
        cout << "Released patient found: " << releasedPatients[idx].name << " (ID: " << releasedPatients[idx].id << ")\n";
        cout << "Confirm re-admission? (1=yes, 0=no): ";
        int confirm;
        while (!(cin >> confirm)) {
            cout << "Invalid input. Enter 1 or 0: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        
        if (confirm == 1) {
            if (count == capacity) {
                capacity *= 2;
                Patient* temp = new Patient[capacity];
                for (int i = 0; i < count; ++i) {
                    temp[i] = patients[i];
                }
                delete[] patients;
                patients = temp;
            }
            
            patients[count++] = releasedPatients[idx];
            sortPatients(patients, count);
            
            for (int i = idx; i < releasedCount - 1; ++i) {
                releasedPatients[i] = releasedPatients[i + 1];
            }
            releasedCount--;
            
            cout << "Patient re-admitted to active patient list.\n";
        } else {
            cout << "Re-admission cancelled.\n";
        }
    } else {
        cout << "Patient not found in released records.\n";
    }
}

void loadReleasedPatients(Patient*& releasedPatients, int& releasedCount, int& releasedCapacity, const string& filename) {
    ifstream fin(filename);
    releasedCount = 0;
    if (!fin) return;
    while (fin >> releasedPatients[releasedCount].id) {
        fin.ignore();
        getline(fin, releasedPatients[releasedCount].name);
        fin >> releasedPatients[releasedCount].age;
        fin.ignore();
        getline(fin, releasedPatients[releasedCount].gender);
        getline(fin, releasedPatients[releasedCount].diagnosis);
        releasedCount++;
        if (releasedCount == releasedCapacity) {
            releasedCapacity *= 2;
            Patient* temp = new Patient[releasedCapacity];
            for (int i = 0; i < releasedCount; ++i) {
                temp[i] = releasedPatients[i];
            }
            delete[] releasedPatients;
            releasedPatients = temp;
        }
    }
    fin.close();
}

void saveReleasedPatients(Patient* releasedPatients, int releasedCount, const string& filename) {
    ofstream fout(filename);
    for (int i = 0; i < releasedCount; i++) {
        fout << releasedPatients[i].id << endl;
        fout << releasedPatients[i].name << endl;
        fout << releasedPatients[i].age << endl;
        fout << releasedPatients[i].gender << endl;
        fout << releasedPatients[i].diagnosis << endl;
    }
    fout.close();
}

void emergencyAlert(Patient* patients, int count) {
    cout << "\n=== Emergency Alert: Critical Patients ===\n";
    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (isCritical(patients[i])) {
            cout << "ID: " << patients[i].id
                 << ", Name: " << patients[i].name
                 << ", Age: " << patients[i].age
                 << ", Gender: " << patients[i].gender
                 << ", Diagnosis: " << patients[i].diagnosis << "  [ALERT!]\n";
            found = true;
        }
    }
    if (!found) cout << "No critical patients at this time.\n";
}

void menu(bool isAdmin) {
    cout << "\n=== Hospital Patient Management System ===\n";
    cout << "1. Add a patient\n";
    cout << "2. Display all patients\n";
    cout << "3. Search for a patient by ID (Binary Search)\n";
    cout << "4. Update patient information\n";
    cout << "5. Delete/Release a patient\n";
    cout << "6. Display released patients\n";
    cout << "7. Search released patient\n";
    cout << "8. Re-admit a released patient\n";
    cout << "9. Save patients to file\n";
    cout << "10. Emergency Alert: Critical Patients\n";
    cout << "11. Add User" << (isAdmin ? "" : " (Admin only)") << "\n";
    cout << "12. Edit My User Info\n";
    if (isAdmin) cout << "13. Edit Any User Info (Admin)\n";
    cout << (isAdmin ? "14" : "13") << ". Switch User\n";
    cout << (isAdmin ? "15" : "14") << ". Exit program\n";
}

int main() {
    const string userfile = "users.txt";
    const string patientfile = "patients.txt";
    const string releasedPatientfile = "released_patients.txt";
    
    vector<User> users = loadUsers(userfile);
    if (users.empty()) {
        cout << "No users found. Creating admin user.\n";
        string u, p;
        cout << "Enter admin username: "; getline(cin, u);
        cout << "Enter admin password: "; getline(cin, p);
        users.push_back({u, p, 1});
        saveUsers(users, userfile);
        cout << "Admin user created. Restart program.\n";
        return 0;
    }

    int userIndex = -1;
    while (userIndex < 0) {
        userIndex = userLogin(users);
        if (userIndex < 0) return 1;
    }

    int capacity = 10, count = 0;
    Patient* patients = new Patient[capacity];
    loadPatients(patients, count, capacity, patientfile);
    
    int releasedCapacity = 10, releasedCount = 0;
    Patient* releasedPatients = new Patient[releasedCapacity];
    loadReleasedPatients(releasedPatients, releasedCount, releasedCapacity, releasedPatientfile);

    int choice;
    bool running = true;
    while (running) {
        menu(users[userIndex].isAdmin);
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        
        switch (choice) {
            case 1:
                addPatient(patients, count, capacity); break;
            case 2:
                displayPatients(patients, count); break;
            case 3:
                searchPatient(patients, count); break;
            case 4:
                updatePatient(patients, count); sortPatients(patients, count); break;
            case 5:
                deletePatient(patients, count, releasedPatients, releasedCount, releasedCapacity); break;
            case 6:
                displayReleasedPatients(releasedPatients, releasedCount); break;
            case 7:
                searchReleasedPatient(releasedPatients, releasedCount); break;
            case 8:
                readmitPatient(patients, count, capacity, releasedPatients, releasedCount); break;
            case 9:
                savePatients(patients, count, patientfile); 
                saveReleasedPatients(releasedPatients, releasedCount, releasedPatientfile);
                cout << "All patient data saved to files.\n"; break;
            case 10:
                emergencyAlert(patients, count); break;
            case 11:
                if (users[userIndex].isAdmin) addUser(users, true);
                else cout << "Only admin can add users.\n";
                break;
            case 12:
                changeUserInfo(users, userIndex); break;
            case 13:
                if (users[userIndex].isAdmin) adminEditUser(users);
                else {
                    saveUsers(users, userfile);
                    savePatients(patients, count, patientfile);
                    saveReleasedPatients(releasedPatients, releasedCount, releasedPatientfile);
                    cout << "Logging out...\n";
                    userIndex = userLogin(users);
                    if (userIndex < 0) running = false;
                }
                break;
            case 14:
                if (users[userIndex].isAdmin) {
                    saveUsers(users, userfile);
                    savePatients(patients, count, patientfile);
                    saveReleasedPatients(releasedPatients, releasedCount, releasedPatientfile);
                    cout << "Logging out...\n";
                    userIndex = userLogin(users);
                    if (userIndex < 0) running = false;
                } else {
                    running = false; cout << "Good Bye!\n";
                }
                break;
            case 15:
                if (users[userIndex].isAdmin) {
                    running = false; cout << "Good Bye!\n";
                } else cout << "Invalid choice.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
        saveUsers(users, userfile);
        if (running) pressEnter();
    }
    savePatients(patients, count, patientfile);
    saveReleasedPatients(releasedPatients, releasedCount, releasedPatientfile);
    delete[] patients;
    delete[] releasedPatients;
    return 0;
}
