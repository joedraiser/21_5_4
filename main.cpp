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
        y++;
        if(this->valid())
            return true;
        else
        {
            y--;
            return false;
        }
    }

    bool bottom()
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

player P, E[5];

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

    return 0;
}
