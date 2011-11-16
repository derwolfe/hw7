#include <stdio.h>

#include "Linked_List_template.h"

int main ()
{
  Linked_List<int>* test = new Linked_List<int>;
  int* a = new int(9);
  int* b = new int(100);
  int* c = new int(2100);
  int* d = new int(892);

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
  cout << test->get_size() << endl;
  //test->find(4);
  cout << endl;
  cout << "find element 3" << endl;
  cout << test->retrieve(3) << endl;
  
}

