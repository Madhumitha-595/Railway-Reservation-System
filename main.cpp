#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

// ===============================
// Passenger - Linked List
// ===============================
struct Passenger {
    int id;
    string name;
    int age;
    string trainName;
    string seatNumber;
    Passenger* next;
};

// ===============================
// BST Node - Passenger Search
// ===============================
struct BSTNode {
    Passenger data;
    BSTNode* left;
    BSTNode* right;
};

// ===============================
// Railway Reservation System
// ===============================
class RailwayReservationSystem {

private:
    Passenger* head;                 // Linked List
    queue<Passenger> waitingList;    // Queue
    stack<Passenger> cancelledTickets; // Stack
    BSTNode* root;                   // BST

    int totalSeats;
    int availableSeats;
    int nextPassengerID;
    int nextSeatNumber;

public:

    // Constructor
    RailwayReservationSystem() {
        head = nullptr;
        root = nullptr;

        totalSeats = 5;
        availableSeats = 5;

        nextPassengerID = 1001;
        nextSeatNumber = 1;
    }

    // ===============================
    // Create BST Node
    // ===============================
    BSTNode* createBSTNode(Passenger p) {
        BSTNode* newNode = new BSTNode;

        newNode->data = p;
        newNode->left = nullptr;
        newNode->right = nullptr;

        return newNode;
    }

    // ===============================
    // Insert into BST
    // ===============================
    BSTNode* insertBST(BSTNode* node, Passenger p) {

        if (node == nullptr) {
            return createBSTNode(p);
        }

        if (p.id < node->data.id) {
            node->left = insertBST(node->left, p);
        }
        else if (p.id > node->data.id) {
            node->right = insertBST(node->right, p);
        }

        return node;
    }

    // ===============================
    // Search BST
    // ===============================
    BSTNode* searchBST(BSTNode* node, int id) {

        if (node == nullptr || node->data.id == id) {
            return node;
        }

        if (id < node->data.id) {
            return searchBST(node->left, id);
        }

        return searchBST(node->right, id);
    }

    // ===============================
    // Book Ticket
    // ===============================
    void bookTicket() {

        Passenger p;

        cout << "\n========== BOOK TICKET ==========\n";

        cout << "Enter Passenger Name: ";
        cin.ignore();
        getline(cin, p.name);

        cout << "Enter Age: ";
        cin >> p.age;

        cout << "Enter Train Name: ";
        cin.ignore();
        getline(cin, p.trainName);

        p.id = nextPassengerID++;

        if (availableSeats > 0) {

            p.seatNumber = "S" + to_string(nextSeatNumber++);

            // Add to Linked List
            p.next = head;
            head = new Passenger(p);

            // Add to BST
            root = insertBST(root, p);

            availableSeats--;

            cout << "\nTicket booked successfully!\n";
            cout << "Passenger ID : " << p.id << endl;
            cout << "Name         : " << p.name << endl;
            cout << "Train        : " << p.trainName << endl;
            cout << "Seat Number  : " << p.seatNumber << endl;
        }
        else {

            p.seatNumber = "WAITING";

            // Add to Queue
            waitingList.push(p);

            cout << "\nNo seats available.\n";
            cout << "Passenger added to waiting list.\n";
            cout << "Passenger ID : " << p.id << endl;
        }
    }

    // ===============================
    // Cancel Ticket
    // ===============================
    void cancelTicket() {

        cout << "\n========== CANCEL TICKET ==========\n";

        if (head == nullptr) {
            cout << "No passengers to cancel.\n";
            return;
        }

        int id;

        cout << "Enter Passenger ID to cancel: ";
        cin >> id;

        Passenger* current = head;
        Passenger* previous = nullptr;

        while (current != nullptr && current->id != id) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Passenger not found.\n";
            return;
        }

        // Remove from Linked List
        if (previous == nullptr) {
            head = current->next;
        }
        else {
            previous->next = current->next;
        }

        // Add to Stack
        cancelledTickets.push(*current);

        cout << "\nTicket cancelled successfully!\n";
        cout << "Passenger ID   : " << current->id << endl;
        cout << "Passenger Name : " << current->name << endl;

        delete current;

        availableSeats++;

        if (!waitingList.empty()) {
            cout << "\nA seat is now available.\n";
            cout << "Process the waiting list to assign the seat.\n";
        }
    }

    // ===============================
    // Display Waiting List
    // ===============================
    void displayWaitingList() {

        cout << "\n========== WAITING LIST ==========\n";

        if (waitingList.empty()) {
            cout << "Waiting list is empty.\n";
            return;
        }

        queue<Passenger> temp = waitingList;

        while (!temp.empty()) {

            Passenger p = temp.front();

            cout << "\nPassenger ID : " << p.id;
            cout << "\nName         : " << p.name;
            cout << "\nAge          : " << p.age;
            cout << "\nTrain        : " << p.trainName;
            cout << "\nStatus       : Waiting\n";

            temp.pop();
        }
    }

    // ===============================
    // Search Passenger using BST
    // ===============================
    void searchPassenger() {

        cout << "\n========== SEARCH PASSENGER ==========\n";

        int id;

        cout << "Enter Passenger ID: ";
        cin >> id;

        BSTNode* result = searchBST(root, id);

        if (result == nullptr) {
            cout << "\nPassenger not found.\n";
        }
        else {

            cout << "\nPassenger Found!\n";
            cout << "Passenger ID : " << result->data.id << endl;
            cout << "Name         : " << result->data.name << endl;
            cout << "Age          : " << result->data.age << endl;
            cout << "Train        : " << result->data.trainName << endl;
            cout << "Seat Number  : " << result->data.seatNumber << endl;
        }
    }

    // ===============================
    // Display Passengers
    // ===============================
    void displayPassengers() {

        cout << "\n========== CONFIRMED PASSENGERS ==========\n";

        if (head == nullptr) {
            cout << "No confirmed passengers.\n";
            return;
        }

        Passenger* current = head;

        while (current != nullptr) {

            cout << "\nPassenger ID : " << current->id;
            cout << "\nName         : " << current->name;
            cout << "\nAge          : " << current->age;
            cout << "\nTrain        : " << current->trainName;
            cout << "\nSeat Number  : " << current->seatNumber;
            cout << "\n-----------------------------";

            current = current->next;
        }
    }

    // ===============================
    // Process Waiting List
    // ===============================
    void processWaitingList() {

        cout << "\n========== PROCESS WAITING LIST ==========\n";

        if (waitingList.empty()) {
            cout << "Waiting list is empty.\n";
            return;
        }

        if (availableSeats <= 0) {
            cout << "No seats currently available.\n";
            return;
        }

        // Remove first passenger from Queue
        Passenger p = waitingList.front();
        waitingList.pop();

        p.seatNumber = "S" + to_string(nextSeatNumber++);

        // Add to Linked List
        p.next = head;
        head = new Passenger(p);

        // Add to BST
        root = insertBST(root, p);

        availableSeats--;

        cout << "\nWaiting passenger successfully allotted a ticket!\n";
        cout << "Passenger ID : " << p.id << endl;
        cout << "Name         : " << p.name << endl;
        cout << "Train        : " << p.trainName << endl;
        cout << "Seat Number  : " << p.seatNumber << endl;
    }

    // ===============================
    // Display Cancelled Tickets
    // ===============================
    void displayCancelledTickets() {

        cout << "\n========== CANCELLED TICKETS ==========\n";

        if (cancelledTickets.empty()) {
            cout << "No cancelled tickets.\n";
            return;
        }

        stack<Passenger> temp = cancelledTickets;

        while (!temp.empty()) {

            Passenger p = temp.top();

            cout << "\nPassenger ID : " << p.id;
            cout << "\nName         : " << p.name;
            cout << "\nTrain        : " << p.trainName;
            cout << "\nSeat Number  : " << p.seatNumber;
            cout << "\n-----------------------------";

            temp.pop();
        }
    }

    // ===============================
    // Display Seat Status
    // ===============================
    void displaySeatStatus() {

        cout << "\n========== SEAT STATUS ==========\n";

        cout << "Total Seats     : " << totalSeats << endl;
        cout << "Available Seats : " << availableSeats << endl;
        cout << "Booked Seats    : "
             << totalSeats - availableSeats << endl;
        cout << "Waiting List    : "
             << waitingList.size() << endl;
    }

    // ===============================
    // Main Menu
    // ===============================
    void menu() {

        int choice;

        do {

            cout << "\n\n";
            cout << "============================================\n";
            cout << "       RAILWAY RESERVATION SYSTEM\n";
            cout << "============================================\n";

            cout << "1. Book Ticket\n";
            cout << "2. Cancel Ticket\n";
            cout << "3. Display Waiting List\n";
            cout << "4. Search Passenger\n";
            cout << "5. Display Passengers\n";
            cout << "6. Process Waiting List\n";
            cout << "7. Display Cancelled Tickets\n";
            cout << "8. Display Seat Status\n";
            cout << "9. Exit\n";

            cout << "============================================\n";

            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {

                case 1:
                    bookTicket();
                    break;

                case 2:
                    cancelTicket();
                    break;

                case 3:
                    displayWaitingList();
                    break;

                case 4:
                    searchPassenger();
                    break;

                case 5:
                    displayPassengers();
                    break;

                case 6:
                    processWaitingList();
                    break;

                case 7:
                    displayCancelledTickets();
                    break;

                case 8:
                    displaySeatStatus();
                    break;

                case 9:
                    cout << "\nThank you for using Railway Reservation System!\n";
                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 9);
    }
};

// ===============================
// Main Function
// ===============================
int main() {

    RailwayReservationSystem railway;

    railway.menu();

    return 0;
}
