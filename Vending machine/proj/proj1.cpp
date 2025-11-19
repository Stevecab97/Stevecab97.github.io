//Title: PROJECT1: TRUE GRIT SNACK BAR                                         
//Author: Steve Cabral Tchounkeu Nana                                          
//E-mail: Steve20@umbc.edu                                                     
//Section: 17                                                                  
//Description: This program reads from a file to create self-service snack     
//             bar. This program will take in the users input and make         
//             a receipt, get their order depending on their choice            


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 10;
const double TAX = 0.06;
const int MAX_ORDERS = 3;
int index;

void printInstructions();
void createMenu();
void userChoice(string itemArray[MAX_SIZE][MAX_SIZE], 
		double priceArray[MAX_SIZE][MAX_SIZE]);

void receipt(int quantity[], double prices[], string items[], int count);

void finalPrice(int quantityArray[MAX_ORDERS], string orderArray[MAX_ORDERS], double allPrices[MAX_SIZE]);

int main(){
  
  int choice = 0;
  int count = 0;

  printInstructions();
  cin >> choice;


  while (choice != MAX_ORDERS and count <= 0) {
    switch (choice){
    case 1:
      createMenu();
      break;

    case 2:
      break;

    default:
      printInstructions();
      cin >> choice;
      break;

    }

    count = count++;

  }

  return 0;
}

//------------------------------------------------------------------------
// Name: printInstructions()
// PreCondition:
// PostCondition: prints instructions the user must follow to execute 
// specific tasks
//------------------------------------------------------------------------

void printInstructions(){

  cout << "The item list was successfully loaded" << endl;
  cout << "Welcome to the True Grit Snack Bar" << endl;
  cout << "What would you like to do?:" << endl;
  cout << "1. New Order"<< endl;
  cout << "2. View Receipts" << endl;
  cout << "3. Exit" << endl;

}

//-----------------------------------------------------------------------
// Name: createMenu
// PreCondition: reads fromthe file proj1_items.txt and creates arrays
// that hold in the content of proj1_items.txt
// PostCondition: passes the created arrays to userChoice() and prints
// a menu with the possible choices the user can make
//-----------------------------------------------------------------------

void createMenu(){
  
  int count = 0;
  string itemArray[MAX_SIZE][MAX_SIZE];
  double priceArray[MAX_SIZE][MAX_SIZE];
  string item ;
  double price ;
  ifstream itemsFile("proj1_items.txt");


  if (itemsFile.is_open()) { //Checks to see if the file exists and was opened
    cout << setw(8) << "Number" << setw(21) << "Item" << setw(11) << "Price" <<endl;
    while(itemsFile && count < MAX_SIZE){

      getline(itemsFile, item, ',');
      itemsFile >> price; 

      itemArray[0][count] = item;
      priceArray[0][count] = price;

      if (itemsFile.peek() == '\n')
	itemsFile.ignore();
      
      cout << setw(8) << count + 1 << "." << setw(21) << item << setw(11) << "$" << price << endl; 
      count++;
    }
  }

  else {
    cout << "Unable to open file"; //If the input file does not exist, notifies user
  }

  itemsFile.close(); 
  userChoice(itemArray, priceArray);  
}

//--------------------------------------------------------------------------
// Name: userChoice
// PreCondition: takes input (snackNum, snackQty, yesOrNo) from the user to
//               either continue making orders, or to stop using the app
// PostCondition:
//-------------------------------------------------------------------------

void userChoice(string itemArray[MAX_SIZE][MAX_SIZE], double priceArray[MAX_SIZE][MAX_SIZE]){

  int count = 0;
  int index = 0;
  int snackNum = 0;
  int snackQty = 0;
  string yesOrNo = "";
  int quantityArray[MAX_ORDERS];
  string orderArray[MAX_ORDERS];
  double allPrices[MAX_ORDERS];

  cout << "What would you like to buy?:" << endl;
  cin >> snackNum;

  //this while loop checks if the snack number is between 1 and 10
  while(snackNum <= 0 or snackNum > MAX_SIZE){
    cout << "What would you like to buy?:" << endl;
    cin >> snackNum;
  }

  cout << "How many would you like to buy?:" << endl;
  cin >> snackQty;

  cout << "Do you want to add more items? (y/n):" << endl;
  cin >> yesOrNo;
  
  if (yesOrNo == "y" or yesOrNo == "Y" and count < MAX_ORDERS){
    quantityArray[count] == snackQty ;
    allPrices[count] == priceArray[0][snackNum - 1];
    orderArray[count] == itemArray[0][snackNum - 1];
    count += 1;
    receipt(quantityArray, allPrices, orderArray, count);
    createMenu();
    
  }

  else (yesOrNo == "n" or yesOrNo == "N");{
    // function calls to print the receipt
    finalPrice(quantityArray, orderArray, allPrices);
  }

}

//--------------------------------------------------------------------------
// Name: receipt
// PreCondition: Take in the value of quantity, price, and item to create
//               the file memory.txt
// PostCondition:
//--------------------------------------------------------------------------

void receipt(int quantity[], double prices[], string items[], int count){

  ofstream memoryFile("memory.txt", ofstream::out | ofstream::app);
  for (int i = 0; i < MAX_ORDERS; i++){
    if (memoryFile.is_open()){
      memoryFile << quantity[i];
      memoryFile << items[i];
      memoryFile << prices[i];
      createMenu();
    }
  }
  memoryFile.close();
}


//---------------------------------------------------------------------------
// Name: finalPrice
// PreCondition: reads from memory file to caculate and print the final price
// PostCondition: calculates the total to pay and prints a receipt
//---------------------------------------------------------------------------
  
void finalPrice(int quantityArray[], string orderArray[], double allPrices[]){
  
  ifstream memoryFile("memory.txt");
  int count1 = 0;
  double subtotal;
  double total;
  double tax;
  int quantity = 0;
  double price;
  string item;

  //this code reads a text file that stores the orders of the user
  // and prints them
  cout << "Your Order:" << endl;
  cout << setw(8) << "Qnty" << setw(21) << "Item" << setw(11) << "Price" << endl;
  
  if(memoryFile.is_open()){
    while (memoryFile){

      memoryFile >> quantity;
      memoryFile >> price;
      memoryFile >> item;

      cout << setw(8) << quantity << setw(21) << item << setw(11) << "$" << price << endl;

      subtotal += quantity * price;
      tax = subtotal * TAX;
      total = subtotal + tax;

    }
  }

  cout << "Subtotal: " << subtotal << endl;
  cout << "Tax: " << tax << endl;
  cout << "Total: " << total << endl;

}


