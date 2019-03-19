#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

typedef pair<char,char> par;
typedef vector<par> Vector; 
typedef vector<Vector> MatrizPar;


FILE *fd;

vector <char> Contenido(1000);
vector <int> estadosT(10000);

int tamArchivo=0;
int delimitador;
char estadoInicial;
bool salir = false;
vector<char> estados(1000);
vector<char> alfabeto(1000);
vector<char> estadosFinales(1000);

MatrizPar transiciones(1000, vector<par> (1000));

void mostrarMenu();
void mostrarContenido();
void cargarArchivo();
void limpiarPantalla();
void pausa();
void completarAutomata();
void extraerEstados();
void extraerAlfabeto();
void definirEstados();
void extraerTransiciones();
void mostrarTransiciones();

int main(int argc, char const *argv[])
{
	mostrarMenu();
	if(salir == true) return 0;
	mostrarContenido();	
	extraerEstados();
	extraerAlfabeto();
	definirEstados();
	extraerTransiciones();
	mostrarTransiciones();

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
	tamArchivo=0;		
	char c;
	fd = fopen("afn.txt","r");

	if (fd == NULL)
		cout<<"Error al abrir el archivo";	
	
	int i=0;
	while((c=fgetc(fd))!=EOF ){
		Contenido[i]= c; //Guarda el contenido en un arreglo
		i++;
	}
	tamArchivo=i;
	fclose(fd);

	cout<<"Archivo cargado con exito..\n";
	pausa();
	completarAutomata();
}


void mostrarContenido(){

	cout<<"Archivo Original. \n";
	for (int i = 0; i < tamArchivo; ++i)
	{
		cout<<Contenido[i];
	}
	cout<<"\n";
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

void extraerEstados(){

	int i=0,j=0;
	while(Contenido[i] != '\n')
	{		

		if ( (Contenido[i] >= 48) && (Contenido[i] <= 122) )
		{		
			estados[j] = Contenido[i];
			cout<<estados[j];
			j++;
		}

		i++;
	}
	delimitador = i+1;
	cout<<"\n";
}
void extraerAlfabeto(){

	int i = delimitador,j=0; 
	while(Contenido[i] != '\n')
	{
		if ( (Contenido[i] >= 48) && (Contenido[i] <= 122) )
		{
			alfabeto[j]= Contenido[i];
			cout<<alfabeto[j];
			j++;
		}
		i++;
	}
	delimitador = i+1;
	cout<<"\n";
}
void definirEstados(){
	int i= delimitador,j=0;

	while(Contenido[i] != '\n')
	{
		if ( (Contenido[i] >= 48) && (Contenido[i] <= 122) )
		{
			estadoInicial = Contenido[i];
			cout<<estadoInicial;			
		}
		i++;
	}
	cout<<"\n";
	i++;
	while(Contenido[i] != '\n')
	{
		if ( (Contenido[i] >= 48) && (Contenido[i] <= 122) )
		{
			estadosFinales[j] = Contenido[i];
			cout<<estadosFinales[j];			
			j++;
		}
		i++;
	}
	cout<<"\n";
	delimitador = i+1;

}
void extraerTransiciones(){
	cout<<"tam: "<<tamArchivo<<"\n";
	int i= delimitador;
	int j;
	bool ban;

	while(i <= tamArchivo-1){
		cout<<"i: "<<i<<"\n";
		
		
		char caracter,estadoDestino;
		int estadoOrigen;
		estadoOrigen =  Contenido[i] - 48;
		caracter = Contenido[i+2];
		estadoDestino = Contenido[i+4];
			
				transiciones[estadoOrigen][estadosT[estadoOrigen]].first = caracter;
				transiciones[estadoOrigen][estadosT[estadoOrigen]].second = estadoDestino;
				estadosT[estadoOrigen]++;
		cout<<estadoOrigen<<" "<<caracter<<" "<<estadoDestino<<"\n";	
		i = i+6;		
		}		

}

void mostrarTransiciones(){	
	cout<<"Transiciones. \n";
	for(int i=0;i<10;i++){
		for (int j = 0; j < 10; j++)
		{
			if (transiciones[i][j].first)
			{
				cout<<transiciones[i][j].first<<" "<<transiciones[i][j].second<<"\n"; 
			}
		}
	}
}
void completarAutomata(){

}