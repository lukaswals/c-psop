/******************************************************************************
 * Operadores propios del algoritmo PSOP.
 * Autores: Labayén Franco - Wals Lucas.
 *****************************************************************************/

/*
 * Resta dos vectores posición y devuelve un vector velocidad como resultado
 */
void restaPSOP(int dim_x, int x1[], int x2[], int v[][2]) {
    dim_x--;
    for(; dim_x >= 0; dim_x--) {
        v[dim_x][0] = x2[dim_x];
        v[dim_x][1] = x1[dim_x];
    }
}

/*
 * Suma dos vectores velocidad y devuelve otra velocidad como resultado
 */
void sumaPSOP(int dim_v1, int dim_v2, int v1[][2], int v2[][2], int vr[][2]) {
    int j,k;
    //Hacemos una copia de la matriz v2 para no modificar la misma
    int copia_v2[dim_v2][2];
    matrizCP(dim_v2, 2, copia_v2, v2);
    //Buscamos y realizamos solapamientos
    for(k = 0; k < dim_v1; k++) {
        for(j = 0; j < dim_v2 && v1[k][1] != copia_v2[j][0]; j++) {}
        if(j == dim_v2) {
             vr[k][0] = v1[k][0];
            vr[k][1] = v1[k][1];
        } else {
            vr[k][0] = v1[k][0];
            vr[k][1] = copia_v2[j][1];
            //Le damos un valor que no este dentro del dominio
            //para que no se use dos veces el mismo solapamiento
            copia_v2[j][0] = -1;
        }
    }
}

/*
 * Multiplica un numero "float" (escalar) con un vector velocidad y devuelve 
 * otra velocidad como resultado (no contempla escalares negativos)
 */
void productoPSOP(int dim_v, float e, int v[][2], int vr[][2]) {
    if(e <= 1) {
        float r;
        dim_v--;
        for(; dim_v >= 0; dim_v--) {
            r = drand48();
            if(r < e) {
                vr[dim_v][0] = v[dim_v][0];
                vr[dim_v][1] = v[dim_v][0];
            } else {
                vr[dim_v][0] = v[dim_v][0];
                vr[dim_v][1] = v[dim_v][1];
            }
        }
    } else {
        int v_acum[dim_v][2], sub_vr[dim_v][2];
        matrizCP(dim_v, 2, v_acum, v);
        for(; e >= 2; e--) {
            sumaPSOP(dim_v, dim_v, v_acum, v, sub_vr);
            matrizCP(dim_v, 2, v_acum, sub_vr);
        }
        e--;
        productoPSOP(dim_v, e, v, sub_vr);
        sumaPSOP(dim_v, dim_v, v_acum, sub_vr, vr);
    }
}

/*
 * Mueve un vector posición acorde a un vector velocidad y devuelve el mismo
 * vector con la nueva posición obtenida
 */
void movimientoPSOP(int dim_x, int dim_v, int x[], int v[][2]) {
    int i,j,k,aux;
    for(i = 0; i < dim_v; i++) {
        for(k = 0; k < dim_x && x[k] != v[i][0]; k++) {}
        for(j = 0; j < dim_x && x[j] != v[i][1]; j++) {}
        aux = x[k];
        x[k] = x[j];
        x[j] = aux;
    }
}

/*
 * Actualiza un vector velocidad acorde a los parámetros del algoritmo PSOP
 */
void actualizacionPSOP(int dim_x,int dim_v, int v[][2],float c1, float c2, int x[], int p[], int g[]) {
    int pos_int[dim_x];
    int r1[dim_x][2], r2[dim_x][2], r3[dim_x][2], r4[dim_x][2], r5[dim_x][2];
    //Calculamos una posición intermedia --> pos_int = p + 0.5 * (g - p)
    restaPSOP(dim_x,g,p,r1);    
    productoPSOP(dim_x,0.5,r1,r2);
    arrayCP(dim_x, pos_int, p);
    movimientoPSOP(dim_x, dim_x, pos_int, r2);
    //Actualizamos la velocidad --> v = c1 * v + c2 * (pos_int - x)
    restaPSOP(dim_x, pos_int, x,r3);
    productoPSOP(dim_x,c2,r3,r4);
    productoPSOP(dim_v,c1,v,r5);
    sumaPSOP(dim_v, dim_x, r5, r4, v);
}
