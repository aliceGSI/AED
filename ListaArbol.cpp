#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
    Node* left;
    Node* right;
};

void push_back(Node*& head, int val)
{
    Node* nuevo = new Node;
    nuevo->data = val;
    nuevo->next = 0;
    nuevo->left = 0;
    nuevo->right = 0;
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

Node* crearArbol(Node*& ini, Node*& fin)
{
    if (!ini) return 0;

    fin = ini;
    while (fin->next) fin = fin->next;

    Node* curr = ini;

    while (curr && curr->next)
    {
        Node* izq = curr;
        Node* der = curr->next;

        if (!der)
            break;

        Node* padre = new Node;
        padre->data = izq->data + der->data;
        padre->next = 0;
        padre->left = izq;
        padre->right = der;

        fin->next = padre;
        fin = padre;

        curr = der->next;

        if (!curr || !curr->next)
        {
            return padre;
        }
    }
    return fin;
}

void printList(Node* head)
{
    if (!head) return;
    
    Node* temp = head;
    while (temp)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void printSpaces(int count)
{
    for (int i = 0; i < count; i++)
        cout << " ";
}

int getHeight(Node* root)
{
    if (!root)
        return 0;
    int leftH = getHeight(root->left);
    int rightH = getHeight(root->right);
    return 1 + (leftH > rightH ? leftH : rightH);
}

void printTreeVisual(Node* root)
{
    if (!root)
        return;

    int h = getHeight(root);

    Node* queue[256];
    int levelStart[20];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;
    levelStart[0] = 0;

    int level = 0;

    while (front < rear && level < h)
    {
        int levelSize = rear - front;
        int spacing = (1 << (h - level - 1)) * 2;
        int firstSpacing = spacing / 2;

        printSpaces(firstSpacing);

        for (int i = 0; i < levelSize; i++)
        {
            Node* current = queue[front++];

            if (current)
            {
                cout << current->data;
                queue[rear++] = current->left;
                queue[rear++] = current->right;
            }
            else
            {
                cout << " ";
                queue[rear++] = 0;
                queue[rear++] = 0;
            }

            if (i < levelSize - 1)
                printSpaces(spacing - 1);
        }
        cout << endl;

        if (level < h - 1)
        {
            printSpaces(firstSpacing - 1);

            int branchFront = levelStart[level];
            for (int i = 0; i < levelSize; i++)
            {
                Node* current = queue[branchFront++];

                if (current && current->left)
                    cout << "/";
                else
                    cout << " ";

                printSpaces(spacing - 2);

                if (current && current->right)
                    cout << "\\";
                else
                    cout << " ";

                if (i < levelSize - 1)
                    printSpaces(2);
            }
            cout << endl;
        }

        levelStart[level + 1] = front;
        level++;
    }
}



int main()
{
    Node* ini = 0;
    Node* fin = 0;

    cout << "Ejemplo 1: 8 elementos (2^3)" << endl;
    push_back(ini, 2);
    push_back(ini, 4);
    push_back(ini, 7);
    push_back(ini, 9);
    push_back(ini, 10);
    push_back(ini, 15);
    push_back(ini, 3);
    push_back(ini, 25);

    cout << "\nLista inicial: ";
    printList(ini);

    Node* raiz = crearArbol(ini, fin);

    cout << "\nLista completa (hojas + padres): ";
    printList(ini);

    cout << "\nArbol visual:" << endl;
    //printTreeVisual(raiz);

    return 0;
}