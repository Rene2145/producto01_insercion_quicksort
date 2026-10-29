#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
using namespace std;

void insercionDirecta(int datos[],int n,int &comparaciones,int &movimientos);
void quicksort(int datos[],int izq,int der,int &comparaciones,int &intercambios,int nivel,int &profMax);

int main(){
    const int MAX=10000;
    int original[MAX],insercion[MAX],rapido[MAX];
    int opcion,n;
    cout<<"1) Numeros manuales"<<endl;
    cout<<"2) Numeros aleatorios"<<endl;
    cout<<"3) Numeros ascendentes"<<endl;
    cout<<"4) Numeros descendentes"<<endl;
    cout<<"5) Experimentos"<<endl;
    cout<<"Opcion: ";
    if(!(cin>>opcion)||opcion<1||opcion>5){
        cout<<"Opcion invalida"<<endl;
        return 0;
    }
    srand(12345);
    if(opcion==5){
        int tamanos[3]={1000,5000,10000};
        char commit[20];
        cout<<"Commit: ";
        cin.width(20);
        if(!(cin>>commit)) return 0;
        ofstream archivo("results/experimentos.csv");
        if(!archivo.is_open()){
            cout<<"No se pudo guardar el CSV"<<endl;
            return 0;
        }
        archivo<<"algoritmo,n,patron,repeticion,tiempo_ms,comparaciones,intercambios,movimientos,profundidad_recursion,semilla,commit_hash\n";
        for(int t=0;t<3;t++){
            n=tamanos[t];
            for(int patron=2;patron<=4;patron++){
                for(int rep=1;rep<=30;rep++){
                    for(int i=0;i<n;i++){
                        if(patron==2) original[i]=rand()%10000;
                        else if(patron==3) original[i]=i+1;
                        else original[i]=n-i;
                        insercion[i]=original[i];
                        rapido[i]=original[i];
                    }
                    int compInsercion=0,movInsercion=0,compQuick=0,interQuick=0,profMax=0;
                    chrono::steady_clock::time_point begin=chrono::steady_clock::now();
                    insercionDirecta(insercion,n,compInsercion,movInsercion);
                    chrono::steady_clock::time_point end=chrono::steady_clock::now();
                    double tiempoInsercion=chrono::duration_cast<chrono::nanoseconds>(end-begin).count()/1000000.0;
                    begin=chrono::steady_clock::now();
                    quicksort(rapido,0,n-1,compQuick,interQuick,1,profMax);
                    end=chrono::steady_clock::now();
                    double tiempoQuick=chrono::duration_cast<chrono::nanoseconds>(end-begin).count()/1000000.0;
                    for(int i=0;i<n;i++){
                        if(insercion[i]!=rapido[i]||(i>0&&insercion[i]<insercion[i-1])){
                            cout<<"Error al ordenar"<<endl;
                            return 0;
                        }
                    }
                    archivo<<"Insercion,"<<n<<","<<patron<<","<<rep<<","<<tiempoInsercion<<","<<compInsercion<<",0,"<<movInsercion<<",0,12345,"<<commit<<"\n";
                    archivo<<"QuickSort,"<<n<<","<<patron<<","<<rep<<","<<tiempoQuick<<","<<compQuick<<","<<interQuick<<","<<3*interQuick<<","<<profMax<<",12345,"<<commit<<"\n";
                }
                cout<<"n="<<n<<" patron="<<patron<<" completado"<<endl;
            }
        }
        archivo.close();
        cout<<"Resultados guardados en results/experimentos.csv"<<endl;
        return 0;
    }
    cout<<"Cantidad de numeros: ";
    if(!(cin>>n)||n<1||n>MAX){
        cout<<"Cantidad invalida"<<endl;
        return 0;
    }
    for(int i=0;i<n;i++){
        if(opcion==1){
            cout<<"Numero "<<i+1<<": ";
            if(!(cin>>original[i])){
                cout<<"Dato invalido"<<endl;
                return 0;
            }
        }else if(opcion==2) original[i]=rand()%10000;
        else if(opcion==3) original[i]=i+1;
        else original[i]=n-i;
        insercion[i]=original[i];
        rapido[i]=original[i];
    }
    int compInsercion=0,movInsercion=0,compQuick=0,interQuick=0,profMax=0;
    chrono::steady_clock::time_point begin=chrono::steady_clock::now();
    insercionDirecta(insercion,n,compInsercion,movInsercion);
    chrono::steady_clock::time_point end=chrono::steady_clock::now();
    long long tiempoInsercion=chrono::duration_cast<chrono::nanoseconds>(end-begin).count();
    cout<<"\n+-------------------+"<<endl;
    cout<<"| INSERCION DIRECTA |"<<endl;
    cout<<"+-------------------+"<<endl;
    for(int i=0;i<n;i++) cout<<insercion[i]<<" ";
    cout<<"\nTime difference = "<<chrono::duration_cast<chrono::milliseconds>(end-begin).count()<<"[ms]"<<endl;
    cout<<"Time difference = "<<chrono::duration_cast<chrono::microseconds>(end-begin).count()<<"[us]"<<endl;
    cout<<"Time difference = "<<tiempoInsercion<<"[ns]"<<endl;
    cout<<"Comparaciones: "<<compInsercion<<endl;
    cout<<"Movimientos: "<<movInsercion<<endl;
    begin=chrono::steady_clock::now();
    quicksort(rapido,0,n-1,compQuick,interQuick,1,profMax);
    end=chrono::steady_clock::now();
    long long tiempoQuick=chrono::duration_cast<chrono::nanoseconds>(end-begin).count();
    cout<<"\n+-------------------+"<<endl;
    cout<<"|     QUICKSORT     |"<<endl;
    cout<<"+-------------------+"<<endl;
    for(int i=0;i<n;i++) cout<<rapido[i]<<" ";
    cout<<"\nTime difference = "<<chrono::duration_cast<chrono::milliseconds>(end-begin).count()<<"[ms]"<<endl;
    cout<<"Time difference = "<<chrono::duration_cast<chrono::microseconds>(end-begin).count()<<"[us]"<<endl;
    cout<<"Time difference = "<<tiempoQuick<<"[ns]"<<endl;
    cout<<"Comparaciones: "<<compQuick<<endl;
    cout<<"Intercambios: "<<interQuick<<endl;
    cout<<"Profundidad: "<<profMax<<endl;
    ofstream archivo("results/pruebas_manuales.csv");
    if(archivo.is_open()){
        archivo<<"algoritmo,n,tiempo_ns,comparaciones,intercambios,movimientos,profundidad_recursion\n";
        archivo<<"Insercion,"<<n<<","<<tiempoInsercion<<","<<compInsercion<<",0,"<<movInsercion<<",0\n";
        archivo<<"QuickSort,"<<n<<","<<tiempoQuick<<","<<compQuick<<","<<interQuick<<","<<3*interQuick<<","<<profMax<<"\n";
        archivo.close();
        cout<<"\nResultados guardados en CSV"<<endl;
    }else cout<<"\nNo se pudo guardar el CSV"<<endl;
    return 0;
}
void insercionDirecta(int datos[],int n,int &comparaciones,int &movimientos){
    for(int i=1;i<n;i++){
        int clave=datos[i];
        int j=i-1;
        while(j>=0){
            comparaciones++;
            if(datos[j]>clave){
                datos[j+1]=datos[j];
                movimientos++;
                j--;
            }else break;
        }
        datos[j+1]=clave;
        movimientos++;
    }
}
void quicksort(int datos[],int izq,int der,int &comparaciones,int &intercambios,int nivel,int &profMax){
    if(izq>=der) return;
    if(nivel>profMax) profMax=nivel;
    int i=izq,j=der;
    int pivote=datos[(izq+der)/2];
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
            if(i!=j){
                int aux=datos[i];
                datos[i]=datos[j];
                datos[j]=aux;
                intercambios++;
            }
            i++;
            j--;
        }
    }
    if(izq<j) quicksort(datos,izq,j,comparaciones,intercambios,nivel+1,profMax);
    if(i<der) quicksort(datos,i,der,comparaciones,intercambios,nivel+1,profMax);
}
