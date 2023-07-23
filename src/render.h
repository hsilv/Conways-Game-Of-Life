#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include "framebuffer.h" // Incluye framebuffer.h para poder usar sus declaraciones

/* const int SCREEN_WIDTH;
const int SCREEN_HEIGHT; */

// Declaración de la función renderBuffer
void renderBuffer(SDL_Renderer* renderer);
void render(SDL_Renderer* renderer);

#endif // RENDER_H