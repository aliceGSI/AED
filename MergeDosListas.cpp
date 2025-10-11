#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

void push_back(Node*& head, int val)
{
    Node* nuevo = new Node;
    nuevo->data = val;
    nuevo->next = 0;
    if (!head)
    {
        head = nuevo;
        return;
    }
    Node* temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = nuevo;
}



void merge(Node*& A, Node*& B)
{
    if (!B)
        return;
    if (!A)
    {
        A = B;
        B = 0;
        return;
    }

    Node* pA = A;
    Node* pB = B;
    Node* tail = 0;

    if (pA->data <= pB->data)
    {
        A = pA;
        pA = pA->next;
    }
    else
    {
        A = pB;
        pB = pB->next;
    }

    tail = A;

    while (pA && pB)
    {
        if (pA->data <= pB->data)
        {
            tail->next = pA;
            pA = pA->next;
        }
        else
        {
            tail->next = pB;
            pB = pB->next;
        }
        tail = tail->next;
    }

    if (pA)
        tail->next = pA;

    if (pB)
        tail->next = pB;

    B = 0;
}
void print(Node* head)
{
    if (!head)
    {
        cout << "Lista vacia" << endl;
        return;
    }
    Node* temp = head;
    while (temp)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void deleteList(Node*& head)
{
    Node* current = head;
    while (current)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = 0;
}
int main()
{
    Node* A = 0;
    Node* B = 0;

    push_back(A, 1);
    push_back(A, 5);
    push_back(A, 8);
    push_back(A, 12);
    push_back(A, 15);
    cout << "Lista A: ";
    print(A);

    push_back(B, 2);
    push_back(B, 4);
    push_back(B, 6);
    push_back(B, 10);
    push_back(B, 14);
    push_back(B, 20);
    cout << "Lista B: ";
    print(B);

    cout << "merge(A, B)\n" << endl;
    merge(A, B);

    cout << "Lista A merge: ";
    print(A);
    cout << "Lista B merge: ";
    print(B);

    deleteList(A);

    return 0;
}