/******************************************************************************
 * Operaciones para cargar las instancias ATSP.
 * Autores: Labayén Franco - Wals Lucas.
 *****************************************************************************/

/*
 * Calculamos el tamaño de la matriz de la instancia "nombre"
 */
int calc_dimension(char *nombre) {
    FILE *ins;
    char dim[3], ruta[50];
    int dimension;
    sprintf(ruta, "./Instancias/");
    strcat(ruta, nombre);
    ins = fopen (ruta,"r");
    
    //Este control es suficiente hacerlo aqui, ya que calc_dimension
    //se llama antes que cargar_matriz
    if (ins != NULL){
        //Obtenemos la dimension de la matriz
        fseek(ins, 70, SEEK_SET);
        fgets(dim, 3, ins);
        fclose(ins);

        dimension = (int) strtol(dim, NULL, 10);
        return dimension;
    }
    else{
        printf("No se encontro la instancia: %s. Verifique el nombre.\n",nombre);
        exit(EXIT_SUCCESS);
    }
}

/*
 * Levantamos los valores de la instancia "nombre", y los cargamos en matriz
 */
void cargar_matriz(char *nombre, int dim, int matriz[dim][dim]) {
    FILE *ins;
    char costo[10], car, ruta[50];
    int num, i=0, j=0, k=0;

    sprintf(ruta, "./Instancias/");
    strcat(ruta, nombre);
        
    ins = fopen (ruta,"r");
    fseek(ins, 153, SEEK_SET);
    while (!feof(ins)){
        car = fgetc(ins);
        num = car - '0';
        if ( (num >= 0) & (num < 10) ) { 
            //Voy armando el numero en el arreglo costo
            costo[k]=car;
            k++; 
        }
        else {
            if (k>0) {
                matriz[i][j] = (int) strtol(costo, NULL, 10);
                j++;
                //Vaciamos el arreglo
                memset(&costo[0], 0, sizeof(costo));
                k=0;
            }
        }
        if (j==dim) {
            j=0;
            i++;
        }
    }
    fclose(ins);
}

/*
 * Funcion para imprimir la "matriz" en forma de matriz
 */
void mostrar_matriz (int dim, int mat[dim][dim]) {
    int f, c;
    for (f=0; f<dim; f++) {         //filas
        for ( c=0; c<dim; c++ )     //columnas
            printf("%d\t",mat[f][c]);
        printf("\n");
    }
}
