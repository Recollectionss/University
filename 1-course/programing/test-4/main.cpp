//
//  main.cpp
//  Практика тест4
//
//  Created by Илья Гончаренко on 07.01.2023.
//
#include <iostream>

using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int data) {
        this->data = data;
        left = right = nullptr;
    }
};

void convertToDoublyLinkedList(TreeNode* node, TreeNode** head_ref, TreeNode** tail_ref) {
    if (node == nullptr) {
        return;
    }

    TreeNode* left = node->left;
    TreeNode* right = node->right;

    convertToDoublyLinkedList(node->left, head_ref, tail_ref);

    if (*head_ref == nullptr) {
        *head_ref = node;
    }

    node->left = *tail_ref;

    if (*tail_ref != nullptr) {
        (*tail_ref)->right = node;
    }

    *tail_ref = node;

    convertToDoublyLinkedList(node->right, head_ref, tail_ref);
}

void printList(TreeNode* node) {
    while (node != nullptr) {
        cout << node->data << " ";
        node = node->right;
    }
}

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    TreeNode* head = nullptr;
    TreeNode* tail = nullptr;

    convertToDoublyLinkedList(root, &head, &tail);

    printList(head);

    return 0;
}
