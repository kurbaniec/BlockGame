//
// Created by kurbaniec on 06.06.2021.
//

#ifndef BLOCK_GAME_DRAWCOLOR_H
#define BLOCK_GAME_DRAWCOLOR_H


class DrawColor {
public:
    static void setColor(int color);
};

enum Color {
    EMPTY = 0,
    RED = 1,
    BLUE = 2,
};

const int Color_Count = 2;


#endif //BLOCK_GAME_DRAWCOLOR_H
