#include <stdio.h>
#include <string.h>

#define MAX 5

int main() {
    // Arreglos paralelos básicos
    char nombres[MAX][30];
    int demandas[MAX];
    float tiempos[MAX];
    int recursos[MAX];
    
    int total = 0;
    int opcion = 0;

    do {
        // Menú principal
        printf("\n==================================\n");
        printf("    CONTROL DE PRODUCCION - FABRICA\n");
        printf("==================================\n");
        printf("1. Registrar producto\n");
        printf("2. Ver productos\n");
        printf("3. Buscar y editar producto\n");
        printf("4. Buscar y eliminar producto\n");
        printf("5. Calcular tiempo, recursos y viabilidad\n");
        printf("6. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);
        
        // Limpiar el salto de línea que deja el scanf
        while (getchar() != '\n');

        // Opcion 1: Registrar
        if (opcion == 1) {
            if (total >= MAX) {
                printf("\nYa llegaste al límite de 5 productos.\n");
            } else {
                printf("\n--- REGISTRAR PRODUCTO %d ---\n", total + 1);
                
                printf("Nombre del producto: ");
                fgets(nombres[total], 30, stdin);
                // Quitar el salto de línea automático de fgets
                nombres[total][strcspn(nombres[total], "\n")] = 0;

                printf("Cantidad a fabricar (Demanda): ");
                scanf("%d", &demandas[total]);

                printf("Tiempo unitario (horas): ");
                scanf("%f", &tiempos[total]);

                printf("Recursos unitarios necesarios: ");
                scanf("%d", &recursos[total]);
                while (getchar() != '\n');

                total++;
                printf("\n¡Producto registrado con éxito!\n");
            }
        } 
        // Opcion 2: Ver inventario
        else if (opcion == 2) {
            if (total == 0) {
                printf("\nAún no hay productos registrados[cite: 2].\n");
            } else {
                printf("\n--- LISTA DE PRODUCTOS ---\n");
                for (int i = 0; i < total; i++) {
                    printf("%d. Nombre: %s\n", i + 1, nombres[i]);
                    printf("   - Demanda: %d\n", demandas[i]);
                    printf("   - Tiempo unitario: %.2f h\n", tiempos[i]);
                    printf("   - Recursos unitarios: %d\n", recursos[i]);
                    printf("---------------------------\n");
                }
            } 
        }
        // Opcion 3: Buscar y editar
        else if (opcion == 3) {
            if (total == 0) {
                printf("\nNo hay productos para editar[cite: 2].\n");
            } else {
                char buscado[30];
                printf("\nEscribe el nombre del producto a editar: ");
                fgets(buscado, 30, stdin);
                buscado[strcspn(buscado, "\n")] = 0;

                int pos = -1;
                // Búsqueda secuencial simple
                for (int i = 0; i < total; i++) {
                    if (strcmp(nombres[i], buscado) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("\nNo se encontró ese producto.\n");
                } else {
                    printf("\n¡Encontrado! Ingresa los nuevos datos:\n");
                    printf("Nuevo nombre: ");
                    fgets(nombres[pos], 30, stdin);
                    nombres[pos][strcspn(nombres[pos], "\n")] = 0;

                    printf("Nueva demanda: ");
                    scanf("%d", &demandas[pos]);

                    printf("Nuevo tiempo unitario: ");
                    scanf("%f", &tiempos[pos]);

                    printf("Nuevos recursos unitarios: ");
                    scanf("%d", &recursos[pos]);
                    while (getchar() != '\n');

                    printf("\n¡Producto modificado con éxito!\n");
                }
            }
        }
        // Opcion 4: Buscar y eliminar
        else if (opcion == 4) {
            if (total == 0) {
                printf("\nNo hay productos para eliminar[cite: 2].\n");
            } else {
                char buscado[30];
                printf("\nEscribe el nombre del producto a eliminar: ");
                fgets(buscado, 30, stdin);
                buscado[strcspn(buscado, "\n")] = 0;

                int pos = -1;
                for (int i = 0; i < total; i++) {
                    if (strcmp(nombres[i], buscado) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("\nNo se encontró ese producto.\n");
                } else {
                    // Recorrer los elementos hacia la izquierda para borrar
                    for (int i = pos; i < total - 1; i++) {
                        strcpy(nombres[i], nombres[i + 1]);
                        demandas[i] = demandas[i + 1];
                        tiempos[i] = tiempos[i + 1];
                        recursos[i] = recursos[i + 1];
                    }
                    total--;
                    printf("\n¡Producto eliminado con éxito!\n");
                }
            }
        }
        // Opcion 5: Calcular viabilidad
        else if (opcion == 5) {
            if (total == 0) {
                printf("\nPrimero registra al menos un producto[cite: 2].\n");
            } else {
                float tiempoTotal = 0;
                int recursosTotales = 0;

                // Calcular totales multiplicando demanda por unidad
                for (int i = 0; i < total; i++) {
                    tiempoTotal += demandas[i] * tiempos[i];
                    recursosTotales += demandas[i] * recursos[i];
                }

                float limiteTiempo;
                int limiteRecursos;

                printf("\n¿Cuántas horas totales hay disponibles en la fábrica?: ");
                scanf("%f", &limiteTiempo);
                printf("¿Cuántos recursos totales hay disponibles?: ");
                scanf("%d", &limiteRecursos);
                while (getchar() != '\n');

                printf("\n--- REPORTE DE VIABILIDAD ---\n");
                printf("Tiempo total requerido: %.2f horas[cite: 1, 2]\n", tiempoTotal);
                printf("Recursos totales requeridos: %d insumos[cite: 1, 2]\n", recursosTotales);

                if (tiempoTotal <= limiteTiempo && recursosTotales <= limiteRecursos) {
                    printf("ESTADO: [ FACTIBLE ] La fábrica cumple con la demanda[cite: 1, 2].\n");
                } else {
                    printf("ESTADO: [ NO FACTIBLE ] La fábrica no alcanza a producir todo[cite: 1, 2].\n");
                }
            }
        }
        else if (opcion == 6) {
            printf("\nSaliendo del programa...\n");
        }
        else {
            printf("\nOpción no válida[cite: 2].\n");
        }

    } while (opcion != 6);

    return 0;
}