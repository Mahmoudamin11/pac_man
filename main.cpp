#include <sfml\Graphics.hpp>
#include<SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include"player.h"
#include "Maps.h"
#include "Ghost.h"
#include "LoseOrWin.h"
#include "Dashboard.h"
#include "PauseMenu.h"
#include <Windows.h>
#include <string>
#include<queue>
#include <thread>
#include<chrono>
using namespace std;
using namespace sf;



int pagenum = 1000;
int levelSelected = -1;
int Number_Of_Level = 0;
bool isfirstplayagain = false;
string name;

void EnterName(RenderWindow& window, string& name)
{
    if (!name.empty())
    {
        name.clear();
    }

    Texture backgroundTexture;
    backgroundTexture.loadFromFile("main_menu/background.jpg");
    Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale(
        static_cast<float>(window.getSize().x) / background.getLocalBounds().width,
        static_cast<float>(window.getSize().y) / background.getLocalBounds().height
    );
    Font font;
    font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
    Text t1;
    Text t2;

    t1.setFont(font);
    t2.setFont(font);
    t1.setString("Enter Your Name : ");
    t1.setCharacterSize(42);
    t2.setCharacterSize(40);
    t1.setPosition(Vector2f(40, 50));
    t2.setPosition(Vector2f(40, 130));
    t1.setFillColor(Color::Yellow);
    t2.setFillColor(Color::Yellow);



    /*levels*/

    Text level[3];
    Text alert;

    // level1 button

    font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
    level[0].setFont(font);
    level[0].setFillColor(Color::White);
    level[0].setString("Level1");
    level[0].setCharacterSize(40);
    level[0].setPosition(Vector2f(20 + 20, 350));


    //level2 
    font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
    level[1].setFont(font);
    level[1].setFillColor(Color::White);
    level[1].setString("Level2");
    level[1].setCharacterSize(40);
    level[1].setPosition(Vector2f(220, 350));


    //level3
    font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
    level[2].setFont(font);
    level[2].setFillColor(Color::White);
    level[2].setString("Level3");
    level[2].setCharacterSize(40);
    level[2].setPosition(Vector2f(300 + 100, 350));



    // alert 
    font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
    alert.setFont(font);
    alert.setFillColor(Color::Red);
    alert.setString("Please Enter Your name");
    alert.setCharacterSize(30);
    alert.setPosition(Vector2f(85, 450));
    alert.setScale(0, 0);




    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed())

            {
                window.close();
            }
            if (event.type == Event::TextEntered)
            {
                name += static_cast<char>(event.text.unicode);
            }
            if (Keyboard::isKeyPressed(Keyboard::BackSpace) && name.size() > 0)
            {
                name.erase(name.size() - 1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Return) && name.size() > 0)
            {
                //main game
                pagenum = 2;
                return;
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {

                pagenum = 1000;
                return;
            }

            /*levels handle */
            if (event.type == Event::MouseButtonPressed && !(name.size() > 0))
            {
                alert.setScale(1, 1);
            }
            if (event.type == Event::MouseButtonPressed && name.size() > 0)
            {
                if (level[0].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && name.size() > 0)
                {
                    // Handle Level 1 button click
                    levelSelected = 1;
                    pagenum = 2;
                    return;
                }
                if (level[1].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && name.size() > 0)
                {
                    // Handle Level 2 button click
                    levelSelected = 2;

                    pagenum = 2;
                    return;
                }
                if (level[2].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && name.size() > 0)
                    // Handle Level 3 button click
                    levelSelected = 3;

                pagenum = 2;
                return;
            }



        }

        t2.setString(name);
        window.clear();
        window.draw(background);
        window.draw(t1);
        window.draw(t2);
        window.draw(alert);
        /*level draw*/
        for (int i = 0; i < 3; i++)
        {
            window.draw(level[i]);
        }
        window.display();





    }


}


/*
    pagenum         fun

    2003      *      pause menu
    1000      *      mainmenu
    -1        *      close
     0        *      entername
     1        *      dashboard
     2        *      maingame
*/

int main()
{



_mainmenu:;
    RenderWindow window(VideoMode(608, 660), "Pac-Man");
    Menu menu(700, 700);

    // sounds 

    SoundBuffer buffer;
    buffer.loadFromFile("pacman_beginning.wav");
    Sound sound;
    sound.setBuffer(buffer);

    SoundBuffer foodb;
    foodb.loadFromFile("dot.wav");
    Sound eats;
    eats.setBuffer(foodb);

    SoundBuffer ghostb;
    ghostb.loadFromFile("pacman_death.wav");
    Sound ghosts;
    ghosts.setBuffer(ghostb);



play_again:;
    pause_menu pausemenu(700, 700);

    // main menu background 
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("main_menu/background.jpg");
    Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale(
        static_cast<float>(window.getSize().x) / background.getLocalBounds().width,
        static_cast<float>(window.getSize().y) / background.getLocalBounds().height
    );

    // main menu font 
    Font font;
    if (!font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf")) {
        cerr << "Error loading font file!" << endl;
        return 1;
    }


    // =========== Maps
    Maps map1("Maps/firstMap.txt", window);
    Maps map2("Maps/secondMap.txt", window);
    Maps map3("Maps/thirdMap.txt", window);

    // Queue that stores the 3 maps
    queue<Maps> gameMaps;



    if (!isfirstplayagain)
    {


        gameMaps.push(map1);
        gameMaps.push(map2);
        gameMaps.push(map3);


    }
    else
    {
        if (Number_Of_Level == 1) {
            gameMaps.push(map1);
            gameMaps.push(map2);
            gameMaps.push(map3);
        }
        if (Number_Of_Level == 2)
        {
            gameMaps.push(map2);
            gameMaps.push(map3);
        }
        else if (Number_Of_Level == 3)
        {
            gameMaps.push(map3);
        }

    }

    // ===========

    // =========== Player
    Texture player_Texture;
    player_Texture.loadFromFile("pacMan2 1.png");
    player p(player_Texture, 32, 32, 32, 32, gameMaps.front().playerRenderPos);
    //===================

    // Ghosts 
    Texture redT, pinkT, orangeT, blueT;
    redT.loadFromFile("Ghosts/red.png");
    pinkT.loadFromFile("Ghosts/pink.png");
    orangeT.loadFromFile("Ghosts/orange.png");
    blueT.loadFromFile("Ghosts/blue.png");
    Ghost red(redT, { 32.0f, 32.0f });
    Ghost pink(pinkT, { 576.0f - 32.0f, 32.0f });
    Ghost orange(orangeT, { 32.0f, 576.0f - 32.0f });
    Ghost blue(blueT, { 576.0f - 32.0f, 576.0f - 32.0f });

    // =================

    // check for loose and win 
    LoseOrWin checker;

    // frame rate handle 
    window.setFramerateLimit(60);
    Clock clk;

    // dashboard 
    Dashboard dashboard(5);

    // score     
    Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    score.setFillColor(Color::Yellow);
    score.setPosition(0, 610);
    String scorenow;

    //health
    Text health;
    health.setFont(font);
    health.setCharacterSize(30);
    health.setFillColor(Color::Yellow);
    health.setPosition(440, 610);
    String healthnow;

    while (true) {



        // if player lose
        if (pagenum == 3000)
        {

            Font font;
            font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
            Text t1;
            Text t2;
            t1.setFont(font);
            t2.setFont(font);
            t1.setString("You Lose");
            t2.setString("score " + to_string(p.getScore()));
            t1.setCharacterSize(42);
            t2.setCharacterSize(40);
            t1.setPosition(Vector2f(40, 50));
            t2.setPosition(Vector2f(40, 130));
            t1.setFillColor(Color::Yellow);
            t2.setFillColor(Color::Yellow);


            font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");

            Text btns[2];

            font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
            btns[0].setFont(font);
            btns[0].setFillColor(Color::White);
            btns[0].setString("Play Again");
            btns[0].setCharacterSize(30);
            btns[0].setPosition(Vector2f(40, 350));


            //level2 
            font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
            btns[1].setFont(font);
            btns[1].setFillColor(Color::White);
            btns[1].setString("main_menu");
            btns[1].setCharacterSize(30);
            btns[1].setPosition(Vector2f(40, 450));


            Event event;
            while (window.pollEvent(event))
            {

                if (event.type == Event::MouseButtonPressed)
                {
                    if (btns[0].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        // Handle Level 1 button click
                        window.clear();
                        pagenum = 2; // game 
                        p.movement = true;
                        isfirstplayagain = true;
                        goto play_again;

                    }
                    // go to main menu 
                    if (btns[1].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        window.clear();
                        ofstream offile;
                        offile.open("Dashboardf.txt", ios::app);
                        offile << name << " " << p.getScore() << "*" << endl;
                        pagenum = 1000;
                        goto _mainmenu;
                    }

                }



            }


            window.draw(t1);
            window.draw(t2);
            for (int i = 0; i < 2; i++)
            {
                window.draw(btns[i]);
            }
            window.display();










        }

        // if player win
        if (pagenum == 2000)
        {





            Font font;
            font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
            Text t1;
            Text t2;
            Text t3;

            t1.setFont(font);
            t2.setFont(font);
            t3.setFont(font);
            t1.setString("You win");
            t2.setString("score " + to_string(p.getScore()));
            t3.setString("THANK YOU, YOU ARE VERY GOOD"); // if player win in level 3
            t1.setCharacterSize(42);
            t2.setCharacterSize(40);
            t3.setCharacterSize(25);
            t1.setPosition(Vector2f(40, 50));
            t2.setPosition(Vector2f(40, 130));
            t3.setPosition(Vector2f(50, 130));
            t1.setFillColor(Color::Yellow);
            t2.setFillColor(Color::Yellow);
            t3.setFillColor(Color::Yellow);


            font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");

            Text btns[2];

            font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
            btns[0].setFont(font);
            btns[0].setFillColor(Color::White);
            btns[0].setString("Save score & go to next level");
            btns[0].setCharacterSize(30);
            btns[0].setPosition(Vector2f(40, 350));


            //level2 
            font.loadFromFile("main_menu/Gatrich-BF63dc6fcf996b7.otf");
            btns[1].setFont(font);
            btns[1].setFillColor(Color::White);
            btns[1].setString("Save score & return to main menu");
            btns[1].setCharacterSize(30);
            btns[1].setPosition(Vector2f(40, 450));


            Event event;
            while (window.pollEvent(event))
            {

                if (event.type == Event::MouseButtonPressed)
                {
                    // go to next map 
                    if (btns[0].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        // Handle Level 1 button click
                        window.clear();
                        pagenum = 2;
                        Number_Of_Level++;
                        if (Number_Of_Level == 4)
                        {
                            window.draw(t3);
                            window.display();
                            Sleep(3000);
                            goto _mainmenu;

                        }
                        isfirstplayagain = true;
                        ofstream offile;
                        offile.open("Dashboardf.txt", ios::app);
                        offile << name << " " << p.getScore() << "*" << endl;
                        goto play_again;
                    }
                    // go to main menu
                    if (btns[1].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        window.clear();
                        ofstream offile;
                        offile.open("Dashboardf.txt", ios::app);
                        offile << name << " " << p.getScore() << "*" << endl;
                        pagenum = 1000;
                        goto _mainmenu;
                    }

                }

            }


            window.draw(t1);
            window.draw(t2);
            for (int i = 0; i < 2; i++)
            {
                window.draw(btns[i]);
            }
            window.display();


        }

        // pause menu
        if (pagenum == 2003)
        {

            Event event;
            while (window.pollEvent(event))
            {


                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Up)
                    {
                        pausemenu.moveUp();
                    }
                    else if (event.key.code == Keyboard::Down)
                    {
                        pausemenu.moveDown();
                    }
                    else if (event.key.code == Keyboard::Return)
                    {

                        if (pausemenu.pressed() == 0) //  continue 
                        {

                            pagenum = 2;
                            p.movement = true;
                            break;
                        }
                        else if (pausemenu.pressed() == 1) // play again
                        {
                            window.clear();
                            pagenum = 2;
                            p.movement = true; // close the pause 
                            goto play_again;

                        }
                        else if (pausemenu.pressed() == 2) // go to main menu
                        {
                            window.clear();
                            pagenum = 1000;
                            goto _mainmenu;
                        }



                    }

                }



            }


            pausemenu.draw(window);
            window.display();





        }

        if (pagenum == 1000)
        {
            bool flagSound = 1;
            if (flagSound) {
                sound.play();
                flagSound = 0;
            }
            while (window.isOpen())
            {
                Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        window.close();
                        break;
                    }
                    if (event.type == Event::KeyPressed)
                    {
                        if (event.key.code == Keyboard::Up)
                        {
                            menu.moveUp();
                        }
                        if (event.key.code == Keyboard::Down)
                        {
                            menu.moveDown();
                        }
                        if (event.key.code == Keyboard::Return)
                        {
                            if (menu.pressed() == 0) // enter name 
                            {
                                pagenum = 0;
                            }
                            if (menu.pressed() == 1) // dashboard
                            {
                                pagenum = 1;
                            }
                            if (menu.pressed() == 2) // exit 
                            {
                                pagenum = -1;
                            }
                        }
                    }
                }
                window.clear();
                if (pagenum != 1000)
                {
                    break;
                }
                window.draw(background);
                menu.draw(window);

                window.display();
            }
        }

        if (pagenum == -1)
        {
            window.close();
            break;
        }

        else if (pagenum == 0)
        {
            EnterName(window, name); // makes pagenum = 2 
            Number_Of_Level = 1;

        }


        else if (pagenum == 1)
        {


            while (window.isOpen())
            {
                Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        window.close();
                        break;
                    }
                    if (event.type == Event::KeyPressed)
                    {
                        /*if (event.key.code == Keyboard::Up)
                        {

                        }
                        if (event.key.code == Keyboard::Down)
                        {

                        }*/
                        /*if (event.key.code == Keyboard::Return) // enter
                        {
                            pagenum = 1000;

                        }*/
                        if (event.key.code == Keyboard::Escape)
                        {
                            pagenum = 1000;
                        }
                    }
                }
                window.clear();
                if (pagenum != 1)
                {
                    break;
                }
                window.draw(background);

                for (int i = 0; i <= dashboard.mutmap.size(); i++)
                {
                    window.draw(dashboard.text[i]);
                }
                window.display();
            }

        }

        // game 
        else if (pagenum == 2) {

            window.clear();
            if (pagenum != 2)
            {
                break;
            }

            float deltaTime;
            deltaTime = clk.restart().asSeconds();

            gameMaps.front().draw(window);
            // load ghosts and set their levels 
            red.selectLevel(levelSelected, gameMaps.front().getMapGrid());
            pink.selectLevel(levelSelected, gameMaps.front().getMapGrid());
            orange.selectLevel(levelSelected, gameMaps.front().getMapGrid());
            blue.selectLevel(levelSelected, gameMaps.front().getMapGrid());

            // eat food 
            for (int i = 0; i < gameMaps.front().getFood().size(); i++) {
                if (p.getPlayerSprite().getGlobalBounds().intersects(gameMaps.front().getFood()[i].getGlobalBounds())) {

                    // map to mark this as eaten
                    gameMaps.front().eaten[i] = 1;
                    p.eat();
                    eats.play();
                    eats.setPlayingOffset(seconds(1.f));
                    break;
                }
                else {
                    eats.stop();
                }
            }

            // check if that weird creature ate everything or not yet 
            if (p.getScore() == gameMaps.front().getFood().size()) {

                pagenum = 2000;
                if (gameMaps.size() > 1) {

                    deltaTime = 0;
                    if (Number_Of_Level == 4) {
                        break;
                    }

                    /*
                    p.reset(gameMaps.front().playerRenderPos);
                    red.reset();
                    pink.reset();
                    orange.reset();
                    blue.reset(); */
                }


            }
            else {
                scorenow = to_string(p.getScore());
                score.setString("Score :" + scorenow);
                healthnow = to_string(p.getHealth());
                health.setString("Health :" + healthnow);
            }

            // when he loses  write in file 

            bool flaglose = true;
            if (p.getHealth() <= 0)  //lose
            {

                flaglose = false;
                //dashboard.currents = p.getScore();

               // pagenum = 4; lose window
            }


            // if not loose 
            if (p.movement == false)
            {
                pagenum = 2003; // open pause menu
            }

            bool coll = checker.checkLose(p, red, pink, blue, orange);

            if (coll) {
                ghosts.play();
                ghosts.setPlayingOffset(seconds(1.f));
            }
            else {
                ghosts.stop();
            }
            if (coll == true && p.getHealth() == 1)
            {
                p.decreaseHealth();
                healthnow = to_string(p.getHealth());
                health.setString("Health :0");
                pagenum = 3000;
                deltaTime = 0;
                p.movement = false;
            }

            // if not lose 
            if (p.movement == false)
            {

                if (pagenum != 2000 && pagenum != 3000)
                {
                    p.update(gameMaps.front().getMapGrid(), 0, window, gameMaps.front().getMapObstacles(), coll);
                    pagenum = 2003;
                }
                //deltatime = 0 to stop animation on the pac-man 

            }
            else
            {
                p.update(gameMaps.front().getMapGrid(), deltaTime, window, gameMaps.front().getMapObstacles(), coll);
                red.update(gameMaps.front().getMapGrid(), deltaTime, window, gameMaps.front().getConnectedCells(), p, coll);
                pink.update(gameMaps.front().getMapGrid(), deltaTime, window, gameMaps.front().getConnectedCells(), p, coll);
                orange.update(gameMaps.front().getMapGrid(), deltaTime, window, gameMaps.front().getConnectedCells(), p, coll);
                blue.update(gameMaps.front().getMapGrid(), deltaTime, window, gameMaps.front().getConnectedCells(), p, coll);

            }



            // updates the movement 
            red.draw(window);
            pink.draw(window);
            orange.draw(window);
            blue.draw(window);
            window.draw(score);
            window.draw(health);
            p.draw(window);
            window.display();
        }
    }

    return 0;
}








