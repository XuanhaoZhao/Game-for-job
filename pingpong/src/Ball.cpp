#include "Ball.h"

/**
 * @brief 构造函数
 *        Constructor
 */
Ball::Ball(float radius, const sf::Vector2f& position)
    : velocity(300.0f, 300.0f) { // 初始速度 / Initial velocity
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(radius, radius); // 设置中心点为圆心 / Set origin to the center
    shape.setPosition(position);
}

/**
 * @brief 更新球的位置
 *        Updates the ball's position
 */
void Ball::update(float deltaTime, const sf::Vector2u& windowSize) {
    shape.move(velocity * deltaTime);

    // 碰撞检测：上下边界 / Collision detection: top and bottom walls
    if (shape.getPosition().y - shape.getRadius() < 0 || 
        shape.getPosition().y + shape.getRadius() > windowSize.y) {
        velocity.y = -velocity.y; // 反转Y方向速度 / Reverse Y velocity
    }
}

/**
 * @brief 重置球的位置和速度
 *        Resets the ball's position and velocity
 */
void Ball::reset(const sf::Vector2f& newPosition, const sf::Vector2f& newVelocity) {
    shape.setPosition(newPosition);
    velocity = newVelocity;
}

/**
 * @brief 检查与挡板的碰撞
 *        Checks collision with the paddle
 */
void Ball::checkCollisionWithPaddle(const sf::RectangleShape& paddle) {
    if (shape.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
        velocity.x = -velocity.x; // 反转X方向速度 / Reverse X velocity
    }
}

/**
 * @brief 绘制球
 *        Renders the ball
 */
void Ball::render(sf::RenderWindow& window) {
    window.draw(shape);
}

const sf::Vector2f& Ball::getPosition() const {
    return shape.getPosition();
}

const sf::Vector2f& Ball::getVelocity() const {
    return velocity;
}