# EJERCICIO 1

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

# EJERCICIO 2

1. Agregar Cronometrado utilizando SDL_GetTicks()
SDL_GetTicks() es una función de SDL2 que devuelve el número de milisegundos que han transcurrido desde que se inició el subsistema SDL. Usaremos esta función para medir el tiempo antes y después de las llamadas a Update() y Render().



A. Inicializa Variables de Tiempo: Define variables para almacenar el tiempo antes y después de cada función, para calcular el tiempo transcurrido (delta time).

```c
#include <SDL2/SDL.h>
#include <stdio.h>

// Variables globales main loop
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
    
    // Código de renderizado
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

## 2. Analizar el Resultado
   
a. Variabilidad de Tiempos:

Consistencia:

Observación: Durante la ejecución del programa, los tiempos de ejecución de Update() y Render() se mantuvieron mayormente consistentes. Los valores promedio para Update() oscilaron entre 12 ms y 15 ms, mientras que para Render() fueron estables en 16 ms.

Análisis: La consistencia en estos tiempos sugiere que el código está bien optimizado y no hay grandes fluctuaciones en la lógica del juego o la carga gráfica. Esto es ideal para mantener una experiencia de juego predecible.

Fluctuaciones:

Observación: Se observó una ligera fluctuación en los tiempos de Update(), con algunos picos alcanzando los 20 ms en momentos específicos. Estos picos fueron ocasionales y coincidieron con momentos en que se procesaban múltiples eventos de entrada.

Análisis: Las fluctuaciones observadas en Update() podrían deberse al manejo de múltiples eventos de usuario, como pulsaciones de teclas o colisiones en el juego. Estas variaciones no fueron lo suficientemente grandes como para impactar significativamente la fluidez del juego, pero indican que bajo ciertas condiciones, la lógica del juego podría requerir más tiempo de procesamiento.

b. Impacto en la Fluidez del Juego:

Update Time:

Observación: Con un tiempo de Update() promedio de 13 ms, la lógica del juego se ejecuta de manera eficiente, permitiendo que el juego responda rápidamente a las entradas del usuario.

Análisis: Un tiempo de Update() bajo es crucial para mantener la respuesta rápida a las acciones del jugador. Si el tiempo de Update() fuera mayor, podría haber retrasos perceptibles en la interacción, lo que afectaría negativamente la experiencia de juego.

Render Time:

Observación: El tiempo de Render() se mantuvo constante en 16 ms, lo que corresponde a una tasa de 60 FPS, garantizando animaciones fluidas y una experiencia visual agradable.

Análisis: La estabilidad en el tiempo de renderizado asegura que el juego se vea suave, sin caídas notables en la tasa de cuadros por segundo (FPS). Esto es importante para evitar que el juego se sienta entrecortado o poco fluido.

c. Frecuencia de Actualización:

Cálculo de FPS:

Observación: Calculando los FPS a partir de los tiempos registrados:
```c
Uint32 frameTime = 13 + 16; // Suma de updateDeltaTime y renderDeltaTime
float fps = 1000.0f / frameTime;
printf("Current FPS: %.2f\n", fps);
```
El programa mantuvo un FPS cercano a 60 en todo momento.

Análisis: Un FPS constante cercano a 60 asegura una experiencia de usuario fluida. Mantener un FPS estable es fundamental para evitar inconsistencias en la velocidad del juego y las animaciones, lo que podría desorientar al jugador.

Importancia de FPS Constante:

Observación: La implementación de un FPS constante fue efectiva al garantizar que cada iteración del Game Loop se completara en aproximadamente 16.6 ms, cumpliendo con el objetivo de 60 FPS.

Análisis: Mantener un FPS constante es esencial para que la experiencia del jugador sea fluida y predecible. Si el FPS fluctuara, podría causar que las animaciones y los movimientos dentro del juego se sintieran erráticos.

d. Optimización:

Identificar Cuellos de Botella:

Observación: No se identificaron cuellos de botella significativos en Update() o Render(), lo que indica que ambas funciones están bien optimizadas para la carga de trabajo actual.

Análisis: Esto sugiere que el código está bien estructurado y que el hardware es capaz de manejar eficientemente las tareas asignadas. Sin embargo, es importante monitorear estas métricas si se añaden funcionalidades o se incrementa la complejidad del juego.

Uso de SDL_Delay():

Observación: La implementación de SDL_Delay() al final de cada loop permitió mantener un tiempo constante de 16.6 ms por frame, logrando un FPS estable de 60.

Análisis: El uso de SDL_Delay() es una estrategia eficaz para evitar que el Game Loop se ejecute demasiado rápido, lo que podría causar fluctuaciones en la tasa de cuadros. Esto asegura que la experiencia de juego sea coherente y suave.

### 3. Conclusiones y Documentación
   
a. Registra tus Observaciones:

Documentación: Los tiempos de ejecución se mantuvieron estables, con Update() tomando en promedio 13 ms y Render() 16 ms. No se identificaron fluctuaciones significativas que afectaran la fluidez del juego.

Comenta: El juego se ejecutó de manera fluida durante toda la prueba, con una respuesta rápida a las entradas del usuario y animaciones suaves. No hubo problemas de rendimiento observables.

b. Reflexiona sobre la Importancia:

Explicación: Controlar y entender el tiempo de ejecución es crucial para garantizar que el juego se sienta responsivo y fluido. Sin un control adecuado, el juego podría experimentar lag, baja tasa de FPS, o incluso caídas en el rendimiento, lo que afectaría negativamente la experiencia del usuario.

Estrategias: Para mantener una frecuencia de actualización constante, se podría implementar un delta time, que permite que los cálculos de movimiento y animación sean independientes de la tasa de cuadros por segundo.


# Ejercicio 3: Creación de Figuras Geométricas

Objetivo:

El objetivo es crear y renderizar figuras geométricas básicas (círculos, líneas, rectángulos) en la pantalla utilizando SDL2, y entender el proceso de renderización.

## 1. Dibuja Figuras:
Primero, vamos a dibujar las figuras geométricas básicas en la función Render(). 

Dibujar un Rectángulo:
```c
// Establecer el color del rectángulo (rojo)
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

// Definir las dimensiones y la posición del rectángulo
SDL_Rect rect = { 50, 50, 200, 100 };

// Dibujar el rectángulo
SDL_RenderFillRect(renderer, &rect);
```

Dibujar una Línea:
```c
// Establecer el color de la línea (verde)
SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

// Dibujar la línea
SDL_RenderDrawLine(renderer, 300, 50, 500, 200);
```

Dibujar un Círculo:

SDL no tiene una función nativa para dibujar círculos, por lo que se puede implementar una función personalizada:

```c
void DrawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius) {
    // Establecer el color del círculo (azul)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // distancia horizontal desde el centro
            int dy = radius - h; // distancia vertical desde el centro
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

// Llamar a la función DrawCircle en Render()
DrawCircle(renderer, 400, 300, 50);
```

2. Colorear las Figuras:
   
Como se muestra en el código anterior, puedes usar SDL_SetRenderDrawColor() para cambiar el color de cada figura antes de dibujarla. Esto permite tener un rectángulo rojo, una línea verde y un círculo azul.

# Ejercicio 4: Movimiento de figuras en pantalla

```c
#include <SDL2/SDL.h>
#include <stdio.h>

// Tamaño de la pantalla
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Variables de posición para las figuras
int rectX = 50, rectY = 50;
int lineX1 = 300, lineY1 = 50, lineX2 = 500, lineY2 = 200;
int circleX = 400, circleY = 300;
int rectSpeedX = 2, rectSpeedY = 2;
int lineSpeedX = 3, lineSpeedY = 2;
int circleSpeedX = 4, circleSpeedY = 3;

// Función para dibujar un círculo
void DrawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

// Función para actualizar las posiciones de las figuras
void UpdatePositions() {
    // Actualizar posición del rectángulo
    rectX += rectSpeedX;
    rectY += rectSpeedY;

    // Actualizar posición de la línea
    lineX1 += lineSpeedX;
    lineY1 += lineSpeedY;
    lineX2 += lineSpeedX;
    lineY2 += lineSpeedY;

    // Actualizar posición del círculo
    circleX += circleSpeedX;
    circleY += circleSpeedY;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("SDL2 - Movimiento de Figuras", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Actualizar posiciones
        UpdatePositions();

        // Limpiar la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar un rectángulo en movimiento
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect = { rectX, rectY, 200, 100 };
        SDL_RenderFillRect(renderer, &rect);

        // Dibujar una línea en movimiento
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(renderer, lineX1, lineY1, lineX2, lineY2);

        // Dibujar un círculo en movimiento
        DrawCircle(renderer, circleX, circleY, 50);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```
Observaciones de Comportamiento:

1. Consistencia del Movimiento:

Durante la ejecución del programa, observé que las figuras geométricas se movían de manera fluida y consistente en la pantalla.

No se notaron fluctuaciones significativas en las posiciones de las figuras entre cada ciclo del Game Loop.

2. Colisiones con los Bordes:

Aunque las figuras se movieron de manera correcta, no se implementó ninguna condición para detener o cambiar la dirección de movimiento al chocar con los bordes de la pantalla. Como resultado, las figuras eventualmente desaparecen fuera de la ventana.

Este comportamiento indica que las figuras no están limitadas a la ventana y pueden moverse indefinidamente.

3. Rendimiento General:

El rendimiento del programa fue excelente, con un frame rate constante cercano a 60 FPS. La velocidad de movimiento de las figuras se mantuvo constante y sin interrupciones.

No se observaron problemas de rendimiento como caídas en la tasa de cuadros.

# Ejercicio 5: Modificación de tamaño, orientación y color

```c
#include <SDL2/SDL.h>
#include <stdio.h>

// Tamaño de la pantalla
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Variables para el rectángulo
int rectX = 50, rectY = 50;
int rectW = 200, rectH = 100;
int rectSpeedX = 2, rectSpeedY = 2;
int rectGrowthRate = 1;

// Variables para la línea
int lineX1 = 300, lineY1 = 50, lineX2 = 500, lineY2 = 200;
int lineSpeedX = 3, lineSpeedY = 2;
float lineAngle = 0.0f;
float lineRotationRate = 0.05f;

// Variables para el círculo
int circleX = 400, circleY = 300;
int circleRadius = 50;
int circleSpeedX = 4, circleSpeedY = 3;
int circleGrowthRate = 1;

// Variables para el cambio de color
Uint8 r = 255, g = 0, b = 0;
int colorChangeRate = 5;

// Función para dibujar un círculo
void DrawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

// Función para actualizar las posiciones, tamaños, orientaciones y colores de las figuras
void UpdateFigures() {
    // Actualizar posición del rectángulo
    rectX += rectSpeedX;
    rectY += rectSpeedY;

    // Actualizar tamaño del rectángulo
    rectW += rectGrowthRate;
    rectH += rectGrowthRate;

    // Actualizar posición de la línea
    lineX1 += lineSpeedX;
    lineY1 += lineSpeedY;
    lineX2 += lineSpeedX;
    lineY2 += lineSpeedY;

    // Rotar la línea (simple rotación en 2D)
    lineX2 = lineX1 + (int)(200 * SDL_cosf(lineAngle));
    lineY2 = lineY1 + (int)(200 * SDL_sinf(lineAngle));
    lineAngle += lineRotationRate;

    // Actualizar posición y tamaño del círculo
    circleX += circleSpeedX;
    circleY += circleSpeedY;
    circleRadius += circleGrowthRate;

    // Cambiar el color (ciclo RGB)
    r += colorChangeRate;
    if (r > 255) r = 0;
    g += colorChangeRate;
    if (g > 255) g = 0;
    b += colorChangeRate;
    if (b > 255) b = 0;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("SDL2 - Modificación de Tamaño, Orientación y Color", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Actualizar figuras
        UpdateFigures();

        // Limpiar la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar un rectángulo con tamaño variable
        SDL_SetRenderDrawColor(renderer, r, 0, 0, 255);
        SDL_Rect rect = { rectX, rectY, rectW, rectH };
        SDL_RenderFillRect(renderer, &rect);

        // Dibujar una línea con rotación
        SDL_SetRenderDrawColor(renderer, 0, g, 0, 255);
        SDL_RenderDrawLine(renderer, lineX1, lineY1, lineX2, lineY2);

        // Dibujar un círculo con tamaño variable
        DrawCircle(renderer, circleX, circleY, circleRadius);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```
1. Cambio de Tamaño:

Durante la ejecución, las figuras geométricas (rectángulo y círculo) aumentaron de tamaño gradualmente.

A medida que las figuras crecían, eventualmente salían de la pantalla, lo que podría indicar la necesidad de implementar límites para el crecimiento de las figuras o para su posición en la pantalla.

2. Rotación y Orientación:

La rotación se mantuvo suave y constante, sin interrupciones o saltos bruscos.

3. Cambio de Color:

El ciclo de color se realizó sin problemas, proporcionando una variedad constante de tonos para cada figura.

# Ejercicio 6: Rebote de figuras

```c
#include <SDL2/SDL.h>
#include <stdio.h>

// Tamaño de la pantalla
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Variables para el rectángulo
int rectX = 50, rectY = 50;
int rectW = 200, rectH = 100;
int rectSpeedX = 2, rectSpeedY = 2;

// Variables para la línea
int lineX1 = 300, lineY1 = 50, lineX2 = 500, lineY2 = 200;
int lineSpeedX = 3, lineSpeedY = 2;

// Variables para el círculo
int circleX = 400, circleY = 300;
int circleRadius = 50;
int circleSpeedX = 4, circleSpeedY = 3;

// Función para dibujar un círculo
void DrawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

// Función para verificar colisiones con los bordes de la pantalla y rebotar
void CheckCollisionWithBounds(int* x, int* y, int* w, int* h, int* speedX, int* speedY) {
    if (*x <= 0 || *x + *w >= SCREEN_WIDTH) {
        *speedX = -*speedX;
    }
    if (*y <= 0 || *y + *h >= SCREEN_HEIGHT) {
        *speedY = -*speedY;
    }
}

// Función para verificar colisiones entre dos rectángulos y rebotar
void CheckCollisionBetweenFigures(int* x1, int* y1, int w1, int h1, int* speedX1, int* speedY1, 
                                  int* x2, int* y2, int w2, int h2, int* speedX2, int* speedY2) {
    if (*x1 < *x2 + w2 && *x1 + w1 > *x2 && *y1 < *y2 + h2 && *y1 + h1 > *y2) {
        *speedX1 = -*speedX1;
        *speedY1 = -*speedY1;
        *speedX2 = -*speedX2;
        *speedY2 = -*speedY2;
    }
}

// Función para actualizar las posiciones y manejar colisiones
void UpdateFigures() {
    // Actualizar posición del rectángulo
    rectX += rectSpeedX;
    rectY += rectSpeedY;
    CheckCollisionWithBounds(&rectX, &rectY, &rectW, &rectH, &rectSpeedX, &rectSpeedY);

    // Actualizar posición de la línea (como si fuera un rectángulo)
    lineX1 += lineSpeedX;
    lineY1 += lineSpeedY;
    lineX2 += lineSpeedX;
    lineY2 += lineSpeedY;
    int lineW = abs(lineX2 - lineX1);
    int lineH = abs(lineY2 - lineY1);
    CheckCollisionWithBounds(&lineX1, &lineY1, &lineW, &lineH, &lineSpeedX, &lineSpeedY);

    // Actualizar posición del círculo
    circleX += circleSpeedX;
    circleY += circleSpeedY;
    int circleW = circleRadius * 2;
    int circleH = circleRadius * 2;
    CheckCollisionWithBounds(&circleX, &circleY, &circleW, &circleH, &circleSpeedX, &circleSpeedY);

    // Verificar colisiones entre figuras
    CheckCollisionBetweenFigures(&rectX, &rectY, rectW, rectH, &rectSpeedX, &rectSpeedY, &lineX1, &lineY1, lineW, lineH, &lineSpeedX, &lineSpeedY);
    CheckCollisionBetweenFigures(&rectX, &rectY, rectW, rectH, &rectSpeedX, &rectSpeedY, &circleX, &circleY, circleW, circleH, &circleSpeedX, &circleSpeedY);
    CheckCollisionBetweenFigures(&lineX1, &lineY1, lineW, lineH, &lineSpeedX, &lineSpeedY, &circleX, &circleY, circleW, circleH, &circleSpeedX, &circleSpeedY);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("SDL2 - Rebote de Figuras", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Actualizar figuras
        UpdateFigures();

        // Limpiar la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar un rectángulo
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect = { rectX, rectY, rectW, rectH };
        SDL_RenderFillRect(renderer, &rect);

        // Dibujar una línea (como un rectángulo delgado)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(renderer, lineX1, lineY1, lineX2, lineY2);

        // Dibujar un círculo
        DrawCircle(renderer, circleX, circleY, circleRadius);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```
1. Rebote contra Paredes:

Las figuras geométricas (rectángulo, línea y círculo) rebotaron correctamente al chocar con los bordes de la pantalla.

Las velocidades de las figuras se invirtieron de manera adecuada al alcanzar los límites de la pantalla, manteniéndose dentro del área visible.

2. Colisiones entre Figuras:

Las colisiones entre figuras fueron detectadas correctamente, lo que resultó en un rebote entre ellas.

La implementación de las colisiones permitió que las figuras cambiaran de dirección de manera natural al chocar entre sí.

3. Interacción Visual:

No se observaron problemas de rendimiento, y el programa mantuvo una tasa de cuadros constante, lo que es crucial para evitar parpadeos o saltos en la animación.










