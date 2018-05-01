#define RAND_MAX = 10;
#define BUFFER_SIZE =  10;
using namespace std;
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <thread>
#include <time.h>
#include <semaphore.h>
string buffer[10] = { " "," "," "," "," "," "," "," "," "," " }; //Use an string array to hold the contents of the buffer 
	int counter = 0; //Use a counter variable to hold the number of occupied cells
	int insert = 0; //Use a variable to keep track of the next location for the producer to insert a value 
	static int removeTrack = 0; //Use a variable to keep track of the next location for the consumer to remove a value.
	pthread_t thid[1000];
	int arrayCount = 0;
	static string* table = new string[1];
	//Creating and initializing mutex locks
	pthread_mutex_t mut;
	sem_t sem;
	//Creating an initializing a semaphor
void* produce(void * produce)
{
	while (1 == 1)
	{
		//Each producer thread sleeps for a random period of seconds (between 0 and RAND_MAX)
		int randomint = (rand() % 10);
		sleep(randomint);
		//upon awakening, will attempt to insert a word randomly selected from the list of words in wordsEn.txt into the buffer
		string randomWord = table[rand() % arrayCount];
		if (counter < 10)
		{
			if (pthread_mutex_lock(&mut) == 0) {
			//if(sem_wait(&sem) == 0)
			
				//Critical Section
				buffer[insert] = randomWord;
				// Whenever a randomly selected word is inserted into the buffer, the information should be printed on the screen(i.e., thread_id and the word)				pid_t this_id = pthread_self();				cout << "[producer thread ID: " << this_id << "] inserted an item (word: " << randomWord << ") to the buffer\n"; //[producer thread ID: 1] inserted an item (word: orange) to the buffer
				if (insert < 9)
				{
					insert++;
				}
				else
				{
					insert = 0;
				}
				counter++;
			}
			else { cout << "Mutex lock failed"; }//end of critical section
			if (pthread_mutex_unlock(&mut) != 0) {
				perror("mutex_lock");

			}
			//sem_post(&sem);
		}
	}
}	
void* consume(void * consume)
{
	string removedWord;
	while (1 == 1)
	{
		//Each consumer thread sleeps for a random period of seconds (between 0 and RAND_MAX), 		sleep(rand() % 10);
		//upon awakening, will attempt to remove a word from the buffer. 
			//if (pthread_mutex_lock(&mut) == 0)
		if (sem_wait(&sem) == 0)
			{
				
				if (buffer[removeTrack] != " ")
				{
				//critical section
				removedWord = buffer[removeTrack];
				buffer[removeTrack] = " ";
				counter = counter - 1;
				if (removeTrack < 9)
				{
					removeTrack++;
				}
				else
				{
					removeTrack = 0;
				}
				// Whenever a word is removed from the buffer, the information should be printed on the screen(i.e., thread_id and the word)
				pid_t this_id = pthread_self();
				cout << "[consumer thread ID: " << this_id << "] removed an item (word: " << removedWord << ") from the buffer\n"; //[consumer thread ID: 2] removed an item (word: apple) from the buffer
			}  //end of critical section
			else { //printf("Mutex lock failed");
			}//end of critical section
		}
		/*if (pthread_mutex_unlock(&mut) != 0) {
			printf("Mutex was not able to be unlocked");		}*/
		sem_post(&sem);
	}
}
int main(int argc, char *argv[])
{
	srand(time(NULL));
	int producerCount = atoi(argv[2]);
	int consumerCount = atoi(argv[3]);
	int runTime = atoi(argv[1]);
	cout << "The program will run for " << runTime << " seconds with " << producerCount << " producer threads and " << consumerCount << " consumer threads\n";
	if (argc == 1) {
		cout << "No command line argument given.\n"
			"Please provide the input file name as an argument.\n"
			"Ex: ./producer_consumer2 180 10 20\n";
		return -1;
	}
	ifstream inputFile;
	string inputFileName("wordEn.txt");
	inputFile.open(inputFileName);
	string inputString;
	//initialize mutext lock
	if (pthread_mutex_init(&mut, NULL) != 0) {
		perror("mutex_lock");
		exit(1);
	}
	//initialize semaphor
	sem_init(&sem, 0, 1);
	//First run counts the number of elements
	if (inputFile.is_open()) {
		while (inputFile >> inputString) {
			// increment the count
			arrayCount++;
		}
		inputFile.close();
	}
	else {
		cout << "Unable to open to count" << endl;
		return -1;
	}
	string wordEnArray[arrayCount];
	int index = 0;
	//Second run adds the number of elements to an array
	inputFile.open(inputFileName);
	if (inputFile.is_open()) {
		while (inputFile >> inputString) {
			// add elements to array
			wordEnArray[index] = inputString;
			index++;
		}
		inputFile.close();
	}
	else {
		cout << "Unable to open to read " << endl;
		return -1;
	}
	/*for (int i = 0; i < 100; i ++)
	{
		cout << wordEnArray[i] << "\n";
		//print out the first 100 values of my array for debugging purposes
	}*/
	table = wordEnArray; //transferring the local array to the global value.
			/* for (int i = 0; i < 100; i ++)
				 {
					cout << table[i] << "\n";
						//print out the first 100 values of my array for debugging purposes
				}*/
	//cout << "Creating producer thread\n";
	for (int i = 0; i < producerCount; i++)
	{
		if (pthread_create(&thid[i], NULL, produce, NULL) != 0)
		{
			perror("pthread_create() error");
			exit(1);
		}
	}
	//cout << "Creating consumer thread\n";
	for (int i = 0; i < consumerCount; i++)
	{
		if (pthread_create(&thid[i], NULL, consume, NULL) != 0)
		{
			perror("pthread_create() error");
			exit(1);
		}
	}
	sleep(runTime);
	exit(1);
}

