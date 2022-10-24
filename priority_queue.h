// =================================================================
//
// File: priority_queue.h
// Author: Arturo Díaz
// Date: 22/10/2022
//
// =================================================================

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <sstream>
#include <string>
#include "header.h"

// =================================================================
// Definition of the PriorityQueue class.
// =================================================================

template <class T>
class PriorityQueue{
private:
  T *queue;
  int size;

public:
  PriorityQueue();

  int parentIndex(int) const;
  int rightIndex(int) const;
  int leftIndex(int) const;

  int top() const;
  void push(int);
  void pop();
  bool empty() const;
  int getSize() const;

  void print() const;
  std::string toString() const;
};

template <class T>
PriorityQueue<T>::PriorityQueue(){
  queue = new int[100];
  size = 0;
}

// =================================================================
// Returns current index of parent node.
// @param val, int index of current node.
// =================================================================

template <class T>
int PriorityQueue<T>::parentIndex(int i) const{
  return (i - 1) / 2;
}

// =================================================================
// Returns current index of right node.
// @param val, int index of current node.
// =================================================================

template <class T>
int PriorityQueue<T>::rightIndex(int i) const{
  return ((i * 2) + 2);
}

// =================================================================
// Returns current index of left node.
// @param val, int index of current node.
// =================================================================

template <class T>
int PriorityQueue<T>::leftIndex(int i) const{
  return ((i * 2) + 1);
}

// =================================================================
// Pushes value to queue. Adds new value and positions it at the right place.
// @param val, int value to add.
// @returns void.
// =================================================================

template <class T>
void PriorityQueue<T>::push(int value){
  if (empty()){
    queue[0] = value;
    this->size += 1;
  }
  else{
    queue[this->size] = value;
    int i = this->size;
    while (i > 0 && this->queue[parentIndex(i)] <= this->queue[i]){
      swap(queue[parentIndex(i)], queue[i]);
      i = parentIndex(i);
    }
    this->size += 1;
  }
}

// =================================================================
// Pops value from queue. Deletes value with highest priority and positions new top at the right place.
// @param val, none.
// @returns void.
// =================================================================

template <class T>
void PriorityQueue<T>::pop(){
  int aux;
  for (int i = 0; i < this->size; i++){
    this->queue[i] = this->queue[i + 1];
  }
  this->queue[size - 1].~T();
  this->size--;

  int i = 0;
  while (i < this->size && this->queue[parentIndex(i)] < this->queue[leftIndex(i)] || this->queue[parentIndex(i)] < this->queue[rightIndex(i)]){
    if (this->queue[parentIndex(i)] < this->queue[leftIndex(i)]){
      swap(this->queue[parentIndex(i)], this->queue[leftIndex(i)]);
      i = leftIndex(i);
    }
    else{
      swap(this->queue[parentIndex(i)], this->queue[rightIndex(i)]);
      i = rightIndex(i);
    }
  }
}

// =================================================================
// Gets top. Value with highest priority (Max Heap Tree).
// @param val, none.
// @returns value with the highest priority.
// =================================================================

template <class T>
int PriorityQueue<T>::top() const{
  if (empty()){
    return -1;
  }
  return this->queue[0];
}

// =================================================================
// Checks if priority queue is empty or not.
// @param val, none.
// @returns true if size < 0.
// =================================================================

template <class T>
bool PriorityQueue<T>::empty() const{
  return (size < 1);
}

// =================================================================
// Gets size of priority queue.
// @param val, none.
// @returns queue size.
// =================================================================

template <class T>
int PriorityQueue<T>::getSize() const{
  return this->size;
}

// =================================================================
// Prints all values.
// @param val, none.
// @returns void.
// =================================================================

template <class T>
void PriorityQueue<T>::print() const{
  for (int i = 0; i < this->size; i++){
    std::cout << this->queue[i] << " ";
  }
}

// =================================================================
// String representation of the elements in the list.
//
// @returns a string containing all the elements of the list.
// =================================================================

template <class T>
std::string PriorityQueue<T>::toString() const{
  std::stringstream aux;
  aux << "[";
  for (int i = 0; i < this->size; i++){
    aux << this->queue[i];
    if (i < size - 1){
      aux << ", ";
    }
  }
  aux << "]";
  return aux.str();
}

#endif /* PriorityQueue_H */