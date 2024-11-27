#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "WindowRenderer.hpp"

class Entity
{
public:
    SDL_Rect atr;
    int health = 100;
    int speed = 5;
    void addSprite(SDL_Texture *sprite, int columns, const std::vector<int> &Arr);
    void nameSpriteFraming(std::string name, int FrameStart, int FrameEnd, int columnStart, int columnEnd);
    void update(const std::string &Animation_Name, int Interval = 500);
    void render();

private:
    // Sprite information
    struct Struc_TEXTURE
    {
        int columns;
        int texture_width, texture_height;
        SDL_Texture *texture;
        std::vector<int> frameArr;
    };
    // All SpriteSheets
    std::vector<Struc_TEXTURE> SpriteSheets;
    // A container for frames of each column
    std::map<std::string, std::vector<int>> AnimationDict;
    // The magnifying glass
    SDL_Rect EntRect;
    std::string name;
    int current_frame = 0;

    bool executed = false;
};