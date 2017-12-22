/******************************************************************************
 * Funciones para almacenar los resultados obtenidos por el algoritmo PSO.
 * Autores: Labayén Franco - Wals Lucas.
 *****************************************************************************/

/*
 * Almacena los resultados en un archivo formato CSV
 */
void registrar(int cant_part, int iter, int lim_iter, float c1, float c2, 
    int cant_ciud, int costo, float tiempo_t, float tiempo_m){

    FILE *result;
    char nombre[50], linea[100]; 
    
    //Encontramos el archivo en el cual guardar los resultados.
    //Notar que el directorio "Resultados" debe estar creado previamente
    sprintf(nombre, "./Resultados/resultado%d.csv", cant_ciud);
    // "a": Abre el archivo para escritura al final. Si no existe se crea.
    result = fopen(nombre,"a");

    sprintf(linea, "%d;%.2f;%.2f;%d;%.2f;%d;%.2f;%d\n", cant_part, c1, c2, iter, 
        tiempo_m, lim_iter, tiempo_t, costo);
    fputs(linea,result);

    fclose(result);
    printf("Datos almacenados correctamente\n");
}
