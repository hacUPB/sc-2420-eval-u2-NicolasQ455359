# 1.Configuración:

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



