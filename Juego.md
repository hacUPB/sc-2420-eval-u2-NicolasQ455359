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

