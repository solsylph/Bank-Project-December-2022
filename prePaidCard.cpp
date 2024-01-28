/*****************************************************************
NAME: Mariana Berrio y Katherine Duque
ORGN: BCSAI-COMPUTER PROGRAMMING 1 22-23, IE University
FILE: prePaidCard.cpp
*****************************************************************/
#include "prePaidCard.h"

void PrePaidCard::setLastLogin() { last_login = time(0); }

string PrePaidCard::getLastLogin() {
  char *dt = ctime(&last_login); // convert in string form
  return dt;
}

char *PrePaidCard::getUsername(void) {
  // Return username
  return username;
}

int PrePaidCard::getPasswords(void) {
  // Return the password
  return password;
}
char* PrePaidCard::getClient_id() {
  return user_ID; 
}

double PrePaidCard::getBalance() { return balance; }
void PrePaidCard::setBalance(double newBalance) { balance = newBalance; }

double PrePaidCard::getLimit() { return limit_negative; }


// Function to get the data
void PrePaidCard::getData(void) {
  srand(0);
  
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Enter username: ";
  cin.getline(username, 30);
  
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Enter your ID: (passport or DNI)";
  cin.getline(user_ID, 30);
  
  cout << "\nEnter a 4-digit password:";
  cin >> password;
  
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "\nEnter initial balance: ";
  cin >> balance;
  
  ccv = (rand() % 9000) + 100;
  cout << "\nYour CCV is: " << ccv;

  card_ID = (rand() % 900) + 1000;
  cout << "\nYour Card ID is: " << card_ID;
  

  setLastLogin();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void PrePaidCard::setPassword(int newPassword) { 
  password = newPassword; 
  }
// Function displaying the data
void PrePaidCard::showData(void) {
  cout << "Username: " << username << "\n Password: " << password << ",\n ID document: " << user_ID <<"\n CCV : " << ccv << "\n Card ID: " << card_ID << "\n Balance: " << balance << "\n Last Login: " << getLastLogin() << endl;
}
