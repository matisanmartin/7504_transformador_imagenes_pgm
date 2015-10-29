#ifndef PILA_H
#define PILA_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class pila
{
    private:
        T *dato;
        size_t tam_total;
        size_t tam_usado;
        void redimensionar();

    public:
        pila();
        pila(size_t tam);
        pila(const pila & orig);
        ~pila();
        void apilar(const T &);
        T desapilar();
        T tope();
        bool vacia();

};

template <typename T>
void pila<T>::redimensionar()
{	
	if(this->tam_total==0)
	this->tam_total=1;
	
    T *nuevo=new T[this->tam_total+2*this->tam_usado];

    for(size_t i=0;i<this->tam_usado;i++)
        nuevo[i]=this->dato[i];

    delete [] this-> dato;
    this->dato=nuevo;
    this->tam_total=this->tam_total+this->tam_usado;
}

template <typename T>
pila<T>::~pila()
{
    delete [] this->dato;
}

template <typename T>
pila<T>::pila()
{
    this->dato=NULL;
    this->tam_total=0;
    this->tam_usado=0;
}

template <typename T>
pila<T>::pila(size_t tam)
{
    this->dato=new T[tam];
    this->tam_total=tam;
    this->tam_usado=0;
}

template <typename T>
pila<T>::pila(const pila & orig)
{
    this->dato=new T[orig.tam_total];
    this->tam_total=orig.tam_total;
    this->tam_usado=orig.tam_usado;

    for(size_t i=0;i<orig.tam_usado;i++)
        this->dato[i]=orig.dato[i];
}

template <typename T>
void pila<T>::apilar(const T & nuevo)
{
    if(this->tam_total==this->tam_usado)
        this->redimensionar();

    this->dato[tam_usado]=nuevo;
    this->tam_usado++;
}

template <typename T>
T pila<T>::desapilar()
{
    //validar tamanio 0 

    T dato=this->dato[this->tam_usado-1];
    this->tam_usado--;

    return dato;
}

template <typename T>
T pila<T>::tope()
{
	if(this->vacia())
		return T();
	else
		return this->dato[this->tam_usado-1];
}

template <typename T>
bool pila<T>::vacia()
{
	if(this->tam_usado==0)
		return true;
	else
		return false;
}

#endif
