#ifndef BST_H
#define BST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
/* 
 * What should the key be? How do you want to initialize the tree?
 */

using namespace std;

template <class T>
class Bst
{
 public:
  struct Tree_node {
  /* structs are inherently public, 
   * why hide it if you want to be public?
   */
    Tree_node*    left;
    Tree_node*    right;
    std::string   key;
    T*            item;
  };
// this is where the struct WAS
  private:
    Tree_node*  root;
    int size;

 public:
  Bst();
  ~Bst();
  
  bool        is_empty() const;
  /* new operations*/
  void        insert(std::string key, T* item);
  T*          search(std::string key);
  Tree_node*  search_node(std::string key, Tree_node* leaf);
  bool        delete_node_item(Tree_node* &target);
  void        process_left_most(Tree_node* &node, T* &data);
  
  /* These just traverse the tree!*/
  void  inorder(Tree_node* root, std::ostream &os);
  void  preorder(Tree_node* root, std::ostream &os);
  void  postorder(Tree_node* root, std::ostream &os);
  
  //test
  void  test();
  void  test_print(Tree_node* head);
    
  void  remove(std::string key);
  void  print_inorder(std::ostream &os);
  void  print_preorder(std::ostream &os);
  void  print_postorder(std::ostream &os);
  
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
 * is_empty()
 * insert()
 * search()
 * search_node()
 * delete_node_item()
 * process_left_most()
 * remove()
 * print_inorder()
 * inorder()
 * print_preorder()
 * preorder()
 * print_postorder()
 * postorder()
 */

template<class T>
Bst<T>::Bst()
{
  root = NULL;
  size = 0;
}

/* Should I remove by key or by root? */
template<class T>
Bst<T>::~Bst()
{
  while (root != NULL) {
    delete_node_item(root);
  }
}

/* Checks if the tree is empty */
template<class T>
bool Bst<T>::is_empty() const
{
  if (size == 0) {
    return true;
  } 
  return false;
}

/* 
 * Insert 
 * The std::string of either the title or artist will be the key, but you still must
 * ADD the item to the tree. 
 *
 * The provided key will determine how the BST is sorted, i.e. if you want it
 * to be keyed by artist, when you call this function use get_track_title() for
 * title, etc.
 *
 * Parents are taken care of by using a current pointer.
 *  */
template<class T>
void Bst<T>::insert(std::string key, T* item)
{
// somewhere a problem is insert  
  Tree_node* leaf = new Tree_node;
  leaf->key       = key; 
  leaf->item      = item;
  leaf->right     = NULL;
  leaf->left      = NULL;
  if (root == NULL) {
    root = leaf;
    size = 1;
    return;
  } else { // if (root != NULL)
    Tree_node* current  = root;
    ++size;
    while (current != NULL) {
        // go LEFT
     // cout << "left = -1, right = >= 0)" << key.compare(current->key) << endl;
      if (key.compare(current->key) < 0) {
        if (current->left == NULL) {
          current->left = leaf;
          return;
        } else { 
          current = current->left;
        }
      } // go RIGHT
      else if (key.compare(current->key) >= 0) {
        if (current->right == NULL) {
          current->right = leaf;
          return;
        } else {
          current = current->right;
        }
      } 
    }
  }
}



/* Search_node
 * Pass in the root node as the first leaf, then move on from there
 * 4 cases
 *  1) object's key  == first node key
 *  2) object's key  > ""
 *  3) object's key  < ""
 *  4) object's key not found.
 */
template<class T>
typename Bst<T>::Tree_node* Bst<T>::search_node(std::string key, Tree_node* leaf)
{
  if (key.compare(leaf->key) == 0) {
    return leaf;
  } else if (key.compare(leaf->key) < 0) {
    if (leaf->left != NULL) {
      return search_node(key, leaf->left);
    }
  } else if (key.compare(leaf->key) > 0) {
    if (leaf->right != NULL) {
      return search_node(key, leaf->right);
    }
  } else { // key not found
    return NULL; // could be a problem, may need to throw exception!
  }
}

/* 
 * Search - this will be the operation called by the user. Search_node will be
 * called by search.
 */
template<class T>
T* Bst<T>::search(std::string key)
{
  Tree_node* found = search_node(key, root);
  if (found == NULL) {
    return NULL; //or throw exception.
  }
  return found->item;
}

/* delete_node_item - will be called by remove.
 *
 * 4 cases
 * -------
 * 1) Node has no children
 * 2) Node has only a right subtree, move up the right subtree.
 * 3) Node has only a left subtree, move up the left subtree.
 * 4) Node has BOTH left and right subtrees. Replace the data element 
 *    of the current tree with the data element from the left most 
 *    element of the RIGHT subtree.
 * PLUS - special set of cases if the root node is the target
 * 
 * there is a problem with deleting the root node. Process left most, is
 * backwards.
 *
 * my solution has been hacked together and is not nearly as simple as I 
 * am sure it could be.
 */
template<class T>
bool Bst<T>::delete_node_item(Tree_node* &target)
{
  Tree_node *del_ptr;
  T* replacement_item;  
  
  /* Case 1 - is the node a leaf?.*/
  if ((target->left == NULL) && (target->right == NULL)) {
    delete target;
    target = NULL;
    return true;

  /* Case 2 - the target has no child to its left, keep checking */ 
  } else if (target->left == NULL) {
    /* find out which parent node it is */
    del_ptr = target;
    target = target->right;
    del_ptr->right = NULL;
    delete del_ptr;
    return true;
 
    /* Case 3 - node has child on its left, and NO Right CHILD */
  } else if (target->right == NULL) {
    del_ptr = target;
    target = target->left;
    del_ptr->left = NULL;
    delete del_ptr;
    return true; 
 
  /* Case 4 - Target has two children. You must figure out
  * which child to promote. Problem: is this the RIGHT child or the LEFT child
  * of the parent?
  */
  } else { //if ((cur->left != NULL) && (cur->right != NULL)) {
    process_left_most(target->right, replacement_item);
    target->item = replacement_item;
    return true;
  }
}


  
/* process_left_most 
 * Traverses the right subtree of the node to find its left most element. 
 * remove passes the right subtree of the node to be deleted. This way, all
 * left most has to do is face Derek Zoolander's greatest fear: going left.
 */
template<class T>
void Bst<T>::process_left_most(Tree_node* &node, T* &data)
{
  if (node->left == NULL) {
    data = node->item;
    // new changes
    Tree_node *del_ptr = node;
    node = node->right;
    del_ptr->right = NULL;
    delete del_ptr;
  } else { 
    return process_left_most(node->left, data);
  }
}

template<class T>
void Bst<T>::remove(std::string key)
{
  Tree_node* target = search_node(key, root);
  if (target == NULL) {
    return;
  } else {
    delete_node_item(target);
  }
}

template<class T>
void Bst<T>::print_inorder(std::ostream& os)
{  
  inorder(root, os);
}

/* Left, root, right. Do this recursively */
template<class T>
void Bst<T>::inorder(Tree_node* node, std::ostream& os)
{ 
  if (node == NULL) {
    return;
  }
  inorder(node->left, os);
  inorder(node->right, os);
  os << *node->item;
}

template<class T>\
void Bst<T>::print_preorder(std::ostream& os)
{ 
  preorder(root, os);
}

/* Root, left, right. Do this recursively */
template<class T>
void Bst<T>::preorder(Tree_node* node, std::ostream& os)
{ 
  if (node == NULL) {
    return;
  }
  preorder(node->left, os);
  os << *node->item;
  preorder(node->right, os);
}

template<class T>
void Bst<T>::print_postorder(std::ostream& os)
{ 
  postorder(root, os);
}

/* Left, right, root. Do this recursively */
template<class T>
void Bst<T>::postorder(Tree_node* node, std::ostream& os)
{ 
  if (node == NULL) {
    return;
  }
  postorder(node->left, os);
  postorder(node->right, os);
  os << *node->item;
}
// test print functions

template<class T>
void Bst<T>::test()
{
  test_print(root);
}

template<class T>
void Bst<T>::test_print(Tree_node* head)
{
  if (head == NULL) {
    return;
  } 
  std::cout << "Key: " << head->key << "  Item: " << *head->item << std::endl;
  test_print(head->left);
  test_print(head->right);
}

#endif
