#include "Engine/GraphicsSystem.h"
#include "Engine/SDLSystem.h"
#include "Engine/sdl2include.h"
#include "Log/log.h"

#include <iostream>

GraphicsSystem *GraphicsSystem::m_instance = 0;

GraphicsSystem::GraphicsSystem() {}

GraphicsSystem::~GraphicsSystem() { m_instance = nullptr; }

GraphicsSystem *GraphicsSystem::GetInstance() {
  if (!m_instance)
    m_instance = new GraphicsSystem();
  return m_instance;
}

void GraphicsSystem::Draw(Image *img, Vector *position,
                          std::pair<int, int> sizes) {
  SDL_Rect dest;
  dest.w = sizes.first;
  dest.h = sizes.second;
  dest.x = position->m_x;
  dest.y = position->m_y;

  // SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), 0, 255, 0,
  //                        255);
  // SDL_RenderDrawRect(SDLSystem::GetInstance()->GetRenderer(), &dest);
  // SDL_RenderDrawLine(SDLSystem::GetInstance()->GetRenderer(), 0, 0, dest.x,
  //                    dest.y);

  int result;
  result = SDL_RenderCopyEx(SDLSystem::GetInstance()->GetRenderer(),
                            img->GetTexture(), img->GetRect(), &dest,
                            img->GetRotationAngle(), img->GetSDLPivot(),
                            img->GetSDLFlip());

  if (result < 0)
    ERROR(SDL_GetError());
}

void GraphicsSystem::DrawFrame(Image *img, Frame *frame, Vector *position) {
  SDL_Rect dest;
  dest.w = frame->GetRect()->w;
  dest.h = frame->GetRect()->h;
  dest.x = position->m_x;
  dest.y = position->m_y;

  // SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), 0, 255, 0,
  //                        255);
  // SDL_RenderDrawRect(SDLSystem::GetInstance()->GetRenderer(), &dest);
  // SDL_RenderDrawLine(SDLSystem::GetInstance()->GetRenderer(), 0, 0, dest.x,
  //                    dest.y);

  int result;
  result = SDL_RenderCopyEx(SDLSystem::GetInstance()->GetRenderer(),
                            img->GetTexture(), frame->GetRect(), &dest,
                            img->GetRotationAngle(), img->GetSDLPivot(),
                            img->GetSDLFlip());

  if (result < 0)
    ERROR(SDL_GetError());
}

void GraphicsSystem::DrawText(SDL_Texture *texture, SDL_Rect *destRect) {
  SDL_RenderCopy(SDLSystem::GetInstance()->GetRenderer(), texture, NULL,
                 destRect);
}

void GraphicsSystem::DrawPoint(Vector point) {
  int result = SDL_RenderDrawPoint(SDLSystem::GetInstance()->GetRenderer(),
                                   point.m_x, point.m_y);
  if (result) {
    SDL_ERROR("Drawing point error");
  }
}

void GraphicsSystem::DrawCircle(Vector &center, float radius) {
  SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), 255, 0, 0,
                         255);
  Vector point;
  for (int angle = 0; angle < 360; angle++) {
    point.m_x = center.m_x + cos(angle) * radius;
    point.m_y = center.m_y - sin(angle) * radius;
    int result = SDL_RenderDrawPoint(SDLSystem::GetInstance()->GetRenderer(),
                                     point.m_x, point.m_y);
    if (result < 0)
      ERROR(SDL_GetError());
  }
}
