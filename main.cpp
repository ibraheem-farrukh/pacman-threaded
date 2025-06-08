#include "unistd.h"
#include <ctime>
#include <iostream>
#include <semaphore.h>
using namespace std;
#include "player.h"
#include "ghost.h"
#include "menu.h"
Font fontfont;
Text title , title1;
pthread_t menuthread;

int grid[31][28] =
{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
  {1,0,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,0,1}, 
  {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1}, 
  {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1}, 
  {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1}, 
  {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1}, 
  {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1}, 
  {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1}, 
  {1,3,2,2,2,2,2,1,1,5,2,2,2,1,1,2,2,2,5,1,1,2,2,2,2,2,3,1}, 
  {1,1,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,1,1}, 
  {1,1,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,1,1}, 
  {1,1,1,1,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,1,1,1,1}, 
  {1,1,1,1,1,1,2,1,1,2,1,1,1,4,4,1,1,1,2,1,1,2,1,1,1,1,1,1}, 
  {1,1,1,1,1,1,2,1,1,2,1,0,0,0,0,0,0,1,2,1,1,2,1,1,1,1,1,1}, 
  {2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2}, 
  {1,1,1,1,1,1,2,1,1,2,1,0,0,0,0,0,0,1,2,1,1,2,1,1,1,1,1,1}, 
  {1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1}, 
  {1,1,1,1,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,1,1,1,1}, 
  {1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1}, 
  {1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1}, 
  {1,3,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,3,1}, 
  {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1}, 
  {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1}, 
  {1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,1}, 
  {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1}, 
  {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1}, 
  {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1}, 
  {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1}, 
  {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1}, 
  {1,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,1}, 
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} }; 

Sprite*** pellets;
Clock delayclock;

player* pacman = new player(32,32,"PACMAN",864,960,32);
int* expath1 = new int[4]{2,2,1,1};
int* expath2 = new int[6]{2,2,1,1,1,1};
int* expath3 = new int[4]{4,4,1,1};
int* expath4 = new int[6]{4,4,1,1,1,1};
ghost** ghostholder = new ghost*[4]
{new ghost(352,416,"red",896,992,32,expath1,4,0.6),
new ghost(352,480,"pink",896,992,32,expath2,6,0.6),
new ghost(512,416,"blue",896,992,32,expath3,4,0.4),
new ghost(512,480,"orange",896,992,32,expath4,6,0.4)};

pthread_t ui_thread,ghost_control_thread,ghost1_thread,ghost2_thread,ghost3_thread,ghost4_thread;
bool quit=0;

pthread_mutex_t gmovemutex;
bool key[2]={1,1};
bool permit[2]={1,1};
int numperm=2;
pthread_mutex_t gkeymutex;
sem_t perkeysem;

void take_key(ghost*& bhoot)
{
    bool found_key=0;
    for(int i=0;i<numperm;i++)
    {
        if(key[i])
        {
            //cout<<"found key"<<endl;
            key[i]=0;
            found_key=1;
            break;
        }
    }

    bhoot->key=found_key;
}

void take_permit(ghost*& bhoot)
{
    bool found_permit=0;
    for(int i=0;i<numperm;i++)
    {
        if(permit[i])
        {
            //cout<<"found permit"<<endl;
            permit[i]=0;
            found_permit=1;
            break;
        }
    }

    bhoot->permit=found_permit;
}

void put_key(ghost*& bhoot)
{
    for(int i=0;i<numperm;i++)
    {
        if(!key[i])
        {
            //cout<<"put key at "<<i<<endl;
            key[i]=1;
            bhoot->key=0;
            break;
        }
    }
}

void put_permit(ghost*& bhoot)
{
    for(int i=0;i<numperm;i++)
    {
        if(!permit[i])
        {
            //cout<<"put permit at "<<i<<endl;
            permit[i]=1;
            bhoot->permit=0;
            break;
        }
    }
}

void ghost_direction_random(ghost*& bhoot)
{
    int randchance = (rand()%100);
    int randdir=(rand()%4)+1;

    if(randchance > 50)
    {
        return;
    }

    if(bhoot->moveclock.getElapsedTime().asSeconds() > bhoot->speed)
    {
        while(randdir==bhoot->direction)
        {
            randdir = (rand()%4)+1;
        }

        bhoot->lastdirection = bhoot->direction;
        bhoot->direction = randdir;
    }
}

int player_wall_check(player*& pacman)
{
    int xx=pacman->getx();
    int yy=pacman->gety();

    switch(pacman->direction)
    {
        case 1:
            if(yy > 0)
                yy-=1;
            break;
        case 2:
            if(xx < pacman->x_limit/pacman->block_size)
                xx+=1;
            break;
        case 3:
            if(yy < pacman->y_limit/pacman->block_size)
                yy+=1;
            break;
        case 4:
            if(xx > 0)
                xx-=1;
            break;
    }


    return grid[yy][xx]==1||grid[yy][xx]==4?0:1;
}

int player_ghost_check()
{
    int xx=pacman->getx();
    int yy=pacman->gety();
    int hit=0;

    for(int i=0;i<4;i++)
    {
        if(xx==ghostholder[i]->getx() && yy==ghostholder[i]->gety())
            hit=i+2;
    }

if(hit)
    return pacman->poweredup==0?1:hit;
else
    return 0;
}

int ghost_wall_check(ghost*& bhoot)
{
    int xx=bhoot->getx();
    int yy=bhoot->gety();

    int oldx = xx;
    int oldy = yy;

    switch(bhoot->direction)
    {
        case 1:
            if(yy > 0)
                yy-=1;
            break;
        case 2:
            if(xx < bhoot->x_limit/bhoot->block_size)
                xx+=1;
            break;
        case 3:
            if(yy < bhoot->y_limit/bhoot->block_size)
                yy+=1;
            break;
        case 4:
            if(xx > 0)
                xx-=1;
            break;
    }

    return grid[yy][xx]==1||(grid[yy][xx]==4 && !bhoot->key)?0:1;
}

int ghost_ghost_check(ghost*& bhoot)
{
    int xx=bhoot->getx();
    int yy=bhoot->gety();

    for(int i=0;i<4;i++)
    {
        if(ghostholder[i]==bhoot)
            continue;

        if(xx==ghostholder[i]->getx() && yy==ghostholder[i]->gety())
            return 0;
    }

return 1;
}

void ghost_death(ghost*& bhoot)
{
    pacman->score+=100;

    int ghostnum=0;
    for(int i=0;i<4;i++)
    {
        if(ghostholder[i]==bhoot)
        {
            ghostnum=i;
            break;
        }
    }

    switch(ghostnum)
    {
        case 0:
            bhoot->x=355;
            bhoot->y=419;
            break;
        case 1:
            bhoot->x=355;
            bhoot->y=483;
            break;
        case 2:
            bhoot->x=515;
            bhoot->y=419;
            break;
        case 3:
            bhoot->x=515;
            bhoot->y=483;
            break;
    }

    bhoot->direction=1;
    bhoot->outside=0;
    bhoot->isscared=0;
    bhoot->lastdirection=0;
    bhoot->key=0;
    bhoot->permit=0;
    bhoot->gsprite.setPosition(bhoot->x,bhoot->y);

    sem_post(&perkeysem);

}

void player_death()
{
    pacman->lives--;
    bool repeatedlydying=0;
    int xarr[4]={1,1,26,26};
    int yarr[4]={1,29,1,29};

    for(int i=0;i<4;i++)
    {

        for(int j=0;j<4;j++)
        {
            int xx=ghostholder[j]->getx();
            int yy=ghostholder[j]->gety();

            if(xx==xarr[i] && yy==yarr[i])
            {
                repeatedlydying=1;
                break;
            }
        }

        if(!repeatedlydying)
        {
            pacman->x=(xarr[i]*32)+3;
            pacman->y=(yarr[i]*32)+3;
            pacman->player_sprite.setPosition(pacman->x,pacman->y);
            pacman->direction=0;
            return;
        }
        repeatedlydying=0;
    }

    if(repeatedlydying==0)
    {
        pacman->x=(0*32)+3;
        pacman->y=(14*32)+3;
        pacman->player_sprite.setPosition(pacman->x,pacman->y);
        pacman->direction=0;
    }

return;
}

void* ui_func(void* arg)
{
    int block_size = 32;
    int num_blocksx = 896/block_size ;
    int num_blocksy = 992/block_size ;
    int window_x=1164;
    int window_y=992;
    RenderWindow window(VideoMode(window_x,window_y), "MAIN GAME");
    Event e;
    bool keyletgo = 1;

    Texture bgtexture;
    Sprite bgsprite;
    bgtexture.loadFromFile("sprites/grid/grid.png");
    bgsprite.setTexture(bgtexture);
    bgsprite.setScale(4,4);
    bgsprite.setPosition(0,0);

    Texture peltexture,powtexture,spetexture;
    peltexture.loadFromFile("sprites/grid/pellet.png");
    powtexture.loadFromFile("sprites/grid/powerup.png");
    spetexture.loadFromFile("sprites/grid/speedup.png");
    pellets = new Sprite**[31];
    for(int i=0;i<31;i++)
        pellets[i]=new Sprite*[28]{NULL};
    for(int i=0;i<31;i++)
    {
        for(int j=0;j<28;j++)
        {
            if(grid[i][j]==2)
            {
                pellets[i][j]=new Sprite(peltexture);
                pellets[i][j]->setScale(6,6);
                pellets[i][j]->setPosition((j*32)+10,(i*32)+10);
            }

            if(grid[i][j]==3)
            {
                pellets[i][j]=new Sprite(powtexture);
                pellets[i][j]->setScale(2,2);
                pellets[i][j]->setPosition((j*32)+3,(i*32)+3);
            }

            if(grid[i][j]==5)
            {
                pellets[i][j]=new Sprite(spetexture);
                pellets[i][j]->setScale(2,2);
                pellets[i][j]->setPosition((j*32)+3,(i*32)+3);
            }
        }
    }

    window.display();

    while(window.isOpen())
    {
        pacman->animation();

        pthread_mutex_lock(&gmovemutex);
        if(player_wall_check(pacman))
        {
            pacman->move();

            if(grid[pacman->gety()][pacman->getx()]==2)
            {
                pacman->score+=10;
                grid[pacman->gety()][pacman->getx()]=0;
                delete pellets[pacman->gety()][pacman->getx()];
                pellets[pacman->gety()][pacman->getx()]=NULL;
            }
            else if(grid[pacman->gety()][pacman->getx()]==3)
            {
                pacman->score+=50;
                pacman->poweredup=1;
                pacman->powclock.restart();
                grid[pacman->gety()][pacman->getx()]=0;
                delete pellets[pacman->gety()][pacman->getx()];
                pellets[pacman->gety()][pacman->getx()]=NULL;
            }
            else 
            {
                int checkhit=player_ghost_check();
                if(checkhit==1)
                {
                    player_death();
                }
                else if(checkhit>0)
                {
                    ghost_death(ghostholder[checkhit-2]);
                }
            }
        }
        pthread_mutex_unlock(&gmovemutex);

        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) 
            {
                quit=1;
                window.close();  
            }                	    
        }
        
        if (e.type == Event::KeyPressed && keyletgo) 
        {             
            keyletgo=0;
            if (e.key.code == Keyboard::Up && pacman->direction!=1) 
            {
                pacman->setdirection(1);  
            }                 
            else if (e.key.code == Keyboard::Right && pacman->direction!=2)  
            {
                pacman->setdirection(2); 
            }                                               
            else if (e.key.code == Keyboard::Down && pacman->direction!=3)  
            {
                pacman->setdirection(3); 
            }                    
            else if (e.key.code == Keyboard::Left && pacman->direction!=4)    
            {
                pacman->setdirection(4); 
            }                         
        } 

        if(e.type = Event::KeyReleased)
            keyletgo=1;

        window.clear(Color::Black);
        window.draw(bgsprite);
        for(int i=0;i<31;i++)
        {
            for(int j=0;j<28;j++)
            {
                if(pellets[i][j])
                {
                    window.draw(*pellets[i][j]);
                }
            }
        }
        window.draw(pacman->player_sprite);
        for(int i=0;i<4;i++)
            window.draw(ghostholder[i]->gsprite);

             title.setString("Lives " + to_string(pacman->lives));
             title1.setString("Score " + to_string(pacman->score));
             window.draw(title1);
             window.draw(title);
        window.display();
    }

return NULL;
}

void* ghost_func(void* arg)
{
    ghost* bhoot = (ghost*)arg;

    while(1)
    {

        if(pacman->poweredup)
            bhoot->scared();
        else
            bhoot->animation();

        if(bhoot->exiting && delayclock.getElapsedTime().asSeconds()>2)
        {
            if(bhoot->moveclock.getElapsedTime().asSeconds() > bhoot->speed)
            {
                pthread_mutex_lock(&gmovemutex);
                bhoot->setdirection(bhoot->exitingpath[bhoot->currexitpath++]);
                bhoot->move();

                int checkhit=player_ghost_check();
                if(checkhit==1)
                {
                    player_death();
                }
                else if(checkhit>0)
                {
                    ghost_death(ghostholder[checkhit-2]);
                }

                if(!bhoot->exiting || bhoot->currexitpath >= bhoot->exitingpathlength)
                {
                    bhoot->exiting=0;
                    bhoot->outside=1;
                    bhoot->currexitpath=0;

                    pthread_mutex_lock(&gkeymutex);
                    put_key(bhoot);
                    put_permit(bhoot);
                    pthread_mutex_unlock(&gkeymutex);
                }
                pthread_mutex_unlock(&gmovemutex);
            }
        }

        else if(!bhoot->outside && !bhoot->key)
        {
            sem_wait(&perkeysem);
            int show=-1;
            sem_getvalue(&perkeysem,&show);
            cout<<show<<endl;
            pthread_mutex_lock(&gkeymutex);

            take_key(bhoot);
            take_permit(bhoot);

            //get out of box
            if(bhoot->key && bhoot->permit)
            {
                bhoot->exiting=1;
                cout<<"bhoot "<<bhoot->gname<<" has key permit."<<endl;
            }

            pthread_mutex_unlock(&gkeymutex);
        }

        else if(bhoot->outside)
        {
            if(bhoot->speedboost == 1)
            {
                if(bhoot->moveclock.getElapsedTime().asSeconds() > bhoot->speed)
                {
                    pthread_mutex_lock(&gmovemutex);
                    bhoot->setdirection(bhoot->speedpath[bhoot->currspeedpath++]);
                    bhoot->move();
                    cout<<"moved "<<bhoot->currspeedpath<<endl;

                    if(bhoot->currspeedpath >= bhoot->speedpathlength)
                    {
                        if(pellets[bhoot->gety()][bhoot->getx()])
                            delete pellets[bhoot->gety()][bhoot->getx()];
                        pellets[bhoot->gety()][bhoot->getx()]=NULL;
                        bhoot->speed = 0.2;
                        bhoot->speedboost=0;
                    }
                    
                    int checkhit=player_ghost_check();
                    if(checkhit==1)
                    {
                        player_death();
                    }
                    else if(checkhit>0)
                    {
                        ghost_death(ghostholder[checkhit-2]);
                    }
                    pthread_mutex_unlock(&gmovemutex);
                }
            }

            else
            {
                pthread_mutex_lock(&gmovemutex);
                ghost_direction_random(bhoot);
                if(ghost_wall_check(bhoot))
                    bhoot->move();
                
                int checkhit=player_ghost_check();
                if(checkhit==1)
                {
                    player_death();
                }
                else if(checkhit>0)
                {
                    ghost_death(ghostholder[checkhit-2]);
                }
                pthread_mutex_unlock(&gmovemutex);
            }

        }
    }

}

void* ghost_controller_func(void* arg)
{
    pthread_mutex_init(&gmovemutex,NULL);
    pthread_create(&ghost1_thread,NULL,ghost_func,ghostholder[0]);
    pthread_create(&ghost2_thread,NULL,ghost_func,ghostholder[1]);
    pthread_create(&ghost3_thread,NULL,ghost_func,ghostholder[2]);
    pthread_create(&ghost4_thread,NULL,ghost_func,ghostholder[3]);

    srand(time(0));
    
    while(1)
    {
    }

return NULL;
}

int main()
{
    fontfont.loadFromFile("sprites/Emulogic-zrEw.ttf");
    title.setFont(fontfont);
    title1.setFont(fontfont);
    title.setPosition(920,300);
    title1.setPosition(920,400);

    cout<<"STARTING GAME : "<<endl;

    sem_init(&perkeysem,0,2);
    pthread_create(&ui_thread,NULL,ui_func,NULL);
    pthread_create(&ghost_control_thread,NULL,ghost_controller_func,NULL);

    while(1)
    {

    }
}


// read write on ghosts / player movement -> mutex
// if power pellet -> powerup -> koi aur power pellet na khaye
// 