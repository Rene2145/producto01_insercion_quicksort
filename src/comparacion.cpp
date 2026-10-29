#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
using namespace std;

void insercionDirecta(int datos[],int n,int &comparaciones);
void quicksort(int datos[],int izquierda,int derecha,int &comparaciones,int &intercambios);

int main() {
    const int MAX=500;
    int n=0;
    int original[MAX],insercion[MAX],rapido[MAX];
    int compInsercion=0,compQuick=0,interQuick=0;
	int opcion;
	cout<<endl;
	cout<<"1) Numeros manuales"<<endl;
	cout<<"2) Numeros aleatorios"<<endl;
	cout<<"3) Numeros ascendentes"<<endl;
	cout<<"4) Numeros descendentes"<<endl;
	cout<<"Elige una opcion: ";
	cin>>opcion;
	if(!cin||opcion<1||opcion>4){
	    cout<<"No es una opcion valida"<<endl;
	    return 0;
	}
    
    cout<<"Ingresa la cantidad de numeros: ";
    if(!(cin>>n)||n<1||n>MAX){
        cout<<"No es una cantidad valida"<<endl;
        return 0;
    }

	srand(12345);
	for(int i=0;i<n;i++){
	    if(opcion==1){
	        cout<<"Numero "<<i+1<<": ";
	        if(!(cin>>original[i])){
	            cout<<"Dato invalido"<<endl;
	            return 0;
	        }
	    }else if(opcion==2){
	        original[i]=rand()%10000;
	    }else if(opcion==3){
	        original[i]=i+1;
	    }else{
	        original[i]=n-i;
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
    
	ofstream archivo("results/pruebas_manuales.csv");
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
