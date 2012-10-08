/* matops.c :
 *  Matrix operations - Multiplication, addition, subtraction, transpose
 *                      and minimum element along the diagonal
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int dim = 3; /* Dimensions dim x dim of matrix */

void accept_user_matrix (double ** mat)
{
    int i, j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            scanf ("%lf", &mat[i][j]);
        }
    }
}

/* Swap two elements of the matrix,
 * used by the transpose function */
void swap (double * a, double * b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

/* Set all elements to zero */
void clear_matrix (double ** matrix)
{
    int i, j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            matrix[i][j] = 0.0;
        }
    }
}

void display (double ** matrix)
{
    int i,j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            printf ("%.2lf\t",  matrix[i][j]);
            if(j == dim - 1)
                printf("\n");
        }
    }
}

/* No parameters are needed since we only construct dim x dim matrices */
double ** allocate_array (void)
{
    int i;
    /* create pointers for the rows starting points */
    double ** rows = malloc (dim * sizeof(double *));

    /* allocate space for each row */
    for (i = 0; i < dim; i++) {
        rows[i] = malloc (dim * sizeof(double));
    }
    return rows;
}

/*  Deallocates the memory for a 2D matrix */
void free_array (double ** mat)
{
    int i;
    for (i = 0; i < dim; i++) {
        free (mat[i]);  /* Free the pointers to the rows */
    }
    free(mat); /* Free the memory for the rows */
}

/* Multiplies two square matrices.
 * Allocates memory for the result matrix.
 * The caller is responsible for freeing the memory.
 */
double ** multiply (double ** m1, double ** m2)
{
    int i, j, k;
    double ** result = allocate_array();
    clear_matrix(result);
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            for (k = 0; k < dim; k++) {
                result [i][j] += (m1[i][k] * m2[k][j]);
            }
        }
    }
    return result;
}

double ** transpose (double ** mat)
{
    int i, j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < i; j++) {
            swap (&mat[i][j], &mat[j][i]);
        }
    }
    return mat;
}

/* Returns the sum of the elements along the diagonal */
double sum_diag (double ** matrix)
{
    double sum = 0;
    int i;

    for (i = 0 ; i < dim; i++) {
        sum += matrix[i][i];
    }
    return sum;
}

double ** add (double ** m1, double ** m2)
{
    int i,j;
    double ** result = allocate_array(); /* Caller must free this */
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            result [i][j] = (m1[i][j] + m2[i][j]);
        }
    }
    return result;
}

double ** sub (double ** m1, double ** m2)
{
    int i, j;
    double ** result = allocate_array(); /* Caller must free this */
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            result [i][j] = (m1[i][j] - m2[i][j]);
        }
    }
    return result;
}

int main (void)
{
    double ** m1 = NULL, **m2 = NULL, **result = NULL;
    printf ("Enter square matrix dimension : ");
    scanf ("%d", &dim);

    m1=allocate_array();
    m2=allocate_array();

    printf ("\nEnter first array : ");
    accept_user_matrix (m1);

    printf ("\nEnter second array : ");
    accept_user_matrix (m2);

    result = multiply (m1,m2);
    printf ("The product of the two matrices is : \n");
    display (result);

    printf ("Transpose of the first matrix is : \n");
    display (transpose (m1));

    printf ("Transpose of the second matrix is : \n");
    display (transpose (m2));

    printf ("The sum of the diagonal elements of the first matrix  is %.2lf\n", sum_diag (m1));
    printf ("The sum of the diagonal elements of the second matrix is %.2lf\n", sum_diag (m2));

    double ** add_result = add (m1,m2);
    printf ("The result of addition is : \n");
    display (add_result);

    double ** sub_result = sub (m1,m2);
    printf ("The result of subtraction is : \n");
    display (sub_result);

    free_array (m1);
    free_array (m2);
    free_array (result);
    free_array (add_result);
    free_array (sub_result);

    return 0;
}
