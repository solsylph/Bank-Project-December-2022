/*****************************************************************
NAME: Mariana Berrio y Katherine Duque
ORGN: BCSAI-COMPUTER PROGRAMMING 1 22-23, IE University
FILE: bankBranch.h.cpp
*****************************************************************/
// C++ code to implement an ATM and
// its basic functions
#include <fstream>
#include <iostream>
#include <limits>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "prePaidCard.h"


using namespace std;

#ifndef Included_BankBranch

#define Included_BankBranch

// Class PrePaidCard to get user and Card details

const int MAX_NUMBER_ACCOUNTS=10;

class BankBranch {
private:
  PrePaidCard client [MAX_NUMBER_ACCOUNTS];   
  string name;
  int number_clients;
  int balance;
  string file; //default name of the file with the PrePaidCards
public:
// Member Functions
   BankBranch(); //V3.0 Constructor. It opens the file passed as argument
   BankBranch(string); //V3.0 Constructor. It asign a name to the Branch. File will be the name + ".txt"
   string getName();
   void loadClients(); //V2.0 It loads all clients from file aaa.txt
   void saveClients(); //V2.0 It saves the clients to a file aaa.txt
   void setUserLoginDate(int); //To update last user login
  void displayUser(char*);
  void loadBlackList();
  int debug();
  bool isBlackListed(char*);
  int blacklistUser(char *);
  int searchSpecificUserBL(char*);
  int deleteUserFromBlackList(char *);
  int changeUserPass(char *); // change pin/pass
  int displayBalance();
   int addUser();
   int viewallUsers();
   int deleteUser(char*);
   void updateBalance(char*, double, char);
  void deposit(char*, double);
  void withdraw(char*, double);
   int searchSpecificUser(char*, int); //To be used by users
   int searchSpecificUser(char*); //To be used by Addmins. Don't need to know the password
  string blackList_clientsID[MAX_NUMBER_ACCOUNTS] = {}; // list of blacklisted clients
  string blackList_cardsID[MAX_NUMBER_ACCOUNTS]; // list of blacklisted card IDs\

};

#endif
