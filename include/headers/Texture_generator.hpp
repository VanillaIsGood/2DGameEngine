#pragma once
#include <iostream>
#include <cstdlib>
#include <SDL_image.h>
#include <SDL.h>
#include "WindowRenderer.hpp"

class generate_texture{
public:
    static SDL_Texture * load_texture(const char* filepath);

    void render(SDL_Texture*texture, int x = 0, int y = 0, int w = 50, int h = 50);
    SDL_Rect& getRect();
    int getWidth();
    int getHeight();
    int getX();
    int getY();
    
private:
    SDL_Rect dest;

};

