#include <Texture_generator.hpp>

SDL_Texture* generate_texture::load_texture(const char* filepath){
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(RenderWindow::getRenderer(), filepath);
    if (texture == nullptr){ std::cerr << "Could not load texture " << filepath << std::endl; return nullptr; } else { return texture; }
}

void generate_texture::render(SDL_Texture* texture, int x, int y, int w, int h){
    dest.w = w; dest.h = h;
    dest.x = x; dest.y = y;
    if (texture != nullptr){
        SDL_RenderCopy(RenderWindow::getRenderer(), texture, nullptr, &dest);
    } else {
        std::cerr << "Could not render texture " << std::endl; 
        SDL_SetRenderDrawColor(RenderWindow::getRenderer(), 255, 0, 0, 255);
        SDL_RenderFillRect(RenderWindow::getRenderer(), &dest);
    }
}

SDL_Rect& generate_texture::getRect(){
    return dest;
}

int generate_texture::getWidth(){
    return dest.w;
}

int generate_texture::getHeight(){
    return dest.h;
}

int generate_texture::getX(){
    return dest.x;
}

int generate_texture::getY(){
    return dest.y;
}