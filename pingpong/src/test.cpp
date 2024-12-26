// test.cpp

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"

void testBallAndPaddle()
{
    // 创建窗口
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ping Pong Test");

    // 创建测试对象
    Ball ball(10.f, sf::Vector2f(400.f, 300.f));  // 半径为10，初始位置为中心
    Paddle paddle(sf::Vector2f(30.f, 5.f), sf::Vector2f(375.f, 550.f));  // 宽30，高5，起始位置

    // 渲染与移动测试
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 更新游戏对象状态
        paddle.update(0.f, sf::Keyboard::Left, sf::Keyboard::Right, window.getSize());
        ball.update(0.f, window.getSize());

        // 渲染所有对象
        window.clear();
        ball.render(window);
        paddle.render(window);
        window.display();
    }
}

int test()
{
    // 调用测试函数
    testBallAndPaddle();

    return 0;
}
