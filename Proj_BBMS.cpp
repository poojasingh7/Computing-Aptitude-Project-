#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <map>

using namespace std;

// Utility function to get current date and time
string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "/"
       << setw(2) << 1 + ltm->tm_mon << "/"
       << 1900 + ltm->tm_year << " "
       << setw(2) << ltm->tm_hour << ":"
       << setw(2) << ltm->tm_min << ":"
       << setw(2) << ltm->tm_sec;
    return ss.str();
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "/"
       << setw(2) << 1 + ltm->tm_mon << "/"
       << 1900 + ltm->tm_year;
    return ss.str();
}

// Base Person class
class Person {
protected:
    string id;
    string name;
    int age;
    string bloodGroup;
    string contact;
    string address;
    string email;
    string gender;
    string registrationDate;
    string lastModified;

public:
    Person() : age(0) {}
    
    Person(string i, string n, int a, string bg, string c, string addr, 
           string em, string gen)
        : id(i), name(n), age(a), bloodGroup(bg), contact(c), address(addr),
          email(em), gender(gen) {
        registrationDate = getCurrentDateTime();
        lastModified = registrationDate;
    }

    string getId() const { return id; }
    string getName() const { return name; }
    string getBloodGroup() const { return bloodGroup; }
    string getContact() const { return contact; }
    int getAge() const { return age; }
    string getEmail() const { return email; }
    string getGender() const { return gender; }
    string getRegistrationDate() const { return registrationDate; }
    string getLastModified() const { return lastModified; }
    string getAddress() const { return address; }
    
    void setName(string n) { name = n; lastModified = getCurrentDateTime(); }
    void setContact(string c) { contact = c; lastModified = getCurrentDateTime(); }
    void setAddress(string addr) { address = addr; lastModified = getCurrentDateTime(); }
    void setEmail(string em) { email = em; lastModified = getCurrentDateTime(); }
    
    virtual void displayDetailed() const {
        cout << "\n┌─────────────────────────────────────────┐\n";
        cout << "│ ID               : " << left << setw(19) << id << "│\n";
        cout << "│ Name             : " << left << setw(19) << name << "│\n";
        cout << "│ Age              : " << left << setw(19) << age << "│\n";
        cout << "│ Blood Group      : " << left << setw(19) << bloodGroup << "│\n";
        cout << "│ Gender           : " << left << setw(19) << gender << "│\n";
        cout << "│ Contact          : " << left << setw(19) << contact << "│\n";
        cout << "│ Email            : " << left << setw(19) << email << "│\n";
        cout << "│ Address          : " << left << setw(19) << address << "│\n";
        cout << "│ Registered On    : " << left << setw(19) << registrationDate << "│\n";
        cout << "│ Last Modified    : " << left << setw(19) << lastModified << "│\n";
    }
    
    virtual void display() const {
        cout << left << setw(12) << id << setw(25) << name 
             << setw(5) << age << setw(8) << bloodGroup 
             << setw(15) << contact << endl;
    }
    
    virtual string serialize() const {
        return id + "," + name + "," + to_string(age) + "," + 
               bloodGroup + "," + contact + "," + address + "," + 
               email + "," + gender + "," + registrationDate + "," + lastModified;
    }
};

// Donor class
class Donor : public Person {
private:
    string lastDonationDate;
    int totalDonations;
    string medicalStatus;
    double weight;
    string diseases;

public:
    Donor() : totalDonations(0), medicalStatus("Healthy"), weight(0.0), 
              diseases("None") {}
    
    Donor(string i, string n, int a, string bg, string c, string addr, 
          string em, string gen, double w, string dis,
          string lastDate = "N/A", int donations = 0, string status = "Healthy")
        : Person(i, n, a, bg, c, addr, em, gen), lastDonationDate(lastDate), 
          totalDonations(donations), medicalStatus(status), weight(w), 
          diseases(dis) {}

    string getLastDonationDate() const { return lastDonationDate; }
    void setLastDonationDate(string date) { 
        lastDonationDate = date; 
        lastModified = getCurrentDateTime();
    }
    
    int getTotalDonations() const { return totalDonations; }
    void incrementDonations() { 
        totalDonations++; 
        lastModified = getCurrentDateTime();
    }
    
    string getMedicalStatus() const { return medicalStatus; }
    void setMedicalStatus(string status) { 
        medicalStatus = status; 
        lastModified = getCurrentDateTime();
    }
    
    double getWeight() const { return weight; }
    string getDiseases() const { return diseases; }
    
    void displayDetailed() const override {
        cout << "\n╔══════════════════════════════════════════════════════╗\n";
        cout << "║              DONOR DETAILED INFORMATION              ║\n";
        cout << "╚══════════════════════════════════════════════════════╝\n";
        Person::displayDetailed();
        cout << "│ Weight           : " << left << setw(19) << weight << "│\n";
        cout << "│ Diseases         : " << left << setw(19) << diseases << "│\n";
        cout << "│ Last Donation    : " << left << setw(19) << lastDonationDate << "│\n";
        cout << "│ Total Donations  : " << left << setw(19) << totalDonations << "│\n";
        cout << "│ Medical Status   : " << left << setw(19) << medicalStatus << "│\n";
        cout << "└─────────────────────────────────────────┘\n";
    }
    
    void display() const override {
        cout << left << setw(12) << id << setw(25) << name 
             << setw(5) << age << setw(8) << bloodGroup 
             << setw(15) << contact << setw(15) << lastDonationDate
             << setw(8) << totalDonations << setw(12) << medicalStatus << endl;
    }
    
    string serialize() const override {
        return Person::serialize() + "," + to_string(weight) + "," + 
               diseases + "," + lastDonationDate + "," + 
               to_string(totalDonations) + "," + medicalStatus;
    }
    
    static Donor deserialize(const string& line) {
        stringstream ss(line);
        string id, name, ageStr, bg, contact, addr, email, gender, regDate, 
               modDate, weightStr, diseases, lastDate, donStr, status;
        
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, bg, ',');
        getline(ss, contact, ',');
        getline(ss, addr, ',');
        getline(ss, email, ',');
        getline(ss, gender, ',');
        getline(ss, regDate, ',');
        getline(ss, modDate, ',');
        getline(ss, weightStr, ',');
        getline(ss, diseases, ',');
        getline(ss, lastDate, ',');
        getline(ss, donStr, ',');
        getline(ss, status, ',');
        
        Donor d(id, name, stoi(ageStr), bg, contact, addr, email, gender,
                stod(weightStr), diseases, lastDate, stoi(donStr), status);
        return d;
    }
};

// Recipient/Accepter class
class Accepter : public Person {
private:
    string requestDate;
    int unitsRequired;
    int unitsReceived;
    string status;
    string hospitalName;
    string doctorName;
    string urgencyLevel;
    string reason;

public:
    Accepter() : unitsRequired(0), unitsReceived(0), status("Pending"), 
                 urgencyLevel("Medium") {}
    
    Accepter(string i, string n, int a, string bg, string c, string addr,
              string em, string gen, int units, string hospital, string doctor,
              string urgency, string rsn, string reqDate = "", string st = "Pending")
        : Person(i, n, a, bg, c, addr, em, gen), unitsRequired(units), 
          unitsReceived(0), hospitalName(hospital), doctorName(doctor),
          urgencyLevel(urgency), reason(rsn), status(st) {
        requestDate = reqDate.empty() ? getCurrentDateTime() : reqDate;
    }

    int getUnitsRequired() const { return unitsRequired; }
    int getUnitsReceived() const { return unitsReceived; }
    string getStatus() const { return status; }
    string getUrgencyLevel() const { return urgencyLevel; }
    
    void setStatus(string st) { 
        status = st; 
        lastModified = getCurrentDateTime();
    }
    
    void addUnitsReceived(int units) {
        unitsReceived += units;
        lastModified = getCurrentDateTime();
        if (unitsReceived >= unitsRequired) {
            status = "Fulfilled";
        } else if (unitsReceived > 0) {
            status = "Partially Fulfilled";
        }
    }
    
    string getRequestDate() const { return requestDate; }
    string getHospitalName() const { return hospitalName; }
    string getDoctorName() const { return doctorName; }
    string getReason() const { return reason; }
    
    void displayDetailed() const override {
        cout << "\n╔══════════════════════════════════════════════════════╗\n";
        cout << "║            ACCEPTER DETAILED INFORMATION             ║\n";
        cout << "╚══════════════════════════════════════════════════════╝\n";
        Person::displayDetailed();
        cout << "│ Hospital         : " << left << setw(19) << hospitalName << "│\n";
        cout << "│ Doctor           : " << left << setw(19) << doctorName << "│\n";
        cout << "│ Request Date     : " << left << setw(19) << requestDate << "│\n";
        cout << "│ Units Required   : " << left << setw(19) << unitsRequired << "│\n";
        cout << "│ Units Received   : " << left << setw(19) << unitsReceived << "│\n";
        cout << "│ Urgency Level    : " << left << setw(19) << urgencyLevel << "│\n";
        cout << "│ Reason           : " << left << setw(19) << reason << "│\n";
        cout << "│ Status           : " << left << setw(19) << status << "│\n";
        cout << "└─────────────────────────────────────────┘\n";
    }
    
    void display() const override {
        cout << left << setw(12) << id << setw(25) << name 
             << setw(5) << age << setw(8) << bloodGroup 
             << setw(8) << unitsRequired << setw(8) << unitsReceived
             << setw(12) << urgencyLevel << setw(12) << status << endl;
    }
    
    string serialize() const override {
        return Person::serialize() + "," + to_string(unitsRequired) + "," + 
               to_string(unitsReceived) + "," + hospitalName + "," + 
               doctorName + "," + urgencyLevel + "," + reason + "," + 
               requestDate + "," + status;
    }
    
    static Accepter deserialize(const string& line) {
        stringstream ss(line);
        string id, name, ageStr, bg, contact, addr, email, gender, regDate, modDate,
               unitsReqStr, unitsRecStr, hospital, doctor, urgency, reason, reqDate, status;
        
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, bg, ',');
        getline(ss, contact, ',');
        getline(ss, addr, ',');
        getline(ss, email, ',');
        getline(ss, gender, ',');
        getline(ss, regDate, ',');
        getline(ss, modDate, ',');
        getline(ss, unitsReqStr, ',');
        getline(ss, unitsRecStr, ',');
        getline(ss, hospital, ',');
        getline(ss, doctor, ',');
        getline(ss, urgency, ',');
        getline(ss, reason, ',');
        getline(ss, reqDate, ',');
        getline(ss, status, ',');
        
        Accepter a(id, name, stoi(ageStr), bg, contact, addr, email, gender,
                   stoi(unitsReqStr), hospital, doctor, urgency, reason, reqDate, status);
        a.unitsReceived = stoi(unitsRecStr);
        return a;
    }
};

// Blood Inventory class
class BloodInventory {
private:
    map<string, int> inventory;
    map<string, string> lastUpdated;

public:
    BloodInventory() {
        inventory["A+"] = 0;
        inventory["A-"] = 0;
        inventory["B+"] = 0;
        inventory["B-"] = 0;
        inventory["AB+"] = 0;
        inventory["AB-"] = 0;
        inventory["O+"] = 0;
        inventory["O-"] = 0;
        
        for (auto& pair : inventory) {
            lastUpdated[pair.first] = getCurrentDate();
        }
    }

    void addBlood(string bloodGroup, int units) {
        if (inventory.find(bloodGroup) != inventory.end()) {
            inventory[bloodGroup] += units;
            lastUpdated[bloodGroup] = getCurrentDateTime();
        }
    }

    bool removeBlood(string bloodGroup, int units) {
        if (inventory.find(bloodGroup) != inventory.end() && 
            inventory[bloodGroup] >= units) {
            inventory[bloodGroup] -= units;
            lastUpdated[bloodGroup] = getCurrentDateTime();
            return true;
        }
        return false;
    }

    int getStock(string bloodGroup) const {
        auto it = inventory.find(bloodGroup);
        return (it != inventory.end()) ? it->second : 0;
    }

    void displayInventory() const {
        cout << "\n╔══════════════════════════════════════════════════╗\n";
        cout << "║            BLOOD INVENTORY STATUS                ║\n";
        cout << "╚══════════════════════════════════════════════════╝\n";
        cout << left << setw(15) << "Blood Group" 
             << setw(18) << "Units Available" 
             << setw(25) << "Last Updated" << endl;
        cout << string(58, '-') << endl;
        
        for (const auto& pair : inventory) {
            cout << left << setw(15) << pair.first 
                 << setw(18) << pair.second 
                 << setw(25) << lastUpdated.at(pair.first) << endl;
        }
        cout << string(58, '=') << endl;
    }

    string serialize() const {
        stringstream ss;
        for (const auto& pair : inventory) {
            ss << pair.first << ":" << pair.second << ":" 
               << lastUpdated.at(pair.first) << ";";
        }
        return ss.str();
    }

    void deserialize(const string& data) {
        if (data.empty()) return;
        
        stringstream ss(data);
        string token;
        
        while (getline(ss, token, ';')) {
            if (token.empty()) continue;
            
            size_t pos1 = token.find(':');
            size_t pos2 = token.rfind(':');
            
            if (pos1 != string::npos && pos2 != string::npos) {
                string bg = token.substr(0, pos1);
                int units = stoi(token.substr(pos1 + 1, pos2 - pos1 - 1));
                string date = token.substr(pos2 + 1);
                
                inventory[bg] = units;
                lastUpdated[bg] = date;
            }
        }
    }
};

// Transaction class for logging
class Transaction {
private:
    string transId;
    string type;
    string bloodGroup;
    int units;
    string dateTime;
    string personId;
    string personName;

public:
    Transaction(string tid, string t, string bg, int u, string pid, string pname)
        : transId(tid), type(t), bloodGroup(bg), units(u), personId(pid), personName(pname) {
        dateTime = getCurrentDateTime();
    }

    string getDateTime() const { return dateTime; }
    void setDateTime(string dt) { dateTime = dt; }

    string serialize() const {
        return transId + "," + type + "," + bloodGroup + "," + 
               to_string(units) + "," + dateTime + "," + personId + "," + personName;
    }

    static Transaction deserialize(const string& line) {
        stringstream ss(line);
        string tid, type, bg, unitsStr, dateTime, pid, pname;
        
        getline(ss, tid, ',');
        getline(ss, type, ',');
        getline(ss, bg, ',');
        getline(ss, unitsStr, ',');
        getline(ss, dateTime, ',');
        getline(ss, pid, ',');
        getline(ss, pname, ',');
        
        Transaction t(tid, type, bg, stoi(unitsStr), pid, pname);
        t.setDateTime(dateTime);
        return t;
    }

    void display() const {
        cout << left << setw(12) << transId << setw(15) << type 
             << setw(8) << bloodGroup << setw(8) << units 
             << setw(22) << dateTime << setw(12) << personId 
             << setw(20) << personName << endl;
    }
};

// Main Blood Bank Management System
class BloodBankSystem {
private:
    vector<Donor> donors;
    vector<Accepter> accepters;
    vector<Transaction> transactions;
    BloodInventory inventory;
    int donorCount, accepterCount, transCount;

    string donorFile = "donors_records.txt";
    string accepterFile = "accepters_records.txt";
    string inventoryFile = "inventory.txt";
    string transactionFile = "transactions.txt";
    string updateLogFile = "update_log.txt";

    void logUpdate(const string& message) {
        ofstream logFile(updateLogFile, ios::app);
        if (logFile.is_open()) {
            logFile << "[" << getCurrentDateTime() << "] " << message << endl;
            logFile.close();
        }
    }

    void saveDonorsToFile() {
        ofstream dFile(donorFile);
        if (!dFile.is_open()) return;

        // Header
        dFile << "================================================================================\n";
        dFile << "                        BLOOD BANK MANAGEMENT SYSTEM                            \n";
        dFile << "                           DONOR RECORDS DATABASE                               \n";
        dFile << "================================================================================\n\n";
        dFile << "File Generated    : " << getCurrentDateTime() << "\n";
        dFile << "Total Donors      : " << donors.size() << "\n";
        dFile << "================================================================================\n\n";

        // Table format for donors
        for (size_t i = 0; i < donors.size(); i++) {
            const Donor& d = donors[i];
            
            dFile << "--------------------------------------------------------------------------------\n";
            dFile << "DONOR #" << (i + 1) << "\n";
            dFile << "--------------------------------------------------------------------------------\n";
            dFile << left;
            dFile << setw(25) << "Property" << "| " << "Value" << "\n";
            dFile << "--------------------------------------------------------------------------------\n";
            dFile << setw(25) << "Donor ID" << "| " << d.getId() << "\n";
            dFile << setw(25) << "Full Name" << "| " << d.getName() << "\n";
            dFile << setw(25) << "Age" << "| " << d.getAge() << " years\n";
            dFile << setw(25) << "Gender" << "| " << d.getGender() << "\n";
            dFile << setw(25) << "Blood Group" << "| " << d.getBloodGroup() << "\n";
            dFile << setw(25) << "Weight" << "| " << d.getWeight() << " kg\n";
            dFile << setw(25) << "Contact Number" << "| " << d.getContact() << "\n";
            dFile << setw(25) << "Email Address" << "| " << d.getEmail() << "\n";
            dFile << setw(25) << "Address" << "| " << d.getAddress() << "\n";
            dFile << setw(25) << "Medical Conditions" << "| " << d.getDiseases() << "\n";
            dFile << setw(25) << "Medical Status" << "| " << d.getMedicalStatus() << "\n";
            dFile << setw(25) << "Last Donation Date" << "| " << d.getLastDonationDate() << "\n";
            dFile << setw(25) << "Total Donations" << "| " << d.getTotalDonations() << " times\n";
            dFile << setw(25) << "Registration Date" << "| " << d.getRegistrationDate() << "\n";
            dFile << setw(25) << "Last Modified" << "| " << d.getLastModified() << "\n";
            dFile << "--------------------------------------------------------------------------------\n\n";
        }

        dFile << "================================================================================\n";
        dFile << "                            END OF DONOR RECORDS                                \n";
        dFile << "================================================================================\n";
        dFile.close();
    }

    void saveAcceptersToFile() {
        ofstream aFile(accepterFile);
        if (!aFile.is_open()) return;

        // Header
        aFile << "================================================================================\n";
        aFile << "                        BLOOD BANK MANAGEMENT SYSTEM                            \n";
        aFile << "                         ACCEPTER RECORDS DATABASE                              \n";
        aFile << "================================================================================\n\n";
        aFile << "File Generated    : " << getCurrentDateTime() << "\n";
        aFile << "Total Accepters   : " << accepters.size() << "\n";
        aFile << "================================================================================\n\n";

        // Table format for accepters
        for (size_t i = 0; i < accepters.size(); i++) {
            const Accepter& a = accepters[i];
            
            aFile << "--------------------------------------------------------------------------------\n";
            aFile << "ACCEPTER #" << (i + 1) << "\n";
            aFile << "--------------------------------------------------------------------------------\n";
            aFile << left;
            aFile << setw(25) << "Property" << "| " << "Value" << "\n";
            aFile << "--------------------------------------------------------------------------------\n";
            aFile << setw(25) << "Accepter ID" << "| " << a.getId() << "\n";
            aFile << setw(25) << "Full Name" << "| " << a.getName() << "\n";
            aFile << setw(25) << "Age" << "| " << a.getAge() << " years\n";
            aFile << setw(25) << "Gender" << "| " << a.getGender() << "\n";
            aFile << setw(25) << "Blood Group Required" << "| " << a.getBloodGroup() << "\n";
            aFile << setw(25) << "Contact Number" << "| " << a.getContact() << "\n";
            aFile << setw(25) << "Email Address" << "| " << a.getEmail() << "\n";
            aFile << setw(25) << "Address" << "| " << a.getAddress() << "\n";
            aFile << setw(25) << "Hospital Name" << "| " << a.getHospitalName() << "\n";
            aFile << setw(25) << "Doctor Name" << "| " << a.getDoctorName() << "\n";
            aFile << setw(25) << "Units Required" << "| " << a.getUnitsRequired() << " units\n";
            aFile << setw(25) << "Units Received" << "| " << a.getUnitsReceived() << " units\n";
            aFile << setw(25) << "Urgency Level" << "| " << a.getUrgencyLevel() << "\n";
            aFile << setw(25) << "Reason" << "| " << a.getReason() << "\n";
            aFile << setw(25) << "Request Status" << "| " << a.getStatus() << "\n";
            aFile << setw(25) << "Request Date" << "| " << a.getRequestDate() << "\n";
            aFile << setw(25) << "Registration Date" << "| " << a.getRegistrationDate() << "\n";
            aFile << setw(25) << "Last Modified" << "| " << a.getLastModified() << "\n";
            aFile << "--------------------------------------------------------------------------------\n\n";
        }

        aFile << "================================================================================\n";
        aFile << "                          END OF ACCEPTER RECORDS                               \n";
        aFile << "================================================================================\n";
        aFile.close();
    }

public:
    BloodBankSystem() : donorCount(0), accepterCount(0), transCount(0) {
        loadData();
    }

    ~BloodBankSystem() {
        saveData();
    }

    // File operations
    void saveData() {
        saveDonorsToFile();
        saveAcceptersToFile();
        logUpdate("Donor records saved. Total: " + to_string(donors.size()));
        logUpdate("Accepter records saved. Total: " + to_string(accepters.size()));

        // Save inventory
        ofstream iFile(inventoryFile);
        iFile << "================================================================================\n";
        iFile << "                        BLOOD INVENTORY DATABASE                                \n";
        iFile << "================================================================================\n\n";
        iFile << "Last Updated: " << getCurrentDateTime() << "\n\n";
        iFile << left << setw(20) << "Blood Group" << "| " << setw(15) << "Units" << "| " << "Last Updated\n";
        iFile << "--------------------------------------------------------------------------------\n";
        
        map<string, int> inv;
        inv["A+"] = inventory.getStock("A+");
        inv["A-"] = inventory.getStock("A-");
        inv["B+"] = inventory.getStock("B+");
        inv["B-"] = inventory.getStock("B-");
        inv["AB+"] = inventory.getStock("AB+");
        inv["AB-"] = inventory.getStock("AB-");
        inv["O+"] = inventory.getStock("O+");
        inv["O-"] = inventory.getStock("O-");
        
        for (const auto& pair : inv) {
            iFile << setw(20) << pair.first << "| " << setw(15) << pair.second << "| " << getCurrentDateTime() << "\n";
        }
        
        iFile << "================================================================================\n";
        iFile << inventory.serialize() << endl;
        iFile.close();

        // Save transactions
        ofstream tFile(transactionFile);
        tFile << "================================================================================\n";
        tFile << "                        TRANSACTION HISTORY                                     \n";
        tFile << "================================================================================\n\n";
        tFile << "Total Transactions: " << transactions.size() << "\n";
        tFile << "Generated: " << getCurrentDateTime() << "\n\n";
        tFile << left << setw(12) << "Trans ID" << "| " << setw(12) << "Type" << "| " 
              << setw(8) << "Blood" << "| " << setw(6) << "Units" << "| " 
              << setw(20) << "Date & Time" << "| " << setw(10) << "Person ID" << "| " << "Name\n";
        tFile << "--------------------------------------------------------------------------------\n";
        
        for (const auto& trans : transactions) {
            tFile << trans.serialize() << endl;
        }
        tFile << "================================================================================\n";
        tFile.close();
    }

    void loadData() {
        // Load donors - skip formatted headers, read serialized data
        ifstream dFile(donorFile);
        if (dFile.is_open()) {
            string line;
            bool dataSection = false;
            
            while (getline(dFile, line)) {
                // Look for lines with comma-separated values (serialized data)
                if (line.find(',') != string::npos && !line.empty() && 
                    line[0] != '=' && line[0] != '-' && line[0] != ' ' &&
                    line.find("Property") == string::npos) {
                    try {
                        donors.push_back(Donor::deserialize(line));
                        donorCount++;
                    } catch (...) {
                        // Skip malformed lines
                    }
                }
            }
            dFile.close();
        }

        // Load accepters
        ifstream aFile(accepterFile);
        if (aFile.is_open()) {
            string line;
            
            while (getline(aFile, line)) {
                if (line.find(',') != string::npos && !line.empty() && 
                    line[0] != '=' && line[0] != '-' && line[0] != ' ' &&
                    line.find("Property") == string::npos) {
                    try {
                        accepters.push_back(Accepter::deserialize(line));
                        accepterCount++;
                    } catch (...) {
                        // Skip malformed lines
                    }
                }
            }
            aFile.close();
        }

        // Load inventory
        ifstream iFile(inventoryFile);
        if (iFile.is_open()) {
            string line;
            while (getline(iFile, line)) {
                if (line.find(':') != string::npos && line.find(';') != string::npos) {
                    inventory.deserialize(line);
                    break;
                }
            }
            iFile.close();
        }

        // Load transactions
        ifstream tFile(transactionFile);
        if (tFile.is_open()) {
            string line;
            while (getline(tFile, line)) {
                if (line.find(',') != string::npos && !line.empty() && 
                    line[0] != '=' && line[0] != '-' && line[0] != ' ' &&
                    line.find("Trans ID") == string::npos) {
                    try {
                        transactions.push_back(Transaction::deserialize(line));
                        transCount++;
                    } catch (...) {
                        // Skip malformed lines
                    }
                }
            }
            tFile.close();
        }
    }

    // Donor management
    void registerDonor() {
        string name, bloodGroup, contact, address, email, gender, diseases;
        int age;
        double weight;

        cout << "\n╔══════════════════════════════════════════╗\n";
        cout << "║       REGISTER NEW DONOR                 ║\n";
        cout << "╚══════════════════════════════════════════╝\n";
        cin.ignore();
        cout << "Enter Full Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Gender (M/F/Other): ";
        cin >> gender;
        cout << "Enter Blood Group (A+/A-/B+/B-/AB+/AB-/O+/O-): ";
        cin >> bloodGroup;
        cout << "Enter Weight (kg): ";
        cin >> weight;
        cin.ignore();
        cout << "Enter Contact Number: ";
        getline(cin, contact);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Any Medical Conditions/Diseases (or 'None'): ";
        getline(cin, diseases);

        string id = "D" + to_string(++donorCount);
        Donor newDonor(id, name, age, bloodGroup, contact, address, email, 
                       gender, weight, diseases);
        donors.push_back(newDonor);

        logUpdate("New donor registered: " + id + " - " + name + " (" + bloodGroup + ")");
        cout << "\n✓ Donor registered successfully!\n";
        cout << "  Donor ID: " << id << endl;
        cout << "  Registration Date: " << getCurrentDateTime() << endl;
    }

    void updateDonor() {
        string donorId;
        cout << "\nEnter Donor ID to update: ";
        cin >> donorId;

        auto it = find_if(donors.begin(), donors.end(),
            [&donorId](const Donor& d) { return d.getId() == donorId; });

        if (it != donors.end()) {
            cout << "\n=== CURRENT DONOR DETAILS ===\n";
            it->displayDetailed();

            int choice;
            cout << "\nWhat would you like to update?\n";
            cout << "1. Contact Number\n";
            cout << "2. Email\n";
            cout << "3. Address\n";
            cout << "4. Medical Status\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            string oldValue, newValue;
            switch (choice) {
                case 1:
                    cout << "Enter new contact: ";
                    getline(cin, newValue);
                    oldValue = it->getContact();
                    it->setContact(newValue);
                    logUpdate("Donor " + donorId + " contact updated from " + 
                             oldValue + " to " + newValue);
                    break;
                case 2:
                    cout << "Enter new email: ";
                    getline(cin, newValue);
                    oldValue = it->getEmail();
                    it->setEmail(newValue);
                    logUpdate("Donor " + donorId + " email updated from " + 
                             oldValue + " to " + newValue);
                    break;
                case 3:
                    cout << "Enter new address: ";
                    getline(cin, newValue);
                    it->setAddress(newValue);
                    logUpdate("Donor " + donorId + " address updated");
                    break;
                case 4:
                    cout << "Enter new medical status: ";
                    getline(cin, newValue);
                    oldValue = it->getMedicalStatus();
                    it->setMedicalStatus(newValue);
                    logUpdate("Donor " + donorId + " medical status updated from " + 
                             oldValue + " to " + newValue);
                    break;
                default:
                    cout << "Invalid choice!\n";
                    return;
            }
            cout << "\n✓ Donor information updated successfully!\n";
        } else {
            cout << "\n✗ Donor not found!\n";
        }
    }

    void processDonation() {
        string donorId;
        int units;

        cout << "\n╔══════════════════════════════════════════╗\n";
        cout << "║       PROCESS BLOOD DONATION             ║\n";
        cout << "╚══════════════════════════════════════════╝\n";
        cout << "Enter Donor ID: ";
        cin >> donorId;

        auto it = find_if(donors.begin(), donors.end(),
            [&donorId](const Donor& d) { return d.getId() == donorId; });

        if (it != donors.end()) {
            it->displayDetailed();
            
            cout << "\nEnter units to donate (1-5): ";
            cin >> units;

            if (units > 0 && units <= 5) {
                inventory.addBlood(it->getBloodGroup(), units);
                it->setLastDonationDate(getCurrentDate());
                it->incrementDonations();

                string transId = "T" + to_string(++transCount);
                transactions.push_back(Transaction(transId, "Donation", 
                    it->getBloodGroup(), units, donorId, it->getName()));

                logUpdate("Donation processed: " + to_string(units) + " units of " + 
                         it->getBloodGroup() + " from " + it->getName() + " (" + donorId + ")");

                cout << "\n✓ Donation processed successfully!\n";
                cout << "  Transaction ID: " << transId << endl;
                cout << "  Units donated: " << units << " unit(s) of " 
                     << it->getBloodGroup() << endl;
                cout << "  Date & Time: " << getCurrentDateTime() << endl;
            } else {
                cout << "\n✗ Invalid number of units (1-5 allowed).\n";
            }
        } else {
            cout << "\n✗ Donor not found!\n";
        }
    }

    void viewDonorDetails() {
        string donorId;
        cout << "\nEnter Donor ID: ";
        cin >> donorId;

        auto it = find_if(donors.begin(), donors.end(),
            [&donorId](const Donor& d) { return d.getId() == donorId; });

        if (it != donors.end()) {
            it->displayDetailed();
        } else {
            cout << "\n✗ Donor not found!\n";
        }
    }

    void displayDonors() {
        if (donors.empty()) {
            cout << "\nNo donors registered.\n";
            return;
        }

        cout << "\n╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                    REGISTERED DONORS                                         ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n";
        cout << left << setw(12) << "ID" << setw(25) << "Name" 
             << setw(5) << "Age" << setw(8) << "Blood" 
             << setw(15) << "Contact" << setw(15) << "Last Donation"
             << setw(8) << "Total" << setw(12) << "Status" << endl;
        cout << string(110, '-') << endl;

        for (const auto& donor : donors) {
            donor.display();
        }
        cout << string(110, '=') << endl;
    }

    // Accepter management
    void registerAccepter() {
        string name, bloodGroup, contact, address, email, gender;
        string hospital, doctor, urgency, reason;
        int age, units;

        cout << "\n╔══════════════════════════════════════════╗\n";
        cout << "║       REGISTER NEW ACCEPTER              ║\n";
        cout << "╚══════════════════════════════════════════╝\n";
        cin.ignore();
        cout << "Enter Full Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Gender (M/F/Other): ";
        cin >> gender;
        cout << "Enter Blood Group Required: ";
        cin >> bloodGroup;
        cout << "Enter Units Required: ";
        cin >> units;
        cin.ignore();
        cout << "Enter Contact Number: ";
        getline(cin, contact);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter Hospital Name: ";
        getline(cin, hospital);
        cout << "Enter Doctor Name: ";
        getline(cin, doctor);
        cout << "Enter Urgency Level (Low/Medium/High/Critical): ";
        getline(cin, urgency);
        cout << "Enter Reason for Blood Requirement: ";
        getline(cin, reason);

        string id = "A" + to_string(++accepterCount);
        Accepter newAccepter(id, name, age, bloodGroup, contact, address, email,
                            gender, units, hospital, doctor, urgency, reason);
        accepters.push_back(newAccepter);

        logUpdate("New accepter registered: " + id + " - " + name + 
                 " (" + bloodGroup + ", " + to_string(units) + " units, " + urgency + ")");
        cout << "\n✓ Accepter registered successfully!\n";
        cout << "  Accepter ID: " << id << endl;
        cout << "  Request Date: " << getCurrentDateTime() << endl;
    }

    void updateAccepter() {
        string accepterId;
        cout << "\nEnter Accepter ID to update: ";
        cin >> accepterId;

        auto it = find_if(accepters.begin(), accepters.end(),
            [&accepterId](const Accepter& a) { return a.getId() == accepterId; });

        if (it != accepters.end()) {
            cout << "\n=== CURRENT ACCEPTER DETAILS ===\n";
            it->displayDetailed();

            int choice;
            cout << "\nWhat would you like to update?\n";
            cout << "1. Contact Number\n";
            cout << "2. Email\n";
            cout << "3. Address\n";
            cout << "4. Request Status\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            string oldValue, newValue;
            switch (choice) {
                case 1:
                    cout << "Enter new contact: ";
                    getline(cin, newValue);
                    oldValue = it->getContact();
                    it->setContact(newValue);
                    logUpdate("Accepter " + accepterId + " contact updated from " + 
                             oldValue + " to " + newValue);
                    break;
                case 2:
                    cout << "Enter new email: ";
                    getline(cin, newValue);
                    oldValue = it->getEmail();
                    it->setEmail(newValue);
                    logUpdate("Accepter " + accepterId + " email updated from " + 
                             oldValue + " to " + newValue);
                    break;
                case 3:
                    cout << "Enter new address: ";
                    getline(cin, newValue);
                    it->setAddress(newValue);
                    logUpdate("Accepter " + accepterId + " address updated");
                    break;
                case 4:
                    cout << "Enter new status (Pending/Cancelled): ";
                    getline(cin, newValue);
                    oldValue = it->getStatus();
                    it->setStatus(newValue);
                    logUpdate("Accepter " + accepterId + " status updated from " + 
                             oldValue + " to " + newValue);
                    break;
                default:
                    cout << "Invalid choice!\n";
                    return;
            }
            cout << "\n✓ Accepter information updated successfully!\n";
        } else {
            cout << "\n✗ Accepter not found!\n";
        }
    }

    void fulfillRequest() {
        string accepterId;

        cout << "\n╔══════════════════════════════════════════╗\n";
        cout << "║       FULFILL BLOOD REQUEST              ║\n";
        cout << "╚══════════════════════════════════════════╝\n";
        cout << "Enter Accepter ID: ";
        cin >> accepterId;

        auto it = find_if(accepters.begin(), accepters.end(),
            [&accepterId](const Accepter& a) { return a.getId() == accepterId; });

        if (it != accepters.end()) {
            it->displayDetailed();

            if (it->getStatus() == "Fulfilled") {
                cout << "\n✗ Request already fulfilled!\n";
                return;
            }
            if (it->getStatus() == "Cancelled") {
                cout << "\n✗ Request has been cancelled!\n";
                return;
            }

            int unitsToFulfill = it->getUnitsRequired() - it->getUnitsReceived();
            cout << "\nUnits still needed: " << unitsToFulfill << endl;
            cout << "Current stock of " << it->getBloodGroup() << ": " 
                 << inventory.getStock(it->getBloodGroup()) << endl;

            int units;
            cout << "Enter units to provide (max " << unitsToFulfill << "): ";
            cin >> units;

            if (units > 0 && units <= unitsToFulfill) {
                if (inventory.removeBlood(it->getBloodGroup(), units)) {
                    it->addUnitsReceived(units);

                    string transId = "T" + to_string(++transCount);
                    transactions.push_back(Transaction(transId, "Distribution", 
                        it->getBloodGroup(), units, accepterId, it->getName()));

                    logUpdate("Blood distributed: " + to_string(units) + " units of " + 
                             it->getBloodGroup() + " to " + it->getName() + 
                             " (" + accepterId + "). Status: " + it->getStatus());

                    cout << "\n✓ Blood request fulfilled successfully!\n";
                    cout << "  Transaction ID: " << transId << endl;
                    cout << "  Units provided: " << units << " unit(s)\n";
                    cout << "  Total received: " << it->getUnitsReceived() 
                         << "/" << it->getUnitsRequired() << endl;
                    cout << "  Status: " << it->getStatus() << endl;
                    cout << "  Date & Time: " << getCurrentDateTime() << endl;
                } else {
                    cout << "\n✗ Insufficient blood stock!\n";
                }
            } else {
                cout << "\n✗ Invalid number of units!\n";
            }
        } else {
            cout << "\n✗ Accepter not found!\n";
        }
    }

    void viewAccepterDetails() {
        string accepterId;
        cout << "\nEnter Accepter ID: ";
        cin >> accepterId;

        auto it = find_if(accepters.begin(), accepters.end(),
            [&accepterId](const Accepter& a) { return a.getId() == accepterId; });

        if (it != accepters.end()) {
            it->displayDetailed();
        } else {
            cout << "\n✗ Accepter not found!\n";
        }
    }

    void displayAccepters() {
        if (accepters.empty()) {
            cout << "\nNo accepters registered.\n";
            return;
        }

        cout << "\n╔══════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                  REGISTERED ACCEPTERS                                    ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════╝\n";
        cout << left << setw(12) << "ID" << setw(25) << "Name" 
             << setw(5) << "Age" << setw(8) << "Blood" 
             << setw(8) << "Req" << setw(8) << "Recv"
             << setw(12) << "Urgency" << setw(12) << "Status" << endl;
        cout << string(90, '-') << endl;

        for (const auto& accepter : accepters) {
            accepter.display();
        }
        cout << string(90, '=') << endl;
    }

    // Search and reports
    void searchDonorByBloodGroup() {
        string bloodGroup;
        cout << "\nEnter Blood Group to search: ";
        cin >> bloodGroup;

        cout << "\n╔══════════════════════════════════════════════════════════════════════╗\n";
        cout << "║         DONORS WITH BLOOD GROUP " << bloodGroup << "                  ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
        cout << left << setw(12) << "ID" << setw(25) << "Name" 
             << setw(5) << "Age" << setw(15) << "Contact" 
             << setw(15) << "Last Donation" << endl;
        cout << string(72, '-') << endl;

        bool found = false;
        for (const auto& donor : donors) {
            if (donor.getBloodGroup() == bloodGroup) {
                cout << left << setw(12) << donor.getId() 
                     << setw(25) << donor.getName()
                     << setw(5) << donor.getAge()
                     << setw(15) << donor.getContact()
                     << setw(15) << donor.getLastDonationDate() << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No donors found with blood group " << bloodGroup << endl;
        }
        cout << string(72, '=') << endl;
    }

    void searchAccepterByBloodGroup() {
        string bloodGroup;
        cout << "\nEnter Blood Group to search: ";
        cin >> bloodGroup;

        cout << "\n╔══════════════════════════════════════════════════════════════════════╗\n";
        cout << "║       ACCEPTERS REQUESTING BLOOD GROUP " << bloodGroup << "            ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
        cout << left << setw(12) << "ID" << setw(25) << "Name" 
             << setw(8) << "Units" << setw(12) << "Urgency"
             << setw(12) << "Status" << endl;
        cout << string(69, '-') << endl;

        bool found = false;
        for (const auto& accepter : accepters) {
            if (accepter.getBloodGroup() == bloodGroup) {
                cout << left << setw(12) << accepter.getId() 
                     << setw(25) << accepter.getName()
                     << setw(8) << accepter.getUnitsRequired()
                     << setw(12) << accepter.getUrgencyLevel()
                     << setw(12) << accepter.getStatus() << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No accepters found requesting blood group " << bloodGroup << endl;
        }
        cout << string(69, '=') << endl;
    }

    void displayTransactionHistory() {
        if (transactions.empty()) {
            cout << "\nNo transactions recorded.\n";
            return;
        }

        cout << "\n╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                  TRANSACTION HISTORY                                         ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n";
        cout << left << setw(12) << "Trans ID" << setw(15) << "Type" 
             << setw(8) << "Blood" << setw(8) << "Units" 
             << setw(22) << "Date & Time" << setw(12) << "Person ID"
             << setw(20) << "Name" << endl;
        cout << string(97, '-') << endl;

        for (const auto& trans : transactions) {
            trans.display();
        }
        cout << string(97, '=') << endl;
    }

    void viewUpdateLog() {
        ifstream logFile(updateLogFile);
        if (!logFile.is_open()) {
            cout << "\nNo update log found.\n";
            return;
        }

        cout << "\n╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                    UPDATE LOG                                                ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n";

        string line;
        while (getline(logFile, line)) {
            cout << line << endl;
        }
        logFile.close();
        cout << string(97, '=') << endl;
    }

    void generateReport() {
        cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
        cout << "║              BLOOD BANK COMPREHENSIVE REPORT                 ║\n";
        cout << "╚══════════════════════════════════════════════════════════════╝\n";
        cout << "Report Generated: " << getCurrentDateTime() << endl;
        cout << string(64, '-') << endl;
        
        cout << "\n📊 STATISTICS:\n";
        cout << "  Total Donors Registered    : " << donors.size() << endl;
        cout << "  Total Accepters Registered : " << accepters.size() << endl;
        cout << "  Total Transactions         : " << transactions.size() << endl;
        
        int pendingRequests = 0, fulfilledRequests = 0, partiallyFulfilled = 0;
        for (const auto& accepter : accepters) {
            if (accepter.getStatus() == "Pending") pendingRequests++;
            else if (accepter.getStatus() == "Fulfilled") fulfilledRequests++;
            else if (accepter.getStatus() == "Partially Fulfilled") partiallyFulfilled++;
        }
        
        cout << "\n📋 REQUEST STATUS:\n";
        cout << "  Pending Requests           : " << pendingRequests << endl;
        cout << "  Partially Fulfilled        : " << partiallyFulfilled << endl;
        cout << "  Fulfilled Requests         : " << fulfilledRequests << endl;
        
        cout << string(64, '=') << endl;
        
        inventory.displayInventory();
    }

    // Main menu
    void displayMenu() {
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║        BLOOD BANK MANAGEMENT SYSTEM                    ║\n";
        cout << "╚════════════════════════════════════════════════════════╝\n";
        cout << "┌────────────────── DONOR SECTION ──────────────────────┐\n";
        cout << "│ 1.  Register New Donor                                │\n";
        cout << "│ 2.  Update Donor Information                          │\n";
        cout << "│ 3.  Process Blood Donation                            │\n";
        cout << "│ 4.  View Donor Details                                │\n";
        cout << "│ 5.  Display All Donors                                │\n";
        cout << "│ 6.  Search Donors by Blood Group                      │\n";
        cout << "├────────────────── ACCEPTER SECTION ───────────────────┤\n";
        cout << "│ 7.  Register New Accepter                             │\n";
        cout << "│ 8.  Update Accepter Information                       │\n";
        cout << "│ 9.  Fulfill Blood Request                             │\n";
        cout << "│ 10. View Accepter Details                             │\n";
        cout << "│ 11. Display All Accepters                             │\n";
        cout << "│ 12. Search Accepters by Blood Group                   │\n";
        cout << "├────────────────── REPORTS & LOGS ─────────────────────┤\n";
        cout << "│ 13. View Blood Inventory                              │\n";
        cout << "│ 14. View Transaction History                          │\n";
        cout << "│ 15. View Update Log                                   │\n";
        cout << "│ 16. Generate Comprehensive Report                     │\n";
        cout << "│ 0.  Exit                                              │\n";
        cout << "└───────────────────────────────────────────────────────┘\n";
        cout << "Enter your choice: ";
    }

    void run() {
        int choice;
        do {
            displayMenu();
            cin >> choice;

            switch (choice) {
                case 1: registerDonor(); break;
                case 2: updateDonor(); break;
                case 3: processDonation(); break;
                case 4: viewDonorDetails(); break;
                case 5: displayDonors(); break;
                case 6: searchDonorByBloodGroup(); break;
                case 7: registerAccepter(); break;
                case 8: updateAccepter(); break;
                case 9: fulfillRequest(); break;
                case 10: viewAccepterDetails(); break;
                case 11: displayAccepters(); break;
                case 12: searchAccepterByBloodGroup(); break;
                case 13: inventory.displayInventory(); break;
                case 14: displayTransactionHistory(); break;
                case 15: viewUpdateLog(); break;
                case 16: generateReport(); break;
                case 0: 
                    cout << "\n💾 Saving all data...\n";
                    saveData();
                    cout << "✓ Data saved successfully!\n";
                    cout << "\nThank you for using Blood Bank Management System!\n";
                    cout << "════════════════════════════════════════════════════\n";
                    break;
                default: 
                    cout << "\n✗ Invalid choice! Please try again.\n";
            }

            if (choice != 0) {
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }

        } while (choice != 0);
    }
};

// Main function
int main() {
    cout << "\n╔════════════════════════════════════════════════════════╗\n";
    cout << "║                                                        ║\n";
    cout << "║        WELCOME TO BLOOD BANK MANAGEMENT SYSTEM         ║\n";
    cout << "║                                                        ║\n";
    cout << "║            Saving Lives, One Drop at a Time           ║\n";
    cout << "║                                                        ║\n";
    cout << "╚════════════════════════════════════════════════════════╝\n\n";
    
    BloodBankSystem system;
    system.run();
    return 0;
}