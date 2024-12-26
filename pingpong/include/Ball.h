#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

/**
 * @class Ball
 * @brief 表示游戏中的球
 *        Represents the ball in the game.
 */
class Ball {
public:
    Ball(float radius, const sf::Vector2f& position);

    /**
     * @brief 更新球的位置
     *        Updates the ball's position
     * @param deltaTime 时间增量 / Time delta
     * @param windowSize 窗口大小 / Window size
     */
    void update(float deltaTime, const sf::Vector2u& windowSize);

    /**
     * @brief 重置球的位置和速度
     *        Resets the ball's position and velocity
     */
    void reset(const sf::Vector2f& newPosition, const sf::Vector2f& newVelocity);

    /**
     * @brief 检查与挡板的碰撞
     *        Checks collision with the paddle
     */
    void checkCollisionWithPaddle(const sf::RectangleShape& paddle);

    /**
     * @brief 绘制球
     *        Renders the ball
     */
    void render(sf::RenderWindow& window);

    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getVelocity() const;

private:
    sf::CircleShape shape; // 球的形状 / Shape of the ball
    sf::Vector2f velocity; // 球的速度 / Velocity of the ball
};

#endif // BALL_H