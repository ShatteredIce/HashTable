//Header file for StudentStudentNode.cpp
//StudentNode for linked lists of Student class
//Stores values: next StudentNode* and stored Student*

#include <iostream>

using namespace std;

struct Student{
  char name_first[81];
  char name_last[81];
  int id;
  double gpa;
};

class StudentNode {
public:
  StudentNode(Student*);
  ~StudentNode();
  StudentNode* getNext();
  void setNext(StudentNode*);
  Student* getStudent();
 protected:
  Student* student;
  StudentNode* next;
};
