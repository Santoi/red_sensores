/*
	Archivo: Utils.hpp
*/

#ifndef _UTILS_HPP_INCLUDED_
#define _UTILS_HPP_INCLUDED_

#include <iostream>
#include <cstdlib>
#include <string>

//void ParseLine(string * & Destino, istream & is);
status_t ParseFirstLine(istream & is, Red & Object);
status_t ParsedData(istream & is, Red & Object);
status_t ManageQuerys(istream & is, ostream & os, Red & Object);

#endif









