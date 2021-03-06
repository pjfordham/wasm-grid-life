#ifndef LIFE_FILE_H
#define LIFE_FILE_H

#include "support.hh"

struct Shape {
public:
   const char * const* figure;
   const char *name;
   int height;
   int width;
   constexpr Shape(const char *const * _figure, const char *_name, int _height, int _width ) :
      figure(_figure), name(_name), height(_height), width(_width) {}
};

constexpr int length(const char* str)
{
    return *str ? 1 + length(str + 1) : 0;
}

#define SubShape( NAME, ... )                                           \
   struct NAME : public Shape {                                         \
      static constexpr const char *shape[] = { __VA_ARGS__ };           \
      static constexpr const char *Name = #NAME;                        \
      constexpr NAME() :                                                \
         Shape( shape, Name,                                            \
                sizeof( shape ) / sizeof( *shape ),                     \
                length( shape[0] ) ) {                                  \
      }                                                                 \
   };

class GameOfLife {
public:

   static const int LIVE = 100;
   static const int DEAD = 0;

   GameOfLife(int HEIGHT, int WIDTH);
   void addShape( Shape shape, int x = -1 , int y = -1);
   void click( int x, int y );

   int getHeight() { return HEIGHT; }
   int getWidth() { return WIDTH; }

   void print();
   void update();
   void clear();
   int getContent( int x, int y);
   int getState( int state , int x , int y );
   void iterate(unsigned int iterations);
private:
   int HEIGHT;
   int WIDTH;
   Array2D<int> world;
   Array2D<int> otherWorld;
};

#endif
