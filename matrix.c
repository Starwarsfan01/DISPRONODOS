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

int Mtx_Zero(
    double mtx[][COLS], /* In/Out: Matrix to be initiated */
    int max_i,          /* In:     Number of rows         */
    int max_j)          /* In:     Number of columns      */
{
    register int jj;
    register int ii;

    for (ii = 0; ii < max_i; ii++)
        for (jj = 0; jj < max_j; jj++)
            mtx[ii][jj] = 0.0;

    return 1;

} /* Mtx_Zero */

/*FN****************************************************************************
*
*   int Show_Mtx_Screen( double (*mtx)[COLS],
*                        int mtx_rows, int mtx_cols, char digits );
*
*   Return:    Number "1" for SUCCEED
*
*   Purpose:   This function displays the contents of a bidimensional array.
*              The desired number of significant digits must be specified.
*              This parameter can be any number between 2 and 18 inclusive,
*              otherwise it will be used by default 3 significant digits.
*
*   Versions:
*         Version 1: Output to standard file (similar to Write_Mtx_Text)
*         Version 2: Output to screen with arrows
*
*   Notes:     - The literal constant 8 specifies the lowest number of
*                characters needed, besides the number of specified digits.
*                The next number in addition to the 3 digits, needs space
*                for 7 additional characters: -1.11E+300 and an extra space.
*              - It doesn't need a file name because output goes to screen.
*              - It has been checked before that the size of input file is
*                adequate.
*              - Include "conio.h", "dos.h"
*
*   Improvement Plan:
*              - Implement functions for Cursor_On and Cursor_Off
*              - Implement HELP
*              - With "mouse" and scroll bars
*              - Output to printer properly formatted
*
*   Plan:
*           Part 1: Compute "width_value" from specified number of "digits"
*           Part 2: Output row by row according to specified "mtx_cols"
*
*   Registro of Revisiones:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Jul 01/07  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

int Show_Mtx_Screen(
    double mtx[][COLS], /* In: Matrix to be printed */
    int mtx_rows,       /* In: Number of rows       */
    int mtx_cols,       /* In: Number of columns    */
    char digits)        /* In: Accuracy in number of significant digits */
{
    register int jj,  /* Index for marching through columns */
        ii;           /* Index for marching through rows    */
    char width_value; /* Width between two values */

    /* Part 1: Compute "width_value" from specified number of "digits" */

    if (digits < LOWER_ACCURACY || digits > UPPER_ACCURACY)
        digits = DEFAULT_ACCURACY;

    width_value = digits + CHARS_PLUS_ONE;

    /* Part 2: Output row by row according to specified "mtx_cols" */

    for (ii = 0; ii < mtx_rows; ii++)
        for (jj = 0; jj < mtx_cols; jj++)
            fprintf(stdout, "%*.*E%c",
                    width_value, digits, mtx[ii][jj], (jj + 1) % mtx_cols ? ' ' : '\n');

    return 1;

} /* Show_Mtx_Screen */

/*FN****************************************************************************
*
*   int Mtx_Gauss_Elimination( double mtx[ROWS][COLS], int rows, int cols );
*
*   Return:  Number "1" for SUCCEED
*
*   Purpose: Solve matrix by Gaussian elimination
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

int Mtx_Gauss_Elimination(
    double mtx[][COLS], /* In/Out: Matrix to be computed */
    int rows,           /* In: Number of rows in matrix  */
    int cols)           /* In: Number of cols in matrix  */
{
    register int jj, ii, diagonal;
    double temporal;

    if (cols < rows)
        return 0;

    for (diagonal = 0; diagonal < rows - 1; diagonal++)
        for (ii = diagonal + 1; ii < rows; ii++)
        {
            temporal = mtx[ii][diagonal] / mtx[diagonal][diagonal];
            for (jj = diagonal; jj < cols; jj++)
                mtx[ii][jj] = mtx[ii][jj] - temporal * mtx[diagonal][jj];
        }

    return 1;

} /* Mtx_Gauss_Elimination */

/*FN****************************************************************************
*
*   int Mtx_Back_Substitution( double mtx[][COLS], int order );
*
*   Return:  Number "1" for SUCCEED
*
*   Purpose: Perform a back substitution to solve set of linear equations
*
*   Plan:    It is not necessary
*
*   Source:  http://blog.abhishekg.com/2014/09/
*   gauss-elimination-method-in-c-language-using-lower-triangular-matrix/
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Spt 30/17  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

int Mtx_Back_Substitution(
    double mtx[][COLS], /* In/Out: Matrix to be computed  */
    int order,          /* In:     Order of square matrix */
    int column)         /* In:     Independent vector     */
{
    register int jj;
    register int ii;
    double temporal;

    for (ii = order - 1; ii >= 0; ii--)
    {
        temporal = mtx[ii][column];
        for (jj = ii + 1; jj < order + 1; jj++)
            temporal = temporal - mtx[ii][jj] * mtx[jj][column];
        mtx[ii][column] = temporal / mtx[ii][ii];
    }

    return 1;
} /* Mtx_Back_Substitution */

/*FN****************************************************************************
*
*   int Write_Results( double mtx[ROWS][COLS], int order, int column );
*
*   Purpose: Write voltages in every node
*
*   Return:  Nothing
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Feb 28/19  J.C.Giraldo  Initial empty implementation
*
*******************************************************************************/

int Write_Results(
    double mtx[][COLS], /* In: Matrix to be computed  */
    int order,          /* In: Order of square matrix */
    int column)         /* In: Column with voltages   */
{
    for (int ii = 0; ii < order; ii++)
        fprintf(stdout,
                "Voltage at node %d: %f volts\n", ii + 1, mtx[ii][column]);

    return 1;

} /* Write_Results */
