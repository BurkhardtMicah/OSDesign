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

std::queue<Job> waitqueue;

//initialize cpuQueues
std::queue<Job> cpuQueue1;
std::queue<Job> cpuQueue2;
std::queue<Job> cpuQueue3;
std::queue<Job> cpuQueue4;

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
	int j = 0;
	
	while(jobqueue.front().arrivalTime <= counter)
	{
		waitqueue.push(jobqueue.front());
		jobqueue.pop();
	}	
	
	// initial population of cpuQueues. populate each with 1 job
	cpuQueue1.push(waitqueue.front());
	waitqueue.pop();

	cpuQueue2.push(waitqueue.front());
	waitqueue.pop();			

	cpuQueue3.push(waitqueue.front());
	waitqueue.pop();			

	cpuQueue4.push(waitqueue.front());
	waitqueue.pop();			
	

	int timeSlice1 = 0; //tracks usage of time slice
	int timeSlice2 = 0;
	int timeSlice3 = 0;
	int timeSlice4 = 0;
	
	//Proccess data while any queue still has jobs in it
	while(!jobqueue.empty() || !waitqueue.empty() || !cpuQueue1.empty() || !cpuQueue2.empty() || !cpuQueue3.empty() || !cpuQueue4.empty()) //While there are still jobs in jobqueue or cpuQueue1 has jobs
	{
		//Process: decrement blasttime by 1
		cpuQueue1.front().blastTime = cpuQueue1.front().blastTime -1;
		cpuQueue2.front().blastTime = cpuQueue2.front().blastTime -1;
		cpuQueue3.front().blastTime = cpuQueue3.front().blastTime -1;
		cpuQueue4.front().blastTime = cpuQueue4.front().blastTime -1;
		
		//increment time counter and timeSlice1
		counter++;
		
		timeSlice1++;
		timeSlice2++;
		timeSlice3++;
		timeSlice4++;
		
		
		//Get all new jobs from job queue if it is not empty
		if(!jobqueue.empty())
		{
			while(jobqueue.front().arrivalTime <= counter && !jobqueue.empty())
			{
				//std::cout<<"added Job: "<<jobqueue.front().name<<" to waitQ"<<std::endl;				
				waitqueue.push(jobqueue.front());

				jobqueue.pop();
			}
		}
		
		
		
		//OUTPUT and reassignment
		//When jobs are finished or time slice is up, place a new job in queue and print results
		if(cpuQueue1.front().blastTime == 0 || timeSlice1 == QUANTUM)
		{	
			if(cpuQueue1.front().blastTime <= 0)//job completed
			{
				//print:  name, completionTime (counter), and Finished?? Check assignment sheet
				std::cout<<"Job "<<cpuQueue1.front().name<<", scheduled for "<<timeSlice1 + 1<<"ms, completed"<<std::endl;
				cpuQueue1.pop(); //remove job from queue
			}
			else
			{
				//print name, completionTime (counter)?? Check assignment sheet
				std::cout<<"Job "<<cpuQueue1.front().name<<", scheduled for "<<timeSlice1 + 1<<"ms"<<std::endl;
				//Place job in back of waitqueue and remove from front
				waitqueue.push(cpuQueue1.front());
				cpuQueue1.pop();
			}
			//if wait queue is not empty & cpu queue is empty and the next job has arrived
			if(!waitqueue.empty() && cpuQueue1.empty())
			{
				cpuQueue1.push(waitqueue.front());
				waitqueue.pop();
			}				
			timeSlice1 = 0;							
		}
		
		if(cpuQueue2.front().blastTime == 0 || timeSlice2 == QUANTUM)
		{
			if(cpuQueue2.front().blastTime <= 0)//job completed
			{
				//print:  name, completionTime (counter), and Finished?? Check assignment sheet
				std::cout<<"Job "<<cpuQueue2.front().name<<", scheduled for "<<timeSlice2 + 1<<"ms, completed"<<std::endl;
				cpuQueue2.pop(); //remove job from queue
			}
			else
			{
				//print name, completionTime (counter)?? Check assignment sheet
				std::cout<<"Job "<<cpuQueue2.front().name<<", scheduled for "<<timeSlice2 + 1<<"ms"<<std::endl;
				//Place job in back of waitqueue and remove from front
				waitqueue.push(cpuQueue2.front());
				cpuQueue2.pop();
			}
			//if wait queue is not empty & cpu queue is empty and the next job has arrived
			if(!waitqueue.empty() && cpuQueue2.empty())
			{
				cpuQueue2.push(waitqueue.front());
				waitqueue.pop();
			}				
			timeSlice2 = 0;					
		}
		
		if(cpuQueue3.front().blastTime == 0 || timeSlice3 == QUANTUM)
		{
			if(cpuQueue3.front().blastTime <= 0)//job completed
			{
				//print:  name, completionTime (counter), and Finished?? Check assignment sheet
				std::cout<<"Job "<<cpuQueue3.front().name<<", scheduled for "<<timeSlice3 + 1<<"ms, completed"<<std::endl;
				cpuQueue3.pop(); //remove job from queue
			}
			else
			{
				//print name, completionTime (counter)?? Check assignment sheet
				std::cout<<"Job "<<cpuQueue3.front().name<<", scheduled for "<<timeSlice3 + 1<<"ms"<<std::endl;
				//Place job in back of waitqueue and remove from front
				waitqueue.push(cpuQueue3.front());
				cpuQueue3.pop();
			}
			//if wait queue is not empty & cpu queue is empty and the next job has arrived
			if(!waitqueue.empty() && cpuQueue3.empty())
			{
				cpuQueue3.push(waitqueue.front());
				waitqueue.pop();
			}				
			timeSlice3 = 0;										
		}
		
		if(cpuQueue4.front().blastTime == 0 || timeSlice4 == QUANTUM)
		{
			if(cpuQueue4.front().blastTime <= 0)//job completed
			{
				//print:  name, completionTime (counter), and Finished?? Check assignment sheet
				std::cout<<"Job "<<cpuQueue4.front().name<<", scheduled for "<<timeSlice4 + 1<<"ms, completed"<<std::endl;
				cpuQueue4.pop(); //remove job from queue
			}
			else
			{
				//print name, completionTime (counter)?? Check assignment sheet
				std::cout<<"Job "<<cpuQueue4.front().name<<", scheduled for "<<timeSlice4 + 1<<"ms"<<std::endl;
				//Place job in back of waitqueue and remove from front
				waitqueue.push(cpuQueue4.front());
				cpuQueue4.pop();
			}
			//if wait queue is not empty & cpu queue is empty and the next job has arrived
			if(!waitqueue.empty() && cpuQueue4.empty())
			{
				cpuQueue4.push(waitqueue.front());
				waitqueue.pop();
			}				
			timeSlice4 = 0;								
		}
	}
	std::cout<<"Total CPU Cycles: "<<counter - 1<<std::endl;
}
