#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// function contains data and pointer to next node

class Node
{
public:
    int data;
    Node *next;

    Node(int n)
    {
        this->data = n;
        this->next = nullptr;
    }
};

// insertion at begininng

Node *insert_begin(Node *node, int n)
{
    Node *n2 = new Node(n);
    n2->next = node;

    node = n2;

    return node;
}

// insertion at position

Node *insert_at_pos(Node *node, int n, int pos)
{
    Node *prev = node;
    Node *curr = node;

    while (pos-- > 0 && curr != nullptr)
    {
        curr = curr->next;
        prev = curr;
    }
    if (curr != nullptr)
    {
        Node *n1 = new Node(n);
        prev->next = n1;
        n1->next = curr;
    }

    return node;
}

Node *insert_at_end(Node *node, int n)
{
    Node *n1 = new Node(n);
    Node *curr = node;

    while (curr->next != nullptr)
    {
        curr = curr->next;
    }
    curr->next = n1;

    return node;
}

// traversal of linked list
void linkedListTraversal(Node *head)
{
    while (head != nullptr)
    {
        cout << head->data << endl;
        head = head->next;
    }
}

// length of linked list
int length_ll(Node *node)
{
    int count = 0;
    Node *curr = node;
    while (curr != nullptr)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

// delete with data
Node *delete_data(Node *node, int n)
{
    if (node == nullptr)
        return nullptr;

    if (node->data == n)
    {
        Node *curr = node;
        node = node->next;
        delete curr;
    }

    Node *prev = nullptr;
    Node *curr = node;
    Node *next_t = node->next;

    while (curr->data != n && next_t != node)
    {
        prev = curr;
        curr = curr->next;
        next_t = curr->next;
    }

    prev->next = next_t;
    curr->next = nullptr;

    return node;
}

// delete at particular position.
Node *delete_pos(Node *node, int n)
{
    if (node == nullptr)
        return nullptr;

    Node *prev = nullptr;
    Node *curr = node;
    Node *next_t = node->next;

    while (n-- > 0 && next_t != nullptr)
    {
        prev = curr;
        curr = curr->next;
        next_t = curr->next;
    }

    prev->next = next_t;

    curr->next = nullptr;
    delete curr;

    return node;
}

int mains()
{
    Node *head;
    head = new Node(5);
    Node *n1;
    n1 = new Node(4);
    Node *n2;
    n2 = new Node(16);
    Node *n3;
    n3 = new Node(17);
    Node *n4;
    n4 = new Node(18);

    head->next = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;

    linkedListTraversal(head);

    return 0;
}