#include <iostream>
using namespace std;

class queue
{
private:
    int* cola;
    int* head;
    int* tail;
    int n_elem;
    int capacity;
public:
    queue(int cap);
    ~queue();
    bool push(int val);
    bool pop(int& val);
    bool lleno();
    bool vacio();
    void print();
};

queue::queue(int cap)
{
    capacity = cap;
    cola = new int[capacity];
    head = cola;
    tail = cola;
    n_elem = 0;
}

queue::~queue()
{
    delete[] cola;
}

bool queue::push(int val)
{
    if (lleno())
    {
        return false;
    }
    *tail = val;
    tail++;
    n_elem++;
    if (tail == cola + capacity)
    {
        tail = cola;
    }
    return true;
}

bool queue::pop(int& val)
{
    if (vacio()) {
        return false;
    }
    val = *head;
    head++;
    n_elem--;
    if (head == cola + capacity)
    {
        head = cola;
    }
    return true;
}

bool queue::lleno()
{
    return n_elem == capacity;
}

bool queue::vacio()
{
    return n_elem == 0;
}

void queue::print()
{
    if (vacio()) {
        cout << "Cola vacia" << endl;
        return;
    }
    int* p = head;
    for (int i = 0; i < n_elem; i++)
    {
        cout << *p << " ";
        p++;
        if (p == cola + capacity)
        {
            p = cola;
        }
    }
    cout << endl;
}

int main() 
{
    queue q(10);
    int x;
    cout << "   DEMOSTRACION COLA CIRCULAR " << endl;

    cout << "\nInsertando 10 elementos" << endl;
    for (int i = 1; i <= 10; i++)
    {
        q.push(i);
        cout << "Encolado: " << i << " -> ";
        q.print();
    }

    cout << "\nDesencolando 5 num" << endl;
    for (int i = 0; i < 5; i++)
    {
        if (q.pop(x)) {
            cout << "Se desencolo: " << x << " -> ";
            q.print();
        }
    }

    cout << "\nInsertando 3 elementos mas (11, 12, 13)" << endl;
    for (int i = 11; i <= 13; i++)
    {
        q.push(i);
        cout << "Encolado: " << i << " -> ";
        q.print();
    }

    cout << "\nfin" << endl;
    q.print();
    return 0;
}
