#pragma once
#include <SDL.h>
#include "well.hpp"
#include "tetromino.hpp"

class Game
{
public:
  Game();
  ~Game();
  bool tick();
private:
  Game(const Game &);
  Game &operator=(const Game &);
  SDL_Window *window;
  SDL_Renderer *renderer;
  Well well;
  Tetromino tetromino;
  uint32_t moveTime;
  void check(const Tetromino &);
};
