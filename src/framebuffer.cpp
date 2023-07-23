#include <iostream>
#include <vector>
#include <cmath>
#include "framebuffer.h"
#include "SDL.h"

Color clearColor(0, 0, 0); // Color base o por defecto del framebuffer
Color currentColor(0, 0, 0);

std::vector<Color> framebuffer; // Vector unidimensional para representar el framebuffer
void setClearColor(Color newColor)
{
    clearColor = newColor;
}

void setCurrentColor(Color newColor)
{
    currentColor = newColor;
}

// Función para llenar el framebuffer con el clearColor
void clear()
{
    std::fill(framebuffer.begin(), framebuffer.end(), clearColor);
}

void stretch(size_t width, size_t height){
    framebuffer.resize(width * height);
}

void point(const Vertex2 &vertex, size_t width, size_t height)
{
    // Redondear las coordenadas a enteros
    int x = static_cast<int>(vertex.x);
    int y = static_cast<int>(vertex.y);

    // Verificar si las coordenadas están dentro del rango del framebuffer
    if (x >= 0 && x < static_cast<int>(width) && y >= 0 && y < static_cast<int>(height))
    {
        size_t index = y * width + x;
        framebuffer[index] = currentColor;
    }
}

void drawLine(int x0, int y0, int x1, int y1, size_t width, size_t height)
{
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        point(Vertex2(x0, y0), width, height);
        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}


void drawStar(int centerX, int centerY, int radius, SDL_Renderer* renderer)
{
    int spikes = 5; // Número de puntas de la estrella

    for (int i = 0; i < spikes * 2; i++)
    {
        double angleRad = M_PI / spikes + i * M_PI / spikes;
        int x1 = centerX + static_cast<int>(radius * std::cos(angleRad));
        int y1 = centerY - static_cast<int>(radius * std::sin(angleRad)); // Restamos el valor del seno

        angleRad += M_PI / spikes;
        int x2 = centerX + static_cast<int>(radius / 2.0 * std::cos(angleRad));
        int y2 = centerY - static_cast<int>(radius / 2.0 * std::sin(angleRad)); // Restamos el valor del seno

        drawLine(x2, y2, x1, y1, framebufferWidth, framebufferHeight);
    }
}
