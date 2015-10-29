#ifndef COMPLEJO_H
#define COMPLEJO_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class complejo
{
	private:
		double real;
		double imag;
		double fase;
		double modulo;

	public:
		complejo();
		complejo(double re, double im);
		complejo(const complejo &);
		double obt_parte_real() const;
		double obt_parte_imag() const;
		double obt_fase() const;
		double obt_modulo() const;
		void mod_parte_real(double);
		void mod_parte_imag(double);
		void mod_fase(double);
        void mod_modulo(double);
		complejo operator+(const complejo &);
		complejo operator*(const complejo &);
		complejo operator/(const complejo &);
		complejo operator-(const complejo &);
		complejo operator^(const complejo &);
		complejo & operator=(const complejo & comp);
		complejo exp();
		complejo id();
		complejo ln();
		complejo abs();
		complejo re();
		complejo im();
		complejo phase();
		~complejo();
};

#endif
