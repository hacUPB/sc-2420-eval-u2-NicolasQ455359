# Juego SDL2 

Este juego consiste en un personaje que debe sobrevivir y derrotar a un grupo de enemigos. El jugador puede moverse utilizando las teclas W, A, S, y D, mientras dispara hacia los enemigos con el clic izquierdo del mouse. Los disparos se dirigen hacia la posición del mouse en el momento del clic y así apuntar en cualquier dirección.

## Variables Globales:

SCREEN_WIDTH y SCREEN_HEIGHT: Establecen el tamaño de la pantalla.

playerSpeed: Controla la velocidad de movimiento del jugador.

playerX y playerY: Coordenadas del jugador en la pantalla.

isShooting: Es una variable booleana que indica si el jugador está disparando o no. Indica si el jugador está disparando.

bulletX, bulletY: Coordenadas del disparo.

bulletDirX, bulletDirY: Dirección en la que se mueve el disparo.

bulletSpeed: Velocidad del disparo.

enemyX[] y enemyY[]: Coordenadas de los enemigos.

enemyAlive[]: Indica si un enemigo está vivo.

enemyHitCount[]: Cuenta cuántos impactos ha recibido cada enemigo.

enemiesLeft: Cantidad de enemigos que quedan vivos.

## Función ResetGame()

Tuve que añadir esta función para que el juego se reinicie cada vez que un enemigo colisiona con el personaje, colocando al jugador en el centro de la pantalla y a los enemigos en las esquinas de la ventana. También restablece la vida de los enemigos y el estado del disparo.
```c
void ResetGame() {
    playerX = SCREEN_WIDTH / 2 - 25;
    playerY = SCREEN_HEIGHT / 2 - 25;

    enemyX[0] = 0; enemyY[0] = 0;
    enemyX[1] = SCREEN_WIDTH - 50; enemyY[1] = 0;
    enemyX[2] = 0; enemyY[2] = SCREEN_HEIGHT - 50;
    enemyX[3] = SCREEN_WIDTH - 50; enemyY[3] = SCREEN_HEIGHT - 50;

    for (int i = 0; i < 4; i++) {
        enemyAlive[i] = true;
        enemyHitCount[i] = 0;
    }
    enemiesLeft = 4;
    isShooting = false;
}
```
## Función Update()
```c
void Update() {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_W] && playerY > 0) playerY -= playerSpeed;
    if (keystate[SDL_SCANCODE_S] && playerY < SCREEN_HEIGHT - 50) playerY += playerSpeed;
    if (keystate[SDL_SCANCODE_A] && playerX > 0) playerX -= playerSpeed;
    if (keystate[SDL_SCANCODE_D] && playerX < SCREEN_WIDTH - 50) playerX += playerSpeed;
```
Esta parte del código maneja el movimiento del jugador con las teclas W, A, S y D. El jugador se mueve dentro de los límites de la pantalla.

```c
    if (isShooting) {
        bulletX += bulletDirX * bulletSpeed;
        bulletY += bulletDirY * bulletSpeed;

        if (bulletX < 0 || bulletX > SCREEN_WIDTH || bulletY < 0 || bulletY > SCREEN_HEIGHT) {
            isShooting = false;
        }

        for (int i = 0; i < 4; i++) {
            if (enemyAlive[i] && bulletX >= enemyX[i] && bulletX <= enemyX[i] + 50 &&
                bulletY >= enemyY[i] && bulletY <= enemyY[i] + 50) {
                enemyHitCount[i]++;
                isShooting = false;
                if (enemyHitCount[i] >= 3) {
                    enemyAlive[i] = false;
                    enemiesLeft--;
                }
            }
        }
    }
```
Manejo del disparo: Si el jugador está disparando, las coordenadas del disparo (bulletX, bulletY) se actualizan con base en la dirección calculada (bulletDirX, bulletDirY).

Si el disparo sale de los límites de la pantalla, se desactiva (isShooting = false).

Si el disparo impacta a un enemigo, se incrementa el contador de golpes (enemyHitCount[i]). Si el enemigo ha sido golpeado 3 veces, muere (enemyAlive[i] = false).

```c
    if (enemiesLeft <= 0) {
        printf("¡Has derrotado a todos los enemigos!\n");
        ResetGame();
    }
```
Si el jugador mata a todos los enemigos, el juego se reinicia.
```c
    for (int i = 0; i < 4; i++) {
        if (enemyAlive[i]) {
            if (enemyX[i] < playerX) enemyX[i] += 1;
            if (enemyX[i] > playerX) enemyX[i] -= 1;
            if (enemyY[i] < playerY) enemyY[i] += 1;
            if (enemyY[i] > playerY) enemyY[i] -= 1;

            if (abs(enemyX[i] - playerX) < 50 && abs(enemyY[i] - playerY) < 50) {
                printf("¡Un enemigo te ha alcanzado! El juego se reinicia.\n");
                ResetGame();
            }
        }
    }
}
```
Movimiento de los enemigos: Los enemigos se mueven hacia el jugador. Si un enemigo alcanza al jugador (colisión detectada con abs(enemyX[i] - playerX) < 50 y abs(enemyY[i] - playerY) < 50), el juego se reinicia.

## Función Render()
```c
void Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect player = { playerX, playerY, 50, 50 };
    SDL_RenderFillRect(renderer, &player);

    if (isShooting) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect bullet = { bulletX, bulletY, 10, 10 };
        SDL_RenderFillRect(renderer, &bullet);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < 4; i++) {
        if (enemyAlive[i]) {
            SDL_Rect enemy = { enemyX[i], enemyY[i], 50, 50 };
            SDL_RenderFillRect(renderer, &enemy);
        }
    }

    SDL_RenderPresent(renderer);
}
```
Renderizado de la pantalla: Esta función dibuja el jugador, los disparos y los enemigos en la pantalla.

Se utiliza SDL_SetRenderDrawColor() para establecer el color y SDL_RenderFillRect() para dibujar rectángulos que representan al jugador, los disparos y los enemigos.

## Función main()
```c
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL no pudo inicializarse. Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Juego de disparos", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("La ventana no pudo ser creada. Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("El renderizador no pudo ser creado. Error: %s\n", SDL_GetError());
        return 1;
    }

    ResetGame();

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && !isShooting) {
                isShooting = true;
                bulletX = playerX + 25;
                bulletY = playerY + 25;
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                float deltaX = mouseX - bulletX;
                float deltaY = mouseY - bulletY;
                float length = sqrt(deltaX * deltaX + deltaY * deltaY);
                bulletDirX = deltaX / length;
                bulletDirY = deltaY / length;
            }
        }

        Update();
        Render();
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```
La función main() inicializa SDL, crea la ventana y el renderizador, y maneja el bucle principal del juego. Dentro del bucle se procesan los eventos (como los clics del mouse para disparar), se actualiza el estado del juego con Update() y se dibuja la escena con Render().




