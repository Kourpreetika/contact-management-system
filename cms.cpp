#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

class Contact {
public:
    string fname, lname, address, email;
    long long phone;

    void input() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "First Name: ";
        getline(cin, fname);

        cout << "Last Name: ";
        getline(cin, lname);

        cout << "Phone: ";
        cin >> phone;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Address: ";
        getline(cin, address);

        cout << "Email: ";
        getline(cin, email);
    }

    void display() const {
        cout << "\n-------------------------\n";
        cout << "Name    : " << fname << " " << lname << endl;
        cout << "Phone   : " << phone << endl;
        cout << "Address : " << address << endl;
        cout << "Email   : " << email << endl;
    }
};

// Save to file
void saveToFile(const vector<Contact>& contacts) {
    ofstream file("contacts.txt");

    for (const auto& c : contacts) {
        file << c.fname << "|"
             << c.lname << "|"
             << c.phone << "|"
             << c.address << "|"
             << c.email << endl;
    }
}

// Load from filecd contact_management_
void loadFromFile(vector<Contact>& contacts) {
    ifstream file("contacts.txt");

    Contact c;
    while (getline(file, c.fname, '|')) {
        getline(file, c.lname, '|');
        file >> c.phone;
        file.ignore();
        getline(file, c.address, '|');
        getline(file, c.email);

        contacts.push_back(c);
    }
}

// Add Contact
void addContact(vector<Contact>& contacts) {
    Contact c;
    c.input();

    // Check duplicate
    for (const auto& existing : contacts) {
        if (existing.phone == c.phone) {
            cout << "\nContact already exists!\n";
            return;
        }
    }

    contacts.push_back(c);
    cout << "\nContact added successfully!\n";
}

// Show All
void showContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "\nNo contacts found.\n";
        return;
    }

    for (const auto& c : contacts) {
        c.display();
    }
}

// Search
void searchContact(const vector<Contact>& contacts) {
    long long num;
    cout << "Enter phone: ";
    cin >> num;

    for (const auto& c : contacts) {
        if (c.phone == num) {
            c.display();
            return;
        }
    }

    cout << "\nContact not found.\n";
}

// Delete
void deleteContact(vector<Contact>& contacts) {
    long long num;
    cout << "Enter phone to delete: ";
    cin >> num;

    for (auto it = contacts.begin(); it != contacts.end(); ++it) {
        if (it->phone == num) {
            contacts.erase(it);
            cout << "\nDeleted successfully!\n";
            return;
        }
    }

    cout << "\nContact not found.\n";
}

// Edit
void editContact(vector<Contact>& contacts) {
    long long num;
    cout << "Enter phone to edit: ";
    cin >> num;

    for (auto& c : contacts) {
        if (c.phone == num) {
            cout << "\nEnter new details:\n";
            c.input();
            cout << "\nUpdated successfully!\n";
            return;
        }
    }

    cout << "\nContact not found.\n";
}

int main() {
    vector<Contact> contacts;
    loadFromFile(contacts);

    int choice;

    while (true) {
        cout << "\n===== CONTACT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Edit Contact\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addContact(contacts); break;
            case 2: showContacts(contacts); break;
            case 3: searchContact(contacts); break;
            case 4: deleteContact(contacts); break;
            case 5: editContact(contacts); break;

            case 0:
                saveToFile(contacts);
                cout << "\nData saved. Exiting...\n";
                return 0;

            default:
                cout << "\nInvalid choice!\n";
        }
    }
}