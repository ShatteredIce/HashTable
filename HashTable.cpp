//C++ Project 14 - HashTable - 6/1/17
//Stores a student list using a hash table

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <fstream>
#include <vector>
#include "StudentNode.h"

using namespace std;

//prototypes
void getInput(char* input);
void trimWhitespace(char* text);
int getInt(char* message);
void addStudent(StudentNode** hashTable, Student* s, int tablesize);
void printTable(StudentNode** hashTable, int tablesize);
int hashFunction(int id, int arr_size);
bool validId(int id, StudentNode** hashTable, int tablesize);

const int INPUT_SIZE = 201;

int main(){

  srand(time(NULL));

  char input[INPUT_SIZE];
  int current_id = 1;

  int tablesize = 100;
  StudentNode** hashTable = new StudentNode* [tablesize];

  cout << "\n-----Hash Table v1.0-----\n";
  cout << "Creates a hash table to store a list of students\n";
  cout << "Availible commands are: 'add', 'print', 'delete', 'generate', and 'quit'.\n";
  cout << "You may enter custom names into firstname.txt and lastname.txt (one per line)\n";
  cout << "C++ Project 14 - Nathan Purwosumarto\n\n";

  while(true){
    cout << "Awaiting input: ";
    getInput(input);
    //if input = quit, then end the program
    if(strcmp(input, "quit") == 0){
      cout << "Program Terminated." << endl;
      break;
    }
    else if(strcmp(input, "add") == 0){
      Student* s = new Student();
      char firstname_line[81];
      char lastname_line[81];
      double newGPA;
      int newID;
      cout << endl << "------ADDING STUDENT------" << endl;
      cout << "First Name: ";
      cin.getline(firstname_line, 81);
      strcpy(s->name_first, firstname_line);
      cout << "Last Name: ";
      cin.getline(lastname_line, 81);
      strcpy(s->name_last, lastname_line);
      s->gpa = getInt("GPA: ");
      s->id = getInt("ID: ");
      while(!validId(s->id, hashTable, tablesize)){
        cout << "that ID is in use. Please use another ID." << endl;
        s->id = getInt("ID: ");
      }
      addStudent(hashTable, s, tablesize);
      cout << "-----ADDED SUCCESSFULLY-----" << endl << endl;
    }
    else if(strcmp(input, "print") == 0){
      printTable(hashTable, tablesize);
    }
    else if(strcmp(input, "delete") == 0){

    }
    else if(strcmp(input, "generate") == 0){
      int numStudents = getInt("How many students to generate? : ");
      char firstname_line[81];
      char lastname_line[81];
      int numFirstNames = 0;
      int numLastNames = 0;
      int randomFirst = 0;
      int randomLast = 0;
      double randomGPA = 0;
      fstream firstname_file("firstnames.txt");
      if (firstname_file.is_open()){
        //find the number of lines in the file
        while(firstname_file.getline(firstname_line, 80)){
          numFirstNames++;
        }
        firstname_file.close();
      }
      //tell the user if file does not exist
      else{
        cout << "firstnames.txt does not exist.\n\n";
        continue;
      }

      fstream lastname_file("lastnames.txt");
      if (lastname_file.is_open()){
        //find the number of lines in the file
        while(lastname_file.getline(lastname_line, 80)){
          numLastNames++;
        }
        lastname_file.close();
      }
      //tell the user if file does not exist
      else{
        cout << "lastnames.txt does not exist.\n\n";
        continue;
      }
      cout << numFirstNames << endl;
      cout << numLastNames << endl;
      //get the random name
      for(int i = 0; i < numStudents; i++){
        randomFirst = rand() % numFirstNames + 1;
        randomLast = rand() % numLastNames + 1;
        cout << randomFirst << endl;
        cout << randomLast << endl;
        //get the random first name
        fstream firstname_file("firstnames.txt");
        if (firstname_file.is_open()){
          for(int a = 0; a < randomFirst; a++){
            firstname_file.getline(firstname_line, 80);
          }
          firstname_file.close();
        }
        //tell the user if file does not exist
        else{
          cout << "firstnames.txt does not exist.\n\n";
          continue;
        }
        //get the random last name
        fstream lastname_file("lastnames.txt");
        if (lastname_file.is_open()){
          for(int b = 0; b < randomLast; b++){
            lastname_file.getline(lastname_line, 80);
          }
          lastname_file.close();
        }
        //tell the user if file does not exist
        else{
          cout << "lastnames.txt does not exist.\n\n";
          continue;
        }
        randomGPA = rand() % 5 + 1 - (double(rand() % 10))/10 - (double(rand() % 10))/100;
        cout << firstname_line << " " << lastname_line << " " << randomGPA << endl;
        Student* s = new Student();
        strcpy(s->name_first,firstname_line);
        strcpy(s->name_last,lastname_line);
        s->gpa = randomGPA;
        while(!validId(current_id, hashTable, tablesize)){
          current_id++;
        }
        s->id = current_id;
        current_id++;
        addStudent(hashTable, s, tablesize);
      }
    }
  }

  return 0;
}

void addStudent(StudentNode** hashTable, Student* s, int tablesize){
  int index = hashFunction(s->id, tablesize);
  StudentNode* newNode = new StudentNode(s);
  if(hashTable[index] == NULL){
    hashTable[index] = newNode;
  }
  else{
    int collisions = 1;
    StudentNode* current = hashTable[index];
    while(current->getNext() != NULL){
      current = current->getNext();
      collisions++;
    }
    current->setNext(newNode);
  }
}

int hashFunction(int id, int arr_size){
  return id % arr_size;
}

bool validId(int id, StudentNode** hashTable, int tablesize){
  int index = hashFunction(id, tablesize);
  if(hashTable[index] == NULL){
    return true;
  }
  else{
    StudentNode* current = hashTable[index];
    while(current != NULL){
      if(current->getStudent()->id == id){
        return false;
      }
      current = current->getNext();
    }
    return true;
  }
}

void printTable(StudentNode** hashTable, int tablesize){
  cout << "-----PRINTING HASH TABLE-----" << endl;
  for(int i = 0; i < tablesize; i++){
    StudentNode* current = hashTable[i];
    while(current != NULL){
      Student* s = current->getStudent();
      cout << "[Table Index:" << i << "] Name: " << s->name_first << " " << s->name_last << " GPA: " << s->gpa << " Id: " << s->id << endl;
      current = current->getNext();
    }
  }
  cout << "-----------------------------" << endl;
}

//stores user input into a char*
void getInput(char* input){
  fill(input, input + sizeof(input), ' ');
  cin.getline(input, INPUT_SIZE);
  trimWhitespace(input);
}

//remove extra whitespaces to make sure input is compared as intended
void trimWhitespace(char* text){
  char* newText = text;
  char lastChar = ' ';
  while(*text != '\0'){
    if(!(*text == ' ' && lastChar == ' ')){
      *newText = *text;
      lastChar = *text;
      newText++;
    }
    text++;
  }
  if(*(newText-1) != ' '){
    *newText = '\0';
  }
  else{
    *(newText-1) = '\0';
  }
}

//prompts the user for an integer
int getInt(char* message){
  int number;
  bool valid = false;
  while (!valid){
    cout << message;
    cin >> number;
    //delete excess whitespace
    while (cin.peek() == ' '){
      cin.ignore(1);
    }
    if(cin.peek() != '\n'){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else{
      valid = true;
    }
  }
  cin.ignore(81, '\n');
  return number;
}
