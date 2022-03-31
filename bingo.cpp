//#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <time.h> // lo mismo que cstdlib y/o ctime?
#include <string.h> //para manejar cadena de caracteres
#include <stack> //para pilas
#include <cstdlib> // para usar el rand()
#include <ctime> // para usar el srand()
#include <stdlib.h> 
#include <conio.h> //contine funciones para manipular la consola en el entorno msdos
#include <Windows.h>

//VALORES CONSTANTES CON DEFINE
#define max_colum 3 
#define max_fila 9
#define max_bingo 27
#define med_bolilla 14
#define max_num 90


//using namespace System;
using namespace std;

void llenar_arr(int arr_carton[],int mat_carton[][max_fila], int max_columna,int rango_inicial,int rango_final)
{
	
	int no_repetido, a=0, i=0; 
	
	//CARGA ARRAY PARA EL CARTON DE BINGO
	while(i<max_bingo)
	{
		while(i<max_columna) 
		{
			no_repetido=(rango_inicial-1)+(rand()%rango_final); //ASIGNA NUMERO RANDOM DENTOR DEL RANGO PARA CADA COLUMNA
			if (arr_carton[i]!=no_repetido && arr_carton[i+1]!=no_repetido && no_repetido!=0 && no_repetido<rango_final)
			{
				arr_carton[i]=no_repetido;
				i++;
			}
		}
		max_columna+=3;
		rango_inicial+=10;
		rango_final+=10;		
	}
	//CARGA MATRIZ DE BINGO
	for (int i = 0; i < max_fila; i++)
	{
		for (int j = 0; j < max_colum; j++)
		{
			mat_carton[j][i]=arr_carton[a];
			a++;
		}
	}
}

void espacios_blancos(int mat_carton[][max_fila])
{
	HANDLE x;
	x=GetStdHandle(STD_OUTPUT_HANDLE);
	//ASIGNA CEROS PARA LOS LUGARES EN BLANCO
	int columna_no_repetida[9];
	int zero, blanco=0;
	for (int i = 0; i < max_colum; i++)
	{
		blanco=0;
		for (int j = 0; j < max_fila;j++)
		{
			zero=1+rand()%2; //ASIGNA NUMERO RANDOM QUE SERA LA COLUMNA PARA  INGRESAR EL VALOR O EL ESPACIO EN BLACNO
			if (zero=rand()%2!=0 && blanco<4)
			{
				mat_carton[i][j]=0;
				blanco++;
			}
			if (blanco<4 && j==max_fila)
			{
				blanco=0;
				j==0;
			}
		}
	}
	
	//MUESTRA CARTON DE BINGO
	
	SetConsoleTextAttribute(x,9);
	cout<<"\333\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\333\n";
	for (int i = 0; i < max_colum; i++)
	{
		SetConsoleTextAttribute(x,9);
		cout<<"\333 ";
		SetConsoleTextAttribute(x,7);
		for (int j = 0; j < max_fila; j++)
		{
			if (mat_carton[i][j]==0 && j==0)
			{
				SetConsoleTextAttribute(x,4);
				cout<<" "<<"\333  ";
			}else if (mat_carton[i][j]==0 && j>0)
			{
				SetConsoleTextAttribute(x,4);
				cout<<" "<<"\333\333 ";
			}else
			{
				SetConsoleTextAttribute(x,8);
				cout<<" "<<mat_carton[i][j]<<" ";
			}
			if (j!=8)
			{
				cout<<"\t";
			}
		}
		SetConsoleTextAttribute(x,9);
		cout<<" \333";
		cout<<"\n";
	}
	
	SetConsoleTextAttribute(x,9);
	cout<<"\333\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\333\n\n";
	
}

bool revision(int bolillas[], int num)
{
	int x=0;
	while (x<med_bolilla)
	{
		if (bolillas[x]==num)
		{
			return(false);
		}
		x++;
	}
	return(true);
}

bool bolillero(int bolillas[])
{
	//BOLILLAS NO REPETIDAS 
	HANDLE x;
	x=GetStdHandle(STD_OUTPUT_HANDLE);
	int num;
	SetConsoleTextAttribute(x,2);
	cout<<"BOLILLAS \20\20";
	for (int i = 0; i < med_bolilla;)
	{
		
		num=rand()%max_num;
		if (revision(bolillas,num))
		{
			bolillas[i]=num;
			cout<<" "<<bolillas[i]<<" ";
			i++;
		}	
	}
	cout<<"\21\21 \n\n";
	return EXIT_SUCCESS;
}

int revision_matriz(int mat_cartonj1[][max_fila],int bolillas[],int i, int j)
{
	int a=0;
	while(a<med_bolilla)
	{
		if (mat_cartonj1[i][j]==bolillas[a])
		{
			return(true);
		}
		a++;
	}
	return(false);
}

int linea(int f, int i, int & fila_0, int & fila_1, int & fila_2)
{
	//ACIERTOS POR LINEA
		switch (i)
		{
			case 0:(fila_0=f);
					   if (fila_0==5)
					   {
						   return(true);break;
					   };
			case 1:(fila_1=f);
					   if (fila_1==5)
					   {
						   return(true);break;
					   };
			case 2:(fila_2=f);
				if (fila_2==5)
				{
					return(true);break;
				};
			default:return(false);
		}
}

int bingo_(int f, int i, int fila_0, int fila_1, int fila_2)
{
	//ACIERTOS PARA BINGO
	if (fila_0==5 && fila_1==5 && fila_2==5)
	{
		return(true);
	}else
	{
		return(false);
	}
}

void cartones_marcados(int mat_carton[][max_fila],int bolillas[])
{
	HANDLE x;
	x=GetStdHandle(STD_OUTPUT_HANDLE);
	int aciertos=0, fila_0, fila_1, fila_2, f, i=0;
	SetConsoleTextAttribute(x,9);
	cout<<"\333\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\333\n";
	//MUESTRA Y MARCA CARTON CON NUMEROS QUE SALIERON DE BOLILLERO
	for (int i = 0; i < max_colum; i++)
	{
		f=0;
		SetConsoleTextAttribute(x,9);
		cout<<"\333 ";
		for (int j = 0; j < max_fila;j++)
		{
			if (revision_matriz(mat_carton,bolillas,i,j))
			{
				SetConsoleTextAttribute(x,2);
				cout<<"\20"<<mat_carton[i][j]<<"\21";
				aciertos++;
				f++;
			}else if (mat_carton[i][j]==0 && j==0)
			{
				SetConsoleTextAttribute(x,4);
				cout<<" "<<"\333 ";
			}else if (mat_carton[i][j]==0 && j>0)
			{
				SetConsoleTextAttribute(x,4);
				cout<<" "<<"\333\333 ";
			}else
			{
				SetConsoleTextAttribute(x,8);
				cout<<" "<<mat_carton[i][j]<<" ";
			}
			if (j!=8)
			{
				cout<<"\t";
			}
		}
		SetConsoleTextAttribute(x,9);
		cout<<" \333";	
		cout<<"\n";
		if (linea(f,i,fila_0,fila_1,fila_2)) //(fila_0==5 || fila_1==5 || fila_2==5)
		{
			SetConsoleTextAttribute(x,2);
			cout<<" \177 Gano Linea! \n";
		}
	}
	
	SetConsoleTextAttribute(x,9);
	cout<<"\333\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\334\333\n";
	
	//MUESTRA BOLILLAS
	SetConsoleTextAttribute(x,2);
	cout<<"\nBOLILLAS \20\20";
		
	for (int i = 0; i < med_bolilla; i++)
	{
			
		cout<<" "<<bolillas[i]<<" ";
	}
	SetConsoleTextAttribute(x,2);
	cout<<"\21\21 \n\n";//break;

	SetConsoleTextAttribute(x,2);
	//CARTEL FINAL QUE MUESTRA ACIERTOS Y SI GANO LINEA O BINGO
	cout<<"\n\n";
	cout<<" \177 Aciertos: "<<aciertos<<"\n";
	cout<<" \177 Aciertos primer fila: "<<fila_0<<"\n";
	cout<<" \177 Aciertos segunda fila: "<<fila_1<<"\n";
	cout<<" \177 Aciertos tercer fila: "<<fila_2<<"\n";
	cout<<"\n\n";
	
	if (bingo_(f,i,fila_0,fila_1,fila_2)) //(fila_0==5 || fila_1==5 || fila_2==5) 
	{
		SetConsoleTextAttribute(x,2);
		cout<<" \177 logro hacer bingo! \177\n";
	}
}

int main(array<System::String ^> ^args)
{ 
	srand((unsigned)time(NULL));
	HANDLE x;
	x=GetStdHandle(STD_OUTPUT_HANDLE);
	int min_columna=0, max_columna=3, rango_inicial=1, rango_final=10, jugadores, a=0;
	int arr_carton[27], mat_cartonj1[3][9], bolillas[14], mat_cartonj2[3][9], mat_cartonj3[3][9];
	//memset(arr_carton,0,sizeof(int)*max_bingo);
	//memset(mat_carton,0,sizeof(int)*max_num);
	memset(bolillas,0,sizeof(int)*med_bolilla); //DA VALOR 0 A TODOS LOS BYTES
	SetConsoleTextAttribute(x,4);
	cout<<"\n\n \t\t \257\257 B "<<"\t I \t"<<"N \t"<<"G \t"<<"O \256\256\t\n\n";
	cout<<"\t\t     El juego va a comenzar!!! \n\n";
	//CANTIDAD DE JUGADORES
	SetConsoleTextAttribute(x,5);
	cout<<"  \177 Cantidad de jugadores?\t";
	cin>>jugadores;
	cout<<"\n";
	switch (jugadores)
	{
	case 1: //LLENA CARTONES				//1 JUGADOR
			llenar_arr(arr_carton,mat_cartonj1,max_columna,rango_inicial,rango_final);
			//MUETRA CARTON CON ESPACIOS BLANCOS
			espacios_blancos(mat_cartonj1);
			//BLILLERO
			bolillero(bolillas);
			SetConsoleTextAttribute(x,4);
			cout<<"En 10 segundos vera los resultados... ";  //LIMPIA PANTALLA TRANSCURRIDOS 10 SEGUNDOS
			for (int i = 5; i >= 0; i--)
			{
				SetConsoleTextAttribute(x,i);
				if (i%2==0)
				{
					SetConsoleTextAttribute(x,i);
					cout<<i<<" ";
				}else
				{
					SetConsoleTextAttribute(x,i);
					cout<<i<<" ";
				}
				
				Sleep(1000);
			}
			system("cls");
			SetConsoleTextAttribute(x,4);
			cout<<"\n\n \t\t \257\257 B "<<"\t I \t"<<"N \t"<<"G \t"<<"O \256\256\t\n\n";
			//MARCAR CARTON CON LOS NUMEROS GENERADOS
			cartones_marcados(mat_cartonj1,bolillas);break;
	case 2:	//LLENA CARTONES                //2 JUGADORER
			llenar_arr(arr_carton,mat_cartonj1,max_columna,rango_inicial,rango_final);
			llenar_arr(arr_carton,mat_cartonj2,max_columna,rango_inicial,rango_final);
			//MUETRA CARTON CON ESPACIOS BLANCOS
			espacios_blancos(mat_cartonj1);
			espacios_blancos(mat_cartonj2);
			//BLILLERO
			bolillero(bolillas);
			SetConsoleTextAttribute(x,4);
			cout<<"En 10 segundos vera los resultados... "; //LIMPIA PANTALLA TRANSCURRIDOS 10 SEGUNDOS
			for (int i = 5; i >= 0; i--)
			{
				SetConsoleTextAttribute(x,i);
				if (i%2==0)
				{
					SetConsoleTextAttribute(x,i);
					cout<<i<<" ";
				}else
				{
					SetConsoleTextAttribute(x,i);
					cout<<i<<" ";
				}
				
				Sleep(1000);
			}
			system("cls");
			SetConsoleTextAttribute(x,4);
			cout<<"\n\n \t\t \257\257 B "<<"\t I \t"<<"N \t"<<"G \t"<<"O \256\256\t\n\n";
			//MARCAR CARTON CON LOS NUMEROS GENERADOS
			cartones_marcados(mat_cartonj1,bolillas);
			cout<<"\n\n";
			cartones_marcados(mat_cartonj2,bolillas);
			cout<<"\n\n";break;
	case 3: //LLENA CARTONES				//3 JUGADORES
			llenar_arr(arr_carton,mat_cartonj1,max_columna,rango_inicial,rango_final);
			llenar_arr(arr_carton,mat_cartonj2,max_columna,rango_inicial,rango_final);
			llenar_arr(arr_carton,mat_cartonj3,max_columna,rango_inicial,rango_final);
			//MUETRA CARTON CON ESPACIOS BLANCOS
			espacios_blancos(mat_cartonj1);
			espacios_blancos(mat_cartonj2);
			espacios_blancos(mat_cartonj3);
			//BLILLERO
			bolillero(bolillas);
			SetConsoleTextAttribute(x,4);
			cout<<"En 10 segundos vera los resultados... "; //LIMPIA PANTALLA TRANSCURRIDOS 10 SEGUNDOS
			for (int i = 5; i >= 0; i--)
			{
				SetConsoleTextAttribute(x,i);
				if (i%2==0)
				{
					SetConsoleTextAttribute(x,i);
					cout<<i<<" ";
				}else
				{
					SetConsoleTextAttribute(x,i);
					cout<<i<<" ";
				}
				
				Sleep(1000);
			}
			system("cls");
			SetConsoleTextAttribute(x,4);
			cout<<"\n\n \t\t \257\257 B "<<"\t I \t"<<"N \t"<<"G \t"<<"O \256\256\t\n\n";
			//MARCAR CARTON CON LOS NUMEROS GENERADOS
			cartones_marcados(mat_cartonj1,bolillas);
			cout<<"\n\n";
			cartones_marcados(mat_cartonj2,bolillas);
			cout<<"\n\n";
			cartones_marcados(mat_cartonj3,bolillas);
			cout<<"\n\n";break;

			default:cout<<"\177 Exede cantidad de jugadores\n\n";break;
	}	
	SetConsoleTextAttribute(x,4);
	cout<<"\t\t       GRACIAS POR JUGAR!!! \n\n";
	cout<<"\n\n";
	system("pause");
    return EXIT_SUCCESS;
}