#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    int tam = 0, op, i = 0;
    char opc[10];
    datos* pelis = (datos*)malloc(tam * sizeof(datos));

    tam = cargarLista(&pelis);
    i = tam;

    do {
        system("cls || clear");
        menu();
        fgets(opc, sizeof(opc), stdin);
        op = atoi(opc);
        system("cls || clear");
        switch (op) {
            case 1:
                if (i > 0) 
				{
                    printf("NOMBRE\t\t\t\tDURACION\tGENERO\tCALIFICACION\tVISTAS\n\n");
                    for (int j = 0; j < i; j++) {
                        printf("%-30.30s\t%d\t\t%d\t%.2f\t\t%d\n", pelis[j].nombre, pelis[j].duracion, pelis[j].genero, pelis[j].calificacion, pelis[j].vista);
                    }
                } else {
                    printf("No hay películas registradas en el sistema.\n");
                }
                break;
            case 2:
               if (i > 0) {
                int numResultados;
                int* resultados = busqueda(i, pelis, &numResultados);
                if (numResultados > 0) {
                printf("\nPelículas encontradas:\n");
                printf("Índice\tNOMBRE\t\t\t\tDURACION\tGENERO\tCALIFICACION\tVISTAS\n");
                for (int j = 0; j < numResultados; j++) {
                int idx = resultados[j];
                printf("%d\t%-30.30s\t%d\t\t%d\t%.2f\t\t%d\n", j + 1,
                    pelis[idx].nombre, pelis[idx].duracion, pelis[idx].genero,
                    pelis[idx].calificacion, pelis[idx].vista);
            }

            printf("\nSeleccione el índice de la película que desea ver (1-%d): ", numResultados);
            int seleccion;
            scanf("%d", &seleccion);
            getchar(); // Limpiar el buffer

            if (seleccion > 0 && seleccion <= numResultados) {
                int idx = resultados[seleccion - 1];
                printf("\nDetalles de la película seleccionada:\n");
                printf("NOMBRE\t\t\t\tDURACION\tGENERO\tCALIFICACION\tVISTAS\n");
                printf("%-30.30s\t%d\t\t%d\t%.2f\t\t%d\n", pelis[idx].nombre,
                    pelis[idx].duracion, pelis[idx].genero, pelis[idx].calificacion,
                    pelis[idx].vista);

                pelis[idx].vista++;
                printf("\nEn una escala del 1 al 5, ¿Qué calificación le pondría? ");
                float calif;
                scanf("%f", &calif);
                getchar(); // Limpiar el buffer

                pelis[idx].calificacion =
                    ((pelis[idx].calificacion) * (pelis[idx].vista - 1) + calif) / pelis[idx].vista;

                guardarLista(pelis, tam);
            } else {
                printf("Selección inválida.\n");
            }
        } else {
            printf("No se encontró ninguna película con ese nombre.\n");
        }
        free(resultados);
    } else {
        printf("No hay películas registradas en el sistema.\n");
    }
    break;
            case 3:
                tam++;
                pelis = (datos*)realloc(pelis, tam * sizeof(datos));
                registro(i, pelis);
                i++;
                guardarLista(pelis, tam);
                break;
            case 4:
                if (i > 0) {
                int numResultados;
                int* resultados = busqueda(i, pelis, &numResultados);
                if (numResultados > 0) 
                {
                    printf("\nPelículas encontradas:\n");
                    printf("NOMBRE\t\t\t\tDURACION\tGENERO\tCALIFICACION\tVISTA\n");
                    for (int j = 0; j < numResultados; j++) 
                    {
                        int idx = resultados[j];
                        printf("%-30.30s\t%d\t\t%d\t%.2f\t\t%d\n",
                        pelis[idx].nombre, pelis[idx].duracion, pelis[idx].genero,
                        pelis[idx].calificacion, pelis[idx].vista);
                    }
                }else 
                {
                printf("No se encontró ninguna película con ese nombre.\n");
                }
                free(resultados);
                } else {
                printf("No hay películas registradas en el sistema.\n");
                }
    break;
            case 5:
            
                if (i > 0) 
				{
                    eliminarPelicula(&tam, &pelis, &i);
                } else 
				{
                    printf("No hay pelis registradas en el sistema.\n");
                }
                break;
                
            case 6:
                if (i > 0) 
                {
                    ordenarPorGenero(pelis, i);
                    printf("Peliculas ordenadas por genero:\n");
                    printf("NOMBRE\t\t\t\tDURACION\tGENERO\tCALIFICACION\tVISTAS\n\n");
                    for (int j = 0; j < i; j++) 
                    {
                        printf("%-30.30s\t%d\t\t%d\t%.2f\t\t%d\n", pelis[j].nombre, pelis[j].duracion, pelis[j].genero, pelis[j].calificacion, pelis[j].vista);
                    }
                } else 
                {
                    printf("No hay películas registradas en el sistema.\n");
                }
                break;
            case 7:
                break;
            case 8:
                printf("Gracias por utilizar nuestro programa. ¡Adios!\n");
                break;
            default:
                printf("Opcion no valida. Por favor, intente nuevamente.\n");
                break;
        }
        printf("\nPresione ENTER para continuar...");
        getchar();
    } while (op != 8);

    free(pelis);
    return 0;
}

void menu(void){
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
    printf("*    Salir                        -> 8    *\n");
	printf("* * * * * * * * * * * * * * * * * * * *\n\n");
	printf("Opcion: ");
}

void registro(int i, datos *pelis) {
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

    printf("\nIngrese el genero de la pelicula segun corresponda: ");
    do {
        scanf("%d", &pelis[i].genero);
		getchar();
        if (pelis[i].genero <= 0)
            printf("Por favor, ingrese un genero valido: ");
    } while (pelis[i].genero <= 0);
    
	pelis[i].calificacion = 0;
	
	pelis[i].vista = 0;
	
	printf("\nPelícula registrada correctamente.\n");
}

int* busqueda(int tam, datos* pelis, int* numResultados) {
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

void guardarLista(datos *pelis, int tam) {
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
    printf("\nLista de películas guardada correctamente en 'lista_pelis.txt'.\n");
}

int cargarLista(datos **pelis) {
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


void eliminarPelicula(int *tam, datos **pelis, int *i) {
    int numResultados;
    int* resultados = busqueda(*tam, *pelis, &numResultados);

    if (numResultados > 0) {
        printf("\nPelículas encontradas:\n");
        for (int j = 0; j < numResultados; j++) {
            int idx = resultados[j];
            printf("%d. %-30.30s\n", j + 1, (*pelis)[idx].nombre);
        }

        printf("\nSeleccione el índice de la película a eliminar (1-%d): ", numResultados);
        int seleccion;
        scanf("%d", &seleccion);
        getchar(); // Limpiar el buffer

        if (seleccion > 0 && seleccion <= numResultados) {
            int idxEliminar = resultados[seleccion - 1];

            printf("\nLa película '%s' ha sido eliminada de los registros.\n", (*pelis)[idxEliminar].nombre);

            // Mover última película al índice a eliminar
            (*pelis)[idxEliminar] = (*pelis)[*tam - 1];
            (*tam)--;
            (*i)--;

            // Reasignar memoria
            *pelis = realloc(*pelis, (*tam) * sizeof(datos));
            if (*pelis == NULL && *tam > 0) {
                printf("Error al reasignar memoria.\n");
                exit(1);
            }

            guardarLista(*pelis, *tam);
        } else {
            printf("Selección inválida.\n");
        }
    } else {
        printf("No se encontró ninguna película con el nombre especificado.\n");
    }

    free(resultados);
}


void ordenarPorGenero(datos* pelis, int tam) {
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