#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

/*
 * IMPLEMENT ME
 */
class Linked_List
{
 private:
  /*
   * IMPLEMENT ME
   */
    struct Node
    {
      Node* next;
      /*
       * IMPLEMENT ME
       */
    };

  int   size;

  /*
   * IMPLEMENT ME
   */

 public:
  Linked_List();
  ~Linked_List();

  int        get_size();
  bool       is_empty();
  void       print(std::ostream& os);
  void       remove(int index);

  /*
   * IMPLEMENT ME
   */
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

#endif

