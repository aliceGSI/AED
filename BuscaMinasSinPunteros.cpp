#include <iostream>
using namespace std;

//Busca Minas sin punteros (recorrido sin punteros)

struct coord
{
    int i;
    int j;
};
void dibujarTablero(char** tablero)
{
    for (int i = 0; i < 10; i++)
    {
        cout << "|";
        for (int j = 0; j < 10; j++)
        {
            cout << " " << tablero[i][j] << " ";
        }

        cout << "|";
        cout << endl;
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

        if (tablero[x][y] != '*')
        {
            tablero[x][y] = '*';
            minasColocadas++;
        }
    }
}

void ContnumMinas(char** tablero)
{

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (tablero[i][j] == '*')
            {
                continue;
            }
            int contador = 0;

            coord alrededor[8] =
            {
                {i - 1, j - 1}, {i - 1 , j}, {i - 1, j + 1},
                {i, j - 1}, {i, j + 1 },
                {i + 1, j - 1},{i + 1, j},{i + 1, j + 1}
            };

            for (coord cActual : alrededor)
            {
                //limites
                if (cActual.i >= 0 && cActual.i < 10 && cActual.j >= 0 && cActual.j < 10)
                {
                    if (tablero[cActual.i][cActual.j] == '*')
                    {
                        contador++;
                    }
                }
            }
            if (contador > 0)
            {
                tablero[i][j] = '0' + contador;
            }
            else
            {
                tablero[i][j] = '0';
            }
        }
    }
}

int main()
{
    srand(time(0));
    char** tablero = new char* [10];
    for (int i = 0; i < 10; i++)
    {
        tablero[i] = new char[10];
        for (int j = 0; j < 10; j++)
        {
            tablero[i][j] = '.';
        }
    }

    cout << "=== Pantalla 1: Tablero en blanco ===" << endl;
    dibujarTablero(tablero);

    asteriscos(tablero, 15);
    cout << "=== Pantalla 2: Con minas (*) ===" << endl;
    dibujarTablero(tablero);

    ContnumMinas(tablero);
    cout << "=== Pantalla 3: Con numeros ===" << endl;
    dibujarTablero(tablero);

    cout << "=== Pantalla 4: Resultado final ===" << endl;
    dibujarTablero(tablero);

    // Liberar memoria
    for (int i = 0; i < 10; i++)
        delete[] tablero[i];
    delete[] tablero;
    return 0;
}