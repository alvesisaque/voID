/**
    @file CircleRenderer.cpp
    @brief Manage circles rendered in the game.
    @copyright MIT License.
*/
#include "Components/CircleRenderer.hpp"
#include "Log/log.hpp"


CircleRenderer::CircleRenderer(GameObject *owner, Vector offset, float radius)
                                                    : Component(owner, C_DRAW) {
    INFO("CircleRenderer - initializing");
    m_offset = offset;
    m_radius = radius;
    INFO("CircleRenderer - initialized");
}

/**
    @brief Update the position of the circle and draw it.
*/
void CircleRenderer::ComponentUpdate() {
    // Sets the positions the circle radius and color.
    int x = GetOwner()->GetPosition()->m_x + m_offset.m_x;
    int y = GetOwner()->GetPosition()->m_y + m_offset.m_y;
    auto center = Vector(x, y);
    GraphicsSystem::GetInstance()->DrawFillCircle(center, m_radius, m_red,
                                                  m_green, m_blue, m_alpha);
}

/**
    @brief Set the color of the circle rendered.
    @param[in] red Red color integer value. The range is from 0 to 255.
    @param[in] green Green color integer value. The range is from 0 to 255.
    @param[in] blue Blue color integer value. The range is from 0 to 255.
    @param[in] alpha Transparency integer value. The range is from 0 to 255, and
    the lower is the value, bigger is the transparency.
*/
void CircleRenderer::SetColor(int red, int green, int blue, int alpha) {
    // Sets the primary colors to use in the game.
    m_red = red;
    m_green = green;
    m_blue = blue;
    m_alpha = alpha;
}
