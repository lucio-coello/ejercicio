#include <stdio.h>
#include <string.h>

char nombres[5][20];
float tiempos[5][3];
int cantidadNadadores = 0;
int datosIngresados = 0;

int main() {
    int opciones, i, j;

    do {
        printf("\n--- Identificador de ganadores ---\n");
        printf("1. Ingresar datos de los nadadores\n");
        printf("2. Mostrar ganadores\n");
        printf("3. Salir\n");
        printf(">> ");
        scanf("%d", &opciones);
        getchar();

        switch (opciones) {
        case 1:
            do {
                printf("Ingrese la cantidad de nadadores (maximo 5): ");
                if (scanf("%d", &cantidadNadadores) != 1 || cantidadNadadores < 1 || cantidadNadadores > 5) {
                    printf("Cantidad invalida. Intente nuevamente.\n");
                    while (getchar() != '\n');
                    cantidadNadadores = 0;
                }
            } while (cantidadNadadores == 0);

            for (i = 0; i < cantidadNadadores; i++) {
                printf("Ingrese el nombre del nadador %d: ", i + 1);
                scanf("%19s", nombres[i]);
                getchar();

                for (j = 0; j < 3; j++) {
                    do {
                        printf("Ingrese el tiempo en competencia %d (en segundos): ", j + 1);
                        if (scanf("%f", &tiempos[i][j]) != 1 || tiempos[i][j] < 0) {
                            printf("Tiempo invalido. Intente de nuevo.\n");
                            while (getchar() != '\n');
                            tiempos[i][j] = -1;
                        }
                    } while (tiempos[i][j] < 0);
                }
            }
            datosIngresados = 1;
            break;

        case 2:
            if (!datosIngresados) {
                printf("Primero debe ingresar los datos de los nadadores.\n");
            } else {
                int victorias[5] = {0};

                for (j = 0; j < 3; j++) {
                    int ganadorCompetencia = 0;
                    for (i = 1; i < cantidadNadadores; i++) {
                        if (tiempos[i][j] < tiempos[ganadorCompetencia][j]) {
                            ganadorCompetencia = i;
                        }
                    }
                    victorias[ganadorCompetencia]++;
                    printf("Ganador de la competencia %d: %s con %.2f segundos\n",
                           j + 1, nombres[ganadorCompetencia], tiempos[ganadorCompetencia][j]);
                }

                int maxVictorias = victorias[0];
                for (i = 1; i < cantidadNadadores; i++) {
                    if (victorias[i] > maxVictorias) {
                        maxVictorias = victorias[i];
                    }
                }

                int cantidadEmpates = 0;
                for (i = 0; i < cantidadNadadores; i++) {
                    if (victorias[i] == maxVictorias) {
                        cantidadEmpates++;
                    }
                }

                printf("\nResultados finales:\n");
                if (cantidadEmpates == 1) {
                    for (i = 0; i < cantidadNadadores; i++) {
                        if (victorias[i] == maxVictorias) {
                            printf("El mejor nadador global es %s con %d competencia(s) ganada(s).\n",
                                   nombres[i], maxVictorias);
                            break;
                        }
                    }
                } else {
                    printf("Empate entre los siguientes nadadores con %d competencia(s) ganada(s):\n", maxVictorias);
                    for (i = 0; i < cantidadNadadores; i++) {
                        if (victorias[i] == maxVictorias) {
                            printf("- %s\n", nombres[i]);
                        }
                    }
                }

                printf("\nPromedio de tiempos por nadador:\n");
                for (i = 0; i < cantidadNadadores; i++) {
                    float suma = 0;
                    for (j = 0; j < 3; j++) {
                        suma += tiempos[i][j];
                    }
                    float promedio = suma / 3.0;
                    printf("%s: %.2f segundos\n", nombres[i], promedio);
                }
            }
            break;

        case 3:
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opcion invalida. Intente nuevamente.\n");
        }

    } while (opciones != 3);

    return 0;
}
