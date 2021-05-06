/* Ruler 1         2         3         4         5         6         7        */

/******************************************************************************/
/*                                                                            */
/*                _____   _____    _____       _                              */
/*               |  __ \ / ____|  / ____|     | |                             */
/*               | |  | | |      | (___   ___ | |_   _____ _ __               */
/*               | |  | | |       \___ \ / _ \| \ \ / / _ \ '__|              */
/*               | |__| | |____   ____) | (_) | |\ V /  __/ |                 */
/*               |_____/ \_____| |_____/ \___/|_| \_/ \___|_|   (C)           */
/*                                                                            */
/*    Written in 2019 by Juan-Carlos Giraldo <jcgiraldo@javeriana.edu.co>     */
/*                                                                            */
/* Letters created with "Big" font using http://www.network-science.de/ascii/ */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*    DC Solver provides a minimalistic simulator using nodal formulation.    */
/*                                                                            */
/*    Copyright (C) 2019 Juan-Carlos Giraldo                                  */
/*                                                                            */
/*    This file is part of DC Solver.                                         */
/*                                                                            */
/*    DC Solver is free software: you can redistribute it and/or modify       */
/*    it under the terms of the GNU General Public License as published by    */
/*    the Free Software Foundation, either version 3 of the License, or       */
/*    (at your option) any later version.                                     */
/*                                                                            */
/*    DC Solver is distributed in the hope that it will be useful,            */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/*    GNU General Public License for more details.                            */
/*                                                                            */
/*    You should have received a copy of the GNU General Public License       */
/*    along with DC Solver.  If not, see <http://www.gnu.org/licenses/>.      */
/*                                                                            */
/******************************************************************************/

/********************************** Headers ***********************************/

/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------ Inclusion of Own Headers ------------------------ */

#include "read.h"  /* Due to: Structures in read file & prototypes */



/************************** Prototypes of Functions ***************************/

/* --------------------------- Private Functions ---------------------------- */

static int Get_Tokens( TOKEN_T *token, char str[] );
static int Clear_Buffers( char *b0, char *b1, char *b2, char *b3, char *b4 );



/************************** Definitions of Functions **************************/

/* ---------------------------- Public Functions ---------------------------- */

/*FN****************************************************************************
*
*   int Read_File( char filename[], ELEMENT_T net[], int size );
*
*   Purpose: Read every line of input file and get tokens
*
*   Return:  Number of lines_read
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Feb 28/19  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

int
Read_File(
char      filename[], /* In:  Name of input file   */
ELEMENT_T net[],      /* Out: Array with netlist   */ 
int       size )      /* In:  Max. Size of netlist */
{
FILE *file_ptr;
char string[STR_256];

TOKEN_T token;

int lines_read = 0;

/* Part 1: Open input file */

file_ptr = fopen( filename, "rt" );
if( file_ptr == NULL ) {
    fprintf( stderr, "Error opening file.\n" );
    exit( 1 );
}

/* Part 2: For every single line: */

while( !feof( file_ptr ) ) {

/* Part 3: Read it, save it & extract tokens */

	if( fgets( string, sizeof( string ), file_ptr ) != NULL ) {

		Get_Tokens( &token, string );

		if( token.word[0][0] == '.' ) {

//			Process_Command();

		} else {

			if( token.word[0][0] == 'R' ||
				token.word[0][0] == 'r' )
					net[lines_read].type = RESISTOR;
			else if( token.word[0][0] == 'I' ||
				token.word[0][0] == 'i' )
					net[lines_read].type = CURRENT_SOURCE;
			else
					net[lines_read].type = NONE;

			strcpy( net[lines_read].element, token.word[0] );
			net[lines_read].n_pos = atoi( token.word[1] );
			net[lines_read].n_neg = atoi( token.word[2] );
			net[lines_read].value = atof( token.word[3] );

		} /* else or not a dot */

	} /* if fgets */

	lines_read++;

} /* while EOF */

/* Part 4: Close files */

(void)fclose( file_ptr );

return lines_read;

} /* Read_File */



/*FN****************************************************************************
*
*   int Print_Netlist( ELEMENT_T net[], int size );
*
*   Purpose: Print the netlist
*
*   Return:  Nothing
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May --/21  -----------  Initial implementation
*
*******************************************************************************/

int
Print_Netlist(
ELEMENT_T net[], /* In: Netlist */
int       size ) /* In: Size of netlist */
{
int max = Get_Number_Elements( net, size );

/*
 * En el cuerpo de esta funcion, cada equipo debe escribir un codigo que
 * realiza la funcion descrita arriba en "Purpose"
 *
 * OJO: BORRE ESTE COMENTARIO ANTES DE ENTREGAR SU CODIGO AL PROFESOR
 *
 */

return 1;

} /* Print_Netlist */



/*FN****************************************************************************
*
*   int Get_Number_Nodes( ELEMENT_T net[], int size );
*
*   Purpose: Get the number of nodes in netlist
*
*   Return:  number_of_nodes in netlist
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May --/21  -----------  Initial implementation
*
*******************************************************************************/

int
Get_Number_Nodes(
ELEMENT_T net[], /* In: Netlist */
int       size ) /* In: Size of netlist */
{
int number_of_nodes = 0;

/*
 * En el cuerpo de esta funcion, cada equipo debe escribir un codigo que
 * realiza la funcion descrita arriba en "Purpose"
 *
 * OJO: BORRE ESTE COMENTARIO ANTES DE ENTREGAR SU CODIGO AL PROFESOR
 *
 */

return number_of_nodes;

} /* Get_Number_Nodes */



/*FN****************************************************************************
*
*   int Get_Number_Elements( ELEMENT_T net[], int size );
*
*   Purpose: Get the value of component in index
*
*   Return:  number_of_elements in netlist
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May --/21  -----------  Initial implementation
*
*******************************************************************************/

int
Get_Number_Elements(
ELEMENT_T net[], /* In: Netlist */
int       size ) /* In: Size of netlist */
{
int ii = 0, number_of_elements = 0;

/*
 * En el cuerpo de esta funcion, cada equipo debe escribir un codigo que
 * realiza la funcion descrita arriba en "Purpose"
 *
 * OJO: BORRE ESTE COMENTARIO ANTES DE ENTREGAR SU CODIGO AL PROFESOR
 *
 */

return number_of_elements;

} /* Get_Number_Elements */



/*FN****************************************************************************
*
*   int Get_Type( ELEMENT_T net[], int size, int index );
*
*   Purpose: Get the type of component in index
*
*   Return:  Type of component and NONE otherwise
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May --/21  -----------  Initial implementation
*
*******************************************************************************/

int
Get_Type(
ELEMENT_T net[],  /* In: Netlist */
int       size,   /* In: Size of netlist */
int       index ) /* In: Element in netlist */
{

/*
 * En el cuerpo de esta funcion, cada equipo debe escribir un codigo que
 * realiza la funcion descrita arriba en "Purpose"
 *
 * OJO: BORRE ESTE COMENTARIO ANTES DE ENTREGAR SU CODIGO AL PROFESOR
 *
 */

} /* Get_Type */



/*FN****************************************************************************
*
*   double Get_Value( ELEMENT_T net[], int size, int index );
*
*   Purpose: Get the value of component in index
*
*   Return:  Value of component and 0 otherwise
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May --/21  -----------  Initial implementation
*
*******************************************************************************/

double
Get_Value(
ELEMENT_T net[],  /* In: Netlist */
int       size,   /* In: Size of netlist */
int       index ) /* In: Element in netlist */
{

/*
 * En el cuerpo de esta funcion, cada equipo debe escribir un codigo que
 * realiza la funcion descrita arriba en "Purpose"
 *
 * OJO: BORRE ESTE COMENTARIO ANTES DE ENTREGAR SU CODIGO AL PROFESOR
 *
 */

} /* Get_Value */



/*FN****************************************************************************
*
*   int Get_Node_Positive( ELEMENT_T net[], int size, int index );
*
*   Purpose: Get the positive node specified in index
*
*   Return:  Number of node and -1 otherwise
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May --/21  -----------  Initial implementation
*
*******************************************************************************/

int
Get_Node_Positive(
ELEMENT_T net[],  /* In: Netlist */
int       size,   /* In: Size of netlist */
int       index ) /* In: Element in netlist */
{

/*
 * En el cuerpo de esta funcion, cada equipo debe escribir un codigo que
 * realiza la funcion descrita arriba en "Purpose"
 *
 * OJO: BORRE ESTE COMENTARIO ANTES DE ENTREGAR SU CODIGO AL PROFESOR
 *
 */

} /* Get_Node_Positive */



/*FN****************************************************************************
*
*   int Get_Node_Negative( ELEMENT_T net[], int size, int index );
*
*   Purpose: Get the negative node specified in index
*
*   Return:  Number of node and -1 otherwise
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May --/21  -----------  Initial implementation
*
*******************************************************************************/

int
Get_Node_Negative(
ELEMENT_T net[],  /* In: Netlist */
int       size,   /* In: Size of netlist */
int       index ) /* In: Element in netlist */
{

/*
 * En el cuerpo de esta funcion, cada equipo debe escribir un codigo que
 * realiza la funcion descrita arriba en "Purpose"
 *
 * OJO: BORRE ESTE COMENTARIO ANTES DE ENTREGAR SU CODIGO AL PROFESOR
 *
 */

} /* Get_Node_Negative */



/* --------------------------- Private Functions ---------------------------- */

/*FN****************************************************************************
*
*   static int Clear_Buffers( char *b0, char *b1, char *b2, char *b3 );
*
*   Purpose: Clear buffers before reading tokens
*
*   Return:  Nothing
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Oct 20/17  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

static int
Clear_Buffers( char *b0, char *b1, char *b2, char *b3, char *b4 )
{
*b0 = *b1 = *b2 = *b3 = *b4 = '\0';

return 1;

} /* Clear_Buffers */



/*FN****************************************************************************
*
*   static int Get_Tokens( TOKEN_T *token, char str[] );
*
*   Purpose: Read every line and get tokens
*
*   Return:  Nothing
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Oct 31/17  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

static int
Get_Tokens(
TOKEN_T *token, /* Out: Returned tokens */
char    str[] ) /* In:  Line of file    */
{
Clear_Buffers( token->word[0], token->word[1],
			token->word[2], token->word[3], token->word[4] );
sscanf( str, "%s %s %s %s %s", token->word[0], token->word[1],
			token->word[2], token->word[3], token->word[4] );

return 1;

} /* Get_Tokens */
