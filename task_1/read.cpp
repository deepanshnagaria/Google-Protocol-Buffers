#pragma comment(lib, "Ws2_32.lib") // essential for linking as given in issue  

#include <iostream>
#include <fstream>
#include <string>
#include "interns.pb.h"
#include "read.h"
using namespace std;

// Iterates though all people in the AddressBook and prints info about them.
void ListPeople(const task_1::Interns& interns) {
    for (int i = 0; i < interns.people_size(); i++) {
        const task_1::Person& person = interns.people(i);

        cout << "Person ID: " << person.id() << endl;
        cout << "  Name: " << person.name() << endl;

        if(person.team()==task_1::Person::SOFTWARE)
            cout << "  Team: Software" << endl;
        else
            cout << "  Team: Hardware" << endl;
       
        if (person.has_email()) {
            cout << "  E-mail address: " << person.email() << endl;
        }

        if (person.has_college()) {
            cout << "  College: " << person.college() << endl;
        }

        for (int j = 0; j < person.phones_size(); j++) {
            const task_1::Person::PhoneNumber& phone_number = person.phones(j);

            switch (phone_number.type()) {
            case task_1::Person::MOBILE:
                cout << "  Mobile phone #: ";
                break;
            case task_1::Person::HOME:
                cout << "  Home phone #: ";
                break;
            case task_1::Person::WORK:
                cout << "  Work phone #: ";
                break;
            }
            cout << phone_number.number() << endl;
        }
    }
}

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int read(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
        return -1;
    }

    task_1::Interns interns;

    {
        // Read the existing interns.
        fstream input(argv[1], ios::in | ios::binary);
        if (!interns.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }

    ListPeople(interns);

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}