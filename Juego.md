# 1. Configuración:

•	SDL_Init: Inicializa la biblioteca SDL para video.

•	SDL_CreateWindow: Crea una ventana con el título "Defiende la Fortaleza".

•	SDL_CreateRenderer: Crea un renderer para dibujar en la ventana.

```c
if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL no se pudo inicializar. Error SDL: %s\n", SDL_GetError());
    return false;
}

window = SDL_CreateWindow("Defiende la Fortaleza", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
if (window == NULL) {
    printf("No se pudo crear la ventana. Error SDL: %s\n", SDL_GetError());
    return false;
}

renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
if (renderer == NULL) {
    printf("No se pudo crear el renderer. Error SDL: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    return false;
}
```


# 2. Configuración de la fortaleza y los enemigos:

•	Fortaleza: Inicialmente se coloca en el centro de la pantalla con un tamaño de 40x40 píxeles.

•	Enemigos: Se colocan en los bordes de la pantalla y se mueven hacia la fortaleza.
```c
fortressX = SCREEN_WIDTH / 2;
fortressY = SCREEN_HEIGHT / 2;

void createEnemies() {
    for (int i = 0; i < 5; i++) {
        enemies[i].x = (i % 2 == 0) ? 0 : SCREEN_WIDTH;
        enemies[i].y = rand() % SCREEN_HEIGHT;
        enemies[i].size = 20;
        enemies[i].speed = 2 + rand() % 3;
    }
}
```

# 3. Movimiento de la Fortaleza:

•	Teclas W, A, S, D: Controlan el movimiento de la fortaleza. Las teclas W y S mueven la fortaleza hacia arriba y abajo, respectivamente, mientras que A y D mueven la fortaleza hacia la izquierda y derecha.
```C
void moveFortress(const Uint8* keystate) {
    if (keystate[SDL_SCANCODE_W]) {
        fortressY -= fortressSpeed;
        if (fortressY < fortressSize / 2) fortressY = fortressSize / 2;
    }
    if (keystate[SDL_SCANCODE_S]) {
        fortressY += fortressSpeed;
        if (fortressY > SCREEN_HEIGHT - fortressSize / 2) fortressY = SCREEN_HEIGHT - fortressSize / 2;
    }
    if (keystate[SDL_SCANCODE_A]) {
        fortressX -= fortressSpeed;
        if (fortressX < fortressSize / 2) fortressX = fortressSize / 2;
    }
    if (keystate[SDL_SCANCODE_D]) {
        fortressX += fortressSpeed;
        if (fortressX > SCREEN_WIDTH - fortressSize / 2) fortressX = SCREEN_WIDTH - fortressSize / 2;
    }
}
```

# 4. Disparo:

•	Disparo con el ratón: Al hacer clic con el botón izquierdo, se dispara un proyectil desde la fortaleza hacia la dirección del cursor del ratón.
```c
void shootBullet(int mouseX, int mouseY) {
    bulletX = fortressX;
    bulletY = fortressY;

    double deltaX = mouseX - bulletX;
    double deltaY = mouseY - bulletY;
    double length = sqrt(deltaX * deltaX + deltaY * deltaY);
    bulletDirX = deltaX / length;
    bulletDirY = deltaY / length;
    isShooting = true;
}
```

# 5. Actualización y Dibujo:
   
•	Actualización: Actualiza las posiciones de la fortaleza, los enemigos y los proyectiles en cada frame.

•	Dibujo: Dibuja la fortaleza, los enemigos y los proyectiles en la pantalla.
```c
// Actualiza la posición del proyectil
void updateBullet() {
    if (isShooting) {
        bulletX += (int)(bulletDirX * bulletSpeed);
        bulletY += (int)(bulletDirY * bulletSpeed);

        if (bulletX < 0 || bulletX > SCREEN_WIDTH || bulletY < 0 || bulletY > SCREEN_HEIGHT) {
            isShooting = false;
        }
    }
}

// Dibuja los elementos en pantalla
void drawFortress() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect fortressRect = {fortressX - fortressSize / 2, fortressY - fortressSize / 2, fortressSize, fortressSize};
    SDL_RenderFillRect(renderer, &fortressRect);
}

void drawBullet() {
    if (isShooting) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect bulletRect = {bulletX - 5, bulletY - 5, 10, 10};
        SDL_RenderFillRect(renderer, &bulletRect);
    }
}

void drawEnemies() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < 5; i++) {
        SDL_Rect enemyRect = {enemies[i].x - enemies[i].size / 2, enemies[i].y - enemies[i].size / 2, enemies[i].size, enemies[i].size};
        SDL_RenderFillRect(renderer, &enemyRect);
    }
}
```

# 6. Bucle Principal:

•	Manejo de eventos: Utiliza SDL_PollEvent para manejar eventos de teclado y mouse.

•	Actualización y renderizado: Llama a funciones de actualización y renderizado en cada iteración del bucle.
```c
while (!quit) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            shootBullet(e.button.x, e.button.y);
        }
    }

    moveFortress(keystate);
    updateEnemies();
    updateBullet();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    drawFortress();
    drawEnemies();
    drawBullet();

    SDL_RenderPresent(renderer);

    SDL_Delay(16);  // Aproximadamente 60 FPS
}
```





