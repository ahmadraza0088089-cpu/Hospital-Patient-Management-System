#include<iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;


class Person {
private:
    string name;
    string dob;
    string cnic;
    string contact;
    string address;

public:
    Person(string name = "", string dob = "", string cnic = "", string contact = "", string address = "" ) {
        this->name = name;
        this->dob = dob;
        this->cnic = cnic;
        this->contact = contact;
        this->address = address;
    }

    virtual ~Person() {}

    string getName() const { return name; }
    string getDOB() const { return dob; }
    string getCNIC() const { return cnic; }
    string getContact() const { return contact; }
    string getAddress() const { return address; }

    void setName(string name) { this->name = name; }
    void setDOB(string dob) { this->dob = dob; }
    void setCNIC(string cnic) { this->cnic = cnic; }
    void setContact(string contact) { this->contact = contact; }
    void setAddress(string address) { this->address = address; }

    int getAge() const {
        if (dob.empty()) return 0;
        int birthYear, birthMonth, birthDay;
        char dash;
        stringstream ss(dob);
        ss >> birthYear >> dash >> birthMonth >> dash >> birthDay;

        time_t now = time(0);
        tm* current = localtime(&now);
        int currentYear = current->tm_year + 1900;
        int currentMonth = current->tm_mon + 1;
        int currentDay = current->tm_mday;

        int age = currentYear - birthYear;
        if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay))
            age--;
        return age;
    }

    virtual void display_info() const {
        cout << "Name:     " << name << endl;
        cout << "DOB:      " << dob << endl;
        cout << "Age:      " << getAge() << " years" << endl;
        cout << "CNIC:     " << cnic << endl;
        cout << "Contact:  " << contact << endl;
        cout << "Address:  " << address << endl;
    }
};

class Patient : public Person {
private:
    string patient_id;
    string blood_group;
    vector<string> records;
    double total_bill;

public:
    Patient(string name = "", string dob = "", string cnic = "", string contact = "",
            string address = "", string patient_id = "", string blood_group = "")
        : Person(name, dob, cnic, contact, address) {
        this->patient_id = patient_id;
        this->blood_group = blood_group;
        this->total_bill = 0.0;
    }

    string getPatientId() const { return patient_id; }
    string getBloodGroup() const { return blood_group; }
    double getTotalBill() const { return total_bill; }

    void add_record(string record) { records.push_back(record); }

    void get_history() const {
        cout << "\n========== Medical History ==========" << endl;
        cout << "Patient: " << getName() << " (ID: " << patient_id << ")" << endl;
        cout << "Blood Group: " << blood_group << endl;
        cout << "Total Bill: Rs. " << total_bill << endl;
        if (records.empty()) {
            cout << "No medical records found." << endl;
        } else {
            cout << "Medical Records:" << endl;
            for (size_t i = 0; i < records.size(); i++)
                cout << i + 1 << ". " << records[i] << endl;
        }
        cout << "===================================\n" << endl;
    }

    void add_bill(double amount) { total_bill += amount; }

    void get_bill() const {
        cout << "\n========== Bill Details ==========" << endl;
        cout << "Patient ID: " << patient_id << endl;
        cout << "Patient Name: " << getName() << endl;
        cout << "Total Bill: Rs. " << total_bill << endl;
        cout << "================================\n" << endl;
    }

    void display_info() const override {
        cout << "\n========== PATIENT INFO ==========" << endl;
        Person::display_info();
        cout << "Patient ID:  " << patient_id << endl;
        cout << "Blood Group: " << blood_group << endl;
        cout << "Records:     " << records.size() << " records" << endl;
        cout << "Total Bill: Rs. " << total_bill << endl;
        cout << "================================\n" << endl;
    }
};


class Doctor : public Person {
private:
    string doctor_id;
    string speciality;
    map<string, bool> schedule;
    double fee;

public:
    Doctor(string name = "", string dob = "", string cnic = "", string contact = "",
           string address = "", string doctor_id = "", string speciality = "", double fee = 0.0)
        : Person(name, dob, cnic, contact, address) {
        this->doctor_id = doctor_id;
        this->speciality = speciality;
        this->fee = fee;
    }

    string getDoctorId() const { return doctor_id; }
    string getSpeciality() const { return speciality; }
    double getFee() const { return fee; }

    void setSpeciality(string speciality) { this->speciality = speciality; }
    void setFee(double fee) { this->fee = fee; }

    bool book_slot(string date, string time) {
        string slot = date + " " + time;
        if (schedule.find(slot) != schedule.end() && schedule[slot]) {
            schedule[slot] = false;
            return true;
        }
        return false;
    }

    bool is_avaliable(string slot) const {
        map<string, bool>::const_iterator it = schedule.find(slot);
        if (it != schedule.end()) return it->second;
        return false;
    }

    void add_available_slot(string slot) { schedule[slot] = true; }

    void get_appointment() const {
        cout << "\n========== Doctor Schedule ==========" << endl;
        cout << "Doctor: " << getName() << " (" << doctor_id << ")" << endl;
        cout << "Speciality: " << speciality << endl;
        cout << "Consultation Fee: Rs. " << fee << endl;
        cout << "----------------------------------------" << endl;
        cout << "Available Slots:" << endl;
        int count = 0;
        for (auto it = schedule.begin(); it != schedule.end(); it++) {
            if (it->second) { cout << "  " << it->first << endl; count++; }
        }
        if (count == 0) cout << "  No available slots!" << endl;
        cout << "=====================================\n" << endl;
    }

    void display_info() const override {
        cout << "\n========== DOCTOR INFO ==========" << endl;
        Person::display_info();
        cout << "Doctor ID:   " << doctor_id << endl;
        cout << "Speciality:  " << speciality << endl;
        cout << "Fee:         Rs. " << fee << endl;
        cout << "==================================\n" << endl;
    }
};


class Staff : public Person {
private:
    string staff_id;
    string department;
    string role;
    string shift;
    vector<string> attendance;

public:
    Staff(string name = "", string dob = "", string cnic = "", string contact = "",
          string address = "", string staff_id = "", string department = "", string role = "")
        : Person(name, dob, cnic, contact, address) {
        this->staff_id = staff_id;
        this->department = department;
        this->role = role;
        this->shift = "Morning";
    }

    string getStaffId() const { return staff_id; }
    string getDepartment() const { return department; }
    string getRole() const { return role; }

    void setDepartment(string department) { this->department = department; }
    void setRole(string role) { this->role = role; }
    void set_shift(string shift) { this->shift = shift; }
    string get_shift() const { return shift; }

    void log_attendence() {
        time_t now = time(0);
        char* dt = ctime(&now);
        string entry = string(dt);
        attendance.push_back(entry.substr(0, entry.length() - 1));
        cout << "Attendance logged for " << getName() << " at " << dt;
    }

    void get_attendance() const {
        cout << "\n========== Attendance ==========" << endl;
        cout << "Staff ID: " << staff_id << endl;
        cout << "Name: " << getName() << endl;
        cout << "Total Entries: " << attendance.size() << endl;
        if (attendance.empty()) {
            cout << "No attendance records." << endl;
        } else {
            for (size_t i = 0; i < attendance.size(); i++)
                cout << i + 1 << ". " << attendance[i] << endl;
        }
        cout << "================================\n" << endl;
    }

    void display_info() const override {
        cout << "\n========== STAFF INFO ==========" << endl;
        Person::display_info();
        cout << "Staff ID:    " << staff_id << endl;
        cout << "Department:  " << department << endl;
        cout << "Role:        " << role << endl;
        cout << "Shift:       " << shift << endl;
        cout << "================================\n" << endl;
    }
};


class Appointment {
private:
    string appt_id;
    Patient* patient;
    Doctor* doctor;
    string date;
    string time;
    string status;

public:
    Appointment(string appt_id = "", Patient* patient = nullptr, Doctor* doctor = nullptr,
                string date = "", string time = "") {
        this->appt_id = appt_id;
        this->patient = patient;
        this->doctor = doctor;
        this->date = date;
        this->time = time;
        this->status = "Pending";
    }

    string getApptId() const { return appt_id; }
    string getStatus() const { return status; }
    Patient* getPatient() const { return patient; }
    Doctor* getDoctor() const { return doctor; }
    string getDate() const { return date; }
    string getTime() const { return time; }

    void confirm() { status = "Confirmed"; cout << "Appointment " << appt_id << " CONFIRMED!" << endl; }
    void cancel()  { status = "Cancelled";  cout << "Appointment " << appt_id << " CANCELLED!"  << endl; }

    double calculate_fee() const { return doctor->getFee(); }

    void display() const {
        cout << "\n---------- Appointment Details ----------" << endl;
        cout << "Appointment ID: " << appt_id << endl;
        cout << "Patient: " << patient->getName() << " (ID: " << patient->getPatientId() << ")" << endl;
        cout << "Doctor:  " << doctor->getName()  << " (ID: " << doctor->getDoctorId()  << ")" << endl;
        cout << "Date/Time: " << date << " at " << time << endl;
        cout << "Status: " << status << endl;
        cout << "Fee: Rs. " << calculate_fee() << endl;
        cout << "------------------------------------------\n" << endl;
    }
};


class MedicalRecord {
private:
    string record_id, patient_id, doctor_id, diagnosis, prescription, date;

public:
    MedicalRecord(string record_id = "", string patient_id = "", string doctor_id = "",
                  string diagnosis = "", string prescription = "", string date = "") {
        this->record_id    = record_id;
        this->patient_id   = patient_id;
        this->doctor_id    = doctor_id;
        this->diagnosis    = diagnosis;
        this->prescription = prescription;
        this->date         = date;
    }

    string getRecordId()     const { return record_id; }
    string getPatientId()    const { return patient_id; }
    string getDoctorId()     const { return doctor_id; }
    string getDiagnosis()    const { return diagnosis; }
    string getPrescription() const { return prescription; }
    string getDate()         const { return date; }

    void display() const {
        cout << "\n--- Medical Record ---" << endl;
        cout << "Record ID:     " << record_id    << endl;
        cout << "Patient ID:    " << patient_id   << endl;
        cout << "Doctor ID:     " << doctor_id    << endl;
        cout << "Diagnosis:     " << diagnosis    << endl;
        cout << "Prescription:  " << prescription << endl;
        cout << "Date:          " << date         << endl;
    }

    void export_to_file(const string& filename) const {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << "Record ID: "     << record_id    << endl;
            file << "Patient ID: "    << patient_id   << endl;
            file << "Doctor ID: "     << doctor_id    << endl;
            file << "Diagnosis: "     << diagnosis    << endl;
            file << "Prescription: "  << prescription << endl;
            file << "Date: "          << date         << endl;
            file << "----------------------------" << endl;
            file.close();
            cout << "Record exported to " << filename << endl;
        } else {
            cout << "Error: Could not open file!" << endl;
        }
    }
};


class Procedure {
private:
    string proc_id, name;
    double base_cost, consumable_cost;

public:
    Procedure(string proc_id = "", string name = "", double base_cost = 0.0, double consumable_cost = 0.0) {
        this->proc_id          = proc_id;
        this->name             = name;
        this->base_cost        = base_cost;
        this->consumable_cost  = consumable_cost;
    }

    string getProcId()          const { return proc_id; }
    string getName()            const { return name; }
    double getBaseCost()        const { return base_cost; }
    double getConsumableCost()  const { return consumable_cost; }
    void   setConsumableCost(double cost) { consumable_cost = cost; }

    double calculate_fee() const { return base_cost + consumable_cost; }

    void display() const {
        cout << "Procedure: " << name << " (ID: " << proc_id << ")" << endl;
        cout << "Base Cost: Rs. " << base_cost << endl;
        cout << "Consumable Cost: Rs. " << consumable_cost << endl;
        cout << "Total Fee: Rs. " << calculate_fee() << endl;
    }
};


class BillItem {
public:
    string description;
    double cost;
    BillItem(string desc = "", double cost = 0.0) : description(desc), cost(cost) {}
};

class Bill {
private:
    string bill_id, patient_id;
    vector<BillItem> items;
    double total;
    bool paid;

public:
    Bill(string bill_id = "", string patient_id = "") {
        this->bill_id     = bill_id;
        this->patient_id  = patient_id;
        this->total       = 0.0;
        this->paid        = false;
    }

    string getBillId()    const { return bill_id; }
    string getPatientId() const { return patient_id; }
    double getTotal()     const { return total; }
    bool   isPaid()       const { return paid; }

    void add_item(string desc, double cost) {
        items.push_back(BillItem(desc, cost));
        total += cost;
    }

    void generate_invoice() const {
        cout << "\n========================================" << endl;
        cout << "           INVOICE" << endl;
        cout << "========================================" << endl;
        cout << "Bill ID:    " << bill_id    << endl;
        cout << "Patient ID: " << patient_id << endl;
        cout << "----------------------------------------" << endl;
        for (size_t i = 0; i < items.size(); i++)
            cout << i + 1 << ". " << items[i].description << ": Rs. " << items[i].cost << endl;
        cout << "----------------------------------------" << endl;
        cout << "TOTAL:  Rs. " << total << endl;
        cout << "Status: " << (paid ? "PAID" : "UNPAID") << endl;
        cout << "========================================\n" << endl;
    }

    void mark_paid() { paid = true; cout << "Bill " << bill_id << " marked as PAID!" << endl; }
};


int main() {

    cout << "############################################################" << endl;
    cout << "#          HOSPITAL MANAGEMENT SYSTEM               #" << endl;
    cout << "############################################################\n" << endl;

    
    cout << "=== 1. PATIENT ===" << endl;

    Patient p1("Ali Hassan", "1990-03-15", "35202-1234567-1",
               "0301-1234567", "House 12, Lahore", "P-001", "B+");

    p1.display_info();                              

    
    p1.setContact("0300-9999999");
    p1.setAddress("House 99, Islamabad");
    cout << "Updated Contact: " << p1.getContact() << endl;
    cout << "Updated Address: " << p1.getAddress() << endl;
    cout << "Calculated Age:  " << p1.getAge() << " years" << endl;

    
    p1.add_record("2024-01-10 | Flu | Dr. Kamran | Paracetamol 500mg");
    p1.add_record("2024-06-22 | Fracture (left arm) | Dr. Sara | Cast + Pain killers");
    p1.add_bill(2500.0);
    p1.add_bill(7500.0);
    p1.get_history();    
    p1.get_bill();       
    
    Patient p2("Fatima Noor", "1985-11-20", "35202-7654321-2",
               "0321-9876543", "Flat 5, Karachi", "P-002", "O-");
    p2.add_record("2025-02-14 | Diabetes checkup | Dr. Umar | Metformin");
    p2.add_bill(1200.0);
    p2.display_info();

    
    cout << "=== 2. DOCTOR ===" << endl;

    Doctor d1("Dr. Kamran Malik", "1975-07-04", "35202-1111111-3",
              "0333-1111111", "Block C, Lahore", "D-001", "Cardiology", 3000.0);

    d1.display_info();

    
    d1.setSpeciality("Cardiology & Internal Medicine");
    d1.setFee(3500.0);
    cout << "Updated Speciality: " << d1.getSpeciality() << endl;
    cout << "Updated Fee:        Rs. " << d1.getFee() << endl;

    
    d1.add_available_slot("2025-08-01 10:00 AM");
    d1.add_available_slot("2025-08-01 11:00 AM");
    d1.add_available_slot("2025-08-02 09:00 AM");
    d1.get_appointment();   // lists all available slots

    
    string slot1 = "2025-08-01 10:00 AM";
    cout << "Is slot '" << slot1 << "' available? "
         << (d1.is_avaliable(slot1) ? "YES" : "NO") << endl;
    bool booked = d1.book_slot("2025-08-01", "10:00 AM");
    cout << "Booking slot '" << slot1 << "': " << (booked ? "SUCCESS" : "FAILED") << endl;
    cout << "Is slot '" << slot1 << "' still available? "
         << (d1.is_avaliable(slot1) ? "YES" : "NO") << endl;

    d1.get_appointment();   

    
    Doctor d2("Dr. Sara Ahmed", "1980-05-12", "35202-2222222-4",
              "0345-2222222", "DHA, Karachi", "D-002", "Orthopedics", 2500.0);
    d2.add_available_slot("2025-08-03 02:00 PM");
    d2.display_info();

    
    cout << "=== 3. STAFF ===" << endl;

    Staff s1("Bilal Raza", "1995-09-09", "35202-3333333-5",
             "0311-3333333", "Gulberg, Lahore", "S-001", "Nursing", "Head Nurse");

    s1.display_info();

    
    s1.setDepartment("ICU");
    s1.setRole("Senior Nurse");
    s1.set_shift("Night");
    cout << "Updated Department: " << s1.getDepartment() << endl;
    cout << "Updated Role:       " << s1.getRole()       << endl;
    cout << "Current Shift:      " << s1.get_shift()     << endl;

    
    s1.log_attendence();
    s1.log_attendence();
    s1.get_attendance();

    Staff s2("Zara Khan", "1998-03-25", "35202-4444444-6",
             "0312-4444444", "F-10, Islamabad", "S-002", "Pharmacy", "Pharmacist");
    s2.set_shift("Evening");
    s2.log_attendence();
    s2.display_info();

    
    cout << "=== 4. APPOINTMENT ===" << endl;

    Appointment a1("A-001", &p1, &d1, "2025-08-01", "10:00 AM");
    a1.display();                   
    cout << "Appointment Fee: Rs. " << a1.calculate_fee() << endl;
    a1.confirm();                   
    a1.display();

   
    Appointment a2("A-002", &p2, &d2, "2025-08-03", "02:00 PM");
    a2.display();
    a2.cancel();                    
    a2.display();

    
    cout << "=== 5. MEDICAL RECORD ===" << endl;

    MedicalRecord mr1("MR-001", p1.getPatientId(), d1.getDoctorId(),
                      "Hypertension Stage 1",
                      "Amlodipine 5mg once daily, low-salt diet",
                      "2025-08-01");
    mr1.display();

    
    cout << "\nRecord ID:    " << mr1.getRecordId()     << endl;
    cout << "Diagnosis:    " << mr1.getDiagnosis()    << endl;
    cout << "Prescription: " << mr1.getPrescription() << endl;
    cout << "Date:         " << mr1.getDate()         << endl;

    
    mr1.export_to_file("medical_records.txt");

    MedicalRecord mr2("MR-002", p2.getPatientId(), d2.getDoctorId(),
                      "Hairline fracture – right wrist",
                      "Splint + Ibuprofen 400mg twice daily",
                      "2025-08-03");
    mr2.display();
    mr2.export_to_file("medical_records.txt");

    
    cout << "\n=== 6. PROCEDURE ===" << endl;

    Procedure proc1("PR-001", "X-Ray (Chest)", 800.0, 200.0);
    proc1.display();
    cout << "Total Fee: Rs. " << proc1.calculate_fee() << endl;

    
    proc1.setConsumableCost(350.0);
    cout << "\nAfter updating consumable cost:" << endl;
    proc1.display();

    Procedure proc2("PR-002", "Blood CBC Test", 500.0, 100.0);
    proc2.display();
    cout << "Proc ID: " << proc2.getProcId() << " | Base: Rs. " << proc2.getBaseCost() << endl;

    
    cout << "\n=== 7. BILL ===" << endl;

    Bill bill1("B-001", p1.getPatientId());

    
    bill1.add_item("Consultation – Dr. Kamran",      d1.getFee());
    bill1.add_item("X-Ray (Chest)",                  proc1.calculate_fee());
    bill1.add_item("Blood CBC Test",                 proc2.calculate_fee());
    bill1.add_item("Medicines",                      1200.0);

    bill1.generate_invoice();       

    cout << "Bill ID:    " << bill1.getBillId()    << endl;
    cout << "Patient ID: " << bill1.getPatientId() << endl;
    cout << "Total:      Rs. " << bill1.getTotal() << endl;
    cout << "Paid?       " << (bill1.isPaid() ? "Yes" : "No") << endl;

    bill1.mark_paid();              
    bill1.generate_invoice();     

    
    p1.add_bill(bill1.getTotal());
    p1.get_bill();

    
    Bill bill2("B-002", p2.getPatientId());
    bill2.add_item("Consultation – Dr. Sara",  d2.getFee());
    bill2.add_item("Splint Application",       1500.0);
    bill2.add_item("Medicines",                800.0);
    bill2.generate_invoice();

    
    
    cout << "\n=== 8. POLYMORPHISM DEMO ===" << endl;

    Person* people[4];
    people[0] = &p1;
    people[1] = &p2;
    people[2] = &d1;
    people[3] = &s1;

    for (int i = 0; i < 4; i++) {
        people[i]->display_info();   
    }

    cout << "\n############################################################" << endl;
    cout << "#                    COMPLETE                          #" << endl;
    cout << "############################################################" << endl;

    return 0;
}
    