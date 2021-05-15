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

/******************************************************************************/
/*                                                                            */
/* HOW TO COMPILE TO PRODUCE EXECUTABLE PROGRAM:                              */
/*                                                                            */
/*           gcc dc_solver.c  read.c  matrix.c  -o  dc_solver.exe             */
/*                                                                            */
/*                                                                            */
/* HOW TO RUN THE PROGRAM:                                                    */
/*                                                                            */
/*                          dc_solver  test_4.c                               */
/*                                                                            */
/******************************************************************************/

/********************************** Headers ***********************************/

/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------ Inclusion of Own Headers ------------------------ */

#include "read.h"
#include "matrix.h"



/************************* Definition of Global Data **************************/

//#include "testing_circuits.c"



/************************** Definition of Data Types **************************/

static ELEMENT_T netlist[MAX_ELEMENTS];
static double matrix[ROWS][COLS];



/********************************* Prototypes *********************************/

int Nodal_Formulation( ELEMENT_T [], int, double (*)[COLS], int );



/******************************* Main Function ********************************/

/*FN****************************************************************************
*
*   Purpose: Simulate DC circuits using the nodal matrix formulation
*
*   Plan:
*           Part 1: Handle arguments in command line
*           Part 2: Read file and prepare netlist array
*           Part 3: Print netlist from data in array to verify
*           Part 4: Prepare matrix with elements from netlist array
*           Part 5: Solve the matrix
*           Part 6: Deliver results to user
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Mar 01/19  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

int
main( int argc, char *argv[] )
{
int  nodes, elements;
char filename[STR_032] = { '\0' };

/* Part 1: Handle arguments in command line */

if( argc == 1 ) {
	fprintf( stderr, "Please ENTER filename: " );
	fscanf( stdin, "%s", filename );
} else if( argc == 2 ) {
	strcpy( filename, argv[1] );
} else {
	fprintf( stderr, "Usage: %s [ filename ]\n", argv[0] );
	exit( 1 );
}

/* Part 2: Read file and prepare netlist array */

Read_File( filename, netlist, MAX_ELEMENTS );

nodes    = Get_Number_Nodes( netlist, MAX_ELEMENTS );
elements = Get_Number_Elements( netlist, MAX_ELEMENTS );

/* Part 3: Print netlist from data in array to verify */

Print_Netlist( netlist, MAX_ELEMENTS );

/* Part 4: Prepare matrix with elements from netlist array */

Nodal_Formulation( netlist, elements, matrix, nodes );

/* Part 5: Solve the matrix */

Mtx_Gauss_Elimination( matrix, nodes, nodes+1 );
Mtx_Back_Substitution( matrix, nodes, nodes );

/* Part 6: Deliver results to user */

Write_Results( matrix, nodes, nodes );

return 0;

} /* main */



/*FN****************************************************************************
*
*   int Nodal_Formulation( ELEMENT_T net[], int elements,
*                          double mtx[ROWS][COLS], int nodes );
*
*   Purpose: Formulate a matrix to compute voltages in every node
*
*   Return:  Nothing
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Mar 01/19  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

int
Nodal_Formulation(
ELEMENT_T net[],           /* In: Netlist array */
int       elements,        /* In: Size of netlist array     */
double    mtx[ROWS][COLS], /* In/Out: Matrix to be computed */
int       nodes )          /* In: Matrix order == nodes     */
{
TYPE_T type;
int    n_pos, n_neg;
double value;

for( int i = 0; i < elements; i++ ) {

	type  = Get_Type( netlist, MAX_ELEMENTS, i );
	n_pos = Get_Node_Positive( netlist, MAX_ELEMENTS, i );
	n_neg = Get_Node_Negative( netlist, MAX_ELEMENTS, i );
	value = Get_Value( netlist, MAX_ELEMENTS, i );

	if( type == RESISTOR ) {

		if( n_pos != 0 )
			matrix[n_pos-1][n_pos-1] += 1.0/value;
		if( n_neg != 0 )
			matrix[n_neg-1][n_neg-1] += 1.0/value;
		if( n_pos != 0 && n_neg != 0 ) {
			matrix[n_neg-1][n_pos-1] += (-1.0/value);
			matrix[n_pos-1][n_neg-1] += (-1.0/value);
		}

	} else	if( type == CURRENT_SOURCE ) {

		if( n_pos != 0 )
			matrix[n_pos-1][nodes] += value;
		if( n_neg != 0 )
			matrix[n_neg-1][nodes] += (-value);

	}

} /* for */

return 1;

} /* Nodal_Formulation */
