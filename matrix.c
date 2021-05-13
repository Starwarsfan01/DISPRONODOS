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
static int Mtx_PivotMatrix(matrix_t, int, int);
static double pow(double, double);
static double abs_val(double);

/************************ Definition of the Structures ************************/

/************************** Definitions of Functions **************************/

/* --------------------------- Private Functions ---------------------------- */

/*FN****************************************************************************
*
*   static int Mtx_PivotMatrix(matrix_t, int, int);
*
*   Return:  Number "1" for SUCCEED
*            Number "0" for FAILURE
*
*   Purpose: Pivot matrix
*
*   Plan:    It is not necessary
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 12/21  Ángel D. Talero  Initial implementation
*
*******************************************************************************/
int Mtx_PivotMatrix(matrix_t mtx, int rows, int cols)
{
    // mtx[ROW][COL]
    // 1 . For every column in a square matrix
    for (register int j = 0; j < (rows < cols ? rows : cols); j++)
    {
        register int r_max = 0;
        // 2. For every row in the column starting from diagonal
        for (register int i = j; i < rows; i++)
        {
            if (mtx[i][j] > mtx[r_max][j])
                r_max = i;
        }

        // 3. Exchange rows if max value is not in the diagonal
        if (mtx[r_max][j] > mtx[j][j])
            if (!Mtx_Exchange_Rows(mtx, cols, r_max, j))
                return 0;
    }
    return 1;
}

/*FN****************************************************************************
*
*   static double pow(double, double);
*
*   Return:  <base> to the power of <exp>
*
*   Purpose: return the power of a number recursively
*
*   Plan:    It is not necessary
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 12/21  Ángel D. Talero  Initial implementation
*
*******************************************************************************/
double pow(double base, double exp)
{
    if (exp != 0.0)
        return (base * pow(base, exp - 1));
    else
        return 1;
}

/*FN****************************************************************************
*
*   static double abs_val(double);
*
*   Return:  Absolute value
*
*   Purpose: Absolute value of a double
*
*   Plan:    It is not necessary
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 12/21  Ángel D. Talero  Initial implementation
*
*******************************************************************************/
double abs_val(double n)
{
    if (n < 0)
        return n * -1.0;
    return n;
}

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
*            Number "0" for FAILURE
*
*   Purpose: Solve matrix by Gaussian elimination
*
*   Plan:   1. Apply matrix pivot
*           2. Apply gauss elimination algorithm:
*               A_k = A_k - A_i(a[k][i]/a[i][i]) (row echelon's form)
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE      COMMENT
*   -----------------------------------------------------------------------
*   Spt 30/17  J.C.Giraldo      Initial implementation
*   May 12/21  Ángel D. Talero  Implemented new algorithm
*
*******************************************************************************/
int Mtx_Gauss_Elimination(
    double mtx[][COLS], /* In/Out: Matrix to be computed */
    int rows,           /* In: Number of rows in matrix  */
    int cols)           /* In: Number of cols in matrix  */
{
    /** !OLD ALGORITHM(J.C.Giraldo ) if needed
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
    */

    // 1. Find pivot for every column [square matrix]
    if (!Mtx_PivotMatrix(mtx, rows, cols) ||
        (cols < rows /* Column validation guard */))
        return 0; //Error propagation

    // 2. Transform matrix into its row echelon's form (Forward Elimination)
    for (int i = 0; i < rows; i++)
        for (int k = i + 1; k < rows; ++k)
        {
            element_t factor = mtx[k][i] / mtx[i][i];
            for (int j = 0; j < cols; ++j)
                mtx[k][j] -= mtx[i][j] * factor;
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
*   May 12/21  Ángel D. Talero  Implemented new algorithm
*
*******************************************************************************/
int Mtx_Back_Substitution(
    double mtx[][COLS], /* In/Out: Matrix to be computed  */
    int order,          /* In:     Order of square matrix */
    int column)         /* In:     Independent vector     */
{
    /** !OLD ALGORITHM(J.C.Giraldo ) if needed
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
    */

    // Adjust column variable so it represents max_cols
    column++;

    // Backsubstitution
    int l_row = order - 1;
    for (register int i = l_row; i >= 0; i--)
    {
        element_t pivot = mtx[i][i];
        for (register int k = i - 1; k >= 0; k--)
        {
            element_t factor = (mtx[k][i] / pivot);
            for (register int j = 0; j < column; j++)
                mtx[k][j] -= mtx[i][j] * factor;
        }
        for (register int j = 0; j < column; j++)
            mtx[i][j] /= mtx[i][i];
    }

    return 1;
} /* Mtx_Back_Substitution */

/*FN****************************************************************************
*
*   int Write_Results( double mtx[ROWS][COLS], int order, int column );
*
*   Purpose: Write voltages in every node
*
*   Return:  Number "1" for SUCCEED
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

/*FN****************************************************************************
*
*   void Mtx_Gauss_Jordan(matrix_t, int, int);
*
*   Purpose: Matrix GaussJordan elimination algorithm
*
*   Return:  1 for SUCCESS
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 12/21  Ángel D. Talero  Initial implementation
*
*******************************************************************************/
int Mtx_Gauss_Jordan(matrix_t mtx, int rows, int cols)
{
    /*
    // 1. Gauss elimination
    if (!Mtx_Gauss_Elimination(mtx, rows, cols))
        return 0; // Error propagation

    // 2. Backsubstitution
    Mtx_Back_Substitution(mtx, rows, cols - 1);
    return 1;
    */

    int order = rows;
    int column = cols - 1;

    /* Applying Gauss Jordan Elimination */
    for (register int i = 0; i < order; i++)
    {
        if (mtx[i][i] == 0.0)
            return 0;

        for (register int j = 0; j < order; j++)
            if (i != j)
            {
                register element_t ratio = mtx[j][i] / mtx[i][i];
                for (register int k = 0; k < order + 1; k++)
                    mtx[j][k] = mtx[j][k] - ratio * mtx[i][k];
            }
    }

    for (register int i = 0; i < order; i++)
        mtx[i][column] = mtx[i][order] / mtx[i][i];

    //Identical matrix
    for (register int i = 0; i < order; i++)
        for (register int j = 0; j < order; j++)
            if (i == j)
                mtx[i][j] = 1.0;
            else
                mtx[i][j] = 0.0;

    return 1;
}

/*FN****************************************************************************
*
*   void Mtx_Exchange_Rows(matrix_t, int, int, int);
*
*   Purpose: Exchange two rows
*
*   Return:  Number "1" for SUCCEED
*            Number "0" for FAILURE
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 12/21  Ángel D. Talero  Initial implementation
*
*******************************************************************************/
int Mtx_Exchange_Rows(matrix_t mtx, int cols, int first, int second)
{
    if (first >= cols || second >= cols)
        return 0;

    for (register int i = 0; i < cols; i++)
    {
        element_t aux = mtx[first][i];
        mtx[first][i] = mtx[second][i];
        mtx[second][i] = aux;
    }
    return 1;
}

/*FN****************************************************************************
*
*   int Mtx_FixPresition(matrix_t, int, int, short);
*
*   Purpose: Fix matrix presition for 0 representation
*
*   Return:  Nothing
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 12/21  Ángel D. Talero  Initial implementation
*
*******************************************************************************/
int Mtx_FixPresition(
    matrix_t mtx,   /* In/Out: Matrix to be computed */
    int rows,       /* In: Number of rows in matrix  */
    int cols,       /* In: Number of cols in matrix  */
    short presition /* In: presition of the number in scientific notation*/
)
{
    // 1. Create a presition factor
    element_t factor = 1.0 / (element_t)pow(10, presition);

    // 2. Replace every element smaller than factor with 0
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if ((element_t)abs_val((element_t)mtx[i][j]) < factor)
                mtx[i][j] = 0.0;

    return 1;
}