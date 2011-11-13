#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

;

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

  int        get_size() const;
  bool       is_empty() const;
  void       print(std::ostream& os);
  void       remove(int index);
  bool       append(T* item);
  T*         retrieve(int index) const; //retrieve at index, or item?
  
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
/* default constructor
 */
template <class T>
Linked_List<T>::Linked_List ()
{
  size = 0;
  head = NULL;
  tail = NULL;
}

/* destructor calls remove at index
 */
//template<class T>
//Linked_List<T>::~Linked_List()
//{
//  while(!is_empty()) {
//    remove(1);
//  }
//}
//
///* printing the items -- what method do I call? Do you require all
// * users of the template to adhere to get_name??
// */
//template<class T>
//void Linked_List::print(std::ostream& os)
//{
//  Node* cur = head;
//  while (cur != NULL) {
//    os << cur->item->get_title();
//  }
//}
//
template<class T>
bool Linked_List<T>::is_empty() const
{
  if (size == 0) {
    return true;
  } // if size > 0 return false
  return false;
}
//
template<class T>
int Linked_List<T>::get_size() const
{
  return size;
}

/* 
 * since this is a list we are going to append to the end
 * that is the convention for the lab. You do have a tail pointer, use it.
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
    size++;
    return true;
  /* 
   * Non-empty list, add nodes to end by convention (and definition of append)
   */
  } else { 
    Node* temp  = tail;
    temp->next  = last_node;
    tail        = last_node;
    temp        = NULL;   // do i need to set to null. clear pointer?
    size++; 
    return true;
  }
}

/* how are you going to implement this? Your program is going to
 * use nodes, nodes that always have some sort of pointer to more
 * data. 
 */
//template<class T>
//Node* Linked_List::find(string item) const
//{
//  Node* target = head;
//  int inc = 1;
//  while (inc <= (size + 1)) {
//    if (inc == (size + 1)) {
//      return NULL;
//    } else if (target->T->get_name() == item ) { // is this wrong?
//      return target;
//    } else {
//      target = target->next;
//      inc++;
//    }
//  }
//}
//
///* remove - think of scratching an item off of a list, any item
// * can be removed, so you'll move some pointers around. Are we 
// * removing by index or by track?
// */
//template<class T>
//bool Linked_List::remove(int index)
//{
//  Node* target = head;
//  Node* tmp = target;
//  
//  if (index < 0) {
//    return false;
//  }
//  /* three conditions, head, middle area, tail
//   */
//  int inc = 0
//  if (index == 0) { // covers head
//    target = head;
//    head = head->next;
//    // what about tail?
//    delete target;
//    target = NULL;
//    return true;
//  } else if (get_size() < index) {
//    // if index == 0, first test will catch this             
//    while (inc < (index - 1)) { 
//      //covers middle cases. It should select the node previous
//      //to the node we want to delete, then set its next pointer
//      //to the node following what we want to delete. 
//      //
//      //Also neither node is the head or the tail.
//      target = target->next;
//      inc++;
//    }
//    tmp = target->next; //target next is the node are deleting!
//    target->next = target->next->next;
//    delete tmp;
//    target = NULL;
//    tmp = NULL;
//  } else { // delete the tail node
//    target = tail;
//    tmp = head;
//    while (inc < (index - 1)) {
//      tmp = tmp->next;
//      inc++;
//    } 
//    tmp->next = NULL;
//    delete target;
//    target = NULL;
//    tail = tmp;
//    tmp = NULL; // may be unnecessary
//  }
//}
//
//template<class T>
//T Linked_List::retrieve (string name) const
//{
//  Node* found = find(name);
//  if (found == NULL){
//    return NULL;
//  } else {
//    return found->item;//should return item or pointer to item.
//  }
//}

#endif

