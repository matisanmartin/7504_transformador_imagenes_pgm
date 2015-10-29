#ifndef OPERADOR_H
#define OPERADOR_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "complejo.hpp"
#include "common.hpp"

using namespace std;

class operador
{
	private:
		char ope;
		precedencia_t prec;
		asociacion_t asoc;
		complejo (*f)(complejo,complejo *);
		
	public:
		operador();
		operador(char,precedencia_t,asociacion_t);
		operador(const operador &);
		operador(char);
		char obt_operador() const;
		precedencia_t obt_precedencia() const;
		asociacion_t obt_asociacion() const;
		void mod_op(char,precedencia_t,asociacion_t);
		~operador();
		
};
		
#endif
