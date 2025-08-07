# Makefile para el juego Snake
# Autor: Snake Game Project
# Versión: 1.0

# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = snake
SOURCE = snake.c

# Reglas principales
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Compilar con optimizaciones
release: CFLAGS += -O2
release: $(TARGET)

# Compilar con información de debug
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

# Limpiar archivos generados
clean:
	rm -f $(TARGET) *.o *.exe

# Instalar (copiar al directorio bin si existe)
install: $(TARGET)
	@if [ -d "/usr/local/bin" ]; then \
		sudo cp $(TARGET) /usr/local/bin/; \
		echo "Instalado en /usr/local/bin/$(TARGET)"; \
	else \
		echo "No se pudo instalar. Directorio /usr/local/bin no existe."; \
	fi

# Ejecutar el juego
run: $(TARGET)
	./$(TARGET)

# Mostrar ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make        - Compilar el juego"
	@echo "  make release - Compilar con optimizaciones"
	@echo "  make debug   - Compilar con información de debug"
	@echo "  make clean   - Limpiar archivos generados"
	@echo "  make install - Instalar el juego (requiere sudo)"
	@echo "  make run     - Compilar y ejecutar el juego"
	@echo "  make help    - Mostrar esta ayuda"

# Regla por defecto
.PHONY: all release debug clean install run help
