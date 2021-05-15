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

/*********************************  read.h  ***********************************/
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

#ifndef READ_H
#define READ_H

/**************************** Symbolic  Constants *****************************/

/* ---------------------- Predefined Sizes of Strings ------------------------ */

#define MAX_ELEMENTS 100
#define MAX_TOKENS     5
#define STR_032       32
#define STR_256      256



/************************** Definition of Data Types **************************/

typedef char STRING_T[STR_032];

typedef struct {
	STRING_T word[MAX_TOKENS]; /* Single word in an input file  */
} TOKEN_T;

typedef enum {
	NONE, RESISTOR, CURRENT_SOURCE
} TYPE_T;

typedef struct {
	STRING_T element; /* Name of component  */
	int      n_pos;   /* Positive node (+)  */
	int      n_neg;   /* Negative node (-)  */
	double   value;   /* Value of component */
	TYPE_T   type;    /* Type of component  */   
} ELEMENT_T;



/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

int Read_File( char [], ELEMENT_T [], int );
int Print_Netlist( ELEMENT_T [], int );
int Get_Number_Nodes( ELEMENT_T [], int );
int Get_Number_Elements( ELEMENT_T [], int );
int Get_Type( ELEMENT_T [], int, int );
int Get_Node_Positive( ELEMENT_T [], int, int );
int Get_Node_Negative( ELEMENT_T [], int, int );
double Get_Value( ELEMENT_T [], int, int );

#endif /* READ_H */
