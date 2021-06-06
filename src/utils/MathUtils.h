//
// Created by kurbaniec on 05.06.2021.
//

#ifndef BLOCK_GAME_MATHUTILS_H
#define BLOCK_GAME_MATHUTILS_H

#include <vector>

class MathUtils {
public:
    template<typename T>
    static void transpose(std::vector<std::vector<T> > &b);

    template<typename T>
    static std::vector<std::vector<T>> multiply(std::vector<std::vector<T>> &a, std::vector<std::vector<T>> &b);

    template<typename T>
    static std::vector<std::vector<T>> multiply(std::vector<std::vector<T>> &a, int scalar);

    template<typename T>
    static std::vector<std::vector<T>> rotationMatrix(int size);
};


#endif //BLOCK_GAME_MATHUTILS_H
