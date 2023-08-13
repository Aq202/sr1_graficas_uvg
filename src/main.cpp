#include <SDL2/SDL.h>
#include "framebuffer.h"
#include "point.h"
#include "triangle.h"
#include "loadOBJ.h"
#include <iostream>
#include "setupVertexArray.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

std::vector<glm::vec4> modelVertex;

void printVertex(glm::vec4 vertex)
{
  SDL_Log("Vértice: (%f, %f, %f, %f)\n", vertex.x, vertex.y, vertex.z, vertex.w);
}


void renderBuffer(SDL_Renderer *renderer)
{
    // Create a texture
    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        FRAMEBUFFER_WIDTH,
        FRAMEBUFFER_HEIGHT);

    // Update the texture with the pixel data from the framebuffer
    SDL_UpdateTexture(
        texture,
        NULL,
        framebuffer,
        FRAMEBUFFER_WIDTH * sizeof(Color));

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}

float rotation = 0;
float pi = 3.1416;
void renderModel()
{   
    const int scaleConst = 30;
    glm::mat4 scale = glm::mat4(
        scaleConst, 0, 0, 0,
        0, scaleConst, 0, 0,
        0, 0, scaleConst, 0,
        0, 0, 0, 1
    );

    glm::mat4 translate = glm::mat4(
        1, 0, 0, 400,
        0, 1, 0, 400,
        0, 0, 1, 0,
        0, 0 ,0, 1
    );

    glm::mat4 ZRotate = glm::mat4(
        glm::cos(pi), -glm::sin(pi), 0.0f, 0.0f,
        glm::sin(pi), glm::cos(pi), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f ,0.0f, 1.0f
    );

    glm::mat4 YRotate = glm::mat4(
        glm::cos(rotation), 0.0f, glm::sin(rotation), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -glm::sin(rotation), 0.0f, glm::cos(rotation), 0.0f,
        0.0f, 0.0f ,0.0f, 1.0f
    );

    rotation+=0.01;

    for (int i = 0; i < modelVertex.size(); i += 3)
    {
        glm::vec4 a = modelVertex[i] * scale * YRotate * ZRotate * translate;
        glm::vec4 b = modelVertex[i + 1] * scale * YRotate * ZRotate * translate;
        glm::vec4 c = modelVertex[i + 2] * scale * YRotate * ZRotate * translate;

        triangle( a,b,c);
    }
}

void render(SDL_Renderer *renderer)
{

    clear();
    renderModel();
    // Render the framebuffer to the screen
    renderBuffer(renderer);
}

int main(int argc, char *argv[])
{

    std::vector<glm::vec3> vertices;
    std::vector<Face> faces;
    if (!loadOBJ("D:\\proyectosProgra\\graficas\\lab3\\nave_espacial.obj", vertices, faces))
    {
        return 0;
    }
    modelVertex = setupVertexArray(vertices, faces);
    
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        0);

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

        // Call our render function
        render(renderer);

        // Present the frame buffer to the screen
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}