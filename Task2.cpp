#include <iostream>
#include <string>
using namespace std;

// Structure for Print Job
struct PrintJob {
    int jobId;
    string documentName;
    int pages; };

// Node structure for Queue
class QueueNode {
public:
    PrintJob job;
    QueueNode* next;
    QueueNode(PrintJob j) {
        job = j;
        next = nullptr;}
};

// Linked Queue Implementation
class LinkedQueue {
private:
    QueueNode* frontPtr;
    QueueNode* rearPtr;
    int jobCount;
public:
    LinkedQueue() {
        frontPtr = nullptr;
        rearPtr = nullptr;
        jobCount = 0; }

    ~LinkedQueue() { clearQueue(); }

    bool isEmpty() {
        return frontPtr == nullptr;}

    void addJob(int id, string doc, int pages) {
        PrintJob newJob = {id, doc, pages};
        QueueNode* newNode = new QueueNode(newJob);
        if (isEmpty()) {
            frontPtr = rearPtr = newNode;
        } else {
            rearPtr->next = newNode;
            rearPtr = newNode; 
        }
        jobCount++;
        cout << "Job added successfully!\n";}

    void processJob() {
        if (isEmpty()) {
            cout << "Queue is empty! Cannot process job.\n";
            return; 
        }
        QueueNode* temp = frontPtr;
        cout << "Processing -> Job ID: " << temp->job.jobId 
             << ", Document: " << temp->job.documentName 
             << ", Pages: " << temp->job.pages << "\n";
        frontPtr = frontPtr->next;
        if (frontPtr == nullptr) {
            rearPtr = nullptr; // Queue becomes empty
        }
        delete temp;
        jobCount--; 
    }

    void viewNextJob() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return; }
        cout << "Next Job -> ID: " << frontPtr->job.jobId 
             << ", Document: " << frontPtr->job.documentName 
             << ", Pages: " << frontPtr->job.pages << "\n";
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        QueueNode* curr = frontPtr;
        cout << "--- Current Waiting Jobs (Front to Rear) ---\n";
        while (curr != nullptr) {
            cout << "[Job ID: " << curr->job.jobId << ", Doc: " << curr->job.documentName 
                 << ", Pages: " << curr->job.pages << "]\n";
            curr = curr->next; }
    }

    int countJobs() {
        return jobCount;}

    void clearQueue() {
        while (!isEmpty()) {
            QueueNode* temp = frontPtr;
            frontPtr = frontPtr->next;
            delete temp;
        }
        rearPtr = nullptr;
        jobCount = 0; }
};

int main() {
    LinkedQueue printerQueue;
    int choice;
    do {
        cout << "\n======== Task 2: Printer Job Scheduling =======\n";
        cout << "1. Add Job\n";
        cout << "2. Process Job\n";
        cout << "3. View Next Job\n";
        cout << "4. Display All Jobs\n";
        cout << "5. Count Waiting Jobs\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, pages;
                string docName;
                cout << "Enter Job ID: ";
                cin >> id;
                cout << "Enter Document Name: ";
                cin >> docName;
                cout << "Enter Number of Pages: ";
                cin >> pages;
                printerQueue.addJob(id, docName, pages);
                break;
            }
            case 2:
                printerQueue.processJob();
                break;
            case 3:
                printerQueue.viewNextJob();
                break;
            case 4:
                printerQueue.displayQueue();
                break;
            case 5:
                cout << "Total waiting jobs: " << printerQueue.countJobs() << "\n";
                break;
            case 6:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    return 0;
}