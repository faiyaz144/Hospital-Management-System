#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Patient {
    string name;
    int id;
    string disease;
    string doctor;
};
// added coment
// Function to add a new patient
void addPatient(vector<Patient>& patients) {
    Patient newPatient;
    cout << "Enter patient name: ";
    cin.ignore(); // Clear newline character from previous input
    getline(cin, newPatient.name);
    cout << "Enter patient ID: ";
    cin >> newPatient.id;
    cout << "Enter disease: ";
    cin.ignore();
    getline(cin, newPatient.disease);
    cout << "Enter doctor name: ";
    cin.ignore();
    getline(cin, newPatient.doctor);
    patients.push_back(newPatient);
    cout << "Patient added successfully!" << endl;
}

// Function to display all patients
void displayPatients(const vector<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients found." << endl;
    } else {
        cout << "--------------------------------------------------" << endl;
        cout << "Name\t\tID\t\tDisease\t\tDoctor" << endl;
        cout << "--------------------------------------------------" << endl;
        for (const Patient& patient : patients) {
            cout << patient.name << "\t\t" << patient.id << "\t\t" << patient.disease << "\t\t" << patient.doctor << endl;
        }
        cout << "--------------------------------------------------" << endl;
    }
}

// Function to search for a patient by ID
void searchPatient(const vector<Patient>& patients) {
    int id;
    cout << "Enter patient ID to search: ";
    cin >> id;
    bool found = false;
    for (const Patient& patient : patients) {
        if (patient.id == id) {
            cout << "Patient Found:" << endl;
            cout << "Name: " << patient.name << endl;
            cout << "ID: " << patient.id << endl;
            cout << "Disease: " << patient.disease << endl;
            cout << "Doctor: " << patient.doctor << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Patient not found." << endl;
    }
}

// Function to delete a patient by ID
void deletePatient(vector<Patient>& patients) {
    int id;
    cout << "Enter patient ID to delete: ";
    cin >> id;
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if (it->id == id) {
            patients.erase(it);
            cout << "Patient deleted successfully!" << endl;
            return;
        }
    }
    cout << "Patient not found." << endl;
}

// Function to save patient data to a file
void saveToFile(const vector<Patient>& patients) {
    ofstream outfile("patients.txt");
    if (outfile.is_open()) {
        for (const Patient& patient : patients) {
            outfile << patient.name << "," << patient.id << "," << patient.disease << "," << patient.doctor << endl;
        }
        outfile.close();
        cout << "Data saved to file successfully!" << endl;
    } else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

// Function to load patient data from a file
void loadFromFile(vector<Patient>& patients) {
    ifstream infile("patients.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            Patient patient;
            size_t pos1 = line.find(",");
            patient.name = line.substr(0, pos1);
            line = line.substr(pos1 + 1);
            size_t pos2 = line.find(",");
            patient.id = stoi(line.substr(0, pos2));
            line = line.substr(pos2 + 1);
            size_t pos3 = line.find(",");
            patient.disease = line.substr(0, pos3);
            patient.doctor = line.substr(pos3 + 1);
            patients.push_back(patient);
        }
        infile.close();
        cout << "Data loaded from file successfully!" << endl;
    } else {
        cout << "Error: Unable to open file for reading." << endl;
    }
}

int main() {
    vector<Patient> patients;
    int choice;

    // Load data from file (optional)
    loadFromFile(patients);

    do {
        cout << "\nHospital Management System" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Display Patients" << endl;
        cout << "3. Search Patient" << endl;
        cout << "4. Delete Patient" << endl;
        cout << "5. Save Data" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPatient(patients);
                break;
            case 2:
                displayPatients(patients);
                break;
            case 3:
                searchPatient(patients);
                break;
            case 4:
                deletePatient(patients);
                break;
            case 5:
                saveToFile(patients);
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
