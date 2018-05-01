using namespace std;
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
int buffer[10] = {0,0,0,0,0,0,0,0,0,0}; //Use an integer array to hold the contents of the buffer 
	int counter = 0; //Use a counter variable to hold the number of occupied cells
	int insert = 0; //Use a variable to keep track of the next location for the producer to insert a value 
	static int removeTrack = 0; //Use a variable to keep track of the next location for the consumer to remove a value.
	pthread_t thid[2];
void* produce(void * produce)
{
int index = 1;
while(index <= 100000 )
	{
		if(counter < 10)
		{
			buffer[insert] = index;
			if(insert < 9 )
			{
			insert++;
			}
			else
			{
			insert = 0;
			}
			counter++;
			index++;
		}
	}
cout << "Success";
	pthread_exit(produce);
}	
void* consume(void * consume)
{
	int index = 1;
while(index <= 1000000)
	{
		if(index == buffer[removeTrack])
			{
				buffer[removeTrack] = 0;
				counter = counter -1;
				index++;//correct
				if( removeTrack < 9 )
				{
				removeTrack++;
				}
				else
				{
				removeTrack = 0;	
				}
			}
		else if (buffer[removeTrack] == 0)
		{
			//stall
		}
		else
			{
			int incorrectNumber = buffer[removeTrack];
			printf("Incorrect Number: %d \n", incorrectNumber);
			//cout << "Incorrect number " << incorrectNumber << "\n"; //incorrect
			cout << index << " numbers recieved correctly\n";
			pthread_exit(consume);
			}
	}
	pthread_exit(consume);
}
int main()
{
	//cout << "Creating producer thread\n";
	if (pthread_create(&thid[0], NULL, produce, NULL) != 0)
		{
		perror("pthread_create() error");
		exit(1);
		}
	//cout << "Creating consumer thread\n";
	if (pthread_create(&thid[1], NULL, consume, NULL) != 0)
		{
		perror("pthread_create() error");
		exit(1);
		}
	sleep(2);

}

