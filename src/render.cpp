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
    // Clear the framebuffer
    clear();

    // Update animation variables
    angle += angleStep;
    centerX = static_cast<int>(SCREEN_WIDTH / 2 + radius * std::cos(angle));
    centerY = static_cast<int>(SCREEN_HEIGHT / 2 + radius * std::sin(angle));
    currentColor = Color(static_cast<uint8_t>((std::sin(angle) + 1.0) * 127.0),
                         static_cast<uint8_t>((std::cos(angle) + 1.0) * 127.0),
                         static_cast<uint8_t>((std::sin(angle + M_PI) + 1.0) * 127.0));

    // Draw the star with the updated center and radius
    drawStar(centerX, centerY, radius, renderer);

    // Render the framebuffer to the screen
    renderBuffer(renderer);
}