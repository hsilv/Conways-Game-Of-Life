#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "framebuffer.cpp"
#include "render.cpp"

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

    // Inicializar el framebuffer
    framebuffer.resize(framebufferWidth * framebufferHeight);
    clear(); // Llenar el framebuffer con el color de fondo

    // Establecer color actual y dibujar algunos puntos en el framebuffer
    setCurrentColor(Color(255, 0, 0)); // Color rojo
    point(Vertex2(100, 100), framebufferWidth, framebufferHeight);
    point(Vertex2(200, 200), framebufferWidth, framebufferHeight);
    setCurrentColor(Color(0, 255, 0)); // Color verde
    point(Vertex2(300, 300), framebufferWidth, framebufferHeight);
    setCurrentColor(Color(0, 0, 255)); // Color azul
    point(Vertex2(400, 400), framebufferWidth, framebufferHeight);

    // Renderizar el framebuffer en la ventana
    renderBuffer(renderer);

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
