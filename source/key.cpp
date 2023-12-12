#include "../include/key.h"

#include <nds.h>

Key* init_keys()
{
    static Key keys[12];

    keys[0] = Key(KEY_X, 'X');
    keys[1] = Key(KEY_Y, 'Y');
    keys[2] = Key(KEY_B, 'B');
    keys[3] = Key(KEY_A, 'A');
    keys[4] = Key(KEY_UP, 'U');
    keys[5] = Key(KEY_DOWN, 'D');
    keys[6] = Key(KEY_LEFT, 'G');
    keys[7] = Key(KEY_RIGHT, 'Q');
    keys[8] = Key(KEY_L, 'L');
    keys[9] = Key(KEY_R, 'R');
    keys[10] = Key(KEY_START, 'S');
    keys[11] = Key(KEY_SELECT, 'E');

    return keys;
}