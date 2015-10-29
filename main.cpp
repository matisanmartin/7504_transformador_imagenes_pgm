#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <ostream>
#include <cmath>
#include "cmdline.hpp"
#include "common.hpp"
#include "matriz.hpp"
#include "pgm.hpp"
#include "procesamiento.hpp"
#include "complejo.hpp"
#include "pila.hpp"
#include "operador.hpp"
#include "sy.hpp"
#include "rpn_calc.hpp" 

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_ancho_real(string const &);
static void opt_ancho_imag(string const &);
static void opt_function(string const &);

static option_t options[] =
{
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "r", "ancho_real", "-", opt_ancho_real, OPT_DEFAULT},
	{1, "j", "ancho_imag", "-", opt_ancho_imag, OPT_DEFAULT},
	{1, "f", "function", "-", opt_function, OPT_DEFAULT},
	{0, },
};

static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;
static string funcion;
static double ancho_real;
static double ancho_imag;

static void opt_input(string const &arg)
{
	if ((arg == "-")) {
		iss = &cin;
	} else {
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}

	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_output(string const &arg)
{
	if ((arg == "-")) {
		oss = &cout;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_ancho_real(string const &arg)
{
	if(arg=="-")
		ancho_real=2;	
	else
		ancho_real=stod(arg);
}

static void opt_ancho_imag(string const &arg)
{
	if(arg=="-")
		ancho_imag=2;	
	else
		ancho_imag=stod(arg);
}

static void opt_function(string const &arg)
{
	if(arg=="-")
	funcion='z';
	else
	funcion=arg;
}

const char* vector_error[]={	"Ok",
				"El encabezado es incorrecto",
				"El tamaño de la imagen es incorrecto",
				"El valor de la intensidad maxima es incorrecto",
				"La intensidad de algun pixel esta fuera de rango",
				"Error en la expresion: Parentesis desbalanceado",
				"Error en la expresion: Algun caracter u operando estan mal ubicados"
				};		

int main(int argc, char *argv[])
{
	cmdline cmdl(options);
	cmdl.parse(argc, argv);
	status_t estado;


	pgm<int> pgm_input;

	if((estado=leer_archivo_entrada(iss,pgm_input))!=OK)
	{
		cerr<<MSJ_ERROR_ABRIR_ARCHIVO<<endl;
		cerr<<vector_error[estado]<<endl;
		return EXIT_FAILURE;
	}

	long int filas=pgm_input.obt_filas();
	long int columnas=pgm_input.obt_columnas();
	int int_max=pgm_input.obt_int_max();
	
	matriz<int> m(filas,columnas);
	
	pgm<int> pgm_output(filas,columnas,int_max,m);
	
    if((estado=procesamiento(pgm_input,pgm_output,ancho_real,ancho_imag,funcion))!=OK)
    {
        cout<<MSJ_ERROR_PROCESAMIENTO<<endl;
        cerr<<vector_error[estado]<<endl;
		return EXIT_FAILURE;
    }

    if((estado=imprimir_archivo_salida(oss, pgm_output))!=OK)
    {
        cout<<MSJ_ERROR_PROCESAMIENTO<<endl;
        cerr<<vector_error[estado]<<endl;
		return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}
