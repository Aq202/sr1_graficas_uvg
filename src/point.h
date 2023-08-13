#pragma once
#include "color.h"
#include "framebuffer.h"

void setCurrentColor(const Color color)
{
    currentColor = color;
}

void point(const int x, const int y)
{
    int index = y * FRAMEBUFFER_WIDTH + x;

    // Verificar si el índice está dentro de la pantalla
    if (index >= 0 && index < FRAMEBUFFER_SIZE)
    {
        // Colocar color del pixel (x,y)
        framebuffer[index] = currentColor;
    }
}