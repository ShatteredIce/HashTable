//StudentStudentNode class for HashTable

#include <iostream>
#include "StudentNode.h"

using namespace std;

//Constructor: stores a Student*, sets next to NULL
StudentNode::StudentNode(Student* newStudent){
  student = newStudent;
  next = NULL;
}

//Deconstructor: deletes Student*, sets next to NULL
StudentNode::~StudentNode(){
  delete student;
  next = NULL;
}

StudentNode* StudentNode::getNext(){
  return next;
}

void StudentNode::setNext(StudentNode* newNext){
  next = newNext;
}

Student* StudentNode::getStudent(){
  return student;
}
