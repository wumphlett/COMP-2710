// Please change the following comment part into you name
// #0#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
// Will
// Humphlett
// #0#END# DO NOT MODIFY THIS COMMENT LINE!

#include <stdio.h>
#include <pthread.h>
#include <iostream>
using namespace std;

// This macro defines how many units of data will be generated in total,
// For simplicity, we use an integer to represent one unit of data,
// therefore, this project actually will generate at most 10 integers.
#define MAX 10 

// We need the mutex to make sure that every time only one thread access the buffer
// , could be the consumer thread or the producer thread.
pthread_mutex_t the_mutex;

// A blocked thread waits for the "traffic lights" before it make an action.
// The condition variables are the "traffic lights" to tell the theads
// whether the job is done and resource, the buffer in this case, available 
// or not. The following two condition variables "condc" and "condp" are
// the traffic lights for consumer thread and producer thread.
pthread_cond_t condc, condp; 

// To simplify the simulation, we use the integer variable as a buffer
// The buffer stores one uint of data, that is, a integer.
int buffer = 0;

void *producer(void *ptr)
{
    int i;
    
    for(i=1; i<=MAX; i++)
    {
        // Step 1, use the function to lock the mutex, therefore, only the
        // producer thread use the buffer after that. You do not want to enter
        // the "dressing room" when someone is using it. If the mutex has already
        // been locked, that means someone is using the "dressing room", the thread will
        // wait. Also, when you start to use the room, you need to lock the door so
        // other people knows someone is in the room. 
        pthread_mutex_lock(&the_mutex); 

        // Step 2, if the buffer is NOT empty, that means buffer hold some data
        // the thread need to wait for traffic light "condp" before output to the buffer,
        while(buffer !=0) pthread_cond_wait(&condp, &the_mutex); 
    
        // Step 3, in this simulation, the producer generate one integer, 
        // which is one unit of data assigned to the buffer.
        buffer = i*7;

        // Step 4, print out message tell what item the producer genetate.
        cout << "producer produce item " << buffer << endl;
    
        // Step 5, since the buffer is only one unit, it is full now.
        // We need to stop, and notify the other thread, the consumer
        // thread that you are ready to go. So we use the following function
        // to change the traffic light for consumer thread to "green".
        pthread_cond_signal(&condc);
    
        // Step 6, after we give green light to the other thread,
        // we now unlock the mutex so the "dressing room" is available. 
        pthread_mutex_unlock(&the_mutex);
    }

    // Step 7, exit the thread, return with 0, which means "success" 
    pthread_exit(0);
    
}

void *consumer(void *ptr)
{
    int i;
    int get_data;

    for(i=1; i<=MAX; i++)
    {
        // Lock the_mutex before you start, see step 1 example in producer 
        // #1#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        pthread_mutex_lock(&the_mutex);
        // #1#END# DO NOT MODIFY THIS COMMENT LINE!

        // When the buffer IS empty, nothing to consume, so we have to wait, 
        // see step 2 example in producer
        // #2#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        while(buffer ==0) pthread_cond_wait(&condc, &the_mutex); 
        // #2#END# DO NOT MODIFY THIS COMMENT LINE!

        // Assign the buffer data to the variable get_data
        // #3#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        get_data = buffer;
        // #3#END# DO NOT MODIFY THIS COMMENT LINE!

        // Prints out the content of what you get in get_data
        cout << "consumer consume item " << get_data << endl;

        // Clear the buffer by assign value 0 to the buffer
        // #4#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        buffer = 0;
        // #4#END# DO NOT MODIFY THIS COMMENT LINE!

        // Notify the condition variable of producer that good to go
        // see step 5 example in producer
        // #5#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        pthread_cond_signal(&condp);
        // #5#END# DO NOT MODIFY THIS COMMENT LINE!

        // Unlock the mutex, see step 6 example in producer
        // #6#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        pthread_mutex_unlock(&the_mutex);
        // #6#END# DO NOT MODIFY THIS COMMENT LINE!
    }
    
    // exit the thread, return with 0, which means "success", see step 7 in producer
    // #7#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
    pthread_exit(0);
    // #7#END# DO NOT MODIFY THIS COMMENT LINE!
}

int main(int argc, char *argv[])
{
    // change your the following id into your banner id
    // #8#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
    int banner_id = 903997842;
    // #8#END# DO NOT MODIFY THIS COMMENT LINE!
    cout << "Banner id: " << banner_id << endl;

    pthread_t pro, con; 
    pthread_mutex_init(&the_mutex, 0);      // create the mutex used by thread
    pthread_cond_init(&condc,0);            // initialize the condition variable for consumer
    pthread_cond_init(&condp,0);            // initialize the condition variable for producer
    
    pthread_create(&con, 0, consumer, 0);   // create thread map to function consumer
    pthread_create(&pro, 0, producer, 0);   // create thread map to function producer
    pthread_join(pro,0);                    // put the producer thread into the system
    pthread_join(con,0);                    // put the consummer thread into the system

    // clean up, destroy the mutex and two threads
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);

    return 0;
}
