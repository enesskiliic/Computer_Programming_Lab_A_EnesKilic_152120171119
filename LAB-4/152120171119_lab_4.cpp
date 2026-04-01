#include <iostream>
#include <string>
using namespace std;

struct Package
{
    string packageID;
    string destinationCity;
    int dimensions[3];
    Package* next;
};

Package* top = nullptr;

void push(string id, string city, int Length, int Width, int Height) {
    Package* p = new Package();
    p->packageID = id;
    p->destinationCity = city;
    p->dimensions[0] = Length;
    p->dimensions[1] = Width;
    p->dimensions[2] = Height;
    p->next = top;
    top = p;
}

Package* pop() {
    if (top == nullptr) { cout << "There is no cargo packages.\n"; return nullptr; }
    Package* p = top;
    top = top->next;
    return p;
}

struct Courier
{
    string courierName;
    string vehicleType;
};

Courier arr[5];
int front = 0;
int rear = -1;
int queueCount = 0;

void enqueue(string name, string vehicle) {
    if (queueCount == 5) { cout << "Kuyruk dolu!\n"; return; }
    rear = (rear + 1) % 5;
    arr[rear].courierName = name;
    arr[rear].vehicleType = vehicle;
    queueCount++;
}

Courier dequeue() {
    Courier c = arr[front];
    front = (front + 1) % 5;
    queueCount--;
    return c;
}

void display() {
    cout << "\n-- Packages --\n";
    Package* cur = top;
    while (cur) {
        cout << "[" << cur->packageID << "] " << cur->destinationCity
             << " " << cur->dimensions[0] << "x"
                    << cur->dimensions[1] << "x"
                    << cur->dimensions[2] << "\n";
        cur = cur->next;
    }

    cout << "\n-- Couriers --\n";
    for (int i = 0; i < queueCount; i++) {
        int idx = (front + i) % 5;
        cout << arr[idx].courierName << " - " << arr[idx].vehicleType << "\n";
    }
}


void dispatch() {
    if (top == nullptr || queueCount == 0) {
        cout << "There is no cargos/couriers to dispatch.\n";
        return;
    }
    Courier c = dequeue();
    Package* p = pop();
    cout << "\n-- Dispatch --\n" << c.courierName << " (" << c.vehicleType << ")"
         << " - " << p->packageID << " " << p->destinationCity << "\n";
    delete p;
}


int main() {
    push("PKG-001", "Ankara",   30, 20, 15);
    push("PKG-002", "Eskisehir", 50, 40, 30);
    push("PKG-003", "Izmir",    25, 25, 25);

    enqueue("Ahmet", "Motosiklet");
    enqueue("Fatma", "Bisiklet");
    enqueue("Mehmet", "Araba");

    display();

    dispatch();
    dispatch();

    display();

    return 0;
}