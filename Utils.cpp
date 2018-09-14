/*
	Archivo: Utils.cpp
*/

#include <iostream>
#include <cstdlib>
#include <string>

#include "Utils.hpp"

void ParseLine(string * & Destino, istream & is, int & ContadorComas = 0){

	string Entrada;		// String sobre la que se va a guardar la linea leida
	int SubString = 0;	// Indica la posicion donde comenza la siguiente palabra a guardar
	int numero;			
	int j = 0;			
	int i = 0;

	//Se inizia leyendo la linea del flujo de entrada
	getline(is, Entrada);

	//Se cuentan la cantidad de palabras que hay en la linea contando la cantidad de comas
	for ( i = 0; i < (Entrada.length() - 1); ++i){
		if(Entrada[i] == ','){
			ContadorComas++;
		}	
	}
	ContadorComas++;

	// Se crea el Arreglo de Strings en funcion de la cantidad de palabras que hay en la linea
	Destino = new string[ContadorComas];

	// Se recorre nuevamente el String para localizar las comas y se copia en un string diferente lo que hay entre ellas
	// Se lo realiza en dos etapas. La primera es con todos las palabras que finalizan en coma y la segunda es con la palabra final
	for (i = 0; i < numero; ++i){
		if(Entrada[i] == ','){
			Destino[j].assign(Entrada, SubString, i - SubString);
			SubString = i + 1;
			j++;
		}	
	}
	Destino[j].assign(Entrada, SubString, i - SubString + 1);	// Se le suma uno porque el elemento final no es una coma

}











