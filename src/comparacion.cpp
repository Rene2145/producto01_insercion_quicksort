#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;

void insercionDirecta(int datos[],int n,int &comparaciones);
void quicksort(int datos[],int izquierda,int derecha,int &comparaciones,int &intercambios);

int main() {
    const int MAX=500;
    int n=0;
    int original[MAX],insercion[MAX],rapido[MAX];
    int compInsercion=0,compQuick=0,interQuick=0;
    cout<<"Ingresa la cantidad de numeros: ";
    if(!(cin>>n)||n<1||n>MAX){
        cout<<"Es una cantidad invalida"<<endl;
        return 0;
    }
    for(int i=0;i<n;i++){
        cout<<"- Numero "<<"( "<<i+1<<" )"<<": ";
        if(!(cin>>original[i])){
            cout<<"No es un dato valido"<<endl;
            return 0;
        }
        insercion[i]=original[i];
        rapido[i]=original[i];
    }

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    insercionDirecta(insercion,n,compInsercion);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    long long tiempoInsercion=chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
    cout<<"\n+-------------------+"<<endl;
	cout<<"| INSERCION DIRECTA |"<<endl;
    cout<<"+-------------------+"<<endl;
    for(int i=0;i<n;i++) cout<<insercion[i]<<" ";
    cout<<"\nTime difference = ";
    cout<<chrono::duration_cast<chrono::milliseconds>(end - begin).count()<<"[ms]"<<endl;
    cout<<"Time difference = ";
    cout<<chrono::duration_cast<chrono::microseconds>(end - begin).count()<<"[us]"<<endl;
    cout<<"Time difference = ";
    cout<<chrono::duration_cast<chrono::nanoseconds>(end - begin).count()<<"[ns]"<<endl;
    cout<<"Comparaciones: "<<compInsercion<<endl;
	
	cout<<endl;
	
	begin=chrono::steady_clock::now();
    quicksort(rapido,0,n-1,compQuick,interQuick);
    end=chrono::steady_clock::now();
    long long tiempoQuick=chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
    cout<<"\n+-------------------+"<<endl;
    cout<<"|     QUICKSORT     |"<<endl;
    cout<<"+-------------------+"<<endl;
    for(int i=0;i<n;i++) cout<<rapido[i]<<" ";
    cout<<"\nTime difference = ";
    cout<<chrono::duration_cast<chrono::milliseconds>(end - begin).count()<<"[ms]"<<endl;
    cout<<"Time difference = ";
    cout<<chrono::duration_cast<chrono::microseconds>(end - begin).count()<<"[us]"<<endl;
    cout<<"Time difference = ";
    cout<<chrono::duration_cast<chrono::nanoseconds>(end - begin).count()<<"[ns]"<<endl;
    cout<<"Comparaciones: "<<compQuick<<endl;
    cout<<"Intercambios: "<<interQuick<<endl;
    
	ofstream archivo("pruebas_manuales.csv");
	if(archivo.is_open()){
	    archivo<<"algoritmo,n,tiempo_ns,comparaciones,intercambios\n";
	    archivo<<"Insercion,"<<n<<","<<tiempoInsercion<<","<<compInsercion<<",0\n";
	    archivo<<"QuickSort,"<<n<<","<<tiempoQuick<<","<<compQuick<<","<<interQuick<<"\n";
	    archivo.close();
	    cout<<"\nResultados guardados en CSV"<<endl;
	}else{
	    cout<<"\nError al guardar el archivo"<<endl;
	}  
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

void quicksort(int datos[],int izquierda,int derecha,int &comparaciones,int &intercambios){
    if(izquierda>=derecha) return;
    int i=izquierda;
    int j=derecha;
    int pivote=datos[(izquierda+derecha)/2];
    while(i<=j){
        while(datos[i]<pivote){
            i++;
            comparaciones++;
        }
        comparaciones++;
        while(datos[j]>pivote){
            j--;
            comparaciones++;
        }
        comparaciones++;
        if(i<=j){
            int aux=datos[i];
            datos[i]=datos[j];
            datos[j]=aux;
            intercambios++;
            i++;
            j--;
        }
    }
    if(izquierda<j) quicksort(datos,izquierda,j,comparaciones,intercambios);
    if(i<derecha) quicksort(datos,i,derecha,comparaciones,intercambios);
}
