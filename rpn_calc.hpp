#ifndef RPN_CALC_H
#define RPN_CALC_H

#include <cstring>
#include "common.hpp"
#include "pila.hpp"
#include "operador.hpp"
#include "complejo.hpp"
#include "sy.hpp"

using namespace std;

template <typename T>
T rpn_calc(string expr, T cmp_in)
{
	
	pila<T> salida;
	int i=0,k=0,d=0;
	string aux=expr;
	size_t p;
	string delim="#";
			
	while(i<expr.length())
	{	
		k=0;
		if((isdigit(expr[i])&&(p=aux.find(delim,i))!=std::string::npos)||((expr[i]=='i')&&(p=aux.find(delim,i))!=std::string::npos)||((expr[i]=='n')&&(p=aux.find(delim,i))!=std::string::npos))
		{
				
				if(expr[i]=='i')
				{
					
					T cmp(0,1);
					salida.apilar(cmp);
					i=p+1;
				}
				else
				{	
					string nuevo;
					
					if(expr[i]=='n')
					{
							if(expr[i+1]=='i')
							{
								T cmp(0,-1);
								salida.apilar(cmp);
								k=p-i;
								d=1;				
							}
							else if(expr[i+1]=='z')
							{
								T cmp(-cmp_in.obt_parte_real(),-cmp_in.obt_parte_imag());	
								salida.apilar(cmp);		
								k=p-i;
								d=1;
							}
							else
							{
								nuevo.push_back('-');
								k=1;
							}
					}
						
					for(size_t j=k;j<(p-i);j++)
						nuevo.push_back(aux[i+j]);
					if(d==0)
					{
						double num=stod(nuevo);
						T cmp(num,0);
						salida.apilar(cmp);
					}
					i=p+1;
					
				}			
				
		}
		else if(expr[i]=='z')
		{
			 	salida.apilar(cmp_in);
			 	i+=2;
		}
			 
		else if(es_funcion(expr[i]))
		{	
			 	T cmp=salida.desapilar();
			 	
			 	switch(expr[i])
				{			
					case 'e':	cmp.exp();
								salida.apilar(cmp);
								i++;
								break;
					
					case 'r':	cmp.re();
								salida.apilar(cmp);
								i++;
								break;
		
					case 'l':	cmp.ln();
								salida.apilar(cmp);
								i++;
								break;
		
					case 'j':	cmp.im();
								salida.apilar(cmp);
								i++;
								break;
		
					case 'a':	cmp.abs();
								salida.apilar(cmp);
								i++;
								break;
					
					case 'p':	cmp.phase();
								salida.apilar(cmp);
								i++;
								break;
				}
			}
			
		else if(es_operador(expr[i]))
		{
				
			 	T cmp1=salida.desapilar();
				T cmp2=salida.desapilar();
				T cmp;
			 	switch(expr[i])
				{
	
					case '+':	
								cmp=cmp1+cmp2;
								salida.apilar(cmp);
								i++;
								break;
		
					case '-':	cmp=cmp2-cmp1;
								salida.apilar(cmp);
								i++;
								break;
		
					case '*':	cmp=cmp1*cmp2;
								salida.apilar(cmp);
								i++;
								break;
		
					case '/':	cmp=cmp2/cmp1;
								salida.apilar(cmp);
								i++;
								break;
					case '^':	cmp=cmp2^cmp1;
								salida.apilar(cmp);
								i++;
								break;

				}
		}
		
		{
		//cout<<salida.tope().obt_parte_real()<<" ";
		//cout<<salida.tope().obt_parte_imag()<<endl;	 
		}
	}
	//cout<<"end"<<endl;	
	{
		//cout<<salida.tope().obt_parte_real()<<" ";
		//cout<<salida.tope().obt_parte_imag()<<endl;	 
		}
	return salida.desapilar();

}
	



#endif

