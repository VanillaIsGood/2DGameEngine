#include "Entities.hpp"
#include "Texture_generator.hpp"
#include "WindowRenderer.hpp"
#include <SDL.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  if (!(IMG_Init(IMG_INIT_PNG))) {
    std::cerr << "IMG_Init Error" << IMG_GetError << std::endl;
    return 1;
  }

  // classes iniialization bing chilling
  RenderWindow screen("Project x", 580, 580);
  Entity player;

  generate_texture test;

  // Images
  SDL_Texture *ban = generate_texture::load_texture("res/gfx/lady.jpg");
  SDL_Texture *Sprite_Adventure =
      generate_texture::load_texture("res/gfx/Sprite_Adventure.png");

  // Holds the running window and anything
  const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
  bool running = true;

  // player
  player.atr.x = player.atr.y = 100;
  player.atr.h = 64 * 2;
  player.atr.w = 64 * 3;

  player.addSprite(Sprite_Adventure, 11, {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2});
  player.nameSpriteFraming("Stand", 0, 3, 0, 0);
  player.nameSpriteFraming("Run", 1, 6, 1, 1);
  player.nameSpriteFraming("Sit", 4, 0, 0, 1);
  int AnimationCycle = 100;

  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
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
    // Key strokes
    if (keyboard_state_array[SDL_SCANCODE_D]) {
      player.update("Run", AnimationCycle);
      player.atr.x += 1;
    }
    if (keyboard_state_array[SDL_SCANCODE_A]) {
      std::cout << "A" << std::endl;
    }
    if (keyboard_state_array[SDL_SCANCODE_W]) {

      std::cout << "W" << std::endl;
    }
    if (keyboard_state_array[SDL_SCANCODE_S]) {
      player.update("Sit", AnimationCycle);
      std::cout << "S" << std::endl;

    } else {
      player.update("Stand", AnimationCycle);
    }
    if (keyboard_state_array[SDL_SCANCODE_T]) {
    }

    // CLEARS THE SCREEN
    SDL_SetRenderDrawColor(RenderWindow::getRenderer(), 255, 255, 255, 255);
    screen.clear();

    // player
    player.render();

    // PRESENTS SCREEN
    screen.present();

    // FPS LIMITER
    int frameTime = frameStart - SDL_GetTicks();
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }
  screen.clean();
  return 0;
}