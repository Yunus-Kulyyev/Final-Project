/**
Yunus Kulyyev
15-May-2016
Description: Generic Algorithm with robots
improving their ability to gather batteries
from random spots on the map
All rights reserved
Copyright © 2016, Yunus Kulyyev
**/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//Class of Object represents Robots. Robots position will be at 55
class object
{
public:
    int power;                 //Stores the battery power of robots
    int counterOfBatteries;    //Number of gathered batteries
    int totalPower;            //Stores max reached power
    int numSteps;              //Number of steps
    int behaviour[40];         //Stores counterBehav
    int counterBehav;          //Direction of step

    //Constructor to set the variables to default NULL values
    object()
    {
        power = 5;            //Every robots starts with initial five power
        totalPower = 5;
        counterBehav = 0;
        counterOfBatteries = 0;
        numSteps = 0;
        for (int x=0; x<40; x++)
        {
            behaviour[x] = 0;
        }
    }

    //Restores all values of robots to default initial values
    void restart()
    {
        power = 5;
        totalPower = 5;
        counterBehav = 0;
        counterOfBatteries = 0;
        numSteps = 0;
        for (int x=0; x<40; x++)
        {
            behaviour[x] = 0;
        }
    }

    //Stores steps inside of a behaviour
    void genetics(int steps)
    {
        behaviour[counterBehav]=steps;
        counterBehav++;
    }

    //Displays objects max number of gathered batteries and max power
    void display ()
    {
        cout<<"Batteries ="<<counterOfBatteries<<" power= "<<totalPower<<endl;
    }

    //Returns the value of a power
    int life()
    {
        return power;
    }

    //Returns the values of a number of batteries
    int batteryReturn()
    {
        return counterOfBatteries;
    }

     //If robots gets batteries
    void gotBattery()
    {
        power=power+5;             //Adds five to the power
        numSteps=numSteps+1;       //Adds one to the number of steps
        if (numSteps == 40)        //If number of moves equals 40, then robots has to stop
        {
            power=0;
        }
        totalPower=totalPower+5;
        counterOfBatteries=counterOfBatteries+1;
    }

     //If robots steps into an empty cell
    void loseLife()
    {
        power=power-1;            //Subtracts one from the power
        numSteps=numSteps+1;
        if (numSteps == 40)
        {
            power=0;
        }
    }

    //If robots hits the wall
    void wallHit()
    {
        power=power-3;          //Minus three from power
        numSteps=numSteps+1;
        if (numSteps == 40)
        {
            power=0;
        }
    }
};



//Class of the room
class world
{
public:
    int room[10][10];      //Ten to Ten two dimensional map
    int batteries[40];     //Max number of batteries that can be collected
    int increment;

    //CONSTRUCTOR for the world values
    world()
    {
        increment = 0;
        for (int x=0; x<40; x++)
        {
            batteries[x]=rand()%99;
        }

        for (int x=0; x<10; x++)   //creates a 10x10 room with values from 0 to 199
        {
            for (int y=0; y<10; y++)
            {
                room[x][y]=increment;
                increment++;
            }
        }
    }

     //Function if needed can display the map
    int display()
    {
        for (int x=0; x<10; x++)
        {
            for (int y=0; y<10; y++)
            {
                if (x==0)
                {
                    cout<<room[x][y]<<"  ";
                }
                else
                    cout<<room[x][y]<<" ";
            }
            cout<<endl;
        }
    }

    //CHECKS IF THE ROBOTS POSITION MATCHES BATTERIES POSITION
    int awards (int position)
    {
        int notMatch= -1;
        for (int x=0; x<40; x++)
        {
            //If position of a robot matches the position of a battery, return robots position as an approval
            if (batteries[x] == position)
            {
                return position;
            }
        }
        return notMatch;           //If it did not match, returns -1
    }
};


//INITIALIZATION OF MAIN
int main()
{
    srand(time(NULL));         //Seeds random number generator

    system("COLOR 0A");        //For windows users, green terminal

    object robots[200];        //Declaration of 200 objects named robots
    world room;                //Declaration of a map called room

//SETS THE VALUES AND CHECKS THE PERFORMANCE OF ROBOTS
    for (int x=0; x<200; x++)     //Loop for all 200 robot objects
    {
        int initialPosition = 55;     //Initial position of a robots on map at the beginning of every round

        while (robots[x].life() > 0)  //Loops until power of robots reaches zero
        {
            int movement=rand()%3;  //Random number between 0-3

            if (movement == 0)
            {
                robots[x].genetics(0);     //Saves info about in which direction robot moved
                initialPosition=initialPosition+10;         //MOVES UP
                if (initialPosition >= 90)                  //Hits bottom wall
                {
                    robots[x].wallHit();
                }
                else if (room.awards(initialPosition) == initialPosition)   //If true, means robot got battery
                {
                    robots[x].gotBattery();
                }
                else
                    robots[x].loseLife();                                   //Else robot loses life
            }
            else if (movement == 1)
            {
                robots[x].genetics(1);
                initialPosition=initialPosition-10;         //MOVES DOWN
                if (initialPosition <= 9)
                {
                    robots[x].wallHit();
                }
                else if (room.awards(initialPosition) == initialPosition)
                {
                    robots[x].gotBattery();
                }
                else
                    robots[x].loseLife();
            }
            else if (movement == 2)
            {
                robots[x].genetics(2);
                int stop=0;
                initialPosition=initialPosition-1;          //MOVES LEFT
                for (int g=0; g<10; g++)
                {
                    if (initialPosition == g*10)
                    {
                        robots[x].wallHit();
                        stop = 1;
                    }
                }
                if (room.awards(initialPosition) == initialPosition && stop == 0)
                {
                    robots[x].gotBattery();
                }
                else if (stop == 0)
                    robots[x].loseLife();
            }
            else if (movement == 3)
            {
                robots[x].genetics(3);
                int stop=0;
                initialPosition=initialPosition+1;          //MOVES RIGHT
                for (int g=0; g<10; g++)
                {
                    if (initialPosition == g*10+9)
                    {
                        robots[x].wallHit();
                        stop=1;
                    }
                }
                if (room.awards(initialPosition) == initialPosition &&  stop == 0)
                {
                    robots[x].gotBattery();
                }
                else if (stop == 0)
                    robots[x].loseLife();

            }
        }
    }

    int highToLow[200];
    int temp=0;
    int placeHolder[200];
    double average;

    for (int x=0; x<200; x++)
    {
        highToLow[x]=robots[x].batteryReturn();
        average=average+highToLow[x];
    }

    double initNum = average/200.0;
    //Calculates the average for the first generation
    cout<<endl<<"Average Batteries for the generation #1 = "<<average/200.0;



    for (int x=0; x<200; x++)
    {
        placeHolder[x]=x;
    }
    //Bubble sorting to sort robots from lowest number of batteries to the highest
    for(int i=0; i<=200; i++)
    {
        for(int j=0; j<199; j++)
        {
            if(highToLow[j] > highToLow[j+1])
            {
                temp = highToLow[j];
                highToLow[j]=highToLow[j+1];
                highToLow[j+1]=temp;
                temp = placeHolder[j];
                placeHolder[j]=placeHolder[j+1];
                placeHolder[j+1]=temp;
            }
        }
    }

    for (int x=0; x<100; x++)
    {
        //First 100 robots with the lowest number of batteries gets refreshed
        for (int g=0; g<200; g++)
            if (robots[g].counterOfBatteries == robots[placeHolder[x]].counterOfBatteries)
            {
                robots[g].restart();
            }
    }

     //Following functions passes the characteristics of a successful robots to the other 100 refreshed generations
    for (int x=0; x<100; x++)
    {
        for (int i=0; i<20; i++)
        {
            robots[placeHolder[x]].behaviour[i]=robots[placeHolder[200-x]].behaviour[i];
        }
        for (int g=20; g<40; g++)
        {
            robots[placeHolder[x]].behaviour[g]=robots[placeHolder[199-x]].behaviour[g];
        }
    }

//SETS THE VALUES AND CHECKS THE PERFORMANCE OF ROBOTS
    int generation=0;
    //Loop for the following generations of robots
    while (generation != 1000)
    {
        for (int x=0; x<200; x++)
        {
            int initialPosition = 55;
            int addsUp=0;
            while (robots[x].life() > 0)
            {
                int movement=robots[x].behaviour[addsUp];
                if (movement == 0)
                {
                    robots[x].genetics(0);
                    initialPosition=initialPosition+10;         //MOVES UP
                    if (initialPosition >= 90)
                    {
                        robots[x].wallHit();
                    }
                    else if (room.awards(initialPosition) == initialPosition)
                    {
                        robots[x].gotBattery();
                    }
                    else
                        robots[x].loseLife();
                }
                else if (movement == 1)
                {
                    robots[x].genetics(1);
                    initialPosition=initialPosition-10;         //MOVES DOWN
                    if (initialPosition <= 9)
                    {
                        robots[x].wallHit();
                    }
                    else if (room.awards(initialPosition) == initialPosition)
                    {
                        robots[x].gotBattery();
                    }
                    else
                        robots[x].loseLife();
                }
                else if (movement == 2)
                {
                    robots[x].genetics(2);
                    int stop=0;
                    initialPosition=initialPosition-1;          //MOVES LEFT
                    for (int g=0; g<10; g++)
                    {
                        if (initialPosition == g*10)
                        {
                            robots[x].wallHit();
                            stop = 1;
                        }
                    }
                    if (room.awards(initialPosition) == initialPosition && stop == 0)
                    {
                        robots[x].gotBattery();
                    }
                    else if (stop == 0)
                        robots[x].loseLife();
                }
                else if (movement == 3)
                {
                    robots[x].genetics(3);
                    int stop=0;
                    initialPosition=initialPosition+1;          //MOVES RIGHT
                    for (int g=0; g<10; g++)
                    {
                        if (initialPosition == g*10+9)
                        {
                            robots[x].wallHit();
                            stop=1;
                        }
                    }
                    if (room.awards(initialPosition) == initialPosition &&  stop == 0)
                    {
                        robots[x].gotBattery();
                    }
                    else if (stop == 0)
                        robots[x].loseLife();

                }
                addsUp++;
            }
        }
        generation++;

        average=0;
        for (int x=0; x<200; x++)
        {
            highToLow[x]=robots[x].batteryReturn();
            average=average+highToLow[x];
        }

        //Calculates the average of a generation
        cout<<endl<<"Average Number of Batteries for the generation #"<<generation+2<<" = "<<average/200.0;

        for (int x=0; x<200; x++)
        {
            placeHolder[x]=x;
        }
        for(int i=0; i<=200; i++)
        {
            for(int j=0; j<199; j++)
            {
                if(highToLow[j] > highToLow[j+1])
                {
                    temp = highToLow[j];
                    highToLow[j]=highToLow[j+1];
                    highToLow[j+1]=temp;
                    temp = placeHolder[j];
                    placeHolder[j]=placeHolder[j+1];
                    placeHolder[j+1]=temp;
                }
            }
        }


        for (int x=0; x<100; x++)
        {
            for (int g=0; g<200; g++)
                if (robots[g].counterOfBatteries == robots[placeHolder[x]].counterOfBatteries)
                {
                    robots[g].restart();
                }
        }

        for (int x=0; x<100; x++)
        {
            for (int i=0; i<20; i++)
            {
                robots[placeHolder[x]].behaviour[i]=robots[placeHolder[200-x]].behaviour[i];
            }
            for (int g=20; g<40; g++)
            {
                robots[placeHolder[x]].behaviour[g]=robots[placeHolder[100+x]].behaviour[g];
            }
        }

        //To boost the speed of change,20 of robots movement will get random directions
        for (int x=0; x<20; x++)
        {
            for (int g=15; g<40; g++)    //Mutated Robots with unique genome
            {
                robots[placeHolder[x]].behaviour[g]=rand()%4;
            }
        }
    }


    //Calculates the average for the last generation
    double finalNum=average/200.0;

    //Calculates the performance difference between first generation and the last
    double percent=((finalNum*100)/initNum)-100;

    cout<<endl<<endl<<"Increase in ability of robots to gather ";
    cout << "batteries from first generation to the last increased by "<<percent<<"%";


    return 0;
}
