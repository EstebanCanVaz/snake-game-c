# 🐍 Juego Snake en C

Proyecto escolar que implementa el clásico juego Snake en lenguaje C, con características como sistema de puntuaciones, múltiples dificultades y modo multijugador.

## 🎮 Características

- **Modo Individual**: Juego clásico de Snake con sistema de puntuación
- **Modo Multijugador**: Dos jugadores juegan por turnos
- **Sistema de Dificultad**: 3 niveles (Fácil, Normal, Difícil)
- **Sistema de Puntuaciones**: Guardado y carga de puntuaciones desde archivo
- **Interfaz Gráfica**: Tablero dibujado con caracteres ASCII
- **Persistencia de Datos**: Las puntuaciones se guardan automáticamente

## 🚀 Instalación y Ejecución

### Requisitos
- Compilador de C (GCC, Clang, etc.)
- Sistema operativo Windows (por el uso de `windows.h` y `conio.h`)
- Terminal en pantalla completa para mejor experiencia

### Compilación
```bash
gcc -o snake snake.c
```

### Ejecución
```bash
./snake
```

**⚠️ IMPORTANTE**: Ejecuta el programa en pantalla completa para la mejor experiencia de juego.

## 🎯 Cómo Jugar

### Controles
- **W**: Mover hacia arriba
- **A**: Mover hacia la izquierda
- **S**: Mover hacia abajo
- **D**: Mover hacia la derecha

### Objetivo
- Come las manzanas (■) para crecer y ganar puntos
- Evita chocar contra las paredes del tablero
- Evita chocar contra tu propio cuerpo
- Intenta conseguir la puntuación más alta posible

## 🎛️ Modos de Juego

### 1. JUGAR (Modo Individual)
- Juego clásico de Snake
- Sistema de puntuación automático
- Guardado de puntuaciones con alias

### 2. DIFICULTAD
- **Fácil**: Movimiento lento (90ms)
- **Normal**: Velocidad media (60ms)
- **Difícil**: Movimiento rápido (30ms)

### 3. MULTIJUGADOR
- Dos jugadores juegan por turnos
- Comparación de puntuaciones al final
- Declaración automática del ganador

### 4. PUNTUACIONES
- Visualización de puntuaciones guardadas
- Lista ordenada por puntuación

### 5. CÓMO JUGAR
- Instrucciones detalladas del juego

## 📁 Estructura del Proyecto

```
snake/
├── snake.c          # Código fuente principal
├── snake.exe        # Ejecutable compilado
├── puntuaciones.txt # Archivo de puntuaciones (se crea automáticamente)
└── README.md        # Este archivo
```

## 🏗️ Arquitectura del Código

### Estructuras de Datos
- `struct snake`: Lista enlazada para el cuerpo de la serpiente
- `struct manzana`: Estructura para las manzanas del juego
- `struct Puntuacion`: Lista enlazada para almacenar puntuaciones

### Funciones Principales
- **Gestión de Juego**: `estadoInicial()`, `mover()`, `crecer()`
- **Detección de Colisiones**: `choqueTablero()`, `choqueSerpiente()`, `choqueManzana()`
- **Sistema de Puntuaciones**: `insertarPuntuacion()`, `guardarPuntuaciones()`
- **Interfaz**: `imprimirTablero()`, `printSnake()`, `imprimirManzana()`

## 🎨 Características Técnicas

- **Memoria Dinámica**: Uso de `malloc()` para estructuras dinámicas
- **Entrada No Bloqueante**: Uso de `kbhit()` y `getch()`
- **Posicionamiento de Cursor**: Función `gotoxy()` personalizada
- **Persistencia de Datos**: Sistema de archivos para puntuaciones
- **Prevención de Errores**: Evita giros de 180° y manejo de memoria

## 📊 Sistema de Puntuaciones

Las puntuaciones se guardan en el archivo `puntuaciones.txt` con el formato:
```
1. ALIAS --------- PUNTUACION
2. ALIAS --------- PUNTUACION
...
```

## 🔧 Personalización

### Cambiar Velocidad del Juego
Modifica los valores en la función `main()`:
```c
case 1: velocidad = 90;  // Fácil
case 2: velocidad = 60;  // Normal  
case 3: velocidad = 30;  // Difícil
```

### Cambiar Tamaño del Tablero
Modifica las constantes en `imprimirTablero()` y `choqueTablero()`.

## 🐛 Solución de Problemas

### Error de Compilación
- Asegúrate de tener un compilador de C instalado
- En Windows, usa MinGW o Visual Studio

### Problemas de Visualización
- Ejecuta en pantalla completa
- Usa una terminal compatible con caracteres ASCII

### Problemas de Rendimiento
- Cierra otras aplicaciones para mejor rendimiento
- En modo difícil, el juego puede ser muy rápido





---

**¡Disfruta jugando Snake!** 🐍🎮
