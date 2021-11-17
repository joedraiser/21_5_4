#include <iostream>
#include <ctime>

struct position
{
    int x, y;

    bool valid()
    {
        if(x>=0&&x<40&&y>=0&&y<40)
            return true;
        else
            return false;
    }

    bool left()
    {
        x--;
        if(this->valid())
            return true;
        else
        {
            x++;
            return false;
        }
    }

    bool right()
    {
        x++;
        if(this->valid())
            return true;
        else
        {
            x--;
            return false;
        }
    }

    bool top()
    {
        y--;
        if(this->valid())
            return true;
        else
        {
            y++;
            return false;
        }
    }

    bool bottom()
    {
        y++;
        if(this->valid())
            return true;
        else
        {
            y--;
            return false;
        }
    }

    bool operator==(position another)
    {
        if(x==another.x&&y==another.y)
            return true;
        else
            return false;
    }
};

struct player
{
    std::string name;
    int health;
    int armour;
    int damage;

    position pos;
};

bool attack(player* attacker, player* defender)
{
    defender->armour-=attacker->damage;
    if(defender->armour<0)
    {
        defender->health+=defender->armour;
        defender->armour=0;
    }

    if(defender->health>0)
    {
        return true;
    }
    else
        return false;
}

player P, E[5];

bool playerCollidedWithEnemy()
{
    for(int i=0;i<5;i++)
    {
        if(P.pos==E[i].pos)
        {
            if(attack(&P, &E[i]))
            {
                std::cout << "player collided with " << E[i].name << " and " << E[i].name << " survived with " << E[i].health << " and " << E[i].armour << std::endl;
                return true;
            }
            else
            {
                std::cout << "player collided with " << E[i].name << " and " << E[i].name << " was KIA\n";
                E[i].pos.x=-1;
                E[i].pos.y=-1;
                return true;
            }
        }
    }
    return false;
}

void enemyDoRandomMove(player* enemy)
{
    position temp=enemy->pos;

    int move = rand()%4;
    switch (move)
    {
        case 0:
            temp.left();
            break;
        case 1:
            temp.right();
            break;
        case 2:
            temp.top();
            break;
        case 3:
            temp.bottom();
            break;
    }

    if(temp==P.pos)
    {
        if(attack(enemy, &P))
        {
            std::cout << enemy->name << " attacked player and player survived with " << P.health << " health and " << P.armour << " armour left" << std::endl;
            return;
        }
        else
        {
            std::cout << enemy->name << " attacked player and player was KIA\n";
            return;
        }
    }

    for(int i=0;i<5;i++)
    {
        if(enemy!=&E[i])
            if(temp==E[i].pos)
                return;
    }

    enemy->pos=temp;
}


void displayField()
{
    position temp;

    for(temp.y=0;temp.y<40;temp.y++)
    {
        for(temp.x=0;temp.x<40;temp.x++)
        {
            if(temp==P.pos)
                std::cout << " P";
            else if(temp==E[0].pos||temp==E[1].pos||temp==E[2].pos||temp==E[3].pos||temp==E[4].pos)
                std::cout << " E";
            else
                std::cout << " *";
        }
        std::cout << std::endl;
    }
}

bool allEnemiesAreDead()
{
    position deadPos;
    deadPos.x=-1;
    deadPos.y=-1;

    if(E[0].pos==deadPos&&E[1].pos==deadPos&&E[2].pos==deadPos&&E[3].pos==deadPos&&E[4].pos==deadPos)
        return true;
    else
        return false;
}

int main()
{
    std::srand(std::time(0));

    std::cout << "Input players name: ";
    std::cin >> P.name;
    std::cout << "Input players health: ";
    std::cin >> P.health;
    std::cout << "Input players armour: ";
    std::cin >> P.armour;
    std::cout << "Input players damage: ";
    std::cin >> P.damage;

    std::cout << "Input players position, x and y: ";
    do
    {
        std::cin >> P.pos.x >> P.pos.y;
        if(P.pos.valid())
            break;
        else
            std::cout << "Invalid position input again: ";
    }
    while(true);

    for(int i=0;i<5;i++)
    {
        E[i].name="Enemy #1";
        E[i].name[7]='1'+i;
        E[i].health=rand()%100+50;
        E[i].armour=rand()%50;
        E[i].damage=rand()%15+15;

        E[i].pos.x=rand()%40;
        E[i].pos.y=rand()%40;



        while(true)
        {
            for(int j=0;j<i;j++)
            {
                if(E[i].pos==E[j].pos||E[i].pos==P.pos)
                {
                    E[i].pos.x=rand()%40;
                    E[i].pos.y=rand()%40;
                    j=0;
                }
            }
            break;
        }
    }

    displayField();

    std::string input;
    position temp;

    while(P.health>0&&!allEnemiesAreDead())
    {
        std::cout << "Input your move: ";
        std::cin >> input;

        if(input=="left")
        {
            P.pos.left();
            if(playerCollidedWithEnemy())
                P.pos.right();
        }
        else if(input=="right")
        {
            P.pos.right();
            if(playerCollidedWithEnemy())
                P.pos.left();
        }
        else if(input=="top")
        {
            P.pos.top();
            if(playerCollidedWithEnemy())
                P.pos.bottom();
        }
        else if(input=="bottom")
        {
            P.pos.bottom();
            if(playerCollidedWithEnemy())
                P.pos.top();
        }
        else
            continue;


        for(int i=0;i<5;i++)
        {
            if(E[i].pos.x!=-1&&E[i].pos.y!=-1)
                enemyDoRandomMove(&E[i]);
        }
        displayField();
    }

    if(P.health>0)
        std::cout << "Player won";
    else
        std::cout << "Player lose";

    return 0;
}
