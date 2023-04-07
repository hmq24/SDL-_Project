#include "game.hpp"
#include <iostream>

Game::Game():
  tetromino{static_cast<Tetromino::Type>(rand() % 7)},
  moveTime(SDL_GetTicks())
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error("SDL_Init(SDL_INIT_VIDEO)");
    SDL_CreateWindowAndRenderer(360, 720, SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowTitle(window,"Tetris");
}

Game::~Game()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool Game::tick()
{
  SDL_Event e;
  if (SDL_WaitEventTimeout(&e, 250))
  {
    switch (e.type)
    {
    case SDL_KEYDOWN:
      {
        switch (e.key.keysym.sym)
        {
        case SDLK_DOWN:
          {
            Tetromino t = tetromino;
            t.move(0, 1);
            if (!well.isCollision(t))
              tetromino = t;
          }
          break;
        case SDLK_RIGHT:
          {
            Tetromino t = tetromino;
            t.move(1, 0);
            if (!well.isCollision(t))
              tetromino = t;
          }
          break;
        case SDLK_LEFT:
          {
            Tetromino t = tetromino;
            t.move(-1, 0);
            if (!well.isCollision(t))
              tetromino = t;
          }
          break;
        case SDLK_UP:
          {
            Tetromino t = tetromino;
            t.rotate();
            if (!well.isCollision(t))
              tetromino = t;
          }
          break;
        }
      }
      break;
    case SDL_QUIT:
      return false;
    }
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
  SDL_RenderClear(renderer);
  well.draw(renderer);
  tetromino.draw(renderer);

  if (SDL_GetTicks() > moveTime)
  {
    moveTime += 1000;
    Tetromino t = tetromino;
    t.move(0, 1);
    check(t);
  }
  SDL_RenderPresent(renderer);
  return true;
};

void Game::check(const Tetromino &t)
{
  if (well.isCollision(t))
  {
    well.unite(tetromino);
    tetromino = Tetromino{static_cast<Tetromino::Type>(rand() % 7)};//random shapes
    if (well.isCollision(tetromino))
    {
      well = Well();
    }
  }
  else
  {
    tetromino = t;
  }
}
