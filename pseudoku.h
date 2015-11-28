#ifndef PSEUDOKU_H
#define PSEUDOKU_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float real32;
typedef double real64;

typedef struct peers {
    uint32 row[9];
    uint32 col[9];
    uint32 box[9];
} peers;

typedef struct pos {
    uint32 vals[9];
    uint32 size;
} pos;

uint32* get_row(uint32*, uint32);
uint32* get_col(uint32*, uint32);
uint32* get_box(uint32*, uint32);
peers* get_peers(uint32*, uint32);
uint32 is_safe(uint32*, uint32, uint32);
pos* get_pos_vals(uint32*, uint32);
uint32 fill_grid(uint32*, uint32);
void copy_grid(uint32*, uint32*);
void init_grid(uint32*);
void print_grid(uint32*);

#endif

/*
  {1, 2, 3,----4, 5, 6,----7, 8, 9,
  .4, 5, 6,----7, 8, 9,----1, 2, 3,
  .7, 8, 9,----1, 2, 3,----4, 5, 6,
  |||||||||||||||||||||||||||||||||
  .2, 3, 4,----5, 6, 7,----8, 9, 1,
  .5, 6, 7,----8, 9, 1,----2, 3, 4,
  .8, 9, 1,----2, 3, 4,----5, 6, 7,
  |||||||||||||||||||||||||||||||||
  .3, 4, 5,----6, 7, 8,----9, 1, 2,
  .6, 7, 8,----9, 1, 2,----3, 4, 5,
  .9, 1, 2,----3, 4, 5,----6, 7, 8}
*/

/*
  {.0, .1, .2,---.3, .4, .5,---.6, .7, .8,
  ..9, 10, 11,---12, 13, 14,---15, 16, 17,
  .18, 19, 20,---21, 22, 23,---24, 25, 26,
  ||||||||||||||||||||||||||||||||||||||||
  .27, 28, 29,---30, 31, 32,---33, 34, 35,
  .36, 37, 38,---39, 40, 41,---42, 43, 44,
  .45, 46, 47,---48, 49, 50,---51, 52, 53,
  ||||||||||||||||||||||||||||||||||||||||
  .54, 55, 56,---57, 58, 59,---60, 61, 62,
  .63, 64, 65,---66, 67, 68,---69, 70, 71,
  .72, 73, 74,---75, 76, 77,---78, 79, 80}
*/
