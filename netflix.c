#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 150

typedef struct pelicula{
	char nombre[31];
	int duracion;
	int genero;
	float calificacion;
	int vista;
}datos;

void menu(void);
void registro(int i,datos *alumnos);
int* busqueda(int tam, datos* pelis, int* numResultados);
void guardarLista(datos *alumnos, int tam);
int cargarLista(datos **pelis);
void eliminarPelicula(int *tam, datos **pelis, int *i);
void ordenarPorGenero(datos* pelis, int tam);
void imprimirEstrellas(float calificacion);
void ordenarPorCalificacion(datos* pelis, int tam);
void imprimirGenero(int genero);
void guardarEnHistorial(datos pelicula);
void mostrarHistorial();

int main() {
    
    int tam = 0, i = 0, numResultados;
    int* resultados; 
    datos* pelis = (datos*)malloc(tam * sizeof(datos));

    tam = cargarLista(&pelis);

    char opc[10];
    int op;
    do
    {
        system("cls || clear");
        menu();
        fgets(opc, sizeof(opc), stdin);
        op = atoi(opc);
        system("cls || clear");
        
        switch (op) 
        {
            case 1:
                if (tam == 0) 
				{
                    printf("No hay peliculas registradas en el sistema\n");
                    break;
                } 
                printf("NOMBRE\t\t\t\tDURACION\tGENERO\tCALIFICACION\tVISTAS\n\n");
                for (int i = 0; i < tam; i++) 
                {
                    printf("%-30.30s\t%d\t\t%d\t", pelis[i].nombre, pelis[i].duracion, pelis[i].genero);
                    imprimirEstrellas(pelis[i].calificacion);
                    printf("\t\t%d\n", pelis[i].vista);
                }
            break;
            case 2:
                if (tam == 0) 
                {
                    printf("No hay peliculas registradas en el sistema.\n");
                    break;
                }
                resultados = busqueda(tam, pelis, &numResultados);
                if (numResultados == 0) 
                {
                    printf("\nNo se encontro ninguna pelicula con ese nombre.\n");
                    break;
                }

                printf("\nPeliculas encontradas:\n");
                printf("INDICE\tNOMBRE\t\t\t\tDURACION\tGENERO\tCALIFICACION\tVISTAS\n");
                for (int i = 0; i < numResultados; i++) 
                {
                    int idx = resultados[i];
                    printf("%d\t%-30.30s\t%d\t\t%d\t",i+1, pelis[idx].nombre, pelis[idx].duracion, pelis[idx].genero);
                    imprimirEstrellas(pelis[idx].calificacion);
                    printf("\t\t%d\n", pelis[idx].vista);    
                }

                printf("\nSeleccione el indice de la pelicula que desea ver (1-%d): ", numResultados);
                int seleccion;
                do 
                {
                    scanf("%d", &seleccion);
                    getchar();
                    if (seleccion < 1 || seleccion > numResultados) 
                    {
                        printf("\nSeleccion invalida. Por favor, elija un numero entre 1 y %d.\n", numResultados);
                    }
                }while (seleccion < 1 || seleccion > numResultados);

                int idx = resultados[seleccion - 1];
                printf("\nDetalles de la pelicula seleccionada:\n");
                printf("NOMBRE\t\t\t\tDURACION\tGENERO\tCALIFICACION\tVISTAS\n");
                printf("%-30.30s\t%d\t\t%d\t", pelis[idx].nombre, pelis[idx].duracion, pelis[idx].genero);
                imprimirEstrellas(pelis[idx].calificacion);
                printf("\t\t%d\n", pelis[idx].vista);
                pelis[idx].vista++;
                guardarEnHistorial(pelis[idx]);
                float calif;
                do
                {
                    printf("\nEn una escala del 0 al 5 (siendo 5 el maximo)... Que calificacion le pondria? ");
                    scanf("%f", &calif);
                    getchar();
                    if(calif<0 || calif>5)
                    printf("\nPor favor ingrese una calificacion valida\n");
                }while(calif<0 || calif>5);
                
                pelis[idx].calificacion = ((pelis[idx].calificacion) * (pelis[idx].vista - 1) + calif) / pelis[idx].vista;
                guardarLista(pelis, tam);
                free(resultados);
            break;
            case 3:
                tam++;
                pelis = (datos*)realloc(pelis, tam * sizeof(datos));
                registro(tam-1, pelis);
                guardarLista(pelis, tam);
            break;
            case 4:
                if (tam == 0) 
                {
                    printf("No hay peliculas registradas en el sistema.\n");
                    break;
                }
                resultados = busqueda(tam, pelis, &numResultados);
                if (numResultados > 0) 
                {
                    printf("\nPeliculas encontradas:\n\n");
                    printf("INDICE\tNOMBRE\t\t\t\tDURACION\tGENERO\tCALIFICACION\tVISTA\n");
                    for (int i = 0; i < numResultados; i++) 
                    {
                        int idx = resultados[i];
                        printf("%d\t%-30.30s\t%d\t\t%d\t",i+1, pelis[idx].nombre, pelis[idx].duracion, pelis[idx].genero);
                        imprimirEstrellas(pelis[idx].calificacion);
                        printf("\t\t%d\n", pelis[idx].vista);}
                }else
                {
                printf("\nNo se encontro ninguna pelicula con ese nombre\n");
                }
                free(resultados);
            break;
            case 5:
                if (tam == 0) 
                {
                    printf("No hay peliculas registradas en el sistema.\n");
                    break;
                }
                    eliminarPelicula(&tam, &pelis, &i);
            break;    
            case 6:
                if (tam == 0) 
                {
                    printf("No hay peliculas registradas en el sistema.\n");
                    break;
                }
                ordenarPorGenero(pelis, tam);
                int generoAnterior = 0;
    
                printf("Peliculas ordenadas por genero:\n");
    
                for (int i = 0; i < tam; i++) 
                {
                    if (pelis[i].genero != generoAnterior) 
                    {
                        generoAnterior = pelis[i].genero;
                        imprimirGenero(generoAnterior);
                    }
                    printf("%-30.30s\t%d\t\t", pelis[i].nombre, pelis[i].duracion);
                    imprimirEstrellas(pelis[i].calificacion);
                    printf("\t\t%d\n", pelis[i].vista);
                }
                break;
            case 7:
                if (tam == 0) 
                {
                    printf("No hay peliculas registradas en el sistema.\n");
                    break;
                }

                ordenarPorCalificacion(pelis, tam);

                printf("TOP 10 Peliculas mejor valoradas:\n");
                printf("PUESTO\tNOMBRE\t\t\t\tDURACION\tGENERO\tCALIFICACION\tVISTAS\n");

                for (int i = 0; i < 10; i++) 
                {
                    printf("#%d\t%-30.30s\t%d\t\t%d\t", i+1, pelis[i].nombre, pelis[i].duracion, pelis[i].genero);
                    imprimirEstrellas(pelis[i].calificacion);
                    printf("\t\t%d\n", pelis[i].vista);
                }
            break;
            case 8:
            mostrarHistorial();
            break;
            case 9:
            break;
            case 10:
                printf("Gracias por utilizar nuestro programa. Adios!\n");
            break;
            default:
                printf("Opcion no valida. Por favor, intente nuevamente.\n");
            break;
        }
        printf("\nPresione ENTER para continuar...");
        getchar();
    } while (op != 10);

    free(pelis);
    return 0;
}

void menu(void)
{
	printf("* * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*            --   UVtflix   --            *\n");
	printf("*                                         *\n");
	printf("*     Seleccione la opcion que desee:     *\n");
	printf("*    Mostrar lista de peliculas   -> 1    *\n");
	printf("*    Ver pelicula                 -> 2    *\n");
	printf("*    Registrar pelicula nueva     -> 3    *\n");
	printf("*    Buscar pelicula              -> 4    *\n");
	printf("*    Eliminar pelicula            -> 5    *\n");
	printf("*    Mostrar peliculas por genero -> 6    *\n");
    printf("*    Mostrar top 10               -> 7    *\n");
    printf("*    Mostrar historial del usuario-> 8    *\n");
    printf("*    Quitar primera pelicula vista-> 9    *\n");
    printf("*    Salir                        -> 10   *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n\n");
	printf("Opcion: ");
}

void registro(int i, datos *pelis) 
{
    int j;
    
    printf("Ingrese los datos de la pelicula segun se indique:\n\n");

    printf("Nombre: ");
    fgets(pelis[i].nombre, sizeof(pelis[i].nombre), stdin);
    pelis[i].nombre[strcspn(pelis[i].nombre, "\n")] = '\0';

    if (strlen(pelis[i].nombre) == sizeof(pelis[i].nombre) - 1 && pelis[i].nombre[sizeof(pelis[i].nombre) - 2] != '\0') 
	{
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }

    printf("\nDuracion (en minutos): ");
    do {
        scanf("%d", &pelis[i].duracion);
        getchar();
        if (pelis[i].duracion <= 0)
            printf("Por favor, ingrese una duracion valida (mayor a 0): ");
    } while (pelis[i].duracion <= 0);

    printf("\nIngrese el genero de la pelicula segun corresponda:\n\n[Accion -> 1]\t[Aventura  -> 2]\t[Comedia  -> 3]\t[Drama    -> 4]\t[Ciencia Ficcion -> 5]\n[Terror -> 6]\t[Romantica -> 7]\t[Misterio -> 8]\t[Fantasia -> 9]\t[Suspenso       -> 10]\n\nGenero: ");
    do {
        scanf("%d", &pelis[i].genero);
		getchar();
        if (pelis[i].genero <= 0)
            printf("Por favor, ingrese un genero valido: ");
    } while (pelis[i].genero <= 0 || pelis[i].genero > 10);
    
	pelis[i].calificacion = 0;
	
	pelis[i].vista = 0;
	
	printf("\nPelicula registrada correctamente.\n");
}

int* busqueda(int tam, datos* pelis, int* numResultados) 
{
    char busq[30];
    printf("Ingrese parte del nombre de la pelicula: ");
    fgets(busq, sizeof(busq), stdin);
    busq[strcspn(busq, "\n")] = '\0';

    int* indices = NULL;
    *numResultados = 0;

    for (int i = 0; i < tam; i++) {
        if (strstr(pelis[i].nombre, busq) != NULL) {
            (*numResultados)++;
            indices = realloc(indices, (*numResultados) * sizeof(int));
            if (indices == NULL) {
                printf("Error al asignar memoria.\n");
                exit(1);
            }
            indices[(*numResultados) - 1] = i;
        }
    }

    return indices;
}

void guardarLista(datos *pelis, int tam) 
{
    FILE *archivo;
    archivo = fopen("lista_pelis.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los datos.\n");
        return;
    }
	
    for (int j = 0; j < tam; j++) 
	{
        fprintf(archivo, "%-30.30s\t%-8d\t%-6d\t%-12.2f\t%-4d\n", pelis[j].nombre, pelis[j].duracion, pelis[j].genero, pelis[j].calificacion, pelis[j].vista);
    }

    fclose(archivo);
}

int cargarLista(datos **pelis) 
{
    FILE *archivo;
    int tam = 0;
    datos peliculaTemp;
    
    archivo = fopen("lista_pelis.txt", "r");
    
	if (archivo == NULL) 
	{
        printf("No se encontro un archivo de registros previos\n");
        return 0;
    }

    while (fscanf(archivo, "%30[^\t]\t%d\t%d\t%f\t%d\n", peliculaTemp.nombre, &peliculaTemp.duracion, &peliculaTemp.genero, &peliculaTemp.calificacion, &peliculaTemp.vista) == 5) 
	{
        tam++;
        *pelis = realloc(*pelis, tam * sizeof(datos));
        if (*pelis == NULL) 
		{
            printf("Error al asignar memoria.\n");
            fclose(archivo);
            return tam;
        }
        (*pelis)[tam - 1] = peliculaTemp;
    }

    fclose(archivo);
    printf("\nLista de pelis cargada correctamente desde 'lista_pelis.txt'.\n");
    return tam;
}


void eliminarPelicula(int *tam, datos **pelis, int *i) 
{
    int numResultados;
    int* resultados = busqueda(*tam, *pelis, &numResultados);

    if (numResultados == 0) 
    {
        printf("No se encontro ninguna pelicula con ese nombre.\n");
        return;
    }

    printf("\nPeliculas encontradas:\n");
    for (int j = 0; j < numResultados; j++) 
    {
        int idx = resultados[j];
        printf("%d. %-30.30s\n", j + 1, (*pelis)[idx].nombre);
    }

    printf("\nSeleccione el indice de la pelicula a eliminar (1-%d): ", numResultados);
    int seleccion;   
    do
    {
        scanf("%d", &seleccion);
        getchar();
        if (seleccion < 1 || seleccion > numResultados) 
        {
        printf("Seleccion invalida. Por favor, elija un numero entre 1 y %d.\n", numResultados);
        }
    }while (seleccion < 1 || seleccion > numResultados);
    
    int idxEliminar = resultados[seleccion - 1];

    printf("\nLa pelicula %s ha sido eliminada de los registros.\n", (*pelis)[idxEliminar].nombre);

    (*pelis)[idxEliminar] = (*pelis)[*tam - 1];
    (*tam)--;

    *pelis = realloc(*pelis, (*tam) * sizeof(datos));
    if (*pelis == NULL && *tam > 0) 
    {
        printf("Error al reasignar memoria.\n");
        exit(1);
    }

    guardarLista(*pelis, *tam);

    free(resultados);
}

void ordenarPorGenero(datos* pelis, int tam) 
{
    int maxGenero = 0;

    for (int i = 0; i < tam; i++) {
        if (pelis[i].genero > maxGenero) {
            maxGenero = pelis[i].genero;
        }
    }

    int* count = (int*)calloc(maxGenero + 1, sizeof(int));
    if (!count) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    for (int i = 0; i < tam; i++) {
        count[pelis[i].genero]++;
    }

    for (int i = 1; i <= maxGenero; i++) {
        count[i] += count[i - 1];
    }

    datos* output = (datos*)malloc(tam * sizeof(datos));
    if (!output) {
        printf("Error al asignar memoria.\n");
        free(count);
        exit(1);
    }

    for (int i = tam - 1; i >= 0; i--) {
        int genero = pelis[i].genero;
        output[count[genero] - 1] = pelis[i];
        count[genero]--;
    }

    for (int i = 0; i < tam; i++) {
        pelis[i] = output[i];
    }

    free(count);
    free(output);
}

void imprimirEstrellas(float calificacion) 
{
    int estrellas = (int)(calificacion + 0.5);
    for (int i = 0; i < 5; i++) 
    {
        if (i < estrellas)
            printf("*");
    }
}

void ordenarPorCalificacion(datos* pelis, int tam) 
{
    datos temp[N];
    
    void merge(datos* pelis, int inicio, int medio, int fin) {
        int i = inicio, j = medio + 1, k = inicio;

        while (i <= medio && j <= fin) {
            if (pelis[i].calificacion >= pelis[j].calificacion) {
                temp[k++] = pelis[i++];
            } else {
                temp[k++] = pelis[j++];
            }
        }
        while (i <= medio) {
            temp[k++] = pelis[i++];
        }
        while (j <= fin) {
            temp[k++] = pelis[j++];
        }
        for (i = inicio; i <= fin; i++) {
            pelis[i] = temp[i];
        }
    }

    void mergeSort(datos* pelis, int inicio, int fin) {
        if (inicio < fin) {
            int medio = (inicio + fin) / 2;
            mergeSort(pelis, inicio, medio);
            mergeSort(pelis, medio + 1, fin);
            merge(pelis, inicio, medio, fin);
        }
    }

    mergeSort(pelis, 0, tam - 1);
}

void imprimirGenero(int genero) 
{
    const char* generos[] = {"Accion", "Aventura", "Comedia", "Drama", "Ciencia Ficcion", "Terror", "Romantica", "Misterio", "Fantasia", "Suspenso"};

    if (genero >= 1 && genero <= 10) 
    {
        printf("\n\t\t[**%s**]\n", generos[genero - 1]);
        printf("NOMBRE\t\t\t\tDURACION\tCALIFICACION\tVISTAS\n");
    }
}

void guardarEnHistorial(datos pelicula) 
{
    FILE *archivo = fopen("historial_pelis.txt", "a");
    if (archivo == NULL) 
    {
        printf("Error al abrir el archivo de historial.\n");
        return;
    }

    fprintf(archivo, "%-30.30s\t%d\t%d\t%.2f\t%d\n", pelicula.nombre, pelicula.duracion, pelicula.genero, pelicula.calificacion, pelicula.vista);
    fclose(archivo);
}

void mostrarHistorial() 
{
    FILE *archivo = fopen("historial_pelis.txt", "r");
    if (archivo == NULL) 
    {
        printf("No hay peliculas vistas en el historial.\n");
        return;
    }

    datos peliculaTemp;
    int esPrimera = 1;

    printf("PELICULAS VISTAS HASTA EL MOMENTO:\n\n");
    

    while (fscanf(archivo, "%30[^\t]\t%d\t%d\t%f\t%d\n", peliculaTemp.nombre, &peliculaTemp.duracion, &peliculaTemp.genero, &peliculaTemp.calificacion, &peliculaTemp.vista) == 5) 
    {
        if (esPrimera) 
        {
            printf("-> PRIMERA PELICULA VISTA: %s\n\n ", peliculaTemp.nombre);
            printf("PELICULAS VISTAS HASTA EL MOMENTO:\n\n");
            printf("NOMBRE\t\t\t\tDURACION\tGENERO\tCALIFICACION\tVISTAS\n");
            esPrimera = 0;
        }
        printf("%-30.30s\t%d\t\t%d\t", peliculaTemp.nombre, peliculaTemp.duracion, peliculaTemp.genero);
        imprimirEstrellas(peliculaTemp.calificacion);
        printf("\t\t%d\n", peliculaTemp.vista);
    }

    fclose(archivo);
}