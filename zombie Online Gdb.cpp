#include <iostream>
#include <unistd.h>
#include <string>
#include <time.h>
#include <climits>

using namespace std;
int sensors()
{
    srand(time(0));
    int numberofVehicles=(1+rand()%50);
    cout<<"The Sensors are Detecting for traffic";
    cout<<endl;
    cout<<"The Sensor have Detected that the traffic at this signal is :: "<<numberofVehicles<<endl;
    return numberofVehicles;
}
void zombieProcess()
{
    
    int a;
    int numberofVehicles=0;
    int vehiclesLeft;
    bool done=false;
    a=fork();
    if(a>0)
    {
        cout<<"The ID of Sensors is :: "<<getpid()<<" ."<<endl;
        cout<<"Checking the Status of sensors\n";
        numberofVehicles=sensors();
        //vehiclesLeft=numberofVehicles/2;
        cout<<"Status Checked.\n";
        sleep(10);
        cout<<"The half of the traffic is Stuck (zombieProcess) at the signal "<<numberofVehicles/2<<endl;
    }
    else
    {
        cout<<"The Signal ID is:: "<<getpid()<<" & its Sensor (parent) ID is :: "<<getppid()<<" ."<<endl;
        cout<<"The Vehicles are leaving the Signal\n";
        while(1)
        {
            
            numberofVehicles--;
            if(numberofVehicles==(numberofVehicles/2))
            { break;
            }
        }
        exit(0);
    }
}

int main()
{
    cout << "\t\t\t\t|`````````````````````|\n";
		cout << "\t\t\t\t|*********************|\n";
		cout << "\t\t\t\t|## Zombie Process  ##|\n";
		cout << "\t\t\t\t|*********************|\n";
		cout << "\t\t\t\t|_____________________|\n\n\n";
    for(int i=0;i<4;i++)
    {
        zombieProcess();
        cout<<endl<<endl;
    }
    
    return 0;
}
