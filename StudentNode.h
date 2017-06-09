//Header file for StudentStudentNode.cpp
//StudentNode for linked lists of Student class
//Stores values: next StudentNode* and stored Student*

#include <iostream>

using namespace std;

//student data values 
struct Student{
  char name_first[81];
  char name_last[81];
  int id;
  double gpa;
};

class StudentNode {
public:
  StudentNode(Student*); //Constructor: stores a Student*, sets next to NULL
  ~StudentNode(); //Deconstructor: deletes Student*, sets next to NULL
  StudentNode* getNext(); //returns the pointer to the next node
  void setNext(StudentNode*); //sets the pointer to the next node
  Student* getStudent(); //returns the student struct
 protected:
  Student* student;
  StudentNode* next;
};
