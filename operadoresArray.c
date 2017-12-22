/******************************************************************************
 * Operaciones básicas con arrays.
 * Autores: Labayén Franco - Wals Lucas.
 *****************************************************************************/

/*
 * Verifica si el entero "e" esta contenido entre las posiciones
 * "lim_inf" y "lim_sup" de un array "a" (considerando los extremos)
 */
int pertenece(int e, int lim_inf, int lim_sup, int a[]) {
    int rta = 0;
    for(; lim_inf <= lim_sup && a[lim_inf] != e; lim_inf++) {}
    if(lim_inf <= lim_sup) {
        rta = 1;
    }
    return rta;
}

/*
 * Copia un array de enteros "b" en otro "a"
 */
void arrayCP(int dim, int a[],int b[]) {
    dim--;
    for(; dim >= 0; dim--) {
        a[dim] = b[dim];
    }
}

/*
 * Copia una matriz de enteros "b" en otra "a"
 */
void matrizCP(int dim1,int dim2, int a[][dim2],int b[][dim2]) {
    int i,j;
    for(i = 0; i < dim1; i++) {
        for(j = 0; j < dim2; j++) {
            a[i][j] = b[i][j];
        }
    }
}

/*
 * Llena un array "a" de números enteros aleatorios, no repetidos y 
 * comprendidos entre 0 y "dim - 1"
 */
void randArray(int dim, int a[]){
    int i, r = rand() % dim;    
    for(i = 0; i < dim; i++) {
        while(pertenece(r, 0, i - 1, a)) {
            r = rand() % dim;
        }
        a[i] = r;
    }
}
