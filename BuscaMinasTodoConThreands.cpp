#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
using namespace std;

struct coord
{
    int i;
    int j;
};

mutex mtx; 

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

void inicializarRango(char** tablero, int inicio, int fin)
{
    for (int k = inicio; k < fin; k++)
    {
        int i = k / 10;
        int j = k % 10;
        *(*(tablero + i) + j) = '.';
    }
}

void colocarMinasRango(char** tablero, int cantMinasPorThread, int& minasTotalesColocadas, int totalMinasDeseadas)
{
    int minasColocadas = 0;
    while (minasColocadas < cantMinasPorThread && minasTotalesColocadas < totalMinasDeseadas)
    {
        int x = rand() % 10;
        int y = rand() % 10;

        mtx.lock(); 
        if (*(*(tablero + x) + y) != '*')
        {
            *(*(tablero + x) + y) = '*';
            minasColocadas++;
            minasTotalesColocadas++;
        }
        mtx.unlock();
    }
}

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

    char** tablero = new char* [10];
    for (int i = 0; i < 10; i++)
    {
        *(tablero + i) = new char[10];
    }

    cout << "=== Buscaminas con 4 Threads ===" << endl;

    int totalCeldas = 10 * 10;
    int bloque = totalCeldas / 4;

    cout << "=== Inicializando tablero con threads ===" << endl;
    thread tInit1(inicializarRango, tablero, 0, bloque);
    thread tInit2(inicializarRango, tablero, bloque, 2 * bloque);
    thread tInit3(inicializarRango, tablero, 2 * bloque, 3 * bloque);
    thread tInit4(inicializarRango, tablero, 3 * bloque, totalCeldas);

    tInit1.join();
    tInit2.join();
    tInit3.join();
    tInit4.join();

    cout << "=== Pantalla 1: Tablero en blanco ===" << endl;
    dibujarTablero(tablero);

    const int TOTAL_MINAS = 20;
    int minasTotalesColocadas = 0;
    int minasPorThread = TOTAL_MINAS / 4;

    cout << "=== Colocando minas con threads ===" << endl;
    thread tMinas1(colocarMinasRango, tablero, minasPorThread, ref(minasTotalesColocadas), TOTAL_MINAS);
    thread tMinas2(colocarMinasRango, tablero, minasPorThread, ref(minasTotalesColocadas), TOTAL_MINAS);
    thread tMinas3(colocarMinasRango, tablero, minasPorThread, ref(minasTotalesColocadas), TOTAL_MINAS);
    thread tMinas4(colocarMinasRango, tablero, minasPorThread, ref(minasTotalesColocadas), TOTAL_MINAS);

    tMinas1.join();
    tMinas2.join();
    tMinas3.join();
    tMinas4.join();

    cout << "=== Pantalla 2: Con minas (*) ===" << endl;
    dibujarTablero(tablero);

    cout << "=== Contando minas alrededor con threads ===" << endl;
    thread tContar1(contarMinasRango, tablero, 0, bloque);
    thread tContar2(contarMinasRango, tablero, bloque, 2 * bloque);
    thread tContar3(contarMinasRango, tablero, 2 * bloque, 3 * bloque);
    thread tContar4(contarMinasRango, tablero, 3 * bloque, totalCeldas);

    tContar1.join();
    tContar2.join();
    tContar3.join();
    tContar4.join();

    cout << "=== Pantalla 3: Con numeros ===" << endl;
    dibujarTablero(tablero);

    cout << "Cantidad de minas: " << contarMinas(tablero) << endl;

    for (int i = 0; i < 10; i++)
    {
        delete[] * (tablero + i);
    }
    delete[] tablero;

    return 0;
}