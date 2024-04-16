#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Ball.h"
#include <cmath>
#include <vector>
#include <sstream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(950, 900), "Arcanoid");
    srand(time(0));
    window.setFramerateLimit(60);
    std::vector<sf::RectangleShape> plitki(100);
    int nPlitok = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10;j++)
        {
            plitki[nPlitok].setFillColor(sf::Color::Blue);
            plitki[nPlitok].setSize(sf::Vector2f(70, 30));
            plitki[nPlitok].setOutlineThickness(2);
            plitki[nPlitok].setPosition(74*i+120, 34*j+120);
            nPlitok++;
        }
    }

    
    Player player;
    Ball ball;
    sf::Clock clock;
    sf::Font font;
    
    if (!font.loadFromFile("Silkscreen.ttf")) exit(EXIT_FAILURE);
    
    sf::Text start("Press Left Mouse Button \n\n\t\t  to start",font,35);
    start.setPosition(217, 500);
    
    sf::Text gameOvertxt("Game over", font, 75);
    gameOvertxt.setFillColor(sf::Color::Red);
    gameOvertxt.setPosition(250, 300);
    
    sf::Text continuetxt("Restart", font, 50);
    continuetxt.setPosition(350,450);

    sf::Text exittxt("Exit", font, 50);
    exittxt.setPosition(415,525);
    
    sf::Text scoretxt;
    scoretxt.setFont(font);
    scoretxt.setCharacterSize(30);
    scoretxt.setFillColor(sf::Color::White);
    scoretxt.setPosition(740, 30);
    
    sf::Text levelCompletetxt("Level complete!",font,75);
    levelCompletetxt.setPosition(150,300);
    levelCompletetxt.setFillColor(sf::Color::Green);

    float speedPlayer = 800.f;
    float speedBallX = 6.f;
    float speedBallY = -9.f;
    bool gameStarted = false;
    bool gameOver = false;
    int score= 0;
    bool levelComplete=0;
    

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();
        while (window.pollEvent(event))
        {
            if (gameStarted==false)
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left && gameStarted == false)
                    {
                        ball.setSpeed(speedBallX, speedBallY);
                        gameStarted = true;
                    }
                    break;
                default:
                    break;
                }
            }
            else 
            { 
                switch (event.type)
                {

                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) player.setSpeed(-dt * speedPlayer);
                        if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) player.setSpeed(dt * speedPlayer);
                        break;
                    case sf::Event::KeyReleased:
                        if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) player.setSpeed(0);
                        if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) player.setSpeed(0);
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            if (continuetxt.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                            {
                                gameOver = false;
                                gameStarted = false;
                                levelComplete = false;
                                ball.setPosition(460,770);
                                player.setPosition(400,800);
                                ball.setSpeed(0, 0);
                                nPlitok = 0;
                                score = 0;
                                std::ostringstream scoreStr;
                                scoretxt.setString(scoreStr.str());
                                for (int i = 0; i < 10; i++)
                                {
                                    for (int j = 0; j < 10; j++)
                                    {  
                                        plitki[nPlitok].setPosition(74 * i + 120, 34 * j + 120);
                                        nPlitok++;
                                    }
                                }
                            }
                            if (exittxt.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                            {
                                window.close();
                            }
                        }
                    case sf::Event::MouseMoved:
                        if (exittxt.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        {
                            exittxt.setFillColor(sf::Color::White);
                        }
                        else
                        {
                            if(gameOver) exittxt.setFillColor(sf::Color::Red);
                            if (levelComplete) exittxt.setFillColor(sf::Color::Green);
                        }
                        if (continuetxt.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        {
                            continuetxt.setFillColor(sf::Color::White);
                        }
                        else
                        {
                            if (gameOver) continuetxt.setFillColor(sf::Color::Red);
                            if (levelComplete) continuetxt.setFillColor(sf::Color::Green);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        
        player.move();
        if (player.getPosition().getPosition().x > window.getSize().x-150)
        {
            player.setPosition(window.getSize().x - 150, 800);
            player.setSpeed(0);
        }
        if (player.getPosition().getPosition().x < 0)
        {
            player.setPosition(0, 800);
            player.setSpeed(0);
        }
        
        ball.move();
        if (ball.isColidePlayer(player)) ball.setSpeedY(-(rand()%9+5));
        for (int i = 0; i < nPlitok; i++)
        {
            if (ball.isColidePlitka(plitki[i]))
            {

                float overlapLeft = ball.getPosition().x - (plitki[i].getPosition().x + plitki[i].getSize().x);
                float overlapRight = (ball.getPosition().x + 30) - plitki[i].getPosition().x;
                float overlapTop = ball.getPosition().y - (plitki[i].getPosition().y + plitki[i].getSize().y);
                float overlapBottom = (ball.getPosition().y + 30) - plitki[i].getPosition().y;

                bool ballFromLeft = abs(overlapLeft) < abs(overlapRight);
                bool ballFromTop = abs(overlapTop) < abs(overlapBottom);

                if (ballFromLeft) ball.setSpeedX(speedBallX);
                else ball.setSpeedX(-speedBallX);
                if (ballFromTop) ball.setSpeedY(-speedBallY);
                else ball.setSpeedY(speedBallY);

                plitki[i].setPosition(-500, 0);
                score++;
                std::ostringstream scoreStr;
                scoreStr  <<"Score: " << score;
                scoretxt.setString(scoreStr.str());
            }
            
        }
        
        if (ball.getPosition().x > window.getSize().x - 30) ball.setSpeedX(-speedBallX);
        if (ball.getPosition().x < 0) ball.setSpeedX(speedBallX);
        if (ball.getPosition().y < 0) ball.setSpeedY(-speedBallY);
        if (ball.getPosition().y > window.getSize().y - 30)
        {
            gameOver = true;
        }
        if (score == 100)
        {
            levelComplete = true;
        }
        if (gameOver)
        {
            window.clear();
            
            window.draw(gameOvertxt);
            window.draw(continuetxt);
            window.draw(exittxt);
            window.display();
        }
        else if (levelComplete)
        {
            ball.setSpeed(0, 0);
            
            window.clear();
            window.draw(levelCompletetxt);
            window.draw(continuetxt);
            window.draw(exittxt);
            window.display();
        }
        else
        {
            window.clear();
            window.draw(scoretxt);
            if (gameStarted == false) window.draw(start);
            player.draw(window);
            ball.draw(window);
            for (int i = 0; i < nPlitok; i++) window.draw(plitki[i]);

            window.display();
        }
        
    }

    return 0;
}