#include "Game.h"  // 包含游戏类的头文件
#include <iostream>  // 包含输入输出流库，用于标准输入输出

sf::Font Game::font;
// 游戏类的构造函数，初始化游戏窗口、球、两个玩家的拍子、分数和字体
Game::Game()
    : window(sf::VideoMode(800, 600), "Ping Pong"),  // 创建800x600的窗口，标题为"Ping Pong"
      ball(10.0f, sf::Vector2f(400.0f, 300.0f)),  // 创建一个半径为10的球，初始位置在(400, 300)
      player1(sf::Vector2f(paddleWidth, paddleHeight), sf::Vector2f(50.0f, 300.0f)),  // 创建玩家1的拍子，初始位置在(50, 300)
      player2(sf::Vector2f(paddleWidth, paddleHeight), sf::Vector2f(750.0f, 300.0f)),  // 创建玩家2的拍子，初始位置在(750, 300)
      scorePlayer1(0), scorePlayer2(0) {  // 初始化玩家1和玩家2的分数为0
    // 加载字体文件，如果失败则输出错误信息并退出程序
    if (!font.loadFromFile("./assets/OpenSans-Italic-VariableFont_wdth,wght.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        exit(EXIT_FAILURE);
    }
    // 设置分数显示文本的字体、字符大小、颜色和位置
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(350.0f, 20.0f);

    // Debug
    debugPointPlayer1.setRadius(5.0f);  // 半径5
    debugPointPlayer1.setFillColor(sf::Color::Red);  // 红色
    debugPointPlayer1.setOrigin(5.0f, 5.0f);  // 中心对齐

    debugPointPlayer2.setRadius(5.0f);
    debugPointPlayer2.setFillColor(sf::Color::Red);
    debugPointPlayer2.setOrigin(5.0f, 5.0f);
    // Debug

    // 重置游戏状态
    resetGame();
}

// 游戏的主循环，负责处理事件、更新游戏状态和渲染画面
void Game::run() {
    sf::Clock clock;  // 创建一个时钟对象，用于计算帧时间

    while (window.isOpen()) {  // 只要窗口是打开的，就继续循环
        processEvents();  // 处理事件
        float deltaTime = clock.restart().asSeconds();  // 计算自上一帧以来的时间差
        update(deltaTime);  // 更新游戏状态
        render();  // 渲染画面
    }
}

// 处理窗口事件，如关闭窗口事件
void Game::processEvents() {
    sf::Event event;  // 创建一个事件对象
    while (window.pollEvent(event)) {  // 循环检查事件
        if (event.type == sf::Event::Closed) {  // 如果是关闭事件，则关闭窗口
            window.close();
        }
    }
}

// 更新游戏状态，包括球和拍子的位置，以及分数
void Game::update(float deltaTime) {
    ball.update(deltaTime, window.getSize());  // 更新球的位置

    player1.update(deltaTime, sf::Keyboard::W, sf::Keyboard::S, window.getSize());  // 更新玩家1的拍子位置
    player2.update(deltaTime, sf::Keyboard::Up, sf::Keyboard::Down, window.getSize());  // 更新玩家2的拍子位置

     // 更新红点的位置，显示拍子中心
    debugPointPlayer1.setPosition(player1.getShape().getPosition().x + paddleWidth / 2,
                                  player1.getShape().getPosition().y + paddleHeight / 2);
    debugPointPlayer2.setPosition(player2.getShape().getPosition().x + paddleWidth / 2,
                                  player2.getShape().getPosition().y + paddleHeight / 2);

    // 输出调试信息，显示拍子的位置
    // std::cout << "Player1 position: " << player1.getShape().getPosition().y << std::endl;
    // std::cout << "Player2 position: " << player2.getShape().getPosition().y << std::endl;
    // 检查球是否与拍子发生碰撞
    ball.checkCollisionWithPaddle(player1.getShape());
    ball.checkCollisionWithPaddle(player2.getShape());

    // 检查球是否出界，并更新分数
    if (ball.getPosition().x < 0) {
        scorePlayer2++;  // 球从左边出界，玩家2得分
        resetGame();  // 重置游戏
    } else if (ball.getPosition().x > window.getSize().x) {
        scorePlayer1++;  // 球从右边出界，玩家1得分
        resetGame();  // 重置游戏
    }

    // 更新分数显示文本
    scoreText.setString(std::to_string(scorePlayer1) + " - " + std::to_string(scorePlayer2));
}

// 渲染游戏画面，包括拍子、球和分数
void Game::render() {
    window.clear(sf::Color::Black);  // 清空窗口，使用黑色背景

    player1.render(window);  // 渲染玩家1的拍子
    player2.render(window);  // 渲染玩家2的拍子
    ball.render(window);  // 渲染球
    
    // 输出调试信息，显示拍子的边界
    std::cout << "Player1 bounds: " << player1.getShape().getGlobalBounds().left << ", " << player1.getShape().getGlobalBounds().top << std::endl;
    std::cout << "Player2 bounds: " << player2.getShape().getGlobalBounds().left << ", " << player2.getShape().getGlobalBounds().top << std::endl;
    window.draw(scoreText);  // 绘制分数文本

    window.display();  // 显示窗口内容
}

// 重置游戏状态，包括球的位置和拍子的位置
void Game::resetGame() {
    ball.reset(sf::Vector2f(400.0f, 300.0f), sf::Vector2f(300.0f, 300.0f));  // 重置球的位置和速度
}