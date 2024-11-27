#include <iostream>
#include <SDL.h>
#include "WindowRenderer.hpp"
#include "Texture_generator.hpp"
#include "Entities.hpp"

using namespace std;

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cerr << "IMG_Init Error" << IMG_GetError << std::endl;
        return 1;
    }

    // classes iniialization bing chilling
    RenderWindow screen("Project x", 480, 440);
    Entity player;

    generate_texture test;

    // Images
    SDL_Texture *ban = generate_texture::load_texture("res/gfx/lady.jpg");
    SDL_Texture *Sprite_Adventure = generate_texture::load_texture("res/gfx/Sprite_Adventure.png");

    // Holds the running window and anything
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
    bool running = true;
    int x = 0;
    int y = 0;
    int speed = 10;

    // player
    player.atr.x = player.atr.y = 100;
    player.atr.h = 64 * 2;
    player.atr.w = 64 * 3;

    player.addSprite(Sprite_Adventure, 11, {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2});
    player.nameSpriteFraming("Stand", 0, 4, 0, 0);

    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
            }
        }
        // FPS (35)
        const int frameDelay = 1000 / 40;
        int frameStart = SDL_GetTicks();

        player.update("Stand", 900);

        // Key strokes
        if (keyboard_state_array[SDL_SCANCODE_D])
        {
            x = x + speed;
            std::cout << "D" << std::endl;
        }
        if (keyboard_state_array[SDL_SCANCODE_A])
        {
            x = x - speed;
            std::cout << "A" << std::endl;
        }
        if (keyboard_state_array[SDL_SCANCODE_W])
        {
            y = y - speed;
            std::cout << "W" << std::endl;
        }
        if (keyboard_state_array[SDL_SCANCODE_S])
        {
            y = y + speed;
            std::cout << "S" << std::endl;
        }
        else
        {
        }
        if (keyboard_state_array[SDL_SCANCODE_T])
        {
        }

        // CLEARS THE SCREEN
        SDL_SetRenderDrawColor(RenderWindow::getRenderer(), 255, 255, 255, 255);
        screen.clear();

        // player
        player.render();

        // test.render(Sprite_Adventure, x, y);

        // BANNER
        // screen.render(ban, 0, 0);
        // test.render(ban, x, y);

        // PRESENTS SCREEN
        screen.present();

        // FPS LIMITER
        int frameTime = frameStart - SDL_GetTicks();
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    screen.clean();
    return 0;
}