#include <iostream>
#include <chrono>
#include <cstdio>
using namespace std;
using namespace std::chrono;

class Array {
    int* arr;
    int capacity;
    int size;

public:
    Array(int cap) : capacity(cap), size(0) {
        arr = new int[cap];
    }

    // Insert at the end
    void insertAtEnd(int value) {
        if (size < capacity) {
            arr[size] = value;
            size++;
        }
    }

    // Insert at the beginning
    void insertAtBeginning(int value) {
        if (size < capacity) {
            for (int i = size; i > 0; i--) {
                arr[i] = arr[i - 1];
            }
            arr[0] = value;
            size++;
        }
    }

    // Search for an element
    int search(int value) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == value)
                return i;
        }
        return -1; // Element not found
    }
};

// Definition of a Node for the linked list
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}  // Constructor
};

// Singly Linked List Class
class LinkedList {
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Insert at the end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Insert at the beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Search for an element
    int search(int value) {
        Node* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;  // Element not found
    }

    // Delete from the end
    void deleteAtEnd() {
        if (head == nullptr) return;  // List is empty

        if (head->next == nullptr) {  // Only one node
            delete head;
            head = nullptr;
            return;
        }

        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }

        delete current->next;
        current->next = nullptr;
    }

    // Delete from the beginning
    void deleteAtBeginning() {
        if (head == nullptr) return;  // List is empty

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Destructor to free allocated memory
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};


// Queue class using linked list
class Queue {
private:
    Node* front;  // Pointer to the front of the queue
    Node* rear;   // Pointer to the rear of the queue

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Enqueue operation
    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (rear) {
            rear->next = newNode;  // Link new node to the rear
        }
        rear = newNode;            // Update rear to new node
        if (!front) {
            front = rear;          // If the queue was empty, front is also new node
        }
    }

    // Dequeue operation
    void dequeue() {
        if (front) {
            Node* temp = front;     // Temporarily store the front node
            front = front->next;    // Move front to the next node
            delete temp;            // Delete the old front node
            if (!front) {
                rear = nullptr;      // If the queue is now empty, reset rear
            }
        }
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Peek at the front element
    int peek() {
        if (front) {
            return front->data;     // Return the data at the front
        }
        throw std::runtime_error("Queue is empty");  // Handle empty queue
    }
};


class ArrayQueue {
private:
    int* arr;      // Array to hold the queue elements
    int capacity;  // Maximum number of elements
    int front;     // Index of the front element
    int rear;      // Index of the last element
    int size;      // Current number of elements

public:
    ArrayQueue(int cap) : capacity(cap), front(0), rear(-1), size(0) {
        arr = new int[cap];
    }

    ~ArrayQueue() {
        delete[] arr; // Clean up dynamically allocated memory
    }

    // Enqueue (insert) an element
    void enqueue(int value) {
        if (size < capacity) {
            rear = (rear + 1) % capacity; // Circular increment
            arr[rear] = value;
            size++;
        }
        else {
            cout << "Queue is full!" << endl;
        }
    }

    // Dequeue (remove) an element
    int dequeue() {
        if (size > 0) {
            int value = arr[front];
            front = (front + 1) % capacity; // Circular increment
            size--;
            return value;
        }
        else {
            cout << "Queue is empty!" << endl;
            return -1; // Indicate empty queue
        }
    }

    // Check if the queue is empty
    bool isEmpty() {
        return size == 0;
    }

    // Check if the queue is full
    bool isFull() {
        return size == capacity;
    }
};

int main() {
    cout << "Enter the Size of array on which to perform insertion at end : ";
    int n = 0;
    cin >> n;

    Array arr1(n);
    double timecostend = 0;
    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            arr1.insertAtEnd(i);
        }
        auto end = high_resolution_clock::now();

        duration<double, milli> duration_op = end - start;

        cout << "Operation took: " << duration_op.count() << " ms" << endl;
        timecostend = timecostend + duration_op.count();
    }
    timecostend = timecostend / 10;
    printf("INSERTION AT END ON AVERAGE TOOK : %.4f ms", timecostend);
    cout << endl;

    cout << endl;
    int a = 0;
    cout << "Enter the Size of array on which to perform insertion at beginning : ";
    cin >> a;

    Array arr2(a);
    double timecostbeg = 0;
    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < a; ++i) {
            arr2.insertAtBeginning(i);
        }
        auto end = high_resolution_clock::now();

        duration<double, milli> duration_op = end - start;

        cout << "Operation took: " << duration_op.count() << " ms" << endl;
        timecostbeg = timecostbeg + duration_op.count();
    }
    timecostbeg = timecostbeg / 10;
    printf("INSERTION AT THE BEGINNING ON AVERAGE TOOK : %.4f ms", timecostbeg);
    cout << endl;

    cout << endl;

    cout << "Performing Search Array : ";
    double timecostsrch = 0;
    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        arr2.search(i);
        auto end = high_resolution_clock::now();

        duration<double, milli> duration_op = end - start;

        cout << "Operation took: " << duration_op.count() << " ms" << endl;
        timecostsrch = timecostsrch + duration_op.count();
    }
    timecostsrch = timecostsrch / 10;
    printf("SEARCH ON AVERAGE TOOK : %.4f ms", timecostsrch);
    cout << endl;

    cout << endl;

    cout << "Enter the size of linked list to perform insertion at end: ";
    int llsize;
    cin >> llsize;

    LinkedList list1;
    double timeCostEnd = 0;

    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        for (int j = 0; j < llsize; ++j) {
            list1.insertAtEnd(j);
        }
        auto end = high_resolution_clock::now();
        duration<double, milli> durationOp = end - start;
        cout << "Insertion at end took: " << durationOp.count() << " ms" << endl;
        timeCostEnd += durationOp.count();
    }
    timeCostEnd /= 10;
    printf("Insertion at end on average took: %.4f ms\n", timeCostEnd);

    cout << "\nEnter the size of linked list to perform insertion at beginning: ";
    int d;
    cin >> d;

    LinkedList list2;
    double timeCostBeg = 0;

    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        for (int j = 0; j < d; ++j) {
            list2.insertAtBeginning(j);
        }
        auto end = high_resolution_clock::now();
        duration<double, milli> durationOp = end - start;
        cout << "Insertion at beginning took: " << durationOp.count() << " ms" << endl;
        timeCostBeg += durationOp.count();
    }
    timeCostBeg /= 10;
    printf("Insertion at beginning on average took: %.4f ms\n", timeCostBeg);

    cout << "\nPerforming search on linked list: ";
    double timeCostSearch = 0;

    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        for (int j = 0; j < d; ++j) {
            list2.search(j);
        }
        auto end = high_resolution_clock::now();
        duration<double, milli> durationOp = end - start;
        cout << "Search took: " << durationOp.count() << " ms" << endl;
        timeCostSearch += durationOp.count();
    }
    timeCostSearch /= 10;
    printf("Search on average took: %.4f ms\n", timeCostSearch);

    cout << "\nPerforming deletion at end: ";
    double timeCostDelEnd = 0;

    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        for (int j = 0; j < llsize; ++j) {
            list1.deleteAtEnd();
        }
        auto end = high_resolution_clock::now();
        duration<double, milli> durationOp = end - start;
        cout << "Deletion at end took: " << durationOp.count() << " ms" << endl;
        timeCostDelEnd += durationOp.count();
    }
    timeCostDelEnd /= 10;
    printf("Deletion at end on average took: %.4f ms\n", timeCostDelEnd);

    cout << "\nPerforming deletion at beginning: ";
    double timeCostDelBeg = 0;

    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        for (int j = 0; j < d; ++j) {
            list2.deleteAtBeginning();
        }
        auto end = high_resolution_clock::now();
        duration<double, milli> durationOp = end - start;
        cout << "Deletion at beginning took: " << durationOp.count() << " ms" << endl;
        timeCostDelBeg += durationOp.count();
    }
    timeCostDelBeg /= 10;
    printf("Deletion at beginning on average took: %.4f ms\n", timeCostDelBeg);



    cout << "Enter the size of the queue for enqueue operation: ";
    int queueSize;
    cin >> queueSize;

    Queue queue1;
    double timeCostEnqueue = 0;

    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        for (int j = 0; j < queueSize; ++j) {
            queue1.enqueue(j);
        }
        auto end = high_resolution_clock::now();
        duration<double, milli> durationOp = end - start;
        cout << "Enqueue operation took: " << durationOp.count() << " ms" << endl;
        timeCostEnqueue += durationOp.count();
    }
    timeCostEnqueue /= 10;
    printf("Enqueue on average took: %.4f ms\n", timeCostEnqueue);

    // Measure dequeue time
    cout << "\nPerforming dequeue operations: ";
    double timeCostDequeue = 0;

    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        for (int j = 0; j < queueSize; ++j) {
            queue1.dequeue();
        }
        auto end = high_resolution_clock::now();
        duration<double, milli> durationOp = end - start;
        cout << "Dequeue operation took: " << durationOp.count() << " ms" << endl;
        timeCostDequeue += durationOp.count();
    }
    timeCostDequeue /= 10;
    printf("Dequeue on average took: %.4f ms\n", timeCostDequeue);

    cout << "Enter the size of the array to perform enqueue operation: ";

    double timeCostEnqueue2 = 0;
    int q;
    cin >> q;

    ArrayQueue queue(q);
    auto start = high_resolution_clock::now();
    for (int j = 0; j < q; j++) {
        queue.enqueue(j);
    }
    auto end = high_resolution_clock::now();
    duration<double, milli> durationOp = end - start;
    timeCostEnqueue2 += durationOp.count();

    printf("Enqueue on average took: %.4f ms\n", timeCostEnqueue2);

    // Timing dequeue operation
    cout << "\nPerforming dequeue operation: ";
    double timeCostDequeue2 = 0;

    auto start1 = high_resolution_clock::now();
    for (int j = 0; j < q; j++) { // Ensure to dequeue only as many as were enqueued
        queue.dequeue();
    }
    auto end1 = high_resolution_clock::now();
    duration<double, milli> durationOp1 = end1 - start1;
    timeCostDequeue2 += durationOp1.count();

    printf("Dequeue on average took: %.4f ms\n", timeCostDequeue2);

    return 0;
}
