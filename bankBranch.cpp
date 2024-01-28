/*****************************************************************
NAME: Mariana Berrio and Katherine Duque
ORGN: BCSAI-COMPUTER PROGRAMMING 1 22-23, IE University
FILE: bankBranch.cpp
*****************************************************************/

#include "bankBranch.h"
#include "prePaidCard.h"

#include <regex>

using namespace std;
int blackListIndex = 0;

// V3.0 Constructor. It opens the file passed as argument
BankBranch::BankBranch(string name_branch) {
  name = name_branch;
  file = name_branch.append(".txt");
};

string BankBranch::getName() {
  return name;
}

// V2.0
void BankBranch::loadClients() {
  PrePaidCard a;

  ifstream file1;

  int i = 0;
  number_clients = 0; // V3 In case it is the first time we open the file

  // Open file in read mode
  file1.open(file, ios::in);
  if (!file1) {
    cout << "Error in opening file..";
  }

  // Read data from file
  file1.read((char *)&a, sizeof(a));
  while (!file1.eof()) {

    // Display data on monitor
    a.showData();
    client[i] = a;
    i++;
    file1.read((char *)&a, sizeof(a));
  }

  // Close the file
  file1.close();
  number_clients = i;
}

// Search user. Used by users
// V3. It returns the account_number if user\password are correct
int BankBranch::searchSpecificUser(char *uname, int pass) {
  for (int i = 0; i < number_clients; i++) {
    if (!strcmp(client[i].getUsername(), uname)) {
      if (client[i].getPasswords() == pass) {
        return i;
      }
    }
  }
  return -1; //-1 Password incorrect
}
void BankBranch::loadBlackList() {
  ifstream file(name + "BL.txt");
  while (file >> blackList_clientsID[blackListIndex]) {
  blackListIndex++;
  }
  file.close();
}
bool BankBranch::isBlackListed(char *uname) {
  string tempS = uname;
  for (int i = 0; i < 10; i++) {
    if (blackList_clientsID[i] == tempS) {
      return true;
    }
  }
  return false;
}

int BankBranch::blacklistUser(char *uname) {
  int index = searchSpecificUser(uname);
  if (index == -1) {
    cout << "Client with that username not found";
    return -1;
  }
  deleteUser(uname);
  blackList_clientsID[blackListIndex] = uname;
  return 0;
}

int BankBranch::searchSpecificUserBL(char *uname) {
  string tempString = uname;
  for (int index = 0; index < blackListIndex; index++) {
    string temp = blackList_clientsID[index];
    temp = regex_replace(temp, regex("\\r\\n|\\r|\\n"), "");
    if (temp == tempString) {
      return index;
    }
  }
  return -1;
}

int BankBranch::deleteUserFromBlackList(char* uname) {
  int index = searchSpecificUserBL(uname);
  if (index == -1) {
    cout << "User not found on black list";
    return -1;
  }
  for (int i = index; i < blackListIndex - 1; i++) {
    blackList_clientsID[i] = blackList_clientsID[i + 1];
  }
  blackListIndex--;
  return 0;
}

// Search user. Used by Admins
// V3. It returns the account_number
int BankBranch::searchSpecificUser(char *uname) {
  for (int i = 0; i < number_clients; i++) {
    if (!strcmp(client[i].getUsername(), uname))
      return i;
  }
  return -1; //-1 No user found
}

void BankBranch::displayUser(char* uname) {
  int index = searchSpecificUser(uname);
  client[index].showData();
}

// V3
void BankBranch::setUserLoginDate(int found) {
  client[found].setLastLogin(); 
  }

// Function to add user
int BankBranch::addUser() {
  PrePaidCard newPrepaidCard;
  newPrepaidCard.getData();
  client[number_clients] = newPrepaidCard;
  number_clients++;
  return 0;
}
// Display user balance
int BankBranch::displayBalance(){
  if (number_clients == 0){
    cout << "We still don't have any client ;(\n";
  }
  for (int i = 0; i < number_clients; i++) {
    client[i].getBalance();
  }
  return 0;
}
// View Users
int BankBranch::viewallUsers() {
  if (number_clients == 0){
    cout << "We still don't have any client ;(\n";
  }
  for (int i = 0; i < number_clients; i++) {
    client[i].showData();
  }
  return 0;
}

void BankBranch::saveClients() {
  fstream temp;
  if (number_clients == 0) // We still don't have any client
    return;

  temp.open("temp.txt", ios::out | ios::app);
  for (int i = 0; i < number_clients; i++) {
    temp.write((char *)&client[i], sizeof(client[i]));
  }
  // Close the file
  temp.close();
  remove(&file[0]);
  rename("temp.txt", &file[0]);
}

// Function to delete the user
int BankBranch::deleteUser(char* uname) {
    int index = searchSpecificUser(uname);
    if (index == -1) {
        cout << "User not found" << endl;
        return -1;
    }
    for (int i = index; i < number_clients - 1; i++) {
        client[i] = client[i + 1];
    }
    number_clients--;
    return 0;
}

void BankBranch::deposit(char* uname, double amount){
  int index = searchSpecificUser(uname);
  double tempBalance = client[index].getBalance();
  client[index].setBalance(tempBalance + amount);
}

void BankBranch::withdraw(char* uname, double amount){
  int index = searchSpecificUser(uname);
  double tempBalance = client[index].getBalance();

  if (tempBalance > amount) {
            client[index].setBalance(tempBalance - amount);
        } else if (tempBalance < amount) {
            cout << "You don't have enough fund do make this transaction";
            } else {
                cout << "Limit exceeded, nothing was done";
            }
}


int BankBranch::changeUserPass(char *uname) {
  int index = searchSpecificUser(uname);
  if (index == -1) {
    cout << "\nClient with that username not found";
    return -1;
  } else {
    bool checkPass = false;
    string tempPass;
    while (!checkPass) {
      cout << "\nEnter the new password: ";
      cin >> tempPass;

      if (tempPass.size() > 4) {
        cout << "\nInvalid password, it has to be 4 characters";
        continue;
      } else {
        checkPass = true;
        client[index].setPassword(stoi(tempPass));
      }
    }
    return 0;
  }
}

// V3.0 Help Debug the code. Information for BankBranch Object
int BankBranch::debug() {
  cout << "BankBranch Attributes\n";
  cout << "Name->" << name << " MAX_NUMBER_ACCOUNTS->" << MAX_NUMBER_ACCOUNTS
       << " number_clients->" << number_clients << " balance->" << balance
       << " file->" << file << endl;
  cout << "\n***All Users Information***\n";
  viewallUsers();
  return 0;
}
