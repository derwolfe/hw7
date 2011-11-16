#ifndef BST_H
#define BST_H

#include <iostream>
#include <cstdlib>
#include <string>

/* 
 * What should the key be? How do you want to initialize the tree?
 */
template <class T>
class Bst
{
 private:

  struct Tree_node {
  public: 
    /* ?structs are inherently public, 
     * why hide it if you want to be public?
     */
    Tree_node*  left;
    Tree_node*  right;
    string      key;
    T*          item;
  };

  Tree_node*  root;
  int size;

 public:
  Bst();
  ~Bst();
  
  bool        is_empty() const;
  /* new operations*/
  bool        insert(string key, T* item);
  T*          search();
  Tree_node*  search_node(string key, Tree_node* leaf);
  bool        delete_node_item(T& item);
  Tree_node*  process_left_most(Tree_node* root);
  
  /* ostream as output? Normally it is by reference */
  std::ostream  inorder(Tree_node* root);
  std::ostream  preorder(Tree_node* root);
  std::ostream  postorder(Tree_node* root);

  void  remove(string key);
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
bool Bst<T>::is_empty()
{
  if (size == 0) {
    return true;
  } 
  return false;
}

/* 
 * Insert 
 * The string of either the title or artist will be the key, but you still must
 * ADD the item to the tree. 
 *
 * The provided key will determine how the BST is sorted, i.e. if you want it
 * to be keyed by artist, when you call this function use get_track_title() for
 * title, etc.
 *
 * What about const?
 */
template<class T>
void Bst<T>::insert(string key, Tree_node* leaf, T* item)
{
  /* If less than 1, then shift to the left
   */
  if (key.compare(leaf->key) < 1) {
    if (leaf->left != NULL) {
      insert(key, leaf->left, item);
    } else { 
      new_leaf          = new Tree_node;
      new_leaf->key     = key; 
      new_leaf->item    = item;
      new_leaf->right   = NULL;
      new_leaf->left    = NULL;
      if (size == 0) {
        root = new_leaf;
      }
      ++size;
    }
    /* key comparison of >= 1 means that the key provided is LARGER than the
     * key against which it was tested
     */
  } else if (key.compare(leaf->key) >= 1) {
    if (leaf->right != NULL) {
      insert(key, leaf->right, item);
    } else { 
      new_leaf          = new Tree_node;
      new_leaf->key     = key; 
      new_leaf->item    = item;
      new_leaf->right   = NULL;
      new_leaf->left    = NULL;
      if (size == 0) {
        root = new_leaf;
      }
      ++size;     
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
typename Bst<T>::Tree_node Bst::search_node(string key, Tree_node* leaf)
{
  if (key.compare(leaf->key) == 1) {
    return leaf;
  } else if (key.compare(leaf->key) < 1) {
    if (leaf->left != NULL) {
      search_node(key, leaf->left);
    }
  } else if (key.compare(leaf->key) > 1) {
    if (leaf->right != NULL) {
      search_node(key, leaf->right);
    }
  } else { // key not found
    return NULL; // could be a problem, may need to throw exception!
  }
}

#endif
