/*****************************************************************
NAME: Mariana Berrio y Katherine Duque
ORGN: BCSAI-COMPUTER PROGRAMMING 1 22-23, IE University
FILE: main.cpp
'aaa' branch = Colombia
'Madrid' branch = Madrid
'Segovia' branch = Venezuela
we wanted to give the project a personal touch
*****************************************************************/
#include "bankBranch.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <string.h>
#include <unistd.h>

using namespace std;

void atmUser() {
  const string branch1 = "madrid";
  const string branch2 = "colombia";
  const string branch3 = "venezuela";
  
  BankBranch *activeBranch;
  string blackList_clientsID[MAX_NUMBER_ACCOUNTS] = {};
  char uname[30];
  char user_ID[30];
  int pass, ch, ch1, ch2, ch3, ch4,loginchoice, found = 0;
  int choice;
  bool validOption = false;
  int d_w;
  double tempAmount;
  
  cout << "Select the Branch that you would like to work with:";
  cout << "\n1. Madrid\n2. Colombia\n3. Venezuela";
  cout << "\nChoose one:";
  while (!validOption) {
    cin >> choice;
    if (choice == 1) {
      BankBranch madridBranch(branch1);
      activeBranch = &madridBranch;
    } else if (choice == 2) {
      BankBranch colombiaBranch(branch2);
      activeBranch = &colombiaBranch;
    } else if (choice == 3) {
      BankBranch venezuelaBranch(branch3);
      activeBranch = &venezuelaBranch;
    } else {
      cout << "Invalid option\nPlease select a valid branch";
      continue;
    }
    validOption = true;
  }

  cout << "*****BankBranch Madrid Information*****\n";
  activeBranch->loadClients();
  activeBranch->debug();

  sleep(5);

mainmenu:
  system("clear");
  cout << "\nWelcome to " << activeBranch->getName() << " BankBranch";
  cout << "\nLogin as: \n1. Admin\n2. User\n3. Exit"
       << "\nChoose one: ";
  cin >> ch;

  switch (ch) {
  case 1:
  rerun:
    system("clear");
    cout << "\nEnter details to login as Admin\n";
    cout << "\nEnter password:";
    cin >> pass;
    if (pass == 1234) {
    admin:
      system("clear");
      cout << "\nWelcome to the BankBranch Admininistrator Menu! What shall you proceed with?: ";
      cout << "\n1. Add user\n2. View all users \n3. Update customer Data\n4. Exit the Admin Menu";
      cout << "\nSelect one: (numbers 1-4)";
      cin >> ch1;
      switch (ch1) {
      case 1:
        activeBranch->addUser();
        goto admin;

      case 2:
        activeBranch->viewallUsers();
        sleep(4);
        goto admin;
        

      case 3:
          cout << "\nUpdate customer Data";
          cout << "\n1. Make a withdrawal on behalf of the selected customer \n2. Make a deposit for the selected customer \n3. Print customer balance \n4. Add customer to blacklist \n5. Remove customer from blacklist \n6. Change customer PIN \n7. Go back to admin menu";
          cout << "\nSelect one: (numbers 1-7)";
          cin >> ch2;

          switch (ch2) {
          case 1:
            cout << "\n You will make a withdrawal on behalf of the selected customer";
          cout << "\n Enter the username that you would like to make a withdrawal on behalf: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(uname, 30);
        cout << "Enter the amount you would like to withdraw from the account:";
        cin >> tempAmount;
          activeBranch->withdraw(uname, tempAmount);
         goto admin;
            
          case 2:
            cout << "\n You will make a deposit on behalf of the selected customer";
          cout << "\n Enter the username that you would like to make a deposit on behalf: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(uname, 30);
        cout << "Enter the amount you would like to deposit into the account:";
        cin >> tempAmount;
          activeBranch->deposit(uname, tempAmount);
        goto admin;

          case 3:
            cout << "Displaying the customer's balance:";
            activeBranch->displayBalance();
          goto admin;
          case 4:
            cout << "You chose to add a customer to the blacklist";
             cout << "\nEnter the username to be added to the blacklist: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(uname, 30);
            
        activeBranch->blacklistUser(uname);
        goto admin;
            
          case 5:
            cout <<"You chose to remove customer from the blacklist";
            cout << "\nEnter the username that you would like to remove from the blacklist: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(uname, 30);
        activeBranch->deleteUserFromBlackList(uname);

        goto admin;
            
          case 6:
            cout << "You chose to change the customer's pin";
            cout << "\nEnter the username of the account you want to change the pin: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(uname, 30);
        activeBranch->changeUserPass(uname);
        goto admin;
            
          case 7:
            goto admin;
                  
          }
      case 4:
        break;
      }
    } else {
      cout << "\nDetails are incorrect! Please try again";
      cin.get();
      goto rerun;
    }
    goto mainmenu;

  case 2:
    cout << "\n Enter details to login as User";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n Press 1 to login with your username and press 2 to login with you ID\n ";
    cin >> loginchoice;

    if(loginchoice == 1)
    {
      cout << "\n Please enter your username:";
      cin >> uname;

      cout << "\nPlease enter your password:";
      cin >> pass;

      goto user;
    }

    else if(loginchoice == 2)
    {
      cout << "\n Please enter your ID number:";
      cin >> user_ID;

      cout << "\nPlease enter your password:";
      cin >> pass;
    }
    else
    {
      cout << "Please enter a valid option";
    }

    if (uname == blackList_clientsID[0]){
    cout << "Sorry, it seems like you are on the blacklist. If you think that his might be an error, please get in touch with a bank admin to solve this issue";
    break;
    }
  

    
    found = activeBranch->searchSpecificUser(uname, pass) || activeBranch->searchSpecificUser(user_ID, pass);

    if (found != -1) {
    user:
      system("clear");
      activeBranch->setUserLoginDate(found);
      cout << "\nWelcome " << uname;
      cout << "\nWelcome to the BankBranch User Menu! Please pick from the following options:";
      cout << "\n1. Print your data\n2. Update your data (Deposit, Withdraw, Change PIN, print balance)\n3. Exit menu\nEnter your choice:";
      cin >> ch3;

      switch (ch3) {
      case 1:
        activeBranch->displayUser(uname);
        sleep(4);
        goto user;

          //activeBranch->updateUserBalance(uname, tempAmount, d_w);
      case 2:
        cout << "\n 1. Withdraw funds\n 2. Make a deposit\n 3. Print balance\n 4. Change the Pin\n 5. Go back to the user menu";
        cout <<"\n Please select one of these choices (1-5)";
        cin >> ch4;
        switch (ch4) {
          case 1:
          cout << "\n You chose to withdraw funds. ";

          cout << "\n How much would you like to withdraw?";
          cin >> tempAmount;
            
          activeBranch->withdraw(uname, tempAmount);
          cout << "Your balance after the withdrawal is "<<d_w;
          goto user; 
        
          case 2:
          cout << "You chose to make a deposit.";
          cout << "\n How much would you like to deposit into your account?";
          cin >> tempAmount;
          activeBranch->deposit(uname, tempAmount);
          goto user;
          
          case 3:
          cout << "You can see your balance below";
          activeBranch->displayBalance();
          goto user;
          
          case 4:
          cout << "You chose to change your pin";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        activeBranch->changeUserPass(uname);
          goto user;
          
          case 5:
          goto user;
          }
          
      case 3:
        cout << "Thank you";
        break;
      }
        
    } else {
      cout << "\nNo record of " << uname
           << " was found in our system :(\nHit ENTER to continue ";
      cin.get();
      goto mainmenu;
      
    }

  case 3:
    cout << "\nThank you for banking with MariandKathe! ";
    activeBranch->saveClients();
    cin.get();
    break;
  }
  }

int main() {
  atmUser();
  return 0;
  }
