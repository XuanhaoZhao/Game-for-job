#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

/**
 * @class Paddle
 * @brief 表示游戏中的挡板
 *        Represents the paddle in the game.
 */
class Paddle {
public:
    Paddle(const sf::Vector2f& size, const sf::Vector2f& position);

    /**
     * @brief 更新挡板的位置
     *        Updates the paddle's position
     * @param deltaTime 时间增量 / Time delta
     * @param upKey 挡板上移键 / Key for moving up
     * @param downKey 挡板下移键 / Key for moving down
     * @param windowSize 窗口大小 / Window size
     */
    void update(float deltaTime, const sf::Keyboard::Key upKey, const sf::Keyboard::Key downKey, const sf::Vector2u& windowSize);

    /**
     * @brief 绘制挡板
     *        Renders the paddle
     */
    void render(sf::RenderWindow& window);

    const sf::RectangleShape& getShape() const;

private:
    sf::RectangleShape shape; // 挡板的形状 / Shape of the paddle
    float speed; // 挡板的速度 / Speed of the paddle
};

#endif // PADDLE_H