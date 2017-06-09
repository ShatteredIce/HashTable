//C++ Project 14 - HashTable - 6/1/17
//Stores a student list using a hash table

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <fstream>
#include <vector>
#include <iomanip>
#include "StudentNode.h"

using namespace std;

//prototypes
void getInput(char* input);
void trimWhitespace(char* text);
int getInt(char* message);
double getDouble(char* message);
int addStudent(StudentNode** hashTable, Student* s, int tablesize);
void printTable(StudentNode** hashTable, int tablesize);
int hashFunction(int id, int arr_size);
bool validId(int id, StudentNode** hashTable, int tablesize);
void searchTable(int id, StudentNode** hashTable, int tablesize);
bool deleteStudent(int id, StudentNode** hashTable, int tablesize);
bool resizeTable(StudentNode** & hashTable, int tablesize);

const int INPUT_SIZE = 201;

int main(){

  srand(time(NULL));

  char input[INPUT_SIZE];
  int current_id = 1;
  int totalStudents = 0;

  //set up the hashtable
  int tablesize = 100;
  StudentNode** hashTable = new StudentNode* [tablesize];

  for(int i = 0; i < tablesize; i++){
    hashTable[i] = NULL;
  }

  cout << "\n-----Hash Table v1.0-----\n";
  cout << "Creates a hash table to store a list of students\n";
  cout << "Availible commands are: 'add', 'print', 'search', 'delete', 'generate', and 'quit'.\n";
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
    //if input = add, then prompt the user for student values and add a student
    else if(strcmp(input, "add") == 0){
      Student* s = new Student();
      char firstname_line[81];
      char lastname_line[81];
      double newGPA;
      int newID;
      //student values
      cout << endl << "------ADDING STUDENT------" << endl;
      cout << "First Name: ";
      cin.getline(firstname_line, 81);
      strcpy(s->name_first, firstname_line);
      cout << "Last Name: ";
      cin.getline(lastname_line, 81);
      strcpy(s->name_last, lastname_line);
      s->gpa = getDouble("GPA: ");
      s->id = getInt("ID: ");
      while(!validId(s->id, hashTable, tablesize)){
        cout << "That ID is in use. Please use another ID." << endl;
        s->id = getInt("ID: ");
      }
      totalStudents++;
      //test for resize
      if((addStudent(hashTable, s, tablesize) > 3)){
        resizeTable(hashTable, tablesize);
        tablesize *= 2;
        cout << "<Table has been resized to " << tablesize << " slots>" << endl;
      }
      cout << "-----ADDED SUCCESSFULLY-----" << endl << endl;
    }
    //if input = print, print out all the students to the console
    else if(strcmp(input, "print") == 0){
      cout << "\n-----PRINTING HASH TABLE-----" << endl;
      printTable(hashTable, tablesize);
      cout << "-----------------------------" << endl;
    }
    //if input = search, search for students in the console
    else if(strcmp(input, "search") == 0){
      cout << "\n-----SEARCHING HASH TABLE-----" << endl;
      int existingId = getInt("Search for existing ID: ");
      searchTable(existingId, hashTable, tablesize);
      cout << "-----------------------------\n" << endl;
    }
    //if input = delete, attempt to delete a student
    else if(strcmp(input, "delete") == 0){
      cout << "\n-----DELETING STUDENT-----" << endl;
      int deleteId = getInt("Delete student with ID: ");
      if(deleteStudent(deleteId, hashTable, tablesize)){
        totalStudents--;
      }
      cout << "-----------------------------\n" << endl;
    }
    //if input = generate, generate students from the firstname and lastname files
    else if(strcmp(input, "generate") == 0){
      cout << "\n-----GENERATING STUDENTS-----" << endl;
      int numStudents = getInt("How many students to generate? : ");
      totalStudents += numStudents;
      cout << endl;
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
      //cout << numFirstNames << endl;
      //cout << numLastNames << endl;
      //get the random name
      for(int i = 0; i < numStudents; i++){
        randomFirst = rand() % numFirstNames + 1;
        randomLast = rand() % numLastNames + 1;
        //cout << randomFirst << endl;
        //cout << randomLast << endl;
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
        //generate random gpa
        randomGPA = rand() % 5 + 1 - (double(rand() % 10))/10 - (double(rand() % 10))/100;
        Student* s = new Student();
        strcpy(s->name_first,firstname_line);
        strcpy(s->name_last,lastname_line);
        s->gpa = randomGPA;
        //check to see if id is valid
        while(!validId(current_id, hashTable, tablesize)){
          current_id++;
        }
        s->id = current_id;
        cout << "Generated Student: " << firstname_line << " " << lastname_line << " GPA: " << randomGPA <<  " ID: " << current_id << endl;
        current_id++;
        //check for resizing
        if((addStudent(hashTable, s, tablesize) > 3)){
          resizeTable(hashTable, tablesize);
          tablesize *= 2;
          cout << "<Table has been resized to " << tablesize << " slots>" << endl;
        }
      }
      cout << "\n-----------------------------\n" << endl;
    }
  }

  return 0;
}

//add a student to the hash table, returns number of students in the index that the student was added in
int addStudent(StudentNode** hashTable, Student* s, int tablesize){
  int index = hashFunction(s->id, tablesize);
  StudentNode* newNode = new StudentNode(s);
  if(hashTable[index] == NULL){
    hashTable[index] = newNode;
    return 1;
  }
  else{
    int collisions = 2;
    StudentNode* current = hashTable[index];
    //iterate through collision
    while(current->getNext() != NULL){
      current = current->getNext();
      collisions++;
    }
    current->setNext(newNode);
    return collisions;
  }
}

//the hash function, takes the modulus of the id and the array size
int hashFunction(int id, int arr_size){
  return id % arr_size;
}

//checks if an id is valid (if it is not being used by a student in the hashtable)
bool validId(int id, StudentNode** hashTable, int tablesize){
  int index = hashFunction(id, tablesize);
  if(hashTable[index] == NULL){
    return true;
  }
  else{
    StudentNode* current = hashTable[index];
    //iterates through collisions
    while(current != NULL){
      if(current->getStudent()->id == id){
        return false;
      }
      current = current->getNext();
    }
    return true;
  }
}

//prints out the hash table to the console
void printTable(StudentNode** hashTable, int tablesize){
  for(int i = 0; i < tablesize; i++){
    StudentNode* current = hashTable[i];
    while(current != NULL){
      Student* s = current->getStudent();
      cout << setprecision(2) << fixed;
      cout << "[Table Index:" << i << "] Name: " << s->name_first << " " << s->name_last << " GPA: " << s->gpa << " Id: " << s->id << endl;
      current = current->getNext();
    }
  }
}

//searches for a student in the hashtable
void searchTable(int id, StudentNode** hashTable, int tablesize){
  //if the id is not valid for a new student, then student is in the list
  if(!validId(id, hashTable, tablesize)){
    int index = hashFunction(id, tablesize);
    StudentNode* current = hashTable[index];
    //iterate through collisions
    while(current != NULL){
      Student* s = current->getStudent();
      if(s->id == id){
        cout << "<Student Found>" << endl;
        cout << "[Table Index:" << index << "] Name: " << s->name_first << " " << s->name_last << " GPA: " << s->gpa << " Id: " << s->id << endl;
        break;
      }
      current = current->getNext();
    }
  }
  //tells the user if no student was found
  else{
    cout << "No Student Found." << endl;
  }
}

//delets a student from the hash table
bool deleteStudent(int id, StudentNode** hashTable, int tablesize){
  //if the id is not valid for a new student, then student is in the list
  if(!validId(id, hashTable, tablesize)){
    int index = hashFunction(id, tablesize);
    StudentNode* current = hashTable[index];
    Student* s = current->getStudent();
    //student is in the first position in the hashtable
    if(s->id == id){
      cout << "Deleted Student: " << s->name_first << " " << s->name_last << endl;
      StudentNode* next = current->getNext();
      delete current;
      hashTable[index] = next;
    }
    //student is not the first position in the hashtable
    else{
      while(current->getNext() != NULL){
        s = current->getNext()->getStudent();
        if(s->id == id){
          cout << "Deleted Student: " << s->name_first << " " << s->name_last << endl;
          StudentNode* next = current->getNext()->getNext();
          delete current->getNext();
          current->setNext(next);
          break;
        }
        current = current->getNext();
      }
    }
    return true;
  }
  else{
    cout << "No Student Found." << endl;
    return false;
  }
}

//resizes the hash table, returns if another resize is required
bool resizeTable(StudentNode** & hashTable, int tablesize){
  //creates the new table
  bool resizeAgain = false;
  StudentNode** newTable = new StudentNode* [tablesize*2];
  for(int i = 0; i < tablesize*2; i++){
    newTable[i] = NULL;
  }
  //add the students from the old table to the new table
  for(int i = 0; i < tablesize; i++){
    StudentNode* current = hashTable[i];
    while(current != NULL){
      Student* s = current->getStudent();
      if(addStudent(newTable, s, tablesize*2)){
        resizeAgain = true;
      }
      current = current->getNext();
    }
  }
  //delete old table
  delete[] hashTable;
  hashTable = newTable;
  return resizeAgain;
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

//prompts the user for an double
double getDouble(char* message){
  double number;
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
