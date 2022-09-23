#include "headers/uteis.h"

void quick_sort_int (TipoBloco *a, int n) {
    int i, j,temp;
    double p;
    aluno t ;
    if (n < 2)
        return;
    p = a->v[n / 2].nota;
    for (i = 0, j = n - 1;; i++, j--) {
        while (a->v[i].nota < p)
            i++;
        while (p < a->v[j].nota)
            j--;
        if (i >= j)
            break;
        t = a->v[i];
        temp = a->pertence[i];
        a->v[i] = a->v[j];
        a->v[j] = t;
        a->pertence[j] = temp;
    }
    quick_sort_int(a, i);
    quick_sort_int(a + i, n - i);
}
