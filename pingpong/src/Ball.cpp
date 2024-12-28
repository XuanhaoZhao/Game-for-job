#include "Ball.h"
#include <cmath> // 用于三角函数计算

/**
 * @brief 构造函数
 *        Constructor
 */
Ball::Ball(float radius, const sf::Vector2f& position)
    : velocity(300.0f, 300.0f), collisionCooldown(0.2f), cooldownTimer(0.0f) { // 初始速度 / Initial velocity
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
        // 计算相对碰撞位置
        float relativeIntersectY = (paddle.getPosition().y + paddle.getSize().y / 2) - shape.getPosition().y;
        float normalizedRelativeIntersectionY = relativeIntersectY / (paddle.getSize().y / 2);

        // 最大反弹角度（75度）
        float maxBounceAngle = 5 * 3.141592653 / 12;
        float bounceAngle = normalizedRelativeIntersectionY * maxBounceAngle;

        // 更新速度向量
        float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        velocity.x = speed * std::cos(bounceAngle);
        velocity.y = speed * -std::sin(bounceAngle);
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