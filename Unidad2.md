### 1. Identificación de Funciones:
Setup(): Se encarga de inicializar recursos, configurar el entorno y realizar preparaciones antes de que el juego comience a ejecutarse.

Update(): Es responsable de actualizar la lógica del juego en cada iteración del loop. Aquí se manejan las entradas del usuario, la física, y las interacciones entre objetos.

Render(): Dibuja los gráficos en la pantalla. Se encarga de la representación visual del juego, actualizando la pantalla con los últimos cambios.

### 2. Inserta un printf():
Se añade un printf() en cada función para observar el orden en que se ejecutan. Por ejemplo:

```c
Copiar código
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
### 3. Ejecución del Programa:

Se ejecuta el programa y se observa cómo las funciones se llaman repetidamente. Esto te mostrará el ciclo continuo del Game Loop, donde Setup() se ejecuta al inicio, y luego Update() y Render() se llaman en cada iteración del loop.
