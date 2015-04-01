//
//  main.cpp
//  Stivali.InterviewPractice.LinkedLists
//
//  Created by Matt on 3/31/15.
//  Copyright (c) 2015 Facebook. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <unordered_map>
using namespace std;

struct node {
    int info;
    struct node* next;
};

class LinkedList {
    
    
public:
    
    LinkedList();
    void InsertAtFront(int);
    void AppendElement(int);
    bool InsertBeforeNode(int, int);
    bool InsertAfterNode(int, int);
    bool DeleteFirstElement();
    bool DeleteLastElement();
    bool DeleteBeforeNode(int);
    bool DeleteAfterNode(int);
    void DeleteDuplicates();
    void DeleteDuplicatesNoBuffer();
    int GetNthToLastNode(int);
    void Display();
    
private:
    
    node *firstNode;
    node *GetPreviousNode(node*);
    
};

void SeedLinkedList(LinkedList &linkedList, int size);
int PrintNodeValue(node *n);


LinkedList::LinkedList() {
    firstNode = NULL;
}




void LinkedList::InsertAtFront(int data){
    //create a new node
    node *p = new node;
    
    //assign data
    p->info = data;
    
    //assign pointer
    p->next = firstNode;
    firstNode = p;
    
}

void LinkedList::AppendElement(int data){
    
    //Declare two nodes
    node *lastNode = new node;
    node *insertedNode = new node;
    
    
    //let the node to the left be initialized to the first element
    //of the linked list
    lastNode = firstNode;
    
    //populate node with new data
    
    insertedNode->info = data;
    insertedNode->next = NULL;
    
    //If there exists no element in the list position,
    //p is assigned as the list element in the List
    
    if(firstNode == NULL){
        firstNode = insertedNode;
        
        //iterate to find the end of the list
    }else{
        while(lastNode->next!=NULL){
            lastNode = lastNode->next;
        }
        //set last element to point to p
        lastNode->next = insertedNode;
    }
}

bool LinkedList::InsertBeforeNode(int targetValue, int newElement)
{
    node *leftNode = new node();
    node *insertedNode = new node();
    node *targetNode = new node();
    bool isFound = false;
    
    //Find target node
    targetNode = firstNode;
    while(targetNode!=NULL) {
        if(targetNode->info == targetValue) {
            isFound = true;
            break;
        }
        leftNode = targetNode;
        targetNode = targetNode->next;
    }
    
    //If found, insert element
    if(isFound){
        insertedNode->info = newElement;
        if(targetNode==firstNode) {
            InsertAtFront(newElement);
        }else {
            leftNode->next = insertedNode;
            insertedNode->next = targetNode;
        }
    } else {
        return false;
    }
    
    return true;
}

bool LinkedList::InsertAfterNode(int targetValue, int newElement)
{
    node *targetNode = new node;
    node *insertedNode = new node;
    node *rightNode = new node;
    bool isFound = false;
    
    //Find Target Node
    targetNode = firstNode;
    while(targetNode!=NULL){
        if(targetNode->info == targetValue){
            isFound = true;
            break;
        }
        targetNode = targetNode->next;
    }
    
    //If found, insert element and adjust pointers
    if(isFound){
        insertedNode->info = newElement;
        if(targetNode->next == NULL){
            AppendElement(newElement);
        }else{
            rightNode = targetNode->next;
            targetNode->next = insertedNode;
            insertedNode->next = rightNode;
        }
    }else{
        return false;
    }
    
    return true;
    
    
}

bool LinkedList::DeleteFirstElement(){
    node *temp = new node;
    
    if(firstNode == NULL){
        return false;
    } else {
        temp = firstNode;
        firstNode = firstNode->next;
        delete temp;
    }
    return true;
}

bool LinkedList::DeleteLastElement(){
    
    node *leftPtr = new node;
    node *leadPtr = new node;
    
    //Handles case for empty list
    if(firstNode == NULL){
        return false;
    }
    
    //Handles case for only one element
    leadPtr = firstNode;
    if(leadPtr->next == NULL) {
        firstNode = NULL;
        delete leadPtr;
    }else{
        while(leadPtr->next!=NULL){
            leftPtr = leadPtr;
            leadPtr = leadPtr->next;
        }
        leftPtr->next = NULL;
        delete leadPtr;
        
    }
    
    return true;
    
}

bool LinkedList::DeleteBeforeNode(int targetValue){
    
    node *nodeForDeletion = new node;
    node *targetNode = new node;
    bool isFound = false;
    
    if(firstNode == NULL){
        //list is empty
        return false;
    }
    
    targetNode = firstNode;
    
    while(targetNode!=NULL){
        if(targetNode->info == targetValue){
            isFound = true;
            break;
        }
        
        nodeForDeletion = targetNode;
        targetNode = targetNode->next;
    }
    
    if(isFound){
        if(targetNode == firstNode){
            //there is only one element, cannot delete previous element
            //if it does not exist
            return false;
        } else if(targetNode == firstNode->next) {
            firstNode = targetNode;
            delete nodeForDeletion;
        } else {
            GetPreviousNode(nodeForDeletion)->next = targetNode;
            delete nodeForDeletion;
            
        }
    }
    return true;
    
}

bool LinkedList::DeleteAfterNode(int targetValue){
    
    node *targetNode = new node;
    node *nodeForDeletion = new node;
    node *rightNode = new node;
    bool isFound = false;
    
    if(firstNode == NULL){
        return false;
    }
    
    if(firstNode->next == NULL){
        return false;
    }
    
    targetNode = firstNode;
    
    while(targetNode!=NULL){
        if(targetNode->next == NULL) {
            //arrived at end of the list, cannot delete
            return false;
        }
        if(targetNode->info == targetValue){
            isFound = true;
            break;
        }
        
        targetNode = targetNode->next;
    }
    
    if(isFound){
        
        nodeForDeletion = targetNode->next;
        
        if(nodeForDeletion->next == NULL){
            targetNode->next = NULL;
            delete nodeForDeletion;
        }
        else {
            nodeForDeletion = targetNode->next;
            rightNode = targetNode->next->next;
            targetNode->next = rightNode;
            delete nodeForDeletion;
        }
    } else {
        return false;
    }
    
    return true;
}

node* LinkedList::GetPreviousNode(node *targetNode){
    int counter1 = 0;
    int counter2 = 0;
    node *temp = new node;
    temp = firstNode;
    while(temp!=targetNode){
        counter1++;
        temp=temp->next;
    }
    
    temp = firstNode;
    while(counter2<counter1-1){
        counter2++;
        temp = temp->next;
    }
    return temp;
}

void LinkedList::Display(){
    node *p = new node;
    p = firstNode;
    if(firstNode==NULL){
        cout<<"\nNothing to Display\n";
    }else{
        cout<<"\nThe contents of list\n\n";
        while(p!=NULL){
            cout<<p->info<<endl;
            p = p->next;
        }
    }
    
}

//Runs in O(N) Time, where N is the number of elements
void LinkedList::DeleteDuplicates(){
    
    unordered_map<int, bool> table;
    
    node *previous = NULL;
    node *current = firstNode;
    
    while(current != NULL){
        if(table.count(current->info)){
            previous->next = current->next;
        } else {
            table.emplace(current->info, true);
            previous = current;
        }
        current = current->next;
    }
}

//Runs in O(1) space but O(n^2) time
void LinkedList::DeleteDuplicatesNoBuffer(){
    
    if(firstNode == NULL) return;
    
    node *current = new node;
    node *runner = new node;
    
    current = firstNode;
    
    while(current != NULL){
        //Remove all future nodes that are duplicates
        runner = current;
        while(runner->next != NULL){
            if(runner->next->info == current->info){
                runner->next = runner->next->next;
            } else {
                runner = runner->next;
            }
        }
        
        current = current->next;
    }
}

int LinkedList::GetNthToLastNode(int k){
    
    if(k<=0) return NULL;
    
    node *p1 = firstNode;
    node *p2 = firstNode;
    
    for(int i=0; i<k-1; i++){
        if(p2 == NULL) return NULL;
        p2 = p2->next;
    }
    
    while(p2->next!=NULL){
        p1 = p1->next;
        p2 = p2->next;
    }
    
    return p1->info;
    
}

void SeedLinkedList(LinkedList &linkedList, int size)
{
    int counter = 0;
    while(counter < size)
    {
        int randomNumber = rand() % 100 + 1;
        linkedList.AppendElement(randomNumber);
        counter+=1;
    }
}

int main(int argc, const char * argv[]) {
    
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
    
    LinkedList linkedList;
    SeedLinkedList(linkedList, 10);
    
    
    linkedList.Display();
    int choice;
    
    while(1){
        int data;
        cout<<"\n1. Insert at the begining"<<endl;
        cout<<"2. Insert at the end"<<endl;
        cout<<"3. Insert before node"<<endl;
        cout<<"4. Insert After node"<<endl;
        cout<<"5. Delete first element"<<endl;
        cout<<"6. Delete last element"<<endl;
        cout<<"7. Delete before node"<<endl;
        cout<<"8. Delete after node"<<endl;
        cout<<"9. Delete Duplicates"<<endl;
        cout<<"10.Delete Duplicates With No Buffer"<<endl;
        cout<<"11. Find Nth To Last Element (Iterative)"<<endl;
        cout<<"12. Exit"<<endl;
        cout<<"Enter the option: ";
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"\nEnter data to Insert: ";
                cin>>data;
                linkedList.InsertAtFront(data);
                linkedList.Display();
                break;
            case 2:
                cout<<"Enter data to Insert: ";
                cin>>data;
                linkedList.AppendElement(data);
                linkedList.Display();
                break;
            case 3:
                int targetBeforeValue;
                int newElementToInsertBefore;
                cout << "Enter target node value: ";
                cin >> targetBeforeValue;
                cout << "Enter new element value: ";
                cin >> newElementToInsertBefore;
                if(linkedList.InsertBeforeNode(targetBeforeValue, newElementToInsertBefore)){
                    linkedList.Display();
                } else {
                    cout << "Target Value Not Found";
                }
                break;
            case 4:
                int targetAfterValue;
                int newElementToInsertAfter;
                cout << "Enter target node value: ";
                cin >> targetAfterValue;
                cout << "Enter new element value: ";
                cin >> newElementToInsertAfter;
                if(linkedList.InsertAfterNode(targetAfterValue, newElementToInsertAfter)){
                    linkedList.Display();
                } else {
                    cout << "Cannot Insert, target node value not found";
                }
                break;
            case 5:
                if(linkedList.DeleteFirstElement()){
                    linkedList.Display();
                } else {
                    cout << "\nCannot delete, List is empty\n";
                }
                break;
            case 6:
                if(linkedList.DeleteLastElement()){
                    linkedList.Display();
                }else{
                    cout << "\nCannot delete, list is empty\n";
                }
                break;
            case 7:
                int targetDeleteBeforeValue;
                cout << "Enter target node value: ";
                cin >> targetDeleteBeforeValue;
                if(linkedList.DeleteBeforeNode(targetDeleteBeforeValue)){
                    linkedList.Display();
                } else{
                    linkedList.Display();
                    cout << "\nCannot delete before target, either list is empty or there is only one element or the target does not exist\n";
                }
                break;
            case 8:
                int targetDeleteAfterValue;
                cout << "Enter target node value: ";
                cin >> targetDeleteAfterValue;
                if(linkedList.DeleteAfterNode(targetDeleteAfterValue)){
                    linkedList.Display();
                }else{
                    linkedList.Display();
                    cout << "\nCannot delete element after target, either the list is empty or the target is the last value in the list\n";
                }
                break;
            case 9:
                linkedList.DeleteDuplicates();
                linkedList.Display();
                break;
            case 10:
                linkedList.DeleteDuplicatesNoBuffer();
                linkedList.Display();
                break;
            case 11:
                int k;
                cout << "Enter a value for k, where k is the nth to last node in a list: ";
                cin >> k;
                cout << "\nThe "<< k << "th to last element is " << linkedList.GetNthToLastNode(k) << endl;
                break;
            case 12:
                exit(0);
                break;
        }
    }
    
    
    return 0;
}






