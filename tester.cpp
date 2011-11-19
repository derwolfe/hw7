#include <stdio.h>

#include "Linked_List_template.h"
#include "Bst_template.h"


int main ()
{
  Linked_List<int>* test = new Linked_List<int>;
  int* a = new int(1);
  int* b = new int(100);
  int* c = new int(2100);
  int* d = new int(892);
  int* f = new int(12);
  int* e = new int(3514);

  test->append(a);
  test->append(b);
  test->append(c);
  test->append(d);
  test->tprint();
  test->remove(4);
  cout << "after pos 4 removed" << endl;
  test->tprint();
  cout << "find item 2" << endl;
  cout << test->retrieve(2) << endl;
 // cout << test->get_size() << endl;
  //test->find(4);
  cout << endl;
  cout << "tree tests" << endl;
//  cout << "find element 3" << endl;
//  cout << test->retrieve(3) << endl;
  
  //test->tprint();
  
  Bst<int>* tree = new Bst<int>;
  tree->insert("d", a);
  tree->insert("b", b);  
  tree->insert("f", d);
//  tree->insert("a", c);
//  tree->insert("f", f);
//  tree->insert("e", e);
   
  cout << "t1" << endl;
  tree->test();
  //cout << "postrev" << endl;
  cout << "post rev 2" << endl;
  tree->remove("b");
//  tree->remove("d");
  tree->test();
  //tree->remove("schietbueddel");
  //cout << "t3" << endl;
  //tree->test();
}

