#include <stdio.h>
#include "matrix.h"
#include "read.h"

static void matrix();

int main()
{
    
}

static void matrix()
{
    matrix_t mtx = {
        {4.0, -3.0, 1.0, -8.0},
        {-2.0, 1.0, -3.0, -4.0},
        {1.0, -1.0, 2.0, 2.0}};

    Show_Mtx_Screen(mtx, 3, 4, 4);
    printf("\n");

    Mtx_Gauss_Elimination(mtx, 3, 4);
    Show_Mtx_Screen(mtx, 3, 4, 4);
    printf("\n");

    Mtx_Back_Substitution(mtx, 3, 4);
    Show_Mtx_Screen(mtx, 3, 4, 4);
    printf("\n");

    Write_Results(mtx, 3, 4);
}