#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#include "complejo.hpp"
#include "matriz.hpp"
#include "common.hpp"
#include "pila.hpp"
#include <cmath>
#include "rpn_calc.hpp"
#include "sy.hpp"

using namespace std;

template <typename T>
status_t leer_archivo_entrada(istream * stream_in,pgm<T> & pgm_in)
{
	int pixels_ancho,pixels_alto;
	int int_max;
	int contador_linea=0;
	bool cargar_matriz=false;
	
	string linea;

    while(getline((*stream_in),linea,'\n')&&(cargar_matriz==false))
	{
		if((contador_linea==0))
		{
			if (*linea.rbegin() == '\r')
       			 linea.erase(linea.length()-1);
			
			if(linea==MAGIC_NUMBER_PGM)
			{
				pgm_in.mod_magic_number(linea);
				contador_linea++;
			}
			else
				return ERROR_FORMATO_PGM;
		}
		else
		{
			if(linea[0]=='#')
				continue;
			else
			{
				stringstream stream_linea(linea);
				if(contador_linea==1)
				{
					stream_linea>>pixels_ancho;
					stream_linea>>pixels_alto;
					
					if(pixels_alto<=0 || pixels_ancho<=0)
						return ERROR_TAMANIO;
					
					pgm_in.mod_cant_filas(pixels_alto);
					pgm_in.mod_cant_columnas(pixels_ancho);
					
					contador_linea++;
				}
				else
				{
					stream_linea>>int_max;
					
					if(int_max<0||int_max>255)
						return ERROR_RANGO_INTENSIDAD_MAX;
	
					pgm_in.mod_int_max(int_max);
					
					contador_linea++;
					cargar_matriz=true;
					break;
				}
			}
		}
	}
	
	pgm_in.resize(pixels_alto,pixels_ancho);
		
	for(int i=0;i<pixels_alto;i++)
		for(int j=0;j<pixels_ancho;j++)
		{
			int int_temp;
			(*stream_in)>>int_temp;	
			
			if(int_temp<0||int_temp>int_max)
				return ERROR_RANGO_INTENSIDAD;
			
			pgm_in.mod_pixel(i,j,int_temp);
		}
			
	return OK;
}

/*status_t validar_funciones(string entrada)
{
	size_t i=0;
	
	while(i<entrada.length()-1)
	{
		char c=entrada[i];
		
		if(!isdigit(c)&&c!='('&&c!=z)
		{
			switch(c)
			{
				case 'l': 	if(entrada[i+1]!='n')
								return ERROR_VALIDACION;
							else
								i+=2;
							break;

				case 'r': 	if(entrada[i+1]!='e')
								return ERROR_VALIDACION;
							else
								i+=2;	
							break;

				case 'e': 	if(entrada[i+1]!='x')
								return ERROR_VALIDACION;
							else
							{
								if(entrada[i+2]!='p')
									return ERROR_VALIDACION;
								else
									i+=3;
							}
							break;	
							
				case 'a': 	if(entrada[i+1]!='b')
								return ERROR_VALIDACION;
							else
							{
								if(entrada[i+2]!='s')
									return ERROR_VALIDACION;
								else
									i+=3;
							}
							break;					

				case 'p': 	if(entrada[i+1]!='h')
								return ERROR_VALIDACION;
							else
							{
								if(entrada[i+2]!='a')
									return ERROR_VALIDACION;
								else
								{
									if(entrada[i+3]!='s')
										return ERROR_VALIDACION;
									else
									{
										if(entrada[i+4]!='e')
											return ERROR_VALIDACION;
										else
											i+=5;
									}
								}
							}
							break;		
				
				default: 	i++;
							break;	
			}
		}
		else
			i++;
	}
	
	return OK;
}*/

string parseo_funcion(string delim, string origen)
{
	string nuevo;
	string aux=origen;
	size_t p;
	size_t pos=0;
	bool mod=false;
		
	while((p=aux.find(delim,pos))!=std::string::npos)
	{
		mod=true;
		if(pos==0)
		{
			if(p==0)
			{	
				if(delim=="im")
					nuevo.push_back('j');
				else
					if(delim=="i")
					{
							if(isdigit(aux[p+1]))
							{
								nuevo.push_back('i');
								nuevo.push_back('*');
							}	
							else
							nuevo.push_back('i');
					}
					else
						if(delim=="-")
							{
								nuevo.push_back('(');
								nuevo.push_back('n');
								nuevo.push_back('1');
								nuevo.push_back(')');
								nuevo.push_back('*');
							}
						else
							nuevo.push_back(aux[p]);
			
			}
			else
			{
				for(size_t i=pos;i<p;i++)
				{
					nuevo.push_back(aux[i]);
				}
				
				if(delim=="im")
					nuevo.push_back('j');
				else 	
					if(delim=="i")
					{
						if(isdigit(aux[p-1]))
						{
							nuevo.push_back('*');
							nuevo.push_back('i');
						}
						else
							if(isdigit(aux[p+1]))
							{
								nuevo.push_back('i');
								nuevo.push_back('*');
							}	
							else
							nuevo.push_back('i');
					}	
				else
					if(delim=="-"&& !(aux[p-1]=='z'||aux[p-1]==')'||isdigit(aux[p-1])||aux[p-1]=='i'))
					{
								nuevo.push_back('(');
								nuevo.push_back('n');
								nuevo.push_back('1');
								nuevo.push_back(')');
								nuevo.push_back('*');
							}
					
					else
					nuevo.push_back(delim[0]);
			}	
		}
		else
		{
			for(size_t i=pos;i<p;i++)
				nuevo.push_back(aux[i]);
		
			if(delim=="im")
					nuevo.push_back('j');
				else 	
					if(delim=="i")
					{
						if(isdigit(aux[p-1]))
						{
							nuevo.push_back('*');
							nuevo.push_back('i');
						}
						else
							if(isdigit(aux[p+1])||aux[p+1]=='(')
							{
								nuevo.push_back('i');
								nuevo.push_back('*');
							}	
							else
							nuevo.push_back('i');
					}	
				else
					if(delim=="-"&& !(aux[p-1]=='z'||isdigit(aux[p-1])||aux[p-1]==')'||aux[p-1]=='i'))
					{
								nuevo.push_back('(');
								nuevo.push_back('n');
								nuevo.push_back('1');
								nuevo.push_back(')');
								nuevo.push_back('*');
							}
					else
					nuevo.push_back(delim[0]);
		}
		pos=p+delim.length();
	}
	if(mod)
	{
		string resto=aux.substr(pos);
		nuevo=nuevo+resto;
	}
	else
		nuevo=origen;
		
	return nuevo;
}

string parseo_total(string expr)
{

	const char* vector_funciones[CANT_FUNCIONES]={
													"-",
													"i",
													"exp",
													"ln",
													"re",
													"im",
													"abs",
													"phase"
												};	
												
	string nuevo=parseo_funcion(vector_funciones[0],expr);

	for(size_t i=1;i<(CANT_FUNCIONES);i++)
	{		
		nuevo=parseo_funcion(vector_funciones[i],nuevo);
	}

	return nuevo;
}




template<typename T>
status_t procesamiento(const pgm<T> & pgm_in, pgm<T>  & pgm_out,double ancho_real,double ancho_imag,string funcion)
{
	/*if(validar_funciones(funcion)!=OK)
	{
		cout<<MSJ_ERROR_VALIDACION<<endl;
		return ERROR_VALIDACION;
	}*/
	
	double Ap=pgm_in.obt_columnas();
	double Alp=pgm_in.obt_filas();
	
	double Au=ancho_real;
	double Alu=ancho_imag;
	
	double Xui=-((ancho_real)/2);
	double Yui=((ancho_imag)/2);
		
    matriz<int> m(pgm_in.obt_m_pixels());
    matriz<int> m_out(pgm_in.obt_m_pixels());
    
    string funcion_parseada=parseo_total(funcion);
    
	string funcion_rpn;
	
	if(infijo_a_rpn(funcion_parseada,funcion_rpn)!=OK)
	{
		return ERROR_INFIJO_RPN;
		cout<<MSJ_ERROR_INFIJO_RPN<<endl;
	}
	 cout<<funcion_rpn;
	for(int i=0;i<Alp;i++)

		for(int j=0;j<Ap;j++)
		{
  	    	complejo cmp_temp(Au*(j/Ap-0.5),Yui-(Alu*i)/(Alp-1));
							
            cmp_temp=rpn_calc(funcion_rpn,cmp_temp);
					
			double re=cmp_temp.obt_parte_real();
			double im=cmp_temp.obt_parte_imag();
				
			long int pos_x=nearbyint((Ap/Au)*(re-Xui));
			long int pos_y=nearbyint((Alp-1)*(Yui-im)/Alu);
		
			long int intensidad_nueva;

			if(re>-Xui||re<Xui||im>Yui||im<-Yui)
				intensidad_nueva=0;
			else
				intensidad_nueva=(m.obt_dato(pos_y,pos_x));
				
			m_out.mod_dato(i,j,intensidad_nueva);
		}
	pgm_out.mod_m_pixels(m_out);

	return OK;
}

template <typename T>
status_t imprimir_archivo_salida(ostream *os, const pgm<T> & pgm_out)
{
	
	(*os)<<MAGIC_NUMBER_PGM<<endl;

	(*os)<<pgm_out.obt_columnas()<<SEP_ESPACIO<<pgm_out.obt_filas()<<endl;

	(*os)<<pgm_out.obt_int_max()<<endl;

	(*os)<<pgm_out.obt_m_pixels()<<endl;
	
	
	return OK;
}

#endif
