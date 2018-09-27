/*
	Archivo: Prueba.cpp
*/

// Este archivo se va a usar para ir probando cosas del programa. Estas pueden
// ser de cosas individuales o de cosas en bloques.
// Este archivo de prueba va complementado con el archivo makePrueba que es
// un segundo archivo make file que se va a utilizar para las compilaciones
// necesarias de las pruebas
// Para utilizar los archivos de prueba se estructura el arbol de dependencias
// como siempre, lo unico que cambia es el metodo de compilacion. Para
// compilar el programa de prueba hay que ingresar
// el comando " make -f makePrueba" y compila utilizando el archibo make file
// que se le indico.

// Por favor avisar si se modifica algno de los archivos con los que se estan
// haciendo pruebas por que puede traer cambios en los resultados de los
//  esteos

// Muchas gracias y programe pronto

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "Cmdline.hpp"
#include "Utils.hpp"
#include "Error.hpp"
#include "Red.hpp"
#include "ArrayDouble.hpp"

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_data(string const &);
static void opt_help(string const &);

/********************* Elementos golbales *********************/

static option_t options[] = {
	{1, "d", "data", NULL, opt_data, OPT_MANDATORY},
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static istream *dss = 0;
static istream *iss = 0;
static ostream *oss = 0;
static fstream dfs;
static fstream ifs;
static fstream ofs;

/********************* Cuerpo principal *********************/

int main(int argc, char * const argv[]){
	Red SensorNet;
	status_t st;

	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente.
	cmdl.parse(argc, argv);	// Metodo de parseo de la clase cmdline. Settea las variables globales

	if ((st = ParseAll(*dss, SensorNet)) != ST_OK) {
		PrintError(st);
		return EXIT_FAILURE;
	}
	int amount = SensorNet.GetAmount();

	for (int i = 0; i < amount; i++) {
		cout << "Id:" << i << std::endl;
		cout << SensorNet.GetId(i) << std::endl;
		cout << "Data:" << std::endl;
		SensorNet.PrintSensorData(i);
		cout << endl << endl << endl;
	}


	return EXIT_SUCCESS;
}

/********************* Funciones de parceo *********************/


static void opt_input(string const &arg){
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
 	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_output(string const &arg){
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminación del programa en su totalidad
	}
}

static void opt_data(string const &arg){
	dfs.open(arg.c_str(), ios::in);
	dss = &dfs;

	//Verificamos que el stream este OK.
	//
	if(!dss->good()){
		cerr << "cannot open "
			 << arg
			 << "."
			 << endl;
		exit(1); 		// EXIT: Terminación del programa en su totalidad
	}
}

static void opt_help(string const &arg){
	cout << "cmdline -d file [-i file] [-o file]"
	     << endl;
	exit(0);
}









