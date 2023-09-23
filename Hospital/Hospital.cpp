// Hospital.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_PATIENTS = 100; 


class Patient
{
public:
    string name;
    string admissionDate;
    string dischargeDate;
    string diagnosis;
    string treatingDoctor;

    Patient() : name(""), admissionDate(""), dischargeDate(""), diagnosis(""), treatingDoctor("") {}


    Patient(const string& _name, const string& _admissionDate, const string& _dischargeDate, const string& _diagnosis, const string& _treatingDoctor)
        : name(_name), admissionDate(_admissionDate), dischargeDate(_dischargeDate), diagnosis(_diagnosis), treatingDoctor(_treatingDoctor) {}
};


class Hospital
{
private:
    Patient patients[MAX_PATIENTS]; 
    int numberOfPatients; 

public:
    Hospital() : numberOfPatients(0) {}

    
    bool addPatient(const Patient& newPatient)
    {
        if (numberOfPatients < MAX_PATIENTS)
        {
            patients[numberOfPatients++] = newPatient;
            return true;
        }
        else
        {
            cout << "Error: Maximum number of patients exceeded." << endl;
            return false;
        }
    }

    
    void displayPatients() 
    {
        for (int i = 0; i < numberOfPatients; ++i) 
        {
            cout << "Patient " << (i + 1) << ":" << endl;
            cout << "Name: " << patients[i].name << endl;
            cout << "Admission Date: " << patients[i].admissionDate << endl;
            cout << "Discharge Date: " << patients[i].dischargeDate << endl;
            cout << "Diagnosis: " << patients[i].diagnosis << endl;
            cout << "Treating Doctor: " << patients[i].treatingDoctor << endl;
            cout << endl;
        }
    }

    
    void writeToFile(const string& fileName)
    {
        ofstream file(fileName);
        if (file.is_open())
        {
            for (int i = 0; i < numberOfPatients; ++i)
            {
                file << "Name: " << patients[i].name << endl;
                file << "Admission Date: " << patients[i].admissionDate << endl;
                file << "Discharge Date: " << patients[i].dischargeDate << endl;
                file << "Diagnosis: " << patients[i].diagnosis << endl;
                file << "Treating Doctor: " << patients[i].treatingDoctor << endl;
                file << endl;
            }
            file.close();
            cout << "Data successfully written to the file." << endl;
        }
        else 
        {
            cout << "Error: Unable to open the file for writing." << endl;
        }
    }

   
    void readFromFile(const string& fileName) 
    {
        ifstream file(fileName);
        if (file.is_open())
        {
            numberOfPatients = 0;
            string ignore;
            while (!file.eof() && numberOfPatients < MAX_PATIENTS) {
                getline(file, patients[numberOfPatients].name);
                getline(file, patients[numberOfPatients].admissionDate);
                getline(file, patients[numberOfPatients].dischargeDate);
                getline(file, patients[numberOfPatients].diagnosis);
                getline(file, patients[numberOfPatients].treatingDoctor);
                getline(file, ignore);
                numberOfPatients++;
            }
            file.close();
            cout << "Data successfully read from the file." << endl;
        }
        else 
        {
            cout << "Error: Unable to open the file for reading." << endl;
        }
    }
};

int main() 
{
    Hospital hospital;

    
    Patient patient1("John Doe", "10.09.2023", "18.09.2023", "Fever", "Dr. Smith");
    Patient patient2("Jane Smith", "11.09.2023", "25.09.2023", "Broken Arm", "Dr. Johnson");

    
    hospital.addPatient(patient1);
    hospital.addPatient(patient2);

    
    cout << "List of Patients:" << endl;
    hospital.displayPatients();

    
    hospital.writeToFile("patients.txt");

  
    hospital.readFromFile("patients.txt");

    return 0;
}
