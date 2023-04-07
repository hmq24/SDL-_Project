#pragma once
#include <SDL.h>

class Tetromino
{
public:
  enum Type { I, J, L, O, S, T, Z };
  Tetromino(Type);
  void draw(SDL_Renderer *);
  void move(int dx, int dy);
  void rotate();
  bool isBlock(int x, int y) const;
  int x() const;
  int y() const;
private:
  Type type;
  int x_;
  int y_;
  int angle;
};
