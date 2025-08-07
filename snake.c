// Juego Snake - Implementación en C
// IMPORTANTE: Al momento de ejecutar el programa asegúrese de poner la terminal en pantalla completa.
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para la serpiente
struct snake {
	int X, Y, AP;
	struct snake *next;
};

// Estructura para la manzana
struct manzana {
	int X, Y, AP;
};

// Estructura para almacenar puntuaciones
typedef struct Puntuacion {
	int puntuacion;
	char alias[10];
	struct Puntuacion *siguiente;
} Puntuacion;

Puntuacion *listaPuntuaciones;
struct snake *Snake;
struct manzana *Manzana;
int colaAnterior[2] = {1, 0};  // Para eliminar la parte final de la cola conforme se mueva

// Función para limpiar el buffer de entrada
void limpiar_stdin(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// Función para insertar una nueva puntuación en la lista de forma ordenada
void insertarPuntuacion(int puntuacion, char *alias) {
	Puntuacion *nueva_puntuacion = (Puntuacion *)malloc(sizeof(Puntuacion));
	if (nueva_puntuacion == NULL) {
		printf("No se pudo asignar memoria para la puntuación.\n");
		return;
	}
	nueva_puntuacion->puntuacion = puntuacion;
	strcpy(nueva_puntuacion->alias, alias);
	nueva_puntuacion->siguiente = NULL;
	
	if (listaPuntuaciones == NULL || listaPuntuaciones->puntuacion <= puntuacion) {
		nueva_puntuacion->siguiente = listaPuntuaciones;
		listaPuntuaciones = nueva_puntuacion;
	} else {
		Puntuacion *actual = listaPuntuaciones;
		while (actual->siguiente != NULL && actual->siguiente->puntuacion > puntuacion) {
			actual = actual->siguiente;
		}
		nueva_puntuacion->siguiente = actual->siguiente;
		actual->siguiente = nueva_puntuacion;
	}
}

// Función para cargar las puntuaciones desde un archivo de texto
void cargarPuntuaciones() {
	FILE *fptr;
	fptr = fopen("puntuaciones.txt", "r");
	char Cad[100];
	while (fgets(Cad, 100, fptr)) {
		printf("%s", Cad);
	}
	fclose(fptr);
}

// Función para imprimir la lista de puntuaciones
void imprimirPuntuaciones() {
	FILE *fptr;
	fptr = fopen("puntuaciones.txt", "r");
	if (fptr == NULL) {
		printf("No hay puntuaciones registradas.\n");
	} else {
		cargarPuntuaciones();
	}
}

// Función para guardar las puntuaciones en un archivo de texto
void guardarPuntuaciones() {
	int i = 1;
	FILE *archivo = fopen("puntuaciones.txt", "w");
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo para escribir las puntuaciones.\n");
		return;
	}
	Puntuacion *actual = listaPuntuaciones;
	while (actual != NULL) {
		fprintf(archivo, "%d. %s --------- %d\n", i, actual->alias, actual->puntuacion);
		actual = actual->siguiente;
		i++;
	}
	
	fclose(archivo);
	printf("Puntuaciones guardadas en puntuaciones.txt\n");
	Sleep(1000);
}

// Función para liberar la memoria de la lista de puntuaciones
void liberarMemoriaPuntuaciones() {
	Puntuacion *actual = listaPuntuaciones;
	while (actual != NULL) {
		Puntuacion *tmp = actual;
		actual = actual->siguiente;
		free(tmp);
	}
	listaPuntuaciones = NULL;
}

// Función que permite ubicarnos en una coordenada para ejecutar el código
void gotoxy(int x, int y) {
	printf("%c[%d;%dH", 27, y, x);
}

// Función para imprimir el tablero del juego
void imprimirTablero() {
	char c;
	gotoxy(5, 5);
	for (int j = 0; j < 50 + 2; ++j) {
		for (int i = 0; i < 50 + 2; ++i) {
			if (i == 0 || i == 51) {
				switch (j) {
				case 0:
					c = (i == 0) ? (char)201 : (char)187;
					break;
				case 51:
					c = (i == 0) ? (char)200 : (char)188;
					break;
				default:
					c = (char)186;
					break;
				}
			} else {
				if (j == 0 || j == 51) {
					c = (char)205;
				} else {
					c = ' ';
				}
			}
			printf("%c", c);
			if (i == 51) {
				gotoxy(5, 5 + j + 1);
			}
		}
	}
}

// Función para hacer crecer la serpiente
void crecer(int x, int y, struct snake *body) {
	if (body->next == NULL) {
		body->next = (struct snake *)malloc(sizeof(struct snake));
		body->next->X = x;
		body->next->Y = y;
		body->next->AP = 219;
		body->next->next = NULL;
	} else {
		crecer(x, y, body->next);
	}
}

// Función para inicializar el estado del juego
void estadoInicial() {
	Snake = (struct snake *)malloc(sizeof(struct snake));
	Snake->X = 30;
	Snake->Y = 30;
	Snake->AP = 219;
	Snake->next = NULL;
	crecer(30 - 1, 30, Snake);
}

// Función para verificar si la serpiente choca con la manzana
int choqueManzana(struct snake *body) {
	static int intersectan;
	if (body == Snake) {
		intersectan = 0;
	}
	intersectan = intersectan + (body->X == Manzana->X) && (body->Y == Manzana->Y);
	if (!intersectan) {
		if (body->next != NULL) {
			choqueManzana(body->next);
		}
	}
	return intersectan;
}

// Función para reubicar la manzana en una nueva posición aleatoria
void reubicarManzana() {
	Manzana->X = 6 + rand() % 45;
	Manzana->Y = 6 + rand() % 40;
	if (choqueManzana(Snake)) {
		reubicarManzana();
	}
}

// Función para hacer aparecer la manzana
void aparecerManzana() {
	Manzana = (struct manzana *)malloc(sizeof(struct manzana));
	Manzana->AP = 219;
	reubicarManzana();
}

// Función para imprimir la serpiente
void printSnake(struct snake *body) {
	gotoxy(body->X, body->Y);
	printf("%c", body->AP);
	if (body->next != NULL) {
		printSnake(body->next);
	} else {
		gotoxy(colaAnterior[0], colaAnterior[1]);
		printf(" ");
	}
}

// Función para imprimir la manzana
void imprimirManzana() {
	gotoxy(Manzana->X, Manzana->Y);
	printf("%c", Manzana->AP);
}

// Función para mover la serpiente
void mover(int x, int y, struct snake *body) {
	if (body->next != NULL) {
		mover(body->X, body->Y, body->next);
	} else {
		colaAnterior[0] = body->X;
		colaAnterior[1] = body->Y;
	}
	body->X = x;
	body->Y = y;
}

// Función para verificar si la serpiente choca con el tablero
int choqueTablero() {
	if (Snake->X <= 5 || Snake->X >= 56 || Snake->Y <= 5 || Snake->Y >= 47) {
		return 1;
	} else {
		return 0;
	}
}

// Función para verificar si la serpiente choca consigo misma
int choqueSerpiente(struct snake *body) {
	if ((Snake->X == body->X) && (Snake->Y == body->Y)) {
		return 1;
	} else {
		if (body->next != NULL) {
			return choqueSerpiente(body->next);
		} else {
			return 0;
		}
	}
}

int dir[2] = {1, 0};  // Dirección inicial de la serpiente (derecha)
int dirAnterior[2] = {1, 0};  // Dirección anterior de la serpiente

int main(int argc, char *argv[]) {
	int opcion, finDelJuego, T, puntuacion, digestion, movimientos, tam, dificultad, velocidad, turno;
	int puntuacionM[2];
	char alias[10];
	opcion = 0;
	dificultad = 2;
	printf("IMPORTANTE: Asegúrese de poner el juego en pantalla completa\n");
	system("pause");
	while (opcion != 6) {
		system("cls");
		printf("   _____   _   _              _____ \n");
		printf("  / ____| | \\ | |    /\\     _  __ | ____|\n ");
		printf(" | (___  |  \\| |   /  \\   | |/ / | |___ \n");
		printf("  \\___ \\| . ` |    / /\\      ' /  |  ___|\n");
		printf("  ____) | | . ` | / ____ \\ |  <   | |____\n");
		printf(" |_____/  |_|\\__| _|   _   |_|\\_\\ |______|\n");
		printf("\nIngrese la opcion que desee ejecutar:\n");
		printf("\n\t1. JUGAR\n");
		printf("\n\t2. DIFICULTAD\n");
		printf("\n\t3. MULTIJUGADOR\n");
		printf("\n\t4. PUNTUACIONES\n");
		printf("\n\t5. COMO JUGAR\n");
		printf("\n\t6. SALIR\n");
		printf("\nOPCION: ");
		scanf("%d", &opcion);
		limpiar_stdin();
		switch (opcion) {
		case 1:
			// Configuración inicial del juego para un jugador
			tam = 0;
			puntuacion = 0;
			finDelJuego = 0;
			T = 0;
			movimientos = 0;
			digestion = 0;
			char tecla = 0;
			system("cls");  // Borra todo de una consola de comandos
			imprimirTablero();
			estadoInicial();
			aparecerManzana();
			printSnake(Snake);
			imprimirManzana();
			// Bucle de juego:
			while (!finDelJuego) {
				gotoxy(5, 4);
				printf("Puntuacion: %d", puntuacion);
				if (kbhit()) {
					tecla = getch();
					if (tecla == 'w' || tecla == 'a' || tecla == 's' || tecla == 'd') {
						int nuevaDir[2] = {(tecla == 'd') - (tecla == 'a'), (tecla == 's') - (tecla == 'w')};
						// Evitar giro abrupto en dirección opuesta
						if (!(nuevaDir[0] == -dirAnterior[0] && nuevaDir[1] == -dirAnterior[1])) {
							dir[0] = nuevaDir[0];
							dir[1] = nuevaDir[1];
						}
					}
				}
				Sleep(16);
				T += 16;
				switch (dificultad) {
				case 1:
					velocidad = 90;
					break;
				case 2:
					velocidad = 60;
					break;
				case 3:
					velocidad = 30;
					break;
				}
				if (T >= velocidad) {
					printSnake(Snake);
					imprimirManzana();
					mover(Snake->X + dir[0], Snake->Y + dir[1], Snake);
					finDelJuego = choqueSerpiente(Snake->next) + choqueTablero();
					if (!digestion) {
						if (choqueManzana(Snake)) {
							puntuacion = puntuacion + 1;
							digestion = 1;
							movimientos = movimientos + tam;
						}
					} else {
						if (tam < puntuacion) {
							if (!movimientos) {
								crecer(Manzana->X, Manzana->Y, Snake);
								tam++;
							} else {
								movimientos--;
							}
						} else {
							reubicarManzana();
							digestion = 0;
						}
					}
					T = 0;
					// Actualizar la dirección anterior
					dirAnterior[0] = dir[0];
					dirAnterior[1] = dir[1];
				}
			}
			gotoxy(1, 58);
			printf("Fin del juego");
			printf("\nPuntuacion: %d", puntuacion);
			printf("\nIngrese su alias: ");
			fflush(stdin);
			gets(alias);
			alias[strcspn(alias, "\n")] = 0;
			insertarPuntuacion(puntuacion, alias);
			guardarPuntuaciones();
			break;
		case 2:
			// Configuración de dificultad
			system("cls");
			printf("\n Ingrese la dificultad que desea jugar:\n");
			printf("\n\t1. FACIL\n");
			printf("\n\t2. NORMAL\n");
			printf("\n\t3. DIFICIL\n");
			scanf("%d", &dificultad);
			limpiar_stdin();
			break;
		case 3:
			// Modo multijugador
			turno = 0;
			do {
				tam = 0;
				puntuacion = 0;
				finDelJuego = 0;
				T = 0;
				movimientos = 0;
				digestion = 0;
				char tecla = 0;
				system("cls");  // Borra todo de una consola de comandos
				printf("    Jugador %d", turno + 1);
				imprimirTablero();
				estadoInicial();
				aparecerManzana();
				printSnake(Snake);
				imprimirManzana();
				// Bucle de juego:
				while (!finDelJuego) {
					gotoxy(5, 4);
					printf("Puntuacion: %d", puntuacion);
					if (kbhit()) {
						tecla = getch();
						if (tecla == 'w' || tecla == 'a' || tecla == 's' || tecla == 'd') {
							int nuevaDir[2] = {(tecla == 'd') - (tecla == 'a'), (tecla == 's') - (tecla == 'w')};
							// Evitar giro abrupto en dirección opuesta
							if (!(nuevaDir[0] == -dirAnterior[0] && nuevaDir[1] == -dirAnterior[1])) {
								dir[0] = nuevaDir[0];
								dir[1] = nuevaDir[1];
							}
						}
					}
					Sleep(16);
					T += 16;
					switch (dificultad) {
					case 1:
						velocidad = 90;
						break;
					case 2:
						velocidad = 60;
						break;
					case 3:
						velocidad = 30;
						break;
					}
					if (T >= velocidad) {
						printSnake(Snake);
						imprimirManzana();
						mover(Snake->X + dir[0], Snake->Y + dir[1], Snake);
						finDelJuego = choqueSerpiente(Snake->next) + choqueTablero();
						if (!digestion) {
							if (choqueManzana(Snake)) {
								puntuacion = puntuacion + 1;
								digestion = 1;
								movimientos = movimientos + tam;
							}
						} else {
							if (tam < puntuacion) {
								if (!movimientos) {
									crecer(Manzana->X, Manzana->Y, Snake);
									tam++;
								} else {
									movimientos--;
								}
							} else {
								reubicarManzana();
								digestion = 0;
							}
						}
						T = 0;
						// Actualizar la dirección anterior
						dirAnterior[0] = dir[0];
						dirAnterior[1] = dir[1];
					}
				}
				gotoxy(1, 58);
				printf("\nFin del turno del Jugador %d", turno + 1);
				printf("\nPuntuacion Jugador %d: %d\n", turno + 1, puntuacion);
				puntuacionM[turno] = puntuacion;
				system("pause");
				++turno;
			} while (turno != 2);
			if (puntuacionM[0] == puntuacionM[1]) {
				printf("\nEMPATE\n");
			} else if (puntuacionM[0] > puntuacionM[1]) {
				printf("\nJugador 1 Ganador\n");
			} else {
				printf("\nJugador 2 Ganador\n");
			}
			system("pause");
			break;
		case 4:
			// Mostrar puntuaciones
			system("cls");
			printf("Puntuaciones.\n\n");
			imprimirPuntuaciones();
			printf("\nPresione cualquier tecla para regresar al menú...");
			getchar();
			break;
		case 5:
			// Mostrar cómo jugar
			system("cls");
			printf("El juego Snake es un clásico juego de arcade en el que el \n"
				   "jugador controla una serpiente que se mueve por un tablero. \n"
				   "La serpiente debe comer manzanas que aparecen en posiciones \n"
				   "aleatorias en el tablero. Cada vez que la serpiente come una \n"
				   "manzana, crece en longitud. El objetivo del juego es hacer \n"
				   "que la serpiente sea lo más larga posible sin chocar contra \n"
				   "las paredes del tablero ni contra sí misma. El jugador \n"
				   "controla la dirección de la serpiente usando las teclas \n"
				   "'W', 'A', 'S' y 'D' para moverse hacia arriba, izquierda, \n"
				   "abajo y derecha, respectivamente. La puntuación del jugador \n"
				   "aumenta con cada manzana que la serpiente consume. El juego \n"
				   "termina si la serpiente choca contra las paredes o contra su \n"
				   "propio cuerpo.\n\n");
			printf("\nPresione Enter para regresar al menú...");
			getchar();
			break;
		case 6:
			// Salir del programa
			printf("\n Saliendo del programa...\n");
			break;
		default:
			printf("\n Opción no válida. Por favor, seleccione una opción del 1 al 6.\n");
		}
	}
	
	liberarMemoriaPuntuaciones();
	return 0;
}



