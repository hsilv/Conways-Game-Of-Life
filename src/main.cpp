#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include "framebuffer.h"
#include "render.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 5; // Tamaño de cada célula en píxeles

// Dimensiones del grid del juego
const int GRID_WIDTH = SCREEN_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;

// Función para obtener el índice de una célula en el grid
// Función para obtener el índice de una célula en el grid
int getIndex(int x, int y)
{
    return y * GRID_WIDTH + x;
}

// Función para obtener el estado de una célula (viva o muerta) en una posición del grid
bool getCellState(const std::vector<bool>& grid, int x, int y)
{
    int index = getIndex(x, y);
    if (index >= 0 && index < grid.size())
    {
        return grid[index];
    }
    return false;
}

// Función para establecer el estado de una célula en una posición del grid
void setCellState(std::vector<bool>& grid, int x, int y, bool state)
{
    int index = getIndex(x, y);
    if (index >= 0 && index < grid.size())
    {
        grid[index] = state;
    }
}

// Función para contar la cantidad de células vecinas vivas de una célula en una posición del grid
int countAliveNeighbors(const std::vector<bool>& grid, int x, int y)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue; // La célula en sí misma no cuenta como vecina
            if (getCellState(grid, x + i, y + j))
                count++;
        }
    }
    return count;
}

// Función para actualizar el estado del grid según las reglas del "Game of Life"
void updateGrid(std::vector<bool>& grid)
{
    std::vector<bool> newGrid = grid; // Creamos una copia del grid actual para almacenar el próximo estado

    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            int neighbors = countAliveNeighbors(grid, x, y);
            bool currentState = getCellState(grid, x, y);
            bool nextState = false;

            // Aplicar las reglas del "Game of Life"
            if (currentState)
            {
                if (neighbors < 2 || neighbors > 3)
                {
                    nextState = false; // Muere por falta de vecinos o por sobrepoblación
                }
                else
                {
                    nextState = true; // Sobrevive si tiene 2 o 3 vecinos vivos
                }
            }
            else
            {
                if (neighbors == 3)
                {
                    nextState = true; // Revive si tiene exactamente 3 vecinos vivos
                }
            }

            newGrid[getIndex(x, y)] = nextState; // Actualizamos el estado de la célula en la nueva copia
        }
    }

    grid = newGrid; // Copiamos el grid actualizado de vuelta al grid original
}

// Función para establecer un patrón inicial de "Glider Gun" en el grid
void setGosperGliderGunPattern(std::vector<bool>& grid, int x, int y)
{
    std::vector<std::string> gliderGunPattern = {
        "........................O",
        "......................O.O",
        "............OO......OO............OO",
        "...........O...O....OO............OO",
        "OO........O.....O...OO",
        "OO........O...O.OO....O.O",
        "..........O.....O.......O",
        "...........O...O",
        "............OO"
    };

    for (int yy = 0; yy < gliderGunPattern.size(); yy++)
    {
        for (int xx = 0; xx < gliderGunPattern[yy].size(); xx++)
        {
            if (gliderGunPattern[yy][xx] == 'O')
            {
                setCellState(grid, x + xx, y + yy, true);
            }
        }
    }
}

void setPufferTypeBreederPattern(std::vector<bool>& grid, int x, int y)
{
    std::vector<std::string> breederPattern = {
        "OOO...O..O..O...OOO",
        "O..O..O..O..O..O..O",
        ".O.O..O..O..O..O.O.",
        "O...O..O..O..O...O",
        "..................."
    };

    for (int yy = 0; yy < breederPattern.size(); yy++)
    {
        for (int xx = 0; xx < breederPattern[yy].size(); xx++)
        {
            if (breederPattern[yy][xx] == 'O')
            {
                setCellState(grid, x + xx, y + yy, true);
            }
        }
    }
}

int main(int argc, char *args[])
{
  // Inicializar SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Error al inicializar SDL: %s\n", SDL_GetError());
    return 1;
  }

  // Crear la ventana
  SDL_Window *window = SDL_CreateWindow(
      "Conway's Game Of Life",          // Título de la ventana
      SDL_WINDOWPOS_UNDEFINED, // Posición x de la ventana (centro)
      SDL_WINDOWPOS_UNDEFINED, // Posición y de la ventana (centro)
      SCREEN_WIDTH,            // Ancho de la ventana
      SCREEN_HEIGHT,           // Alto de la ventana
      SDL_WINDOW_SHOWN         // Mostrar la ventana
  );

  if (window == NULL)
  {
    printf("Error al crear la ventana: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Crear el renderer (contexto de dibujo)
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
  {
    printf("Error al crear el renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Inicializar el framebuffer
  framebuffer.resize(framebufferWidth * framebufferHeight);
  clear(); // Llenar el framebuffer con el color de fondo

  // Centrar el grid de células en la pantalla
  int gridOffsetX = (SCREEN_WIDTH - GRID_WIDTH * CELL_SIZE) / 2;
  int gridOffsetY = (SCREEN_HEIGHT - GRID_HEIGHT * CELL_SIZE) / 2;

  // Crear el grid de células del "Game of Life"
  // Crear el grid del "Game of Life" y establecer los patrones iniciales
    std::vector<bool> grid(GRID_WIDTH * GRID_HEIGHT, false);
    setGosperGliderGunPattern(grid, GRID_WIDTH / 4, GRID_HEIGHT / 4);
    setGosperGliderGunPattern(grid, GRID_WIDTH * 3 / 4 - 36, GRID_HEIGHT / 4);
    setPufferTypeBreederPattern(grid, GRID_WIDTH / 2 - 5, GRID_HEIGHT * 3 / 4 - 2);

  bool running = true;
  SDL_Event event;

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
    }

    // Actualizar el grid según las reglas del "Game of Life"
    updateGrid(grid);

    // Renderizar el grid en el framebuffer
    clear(); // Limpiar el framebuffer

    for (int y = 0; y < GRID_HEIGHT; y++)
    {
      for (int x = 0; x < GRID_WIDTH; x++)
      {
        if (getCellState(grid, x, y))
        {
          // Si la célula está viva, dibujarla de color blanco
          setCurrentColor(Color(255, 255, 255));
        }
        else
        {
          // Si la célula está muerta, dibujarla de color negro
          setCurrentColor(Color(0, 0, 0));
        }

        // Dibujar la célula en el framebuffer
        int pixelX = x * CELL_SIZE;
        int pixelY = y * CELL_SIZE;
        for (int dy = 0; dy < CELL_SIZE; dy++)
        {
          for (int dx = 0; dx < CELL_SIZE; dx++)
          {
            point(Vertex2(pixelX + dx, pixelY + dy), framebufferWidth, framebufferHeight);
          }
        }
      }
    }

    // Call our render function
    render(renderer);

    // Present the frame buffer to the screen
    SDL_RenderPresent(renderer);

    // Delay to limit the frame rate
    SDL_Delay(1000 / 144); // 10 frames per second
  }

  // Liberar recursos
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}