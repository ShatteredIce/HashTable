//StudentNode class for HashTable

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

//returns the pointer to the next node
StudentNode* StudentNode::getNext(){
  return next;
}

//sets the pointer to the next node
void StudentNode::setNext(StudentNode* newNext){
  next = newNext;
}

//returns the student struct
Student* StudentNode::getStudent(){
  return student;
}
