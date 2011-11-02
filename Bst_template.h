#ifndef BST_H
#define BST_H

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * IMPLEMENT ME
 */
class Bst
{
 private:

  /*
   * IMPLEMENT ME
   */
  struct Tree_node {
  public:
    Tree_node* left;
    Tree_node* right;
    string key;
    /*
     * IMPLEMENT ME
     */
  };

  /*
   * IMPLEMENT ME
   */

 public:
  Bst();
  ~Bst();
  
  bool isEmpty() const;

  void remove(string key);
  void print_inorder(ostream &os);
  void print_preorder(ostream &os);
  void print_postorder(ostream &os);

  /*
   * IMPLEMENT ME
   */

 private:
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
 * Bst()
 * ~Bst()
 * isEmpty()
 * insert()
 * search()
 * searchNode()
 * deleteNodeItem()
 * processLeftMost()
 * remove()
 * print_inorder()
 * inorder()
 * print_preorder()
 * preorder()
 * print_postorder()
 * postorder()
 */

#endif
