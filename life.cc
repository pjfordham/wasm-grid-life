#include <emscripten/bind.h>

#include "life.hh"
#include <algorithm>

GameOfLife::GameOfLife(int _WIDTH, int _HEIGHT) :
   HEIGHT(_HEIGHT), WIDTH(_WIDTH), world(HEIGHT,WIDTH), otherWorld(HEIGHT,WIDTH) {
   clear();
}

void GameOfLife::clear() {
   for ( int y = 0; y < HEIGHT; y++ ) {
      for ( int x = 0; x < WIDTH; x++ ) {
         world[y][x] = DEAD;
      }
   }
}

void GameOfLife::click( int x, int y )
{
   if ( world[y][x] == LIVE ){
      world[y][x] = DEAD;
   } else {
      world[y][x] = LIVE;
   }
}

void GameOfLife::addShape( Shape shape, int x, int y )
{
   for ( int i = y; i - y < shape.height; i++ ) {
      for ( int j = x; j - x < shape.width; j++ ) {
         if ( i < HEIGHT && j < WIDTH ) {
            world[i][j] = shape.figure[ i - y ][j - x ] == 'X' ? LIVE : DEAD;
         }
      }
   }
}

void GameOfLife::print() {
   // for ( int i = 0; i < HEIGHT; i++ ) {
   //    for ( int j = 0; j < WIDTH; j++ ) {
   //       std::cout << world[i][j];
   //    }
   //    std::cout << std::endl;
   // }
   // for ( int i = 0; i < WIDTH; i++ ) {
   //    std::cout << '=';
   // }
   // std::cout << std::endl;
}

int GameOfLife::getContent(int x, int y) {
   return world[y][x];
}

int GameOfLife::getState( int state, int x, int y ) {
    int neighbors = 0;
    for ( int i = y - 1; i <= y + 1; i++ ) {
       for ( int j = x - 1; j <= x + 1; j++ ) {
          if ( i == y && j == x ) {
             continue;
          }
          if ( i > -1 && i < HEIGHT && j > -1 && j < WIDTH ) {
             if ( world[i][j] == LIVE ) {
                neighbors++;
             }
          }
       }
    }
    if (state == LIVE) {
       return ( neighbors > 1 && neighbors < 4 ) ? LIVE : std::max( 0, world[y][x]-1);
    }
    else {
       return ( neighbors == 3 ) ? LIVE : std::max(0, world[y][x]-1);
    }
}

void GameOfLife::iterate( unsigned int iterations ) {
   for ( int i = 0; i < iterations; i++ ) {
      for ( int y = 0; y < HEIGHT; y++ ) {
         for ( int x = 0; x < WIDTH; x++ ) {
            otherWorld[y][x] =
               GameOfLife::getState(world[y][x] , x , y);
         }
      }
      std::swap(world, otherWorld);
   }
}


// Binding code
EMSCRIPTEN_BINDINGS(my_class_example) {
   emscripten::class_<GameOfLife>("GameOfLife")
      .constructor<int,int>()
      .function("click", &GameOfLife::click)
      .function("clear", &GameOfLife::clear)
      .function("iterate", &GameOfLife::iterate)
      .function("getContent", &GameOfLife::getContent)
      .function("getState", &GameOfLife::getState)
      .function("getHeight", &GameOfLife::getHeight)
      .function("getWidth", &GameOfLife::getWidth)
      ;
}
