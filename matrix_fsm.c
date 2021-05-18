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
*   Source: J.C Giraldo's initial algorithm
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 17/21  Talero, A.D  Initial implementation
*
*******************************************************************************/
int Mtx_Zero(double mtx[][COLS], int max_i, int max_j)
{
    typedef enum
    {
        STATE0,
        STATE1,
    };
    static state = STATE0;

    register int ii;
    register int jj;

    ii = 0;

    while (1)
    {
        switch (state)
        {
        case STATE0:
            if (ii < max_i)
            {
                jj = 0;
                state = STATE1;
            }

            else if (ii >= max_i)
            {
                return 1;
            }

            break;

        case STATE1:
            if (jj < max_j)
            {
                mtx[ii][jj] = 0;
                jj++;
                state = STATE1;
            }

            else if (jj >= max_j)
            {
                ii++;
                state = STATE0;
            }

            break;
        }
    }

    return 0;
}

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
*   Source: J.C Giraldo's initial algorithm and 
*           Caicedo, J.J's FSM algorith diagram
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 17/21  Conde, J.D   Initial implementation
*
*
*******************************************************************************/
int Show_Mtx_Screen(double mtx[][COLS], int mtx_rows, int mtx_cols, char digits)
{
    typedef enum
    {
        STATE0,
        STATE1,
        STATE2
    };

    static state = STATE0;

    register int ii;
    register int jj;
    char width_value;

    while (1)
    {
        switch (state)
        {
        case STATE0:
            if (digits < LOWER_ACCURACY || digits > UPPER_ACCURACY)
            {
                digits = DEFAULT_ACCURACY;
                width_value = digits + CHARS_PLUS_ONE;
                ii = 0;

                state = STATE1;
            }
            else
            {
                width_value = digits + CHARS_PLUS_ONE;
                ii = 0;

                state = STATE1;
            }
            break;

        case STATE1:
            if (ii < mtx_rows)
            {
                jj = 0;
                state = STATE2;
            }
            else if (ii == mtx_rows)
            {
                return 1;
            }
            break;

        case STATE2:
            if (jj == mtx_cols)
            {
                ii = ii + 1;

                state = STATE1;
            }
            else if (jj < mtx_cols)
            {
                fprintf(stdout, "%*.*E%c",
                        width_value, digits, mtx[ii][jj], (jj + 1) % mtx_cols ? ' ' : '\n');
                jj = jj + 1;

                state = STATE2;
            }
            break;
        }
    }
    return 1;
}

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
*   Source: J.C Giraldo's initial algorithm and 
*           Caicedo, J.J's FSM algorith diagram
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 17/21  Conde, J.D   Initial implementation
*   May 17/21  Talero, A.D  Fixed bug
*
*
*******************************************************************************/
int Mtx_Gauss_Elimination(double mtx[][COLS], int rows, int cols)
{
    typedef enum
    {
        STATE0,
        STATE1,
        STATE2,
        STATE3
    };

    static state = STATE0;

    register int ii;
    register int jj;
    register int diagonal;
    double temporal = 0.0;

    while (1)
    {
        switch (state)
        {
        case STATE0:
            if (cols >= rows)
            {
                diagonal = 0;
                state = STATE1;
            }
            else if (cols < rows)
            {
                return 0;
            }
            break;

        case STATE1:
            if (diagonal < rows - 1)
            {
                ii = diagonal + 1;
                state = STATE2;
            }

            else if (diagonal >= rows - 1)
            {
                return 1;
            }
            break;

        case STATE2:
            if (ii >= rows)
            {
                diagonal++;
                state = STATE1;
            }
            else if (ii < rows)
            {
                temporal = mtx[ii][diagonal] / mtx[diagonal][diagonal];
                jj = diagonal;
                state = STATE3;
            }
            break;

        case STATE3:
            if (jj < cols)
            {
                mtx[ii][jj] = mtx[ii][jj] - temporal * mtx[diagonal][jj];
                jj++;
                state = STATE3;
            }
            else
            {
                ii++;
                state = STATE2;
            }
            break;
        }
    }
    return 1;
}

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
*   and Caicedo, J.J's FSM algorith diagram
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 17/21  Conde, J.D   Initial implementation
*   May 17/21  Talero, A.D  Fixed bug
*
*
*******************************************************************************/
int Mtx_Back_Substitution(
    double mtx[][COLS], int order, int column)
{
    typedef enum
    {
        STATE0,
        STATE1
    };
    static state = STATE0;

    register int jj;
    register int ii;
    double temporal;

    ii = order - 1;

    while (1)
    {
        switch (state)
        {
        case STATE0:
            if (ii >= 0)
            {
                temporal = mtx[ii][column];
                jj = ii + 1;
                state = STATE1;
            }
            else
            {
                return 1;
            }
            break;

        case STATE1:
            if (jj < order + 1)
            {
                temporal = temporal - mtx[ii][jj] * mtx[jj][column];
                jj++;
                state = STATE1;
            }
            else
            {
                mtx[ii][column] = temporal / mtx[ii][ii];
                ii--;
                state = STATE0;
            }
            break;
        }
    }
    return 1;
}

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
*   Source: J.C Giraldo's initial algorithm and 
*           Caicedo, J.J's FSM algorith diagram
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 17/21  Conde, J.D   Initial implementation
*   May 17/21  Talero, A.D  Fixed bug
*
*******************************************************************************/
int Write_Results(double mtx[][COLS], int order, int column)
{
    typedef enum
    {
        STATE0
    };
    static state = STATE0;

    register int ii = 0;

    while (1)
    {
        switch (state)
        {
        case STATE0:
            if (ii < order)
            {
                fprintf(stdout,
                        "Voltage at node %d: %f volts\n", ii + 1, mtx[ii][column]);
                ii++;
                state = STATE0;
            }

            else
            {
                return 1;
            }

            break;
        }
    }

    return 1;
}