#ifndef SY_H
#define SY_H

#include "common.hpp"
#include "pila.hpp"
#include "operador.hpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <ostream>





bool es_operador(char c)
{
	switch(c)
	{
	
		case '+':	return true;
					break;
		
		case '-':	return true;
					break;
		
		case '*':	return true;
					break;
		
		case '/':	return true;
					break;
					
		case '^' :	return true;
					break;		

		default:	return false;
					break;
	}
}

bool es_funcion(char c)
{
	switch(c)
	{			
		case 'e':	return true;
					break;
					
		case 'r':	return true;
					break;
		
		case 'l':	return true;
					break;
		
		case 'j':	return true;
					break;
		
		case 'a':	return true;
					break;
					
		case 'p':	return true;
					break;

		default:	return false;
					break;
	}
}




bool es_separador(char c)
{
	switch(c)
	{
		case '(':	return true;
					break;
		
		case ')':	return true;
					break;
		
		case 'i':	return true;
					break;
		
		case '.':	return true;
					break;
					
		default:	return false;
					break;
	}
}


status_t infijo_a_rpn(string expr, string & salida)
{
	
	pila<char> pila_op;
	
	size_t i=0;

	while(i<expr.length())
	{	
		
		char c1= expr[i]; //por ahora validaria numeros entre 0 y 10, mejorarloxpr	
		
		if(isdigit(c1)||c1=='z'||c1=='i')
		{ 	
			salida.push_back(c1);
			
			if(expr[i+1]=='.'||isdigit(expr[i+1]))
			{
				size_t j;
				if(expr[i+1]=='.')
				{	
					j=i+2;
					salida.push_back('.');
				}
				else
				j=i+1;

				while(isdigit(expr[j]))
				{
					salida.push_back(expr[j]);
					j++;
					i=j-1;
				}
			}
			
			salida.push_back('#');
			i++;
		}
		else
			if(c1=='n')
				{	
					salida.push_back('n');
					i++;
				}
			else if(es_funcion(c1)) 
			{

				pila_op.apilar(c1); //se agrega a stack
				i++;
			}
		
			else if(es_operador(c1))
			{
				if(i==expr.size()-1)
					return ERROR_EXPRESION;
			
				else
				{
					operador o1(c1); 
					asociacion_t a1=o1.obt_asociacion();
					precedencia_t p1=o1.obt_precedencia();
			
					char c2=pila_op.tope();

					operador o2;
					precedencia_t p2;
					asociacion_t a2;

					if(es_operador(c2))
					{
						operador aux(c2);
						a2=aux.obt_asociacion();
						p2=aux.obt_precedencia();
						o2.mod_op(c2,p2,a2);
					}
			
					while(	es_operador(c2)&&
							c2!=PAR_ABI&&
							(((a1==ASOC_IZQ)&&(p1<=p2))||((a1==ASOC_DER)&&(p1<p2))))
					{
						char c_aux=pila_op.desapilar();
				
						salida.push_back(c_aux);
				
						c2=pila_op.tope();
			
						if(es_operador(c2))
						{
							operador aux(c2);
							a2=aux.obt_asociacion();
							p2=aux.obt_precedencia();
							o2.mod_op(c2,p2,a2);
						}
					}
			
					pila_op.apilar(c1);
					i++;
				}
		}
		
		else if(c1==PAR_ABI)
		{
			pila_op.apilar(c1);
			i++;
		}
		
		else if(c1==PAR_CER)
		{
			while(pila_op.tope()!=PAR_ABI)
			{
				if(pila_op.vacia())
					return ERROR_PARENTESIS;
				
				char c_aux=pila_op.desapilar();
				salida.push_back(c_aux);	
			}
			
			pila_op.desapilar();
			
			char aux=pila_op.tope();
			
			if(es_funcion(aux))
			{
				pila_op.desapilar();
				salida.push_back(aux);
			}
			i++;
		}
	}
	
	while(!pila_op.vacia())
	{
		char aux=pila_op.tope();
		
		if(aux==PAR_CER||aux==PAR_ABI) //verificar si es cerrado o abierto o ambos
			return ERROR_PARENTESIS;
		
		char c_aux=pila_op.desapilar();
		salida.push_back(c_aux);
	}
	
	return OK;
}

#endif
