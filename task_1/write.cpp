// task_1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#pragma comment(lib, "Ws2_32.lib") // essential for linking as given in issue  

#include "write.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <C:/Users/Deepansh/source/repos/task_1/task_1/interns.pb.h>

void PromptForIntern(task_1::Person* person) {
    cout << "Enter person ID number: ";
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout << "Enter name: ";
    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none): ";
    string email;
    getline(cin, email);
    if (!email.empty()) {
        person->set_email(email);
    }

    cout << "Enter college (blank for skipping): ";
    string college;
    getline(cin, college);
    if (!college.empty()) {
        person->set_college(college);
    }

    cout << "Team? Software/Hardware : ";
    string team;
    getline(cin, team);
    if (team == "Software")
        person->set_team(task_1::Person::SOFTWARE);
    else if (team == "Hardware")
        person->set_team(task_1::Person::HARDWARE);
    else
        cout << "Invalid Choice:: Using Default"<<endl;

    while (true) {
        cout << "Enter a phone number (or leave blank to finish): ";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }

        task_1::Person::PhoneNumber* phone_number = person->add_phones();
        phone_number->set_number(number);

        cout << "Is this a mobile, home, or work phone? ";
        string type;
        getline(cin, type);
        if (type == "mobile") {
            phone_number->set_type(task_1::Person::MOBILE);
        }
        else if (type == "home") {
            phone_number->set_type(task_1::Person::HOME);
        }
        else if (type == "work") {
            phone_number->set_type(task_1::Person::WORK);
        }
        else {
            cout << "Unknown phone type.  Using default." << endl;
        }
    }
}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
int write(int argc, char* argv[])
{
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        cerr << "Usage:  " << argv[0] << " Intern_FILE" << endl;
        return -1;
    }

    task_1::Interns interns;

    {
        // Read the existing address book.
        fstream input(argv[1], ios::in | ios::binary);
        if (!input) {
            cout << argv[1] << ": File not found.  Creating a new file." << endl;
        }
        else if (!interns.ParseFromIstream(&input)) {
            cerr << "Failed to parse intern binary file." << endl;
            return -1;
        }
    }

    // Add an address.
    PromptForIntern(interns.add_people());

    {
        // Write the new address book back to disk.
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if (!interns.SerializeToOstream(&output)) {
            cerr << "Failed to write address book." << endl;
            return -1;
        }
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}

