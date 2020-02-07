//read process file in while it is not at the end 
#include <iostream>
#include <cstddef>
#include <fstream>
#include <queue>
#include <sstream>

const int QUANTUM = 4;

struct Job
{
	int name;
	int arrivalTime;
	int blastTime;
};
//Initialize Job queue
std::queue<Job> jobqueue;

//initialize cpuQueues
std::queue<Job> cpuQueue1;

int main(void)
{
	//Import data
	std::string line;
	
	std::ifstream jobFile("job.txt");
	
	if(jobFile.is_open())
	{
		Job tmp;
		std::string line;
		
		int i = 0;
		char delimiter = ',';
		
		while(!(jobFile.eof()))
		{
			
		
			
			if(i == 0)
			{
				std::getline(jobFile, line, delimiter);
				//std::cout<<line<<std::endl;
				
				int number;
				std::istringstream iss (line);
				iss >> number;
				
				tmp.name = number;
				i++;
			}
			else if(i == 1)
			{
				std::getline(jobFile, line, delimiter);
				//std::cout<<line<<std::endl;
				int number;
				std::istringstream iss (line);
				iss >> number;				
				
				tmp.arrivalTime = number;
				i++;
			}
			else
			{
				std::getline(jobFile, line);
				//std::cout<<line<<std::endl;
				int number;
				std::istringstream iss (line);
				iss >> number;				
				
				tmp.blastTime = number;
				jobqueue.push(tmp);
				i = 0;
			}
		}
	}
	else
	{
		std::cout<<"job.txt failed to open"<<std::endl;
		return -1;
	}
	//Close file
	jobFile.close();
	//////////////////////////////////////////////////////////
	

	
	
	

	// Total Processes cycle counter
	int counter = 0;
	
	//populate cpuQueue1
	while(jobqueue.front().arrivalTime <= counter)
	{
		cpuQueue1.push(jobqueue.front());
		jobqueue.pop();
	}
	
	
	

	int timeSlice = 0; //tracks usage of time slice
	
	//Proccess data
	while(!jobqueue.empty() || !cpuQueue1.empty()) //While there are still jobs in jobqueue or cpuQueue1 has jobs
	{

		//process next job while blasttime is greater than 0 and time quantum is not used up
		while(cpuQueue1.front().blastTime > 0 && timeSlice <= QUANTUM) //while blastTime is not over and timeSlice is not used up 
		{
			//Process: decrement blasttime by 1
			cpuQueue1.front().blastTime = cpuQueue1.front().blastTime -1;
			
			//increment time counter and timeSlice
			counter++;
			timeSlice++;
			
			//Check for all new jobs
			while(jobqueue.front().arrivalTime <= counter && !jobqueue.empty()) //while the arrival time of first element is le the counter and the queue is not empty
			{
				cpuQueue1.push(jobqueue.front());
				jobqueue.pop();
			}
		}
			
		//print results of run
		
		if(cpuQueue1.front().blastTime == 0)//job completed
		{
			//print:  name, completionTime (counter), and Finished?? Check assignment sheet
			std::cout<<"Job "<<cpuQueue1.front().name<<", scheduled for "<<timeSlice<<"ms, completed"<<std::endl;
			cpuQueue1.pop(); //remove job from queue
		}
		else
		{
			//print name, completionTime (counter)?? Check assignment sheet
			std::cout<<"Job "<<cpuQueue1.front().name<<", scheduled for "<<timeSlice<<"ms,"<<std::endl;
			//Place job in back of queue and remove from front
			cpuQueue1.push(cpuQueue1.front());
			cpuQueue1.pop();
		}
		timeSlice = 0;	
	}
	std::cout<<"Total CPU Cycles: "<<counter - 1<<std::endl;
}
