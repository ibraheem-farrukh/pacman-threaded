#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
using namespace sf;
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

class player
{
public:
    int direction;  
    double x;
    double y;
    int x_limit;
    int y_limit;
    int block_size;
    Sprite player_sprite;
    Texture player_texture;
    string player_name;
    Clock moveclock;
    Clock aniclock;
    int anistate;
    int score;
    Clock powclock;
    bool poweredup;
    int lives;

    player()
    {
        x=y=0;
        player_name = "";
    }

    player(double xx,double yy,string name,int lx,int ly,int b)
    {
        player_texture.loadFromFile("sprites/pacman/neutral.png");
		player_sprite.setTexture(player_texture);
        player_sprite.setScale(2,2);
        x = xx+3;
        y = yy+3;
        player_sprite.setPosition(x,y);
        player_name=name;
        x_limit = lx;
        y_limit = ly;
        block_size=b;
        direction=0;
        anistate=1;
        score=0;
        poweredup=0;
        lives=5;
    }


    void move()
    {
        if(poweredup && powclock.getElapsedTime().asSeconds() > 5)
        {
            poweredup=0;
            powclock.restart();
        }

        
        if(moveclock.getElapsedTime().asSeconds() < 0.2)
        {
            return;
        }

        moveclock.restart();
        switch(direction)
        {
            case 1:
                    this->y-=block_size;
                break;
            case 2:
                    this->x+=block_size;
                break;
            case 3:
                    this->y+=block_size;
                break;
            case 4:
                    this->x-=block_size;
                break;
        }

        if(x<0)
            x=867;
        if(x>896)
            x=3;
        if(y<0)
            y=963;
        if(y>992)
            y=3;

        player_sprite.setPosition(x,y);
    }

    void animation()
    {
        if(direction==0)
        {
            aniclock.restart();
            return;   
        }

        if(aniclock.getElapsedTime().asSeconds() > 0.2)
        {
            aniclock.restart();

            string directionstr="sprites/pacman/";
            switch(direction)
            {
                case 1:
                    directionstr+="up";
                    break;
                case 2:
                    directionstr+="right";
                    break;
                case 3:
                    directionstr+="down";
                    break;
                case 4:
                    directionstr+="left";
                    break;
            }
            switch(anistate)
            {
                case 1:
                    anistate=2;
                    directionstr+="_2";
                    break;
                case 2:
                    anistate=1;
                    directionstr+="_1";
                    break;
            }

            directionstr+=".png";

            player_texture.loadFromFile(directionstr);
            player_sprite.setTexture(player_texture);
            player_sprite.setScale(2,2);
        }
    }

    void setdirection(int taraf)
    {
        direction = taraf;

        string directionstr="sprites/pacman/";
        switch(direction)
        {
            case 1:
                directionstr+="up";
                break;
            case 2:
                directionstr+="right";
                break;
            case 3:
                directionstr+="down";
                break;
            case 4:
                directionstr+="left";
                break;
        }

        directionstr+="_1.png";
        player_texture.loadFromFile(directionstr);
        player_sprite.setTexture(player_texture);
        player_sprite.setScale(2,2);
    }

    int getx()
    {
        return (x-3)/32;
    }

    int gety()
    {
        return (y-3)/32;
    }
};