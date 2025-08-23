#include <iostream>
#include <thread>
using namespace std;

/*
void mostrarTablero(char* tablero)
{
    for (int i = 0; i < 10; i++)
    {
        cout << "|";
        for (int j = 0; j < 10; j++)
        {
            cout << " " <<*(tablero + i * 10 + j) <<" ";
        }
        cout << "|";
        cout << endl;
    }
}

void ponerMinas(char* tablero, int cant)
{
    for (int k = 0; k < cant; k++)
    {
        int idx = rand() % 100;
        int i = idx / 10;
        int j = idx % 10;
        *(tablero + i * 10 + j) = '*';
    }
}

void inicializarRango(char* tablero, int ini, int fin)
{
    for (int k = ini; k < fin; k++)
    {
        int i = k / 10;
        int j = k % 10;
        *(tablero + i * 10 + j) = '.';
    }
}

*/
struct coord
{
    int i;
    int j;
};
void dibujarTablero(char** tablero)
{
    for (char** fila = tablero; fila < tablero + 10; fila++)
    {
        cout << "|";
        for (char* col = *fila; col < *fila + 10; col++)
        {
            cout << " " << *col << " ";
        }
        cout << "|" << endl;
    }
    cout << endl;
}
void asteriscos(char** tablero, int cantMinas)
{
    int minasColocadas = 0;
    while (minasColocadas < cantMinas)
    {
        int x = rand() % 10;
        int y = rand() % 10;

        if (*(*(tablero + x) + y) != '*')
        {
            *(*(tablero + x) + y) = '*';
            minasColocadas++;
        }
    }
}
//punteros
/*
void ContnumMinas(char** tablero)
{
    for (char** fila = tablero; fila < tablero + 10; fila++)
    {
        for (char* col = *fila; col < *fila + 10; col++)
        {
            if (*col == '*')
            {
                continue;
            }


            int contador = 0;
            int i = fila - tablero;
            int j = col - *fila;

            coord alrededor[8] =
            {
                {i - 1, j - 1}, {i - 1 , j}, {i - 1, j + 1},
                {i, j - 1},  {i, j + 1},
                {i + 1, j - 1},{i + 1, j},{i + 1, j + 1}
            };

            for (coord cActual : alrededor)
            {
                if (cActual.i >= 0 && cActual.i < 10 && cActual.j >= 0 && cActual.j < 10)
                {
                    if (*(*(tablero + cActual.i) + cActual.j) == '*')
                        contador++;
                }
            }

            if (contador > 0)
            {
                *(*(tablero + i) + j) = '0' + contador;
            }
            else
            {
                *(*(tablero + i) + j) = '0';
            }
        }
    }
}
*/
//Threads
void contarMinasRango(char** tablero, int inicio, int fin)
{
    for (int k = inicio; k < fin; k++)
    {
        int i = k / 10;
        int j = k % 10;

        if (*(*(tablero + i) + j) == '*')
        {
            continue;
        }

        int contador = 0;
        coord alrededor[8] =
        {
            {i - 1, j - 1}, {i - 1 , j}, {i - 1, j + 1},
            {i, j - 1},  {i, j + 1},
            {i + 1, j - 1},{i + 1, j},{i + 1, j + 1}
        };

        for (coord cActual : alrededor)
        {
            if (cActual.i >= 0 && cActual.i < 10 && cActual.j >= 0 && cActual.j < 10)
            {
                if (*(*(tablero + cActual.i) + cActual.j) == '*')
                {
                    contador++;
                }
            }
        }

        if (contador > 0)
        {
            *(*(tablero + i) + j) = '0' + contador;
        }
        else
        {
            *(*(tablero + i) + j) = '0';
        }
    }
}

int contarMinas(char** tablero)
{
    int contador = 0;
    for (char** fila = tablero; fila < tablero + 10; fila++)
    {
        for (char* col = *fila; col < *fila + 10; col++)
        {
            if (*col == '*')
            {
                contador++;
            }
        }
    }
    return contador;
}
int main()
{
    srand(time(0));
    /*
    * 
    char tablero[10 * 10];
    mostrarTablero(tablero);
    thread t1(inicializarRango, tablero, 0, 25);
    thread t2(inicializarRango, tablero, 25, 50);
    thread t3(inicializarRango, tablero, 50, 75);
    thread t4(inicializarRango, tablero, 75, 100);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    ponerMinas(tablero, 15);
    mostrarTablero(tablero);
    */
    char** tablero = new char* [10];
    for (int i = 0; i < 10; i++)
    {
        *(tablero + i) = new char[10];
        for (int j = 0; j < 10; j++)
        {
            *(*(tablero + i) + j) = '.';
        }
    }

    cout << "=== Contar minas con Threads ===" << endl;

    cout << "=== Pantalla 1: Tablero en blanco ===" << endl;
    dibujarTablero(tablero);

    asteriscos(tablero, 15);
    cout << "=== Pantalla 2: Con minas (*) ===" << endl;
    dibujarTablero(tablero);

    /*
    ContnumMinas(tablero);
    cout << "=== Pantalla 3: Con numeros Punteros ===" << endl;
    dibujarTablero(tablero);
    */
    int totalCeldas = 10 * 10;
    int bloque = totalCeldas / 4;

    thread t1(contarMinasRango, tablero, 0, bloque);
    thread t2(contarMinasRango, tablero, bloque, 2 * bloque);
    thread t3(contarMinasRango, tablero, 2 * bloque, 3 * bloque);
    thread t4(contarMinasRango, tablero, 3 * bloque, totalCeldas);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << "=== Pantalla 4: Con numeros - Threads ===" << endl;
    dibujarTablero(tablero);

    cout << "Cantidad de minas: " << contarMinas(tablero) << endl;
    for (int i = 0; i < 10; i++)
    {
        delete[] * (tablero + i);
    }
    delete[] tablero;

    return 0;
}
