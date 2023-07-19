	// Zombie And Orphan Are implemented in separate files-online because of having fork function
	//Mam this code is written and compiled on visual studio profession its better to use visual studio 

#include <iostream>
#include <Windows.h>
#include <string>
#include <time.h>
#include<queue>

#define SIZE 4

using namespace std;
class OperatingSystem
{
private:
	//for whole system
	         
	int numberofVehicles;
	queue<int> suspendList;
	char a; char b;//  for loading bar
	//for zombie and 
	int number;
	int traffic[SIZE] = {};
	//for orphan process
	
	//for IPC
	//its variables is specified in the functions
	//for scheduling algorithm
	int numberOfSignal;
	double timeQuantum;
	double Time;
	//for signals 
	double arrivalTimeofSignal[SIZE] = {};
	double burstTimeofSignal[SIZE]={};
	double waitingTimeofSignal[SIZE] = {};
	double turnAroundTimeofSignal[SIZE] = {};
	double avgWTimeOfsignal;
	double avgTatTimeofSignal;
	double burstTime[5] = {};
	int array[2][5] = {};
	//for vehicles
	double *arrivalTime;  // not used
	double *waitingTime;
	double *turnAroundTime;
	//double  *burstTime;
	double avgWtime;
	double avgTatime;
	// for producer consumer example of process synchronization
	int mutexForSignal;
	int full;
	int empty;
	int x;

public:
	
	OperatingSystem(int value)
	{
		for (int i = 0; i < SIZE; i++)
		{
			arrivalTimeofSignal[i] = value;
			burstTimeofSignal[i] = value;
			waitingTimeofSignal[i] = value;
			turnAroundTimeofSignal[i] = value;
			traffic[i] = value;
		}

		
		number = value;
		
		avgWTimeOfsignal = value;
		avgTatTimeofSignal = value;
		//not used till now
		arrivalTime = NULL;
		waitingTime = NULL;
		turnAroundTime = NULL;
	//	burstTime = NULL;
		avgWtime = value;
		avgTatime = value;
		// till here
		a = 219;
		b = 219;
		numberofVehicles = value;
		timeQuantum = value;
		Time = value;
		numberOfSignal = value;

		mutexForSignal = 0;
		 full = 0;
		empty = 0;
		 x = 0;
	}
	~OperatingSystem()
	{
		cout << "\t\t\t\t|%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%|" << endl;
		cout << "\t\t\t\t|                       THANK YOU! Comeback Later..                  |" << endl;
		cout << "\t\t\t\t|____________________________________________________________________|" << endl << endl;
	}
	void Ipc()
	{
		cout << "\t\t\t\t|````````````````````````````````````````|\n";
		cout << "\t\t\t\t|****************************************|\n";
		cout << "\t\t\t\t|##  Inter-Process Communication (IPC) ##|\n";
		cout << "\t\t\t\t|****************************************|\n";
		cout << "\t\t\t\t|________________________________________|\n\n\n";
	startIPC:
		cout << "\t\t\t\t\t\tEstablishing IPC\n\n";
		string option;
		cout << "Enter : \n";
		cout << "1 If you want the Sensor to Notify the signal to open something to Signal : \n";
		cout << "2 if you want to Exit\n";
		getline(cin >> ws, option);
		if (option == "1")
		{
			write(); 
		}
		else if (option == "2")
		{
			system("CLS");
		}
		else
		{
			goto startIPC;
		}
	}
	void read(bool end,string buffer,long size) // reader is our signal string buffer instead of char buffer[1128]
	{
		string msg[3];
		msg[0] = "Open The signal.";
		msg[1] = "Close the Signal.";
		msg[2] = "Sensor is turing of.";
		if (buffer == "Open The signal." && size==msg[0].length() && end==1)
		{
			cout << "The Signal is Open..." << endl;
			vehicles();
		}
		else if (buffer == "Close the Signal." && size== msg[1].length() && end==1)
		{
			cout << "Closing The Signal : ";
			for (int j = 0; j < 8; j++) {
				cout << ".";
				Sleep(1000);
			}
			cout << "\n";
		}
		else if (buffer == "Sensor is turing of." && size==msg[2].length() && end==1)
		{
			cout << "Senors  are Turn off, notifying  the Signal : ";
			for (int j = 0; j < 8; j++) {
				cout << ".";
				Sleep(1000);
			}
			cout << "\n";
		}
	}
	void write() //writer is our sensor
	{
	startWriter:
		string buffer=" ";
		long messageSize =0;
		string option;
		cout << "Enter option  of Messages from Sensor to Signal: \n";
		cout << "1-If you want to Open the Signal : \n";
		cout << "2-If you want to Close the Signal : \n";
		cout<< "3-If Sensors is going to Turn off : \n";
		cout << "4-If you want to Exit.\n";
		getline(cin >> ws, option);
		if (option == "1")
		{
			 buffer = "Open The signal.";
			 messageSize = buffer.length();;/*buffer.length()*/;
			read(1, buffer, messageSize);
		}
		else if (option == "2")
		{
			buffer = "Close the Signal.";
			messageSize = buffer.length();
			read(1, buffer, messageSize);
		}
		else if (option == "3")
		{
			buffer = "Sensor is turing of.";
			
			messageSize = buffer.length();
			read(1, buffer, messageSize);
		}
		else if (option == "4")
		{
			system("CLS");
		}
		else
		{
			goto startWriter;
		}
	
	}
	void producer()
	{ //1-50  //1-100
		cout << "Senosrs (producers) are Detecting the traffic:\n";
		mutexForSignal--; //0
		srand(time(0)); //srand=rand
		x = (1 + rand() % 100);  	//the value of traffic in signal is increamented
		if (x >=20)
		{
			full++; //1
			empty--; //0
			mutexForSignal++;
		}
		else if (x < 20)
		{
			cout << "The Signal will Open (consume) when number of vehicles will be more than 20.\n\n";
		}
		
		if (mutexForSignal == 1 && full > 0) 
		{
			consumer();
		}
	}
	void consumer()
	{
		cout << "The amount of Vehicles till now is " << x << " : \n";
		mutexForSignal--; //0
		full--; //0
		empty++; //1
		cout << "The Signal Open";
		for (int j = 0; j < 8; j++) {
			cout << ".";
			Sleep(1000);
		}
		while (1)
		{
			x--;
			if (x == 0)
			{
				break;
			}
		}//
		cout << "Signal Closed,\n";
		cout << "  The Traffic left is :: " << x << endl;
		mutexForSignal++; //1
		cout << "\n\n";
	}
	void ProducerConsumerBinary()  //producer comsumer
	{
	startProdcuerConsumer:
		/*srand(time(0));*/
		full = 0;
		empty = 1;
		x = 0;
			//(1 + rand() % 50);
		mutexForSignal = 1;
		string option;
		cout << "Enter:\n";
		cout << "1-If Sensor Will  Call the Signal and Give Amount of Vehicle:\n"; 
		cout << "2-Or not, and want to Exit.\n";
		getline(cin >> ws, option);
		if (option == "1")
		{
			if (mutexForSignal == 1 && empty > 0)
			{
				producer();   // producer or sensor will be called and it will then call consumer from there
			}
		}
		else if (option == "2")
		{
			system("CLS");
		}
		else {
			goto startProdcuerConsumer;
		}
		
	}

	void Fcfs() //applied on the warden-inspection scenario
	{ // FCFS ALGORITHM IMPLEMENTATION
		cout << "\t\t\t\t|`````````````````````|\n";
		cout << "\t\t\t\t|*********************|\n";
		cout << "\t\t\t\t|     ### FCFS ###    |\n";
		cout << "\t\t\t\t|*********************|\n";
		cout << "\t\t\t\t|_____________________|\n\n\n";
		//string option;
	start2:
		/*cout << "Enter the Number of Vehicles that Were Stopped by the Warden.\n";
		cin >> n;*/
		srand(time(0));
		int n = (1 + rand() % 5);
		cout << "The Number of Cars that the warden has stopped " << n << endl;
		double* waitingTime = new double[n]; //time each vehicle wait to get inspected
		double* turnAroundTime = new double[n]; //time each vehicle spent to get free
		double* burstTime = new double[n];     //time each vehicle should be given according to size

		for (int i = 0; i < n; i++)
		{
			burstTime[i] = (1 + rand() % 120);    //note the burst time is initialized in seconds
		}
		waitingTime[0] = 0;
		for (int i = 1; i < n; i++)
		{
			waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
		}
		for (int i = 0; i < n; i++)
		{
			turnAroundTime[i] = waitingTime[i] + burstTime[i];
		}
		double avgWTime = 0, avgTT = 0; // the avg time spent by each vehicle in the queue.
		for (int i = 0; i < n; i++)
		{
			avgWTime += waitingTime[i];
			avgTT += turnAroundTime[i];
		}
		avgWTime / n;
		avgTT / n;
		for (int i = 0; i < n; i++)
		{
			cout << "\nVehicle-" << i + 1 << "\n(BT)Time Spent by on Inspection-" << burstTime[i] << " (WT)Time Spent on Waiting- " << waitingTime[i] << "  (TT)Time to Finally get inspected- " << turnAroundTime[i] << endl;
		}
		cout << "\nThe Avg Waiting was ::" << avgWTime <<
			"\nThe Avg  Time to get Finally Inspected :: " << avgTT << endl;
		cout << endl << endl;
	}
	void roundRobin()
	{
		cout << "\t\t\t\t|`````````````````````|\n";
		cout << "\t\t\t\t|*********************|\n";
		cout << "\t\t\t\t| ### Round Robin ### |\n";
		cout << "\t\t\t\t|*********************|\n";
		cout << "\t\t\t\t|_____________________|\n\n\n";
		string option;
	
		cout << "There are Total 4 Signals in Total.\n";
  	   //numbers of signals are 4 in a intersection
		start2:
			cout << "Enter:\n";
			cout << "1- If Sensor Notifies that When the Signal is Full:\n";
			cout << "2- IF Sensors dont Notify that when the Signal is Full:\n";
			getline(cin >> ws, option);
			if (option == "1") //if arrival time is known
			{
				cout << "\nThe category and the amount of these Vechicles:\n\n";
				cout << "1-Car (Sedan, etc.)\n2-Truck\n3-Bus\n4-MotorBike\n5-Emergency Vehicle\n6-Other Vehicles (bicycle,skateboard, etc.)\n";
				cout << "\n\n";
				srand(time(0));
				for (int i = 0; i < SIZE; i++)
				{
					for (int i = 0; i < 5; i++)  //category of cars initialized
					{
						array[1][i] = (1 + (rand() % 50));
						//just to know how many vehicles the user entered
					}
					burstTime[0] = array[1][0] / 3;
					burstTime[1] = array[1][1] / 3;
					burstTime[2] = array[1][2] / 3;
					burstTime[3] = array[1][3] / 3;
					burstTime[4] = array[1][4] / 3;
					double TotalBurstTime = 0;
					for (int i = 0; i < 5; i++)
					{
						TotalBurstTime += burstTime[i];
					}
					/*cout << "The Total  the Signal will require to Get Free (Burst Time) is:" << TotalBurstTime<<endl;*/
					burstTimeofSignal[i] = TotalBurstTime;
					
					arrivalTimeofSignal[i] = 1 + (rand() % 15);
				}
					for (int i = 0; i < SIZE - 1; i++)
					{
						for (int j = 0; j < SIZE - i - 1; j++)
						{
							if (arrivalTimeofSignal[j] > arrivalTimeofSignal[j + 1])
							{
								swap(arrivalTimeofSignal[j], arrivalTimeofSignal[j + 1]);
								swap(burstTimeofSignal[j], burstTimeofSignal[j + 1]);
							}
						}
					}
				
			}
			else if (option == "2")   //if arrival time is not known
			{
				cout << "\nThe category and the amount of these Vechicles:\n\n";
				cout << "1-Car (Sedan, etc.)\n2-Truck\n3-Bus\n4-MotorBike\n5-Emergency Vehicle\n6-Padesterian (bicycle,skateboard, etc.)\n";
				cout << "\n\n";
				srand(time(0));
				for (int i = 0; i < SIZE; i++)
				{
					for (int i = 0; i < 5; i++)  //category of cars initialized
					{
						array[1][i] = (1 + (rand() % 50));
						//just to know how many vehicles the user entered
					}
					burstTime[0] = array[1][0] / 3;
					burstTime[1] = array[1][1] / 3;
					burstTime[2] = array[1][2] / 3;
					burstTime[3] = array[1][3] / 3;
					burstTime[4] = array[1][4] / 3;
					double TotalBurstTime = 0;
					for (int i = 0; i < 5; i++)
					{
						TotalBurstTime += burstTime[i];
					}
					cout << "The Total  Burst Time is:" << TotalBurstTime<<endl;
					burstTimeofSignal[i] = TotalBurstTime;
					arrivalTimeofSignal[i] = 0;
				}
			}
			else
			{
				cout << "Invalid input.\n";
				goto start2;
			}
			/*cout << "Enter the Time Quantum of Signals (time that want each Signal To Open):";
			cin >> timeQuantum;*/ 
			timeQuantum = 2;// srand(time(0)) and 1 + rand() % 9           //time quantum taken as input
			double newArray[SIZE];
			for (int i = 0; i < SIZE; i++)  // assigning new array the burst time taken
			{
				newArray[i] = burstTimeofSignal[i];
			}
			bool done = false;
			while (!done)   //calculating the waiting time of signal
			{
				done = true;
				for (int i = 0; i < SIZE; i++)
				{

					if (newArray[i] > 0)
					{
						done = false;
						if (newArray[i] > timeQuantum)
						{
							Time = Time + timeQuantum;
							newArray[i] = newArray[i] - timeQuantum;
						}
						else {
							Time = Time + newArray[i];
							waitingTimeofSignal[i] = Time - burstTimeofSignal[i];
							newArray[i] = 0;
						}
					}
					else
					{
						// add ni hoga
						break;
 					}

				}
			}
			for (int i = 0; i < SIZE; i++) //turn around time of signal
			{
				turnAroundTimeofSignal[i] = burstTimeofSignal[i] + waitingTimeofSignal[i];
			}
			for (int i = 0; i < SIZE; i++)  //avg tat and Wt of Signal
			{
				avgWTimeOfsignal += waitingTimeofSignal[i];
				avgTatTimeofSignal += turnAroundTimeofSignal[i];
			}
			avgWTimeOfsignal = avgWTimeOfsignal / SIZE;
			avgTatTimeofSignal = avgTatTimeofSignal / SIZE;
			
			
			for (int i = 0; i < 4; i++)
			{
				if (burstTimeofSignal[i] > 0)
				{
					cout << "\n";
					cout << "\t\tNumber of Vehicles and thier Catergory in the Signal-" << i + 1 << " :\n\n";
					vehicles();
				}
				else
				{
					cout << "\n";
					cout << "\tAs the burst-time of Signal (Process) is lesser than zero so it is not in Queue.\n";
				}
			}
			
			cout << "\n\nWait for 2 Seconds Showing results : \n";
			system("PAUSE");
			system("CLS");
			printFunction();
    }
	void vehicles()   //assigns vehicles to every signal 
	{
		int Amount[6]; // to chng
		srand(time(0)); // srand = rand  //0,1,2
		for (int i = 0; i < 6; i++)
		{
			Amount[i]=(1+rand()%50);
		}
		int number=0;
		for (int i = 0; i < 6; i++)
		{
			number = number + Amount[i];
		}

		 numberofVehicles = number;
		for (int i = 0; i < 6; i++)
		{
			if (i == 0)
			{
				cout << "Cars - ";
			}
			else if (i == 1)
			{
				cout << "Truck - ";
			}
			else if (i == 2)
			{
				cout << "BUS - " ;
			}
			else if (i == 3)
			{
				cout << "MotorBike - ";
			}
			else if (i == 4)
			{
				cout << "Emergency Vehicle - " ;
			}
			else if (i == 5)
			{
				cout << "Other Vehicles - ";
			}
			cout << Amount[i] << endl;
		}
		bool greenLight = true;
		while (greenLight != false)
		{
			numberofVehicles--;
		
			if (numberofVehicles==0)
			{
				greenLight = false;

				break;
			}
		}
		cout << "Total Number of Vehicles :: " << number<<"..\n";
		loadingBar(number);
	}
	void loadingBar(int value) //just to tell user that vehicles are crossing through signal now by loading bar
	{                          // shows total amount ---------- left amount
		cout << endl;
		cout << "\t\t\t\t"<<value << "-";
		// Print initial loading bar
		for (int i = 0; i < 26; i++)
		{
			cout << a;
			Sleep(40);
		}
		cout << " -0" << "\n";
	}
	//void printFunctionFcfs()  //function to print fcfs
	//{
	//	for (int i = 0; i < SIZE; i++)
	//	{
	//		cout << "\nSignal-" << i + 1<<"\nArrival Time : "<<arrivalTimeofSignal[i]<< "  Burst Time of : " << burstTimeofSignal[i]<< "   Waiting Time Of Signal-" << waitingTimeofSignal[i] << "  Turn Around Time Signal-" << turnAroundTimeofSignal[i] << endl;
	//	}
	//	cout << "\nAverage Turn Around Time of Signal :" << avgTatTimeofSignal <<
	//		"\nAverage Waiting Time of Signal : " << avgWTimeOfsignal << endl;
	//	cout << endl << endl;
	//}
	void printFunction()  //function to print round robin
	{
		for (int i = 0; i < SIZE; i++)
		{
			cout << "\nSignal-" << i + 1 <<"\n (AT)Filling Time of Signal-"<<arrivalTimeofSignal[i]<<"  (BT)Time Signal Needs-" << burstTimeofSignal[i] <<" (TQ)Signal Opened For-"<<timeQuantum<< "  (WT)Time Signal Waits-" << waitingTimeofSignal[i] << " (TT)Time Signal Took-" << turnAroundTimeofSignal[i]<<endl;
		}
		cout << "\nAverage Time Signal Took to Get Free ::" << avgTatTimeofSignal <<
			"\nAverage Signal Had to Wait :: " << avgWTimeOfsignal << endl;
		cout << endl<<endl;
	}
	void repeatetionChecker(int value)  // to assure values are of integer type
	{
		while (!cin.good())
		{
			cout << "Invalid Input, Enter value again.\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> value;
		}
		return;
	}
};
int max_parking_spaces = 50;
int numberOfCars=0;
class Semaphore {
public:
	int value;
	Semaphore(int initial) : value(initial) {}

	void wait() {
		bool done = false;
		while (!done)
		{
			value--;
			if ((max_parking_spaces - numberOfCars) == value)
			{
				cout << "The Given Cars are alloted to the Parking Space\n";
				max_parking_spaces = value;
				done = true;
			}
		}

	}

	void signal() {
		value++;
		max_parking_spaces = value;
	}
};

class Parking {
private:
	Semaphore parking_spaces;

public:
	Parking() : parking_spaces(max_parking_spaces)
	{
	}

	void parkVehicle() {
		//numberOfCars=1;
	start:
		cout << "Enter the Number of Cars (1-50):";
		cin >> numberOfCars;
		if (numberOfCars <= max_parking_spaces)
		{
			parking_spaces.wait();
			cout << "Vehicle parked. Remaining Parking Spaces::  " << parking_spaces.value << endl << endl;
		}
		else {
			cout << "Enter the Amount Again because there are only 50 parking spaces or the parking spaces are occupied.\n";
			goto start;
		}

	}

	void exitVehicle() {
		parking_spaces.signal();
		cout << "Vehicle exited parking. Parking Space Freed, Available :: " << parking_spaces.value << endl;
	}
};
int main()
{

	cout << "\t\t\t\t|%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%|\n";
	cout << "\t\t\t\t|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|\n";
	cout << "\t\t\t\t|           Smart Traffic Management System                |\n";
	cout << "\t\t\t\t|__________________________________________________________|\n";
	cout << "\t\t\t\t|__________________________________________________________|\n\n";
	OperatingSystem obj1(0);
	string option=" ";
	bool breaker = false;
	while (breaker!=true)
	{
		cout <<"Enter number which Algorithm to Apply:\n";
		cout << "1-For IPC (Inter Process Communication).\n";
		cout <<"2-For FCFS (First Come First Serve).\n";
		cout <<"3-For Round Robin Algorithm).\n";
		cout <<"4-For Producer Consumer Binary : \n";
		cout << "5-For Counting Semaphore:\n";
		cout <<"6-To Exit.\n";
		getline(cin >> ws, option);
		if (option == "1")
		{
			obj1.Ipc();
		}
		else if (option == "2")
		{
			system("CLS");
			obj1.Fcfs();
		}
		else if (option == "3")
		{
			system("CLS");
			
			obj1.roundRobin();
		}
		else if (option=="4")
		{
			system("CLS");
			obj1.ProducerConsumerBinary();
		
		}
		else if (option == "5")
		{

		Counting:
		 static int i = 1;
		 cout << "The value of I in this case is:" << i << endl;
			Parking parking;
			string option;
			cout << "Enter:\n1-For Parking the Vehicle.\n";
			cout << "2-Removing the Vehicle.\n";
			getline(cin >> ws, option);
			if (option == "1")
			{
				i++;
				parking.parkVehicle();
				
			}
			else if (option == "2" && i > 1)
			{
				parking.exitVehicle();
			}
			else if (i <= 1 && option == "2") {
				cout << "No Vehice is parked so you cannot Exit any, First Park Them.\n";
				parking.parkVehicle();
				i++;
			}
			else if (option == "3") {
				system("clear");
			}
			else {
				goto Counting;
			}
		}
		else if (option == "6")
		{
			system("CLS");
			cout << "Exiting";
			for (int i = 0; i < 3; i++)
			{
				Sleep(10);
				cout << ".";
			}
			cout << "\n";
			Sleep(300);
			system("CLS");
			breaker=true;
		}
		else {
			cout << "Invalid Input.\n";
		}
	}
	return 0;
}
