/*
	Archivo: Utils.cpp
*/

#include <iostream>
#include <cstdlib>
#include <string>

#include "Utils.hpp"
/*
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
*/
// Se llama para parcear la primera linea del archivo que contiene los datos. La funcion procesa los Ids de cada columna y
// setea el objeto red con los ids y las columnas
status_t ParseFirstLine(istream & is, Red & Object){  // Este supuestamente esta ok con una duda
	string * Parsed;
	string Read, aux;
	stringstream StringRead;
	int Comas = 0, i = 0;
	char c;
	bool eol;

	// Lee la primera linea del archivo
	if(!(getline(is, Read))){
		return ST_ERROR_FILE_CORRUPTED;
	}

	// Recorre la linea para establecer la cantidad de strings que hace falta
	for ( i = 0; i < (Read.length() - 1); ++i){
		if(Read[i] == ','){
			Comas++;
		}
	}
	Comas++; // Se suma uno porque hay una palabra mas que comas
	Parsed = new string[Comas];

	// Se pasa el string a un streamstring para utilizar el operador >> para recibir los strings

	i = 0;
	stringstream StringRead(Read);
	while((StringRead >> aux) && (!StringRead.eof())){  // la duda es sobre el eof????????????????
		if(aux[aux.length() - 1] == ','){	// Si se leyo tambien la coma porque estaba pegada se la vuelve a poner en el string
			StringRead.putback(',');
			Parsed[i].assign(aux, 0, aux.length() - 1); // Se copia todo el string en parsed salvo la coma final que no pertenece al ID
		}else{
			Parsed[i] = aux;	// Si no tiene coma se lo introduce directamente
		}

		c = is.peek();
		if(c == 'c' && i < Comas){
			StringRead.ignore();
		}else if(c == 'c' && i == Comas){	// no puede haber la misma cantidad de palabras que de comas
			return ST_ERROR_FILE_CORRUPTED;
		}
		i++;
	}

	Object.SetSensors(Parsed, Comas);
	delete [] Parsed;

	return OK;
}

status_t ParsedData(istream & is, Red & Object){
	string Read;
	stringstream StringRead;
	int i;
	char ch;
	double Number;
	double * Data;
	bool eol;

	Data = new double[Object.GetLeng()];


	while(getline(is, Read)){
		stringstream StringRead(Read);
		i = 0;
		while((Read >> Number) && (!Read.eof())){
			Data[i] = Number;
			ch = is.peek();
			if((ch == ',') && (i < Object.GetLeng())){
				StringRead.ignore();
			}else if((ch != ',') || ((ch == ',') && (i < Object.GetLeng()))){
				return ST_ERROR_FILE_CORRUPTED;
			}
			i++;
		}
		Object.Append(Data);
	}

	delete [] Data;

	return OK;
}

status_t ManageQuerys(istream & is, ostream & os, Red & Object){
	string Read, aux, Sensor;
	stringstream StringRead;
	int i, Start, End;
	char ch;
	bool BigQuery;

// Se comienza la iteracion copiando la primera linea del programa, si no hay linea no hace nada
	while(getline(is, Read)){
		BigQuery = false;
		stringstream StringRead(Read);

		// Se hace con un if porque si no lee nada entonce pasa a la siguiente linea
		if(!(StringRead >> aux)){
			continue;
		}
		if((aux.length() == 1) && aux[0] == ','){	// Si solo hay una coma en el string auxiliar significa que no hay Id, por lo que es un BigQuery. Se vuelve a introducir la coma en el streram
			BigQuery = true;
			StringRead.putback(',');
		}
		if(BigQuery == false){
			if(aux[aux.length() - 1] == ','){			// Se verifica si se introdujo la coma en el string auxiliar
				StringRead.putback(',');
				Sensor.assign(aux, 0, aux.length() - 1);	// Se copia el string sinn la coma
			}else{											// Si no tiene coma se lo copia como esta
				Sensor = aux;
			}
		}

		// Se procesa las comas y los numero enteros
		ch = is.peek();
		if(ch != ','){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}else{
			is.ignore();
		}
		if(!(is >> Start)){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}
		ch = is.peek();
		if(ch != ','){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}else{
			is.ignore();
		}
		if(!(is >> End)){
			Object.SetQueryStatus(true);
			Object.PrintPackage();
			continue;
		}

		// Se hacen las Querys

		if(BigQuery){
			Object.MakeBigQuery(Start, End);
		}else{
			Object.MakeSmallQuery(Sensor, Start,End);
		}

		// Se impreime en el archivo el resultado
		Object.PrintPackage(os);
	}
	return OK;
}



