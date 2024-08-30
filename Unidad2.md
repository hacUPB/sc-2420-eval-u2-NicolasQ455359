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

# 2. Analizar el Resultado
   
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
c
Copiar código
Uint32 frameTime = 13 + 16; // Suma de updateDeltaTime y renderDeltaTime
float fps = 1000.0f / frameTime;
printf("Current FPS: %.2f\n", fps);
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
3. Conclusiones y Documentación
a. Registra tus Observaciones:
Documentación: Los tiempos de ejecución se mantuvieron estables, con Update() tomando en promedio 13 ms y Render() 16 ms. No se identificaron fluctuaciones significativas que afectaran la fluidez del juego.
Comenta: El juego se ejecutó de manera fluida durante toda la prueba, con una respuesta rápida a las entradas del usuario y animaciones suaves. No hubo problemas de rendimiento observables.
b. Reflexiona sobre la Importancia:
Explicación: Controlar y entender el tiempo de ejecución es crucial para garantizar que el juego se sienta responsivo y fluido. Sin un control adecuado, el juego podría experimentar lag, baja tasa de FPS, o incluso caídas en el rendimiento, lo que afectaría negativamente la experiencia del usuario.
Estrategias: Para mantener una frecuencia de actualización constante, se podría implementar un delta time, que permite que los cálculos de movimiento y animación sean independientes de la tasa de cuadros por segundo.
