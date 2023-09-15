#include <iostream>
#include <string>
using namespace std;
#include "Lstack.cpp"

// To test just queue follow these instructions:
//   1.  make ttest


int main () {
  //Test 1 - Default Constructor, Push, and Display
  cout << "Test 1 - Default Constructor, Push, and Display Test" << endl;
  int test1 = 10;
  int test2 = 20;
  int test3 = 30;
  //Test Default Constructor
  Lstack <int> *newLS1 = new Lstack <int>();
  //Push 3 nodes into Lstack
  newLS1->Push(test1);
  newLS1->Push(test2);
  newLS1->Push(test3);
  cout << "After 3 Pushs size: " << newLS1->GetSize() << endl;
  newLS1->Display();
  cout << "End Test 1 - Constructor, Push, and Display Test" << endl << endl;
    
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor Running" << endl;
  //Test Copy constructor
  Lstack <int> *newLS2 = new Lstack <int>(*newLS1);
  newLS2->Display();
  cout << "size below should match. Location should not" << endl;
  cout << "Source size: " << newLS1->GetSize() << " and Copied size: "
       << newLS2->GetSize() << endl;
  cout << "Source location: " << &newLS1 << " and Copied location: " << &newLS2 << endl;
  cout << "End Test 2 - Copy Constructor" << endl << endl;
  
  //Test 3 - Overloaded Assignment Operator
  cout << "Test 3 - Overloaded Assignment Operator Running" << endl;
  //Create new Lstack using constructor
  Lstack <int> *newLS3 = new Lstack <int>();
  //Update using overloaded assignment operator
  *newLS3 = *newLS1;
  newLS3->Display(); //Display contents of newLS3
  cout << "size below should match. Location should not" << endl;
  cout << "Source size: " << newLS1->GetSize() << " and Assigned size: " << newLS3->GetSize() << endl;
  cout << "Source location: " << &newLS1 << " and Assigned location: " << &newLS3 << endl;
  cout << "End Test 3 - Assignment" << endl << endl;
  
  //Test 4 - Test Pop
  cout << "Test 4 - Pop" << endl;
  cout << "size before: " << newLS1->GetSize() << " ";
  newLS1->Pop();
  cout << "size after: " << newLS1->GetSize() << endl;
  cout << "End Test 4 - Pop" << endl << endl;
  
  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test size()
  cout << "Outputting GetSize" << endl;
  cout << newLS2->GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLS2->Clear();
  cout << "Outputting the size (should now be 0)" << endl;
  cout << newLS2->GetSize() << endl;
  cout << "End Test 5 - GetSize and Clear" << endl << endl;
  
  //Test 6 - Test Find
  cout << "Test 6 - Find" << endl;
  cout << "Try to find 30 (Should NOT find it)" << endl;
  if(newLS1->Find(test3) != -1){
    cout << "30 Found" << endl;
  }else{
    cout << "30 NOT Found" << endl;
  }
  cout << "Try to find 20 (Should find it)" << endl;
  if(newLS1->Find(test2) != -1){
    cout << "20 Found" << endl << endl;
  }else{
    cout << "20 NOT Found" << endl;
  }
  cout << "End Test 6 - Find" << endl << endl;
  
  //Test 7 - Test At()
  cout << "Test 7 - At()" << endl;
  cout << "Should output 20 10" << endl;
  for(int i = 0; i < newLS1->GetSize(); i++){
    cout << newLS1->At(i) << endl;
  }
  cout << "End Test 7 - At()" << endl << endl;
  
  //Test 8 - Test Destructor
  cout << "Test 8 - Test Destructor" << endl;
  cout << "delete newLS1" << endl;
  delete newLS1;
  cout << "delete newLS2" << endl;
  delete newLS2;
  cout << "delete newLS3" << endl;
  delete newLS3;
  cout << "End Test 6 - Destructors" << endl;
  return 0;
}
