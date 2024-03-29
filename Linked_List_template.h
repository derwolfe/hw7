#ifndef LIST_H
#define LIST_H

#include <iostream>

#include "List_out_of_index_exception.h"

using namespace std;

template <class T>
class Linked_List
{
 private:
  /*
   * Template class for node. Struct instead of class because
   * it only holds data, nothing more. Class could be used, but 
   * struct works.
   */
  struct Node
  {
    T*    item;
    Node* next;
  };
  /* 
   * Length of the linked list
  */

  Node*  head;
  Node*  tail;
  int    size;
 
 public:
  Linked_List(); // do you need a copy constructor?
  ~Linked_List();

  int       get_size() const;
  bool      is_empty() const;
  void      print(std::ostream& os);
  bool      remove(int index);
  bool      append(T* item);
  Node*     find(int index) const; //retrieve at index, or item?
  T*        retrieve(int index) const;
 // following used in testing 
  void      tprint();
};

/*
 * IMPLEMENT ME
 */
/*
 * Please implement the ADT methods and functions in the following
 * order as an aid to more accurate and efficient grading of the
 * assignment.
 *
 * Linked_List()
 * ~Linked_List()
 * print()
 * is_empty()
 * get_size()
 * insert()
 * append()
 * find()
 * remove()
 * retrieve()
 */
/* 
 * WORKING - constructor
 */
template <class T>
Linked_List<T>::Linked_List ()
{
  size = 0;
  head = NULL;
  tail = NULL;
}

/* WORKING -
 * destructor calls remove at index
 */
template<class T>
Linked_List<T>::~Linked_List()
{
  while(!is_empty()) {
    remove(1);
  }
}

/* WORKING print */
template<class T>
void Linked_List<T>::print(std::ostream& os)
{
  Node* cur = head;
  while (cur != NULL) {
    os << *cur->item << endl;
    cur = cur->next;
  }
}
/* WORKING test print method */
template<class T>
void Linked_List<T>::tprint()
{
  Node* cur = head;
  while (cur != NULL) {
    cout << *cur->item << endl;
    cur = cur->next;
  }
}

/* Working - size test */
template<class T>
bool Linked_List<T>::is_empty() const
{
  if (size == 0) {
    return true;
  } // if size > 0 return false
  return false;
}

/* Working - size getter */
template<class T>
int Linked_List<T>::get_size() const
{
  return size;
}

/* WORKING!
 * since this is a list we are going to append to the end
 * that is the convention for the lab. You do have a tail pointer, use it
 *
 * The list will contain pointers to the item, not the item it self. .
 */
template<class T>
bool Linked_List<T>::append(T *item) 
{
  /* allocate mem for a new node, since this will be the tail node
   * set its next pointer to NULL, set its item pointer to item.
   * increment size.
   */
  Node* last_node = new Node;
  /* check to make sure memory has been allocated
   */
  if (last_node == NULL) {
    return false; //mem alloc has failed
  }
  last_node->next = NULL; 
  last_node->item = item; //make sure this is a pointer
  /* 
   * If the list is empty, just add the node.
   */
  if (is_empty()) {
    last_node->next = NULL;
    head            = last_node;
    tail            = last_node;
    ++size;
    return true;
  /* 
   * Non-empty list, add nodes to end by convention (and definition of append)
   */
  } else { 
    Node* temp  = tail;
    temp->next  = last_node;
    tail        = last_node;
    temp        = NULL;   // do i need to set to null. clear pointer?
    ++size; 
    return true;
  }
}

/* WORKING - find item at any given index.
 * there is a problem returning a NULL pointer. The template doesn't like it. 
 * I could try throwing an exception.
 * */
template<class T>
typename Linked_List<T>::Node* Linked_List<T>::find(int index) const
{
  Node* target = head;
  int inc = 1;
  if (index > size) {
    throw List_out_of_index_exception
      ("List_out_of_index_exception: Index must be greater than 0 and less than size");
  } else if (index == 1) {
    return head; //already a pointer, ok
  } else {
    while (inc < index) {
      target = target->next;
      ++inc;
    }
    // it is iterating over the list one item too far.
    return target;
  }
}

/* WORKING remove 
 */
template<class T>
bool Linked_List<T>::remove(int index)
{
  Node* target = head;
  Node* prev = head;
  int inc = 0;
  // 3 conditions: either the head, the tail, or the a middle node is
  // slated for deletion.
  // 1. delete the head:
  // WORKING
  if (index == 1) {
    head = head->next;
    delete target;
    target = NULL;
    --size;
    return true;
  
  } else if (index == size) {
    while (inc <= size) { //again, finds previous node to tail
      prev = target->next;
     ++inc;
    }
    delete tail;
    tail = prev->next;
    tail->next = NULL;
    --size; 
    return true;
    
    /* WORKING, skipping over by one\
     * 2. Delete a central node. I made a work around, I think I have lost
     * track of something somewhere in this chunk.
     */
  
  } else if ((index > 1) && (index < size)) {
    inc = 1;
    if (inc != (index - 1)) {
      while (inc < (index - 1)) { 
        // less will give the node preceding the target for deletion
        prev = target->next;
        ++inc;
      }
    }
    target = prev->next;
    prev->next = prev->next->next;
    delete target;
    target = NULL;
    prev = NULL;
    --size;
    return true;
  } else { // handles indexes that are out of bounds
    return false;
  }
} 
  
template<class T>
T* Linked_List<T>::retrieve (int index) const
{
  /* 
   * find() will deal with an index that cannot be found.
   */
  Node* target = find(index);
  return target->item;
}

#endif

