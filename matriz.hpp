#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <cstdlib>
#include "common.hpp"

using namespace std;

template<typename T>
class matriz
{
	private:
		long int filas;
		long int columnas;
		T** dato;

	public:
		matriz();
		matriz(long int filas, long int columnas);
		matriz(const matriz &);
		void mod_dato(int,int,T);
		void mod_dato(T **);
		long int obt_cant_filas() const;
		long int obt_cant_col() const;
		T & obt_dato(int,int) const;
		T ** obt_dato() const;
		matriz<T> & operator=(const matriz<T> & m);
		void redim_matriz(int new_fil, int new_col);
		~matriz();
};

template<typename T>
matriz<T>::matriz()
{
	this->filas=1;
	this->columnas=1;
	this->dato=new T*[1];
	
	this->dato[0]=new T[1];
	this->dato[0][0]=0;
}

template<typename T>
matriz<T>::matriz(long int filas, long int columnas)
{

	this->filas=filas;
	this->columnas=columnas;

	T **m = new T*[filas];

	for(unsigned int i=0;i<filas;i++)
		m[i]=new T[columnas];


	for(unsigned int  i=0; i<filas;i++)
		for(unsigned int  j=0; j<columnas;j++)
			m[i][j]=0;

	this->dato=m;
}

template<typename T>
matriz<T>::matriz(const matriz &orig)
{

	this->filas=orig.filas;
	this->columnas=orig.columnas;

	this->dato= new T*[orig.filas];

	for(int i=0;i<filas;i++)
		this->dato[i]=new T[orig.columnas];

	for(int i=0;i<orig.filas;i++)
		for(int j=0;j<orig.columnas;j++)
			this->dato[i][j]=orig.obt_dato(i,j);

}

template<typename T>
matriz<T> & matriz<T>::operator=(const matriz<T> & m)
{
	if(this == &m)
		return *this;
	else
	{ 	
		for(unsigned int  j=0;j<this->filas;j++)
			delete[] this->dato[j];
		
		delete[] this->dato;
				
		this->filas=m.filas;
		this->columnas=m.columnas;	
		this->dato= new T*[m.filas];

		for(int i=0;i<filas;i++)
			this->dato[i]=new T[m.columnas];

		for(int i=0;i<m.filas;i++)
			for(int j=0;j<m.columnas;j++)
				this->dato[i][j]=m.obt_dato(i,j);
	}
	return *this;
}

template <typename T>
ostream& operator<<(ostream &os, const matriz<T> & m)
{
	for(int i=0;i<m.obt_cant_filas();i++)
	{
		for(int j=0;j<m.obt_cant_col();j++)
			os<<m.obt_dato(i,j)<<SEP_ESPACIO;

		os<<endl;
	}

	return os;
}

template <typename T>
void matriz<T>::mod_dato(T **p)
{
	this->dato=p;
}



template<typename T>
void matriz<T>::mod_dato(int i,int j,T dato)
{
	this->dato[i][j]=dato;
}

template<typename T>
T ** matriz<T>::obt_dato() const
{
	return this->dato;
}

template<typename T>
long int matriz<T>::obt_cant_filas() const
{
	return this->filas;
}

template<typename T>
long int matriz<T>::obt_cant_col() const
{
	return this->columnas;
}

template <typename T>
T & matriz<T>::obt_dato(int i, int j) const
{
	return this->dato[i][j];
}
template <typename T>
void matriz<T>::redim_matriz(int new_fil, int new_col)
{
	matriz<T> aux(new_fil,new_col);
	
	*this=aux;

}

template<typename T>
matriz<T>::~matriz()
{
	for(unsigned int  j=0;j<this->filas;j++)
		delete[] this->dato[j];

	delete[] this->dato;

}

#endif
