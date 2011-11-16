#ifndef BST_H
#define BST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
/* 
 * What should the key be? How do you want to initialize the tree?
 */
template <class T>
class Bst
{
 private:

  struct Tree_node {
  public: 
    /* structs are inherently public, 
     * why hide it if you want to be public?
     */
    Tree_node*    left;
    Tree_node*    right;
    std::string   key;
    T*            item;
  };

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
  bool        delete_node_item(Tree_node* item);
  void        process_left_most(Tree_node& node, T& data);
  
  /* These just traverse the tree!*/
  void  inorder(Tree_node* root, std::ostream &os);
  void  preorder(Tree_node* root, std::ostream &os);
  void  postorder(Tree_node* root, std::ostream &os);

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
    remove(root);
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
  if (root == NULL) {
    Tree_node* new_leaf = new Tree_node;
    new_leaf->key       = key; 
    new_leaf->item      = item;
    new_leaf->right     = NULL;
    new_leaf->left      = NULL;
    root = new_leaf;
    size = 1;
  } else if (root != NULL){ 
    Tree_node* current  = root;
    Tree_node* leaf     = new Tree_node;
    while (current != NULL) {
        // go LEFT
      if (key.compare(current->key) < 0) {
        if (current->left == NULL) {
          current->left   = leaf;
          leaf->key       = key; 
          leaf->item      = item;
          leaf->right     = NULL;
          leaf->left      = NULL;
          return;
        } else { 
          current = current->left;
        }
      } // go RIGHT
      else if (key.compare(current->key) > 0) {
        if (current->right == NULL) {
          current->left   = leaf;
          leaf->key       = key; 
          leaf->item      = item;
          leaf->right     = NULL;
          leaf->left      = NULL;
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
  return found;
}

/* delete_node_item - will be called by remove.
 *
 * called with a pointer to the NODE!
 *
 * 4 cases
 * -------
 * 1) Node has no children
 * 2) Node has only a right subtree, move up the right subtree.
 * 3) Node has only a left subtree, move up the left subtree.
 * 4) Node has BOTH left and right subtrees. Replace the data element 
 *    of the current tree with the data element from the left most 
 *    element of the RIGHT subtree.
 *
 */
template<class T>
bool Bst<T>::delete_node_item(Tree_node* item)
{
  Tree_node* target = root;
  Tree_node* parent = root;
  /* traverse the tree to find the pointer matching the provided node. 
   * This must be done so the parent isn't left with a garbage address in its pointer.
   * 
   * I can't think of any other way but to traverse the tree to find the parents
   */ 
  while (target != NULL) {
    if( (*item->key).compare(*target->key) == 0) { /* item found  */
      break;
      /* pick the left tree */
    } else if ((*item->key).compare(*target->key) < 0) { 
      parent = target;
      target = target->right;
      /* pick the right subtree */
    } else {
      parent = target;
      target = target->left;
    } /* rinse, repeat */
  }
  // tests
  cout << "item add:    " << endl;
  cout << "target add:  " << endl;

  //assert(target == item) /* make sure the two pointers are equal */
  /* condition that will occur only the parent is the root node */
  if (size == 1) { // root node case
    delete target; // why not delete item?
    root = NULL;
    size = 0;
    return true; /* breaks the function returns the value! */
  }
  /* Now we can start deallocating memory. Having the parent pointer helps immensely. 
   *
   * Case 1 - test to see if node is a leaf.*/
  if ((target->left == NULL) && (target->right == NULL)) {
    if (target == parent) { //root node case
      delete target;
    /* check to see if the target is a child */
    } else if (parent->left == target) {
      parent->left = NULL;
      delete target;
    } else if (parent->right == target) {
      parent->right = NULL;
      delete target;
    }
    target = NULL;
    parent = NULL;
    return true;
  /* Case 2 - the node has a child to its left, so delete the node, and move
   * the the parent's LEFT pointer to target->left */
  } else if ((target->left != NULL) && (target->right == NULL)) {
    parent->left = target->left; /*move up the node to the left! */
    delete target;
  /* Case 3 - node has child on its left */
  } else if ((target->left == NULL) && (target->right != NULL)) {
    parent->right = target->right; /* move up the node to the right! */
    delete target;
  /* Case 4 - parent has a child, target. Target has two children. You must figure out
   * which child to promote. Problem: is this the RIGHT child or the LEFT child
   * of the parent?
   *
   * SOMETHING IS VERY WRONG HERE - process_left_most does not return any thing
   * you need to replace the information contained in target with the information from
   * the left most node. Call process left node on the data to do that, then delete the node
   * from which you TOOK the data.
   */
  } else if ((target->left != NULL) && (target->right != NULL)) {
    if (parent->left == target) {
      process_left_most(target->right, target->data);
      
    //  delete target;
    } else if (parent->right == target) {
      process_left_most(target->right, target->data);
    //  delete target;
    }
    target = NULL;
    parent = NULL;
    item   = NULL;
    return true;
  }
}
/* process_left_most 
 * Traverses the right subtree of the node to find its left most element. 
 * remove passes the right subtree of the node to be deleted. This way, all
 * left most has to do is face Derek Zoolander's greatest fear: going left. 
 */
template<class T>
void Bst<T>::process_left_most(Tree_node& node, T& data)
{
  if (node->left == NULL) {
    data = node->data;
  } else { 
    return process_left_most(node->left, data);
  }
}

template<class T>
void Bst<T>::print_inorder(std::ostream& os)
{  
  Tree_node* temp = root;
  inorder(temp, os);
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

template<class T>
void Bst<T>::print_preorder(std::ostream& os)
{ 
  Tree_node* temp = root;
  preorder(temp, os);
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
  Tree_node* temp = root;  
  postorder(temp, os);
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

 
#endif
