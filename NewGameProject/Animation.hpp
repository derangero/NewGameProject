#pragma once
# include <Siv3D.hpp>

class Animation
{
public:
    int width;
    int height;
    int pattern; // ‰¡8
    Texture texture;
    Animation(int width, int height, int pattern, Texture texture);
};