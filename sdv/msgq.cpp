using namespace std;

#include <iostream>
#include <cstdlib>
#include <unistd.h>	// usleep
#include <fcntl.h>	// threads
#include <pthread.h>
#include <string>	// messages
#include <queue>	// the message queue


pthread_mutex_t msgmutex = PTHREAD_MUTEX_INITIALIZER;


queue<string> msgq;


void *msgreceiver(void *arg)
{
long qsize;
string nextmsg;

  while(true){
    if(msgq.empty()){
      usleep(10000); // sleep 0.01 sec before trying again
      continue;
    }

    // we end up here because there was something in the msg queue
    pthread_mutex_lock(&msgmutex);
    qsize=msgq.size();
    if(qsize > 5)cout << "Queue size: " << qsize << endl;
    nextmsg=msgq.front(); // get next message in queue
    msgq.pop(); // remove it from the queue
    pthread_mutex_unlock(&msgmutex);

    cout << "Processing value " << nextmsg << endl;
    usleep(2000000);
  }
  pthread_exit((void *)0);
} // msgreceiver()



void *msgtransmitter(void *arg)
{
string nextmsg;

  while(true){
    cin >> nextmsg;
    pthread_mutex_lock(&msgmutex);
    msgq.push(nextmsg); // push message onto the queue
    pthread_mutex_unlock(&msgmutex);
  }
  pthread_exit((void *)0);
} // msgtransmitter()



int main(int argc, char **argv)
{
pthread_t thr;

  // Create threads
  if(pthread_create(&thr,NULL,msgreceiver,NULL) ||
     pthread_create(&thr,NULL,msgtransmitter,NULL))
  {
    cout << argv[0] << " cannot make thread\n";
    exit(1);
  }

  /*
   * At this point the main thread can perform its actions or end
   */
  cout << "** Main thread ends **\n";
  pthread_exit((void *)0);

} // main()
