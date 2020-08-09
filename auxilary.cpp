#include "auxilary.h"

void solverGauss(double a[SIZE_SYSTEM][SIZE_SYSTEM + 1], double var[SIZE_SYSTEM])
{
    for (int i = 0; i < SIZE_SYSTEM; ++i)
    {
        double max_element = abs(a[i][i]);
        int max_row = i;
        for (int k = i + 1; k < SIZE_SYSTEM; ++k)
        {
            if (abs(a[k][i]) > max_element)
            {
                max_element = abs(a[k][i]);
                max_row = k;
            }
        }

        for (int k = i; k < SIZE_SYSTEM + 1; ++k)
        {
            double temp = a[max_row][k];
            a[max_row][k] = a[i][k];
            a[i][k] = temp;
        }

        for (int k = i + 1; k < SIZE_SYSTEM; ++k)
        {
            double coef = -a[k][i]/a[i][i];
            for (int j = i; j < SIZE_SYSTEM + 1; ++j)
            {
                if (i==j)
                {
                    a[k][j] = 0;
                }
                else
                {
                    a[k][j] += coef * a[i][j];
                }
            }
        }
    }

    for (int i = SIZE_SYSTEM - 1; i >= 0; --i)
    {
        var[i] = a[i][SIZE_SYSTEM]/a[i][i];
        for (int k = i - 1; k >= 0; --k)
        {
            a[k][SIZE_SYSTEM] -= a[k][i] * var[i];
        }
    }

}
