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

/*********************************  matrix.h  *********************************/
/*                                                                            */
/*   Purpose: Header that defines types of structures and public prototypes   */
/*                                                                            */
/*   Origin:  Module designed, tested and documented by Juan C. Giraldo       */
/*                                                                            */
/*   Notes:   None                                                            */
/*                                                                            */
/*   Register of Revisions (Debugging Process):                               */
/*                                                                            */
/*   DATE       RESPONSIBLE  COMMENT                                          */
/*   -----------------------------------------------------------------------  */
/*   Feb 28/19  J.C.Giraldo  Initial implementation                           */
/*                                                                            */
/******************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

/**************************** Symbolic  Constants *****************************/

/* --------------------- Predefined Sizes of Matrices ----------------------- */

#define ROWS 100  /* Maximum number of rows in a matrix    */
#define COLS 100  /* Maximum number of columns in a matrix */

/* The following constants are exclusively used in function Show_Mtx_Screen */

#define DEFAULT_ACCURACY 3  /* Number of digits by default */
#define LOWER_ACCURACY   2  /* Minimum number of digits to be shown */
#define UPPER_ACCURACY  18  /* Maximum number of digits to be shown */

#define CHARS_PLUS_ONE   8  /* Number of chars in scientific notation */



/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

int Show_Mtx_Screen( double (*)[COLS], int, int, char );
int Mtx_Gauss_Elimination( double (*)[COLS], int, int );
int Mtx_Back_Substitution( double (*)[COLS], int, int );
int Mtx_Zero( double (*)[COLS], int, int );
int Write_Results( double (*)[COLS], int, int );

#endif /* MATRIX_H */
