#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
using namespace sf;
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
class Menu{
public:
// attributes
    Sprite msprite;
    Texture mtexture;
    Sprite instructionssprite;
    Texture instructionstexture;
    Font fontfont;
    Font titlefont;
    Text texttext[4];
    Text title[2];
    Text nameenter[2];
    string name;

    int button;

    int page;

/// constructor
Menu()
{
    fontfont.loadFromFile("sprites/Emulogic-zrEw.ttf");

    // play button
    texttext[0].setFont(fontfont);
    texttext[0].setFillColor(Color::White);
    texttext[0].setString("PLAY");
    texttext[0].setCharacterSize(40);
    texttext[0].setPosition(410, 390);

    // quit button
    texttext[3].setFont(fontfont);
    texttext[3].setFillColor(Color::White);
    texttext[3].setString("QUIT");
    texttext[3].setCharacterSize(40);
    texttext[3].setPosition(410, 540);

    button = 0;
    page = 1;

    titlefont.loadFromFile("sprites/Emulogic-zrEw.ttf");

    title[0].setFont(titlefont);
    title[0].setFillColor(Color::Green);
    title[0].setOutlineColor(Color::White);
    title[0].setString("Space");
    title[0].setCharacterSize(65);
    title[0].setPosition(100, 100);

    title[1].setFont(titlefont);
    title[1].setFillColor(Color::Green);
    title[1].setString("Shooter");
    title[1].setCharacterSize(65);
    title[1].setPosition(300, 160);

    // play button
    nameenter[0].setFont(fontfont);
    nameenter[0].setFillColor(Color::White);
    nameenter[0].setString("ENTER NAME : ");
    nameenter[0].setCharacterSize(40);
    nameenter[0].setPosition(200, 200);

    nameenter[1].setFont(fontfont);
    nameenter[1].setFillColor(Color::Red);
    nameenter[1].setCharacterSize(40);
    nameenter[1].setPosition(200, 300);

    instructionstexture.loadFromFile("Menu/instructions.png");
    instructionssprite.setTexture(instructionstexture);
}

void buttonup()
{
    texttext[button].setFillColor(Color::White);

    if(button>0)
    {
        button--;
    }
    else
    {
        button = 3;
    }

    texttext[button].setFillColor(Color::Red);
}

void buttondown()
{
    texttext[button].setFillColor(Color::White);

    if(button<3)
    {
        button++;
    }
    else
    {
        button = 0;
    }

    texttext[button].setFillColor(Color::Red);

}

void display_menu()
{
    RenderWindow mainmenuwindow(VideoMode(700, 700), "Welcome To SpaceShooter !");
    mtexture.loadFromFile("Menu/space.png");
    msprite.setTexture(mtexture);
    msprite.setScale(1.68, 1.68);

    Clock clock;
    float delay = 0;


    while (mainmenuwindow.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        delay += time;

        Event em;
        

        if(page == 1)
        {
            while (mainmenuwindow.pollEvent(em))
            {  
                if (em.type == Event::Closed) // If cross/close is clicked/pressed
                    mainmenuwindow.close(); //close the game                        	    
            }

            texttext[button].setFillColor(Color::Red);

            if(Keyboard::isKeyPressed(Keyboard::Up))
                if(delay>0.2)
                {
                    buttonup();
                    delay=0;
                }

            if(Keyboard::isKeyPressed(Keyboard::Down))
                if(delay>0.2)
                {
                    buttondown();
                    delay=0;
                }

            if(Keyboard::isKeyPressed(Keyboard::Enter))
            {
                switch(button)
                {
                    case 0:
                        page = 2;
                        break;
                    case 1:
                        page = 3;
                        break;
                    case 2:
                        page = 4;
                        break;
                    case 3:
                        mainmenuwindow.close();
                        break;
                }
            }

        }

        if(page==2)
        {
            while (mainmenuwindow.pollEvent(em))
            {  
                if (em.type == Event::Closed) // If cross/close is clicked/pressed
                    mainmenuwindow.close(); //close the game 
                if(em.type == Event::TextEntered)      
                    name += static_cast<char>(em.text.unicode);  
                if(Keyboard::isKeyPressed(Keyboard::BackSpace) && name.size()>0)
                    name.resize (name.size()-1);   
                if(Keyboard::isKeyPressed(Keyboard::Enter) && name.size()>1)
                {
                    return; 
                }
            }

                if(Keyboard::isKeyPressed(Keyboard::Escape) && name.size()>1)
                    page=1;     	    
            

            nameenter[1].setString(name);
        }

        if(page==4)
        {
            while (mainmenuwindow.pollEvent(em))
            {  
                if (em.type == Event::Closed) // If cross/close is clicked/pressed
                    mainmenuwindow.close(); //close the game     	    
            }

            if(Keyboard::isKeyPressed(Keyboard::Escape))
                page=1; 
        }

        mainmenuwindow.clear(Color::Black);
	    mainmenuwindow.draw(msprite);

        if(page==1)
        {
            for(int i=0;i<4;i++)
            {
                mainmenuwindow.draw(texttext[i]);
            }
            for(int i=0;i<2;i++)
            {
                mainmenuwindow.draw(title[i]);
            }
        }

        if(page==2)
        {
            for(int i=0;i<2;i++)
            {
                mainmenuwindow.draw(nameenter[i]);
            }
        }

        if(page==4)
        {
            mainmenuwindow.draw(instructionssprite);
        }

        mainmenuwindow.display();
    }
}


};
