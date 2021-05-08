#include <stdio.h>
#include "matrix.h"

int main()
{
    matrix_t mtx = {
        {4.0, -3.0, 1.0, -8.0},
        {-2.0, 1.0, -3.0, -4.0},
        {1.0, -1.0, 2.0, 2.0}
    };

    Show_Mtx_Screen(mtx, 3, 4, 0);
    printf("\n");

    Mtx_Gauss_Elimination(mtx, 3, 5);
    Mtx_Back_Substitution(mtx, 3, 5);

    Show_Mtx_Screen(mtx, 3, 4, 0);
    printf("\n");
}