// Title: CipherString.cpp
// Author: Steve Cabral Tchounkeu Nana
// E-mail: steve20@umbc.edu
// Section: 17
// Date: 10/27/2017
// Description: This code will make the instructions that will be used by 
//              CipherString.h

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "CipherString.h"

using namespace std;

// Name: CipherString - default constructor                               
// Preconditions - None                                                   
// Postconditions - Creates a new CipherString
                                
CipherString::CipherString(){
  m_head = NULL; //Sets the pointer to point at nothing
  m_size = 0; //Sets the size of the linked list to 0
}
  

// Name: CipherString - overloaded constructor                               
// Preconditions - None                                                      
// Postconditions - Creates a new CipherString (using char*)

CipherString::CipherString(const char* ){
  m_head = NULL;
  m_size = 0;
}

// Name: ~CipherString - destructor                                          
// Preconditions - None                                                      
// Postconditions - Destroys CipherString                                    
CipherString::~CipherString(){
  Node* currentNode = m_head;
  while(currentNode != NULL ) {
    currentNode = currentNode->getNext();
    delete currentNode;
    currentNode = m_head;
    m_size--;
  }
  m_head = NULL;
}
  

// Name: loadMessage                                                         
// Preconditions - File (with text in it) is passed to function              
// Postconditions - Opens file and loads one character at a time into the linked list                                                                       
void CipherString::loadMessage(const char* stringFile){

  char character;
  ifstream myFile (stringFile); //Declares and opens a file
  if (myFile.is_open()) { //Checks to see if the file exists and was opened
    while(myFile){
      myFile.get(character); 
      addCharacter(character);
    }
  }else {
    cout << "Unable to open file" << endl;
  }
  myFile.close();

}
  
// Name: addCharacter                                                        
// Preconditions - Linked list exists                                        
// Postconditions - Adds character to end of linked list                     
void CipherString::addCharacter(char character){

   Node *newNode = new Node();
  if(m_head == NULL){ //Checks to see if the linked list is empty
    m_head = newNode; //Inserts the first node to the linked list
    newNode->setChar(character); //Sets the value of the first node
    newNode->setNext(NULL); //Sets the first node in the linked list to point to nothing
    m_size++;
  }
  else{
    Node *temp = m_head;
    
    while(temp->getNext() != NULL){
      temp = temp->getNext();
    }
    temp->setNext(new Node(character));
    m_size++; //Increments the size of the linked list
  }    
  
}

// Name: encryptOng                                                          
// Preconditions - Linked list exists                                        
// Postconditions - For each consonent, adds a node with "o", adds a node with "n"
// adds a node with "g". Every "letter" is separated with a "-" and each word is
// seperated by a space.                                 
void CipherString::encryptOng(){

  for(Node *curr = m_head; curr != NULL; curr->getNext()){
    //checks for lower case vowels and adds a '-' after them
    if(curr->getChar() == 'a' or curr->getChar() == 'e' or curr->getChar() == 'i' or curr->getChar() == 'o' or curr->getChar() == 'u'){
      //checks if the next character exits
      if(curr->getNext() != NULL){
	Node* nextNode = curr->getNext();
  	curr->setNext(new Node('-'));
  	curr->getNext();
  	curr->setChar(nextNode->getChar());
      }
    }

    //checks for upper case vowels and adds a '-' after them
    else if(curr->getChar() == 'A' or curr->getChar() == 'E' or curr->getChar() == 'I' or curr->getChar() == 'O' or curr->getChar() == 'U'){   
      //checks if the next character exits
      if(curr->getNext() != NULL){
	Node* nextNode = curr->getNext();
  	curr->setNext(new Node('-'));
  	curr->getNext();
  	curr->setChar(nextNode->getChar());
      }
    }

    else{
      //checks if the next character exits
      if(curr->getNext() != NULL){
  	Node* nextNode = curr->getNext();
  	curr->setNext(new Node('o'));
  	curr->getNext();
  	curr->setNext(new Node('n'));
  	curr->getNext();
  	curr->setNext(new Node('g'));
  	curr->getNext();
  	curr->setNext(new Node('-'));
  	curr->getNext();
  	curr->setChar(nextNode->getChar());
      }
    }
  }
}

// Name: decryptOng                                                          
// Preconditions - Linked list exists                                        
// Postconditions - For each consonent, adds a node with "o", adds a node with "n"
// adds a node with "g". Every "letter" is separated with a "-" and each word is    
// seperated by a space                                                     
void CipherString::decryptOng(){
  //    for(Node *curr = m_head; curr != NULL; curr->getNext()){
      
  //}
}

// Name: encryptCaesar                                                       
// Preconditions - Linked list exists                                        
// Postconditions - Shifts each character "right" by the int provided.       
// See project document for additional details.                              
void CipherString::encryptCaesar(int caesarKey){

  Node *character = m_head;
  for (int i = 0; i < m_size; i++){

    //checks if the character is a space and leaves it unchanged
    if (character->getChar() == ' '){
      character->setChar(' ');
    }

    //checks if the character is upper case make changes with respect to 
    //the caesar key
    else if (character->getChar() == isupper(character->getChar())){
      character->setChar((((character->getChar() + caesarKey) - 65) % 26) + 65);
    }
    
    //checks if the character is lower case make changes with respect to 
    //the caesar key
    else{
      character->setChar((((character->getChar() + caesarKey) - 97) % 26) + 97);
    }
    character = character->getNext();//allows to go to the next node
  }
}

// Name: decryptCaesar                                                       
// Preconditions - Linked list exists                                        
// Postconditions - Shifts each character "left" by the int provided.        
// See project document for additional details.                              
void CipherString::decryptCaesar(int caesarKey){

  Node *character = m_head;
  for (int i = 0; i < m_size; i++){

    //checks if the character is a space and leaves it unchanged
    if (character->getChar() == ' '){
      character->setChar(' ');
    }

    //checks if the character is upper case make changes with respect to 
    //the caesar key
    else if (character->getChar() == isupper(character->getChar())){
      character->setChar((((character->getChar() - caesarKey) - 65) % 26) + 65);
    }

    //checks if the character is lower case make changes with respect to 
    //the caesar key
    else{
      character->setChar((((character->getChar() - caesarKey) - 97) % 26) + 97);
    }
    character = character->getNext();
  }
}

// Name: encryptVigenere                                                     
// Preconditions - Linked list exists                                        
// Postconditions - Shifts each character by the character (in string) provided.
// See project document for additional details.                              
void CipherString::encryptVigenere(string vigenereKey){

  int changePosition = 0;
  if (m_head != NULL){
    int vigenereKeyIndex = 0;
    Node *curr = m_head;

    //iterates through the linked list and use the vigenere to make changes
    while(curr != NULL){
      //checks for upper case letter 
      if(isupper(curr->getChar())){
	changePosition = curr->getChar() + vigenereKey[vigenereKeyIndex % vigenereKey.size()] - 96;

	if(changePosition > 90){
	  changePosition -= 26;
	}

	curr->setChar(char(changePosition));
      }
      //checks for lower case letter
      else if(islower(curr->getChar())){
	changePosition = curr->getChar() + vigenereKey[vigenereKeyIndex % vigenereKey.size()] - 96;

	if(changePosition > 122){
          changePosition -= 26;
        }

	curr->setChar(char(changePosition));
      }
      curr = curr->getNext();
      changePosition++;
    }
  }
}

// Name: decryptVigenere                                                      
// Preconditions - Linked list exists                                         
// Postconditions - Shifts each character by the character (in string) provided
// See project document for additional details.                               
void CipherString::decryptVigenere(string vigenereKey){
  int changePosition = 0;
  if (m_head != NULL){
    int vigenereKeyIndex = 0;
    Node *curr = m_head;
    while(curr != NULL) {
      if(isupper(curr->getChar())){
        changePosition = curr->getChar() - vigenereKey[vigenereKeyIndex % vigenereKey.size()] + 96;
	
        if(changePosition < 65){
          changePosition += 26;
        }

        curr->setChar(char(changePosition));
      }

      else if(islower(curr->getChar())){
        changePosition = curr->getChar() - vigenereKey[vigenereKeyIndex % vigenereKey.size()] + 96;

        if(changePosition < 97){
          changePosition += 26;
        }
        curr->setChar(char(changePosition));
      }
      curr = curr->getNext();
      changePosition++;
    }
  }
}

// Name: getSize                                                              
// Preconditions - Linked list exists                                         
// Postconditions - Return size of structure                                 
 
int CipherString::getSize(){
  return m_size;
}

// Name: operator<< (overloaded insertion operator)                           
// Preconditions - Linked list exists                                         
// Postconditions - Iterates over the linked list and prints each char in each node  
// In this case, friend means that it is accessible outside the class (like public) 
ostream& operator<<(ostream& cipherString, const CipherString& linkedList){

  Node *curr = linkedList.m_head;
  int count = 0;
  while(count < linkedList.m_size){

    cipherString << curr -> getChar();

    curr = curr -> getNext();

    count++;

  }

  return cipherString;
}


