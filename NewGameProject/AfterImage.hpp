#pragma once
#include <Siv3d.hpp>

struct Afterimage : IEffect
{
    TextureRegion m_texture;
    Vec2 m_pos;
    double m_fadeoutTime;

    Afterimage(const TextureRegion& texture, const Vec2& pos, double fadeoutTime = 1.0)
        : m_texture(texture), m_pos(pos), m_fadeoutTime(fadeoutTime)
    {
    }

    bool update(double t) override
    {
        m_texture.draw(m_pos, ColorF(0.2, 0.3, 0.5, 0.8 - t / m_fadeoutTime));
        return t < m_fadeoutTime;
    }
};
