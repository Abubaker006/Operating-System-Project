#include<iostream>
#include<unistd.h>
#include<time.h>
using namespace std;
void orphanprocess() {
		cout << "\t\t\t\t|`````````````````````|\n";
		cout << "\t\t\t\t|*********************|\n";
		cout << "\t\t\t\t|##  Orphan Process ##|\n";
		cout << "\t\t\t\t|*********************|\n";
		cout << "\t\t\t\t|_____________________|\n\n\n";
		int traffic[4];
		srand(time(0));
	int	a = fork();
		if (a > 0)
		{   //Parent process
			cout << "The ID of Sensors is :: " << getpid() << " ." << endl;
			cout << "Checking the Status of sensors\n";
			for (int i = 0; i < 4; i++)
			{


				cout << "The sensors are Detecting the traffic in the Signal-" << i + 1 << " : ";
				traffic[i] = (1 + rand() % 50);
				cout << traffic[i] << endl;

			}
			
			cout << "After detecting all the tarffic signals, sensor is terminated (Parent process)" << endl;
			exit(0);
			
		}
		else
		{   //child process
			cout << "The Signal ID is:: " << getpid() << endl;
			cout<<" & its Sensor (parent) ID is :: " << getppid() << " ." << endl;
			for (int i = 0; i < 4; i++) {
				if (traffic[i] > 0) {
					cout << "Traffic Found on a Signal " << i + 1 << " SIGNAL IS ON" << endl;
				}
				else {
					cout << "There is no traffic on signal " << i + 1 << endl;
				}
			}
			cout << "After crossing all the traffic,Again signal is waiting for the sensor signal (Child process)" << endl;
			sleep(20);
			
			
		}
	}
	
	
int main()
{
    orphanprocess();
	    return 0;
	}