#include"include/accessPrivate.h"
#include"include/CArray.h"
#include "include/delete.h"
#include "include/fold_expressions.h"
#include<iostream>
#include "include/gen_hash_values.h"
#include "include/optional.h"
#include "include/modern_class.h"
//#include "performance/error_handling.h"
#include "performance/move_buffer.h"
#include "dataStructures/single_linked_list.h"
#include "string"

int main()
{

    /** //private class implementation
    accessPrivate shape(10.1, 11.1, "Polar");

    std::cout << shape.getShape().c_str() << std::endl;
    shape.getPoint().display();

    */

   /** Array container implementation */
   /*
    c_array<int, 3> arr;

    arr.SetAt(0, 10);
    arr.SetAt(1, 11);
    arr.SetAt(2, 12);
//    arr.SetAt(4, 13);

    for(int i=0; i < arr.GetSize(); i++){
        std::cout<< arr.GetAt(i) << std::endl;
    }

    print_c_array(arr);

    arr[0] = 20;
    std::cout<< "Value at 1 "<< arr[1] << std::endl;

    print_c_array(arr);
    */

    /*
    //#include "include/delete.h"

    Data original("Girish", 24);
    // Data copy = original; // Copy constructor is called
    
    // Data assignData;
    // assignData = original;

    // original.display();
    // copy.display();
    // assignData.display();

    data_wrapper wrapper_original(&original);
    wrapper_original.printData();
 //   data_wrapper wrapper_copy = wrapper_original; cannot be referenced -- it is a deleted function
    data_wrapper wrapper_copy(std::move(wrapper_original));
    wrapper_copy.printData();

    wrapper_original = std::move(wrapper_copy);
    wrapper_original.printData();
    if(wrapper_copy)
        wrapper_copy.printData();

    */

    /*
    // #include "include/fold_expressions.h"
    printAll(1, 2, "Hello", " ", "Girish");
    auto sum = add_to_one(1, 2, 3, 4, 5); // sum = 16
    auto sum2 = add_to_one(sum, 1, 2, 3, 4, 5); // sum = 32
    printAll(sum, " -> ", sum2);
    */

   /*
   std::hash<Item> hasher;
   size_t hashValue = hasher(Item(1, "one", 1.0));
   std::cout<<"Item hash value " << hashValue << std::endl;
   hashValue = hasher(Item(1, "one", 2.0));
   std::cout<<"Item hash value " << hashValue << std::endl;
   std::cout<< std::hash<Item>{}(Item(1, "one", 0.1)) << std::endl;
   */
   
   /*
   std::map<int, std::string> m {
    {1, "one"}, {2, "two"}, {3, "three"}
    };

    auto value = find(2, m);
    if(value) std::cout<< *value << std::endl;
    value = find(4, m);
    if(value) std::cout<< *value << std::endl;
    */

    /**
     * 
     // src\include\modern_class.h
     UserManager manager;
     manager.addUser("Alice", 30);
     manager.addUser("Bob", 25);
     
     auto result = manager.findUser("Charlie");
     
     if (result.has_value()) {
        std::cout << "Found user: " << result->get().getName() << '\n';
    } else {
        std::cerr << "User not found.\n";
    }
    */

    // try {
    //     openFile("missing.txt");
    // }
    // catch (const FileNotFound& e) {
    //     std::cerr << "Error: " << e.what() << "\n";
    // }

    /**
    
    std::vector<Buffer> c;
    c.push_back(Buffer(100));   // move
    Buffer b(200);
    c.push_back(b);             // copy
    c.push_back(std::move(b));  // move
    c.push_back(std::move(b));  // move
    
    Buffer b1; // default constructor
    cout << "b1 object=" << &b1 << " data=" << (void*)b1.c_str() << "\n\n";
    Buffer b2(100); // explicit constructor
    cout << "b2 object=" << &b2 << " data=" << (void*)b2.c_str() << "\n\n";
    Buffer b3(b2); // copy constructor
    b1 = b3; // assignment operator
    Buffer b4(std::move(b1)); // move constructor
    b3 = std::move(b4); // move assignment
    
    // std::string a = "Hello";
    // std::string b = a;              // copies (a is an lvalue)
    // std::cout << "a (before move): " << a << " " << &a << "\n";
    // std::string c = std::move(a);   // moves (a is treated as an rvalue)
    
    // std::cout << "b: " << b << " " << &b << "\n";
    // std::cout << "c: " << c << " " << &c << "\n";
    // std::cout << "a (after move): " << a << " " << &a << "\n"; // a is in a valid but unspecified state
    */

    LinkedList<int> list; // Linked List created
    // for (int i = 1; i < 10; i++) {
    //     list.insertAtTail(new Node<int>(i)); // inserting data at head of the list
    //     list.printList();
    // }

    //  for (int i = 10; i < 20; i++) {
    //     list.insertAtHead(new Node<int>(i)); // inserting data at head of the list
    //     list.printList();
    // }

    /*
    int inputs[][10] = {
        {10, 20, 30, 40, 50},
        {-1, -2, -3, -4, -5, -6},
        {3, 2, 1},
        {},
        {12}
    };
    int sizes[] = {5, 6, 3, 0, 1}; // Sizes of the input arrays
    
    int value[] = {50, -7, 3, 55, 12};
    
    for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++) {
        LinkedList<int> inputLinkedList;
        inputLinkedList.CreateLinkedList(inputs[i], sizes[i]);
        std::cout << (i + 1) << ".\tInput linked list: ";
        inputLinkedList.printList();
        std::cout << "\n\tSearched value: " << value[i] << std::endl;
        std::cout << "\n\tSingly linked list value found : " << search(inputLinkedList.head, value[i]) << std::endl;
        std::cout << std::string(75, '-') << std::endl;
    }
    
    */

 //   LinkedList<int> list; // creating list

    for (int i = 1; i < 5; i++) {
        list.insertAtTail(new Node<int>(i)); // inserting data in list
        list.printList();
    }

    list.deleteAtHead(); // deleting 1 from list 
    list.printList();
    list.deleteAtHead(); // now deleting 2 from list
    list.printList();

    std::cout << "\n\value to be deleted: " << 3 << std::endl;
    std::cout << "\n\tvalue deleted : " << deleteNode(list.head, 3) << std::endl;
    list.printList();
    std::cout << std::string(75, '-') << std::endl;

    int input[][10] = {
        {30, 20, 30, 10, 50},
        {-7, -7, -22, -1, -5, -5},
        {1, 1, 1},
        {9, -9, 9},
        {1, -2, -2},
    };
    int sizes[] = {5, 6, 3, 3, 3};
    int values[] = {30, -8, 3, 12, 1};

    int unionList[][20] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 1, 2, 2, 3, 3, 4, 4, 5},
        {-45, 34, -54, 45, -65, 54},
        {12},
        {0, 1, 2},
    };
    int unionSizes[] = {9, 9, 6, 1, 3};
    
    int intersectionList[][20] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 1, 2, 2, 3, 3, 4, 4, 5},
        {-45, 34, -54, 45, -65, 54},
        {12},
        {0, 1, 2}
    };
    int intersectionSizes[] = {9, 9, 6, 1, 3};

    int inputList2[][20] = {
        {7, 8, 9, 10, 11, 12, 13, 14},
        {1, 2, 3, 4, 5, 6},
        {3, 2, 1},
        {12},
        {3, 4, 5},
    };
    int inputList2sizes[] = {8, 6, 3, 1, 3};
   
    /*
    for (int i = 0; i < sizeof(input)/sizeof(input[0]); i++) {
        LinkedList<int> inputLinkedList;
        inputLinkedList.CreateLinkedList(input[i], sizes[i]);
        std::cout << (i + 1) << ".\tInput linked list: ";
        PrintListWithForwardArrow(inputLinkedList.head);
        
        //        std::cout << "\n\tSearched value: " << value[i] << std::endl;
        //        std::cout << "\n\tSingly linked list value found : " << search(inputLinkedList.head, value[i]) << std::endl;
        
        //        std::cout << "\n\tValue to be deleted: " << values[i] << std::endl;
        //        std::cout << "\n\tResult: " << (deleteNode2(inputLinkedList.head, values[i]) ? "true" : "false") << std::endl;
        
        // std::cout << "\n\tReverse linked list: ";
        // PrintListWithForwardArrow(reverse(inputLinkedList.head));
        // inputLinkedList.insertLoop();
        // std::cout << "\n\tDetect Cycle Result: " << (detectCycle(inputLinkedList.head) ? "true" : "false") << std::endl;
        
        //std::cout << "\n\tMiddle Node: " << FindMid(inputLinkedList.head)->data << std::endl;
        
        std::cout << "\n\tLinked list without duplicates: ";
        PrintListWithForwardArrow(RemoveDuplicates(inputLinkedList.head));
        std::cout << std::string(100, '-') << std::endl;
    }
    */

    for (int i = 0; i < sizeof(unionList)/sizeof(unionList[0]); i++) {
        LinkedList<int> inputLinkedList1;
        LinkedList<int> inputLinkedList2;
        LinkedList<int> inputLinkedList3;

    
        inputLinkedList1.CreateLinkedList(unionList[i], unionSizes[i]);
        inputLinkedList2.CreateLinkedList(intersectionList[i], intersectionSizes[i]);
        inputLinkedList3.CreateLinkedList(inputList2[i], inputList2sizes[i]);


        std::cout << (i + 1) << ".\tInput linked list 1: ";
        PrintListWithForwardArrow(inputLinkedList1.head);
        std::cout << std::endl;

        std::cout << "\tInput linked list 2: ";
        PrintListWithForwardArrow(inputLinkedList3.head);
        std::cout << std::endl;

        std::cout << "\n\tUnion: ";
        PrintListWithForwardArrow(Union(inputLinkedList1.head, inputLinkedList3.head));
        std::cout << std::endl;
        LinkedList<int> inputLinkedList4;

        inputLinkedList4.CreateLinkedList(inputList2[i], inputList2sizes[i]);
        

        std::cout << "\n\tIntersection: ";
        PrintListWithForwardArrow(Intersection(inputLinkedList2.head, inputLinkedList4.head));
        std::cout << std::endl;

        std::cout << std::string(100, '-') << std::endl;
    }
    
    
}