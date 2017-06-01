//C++ Project 14 - HashTable - 6/1/17
//Stores a student list using a hash table

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <fstream>
#include <vector>

using namespace std;

//Student variables
struct Student {
  char nameFirst[81];
  char nameLast[81];
  int id;
  float gpa;
};

//prototypes
void getInput(char* input);
void trimWhitespace(char* text);
int getInt(char* message);

const int INPUT_SIZE = 201;

int main(){

  srand(time(NULL));

  char input[INPUT_SIZE];
  int id = 1;

  cout << "\n-----Hash Table v1.0-----\n";
  cout << "Creates a hash table to store a list of students\n";
  cout << "Availible commands are: 'add', 'print', 'delete', 'generate', and 'quit'.\n";
  cout << "C++ Project 14 - Nathan Purwosumarto\n\n";

  while(true){
    cout << "Awaiting input: ";
    getInput(input);
    //if input = quit, then end the program
    if(strcmp(input, "quit") == 0){
      cout << "Program Terminated." << endl;
      break;
    }
    else if(strcmp(input, "generate") == 0){
      int numStudents = getInt("How many students to generate? : ");
      char firstname_line[81];
      char lastname_line[81];
      int numFirstNames = 0;
      int numLastNames = 0;
      int randomFirst = 0;
      int randomLast = 0;
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
        //if file is found, copy contents into lastname vector
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
      for(int i = 0; i < numStudents; i++){
        randomFirst = rand() % numFirstNames;
        randomLast = rand() % numLastNames;
        cout << randomFirst << endl;
        cout << randomLast << endl;
      }
      cin.ignore(81, '\n');
    }
  }

  return 0;
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
  return number;
}
