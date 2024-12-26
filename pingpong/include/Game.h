#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"

/**
 * @class Game
 * @brief 游戏主逻辑类
 *        Main game logic class
 */
class Game {
public:
    Game();
    void run(); // 开始游戏 / Start the game

private:
    void processEvents(); // 处理用户输入 / Handle user input
    void update(float deltaTime); // 更新游戏逻辑 / Update game logic
    void render(); // 渲染游戏 / Render the game
    void resetGame(); // 重置游戏 / Reset the game

private:
    sf::RenderWindow window; // 游戏窗口 / Game window
    Ball ball; // 球对象 / Ball object
    Paddle player1; // 玩家1的挡板 / Player 1's paddle
    Paddle player2; // 玩家2的挡板 / Player 2's paddle
    sf::CircleShape debugPointPlayer1;  // 用于显示 Player1 的位置
    sf::CircleShape debugPointPlayer2;  // 用于显示 Player2 的位置

    sf::Font font; // 字体 / Font
    sf::Text scoreText; // 分数显示 / Score display
    int scorePlayer1; // 玩家1得分 / Player 1 score
    int scorePlayer2; // 玩家2得分 / Player 2 score

    static constexpr float paddleWidth = 5.0f;  // 挡板宽度 / Paddle width
    static constexpr float paddleHeight = 30.0f; // 挡板高度 / Paddle height
};

#endif // GAME_H