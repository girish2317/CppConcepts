#include<iostream>

template<class T>
class Node
{
public:
    T data;
    Node* next;

    Node(T data) : data(data), next(nullptr) {}
};

template<class T>
class LinkedList 
{
public:
    Node<T>* head;

    LinkedList(): head(nullptr){}

    Node<T>* gethead(){
        return head;
    }

    bool isEmpty(){

        if(head == nullptr)
            return true;
        else
            return false;
    }

    int Length() {

        int count = 0;
        while (head) {
            head = head->next;
            count++;
        }
        return count;
    }

    bool printList(){
        if(isEmpty()){
            std::cout << "List is empty" << std::endl;
            return false;
        }

        Node<T>* temp = head;
        std::cout << "List : ";

        while(temp != nullptr){
             std::cout << temp->data << "->";
             temp = temp->next;
        }
        std::cout  << "null " << std::endl;    // printing null at the end
        return true;

    }

    void insertAtHead(Node<T>* node){

        if(!head){
            head = node;
        }
        else{
            node->next = head;
            head = node;
        }
    }

    void insertAtTail(Node<T>* node){

        Node<T>* temp = head;

        if(head == nullptr){
            head = node;
        }
        else{

            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = node;
        }
    }

    bool deleteAtHead()
    {
        if(isEmpty()){
            std::cout<< "empty list" << std::endl;
            return false;
        }
        Node<T>* current = head;
        head = head->next;
        delete current;
        return true;
    }

    void CreateLinkedList(T lst[], int size) {
        for (int i = size - 1; i >= 0; i--) {
            Node<T>* newNode = new Node<T>(lst[i]);
            insertAtHead(newNode);
        }
    }

    void insertLoop()
    {
        Node<T>* temp = head;

        while(temp->next != nullptr){
            temp= temp->next;
        }

        temp->next = head;
    }
};

template<class T>
void PrintListWithForwardArrow(Node<T>* head) {
    Node<T>* temp = head;

    while (temp) {
        std::cout << temp->data;
        temp = temp->next;
        if (temp) {
            std::cout << " -> ";
        }
    }
    std::cout << " -> nullptr ";
}

template<class T>
bool search(Node<T> *head, T value)
{
    Node<T> *temp = head;

    while(temp != nullptr){
        if(temp->data == value)
            return true;
        else
            temp = temp->next;
    }
    
    return false;
}

template<class T>
bool deleteNode2(Node<T>* head, int value) {
    bool deleted = false;

    Node<T>* current = head;
    Node<T>* previous = nullptr;
    // Check if the value to delete is in the head node
    if (current->data == value) {
        head = current->next;
        delete current;
        deleted = true;
        return deleted;
    }
    // Traverse the linked list to find the node with the given value
    while (current) {
        if (current->data == value) { // If the value is found
            previous->next = current->next;
            delete current;
            deleted = true;
            break;
        }
        previous = current;
        current = current->next;
    }

    return deleted;
}

template<typename T>
bool deleteNode(Node<T>*& head, T value){

    Node<T>* current = head;
    Node<T>* previous = nullptr;

    while(current != nullptr){

        if(current->data == value){
            
            if(previous != nullptr){
                previous->next = current->next;   
            }
            else{
                head = head->next;
            }
            delete current;
            return true;

        }
        else{
            previous = current;
            current = current->next;
        }
    }
    return false;
}

template<typename T>
Node<T>* reverse(Node<T>* head)
{
    Node<T>* previous = nullptr;
    Node<T>* current = head;
    Node<T>* nextNode = nullptr;

    while(current){

        nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    head = previous;
    return head;   
}

template<typename T>
bool detectCycle(Node<T>* head)
{
    Node<T>* slow = head;
    Node<T>* fast = head;

    while(slow && fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast){
            return true;
        }
    }
    return false;
}

template<typename T>
Node<T>* FindMid(Node<T>* head)
{
    if (!head) return nullptr;

    Node<T>* node = head;
    Node<T>* fast = head;

    while(fast && fast->next){
        node = node->next;
        fast = fast->next->next;
    }

    return node;
}

template<typename T>
Node<T>* RemoveDuplicates(Node<T>* head)
{
    Node<T>* outerNode = head;

    while(outerNode){

        Node<T>* innerNode = outerNode;

        while(innerNode){

            if(innerNode->next){

                if(outerNode->data == innerNode->next->data){
                    Node<T>* duplicateNode = innerNode->next;
                    innerNode->next = innerNode->next->next;
                    delete duplicateNode;
                }
                else{
                    innerNode = innerNode->next;
                }
            }
            else{
                innerNode = innerNode->next;
            }
        }
        outerNode = outerNode->next;
    }
    return head;
}

template<typename T>
Node<T>* Union(Node<T>* head1, Node<T>* head2)
{
    if(!head1) return head2;
    if(!head2) return head1;

    Node<T>* current = head1;
    while(current->next){
        current = current->next;
    }

    current->next = head2;

    return RemoveDuplicates(head1);
 //   return head1;
}

template<typename T>
bool IsExists(T data, Node<T>* head)
{
    Node<T>* current = head;
    while(current){

        if(data == current->data)
            return true;
        current = current->next;
    }
    return false;
}

template<typename T>
Node<T>* InsertAtHead(T data, Node<T>* head){

    Node<T>* temp = new Node<T>(data);
    temp->next = head;
    return temp;
}

template<typename T>
Node<T>* Intersection(Node<T>* head1, Node<T>* head2)
{
    Node<T>* current1 = head1;
    Node<T>* results = nullptr;
    while(current1){

        Node<T>* current2 = head2;

        while(current2){

            if(current1->data == current2->data && !IsExists(current2->data, results)){

                //add to results
                results = InsertAtHead(current2->data, results);
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    return results;
}