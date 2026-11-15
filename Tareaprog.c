#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROD 5
#define MAX_NOMBRE 30

void mostrarMenu();
void agregarProducto(char nombres[][MAX_NOMBRE], int *demandas, float *tiempos, int *recursos, int *total);
void verInventario(char nombres[][MAX_NOMBRE], int *demandas, float *tiempos, int *recursos, int total);
int buscarPorNombre(char nombres[][MAX_NOMBRE], int total, char *buscado);
void modificarProducto(char nombres[][MAX_NOMBRE], int *demandas, float *tiempos, int *recursos, int total);
void borrarProducto(char nombres[][MAX_NOMBRE], int *demandas, float *tiempos, int *recursos, int *total);
void calcularViabilidad(int *demandas, float *tiempos, int *recursos, int total);

int main() {
    char nombres[MAX_PROD][MAX_NOMBRE];
    int demandas[MAX_PROD];
    float tiempos[MAX_PROD];
    int recursos[MAX_PROD];
    
    int totalProductos = 0;
    int opcion;

    do {
        mostrarMenu();
        printf("Elige una opcion: ");
        scanf("%d", &opcion);
        
        while (getchar() != '\n');

        switch (opcion) {
            case 1:
                agregarProducto(nombres, demandas, tiempos, recursos, &totalProductos);
                break;
            case 2:
                verInventario(nombres, demandas, tiempos, recursos, totalProductos);
                break;
            case 3:
                modificarProducto(nombres, demandas, tiempos, recursos, totalProductos);
                break;
            case 4:
                borrarProducto(nombres, demandas, tiempos, recursos, &totalProductos);
                break;
            case 5:
                calcularViabilidad(demandas, tiempos, recursos, totalProductos);
                break;
            case 6:
                printf("\nSaliendo del programa... ¡Hasta luego!\n");
                break;
            default:
                printf("\nOpción no válida. Inténtalo de nuevo.\n");
        }
        
        if (opcion != 6) {
            printf("\n");
            system("pause");
            system("cls");
        }
    } while (opcion != 6);

    return 0;
}

void mostrarMenu() {
    printf("==================================================\n");
    printf("    CONTROL DE PRODUCCION - FABRICA ELECTRONICA\n");
    printf("==================================================\n");
    printf("1. Registrar nuevo producto (Max. 5)\n");
    printf("2. Ver productos registrados\n");
    printf("3. Buscar y editar un producto\n");
    printf("4. Buscar y eliminar un producto\n");
    printf("5. Calcular tiempos, recursos y viabilidad\n");
    printf("6. Salir\n");
    printf("==================================================\n");
}

void agregarProducto(char nombres[][MAX_NOMBRE], int *demandas, float *tiempos, int *recursos, int *total) {
    if (*total >= MAX_PROD) {
        printf("\nYa llegaste al límite de 5 productos.\n");
        return;
    }

    printf("\n--- REGISTRO DE PRODUCTO (%d/%d) ---\n", *total + 1, MAX_PROD);

    printf("Nombre del componente: ");
    fgets(*(nombres + *total), MAX_NOMBRE, stdin);
    
    size_t len = strlen(*(nombres + *total));
    if (len > 0 && *(*(nombres + *total) + len - 1) == '\n') {
        *(*(nombres + *total) + len - 1) = '\0';
    }

    printf("Cantidad a fabricar (Demanda): ");
    scanf("%d", (demandas + *total));

    printf("Tiempo por unidad (en horas): ");
    scanf("%f", (tiempos + *total));

    printf("Recursos necesarios por unidad (insumos): ");
    scanf("%d", (recursos + *total));

    (*total)++;
    printf("\n¡Producto guardado con éxito!\n");
}

void verInventario(char nombres[][MAX_NOMBRE], int *demandas, float *tiempos, int *recursos, int total) {
    if (total == 0) {
        printf("\nAún no hay productos registrados.\n");
        return;
    }

    printf("\n--------------------------------------------------\n");
    printf("               LISTA DE PRODUCTOS                 \n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf(" Producto %d: %s\n", i + 1, *(nombres + i));
        printf("   - Demanda: %d unidades\n", *(demandas + i));
        printf("   - Tiempo unitario: %.2f horas\n", *(tiempos + i));
        printf("   - Recursos unitarios: %d insumos\n", *(recursos + i));
        printf("--------------------------------------------------\n");
    }
}

int buscarPorNombre(char nombres[][MAX_NOMBRE], int total, char *buscado) {
    for (int i = 0; i < total; i++) {
        if (strcmp(*(nombres + i), buscado) == 0) {
            return i;
        }
    }
    return -1;
}

void modificarProducto(char nombres[][MAX_NOMBRE], int *demandas, float *tiempos, int *recursos, int total) {
    if (total == 0) {
        printf("\nNo hay productos para editar.\n");
        return;
    }

    char buscado[MAX_NOMBRE];
    printf("\nEscribe el nombre exacto del producto que quieres buscar y editar: ");
    fgets(buscado, MAX_NOMBRE, stdin);
    size_t len = strlen(buscado);
    if (len > 0 && buscado[len - 1] == '\n') {
        buscado[len - 1] = '\0';
    }

    int pos = buscarPorNombre(nombres, total, buscado);

    if (pos == -1) {
        printf("\nNo se encontró ningún producto con ese nombre.\n");
        return;
    }

    printf("\n¡Encontrado en la posición %d! Ingresa los nuevos datos:\n", pos + 1);
    
    printf("Nuevo nombre: ");
    fgets(*(nombres + pos), MAX_NOMBRE, stdin);
    len = strlen(*(nombres + pos));
    if (len > 0 && *(*(nombres + pos) + len - 1) == '\n') {
        *(*(nombres + pos) + len - 1) = '\0';
    }

    printf("Nueva demanda: ");
    scanf("%d", (demandas + pos));

    printf("Nuevo tiempo unitario (horas): ");
    scanf("%f", (tiempos + pos));

    printf("Nuevos recursos unitarios: ");
    scanf("%d", (recursos + pos));

    printf("\n¡Producto modificado correctamente!\n");
}

void borrarProducto(char nombres[][MAX_NOMBRE], int *demandas, float *tiempos, int *recursos, int *total) {
    if (*total == 0) {
        printf("\nNo hay productos para eliminar.\n");
        return;
    }

    char buscado[MAX_NOMBRE];
    printf("\nEscribe el nombre exacto del producto que deseas eliminar: ");
    fgets(buscado, MAX_NOMBRE, stdin);
    size_t len = strlen(buscado);
    if (len > 0 && buscado[len - 1] == '\n') {
        buscado[len - 1] = '\0';
    }

    int pos = buscarPorNombre(nombres, *total, buscado);

    if (pos == -1) {
        printf("\nEl producto no existe en el sistema.\n");
        return;
    }

    for (int i = pos; i < *total - 1; i++) {
        strcpy(*(nombres + i), *(nombres + (i + 1)));
        *(demandas + i) = *(demandas + (i + 1));
        *(tiempos + i) = *(tiempos + (i + 1));
        *(recursos + i) = *(recursos + (i + 1));
    }

    (*total)--;
    printf("\nProducto eliminado y lista actualizada.\n");
}

void calcularViabilidad(int *demandas, float *tiempos, int *recursos, int total) {
    if (total == 0) {
        printf("\nPrimero debes registrar al menos un producto.\n");
        return;
    }

    float tiempoTotal = 0;
    int recursosTotales = 0;

    for (int i = 0; i < total; i++) {
        tiempoTotal += (*(demandas + i)) * (*(tiempos + i));
        recursosTotales += (*(demandas + i)) * (*(recursos + i));
    }

    float tiempoLimite;
    int recursosLimite;

    printf("\n--- LIMITES DISPONIBLES EN LA FABRICA ---\n");
    printf("¿Cuántas horas de tiempo total hay disponibles?: ");
    scanf("%f", &tiempoLimite);

    printf("¿Cuántos recursos/insumos máximos hay disponibles?: ");
    scanf("%d", &recursosLimite);

    printf("\n==================================================\n");
    printf("                REPORTE DE RESULTADOS             \n");
    printf("==================================================\n");
    printf("1. Tiempo total requerido: %.2f horas\n", tiempoTotal);
    printf("2. Recursos totales requeridos: %d insumos\n", recursosTotales);
    printf("--------------------------------------------------\n");
    printf("3. Estado de la producción:\n");

    int tiempoBien = (tiempoTotal <= tiempoLimite);
    int recursosBien = (recursosTotales <= recursosLimite);

    if (tiempoBien && recursosBien) {
        printf("   -> [ FACTIBLE ] La fábrica CUMPLE con la demanda.\n");
    } else {
        printf("   -> [ NO FACTIBLE ] La fábrica NO alcanza a producir todo.\n");
        if (!tiempoBien) {
            printf("      * Faltan %.2f horas de producción.\n", tiempoTotal - tiempoLimite);
        }
        if (!recursosBien) {
            printf("      * Faltan %d unidades de recursos.\n", recursosTotales - recursosLimite);
        }
    }
    printf("==================================================\n");
}