#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "complejo.hpp"
#include "operador.hpp"
#include "common.hpp"

operador::operador()
{
	this->ope=' ';
	this->prec=PREC_CERO;
	this->asoc=ASOC_NO;
}

operador::operador(char o)
{
	
	if(o=='('||o==')')
	{
		this->prec=PREC_CERO;
		this->asoc=ASOC_NO;
	}
	else if(o=='+'||o=='-')
	{
		this->prec=PREC_UNO;
		this->asoc=ASOC_IZQ;
	}
	else if(o=='*'||o=='/')
	{
		this->prec=PREC_DOS;
		this->asoc=ASOC_IZQ;
	}
	else if(o=='^')
	{
		this->prec=PREC_TRES;
		this->asoc=ASOC_DER;
	}
	
}	

operador::operador(char o, precedencia_t p, asociacion_t a)
{
	this->ope=o;
	this->prec=p;
	this->asoc=a;
}

operador::operador(const operador & orig)
{
	this->ope=orig.ope;
	this->prec=orig.prec;
	this->asoc=orig.asoc;
}

char operador::obt_operador() const
{
	return this->ope;
}

precedencia_t operador::obt_precedencia() const
{
	return this->prec;
}

asociacion_t operador::obt_asociacion() const
{
	return this->asoc;
}

void operador::mod_op(char o, precedencia_t p, asociacion_t a)
{
	this->ope=o;
	this->prec=p;
	this->asoc=a;
}

operador::~operador()
{}



