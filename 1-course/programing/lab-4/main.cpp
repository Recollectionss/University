//
//  main.cpp
//  Лаба 4(2 семестр)
//
//  Created by Илья Гончаренко on 22.05.2023.
//

#include <iostream>
using namespace std;
// Data structure for storing binary tree packages
struct Node
{
    int data;
    Node *left, *right;
 
    Node(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
};



 
// Helper function for printing a given doubly linked list
void printDLL(Node* &head)
{
    Node* curr = head;
    while (curr != nullptr)
    {
        cout << curr->data << " ";
        curr = curr->right;
    }
}
 
// Function to convert a given binary tree to a doubly linked list in place
// by normal traversal in order
void convert(Node* root, Node* &head)
{
    // if tree is empty
    if (root == nullptr) {
        return;
    }
 
    // left subtree recursion
    convert(root->left, head);
    root->left = nullptr;
 
    // saving the correct child
    Node* right = root->right;
 
    // insert the current node at the beginning of the doubly linked list
    root->right = head;
    if (head != nullptr) {
        head->left = root;
    }
 
    head = root;
 
    // right subtree recursion
    convert(right, head);
}
 
// Function to reverse a doubly linked list
void reverse(Node*& head)
{
    Node* prev = nullptr;
    Node* current = head;
 
    while (current)
    {
        swap(current->left, current->right);
        prev = current;
        current = current->left;
    }
 
    if (prev != nullptr) {
        head = prev;
    }
}
 
// The main function for converting the given binary tree into
// doubly linked list
void convert(Node* root)
{
    // start of doubly linked list
    Node* head = nullptr;
 
    // convert the above binary tree to a doubly linked list
    convert(root, head);
 
    //reverse linked list
    reverse(head);
 
    // function print
    printDLL(head);
}

int main()
{
    /* Tree:
              1
            /   \
           /     \
          2       3
         / \     / \
        4   5   6   7
    */
 
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
 
    convert(root);
    cout<<'\n';
    return 0;
}
