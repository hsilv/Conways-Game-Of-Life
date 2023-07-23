#include <SDL.h>
#include <stdio.h>

// Dimensiones de la ventana
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Crear la ventana
    SDL_Window* window = SDL_CreateWindow(
        "Hello, SDL!",         // Título de la ventana
        SDL_WINDOWPOS_UNDEFINED,  // Posición x de la ventana (centro)
        SDL_WINDOWPOS_UNDEFINED,  // Posición y de la ventana (centro)
        SCREEN_WIDTH,             // Ancho de la ventana
        SCREEN_HEIGHT,            // Alto de la ventana
        SDL_WINDOW_SHOWN          // Mostrar la ventana
    );

    if (window == NULL) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Crear el renderer (contexto de dibujo)
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Color de fondo (blanco)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Limpiar la ventana con el color de fondo
    SDL_RenderClear(renderer);

    // Mensaje a mostrar
    const char* message = "Hello, SDL!";
    
    // Color del mensaje (negro)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Coordenadas del mensaje en la ventana (centrado)
    int x = (SCREEN_WIDTH - strlen(message) * 8) / 2;
    int y = (SCREEN_HEIGHT - 16) / 2;

    // Dibujar el mensaje en la ventana
    for (int i = 0; message[i] != '\0'; i++) {
        SDL_Rect srcRect = { (message[i] - 32) * 8, 0, 8, 16 };
        SDL_Rect destRect = { x + i * 8, y, 8, 16 };
        SDL_RenderFillRect(renderer, &destRect);
    }

    // Mostrar la ventana
    SDL_RenderPresent(renderer);

    // Esperar 3 segundos
    SDL_Delay(3000);

    // Liberar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
