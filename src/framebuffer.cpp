#include <iostream>
#include <vector>
#include "framebuffer.h"

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