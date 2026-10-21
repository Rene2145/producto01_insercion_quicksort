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

    cout << "\nInsercion directa: ";
    for (int i = 0; i < n; i++) {
        cout << insercion[i] << " ";
    }

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
