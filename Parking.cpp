
#include <bits/stdc++.h>
using namespace std;

class Vehicle {
public:
    string number;
    string type;
    int entryTime;

    Vehicle(string num, string t, int time) {
        number = num;
        type = t;
        entryTime = time;
    }
};

class ParkingSystem {
private:
    int capacity;
    vector<Vehicle*> slots;

    string toLower(string s) {
        for (char &c : s) c = tolower(c);
        return s;
    }

public:
    ParkingSystem(int cap) {
        capacity = cap;
        slots.resize(capacity, nullptr);
    }

    bool isValidTime(int time) {
        return (time >= 0 && time <= 23);
    }

    bool isDuplicate(string num) {
        for (auto v : slots) {
            if (v != nullptr && v->number == num)
                return true;
        }
        return false;
    }

    void parkVehicle(string num, string type, int time) {
        type = toLower(type);

        if (type != "car" && type != "bike") {
            cout << "Invalid vehicle type! Use car/bike\n";
            return;
        }

        if (isDuplicate(num)) {
            cout << "Vehicle already parked!\n";
            return;
        }

        for (int i = 0; i < capacity; i++) {
            if (slots[i] == nullptr) {
                slots[i] = new Vehicle(num, type, time);
                cout << "Vehicle parked at slot " << i + 1 << endl;
                return;
            }
        }

        cout << "Parking Full! Cannot allow new vehicle\n";
    }

    void removeVehicle(string num, int exitTime) {
        for (int i = 0; i < capacity; i++) {
            if (slots[i] != nullptr && slots[i]->number == num) {

                if (exitTime < slots[i]->entryTime) {
                    cout << "Invalid exit time!\n";
                    return;
                }

                int duration = exitTime - slots[i]->entryTime;
                int rate = (slots[i]->type == "car") ? 20 : 10;
                int fee = duration * rate;

                cout << "Vehicle removed from slot " << i + 1 << endl;
                cout << "Type: " << slots[i]->type << endl;
                cout << "Duration: " << duration << " hours\n";
                cout << "Parking Fee: Rs." << fee << endl;

                delete slots[i];
                slots[i] = nullptr;
                return;
            }
        }

        cout << "Vehicle not found!\n";
    }

    void display() {
        cout << "\nParking Status:\n";
        for (int i = 0; i < capacity; i++) {
            if (slots[i] == nullptr)
                cout << "Slot " << i + 1 << ": Empty\n";
            else
                cout << "Slot " << i + 1 << ": "
                     << slots[i]->number << " (" << slots[i]->type << ")\n";
        }
    }

    void searchVehicle(string num) {
        for (int i = 0; i < capacity; i++) {
            if (slots[i] != nullptr && slots[i]->number == num) {
                cout << "Vehicle found at slot " << i + 1 << endl;
                return;
            }
        }
        cout << "Vehicle not found!\n";
    }

    ~ParkingSystem() {
        for (auto v : slots) {
            delete v;
        }
    }
};

int main() {
    int cap;
    cout << "Enter total parking slots: ";
    cin >> cap;

    ParkingSystem ps(cap);

    int choice;
    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Display Slots\n";
        cout << "4. Search Vehicle\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string num, type;
            int time;

            cout << "Enter vehicle number: ";
            cin >> num;
            cout << "Enter type (car/bike): ";
            cin >> type;

            while (true) {
                cout << "Enter entry time (0-23): ";
                cin >> time;

                if (ps.isValidTime(time)) break;
                cout << "Invalid time! Enter between 0 and 23.\n";
            }

            ps.parkVehicle(num, type, time);
        }
        else if (choice == 2) {
            string num;
            int time;

            cout << "Enter vehicle number: ";
            cin >> num;

            while (true) {
                cout << "Enter exit time (0-23): ";
                cin >> time;

                if (ps.isValidTime(time)) break;
                cout << "Invalid time! Enter between 0 and 23.\n";
            }

            ps.removeVehicle(num, time);
        }
        else if (choice == 3) {
            ps.display();
        }
        else if (choice == 4) {
            string num;
            cout << "Enter vehicle number: ";
            cin >> num;
            ps.searchVehicle(num);
        }
        else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
