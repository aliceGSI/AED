#include <iostream>
#include <cstring>
#include <thread>
using namespace std;
struct c
{
    int i;
    int j;
};
void dibujarTablero(char tablero[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        cout << "|";
        for (int j = 0; j < 10; j++)
        {
            cout << " " << tablero[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << endl;
}

bool horizontal(char tablero[10][10], char* palabra, int& contador)
{
    int l = strlen(palabra);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j <= 10 - l; j++)
        {
            int k;
            for ( k= 0; k < l; k++)
            {
                if (tablero[i][j + k] != palabra[k])
                {
                    break;
                }
                
            }

            if (k == l)
            {
                contador++;
            }
            for (k = 0; k < l; k++)
            {
                if (tablero[i][j + k] != palabra[l - 1 - k])
                {
                    break;
                }
            }
            if (k == l)
            {
                contador++;
            }
        }
    }

    return (contador > 0);

}

bool vertical(char tablero[10][10], char* palabra, int& contador)
{
    int l = strlen(palabra);
    for (int i = 0; i <= 10-l; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int k;
            for ( k = 0; k < l; k++)
            {
                if (tablero[i + k][j] != palabra[k])
                {
                    break;
                }
            }
            if (k == l)
            {
                contador++;
            }
            for (k = 0; k < l; k++) 
            {
                if (tablero[i + k][j] != palabra[l - 1 - k]) 
                {
                    break;
                }
            }
            if (k == l)
            {
                contador++;
            }
        }
    }
    return (contador > 0);
}

bool diagonal(char tablero[10][10], char* palabra, int& contador)
{
    int l = strlen(palabra);
    for (int i = 0; i <= 10-l; i++)
    {
        for (int j = 0; j <= 10 - l; j++)
        {
            int k;
            for ( k = 0; k < l; k++)
            {
                if (tablero[i + k][j+k] != palabra[k])
                {
                    break;
                }
            }

            if (k == l)
            {
                contador++;
            }

            for (k = 0; k < l; k++)
            {
                if (tablero[i + k][j + k] != palabra[l - 1 - k]) 
                {
                    break;
                }
            }
            if (k == l)
            {
                contador++;
            }
        }
    }
    return (contador > 0);

}
void buscarPalabraSinT(char tablero[10][10], char* palabra)
{
    int cH = 0, cV = 0, cD = 0;

    horizontal(tablero, palabra, cH);
    vertical(tablero, palabra, cV);
    diagonal(tablero, palabra, cD);

    cout << "\nPalabra: " << palabra << endl;
    cout << "Horizontal: " << cH << endl;
    cout << "Vertical:   " << cV << endl;
    cout << "Diagonal:   " << cD << endl;
    cout << "TOTAL:      " << (cH + cV + cD) << endl;
}
void buscarPalabra(char tablero[10][10], char* palabra)
{
    int cH = 0, cV = 0, cD = 0;

    thread th1(horizontal, tablero, palabra, ref(cH));
    thread th2(vertical, tablero, palabra, ref(cV));
    thread th3(diagonal, tablero, palabra, ref(cD));

    th1.join();
    th2.join();
    th3.join();

    cout << "\nPalabra: " << palabra << endl;
    cout << "Horizontal: " << cH << endl;
    cout << "Vertical:   " << cV << endl;
    cout << "Diagonal:   " << cD << endl;
    cout << "TOTAL:      " << (cH + cV + cD) << endl;
}

int main()
{
    char tablero[10][10] = {
        {'T','P','P','A','P','T','P','P','P','T'},
        {'O','P','A','T','A','P','O','Z','O','J'},
        {'S','A','T','A','T','O','T','A','Z','I'},
        {'A','T','A','P','A','P','A','T','O','S'},
        {'P','A','T','A','N','O', 'D','O','T','N'},
        {'T','A','A','P','A','T','I','P','A','P'},
        {'R','R','N','A','D','O','T','A','P','O'},
        {'E','D','N','T','A','P','O','T', 'A','T'},
        {'N','I','I','A','T','I','T','A','P','A'},
        {'P','S','S','N','T','T','T','P','A','P'}
    };
    /*
    char palabra[] = "PAN";
    int c = 0;
    dibujarTablero(tablero);

    if (horizontal(tablero, palabra, c))
        cout << "La palabra '" << palabra << "' aparece " << c << " veces horizontalmente.\n";

    if (vertical(tablero, palabra, c))
        cout << "La palabra '" << palabra << "' aparece " << c << " veces verticalmente.\n";

    if (diagonal(tablero, palabra, c))
        cout << "La palabra '" << palabra << "' aparece " << c << " veces en diagonal.\n";
    */

    /*
    char palabra[] = "PAN";

    int cH = 0, cV = 0, cD = 0;

    dibujarTablero(tablero);

    
    thread th1(horizontal, tablero, palabra, ref(cH));
    thread th2(vertical, tablero, palabra, ref(cV));
    thread th3(diagonal, tablero, palabra, ref(cD));

    th1.join();
    th2.join();
    th3.join();
    
    cout << "Palabra: ";
    for (int i = 0; i < strlen(palabra); i++)
    {
        cout << palabra[i] << endl;
    }
    cout << "Horizontal: " << cH << endl;
    cout << "Vertical: " << cV << endl;
    cout << "Diagonal: " << cD << endl;
    */
    dibujarTablero(tablero);

    char palabra1[] = "PATAN";
    char palabra2[] = "PATA";
    char palabra3[] = "TAPA";
    char palabra4[] = "PATO";
    char palabra5[] = "TIPA";

    buscarPalabra(tablero, palabra1);
    buscarPalabra(tablero, palabra2);
    buscarPalabra(tablero, palabra3);
    buscarPalabra(tablero, palabra4);
    buscarPalabra(tablero, palabra5);

    return 0;
}