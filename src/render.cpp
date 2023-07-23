#include <SDL.h>
#include "framebuffer.h"
#include "render.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
double angle = 0.0;
int centerX = SCREEN_WIDTH / 2;
int centerY = SCREEN_HEIGHT / 2;
int radius = 100;
double angleStep = 0.01;

void renderBuffer(SDL_Renderer* renderer) {
    // Create a texture
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        framebufferWidth,
        framebufferHeight
    );

    // Update the texture with the pixel data from the framebuffer
    SDL_UpdateTexture(
        texture,
        NULL,
        framebuffer.data(),
        framebufferWidth * sizeof(Color)
    );

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}

void render(SDL_Renderer* renderer) {
    // Render the framebuffer to the screen
    renderBuffer(renderer);
}