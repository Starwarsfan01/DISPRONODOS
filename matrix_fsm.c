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

#include <stdlib.h> // Due to exit
#include <stdio.h>  // Due to fprintf

/* ------------------------ Inclusion of Own Headers ------------------------ */

#include "matrix.h"



/************************** Prototypes of Functions ***************************/

/* --------------------------- Private Functions ---------------------------- */



/************************ Definition of the Structures ************************/



/************************** Definitions of Functions **************************/

/* ---------------------------- Public Functions ---------------------------- */

/*FN****************************************************************************
*
*   int Mtx_Zero( double mtx[][COLS], int max_i, int max_j );
*
*   Return:  Number "1" for SUCCEED
*
*   Purpose: Fill a matrix with zeros
*
*   Plan:    It is not necessary
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Spt 30/17  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

typedef enum {Mtx_Zero, Show_Mtx_Screen, Mtx_Gauss_Elimination, Mtx_Mtx_Back_Substitution, Write_Results} STATE_T;

int main()
{
    //Mtx_zero
    int max_i;
    int max_j;
    double mtx[ROWS][COLS];

    //show_Mtx_Sreen
    int   mtx_rows;
    int    mtx_cols;
    char   digits;
    double mtx[ROWS][COLS];

    STATE_T state = Mtx_Zero;
    while(TRUE)
    {
        switch (state)
        {
            case Mtx_Zero:
                register int jj; // la variable entera jj es puesta en el register, lugar mas rapido de acceder que la memoria
                register int ii; // la variable entera jj es puesta en el register, lugar mas rapido de acceder que la memoria

                for( ii = 0; ii < max_i; ii++ ) //ciclo for que inicia con ii==0 acaba cuando ii<max_i, incrementa en ii en 1 en cada iteracion
                {
                    for( jj = 0; jj < max_j; jj++ ) //ciclo for que inicia con jj==0 acaba cuando jj<max_i, incrementa en jj en 1 en cada iteracion
                    {
                        mtx[ii][jj] = 0.0;//en la posicion mtx(ii,jj) coloca 0
                    }
                }
            break;
            
            case Show_Mtx_Screen:
                register int jj;  /* Index for marching through columns */
                register int ii;  /* Index for marching through rows    */
                char width_value; /* Width between two values */

                    /* Part 1: Compute "width_value" from specified number of "digits" */

                    if( digits<LOWER_ACCURACY || digits>UPPER_ACCURACY ) //Si el dígito introducido está fuera de límites
                    {
                        digits = DEFAULT_ACCURACY;  //El digito introducido se asigna al valor por defecto [3]
                    }

                    width_value = digits + CHARS_PLUS_ONE;  //Se le asigna al tamaño del espacio en blanco el valor de el dígito introducido + 8 digitos

                    /* Part 2: Output row by row according to specified "mtx_cols" */

                    for( ii = 0; ii < mtx_rows; ii++ )  //Por cada fila de la matrix
                    {
                        for( jj = 0; jj < mtx_cols; jj++ )  //Por cada columna de la matrix
                        {
                            fprintf( stdout, "%*.*E%c", //Imprime <width_value> espacios en blanco seguido de un número en notación científica con <digits> cantidad de dígitos
                                    width_value, digits, mtx[ii][jj], (jj+1)%mtx_cols?' ':'\n' ); //Imprime el número y luego verifica si JJ está en la última columna, si está en la ultima columna imprime salto de línea, de lo contrario, imprime un espacio en blanco
                        }
                    }
            break;
            
            case Mtx_Gauss_Elimination:
                /* code */
            break;

            case Mtx_Mtx_Back_Substitution:
                /* code */
            break;

            case Write_Results:
                /* code */
            break;
        }
        
    }
}