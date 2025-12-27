#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <conio.h>
using namespace std;

class library {
private:
    struct Node {
        int id, quantity;
        string name, auther, publisher, category;
        Node* next_add;
    };

public:
    Node* head = nullptr;

    void menu();
    void insert();
    void search();
    void update();
    void del();
    void sort();
    void show();
    void showCreatorDetails();

    void saveToFile();
    void loadFromFile();
};


// LOGIN
bool login() {
    string user, pass;
    cout << "\n\n\t\tLIBRARY MANAGEMENT SYSTEM - LOGIN";
    cout << "\n Username: ";
    cin >> user;
    cout << "\n Password: ";
    cin >> pass;

    if (user == "zainab" && pass == "2903") {
        cout << "\n Login successful!";
        Sleep(1000);
        return true;
    }
    else {
        cout << "\n Invalid details!";
        return false;
    }
}


// SAVE TO FILE
void library::saveToFile() {
    ofstream outFile("library_data.txt");
    Node* ptr = head;

    while (ptr != nullptr) {
        outFile << ptr->id << ","
                << ptr->name << ","
                << ptr->auther << ","
                << ptr->publisher << ","
                << ptr->quantity << ","
                << ptr->category << endl;
        ptr = ptr->next_add;
    }
    cout << "\n Data saved.";
}


// LOAD FROM FILE
void library::loadFromFile() {
    ifstream inFile("library_data.txt");
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        Node* newNode = new Node;

        getline(ss, line, ','); newNode->id = stoi(line);
        getline(ss, newNode->name, ',');
        getline(ss, newNode->auther, ',');
        getline(ss, newNode->publisher, ',');
        getline(ss, line, ','); newNode->quantity = stoi(line);
        getline(ss, newNode->category, ',');

        newNode->next_add = head;
        head = newNode;
    }
}


// MENU
void library::menu() {
    system("cls");

    int choice;
    cout << "\n\n===== LIBRARY MANAGEMENT SYSTEM =====";
    cout << "\n 1. Insert New Record";
    cout << "\n 2. Search Record (By ID)";
    cout << "\n 3. Update Record";
    cout << "\n 4. Delete Record";
    cout << "\n 5. Show All Records";
    cout << "\n 6. Show Creator Details";
    cout << "\n 7. Exit";

    cout << "\n\n Enter Your Choice: ";
    cin >> choice;

    switch (choice) {
    case 1: insert(); break;
    case 2: search(); break;
    case 3: update(); break;
    case 4: del(); break;
    case 5: sort(); show(); menu(); break;
    case 6: showCreatorDetails(); getch(); menu(); break;
    case 7: exit(0);
    default:
        cout << "\n Invalid Input!";
        getch();
        menu();
    }
}


// INSERT
void library::insert() {
    system("cls");
    Node* new_node = new Node;

    cout << "\n Book ID: ";
    cin >> new_node->id;

    cout << "\n Book Name: ";
    cin >> new_node->name;

    cout << "\n Author Name: ";
    cin >> new_node->auther;

    cout << "\n Publisher Name: ";
    cin >> new_node->publisher;

    cout << "\n Category: ";
    cin >> new_node->category;

    cout << "\n Quantity: ";
    cin >> new_node->quantity;

    new_node->next_add = nullptr;

    if (head == nullptr)
        head = new_node;
    else {
        Node* ptr = head;
        while (ptr->next_add != nullptr)
            ptr = ptr->next_add;
        ptr->next_add = new_node;
    }

    cout << "\n Book Inserted Successfully!";
    saveToFile();
    getch();
    menu();
}


// SEARCH
void library::search() {
    system("cls");

    if (head == nullptr) {
        cout << "\n No Records Found!";
        getch();
        menu();
        return;
    }

    int t_id;
    cout << "\n Enter Book ID: ";
    cin >> t_id;

    Node* ptr = head;

    while (ptr != nullptr) {
        if (ptr->id == t_id) {
            cout << "\n Book Found!";
            cout << "\n ID: " << ptr->id;
            cout << "\n Name: " << ptr->name;
            cout << "\n Author: " << ptr->auther;
            cout << "\n Publisher: " << ptr->publisher;
            cout << "\n Category: " << ptr->category;
            cout << "\n Quantity: " << ptr->quantity;

            getch();
            menu();
            return;
        }
        ptr = ptr->next_add;
    }

    cout << "\n Book Not Found!";
    getch();
    menu();
}



// UPDATE
void library::update() {
    system("cls");

    if (!head) {
        cout << "\n No Records Found!";
        getch();
        menu();
        return;
    }

    int t_id;
    cout << "\n Enter Book ID To Update: ";
    cin >> t_id;

    Node* ptr = head;

    while (ptr != nullptr) {
        if (ptr->id == t_id) {

            cout << "\n New Book Name: ";
            cin >> ptr->name;

            cout << "\n New Author: ";
            cin >> ptr->auther;

            cout << "\n New Publisher: ";
            cin >> ptr->publisher;

            cout << "\n New Category: ";
            cin >> ptr->category;

            cout << "\n New Quantity: ";
            
            cin >> ptr->quantity;

            cout << "\n Book Updated Successfully!";
            saveToFile();
            getch();
            menu();
            return;
        }
        ptr = ptr->next_add;
    }

    cout << "\n Book ID Not Found!";
    getch();
    menu();
}



// DELETE
void library::del() {
    system("cls");

    if (!head) {
        cout << "\n No Records Found!";
        getch();
        menu();
        return;
    }

    int t_id;
    cout << "\n Enter Book ID To Delete: ";
    cin >> t_id;

    Node* ptr = head;
    Node* prev = nullptr;

    while (ptr != nullptr) {

        if (ptr->id == t_id) {

            if (prev == nullptr)
                head = ptr->next_add;  
            else
                prev->next_add = ptr->next_add;

            delete ptr;

            cout << "\n Book Deleted Successfully!";
            saveToFile();
            getch();
            menu();
            return;
        }

        prev = ptr;
        ptr = ptr->next_add;
    }

    cout << "\n Book ID Not Found!";
    getch();
    menu();
}



// ⭐ FIXED SORT (CORRECT VERSION)
void library::sort() {
    if (!head) return;

    for (Node* i = head; i != nullptr; i = i->next_add) {
        for (Node* j = i->next_add; j != nullptr; j = j->next_add) {
            if (i->id > j->id) {

                // Swap ONLY data (not pointers)
                swap(i->id, j->id);
                swap(i->name, j->name);
                swap(i->auther, j->auther);
                swap(i->publisher, j->publisher);
                swap(i->category, j->category);
                swap(i->quantity, j->quantity);
            }
        }
    }
}



// SHOW (WORKING NOW ✔)
void library::show() {
    system("cls");

    if (!head) {
        cout << "\n No Records Found!";
        getch();
        return;
    }

    Node* ptr = head;

    while (ptr != nullptr) {
        cout << "\n ID: " << ptr->id;
        cout << "\n Name: " << ptr->name;
        cout << "\n Author: " << ptr->auther;
        cout << "\n Publisher: " << ptr->publisher;
        cout << "\n Category: " << ptr->category;
        cout << "\n Quantity: " << ptr->quantity;
        cout << "\n-----------------------------------------------";

        ptr = ptr->next_add;
    }

    cout << "\n\nPress any key to return...";
    getch();
}



// CREATOR INFO
void library::showCreatorDetails() {
    cout << "\n==================================================\n";
    cout << "            DSA Project: Library Management System\n";
    cout << "==================================================\n";
    cout << " Subject       : Data Structures & Algorithms (DSA)\n";
    cout << " Instructor    : Aleema Imran\n";
    cout << " Technology    : Singly Linked List (Data Structure)\n";
    cout << " Functionality : Book Insert, Search, Update, Delete, Sort, etc.\n";
    cout << "--------------------------------------------------\n";
    cout << " Project Created By:\n";
    cout << " 1. Zainab-Afzal     | Roll Number: FA24-BCS-147\n";
    cout << " Department         :  Computer Science \n";
    cout << " Session            : Fall 2024\n";
    cout << " Institution        : COMSATS University, Sahiwal\n";
    cout << "==================================================\n";
}



// MAIN
int main() {

    library obj;
    obj.loadFromFile();

    if (login())
        obj.menu();
    else {
        Sleep(1000);
        exit(0);
    }
}
