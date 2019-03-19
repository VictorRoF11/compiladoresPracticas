#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <stdlib.h>
using namespace std;
#define i64 long long int
#define error 1000
//Estado de error 1000

typedef pair<char,int> par;
typedef vector<par> Vector; 
typedef vector<Vector> MatrizPar;

vector<char> numero (10);
vector<char> numero2 (10);


FILE *fd;

vector <char> Contenido(1000);


int numEstados;
int numCaracteresAlf;
int numEstadosFinales;
int estadoInicial;
bool salir = false;
char renglon1[10000];
char renglon2[10000];
char renglon3[1001];
char renglon4[1001];
char T[10000];

int num[100];

vector<int> estados(1000); //arreglo para los estados
vector<int> estadosT(1000); //Este arreglo me sirve para saber cuantas transiciones tiene un estado Origen
vector<char> alfabeto(1000);
vector<int> estadosFinales(1000);
MatrizPar transiciones(1010, vector<par> (1010)); 
//Las transiciones se guardan en la posición del estado Origen, en el se guardan todas sus transiciones
//con la ayuda de un par <char,int> caracter y estado Destino

int convertirNumero(vector<char> n, int tam);
void mostrarMenu();
void cargarArchivo();
void limpiarPantalla();
void pausa();
void completarAutomata();
void mostrarTransiciones();
void mostrarEstados();
void mostrarAlfabeto();

int main(int argc, char const *argv[])
{
	mostrarMenu();
	if(salir == true) return 0;

	return 0;
}

void mostrarMenu(){
	char opc1=0;
	cout<<"--- Automata No Deterministico ----\n\n";
	cout<<"Selecciona una opcion: \n";
	cout<<" (1) Cargar un archivo (AFN).   (2) Salir \n";
	cin>>opc1;

	switch(opc1){
		case '1':
			limpiarPantalla();
			cargarArchivo();		
			break;
		case '2':
			limpiarPantalla();
			cout<<"Saliendo del programa.. Adios.\n";
			salir = true;
			break;
		default:
			limpiarPantalla();
			cout<<"ERROR: Opcion no valida.\n\n";
			mostrarMenu();
	}
}

void cargarArchivo(){

	cout<<"Cargando archivo. Espere un momento...\n";	
	
	fd = fopen("afn.txt","r"); //Abrir el archivo

		if (fd == NULL)	cout<<"Error al abrir el archivo";	
		else cout<<"Archivo cargado con exito..\n";

		fgets(renglon1,1000,fd); //Estados
		fgets(renglon2,1000,fd); //Alfabeto
		fgets(renglon3,1000,fd); //Inicial
		fgets(renglon4,1000,fd); //Finales

 //Aquí leo las transiciones y las voy guardando, renglon por renglon.
		while(!feof(fd)){

			fgets(T,1000,fd);

			int i=0,j=0,k=0;
			int origen=0,destino=0;
			char caracter;
			int comas=0;
			bool isError = false;
			
				while(T[i]){
					if(T[i] == 69){
						//cout<<"estado de error\n";
						if(comas == 0) origen = 1000;
						else isError = true;
					}

					if((T[i] >= 48) && (T[i] <= 57)){ //Leyendo un estado caracter por caracter
						numero[j]=T[i];								
						j++;
					}else{
							if(comas == 0 && T[i] != 69){							
								 origen = convertirNumero(numero, j); // converir el estado a Int																	 					
								for (int i = 0; i < 10; ++i) numero[i]=0;
								j=0;
							}				
						comas++;
					}
					if((T[i] >= 58) && (T[i] <= 68) || (T[i] >= 70) && (T[i] <= 126)){ // guardar caracter perteneciente al alfabeto
						caracter = T[i];					
					}
				i++;
				}
				if(!isError) destino = convertirNumero(numero, j);
				else destino = 1000; //Estado de error = 1000

				//cout<<"Orig: "<<origen<<" car: "<<caracter<<" des: "<<destino<<"\n";

				transiciones[origen][estadosT[origen]].first = caracter;
				transiciones[origen][estadosT[origen]].second = destino;
				estadosT[origen]++;
		}
	
	fclose(fd);
		
	/******************************** 
		Leer todos los Estados 
	*********************************/
		
		int i=0,j=0,k=0;	
		while(renglon1[i]){
			
			if(renglon1[i] == 'E'){
				estados[k] = 1000; //Estado error = 1000
				k++;
				i++;
			}else{

				if(renglon1[i] != ',' && renglon1[i] != '\n' ){
					numero[j]=renglon1[i];								
					j++;
				}else{

					estados[k] = convertirNumero(numero, j);				
					for (int i = 0; i < 10; ++i) numero[i]=0;
				j=0;
				k++;
				}
			}

		i++;	
		}
		numEstados = k;
		//cout<<"numEstados: "<<numEstados<<"\n";	

	/*******************************************
		Leer todos los caracteres del alfabeto
	********************************************/		
		int n=0,m=0;
		while(renglon2[n]){
			if(renglon2[n] != ',' && renglon2[n] != '\n' ){
				alfabeto[m] = renglon2[n];
				m++;
			}
		n++;		
		}
		numCaracteresAlf = m;
		//cout<<"numAlf: "<<numCaracteresAlf<<"\n";

//Leo el estado Inicial
		i=0,j=0,k=0;	
		while(renglon3[i]){

			if(renglon3[i] != ',' && renglon3[i] != '\n' ){
				numero[j]=renglon3[i];								
				j++;
			}else{											
				estadoInicial = convertirNumero(numero, j);				
				for (int i = 0; i < 10; ++i) numero[i]=0;
				j=0;
				k++;
			}
		i++;	
		}
//Leo los estados finales.
		i=0,j=0,k=0;	
		while(renglon4[i]){

			if(renglon4[i] != ',' && renglon4[i] != '\n' ){
				numero[j]=renglon4[i];								
				j++;
			}else{											
				estadosFinales[k] = convertirNumero(numero, j);				
				for (int i = 0; i < 10; ++i) numero[i]=0;
				j=0;
				k++;
			}
		i++;	
		}
		numEstadosFinales = k;


//	Mostrar información del AFN (Quintupla)	
	cout<<"Estados: {";
	if (estados[0] != 1000) cout<<estados[0];
	else cout<<"ERROR";
	for (int i = 1; i < numEstados; ++i){
		if(estados[i] == 1000) cout<<",ERROR";
		else cout<<","<<estados[i]<<"";
	}
	cout<<"}\n";
	cout<<"Alfabeto: {";
	cout<<alfabeto[0];
	for (int i = 1; i < numCaracteresAlf; ++i)
		cout<<","<<alfabeto[i];
	cout<<"}\n";
	cout<<"Estado Inicial: "<<estadoInicial<<"\n";
	cout<<"Estados Finales: {";
	cout<<estadosFinales[0];
	for (int i = 1; i < numEstadosFinales; ++i)
		cout<<","<<estadosFinales[i];
	cout<<"}\n";

	
	mostrarTransiciones();
	pausa();
	completarAutomata();

}


void limpiarPantalla(){
	system("cls");
}

void pausa()
{
    cout << "\nPulsa una tecla para continuar...\n";
    getwchar();
    getwchar();
}

//Función para mostra todas las transiciones.
void mostrarTransiciones(){	
	cout<<"Transiciones. \n";
	for(int i=0;i<1001;i++){
		for (int j = 0; j < 1001; j++)
		{
			if (transiciones[i][j].first)
			{
				if(i != 1000 ){//estado de error = 1000
					cout<<"q"<<i<<"(";
					if(transiciones[i][j].second != 1000)
						cout<<transiciones[i][j].first<<") -> q"<<transiciones[i][j].second<<"\n";
					else
						cout<<transiciones[i][j].first<<") -> qERROR"<<"\n";
				}
				else{
					cout<<"qERROR"<<""<<"(";
					if(transiciones[i][j].second != 1000)
						cout<<transiciones[i][j].first<<") -> q"<<transiciones[i][j].second<<"\n";
					else
						cout<<transiciones[i][j].first<<") -> qERROR"<<"\n";	
				}
				
			}
		}
	}
}

void completarAutomata(){
	cout<<"Agregando estado de error y transiciones faltantes. Espere un momento...\n";
	
	int existeError=false;
	for (int i = 0; i < numEstados; ++i) //Comprobar si existe estado de Error = 1000
			if (estados[i] == 1000) existeError = true;

	if (!existeError){
		estados[numEstados] = 1000; numEstados++; //Se crea el estado de Error
		estadosT[1000] = 0;
		for (int i = 0; i < numCaracteresAlf; ++i)
		{
			transiciones[1000][estadosT[1000]].first = alfabeto[i];
			transiciones[1000][estadosT[1000]].second = 1000;
			estadosT[1000]++;
		}
	}


	mostrarEstados();
	mostrarAlfabeto();
	/*cout<<"estadosT\n";
	for (int i = 0; i < numEstados; ++i)
	{
		//for (int j = 0; j < esta; ++j)
			cout<<estados[i]<<" - ";
			cout<<estadosT[estados[i]]<<"\n";
		
	}cout<<"***\n";*/

	bool ban;
	for (int i = 0; i < numEstados; i++)
	{		
		for (int j = 0; j < numCaracteresAlf  ; j++)
		{
			ban=false;
			//cout<<"T: "<<estadosT[ estados[i] ]<<"\n";
			//cout<<"est: "<<estados[i]<<"\n";

			for (int k = 0; k < estadosT[ estados[i] ]; k++) 
			{
				//cout<<"k= "<<k<<"\n";

				if(transiciones[ estados[i] ][k].first == alfabeto[j]){
					ban=true;
				}

				if(!ban && k == estadosT[ estados[i] ]-1){
				 transiciones[ estados[i] ][ estadosT[ estados[i]] ].first = alfabeto[j];
				 transiciones[ estados[i] ][ estadosT[ estados[i]] ].second = 1000; //Estado de Error
				 estadosT[estados[i]]++;
				}

			}
			
		}
	}

	mostrarTransiciones();
}
void mostrarEstados(){

	cout<<"Estados: {"<<estados[0];
	for (int i = 1; i < numEstados; ++i)
		cout<<","<<estados[i]<<"";
	cout<<"}\n";
}
void mostrarAlfabeto(){
	cout<<"alfabeto: {"<<alfabeto[0];
	for (int i = 1; i < numCaracteresAlf; ++i)
		cout<<","<<alfabeto[i];
	cout<<"}\n";
}


//Esta función me sirve cuando leo los estados desde archivo. String -> Int
int convertirNumero(vector<char> n, int tam){				
		int numero=0,i,j;		
		for (i = 0, j=tam-1 ; i < tam,j >= 0 ; i++,j--){
			int x = n[j];
			x-=48;			
			numero += (x)*(pow(10,i));					
		}
		return numero;
}