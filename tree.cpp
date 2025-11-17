#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int x)
    {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

void BFS(Node *node)
{
    queue<Node *> q;

    if (node == nullptr)
        return;

    q.push(node);

    while (q.empty() == false)
    {
        Node *n1 = q.front();
        q.pop();

        cout << n1->data << endl;
        if (n1->left != nullptr)
        {
            q.push(n1->left);
        }
        if (n1->right != nullptr)
        {
            q.push(n1->right);
        }
    }
}

int main()
{
    Node *root = new Node(2);
    root->left = new Node(3);
    root->right = new Node(4);
    root->left->left = new Node(5);

    BFS(root);
}