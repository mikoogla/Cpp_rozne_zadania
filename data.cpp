#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

class Record {
public:
    string name;
    string surname;
    string address;
    string pesel;

    Record() {
        name = "null";
        surname = "null";
        address = "null";
        pesel = "null";
    }

    Record(string nam, string sur, string add, string pes) {
        create(
                std::move(nam), std::move(sur),
                std::move(add), std::move(pes)
        );
    }

    void create(string nam, string sur, string add, string pes) {
        name = std::move(nam);
        surname = std::move(sur);
        address = std::move(add);
        pesel = std::move(pes);
    }
};

class Data {
public:
    int size = 0;
    vector<Record> database;
    Record temp;

    Data() {
        temp.create("Jan", "Kowalski", "Kolejowa 123", "67122144214");
        database.push_back(temp);

        temp.create("Rew", "Kaddaki", "Plac Jana Pawla 67A", "82073124236");
        database.push_back(temp);

        temp.create("Niwrad", "Darwin", "Pilsudskiego 32/12", "93062079235");
        database.push_back(temp);
        size += 3;
    }

    void view() {
        if (size == 0) {
            cout << "Database is empty\n";
            return;
        }
        for (int i = 0; i < size; i++) {
            printf("Name: ");
            cout << database[i].name << "\t";
            printf("Surname: ");
            cout << database[i].surname << "\t";
            printf("Address: ");
            cout << database[i].address << "\t";
            printf("Pesel: ");
            cout << database[i].pesel << "\t\n";
        }
    }

    void add(string nam, string sur, string add, string pes) {
        temp.create(std::move(nam), std::move(sur), std::move(add), std::move(pes));
        database.push_back(temp);
        size++;
        cout << "[1 RECORD ADDED]\n";
    }

    void create() {
        getchar();
        string name, surname, pesel, address;
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter surname: ";
        getline(cin, surname);
        cout << "Enter pesel: ";
        getline(cin, pesel);
        cout << "Enter address: ";
        getline(cin, address);
        add(name, surname, address, pesel);
    }

    void remove() {
        if (size == 0) {
            cout << "Database is empty\n";
            return;
        }
        int i;
        string pesel;
        cout << "[Removing record] Enter pesel: ";
        cin >> pesel;

        for (i = 0; i < size; i++) {
            if (database[i].pesel == pesel) goto removal;
        }
        cout << "Record with pesel " << pesel << " does not exist in database\n";
        return;
        removal:
        {
            vector<Record>::iterator iterator;
            iterator = database.begin() + i;
            database.erase(iterator);
            size--;
        };
        cout << "Element removed\n";
    }


};

int main() {
    int choice = 0;
    Data db1;
    while (true) {
        cout << "1 - add record | 2 - remove record \n3 - view database | 4 - exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                db1.create();
                break;
            case 2:
                db1.remove();
                break;
            case 3:
                db1.view();
                break;
            default:
                return 0;
        }
        printf("\n");
    }
}