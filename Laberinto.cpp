#include <iostream>
#include <climits>
using namespace std;

const int N = 10;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

bool esValido(char** tablero, int x, int y)
{
    if (x >= 0 && x < N && y >= 0 && y < N && tablero[x][y] != 'X' && tablero[x][y] != '+')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool llegar(char** tablero, int x, int y)
{
    if (tablero[x][y] == 'B')
    {
        return true;
    }

    tablero[x][y] = '+';

    for (int k = 0; k < 4; k++)
    {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (esValido(tablero, nx, ny))
        {
            if (llegar(tablero, nx, ny))
            {
                return true;
            }
        }
    }

    tablero[x][y] = ' ';
    return false;
}
const int inf = 1000;
int mejor = inf;
char** mejorTablero;

void copiarTablero(char** src, char** dest)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}

void caminoMasCorto(char** tablero, int x, int y, int pasos)
{
    if (tablero[x][y] == 'B')
    {
        if (pasos < mejor)
        {
            mejor = pasos;
            copiarTablero(tablero, mejorTablero);
        }
        return;
    }

    tablero[x][y] = '+';

    for (int k = 0; k < 4; k++)
    {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (esValido(tablero, nx, ny))
        {
            caminoMasCorto(tablero, nx, ny, pasos + 1);
        }
    }

    tablero[x][y] = ' ';
}
/*
void imprimir(char** tablero)
{
    for (int i = 0; i < N; i++)
    {

        cout << "|";
        for (int j = 0; j < N; j++)
        {
            cout << tablero[i][j] << " ";
        }

        cout << "|" << endl;
        
    }
    cout << endl;
}
*/
void imprimir(char** tablero)
{
    cout << " ";
    for (int j = 0; j < N; j++)
        cout << "----";
    cout << "-" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|";
        for (int j = 0; j < N; j++)
        {
            cout << " " << tablero[i][j] << " |";
        }
        cout << endl;

        cout << " ";
        for (int j = 0; j < N; j++)
            cout << "----";
        cout << "-" << endl;
    }
    cout << endl;
}

int main()
{
    char** tablero = new char*[N];
    mejorTablero = new char *[N];
    for (int i = 0; i < N; i++)
    {
        tablero[i] = new char[N];
        mejorTablero[i] = new char[N];
    }

    char temp[N][N] = {
        {'A','X',' ',' ',' ',' ',' ',' ',' ','X'},
        {' ','X',' ',' ',' ',' ','X','X',' ','X'},
        {' ','X',' ','X','X',' ','X','X','X','X'},
        {' ','X',' ','X',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ','X',' ',' ',' ',' ','X','X'},
        {' ','X','X','X','X','X',' ',' ','X',' '},
        {' ',' ',' ',' ','X',' ',' ',' ',' ',' '},
        {' ','X','X',' ','X',' ',' ','X','X','X'},
        {'X','X',' ',' ','X',' ',' ','X',' ',' '},
        {' ',' ',' ','X','X',' ',' ',' ',' ','B'}
    };

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            tablero[i][j] = temp[i][j];
        }
    }

    cout << "Tablero inicial:" << endl;
    imprimir(tablero);

    cout << endl << "llegar a B" << endl;
    if (llegar(tablero, 0, 0))
    {
        imprimir(tablero);
    }
    else
    {
        cout << "No hay camino." << endl;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            tablero[i][j] = temp[i][j];
        }
    }

    cout << endl << "Camino mas corto" << endl;
    caminoMasCorto(tablero, 0, 0, 0);

    if (mejor == inf)
    {
        cout << "No hay camino." << endl;
    }
    else
    {

        imprimir(mejorTablero);
        cout << "Longitud: " << mejor << endl;
    }

    for (int i = 0; i < N; i++)
    {
        delete[] tablero[i];
        delete[] mejorTablero[i];
    }
    delete[] tablero;
    delete[] mejorTablero;

    return 0;
}