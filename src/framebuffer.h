#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>
#include <iostream>
#include "vertex2.h"
#include "color.h"
#include "SDL.h"

extern Color clearColor;
extern Color currentColor;
extern std::vector<Color> framebuffer;
const size_t framebufferWidth = 800;
const size_t framebufferHeight = 600;

void clear();
void point(const Vertex2& vertex, size_t width, size_t height);
void setClearColor(Color newColor);
void setCurrentColor(Color newColor);
void stretch(size_t width, size_t height);
void drawStar(int centerX, int centerY, int radius, SDL_Renderer* renderer);

#endif  // FRAMEBUFFER_H