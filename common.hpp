#ifndef COMMON_H
#define COMMON_H

#define SEP_ESPACIO " "
#define IDENTIDAD "z"
#define EXPONENCIAL "exp(z)"
#define MAGIC_NUMBER_PGM "P2"

#define F_ID 'I'
#define F_EXP 'E'
#define IDENTIF_COMENTARIO '#'

#define PAR_ABI '('
#define PAR_CER ')'

#define CANT_FUNCIONES 8

#define MSJ_FUNC_INCOMPATIBLE "Error: Funcion Incompatible"
#define MSJ_ERROR_VALIDAR_ARGUMENTOS "Error: Argumentos incorrectos"
#define MSJ_ERROR_ABRIR_ARCHIVO "Error: No se ha podido abrir el archivo o algun dato es invalido"
#define MSJ_ERROR_PROCESAMIENTO "Error: No se pudo procesar el archivo de entrada"
#define MSJ_ERROR_SALIDA "Error: No se pudo generar el archivo de salida"
#define MSJ_ERROR_INFIJO_RPN "Error: No se pudo hacer la conversion de Infijo a RPN"
#define MSJ_ERROR_VALIDACION "Error: Expresion invalida en la funcion"

typedef enum
{
	OK,
	ERROR_FORMATO_PGM,
	ERROR_TAMANIO,
	ERROR_RANGO_INTENSIDAD_MAX,
	ERROR_RANGO_INTENSIDAD,
	ERROR_PARENTESIS,
	ERROR_EXPRESION,
	ERROR_INFIJO_RPN,
	ERROR_VALIDACION
}status_t;

typedef enum
{
	PREC_CERO,
	PREC_UNO,
	PREC_DOS,
	PREC_TRES
}precedencia_t;

typedef enum
{
	ASOC_NO,
	ASOC_IZQ,
	ASOC_DER
}asociacion_t;


#endif
