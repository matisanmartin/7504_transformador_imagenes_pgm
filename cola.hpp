#ifndef COLA_H
#define COLA_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class cola
{
    private:
        T *dato;
        size_t tam_total;
        size_t tam_usado;
        size_t primero;
        size_t ultimo;
        void redimensionar();
        void incrementar(size_t &);

    public:
        cola();
        cola(size_t tam);
        cola(const cola & orig);
        ~cola();
        void encolar(const T &);
        T desencolar();
        T tope();
        bool vacia();

};

template <typename T>
void cola<T>::redimensionar()
{
	size_t m=(this->tam_total==0)?1:(2*this->tam_total);
	
	size_t n=this->tam_usado;
	
	T *v=new T[m];
	
	for(size_t i=0;i<n;i++)
		v[i]=this->datos[this->primero+i]%this->tam_total;   
		
	delete [] this->datos;
	
	this->datos=v;
	
	this->tam_total=m;
	this->primero=0;
	this->ultimo=n;
}

template <typename T>
cola<T>::~cola()
{
    delete [] this->dato;
}

template <typename T>
cola<T>::cola()
{
    this->dato=NULL;
    this->tam_total=0;
    this->tam_usado=0;
    this->primero=0;
    this->ultimo=0;
}

template <typename T>
cola<T>::cola(size_t tam)
{
    this->dato=new T[tam];
    this->tam_total=tam;
    this->tam_usado=0;
    this->primero=0;
    this->ultimo=tam-1;
}

template <typename T>
cola<T>::cola(const cola & orig)
{
    this->dato=new T[orig.tam_total];
    this->tam_total=orig.tam_total;
    this->tam_usado=orig.tam_usado;

    for(size_t i=orig.primero;i<orig.ultimo;i++)
        this->dato[i]=orig.dato[i];
}

template <typename T>
void cola<T>::encolar(const T & nuevo)
{
    if(this->tam_total==this->tam_usado)
        this->redimensionar();

    this->dato[this->ultimo]=nuevo;
    this->incrementar(this->ultimo);
    this->tam_usado++;
}

template<typename T>
void cola<T>::incrementar(size_t &i)
{
	i=(i+1)%this->tam_total;
}

template <typename T>
T cola<T>::desencolar()
{
    //validar tamanio 0

    T dato=this->dato[this->primero];
    this->incrementar(this->primero);
    this->tam_usado--;

    return dato;
}

template <typename T>
T cola<T>::tope()
{
	return this->dato[this->tam_usado-1];
}

template <typename T>
bool cola<T>::vacia()
{
	if(this->tam_usado==0)
		return true;
	else
		return false;
}

#endif
