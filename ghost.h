#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
using namespace sf;
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

class ghost
{
public:
    string gname;
    float speed;
    int direction;  
    double x;
    double y;
    int x_limit;
    int y_limit;
    int block_size;
    Sprite gsprite;
    Texture gtexture;
    Clock moveclock;
    Clock aniclock;
    int anistate;
    bool outside;
    bool isscared;
    int lastdirection;
    bool key;
    bool permit;
    int* exitingpath;
    int exitingpathlength;
    int currexitpath;
    bool exiting;
    bool speedboost;
    int* speedpath;
    int speedpathlength;
    int currspeedpath;

    ghost()
    {
        x=y=0;
    }

    ghost(double xx,double yy,string name,int lx,int ly,int b,int*& expath,int ep,float s)
    {
        speed=s;
        gname=name;
        string path = "sprites/ghost/";
        path+=name+"_right_1.png";
        gtexture.loadFromFile(path);
		gsprite.setTexture(gtexture);
        gsprite.setScale(2,2);
        x = xx+3;
        y = yy+3;
        gsprite.setPosition(x,y);
        x_limit = lx;
        y_limit = ly;
        block_size=b;
        direction=1;
        anistate=1;
        outside=0;
        isscared=0;
        lastdirection=0;
        key=0;
        permit=0;
        exitingpath = expath;
        exitingpathlength=ep;
        exiting=0;
        currexitpath = 0;
        speedboost=0;

        currspeedpath = 0;

        if(gname=="blue")
        {
            speedpathlength=7;
            speedpath = new int[7]{2,1,1,1,2,2,2};
            speedboost=1;
        }

        else if(gname=="orange")
        {
            speedpathlength=7;
            speedpath = new int[7]{2,1,1,1,2,2,2};
            speedboost=1;
        }
    }


    void move()
    {
        if(moveclock.getElapsedTime().asSeconds() < speed)
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

        gsprite.setPosition(x,y);
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

            string directionstr="sprites/ghost/";
            directionstr+=gname+"_";
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

            gtexture.loadFromFile(directionstr);
            gsprite.setTexture(gtexture);
            gsprite.setScale(2,2);
        }
    }

    void scared()
    {
        if(aniclock.getElapsedTime().asSeconds() > 0.2 || isscared==0)
        {
            aniclock.restart();
            isscared=1;

            string directionstr="sprites/ghost/scared";
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

            gtexture.loadFromFile(directionstr);
            gsprite.setTexture(gtexture);
            gsprite.setScale(2,2);
        }
    }

    void setdirection(int taraf)
    {
        direction = taraf;

        // string directionstr="sprites/ghost/";
        // directionstr+=gname+"_";
        // switch(direction)
        // {
        //     case 1:
        //         directionstr+="up";
        //         break;
        //     case 2:
        //         directionstr+="right";
        //         break;
        //     case 3:
        //         directionstr+="down";
        //         break;
        //     case 4:
        //         directionstr+="left";
        //         break;
        // }

        // directionstr+="_1.png";
        // gtexture.loadFromFile(directionstr);
        // gsprite.setTexture(gtexture);
        // gsprite.setScale(2,2);
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

