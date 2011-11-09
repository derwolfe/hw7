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
 * that is the convention for the lab
 */
template<class T>
bool Linked_List:append(const T* item) 
{
  if (is_empty()) {
    Node* first = new Node<T>;
    first->item = item;


    
#endif

