#include "Engine/Image.h"

Image::Image() {}

Image::Image(std::string path, int x, int y, int width, int height)
{
    LoadImage(path, x, y, width, height);
}

void Image::LoadImage(std::string path, int x, int y, int _width, int _height)
{
    SDL_Surface *surface = IMG_Load(path.c_str());

    if (!surface)
    {
        ERROR(IMG_GetError());
        exit(1);
    }

    m_texture = SDL_CreateTextureFromSurface(SDLSystem::GetInstance()->GetRenderer(),
                                             surface);

    if (!m_texture)
    {
        ERROR(SDL_GetError());
        exit(1);
    }

    SDL_FreeSurface(surface);

    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = _width;
    m_rectangle.h = _height;

    width = _width;
    height = _height;
}

SDL_Texture *Image::GetTexture()
{
    return m_texture;
}

SDL_Rect *Image::GetRect()
{
    return &m_rectangle;
}