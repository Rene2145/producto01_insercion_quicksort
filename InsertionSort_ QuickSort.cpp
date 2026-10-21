#include <iostream>
using namespace std;

void insercionDirecta(int datos[], int n);
void quicksort(int datos[], int izquierda, int derecha);

int main() {
    int original[4] = {5, 2, 4, 1};
    int insercion[4];
    int rapido[4];
    int n = 4;

    cout << "Original: ";
    for (int i = 0; i < n; i++) {
        cout << original[i] << " ";
        insercion[i] = original[i];
        rapido[i] = original[i];
    }

    insercionDirecta(insercion, n);
    quicksort(rapido, 0, n - 1);

    cout << "\nInsercion directa: ";
    for (int i = 0; i < n; i++) {
        cout << insercion[i] << " ";
    }

    cout << "\nQuickSort: ";
    for (int i = 0; i < n; i++) {
        cout << rapido[i] << " ";
    }
    cout << "\n";

    return 0;
}

void insercionDirecta(int datos[], int n) {
    for (int i = 1; i < n; i++) {
        int clave = datos[i];
        int j = i - 1;

        while (j >= 0 && datos[j] > clave) {
            datos[j + 1] = datos[j];
            j--;
        }
        datos[j + 1] = clave;
    }
}

void quicksort(int datos[], int izquierda, int derecha) {
    if (izquierda >= derecha) {
        return; 
    }

    int i = izquierda;
    int j = derecha;
    int centro = izquierda + (derecha - izquierda) / 2;
    int pivote = datos[centro];

    while (i <= j) {
        while (datos[i] < pivote) {
            i++;
        }
        while (datos[j] > pivote) {
            j--;
        }

        if (i <= j) {
            if (i < j) {
                int auxiliar = datos[i];
                datos[i] = datos[j];
                datos[j] = auxiliar;
            }
            i++;
            j--;
        }
    }
    if (izquierda < j) {
        quicksort(datos, izquierda, j);
    }
    if (i < derecha) {
        quicksort(datos, i, derecha);
    }
}

