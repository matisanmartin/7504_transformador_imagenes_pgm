#ifndef PGM_H
#define PGM_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "matriz.hpp"
#include "common.hpp"

using namespace std;

template<typename T>
class pgm
{
	private:
		string magic_number;
		int cant_filas;
		int cant_columnas;
		int intensidad_maxima;
        matriz<T> m_pixels;

	public:
		pgm();
		pgm(long int filas, long int cols, int int_max, const matriz<T> &);
		pgm(const pgm &);
		void mod_magic_number(string);
		void mod_cant_filas(int);
		void mod_cant_columnas(int);
		void mod_int_max(int);
		void mod_m_pixels(matriz<T>);
		void mod_pixel(int,int,T);
		void resize(int filas, int columnas);
		long int obt_filas() const;
		long int obt_columnas() const;
		int obt_int_max() const;
		matriz<T> obt_m_pixels() const;
		~pgm();
};

template<typename T>
pgm<T>::pgm()
{
	this->magic_number=MAGIC_NUMBER_PGM;
	this->cant_filas=1;
	this->cant_columnas=1;
	this->intensidad_maxima=0;

	matriz<T> aux;
	this->m_pixels=aux;
}

template<typename T>
pgm<T>::pgm(long int filas, long int cols, int int_max, const matriz<T> &  m_orig)
{
	matriz<T> aux(m_orig);
	this->magic_number=MAGIC_NUMBER_PGM;
	this->cant_filas=filas;
	this->cant_columnas=cols;
	this->intensidad_maxima=int_max;
	this->m_pixels=aux;
}

template<typename T>
pgm<T>::pgm(const pgm & origen)
{
	this->magic_number=origen.magic_number;
	this->cant_filas=origen.cant_filas;
	this->cant_columnas=origen.cant_columnas;
	this->intensidad_maxima=origen.intensidad_maxima;
	this->m_pixels=origen.m_pixels;

}

template<typename T>
void pgm<T>::resize(int filas, int columnas)
{
	this->cant_filas=filas;
	this->cant_columnas=columnas;
	(this->m_pixels).redim_matriz(filas,columnas);
}


template <typename T>
void pgm<T>::mod_pixel(int i, int j, T dato)
{
	(this->m_pixels).mod_dato(i,j,dato);
}


template<typename T>
void pgm<T>::mod_magic_number(string new_magic_number)
{
	this->magic_number=new_magic_number;

}

template<typename T>
void pgm<T>::mod_cant_filas(int new_cant_filas)
{
	this->cant_filas=new_cant_filas;

}

template<typename T>
void pgm<T>::mod_cant_columnas(int new_cant_columnas)
{
	this->cant_columnas=new_cant_columnas;

}

template<typename T>
void pgm<T>::mod_int_max(int new_intensidad_maxima)
{
	this->intensidad_maxima=new_intensidad_maxima;

}

template<typename T>
void pgm<T>::mod_m_pixels(matriz<T> new_m_pixels)
{
	this->m_pixels=new_m_pixels;

}

template<typename T>
long int pgm<T>::obt_filas() const
{
	return this->cant_filas;
}

template<typename T>
long int pgm<T>::obt_columnas() const
{
	return this->cant_columnas;
}

template<typename T>
int pgm<T>::obt_int_max() const
{
	return this->intensidad_maxima;
}

template<typename T>
matriz<T> pgm<T>::obt_m_pixels() const
{
	return this->m_pixels;
}

template<typename T>
pgm<T>::~pgm()
{}

#endif
