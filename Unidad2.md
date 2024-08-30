### EJERCICIO 1

## 1. Identificación de Funciones:
Setup(): Se encarga de inicializar recursos, configurar el entorno y realizar preparaciones antes de que el juego comience a ejecutarse.

Update(): Es responsable de actualizar la lógica del juego en cada iteración del loop. Aquí se manejan las entradas del usuario, la física, y las interacciones entre objetos.

Render(): Dibuja los gráficos en la pantalla. Se encarga de la representación visual del juego, actualizando la pantalla con los últimos cambios.

## 2. Inserta un printf():
Se añade un printf() en cada función para observar el orden en que se ejecutan. Por ejemplo:

```c
void Setup() {
    printf("Setup function called\n");
    // Inicialización de recursos
}

void Update() {
    printf("Update function called\n");
    // Lógica del juego
}

void Render() {
    printf("Render function called\n");
    // Dibuja la escena
}
```

## 3. Ejecución del Programa:

Se ejecuta el programa y se observa cómo las funciones se llaman repetidamente. Esto te mostrará el ciclo continuo del Game Loop, donde Setup() se ejecuta al inicio, y luego Update() y Render() se llaman en cada iteración del loop.

### EJERCICIO 2

1. Agregar Cronometrado utilizando SDL_GetTicks()
SDL_GetTicks() es una función de SDL2 que devuelve el número de milisegundos que han transcurrido desde que se inició el subsistema SDL. Usaremos esta función para medir el tiempo antes y después de las llamadas a Update() y Render().



A. Inicializa Variables de Tiempo: Define variables para almacenar el tiempo antes y después de cada función, para calcular el tiempo transcurrido (delta time).

```c
#include <SDL2/SDL.h>
#include <stdio.h>

// Variables globales o dentro de tu main loop
Uint32 updateStartTime, updateEndTime, updateDeltaTime;
Uint32 renderStartTime, renderEndTime, renderDeltaTime;

```
b. Modifica la Función Update(): Mide el tiempo antes y después de la ejecución de Update().

```c
void Update() {
    updateStartTime = SDL_GetTicks();
    
    // Lógica del juego 
    printf("Update logic running...\n");
    
    updateEndTime = SDL_GetTicks();
    updateDeltaTime = updateEndTime - updateStartTime;
    
    printf("Update took %u milliseconds\n", updateDeltaTime);
}
```

c. Modifica la Función Render()

```c
void Render() {
    renderStartTime = SDL_GetTicks();
    
    // Código de renderizado aquí
    printf("Rendering scene...\n");
    
    renderEndTime = SDL_GetTicks();
    renderDeltaTime = renderEndTime - renderStartTime;
    
    printf("Render took %u milliseconds\n", renderDeltaTime);
}
```

d. Estructura del Game Loop

```c
int main(int argc, char* argv[]) {
    // Inicialización de SDL y otros recursos
    Setup();
    
    int running = 1;
    while (running) {
        Update();
        Render();
        
        // Manejo de eventos y condiciones para salir del loop
        SDL_Delay(16); 
    }
    
    // Limpieza y cierre de recursos
    SDL_Quit();
    return 0;
}
```

e. Compila y Ejecuta el Programa

```bash
gcc -o game main.c -lSDL2
./game
```
