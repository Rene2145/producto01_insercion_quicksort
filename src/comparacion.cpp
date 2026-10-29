#include <iostream>
#include <chrono>

using namespace std;

void insercionDirecta(int datos[], int n, int &comparaciones);
void quicksort(int datos[], int izquierda, int derecha, int &comparaciones, int &intercambios);

int main() {
    const int n = 4;
    int original[n] = {5, 2, 4, 1};
    int insercion[n], rapido[n];
    
    int compInsercion = 0;
    int compQuick = 0;
    int interQuick = 0;

    for(int i=0; i<n; i++) {
        insercion[i] = original[i];
        rapido[i] = original[i];
    }

    auto inicio = chrono::steady_clock::now();
    insercionDirecta(insercion, n, compInsercion);
    auto fin = chrono::steady_clock::now();
    double tiempoInsercion = chrono::duration<double, milli>(fin-inicio).count();

    inicio = chrono::steady_clock::now();
    quicksort(rapido, 0, n-1, compQuick, interQuick);
    fin = chrono::steady_clock::now();
    double tiempoQuick = chrono::duration<double, milli>(fin-inicio).count();

    cout << ">> INSERCION DIRECTA <<" << endl;
    cout << "Arreglo: ";
    for(int i=0; i<n; i++) cout << insercion[i] << " ";
    cout << "\nTiempo: " << tiempoInsercion << " ms";
    cout << "\nComparaciones: " << compInsercion << endl;

    cout << "\n=== QUICKSORT ===" << endl;
    cout << "Arreglo: ";
    for(int i=0; i<n; i++) cout << rapido[i] << " ";
    cout << "\nTiempo: " << tiempoQuick << " ms";
    cout << "\nComparaciones: " << compQuick;
    cout << "\nIntercambios: " << interQuick << endl;

    return 0;
}

void insercionDirecta(int datos[], int n, int &comparaciones) {
    for(int i=1; i<n; i++) {
        int clave = datos[i];
        int j = i-1;

        while(j>=0) {
            comparaciones++;
            if(datos[j]>clave) {
                datos[j+1] = datos[j];
                j--;
            } else {
                break;
            }
        }
        datos[j+1] = clave;
    }
}

void quicksort(int datos[], int izquierda, int derecha, int &comparaciones, int &intercambios) {
    if(izquierda>=derecha) return;

    int i = izquierda;
    int j = derecha;
    int pivote = datos[(izquierda+derecha)/2];

    while(i<=j) {
        while(datos[i]<pivote) {
            i++;
            comparaciones++;
        }
        comparaciones++;

        while(datos[j]>pivote) {
            j--;
            comparaciones++;
        }
        comparaciones++;

        if(i<=j) {
            int aux = datos[i];
            datos[i] = datos[j];
            datos[j] = aux;
            intercambios++;
            i++;
            j--;
        }
    }

    if(izquierda<j) {
        quicksort(datos, izquierda, j, comparaciones, intercambios);
    }
    if(i<derecha) {
        quicksort(datos, i, derecha, comparaciones, intercambios);
    }
}
