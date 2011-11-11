#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

/*
 * IMPLEMENT ME
 */
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
  int   size;
  Node* head;
  Node* tail;
  Node* find;

 public:
  Linked_List(); // do you need a copy constructor?
  ~Linked_List();

  int        get_size();
  bool       is_empty() const;
  void       print(std::ostream& os);
  void       remove(int index);
  T          append(const T& item);
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
template<class T>
Linked_List::~Linked_List()
{
  while(!is_empty()) {
    remove(1);
  }
}

/* printing the items -- what method do I call? Do you require all
 * users of the template to adhere to get_name??
 */
template<class T>
void Linked_List::print(std::ostream& os)
{
  Node* cur = head;
  while (cur != NULL) {
    os << cur->item->get_title();
  }
}

template<class T>
bool Linked_List::is_empty() const
{
  if (size == 0) {
    return true;
  } // if size > 0 return false
  return false;
}

/* 
 * since this is a list we are going to append to the end
 * that is the convention for the lab. You do have a tail pointer, use it.
 */
template<class T>
bool Linked_List:append(const T* item) 
{
  /* allocate mem for a new node, since this will be the tail node
   * set its next pointer to NULL, set its item pointer to item.
   * increment size.
   */
  Node* last_node = new Node<T>;
  /* check to make sure memory has been allocated
   */
  if (last_node == NULL) {
    return false;
  }
  last_node->next = NULL; 
  last_node->item = item;
  size++;
  /* 
   * If the list is empty, just add the node.
   */
  if (is_empty()) {
    last_node->item = item;
    last_node->next = NULL;
    head            = last_node;
    tail            = last_node;
    return true;
  /* 
   * Non-empty list, add nodes to end by convention (and definition of append)
   */
  } else { 
    Node* temp  = tail;
    temp->next  = last_node;
    tail        = last_node;
    temp        = NULL;   // do i need to set to null. clear pointer?
    return true;
  }
}
    
    
#endif

