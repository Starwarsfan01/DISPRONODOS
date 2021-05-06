/* Ruler 1         2         3         4         5         6         7        */

/**************************** Symbolic  Constants *****************************/

/* The following constants will be used for testing some basic circuits */

#define R1 1000.0
#define R2 1000.0
#define R3 1000.0
#define R4 1000.0



static ELEMENT_T netlist_1[MAX_ELEMENTS] = {
	{ "I_input", 1, 0, 0.001, CURRENT_SOURCE },
	{ "R1", 1, 0, 1000.0, RESISTOR },
	{ "R2", 1, 0, 1000.0, RESISTOR },
	{ "R3", 1, 0, 1000.0, RESISTOR }
};

static ELEMENT_T netlist_2[MAX_ELEMENTS] = {
	{ "I_input", 1, 0, 0.001, CURRENT_SOURCE },
	{ "R1", 1, 2, 1000.0, RESISTOR },
	{ "R2", 2, 3, 1000.0, RESISTOR },
	{ "R3", 3, 0, 1000.0, RESISTOR }
};

static ELEMENT_T netlist_3[MAX_ELEMENTS] = {
	{ "I_input", 1, 2, 0.001, CURRENT_SOURCE },
	{ "R1", 1, 0, 1000.0, RESISTOR },
	{ "R2", 2, 3, 1000.0, RESISTOR },
	{ "R3", 3, 0, 1000.0, RESISTOR },
	{ "R4", 3, 0, 1000.0, RESISTOR }
};



/*******************************************************************************
*
*  Assuming the following solution for x, y, z:
*
*  x =  3;
*  y =  2;
*  z = -1;
*
*  3x - 1y + 2z = 5
*   9 -  2 -  2 = 5
*
*  2x + 5y - 2z = 18
*   6 + 10 +  2 = 18
*
*  1x - 1y - 2z = 3
*   3 -  2 +  2 = 3
*
*******************************************************************************/

static double matrix1[ROWS][COLS] = {
    { 3.0, -1.0, +2.0,  5.0 },
    { 2.0,  5.0, -2.0, 18.0 },
    { 1.0, -1.0, -2.0,  3.0 }
};



/*******************************************************************************
*
*  Assuming the following solution for x, y, z:
*
*  x = 10;
*  y =  6;
*  z =  5;
*
*  10x - 2y + 3z = 103
*  100 - 12 + 15 = 103
*
*   5x + 4y + 6z = 104
*   50 + 24 + 30 = 104
*
*  -2x - 1y - 3z = -41
*  -20 -  6 - 15 = -41
*
*******************************************************************************/

static double matrix2[ROWS][COLS] = {
    { 10.0, -2.0, +3.0, 103.0 },
    {  5.0, +4.0, +6.0, 104.0 },
    { -2.0, -1.0, -3.0, -41.0 }
};



/*******************************************************************************
*
*  Schematic circuit (Grid of resistors):
*
*              V1   R1       V2   R2       V3   R3       V4   R4      V5
*      o-------o----A A A----o----A A A----o----A A A----o----A A A----o
*      |       |     V V     |     V V     |     V V     |     V V     |
*      |      <             <             <             <             <
*      |        > R5          > R6          > R7          > R8          > R9
*      |      <             <             <             <             <
*      |        >             >             >             >             >
*      |       |V6   R10     |V7   R11     |V8   R12     |V9   R13     |V10
*      |       o----A A A----o----A A A----o----A A A----o----A A A----o
*      |       |     V V     |     V V     |     V V     |     V V     |
*      |      <             <             <             <             <
*      |        > R14         > R15         > R16         > R17         > R18
*      |      <             <             <             <             <
*      |        >             >             >             >             >
*      |       |V11  R19     |V12  R20     |V13  R21     |V14  R22     |V15
*      |       o----A A A----o----A A A----o----A A A----o----A A A----o
*      |       |     V V     |     V V     |     V V     |     V V     |
*      -      <             <             <             <             <
*    / A \      > R23         > R24         > R25         > R26         > R27
*    \ | /    <             <             <             <             <
*      -        >             >             >             >             >
*      |       |V16  R28     |V17  R29     |V18  R30     |V19  R31     |V20
*      |       o----A A A----o----A A A----o----A A A----o----A A A----o
*      |       |     V V     |     V V     |     V V     |     V V     |
*      |      <             <             <             <             <
*      |        > R32         > R33         > R34         > R35         > R36
*      |      <             <             <             <             <
*      |        >             >             >             >             >
*      |       |V21  R37     |V22  R38     |V23  R39     |V24  R40     |
*      |       o----A A A----o----A A A----o----A A A----o----A A A----o
*      |             V V           V V           V V           V V     |
*      |                                                               |
*      |                                                               |
*      o---------------------------------------------------------------o
*                                                                      |
*                                                              Ground ---
*                                                                      =
*
*  Admittance matrix (24x24):
*
*  | 1/R1+1/R5  -1/R1  ..          0         |       |  V1 |     | 0.001 |
*  |                                         |       |     |     |       |
*  |     :        ..   ..          :         |   x   |  :  |  =  |   :   |
*  |                                         |       |     |     |       |
*  |     0        0    ..  1/R35+1/R39+1/R40 |       | V24 |     | 0.000 |
*                                             24x24         24x1          24x1
*
*******************************************************************************/
// Net-list of previous circuit (Copy & paste the lines in an independent file)
// PROPOSED PROBLEMS:
// 1. Compute The voltages in every single node
// 2. How could you determine the path with maximum current flow between 1 & 25
// 3. How could you compute the equivalent resistance between nodes 1 & 25
// 4. Could it be possible to model the minimum path between 2 points in a MAZE?
/*******************************************************************************
R1	1	2	1000
R2	2	3	1000
R3	3	4	1000
R4	4	5	1000
R5	1	6	1000
R6	2	7	1000
R7	3	8	1000
R8	4	9	1000
R9	5	10	1000
R10	6	7	1000
R11	7	8	1000
R12	8	9	1000
R13	9	10	1000
R14	6	11	1000
R15	7	12	1000
R16	8	13	1000
R17	9	14	1000
R18	10	15	1000
R19	11	12	1000
R20	12	13	1000
R21	13	14	1000
R22	14	15	1000
R23	11	16	1000
R24	12	17	1000
R25	13	18	1000
R26	14	19	1000
R27	15	20	1000
R28	16	17	1000
R29	17	18	1000
R30	18	19	1000
R31	19	20	1000
R32	16	21	1000
R33	17	22	1000
R34	18	23	1000
R35	19	24	1000
R36	20	0	1000
R37	21	22	1000
R38	22	23	1000
R39	23	24	1000
R40	24	0	1000
Input	1	0	0.001
*******************************************************************************/



/*******************************************************************************
*
*  Schematic circuit (Ladder resistors):
*
*           R1          R3          R5                    R(2n-1)
*
*     V1          V2          V3          V4          V(n-1)      Vn
*     o---A A A---o---A A A---o---A A A---o  -  -  -  o---A A A---o
*     |    V V    |    V V    |    V V    |           |    V V    |
*     -          <           <           <           <           <
*   / A \          >           >           >           >           >
*   \ | /        <           <           <           <           <
*     -            >  R2       >  R4       >  R6       > R(2n-4)   >  R(2n-2)
*     |           |           |           |           |           |
*     o-----------o-----------o-----------o-----------o-----------o
*     |
*    --- Ground
*     =
*
*  Admittance matrix (nxn):
*
*  |  1/R1       -1/R1         0           0        .. |   | V1  |   | 0.001 |
*  |                                                   |   |     |   |       |
*  | -1/R1   1/R1+1/R2+1/R3  -1/R3         0        .. |   | V2  |   | 0.000 |
*  |                                                   |   |     |   |       |
*  |   0         -1/R3   1/R3+1/R4+1/R5  -1/R5      .. |   | V3  |   | 0.000 |
*  |                                                   | x |     | = |       |
*  |   0           0         -1/R5   1/R5+1/R6+1/R7 .. |   | V4  |   | 0.000 |
*  |                                                   |   |     |   |       |
*  |   0           0           0         -1/R6      .. |   |  :  |   | 0.000 |
*  |                                                   |   |     |   |       |
*  |   :           :           :           :        .. |   | V25 |   | 0.000 |
*
*
*******************************************************************************/
// PROPOSED CHALLENGE:
// Could it be possible to design a program able to generate a net-list?
/******************************************************************************/



/*******************************************************************************
*
*  Schematic circuit (Parallel resistors):
*
*                                          V1
*                         o--------o--------o--------o
*                         |        |        |        |
*                         -       <        <        <
*                       / A \       > R1     > R2     > R3
*                       \ | /     <        <        <
*                         -         >        >        >
*                         |        |        |        |
*                         o--------o--------o--------o
*                                           |
*                                          --- Ground
*                                           =
*
*  Admittance matrix (1x1):
*
*                |                      |   |    |   |       |
*                |  1/R1 + 1/R2 + 1/R3  | x | V1 | = | 0.001 |
*                |                      |   |    |   |       |
*
*******************************************************************************/
// Net-list of previous circuit (Copy & paste the lines in an independent file)
/*******************************************************************************
I_input 1 0 0.001
R1      1 0 1000
R2      1 0 1000
R3      1 0 1000
*******************************************************************************/

static double matrix_parallel[ROWS][COLS] = {
    { 1/R1 + 1/R2 + 1/R3,   0.001 }
};



/*******************************************************************************
*
*  Schematic circuit (Serial resistors):
*
*                              V1     R1     V2
*
*                              o----A A A----o
*                              |     V V     |
*                              -            <
*                            / A \            >  R2
*                            \ | /          <
*                              -              >
*                              |             |
*                              o----A A A----o
*                              |     V V
*                      Ground ---            V3
*                              =      R3
*
*  Admittance matrix (3x3):
*
*        |  1/R1       -1/R1          0       |   | V1 |   | 0.001 |
*        |                                    |   |    |   |       |
*        | -1/R1     1/R1 + 1/R2    -1/R2     | x | V2 | = | 0.000 |
*        |                                    |   |    |   |       |
*        |   0         -1/R2      1/R2 + 1/R3 |   | V3 |   | 0.000 |
*
*******************************************************************************/
// Net-list of previous circuit (Copy & paste the lines in an independent file)
/*******************************************************************************
I_input 1 0 0.001
R1      1 2 1000
R2      2 3 1000
R3      3 0 1000
*******************************************************************************/

static double matrix_serial[ROWS][COLS] = {
    {  1/R1,     -1/R1,          0.0,      0.001 },
    { -1/R1,   1/R1 + 1/R2,    -1/R2,      0.000 },
    {   0.0,     -1/R2,      1/R2 + 1/R3,  0.000 }
};



/*******************************************************************************
*
*  Schematic circuit (Serial and parallel resistors with a floating source):
*
*                           V2     R2          V3
*
*                           o----A A A----o---------o
*                           |     V V     |         |
*                           -            <         <
*                         / A \            >         >
*                         \ | /       R3 <         <   R4
*                           -              >         >
*                           |             |         |
*                           o----A A A----o----o----o
*                                 V V          |
*                           V1                --- Ground
*                                  R1          =
*
*  Admittance matrix (3x3):
*
*     | 1/R1            0              0          |   | V1 |   | -0.001 |
*     |                                           |   |    |   |        |
*     |  0             1/R2          -1/R2        | x | V2 | = | +0.001 |
*     |                                           |   |    |   |        |
*     |  0            -1/R2    1/R2 + 1/R3 + 1/R4 |   | V3 |   |  0.000 |
*
*******************************************************************************/
// Net-list of previous circuit (Copy & paste the lines in an independent file)
/*******************************************************************************
I_input 1 2 0.001
R1      1 0 1000
R2      2 3 1000
R3      3 0 1000
R4      3 0 1000
*******************************************************************************/

static double matrix_flotant_source[ROWS][COLS] = {
    {  1/R1,    0.0,          0.0,         -0.001 },
    {   0.0,    1/R2,        -1/R2,        +0.001 },
    {   0.0,   -1/R3,  1/R2 + 1/R3 + 1/R4,  0.000 }
};

