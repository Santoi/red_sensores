/*
	Archivo: Utils.cpp
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "Utils.hpp"
#include "Red.hpp"
#include "Error.hpp"
#include "Package.hpp"

status_t ParseFirstLine(istream & is, Red & Object);
status_t ParsedData(istream & is, Red & Object);
status_t DivideString(string & Read, string * & Parsed, char Divider);

// Se llama para parcear la primera linea del archivo que contiene los datos. La funcion procesa los Ids de cada columna y
// setea el objeto red con los ids y las columnas

status_t ParseAll(istream & is, Red & Object){
	status_t st;
	st = ParseFirstLine(is, Object);
	if (st != ST_OK)
		return st;
	st = ParsedData(is, Object);
	return st;
}

status_t ManageQuerys(istream & is, ostream & os, Red & Object){
	string Read, aux;
	string * Sensor;
	stringstream StringRead;
	size_t i, len;
	int Start, End, SensorsQuantity = 0;
	char ch;
	bool BigQuery, ComplexQuery;
	status_t status;
	// Se comienza la iteracion copiando la primera linea del programa, si no hay linea no hace nada
	while(getline(is, Read)){
		BigQuery = false;
		ComplexQuery = false;

		// Se pasa el string a un streamstring para utilizar el operador >> para recibir los strings de caracter a caracter
		stringstream StringRead(Read);

		StringRead >> ch;

		// Se verifica si el primer caracter es un divisor de linea, si lo es se debe hacer un big query, si no se lo agrega al stribg auxiliar
		if(ch == LINE_DIVIDER){
			BigQuery = true;
			StringRead.putback(LINE_DIVIDER);
		}else{
			aux.clear();
			aux += ch;
			// Se lee el resto del Id mientras se fija si hay varios sensores o no. Si hay varios sensores lo marca con un flag y se lo procesa.
			while((StringRead >> ch) && (ch != LINE_DIVIDER)){
				if(ch == SENSOR_DIVIDER){
					ComplexQuery = true;
				}
				aux += ch;
			}
			StringRead.putback(LINE_DIVIDER);
		}

		// Se procesa el string auxiliar si hay varios Ids en el query
		if(ComplexQuery == true){
			// Recorre la linea para establecer la cantidad de strings que hace falta
			len = aux.length() - 1;
			for(i = 0; i < len; ++i){
				if(Read[i] == SENSOR_DIVIDER){
					SensorsQuantity++;
				}
			}
			// Se llama a una funcion que te separa los Ids en diferentes strings
			status = DivideString(aux, Sensor, SENSOR_DIVIDER);
			if (status != ST_OK){
				delete [] Sensor;
				return status;
			}
		}else if(BigQuery == false){
			// Si el query no es ni Big ni Complex se crea un string con el Id unico
			Sensor = new string(aux);
		}

		// Se procesa las comas y los numero enteros
		ch = StringRead.peek();
		if(ch != LINE_DIVIDER){
			Object.GetPackage()->SetQueryStatus(true);
			Object.PrintPackage(os);
			if(ComplexQuery){
				delete[] Sensor;
			}else if(!BigQuery){
				delete Sensor;
			}
			continue;
		}else{
			StringRead.ignore();
		}
		if(!(StringRead >> Start)){
			Object.GetPackage()->SetQueryStatus(true);
			Object.PrintPackage(os);
			if(ComplexQuery){
				delete[] Sensor;
			}else if(!BigQuery){
				delete Sensor;
			}
			continue;
		}
		ch = StringRead.peek();
		if(ch != LINE_DIVIDER){
			Object.GetPackage()->SetQueryStatus(true);
			Object.PrintPackage(os);
			if(ComplexQuery){
				delete[] Sensor;
			}else if(!BigQuery){
				delete Sensor;
			}
			continue;
		}else{
			StringRead.ignore();
		}
		if(!(StringRead >> End)){
			Object.GetPackage()->SetQueryStatus(true);
			Object.PrintPackage(os);
			if(ComplexQuery){
				delete[] Sensor;
			}else if(!BigQuery){
				delete Sensor;
			}
			continue;
		}

		// Se hacen las Querys
		if(BigQuery){
			Object.MakeBigQuery(Start, End);
		}else if(ComplexQuery){
			Object.MakeComplexQuery(Sensor, SensorsQuantity, Start, End);
		}else{
			Object.MakeSmallQuery(*Sensor, Start, End);
		}



		// Se impreime en el archivo el resultado
		Object.PrintPackage(os);
		if(ComplexQuery){
			delete[] Sensor;
		}else if(!BigQuery){
			delete Sensor;
		}
	}
	return ST_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////
									// Funciones privadas
//////////////////////////////////////////////////////////////////////////////////////////////

status_t ParseFirstLine(istream & is, Red & Object){
	string * Parsed;
	string Read;
	stringstream StringRead;
	status_t status;
	size_t i, len, Comas = 0;

	// Lee la primera linea del archivo
	if(!(getline(is, Read))){
		return ST_ERROR_FILE_CORRUPTED;
	}

	// Recorre la linea para establecer la cantidad de strings que hace falta
	len = Read.length() - 1;
	for (i = 0; i < len; ++i){
		if(Read[i] == LINE_DIVIDER){
			Comas++;
		}
	}

	// Llama a una funcion que separa a los varios substrings en funcion del divisor que se utiliza
	status = DivideString(Read, Parsed, LINE_DIVIDER);
	if(status != ST_OK){
		delete [] Parsed;
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
				delete[] Data;
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

status_t DivideString(string & Read, string * & Parsed, char Divider){
	string  aux;
	//stringstream StringRead;
	size_t i, len, Comas = 0;
	char ch;

	// Recorre la linea para establecer la cantidad de strings que hace falta
	len = Read.length() - 1;
	for(i = 0; i < len; ++i){
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













