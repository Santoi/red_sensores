/*
	Archivo: Utils.cpp
*/

#include <iostream>
#include <cstdlib>
#include <string>

#include "Utils.hpp"

status_t DivideString(string & Read, string * & Parsed, char Divider);

// Se llama para parcear la primera linea del archivo que contiene los datos. La funcion procesa los Ids de cada columna y
// setea el objeto red con los ids y las columnas
status_t ParseFirstLine(istream & is, Red & Object){
	string * Parsed;
	string Read;
	stringstream StringRead;
	int Comas = 0, i;
	char ch;

	// Lee la primera linea del archivo
	if(!(getline(is, Read))){
		return ST_ERROR_FILE_CORRUPTED;
	}

	// Recorre la linea para establecer la cantidad de strings que hace falta
	for ( i = 0; i < (Read.length() - 1); ++i){
		if(Read[i] == LINE_DIVIDER){
			Comas++;
		}
	}

	// Llama a una funcion que separa a los varios substrings en funcion del divisor que se utiliza
	if((status = DivideString(Read, Parsed, LINE_DIVIDER)) && (status != ST_OK)){
		return status;
	}

	// Se setea la cantidad de sensores y sus Ids en el objeto 
	Object.SetSensors(Parsed, Comas + 1);
	delete [] Parsed;

	return ST_OK;
}

status_t ParsedData(istream & is, Red & Object){
	string Read;
	stringstream StringRead;
	int i;
	char ch;
	double Number;
	double * Data;

	Data = new double[Object.GetLeng()];

	// Lee linea por linea 
	while(getline(is, Read)){
		// Se pasa el string a un streamstring para utilizar el operador >> para recibir los strings de caracter a caracter	
		stringstream StringRead(Read);
		i = 0;
		while((StringRead >> Number)){
			Data[i] = Number;
			if((StringRead >> ch) && (ch != LINE_DIVIDER)){
				return ST_ERROR_FILE_CORRUPTED;
			}
			i++;
		}
		Object.AppendRow(Data);
	}

	// Se borra el el array de doubles que se utilizo como auxiliar
	delete [] Data;
	return ST_OK;
}

status_t ManageQuerys(istream & is, ostream & os, Red & Object){
	string Read, aux;
	string * Sensor;
	stringstream StringRead;
	int i, Start, End, SensorsQuantity = 0;
	char ch;
	bool BigQuery, ComplexQuery;
	status_t status;

	// Se comienza la iteracion copiando la primera linea del programa, si no hay linea no hace nada
	while(getline(is, Read)){
		BigQuery = false;
		ComplexQuery = false;

		// Se pasa el string a un streamstring para utilizar el operador >> para recibir los strings de caracter a caracter	
		stringstream StringRead(Read);

		if(!(StringRead >> ch))
			continue;

		// Se verifica si el primer caracter es un divisor de linea, si lo es se debe hacer un big query, si no se lo agrega al stribg auxiliar
		if(ch == LINE_DIVIDER){
			BigQuery = true;
			StringRead.putback(LINE_DIVIDER);
		}else{
			aux.clear();
			aux += ch;
			// Se lee el resto del Id mientras se fija si hay varios sensores o no. Si hay varios sensores lo marca con un flag y se lo procesa.
			while((ch = StringRead.peek()) && (ch != LINE_DIVIDER)){	
				if(ch == SENSOR_DIVIDER){
					ComplexQuery = true;
				}
				aux += ch;
				StringRead.ignore();
			}
		}

		// Se procesa el string auxiliar si hay varios Ids en el query
		if(ComplexQuery == true){
			// Recorre la linea para establecer la cantidad de strings que hace falta
			for(i = 0; i < (aux.length() - 1); ++i){
				if(Read[i] == SENSOR_DIVIDER){
					SensorsQuantity++;
				}
			}
			// Se llama a una funcion que te separa los Ids en diferentes strings
			if((status = DivideString(aux, Sensor, SENSOR_DIVIDER)) && (status != ST_OK)){
				return status;
			}
		}else if(BigQuery == false){
			// Si el query no es ni Big ni Complex se crea un string con el Id unico
			Sensor = new string(aux);
		}

		// Se procesa las comas y los numero enteros
		ch = is.peek();
		if(ch != LINE_DIVIDER){
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
		if(ch != LINE_DIVIDER){
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
		}else if{
			Object.MakeComplexQuery(Sensor, SensorsQuantity, Start, End);
		}else{
			Object.MakeSmallQuery(*Sensor, Start, End);
		}

		// Se impreime en el archivo el resultado
		Object.PrintPackage(os);
	}
	return ST_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////
									// Funciones privadas
//////////////////////////////////////////////////////////////////////////////////////////////

status_t DivideString(string & Read, string * & Parsed, char Divider){
	string  aux;
	stringstream StringRead;
	int Comas = 0, i;
	char ch;

	// Recorre la linea para establecer la cantidad de strings que hace falta
	for(i = 0; i < (Read.length() - 1); ++i){
		if(Read[i] == Divider){
			Comas++;
		}
	}
	Parsed = new string[Comas + 1]; 	// Se le suma uno debido a que hay un sring mas que divisor

	// Se pasa el string a un streamstring para utilizar el operador >> para recibir los strings de caracter a caracter
	stringstream StringRead(Read);

	for ( i = 0; i < (Comas + 1); ++i){
		Parsed[i].clear();
		while((StringRead >> ch) && (ch != Divider )){	// No hace falta un peek porque el char se come la coma
			Parsed[i] += ch;
		}
	}

	return ST_OK;
}



















