#include "Paddle.h"
#include <iostream>

/**
 * @brief 构造函数
 *        Constructor
 */
Paddle::Paddle(const sf::Vector2f& size, const sf::Vector2f& position)
    : speed(400.0f) { // 挡板移动速度 / Paddle movement speed
    shape.setSize(size);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(size.x / 2, size.y / 2); // 设置中心点 / Set origin
    shape.setPosition(position);
}

/**
 * @brief 更新挡板的位置
 *        Updates the paddle's position
 */
// void Paddle::update(float deltaTime, const sf::Keyboard::Key upKey, const sf::Keyboard::Key downKey, const sf::Vector2u& windowSize) {
//     if (sf::Keyboard::isKeyPressed(upKey) && shape.getPosition().y - shape.getSize().y / 2 > 0) {
//         shape.move(0, -speed * deltaTime); // 向上移动 / Move up
//     }
//     if (sf::Keyboard::isKeyPressed(downKey) && shape.getPosition().y + shape.getSize().y / 2 < windowSize.y) {
//         shape.move(0, speed * deltaTime); // 向下移动 / Move down
//     }
//     shape.setPosition(position);
// }
void Paddle::update(float deltaTime, const sf::Keyboard::Key upKey, const sf::Keyboard::Key downKey, const sf::Vector2u& windowSize) {
    sf::Vector2f shapePosition = shape.getPosition();
    if (sf::Keyboard::isKeyPressed(upKey) && shapePosition.y - shape.getSize().y / 2 > 0) { // [改动3] 防止越界逻辑更完善
        shape.move(0, -speed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(downKey) && shapePosition.y + shape.getSize().y / 2 < windowSize.y) {
        shape.move(0, speed * deltaTime);
    }
}

/**
 * @brief 绘制挡板
 *        Renders the paddle
 */
void Paddle::render(sf::RenderWindow& window) {
    std::cout << "Rendering paddle at position: " 
              << shape.getPosition().x << ", " 
              << shape.getPosition().y << std::endl;
    window.draw(shape);
}

const sf::RectangleShape& Paddle::getShape() const {
    return shape;
}