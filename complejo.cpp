#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "complejo.hpp"

complejo::complejo()
{
	this->real=0;
	this->imag=0;
	this->modulo=0;
	this->fase=0;
}

complejo::complejo(double re, double im)
{
	this->real=re;
	this->imag=im;

	this->modulo=sqrt(re*re+im*im);

	if(re==0)
        this->fase=atan(1)*2;
    else
        this->fase=atan(im/re);

}

complejo::complejo(const complejo & comp)
{
	this->real=comp.real;
	this->imag=comp.imag;
	this->modulo=comp.modulo;
	this->fase=comp.fase;
}

double complejo::obt_parte_real() const
{
	return this->real;
}

double complejo::obt_parte_imag() const
{
	return this->imag;
}

double complejo::obt_modulo() const
{
    return this->modulo;
}

double complejo::obt_fase() const
{
    return this->fase;
}

void complejo::mod_parte_real(double re)
{
	this->real=re;
}

void complejo::mod_fase(double f)
{
    this->fase=f;
}

void complejo::mod_modulo(double m)
{
    this->modulo=m;
}

void complejo::mod_parte_imag(double im)
{
	this->imag=im;
}


complejo & complejo::operator=(const complejo & comp)
{
	if(this != &comp)
	{
		this->real=comp.real;
		this->imag=comp.imag;
		this->fase=comp.fase;
		this->modulo=comp.modulo;
	}

	return *this;
}
 complejo complejo::operator+(const complejo & comp)
 {
	 complejo suma(real+comp.real,imag+comp.imag);
	 suma.modulo=sqrt(suma.real*suma.real+suma.imag*suma.imag);

	 if(suma.real==0&&suma.imag<0)
        suma.fase=-atan(1)*2;
     else if(suma.real==0&&suma.imag>0)
        suma.fase=atan(1)*2;
     else
        suma.fase=atan(suma.imag/suma.real);

	 return suma;
 }

 complejo complejo::operator*(const complejo & comp)
 {
	 complejo mult((real*comp.real)-(imag*comp.imag),(real*comp.imag)+(imag*comp.real));

	 return mult;
 }
 
 complejo complejo::operator^(const complejo & orig)
 {
 	complejo aux1=*this;
 	
 	aux1.ln();
 	
 	complejo aux2=aux1*orig;
 	
 	return aux2.exp();
 }

complejo complejo::operator/(const complejo &comp)
{
    this->modulo=this->modulo/comp.modulo;
    this->fase=this->fase-comp.fase;
    this->real=this->modulo*cos(this->fase);
    this->imag=this->modulo*sin(this->fase);

    return *this;
}
complejo complejo::operator-(const complejo &comp)
{
    complejo resta(real-comp.real,imag-comp.imag);
    resta.modulo=sqrt(resta.real*resta.real+resta.imag*resta.imag);
    if(resta.real==0&&resta.imag<0)
        resta.fase=-atan(1)*2;
     else if(resta.real==0&&resta.imag>0)
        resta.fase=atan(1)*2;
     else
        resta.fase=atan(resta.imag/resta.real);
    return resta;
}
complejo complejo::exp()
{
	double a=this->real;
	double b=this->imag;

    this->real=::exp(a)*cos(b);
    this->imag=::exp(a)*sin(b);
    this->modulo=sqrt(real*real+imag*imag);
   	if(real==0&&imag<0)
        this->fase=-atan(1)*2;
	 else if(real==0&&imag>0)
        this->fase=atan(1)*2;
     else
        this->fase=atan(imag/real);

    return *this;
}

complejo complejo::id()
{
	return *this;
}

complejo complejo::ln()
{
    this->real=log(this->modulo);
    this->imag=this->fase;
    this->modulo=sqrt(real*real+imag*imag);
   	if(real==0&&imag<0)
        this->fase=-atan(1)*2;
	 else if(real==0&&imag>0)
        this->fase=atan(1)*2;
     else
        this->fase=atan(imag/real);

    return *this;
}

complejo complejo::phase()
{
   this->real=this->fase;
   this->imag=0;
    this->modulo=sqrt(real*real);
   if(real<0)
    	this->fase=atan(1)*4;
    else if(real>0)
        this->fase=0;
     else
        this->fase=atan(imag/real);
    
    return *this;
}

complejo complejo::im()
{
    this->real=0;
    this->modulo=sqrt(imag*imag);
   	if(imag<0)
        this->fase=-atan(1)*2;
	 else if(imag>0)
        this->fase=atan(1)*2;
     else
        this->fase=atan(imag/real);

    
    return *this;
}

complejo complejo::re()
{
    this->imag=0;
    this->modulo=sqrt(real*real);
    if(real<0)
    	this->fase=atan(1)*4;
    else if(real>0)
        this->fase=0;
     else
        this->fase=atan(imag/real);
    
    return *this;
}

complejo complejo::abs()
{
    this->real=this->modulo;
    this->imag=0;
    this->fase=0;
    return *this;
}

complejo::~complejo(){}

