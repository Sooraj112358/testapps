#include <thread>
#include <zmq.hpp>
#include <iostream>
#include <signal.h>
#include <unistd.h>

#define ZMQ_URL "ipc://localsock:5000"

const std::string TOPIC1 = "4567";
const std::string TOPIC2 = "8901";
volatile bool run = true;
static int s_interrupted = 0;


static void stopEverything()
{
	std::cout << __func__ << std::endl;
	s_interrupted = 1;
	run = false;
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_PAIR);
	socket.connect("ipc://killmebaby");
	zmq::message_t msg1;
	memcpy(msg1.data(),"0", 1);
	socket.send(msg1);
	zmq::message_t msg2;
	memcpy(msg2.data(),"0", 1);
	socket.send(msg2);
	socket.close();
	//context.close();
	zmq_ctx_destroy(&context);
	std::cout << __func__ << "exit" << std::endl;
}
static void s_signal_handler (int signal_value)
{
    if(s_interrupted == 0)
    {
        std::cout << "sighandler" << std::endl;
		stopEverything();
    }
}

// Setup signal handler to quit the program
static void s_catch_signals (void)
{
    struct sigaction action;
    action.sa_handler = s_signal_handler;
    action.sa_flags = 0;
    sigemptyset (&action.sa_mask);
    sigaction (SIGINT, &action, NULL);
    sigaction (SIGTERM, &action, NULL);
}


void startPublisher1(zmq::socket_t& zmq_socket)
{
	std::cout << __func__ << std::endl;
	sleep(1);
    usleep(100000); // Sending message too fast after connexion will result in dropped message
    zmq::message_t msg(3);
    zmq::message_t topic(4);
    for(int i = 0; i < 10; i++) {
        memcpy(topic.data(), TOPIC1.data(), TOPIC1.size()); // <= Change your topic message here
        memcpy(msg.data(), "abc", 3);
		std::cout << "Message data " << (char *)msg.data() << " and topic " << (char *)topic.data() << std::endl;
        try {
            zmq_socket.send(topic, ZMQ_SNDMORE); 
            zmq_socket.send(msg); 
			//usleep(1000000); 
        } catch(zmq::error_t &e) {
            std::cout << e.what() << std::endl;
        }
        msg.rebuild(3);
        topic.rebuild(4);
        usleep(1); // Temporisation between message; not necessary
    }

	std::cout << __func__ << "exit" << std::endl;
}

void startPublisher2(zmq::socket_t& zmq_socket)
{
	std::cout << __func__ << std::endl;
    usleep(100000); // Sending message too fast after connexion will result in dropped message
    zmq::message_t msg(3);
    zmq::message_t topic(4);
    for(int i = 0; i < 10; i++) {
        memcpy(topic.data(), TOPIC2.data(), TOPIC2.size()); // <= Change your topic message here
        memcpy(msg.data(), "def", 3);
		std::cout << "Message data " << (char *)msg.data() << " and topic " << (char *)topic.data() << std::endl;
        try {
            zmq_socket.send(topic, ZMQ_SNDMORE); 
            zmq_socket.send(msg); 
			//usleep(1000000); 
        } catch(zmq::error_t &e) {
            std::cout << e.what() << std::endl;
        }
        msg.rebuild(3);
        topic.rebuild(4);
        usleep(1); // Temporisation between message; not necessary
    }

	std::cout << __func__ << "exit" << std::endl;
}

void startSubscriber1(zmq::socket_t& killer_socket)
{
	int count = 0;
	std::cout << __func__ << std::endl;
    zmq::context_t zmq_context(1);
    zmq::socket_t zmq_socket(zmq_context, ZMQ_SUB);
    zmq_socket.connect(ZMQ_URL);
	int i32Val = 0;
	zmq_socket.setsockopt(ZMQ_LINGER, &i32Val, sizeof i32Val);

	//zmq_socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
	zmq_socket.setsockopt(ZMQ_RCVTIMEO, 5000);
    //zmq_socket.setsockopt(ZMQ_SUBSCRIBE, TOPIC2.c_str(), TOPIC2.length()); // Subscribe to any topic you want here
    zmq_socket.setsockopt(ZMQ_SUBSCRIBE, TOPIC1.c_str(), TOPIC1.length()); // Subscribe to any topic you want here
    zmq::pollitem_t items [] = {
        { zmq_socket, 0, ZMQ_POLLIN, 0 },
        { killer_socket, 0, ZMQ_POLLIN, 0 }
    };
    while(true == run)
    {
        int rc = 0;
        zmq::message_t topic;
        zmq::message_t msg;
        zmq::poll (&items [0], 2, -1);

        if (items [0].revents & ZMQ_POLLIN)
        {
            //std::cout << "waiting on recv..." << std::endl;
            rc = zmq_socket.recv(&topic, ZMQ_RCVMORE);  // Works fine
            rc = zmq_socket.recv(&msg) && rc;
            if(rc > 0) // Do no print trace when recv return from timeout
            {
                std::cout << "topic:\"" << std::string(static_cast<char*>(topic.data()), topic.size()) << "\"" << std::endl;
                std::cout << "msg:\"" << std::string(static_cast<char*>(msg.data()), msg.size()) << "\"" << std::endl;
				count++;
            }
        }
        else if (items [1].revents & ZMQ_POLLIN)
        {
            if(s_interrupted == 1)
            {
                std::cout << "Exiting bye bye..1" << std::endl;
                break;
            }
        }
    }
	std::cout << "Exiting bye bye..11" << std::endl;
	zmq_socket.close();
	std::cout << "Exiting bye bye..22" << std::endl;
	//zmq_context.close();
	std::cout << "Exiting bye bye..11" << std::endl;
	zmq_ctx_destroy(&zmq_context);
	std::cout << "Exiting bye bye..22" << std::endl;
	std::cout << __func__ << "exit" << count << std::endl;
}



void startSubscriber2(zmq::socket_t& killer_socket)
{
	int count = 0;
	std::cout << __func__ << std::endl;
    zmq::context_t zmq_context(1);
    zmq::socket_t zmq_socket(zmq_context, ZMQ_SUB);
    zmq_socket.connect(ZMQ_URL);
	int i32Val = 0;
	zmq_socket.setsockopt(ZMQ_LINGER, &i32Val, sizeof i32Val);

    //zmq_socket.setsockopt(ZMQ_SUBSCRIBE, TOPIC1.c_str(), TOPIC1.length()); // Subscribe to any topic you want here
    zmq_socket.setsockopt(ZMQ_SUBSCRIBE, TOPIC2.c_str(), TOPIC2.length()); // Subscribe to any topic you want here
    zmq::pollitem_t items [] = {
        { zmq_socket, 0, ZMQ_POLLIN, 0 },
        { killer_socket, 0, ZMQ_POLLIN, 0 }
    };
    while(true == run)
    {
        int rc = 0;
        zmq::message_t topic;
        zmq::message_t msg;
        zmq::poll (&items [0], 2, -1);

        if (items [0].revents & ZMQ_POLLIN)
        {
            //std::cout << "waiting on recv..." << std::endl;
            rc = zmq_socket.recv(&topic, ZMQ_RCVMORE);  // Works fine
            rc = zmq_socket.recv(&msg) && rc;
            if(rc > 0) // Do no print trace when recv return from timeout
            {
                //std::cout << "topic:\"" << std::string(static_cast<char*>(topic.data()), topic.size()) << "\"" << std::endl;
                std::cout << "msg:\"" << std::string(static_cast<char*>(msg.data()), msg.size()) << "\"" << std::endl;
				count++;
            }
        }
        else if (items [1].revents & ZMQ_POLLIN)
        {
            if(s_interrupted == 1)
            {
                std::cout << "Exiting bye bye2.." << std::endl;
                break;
            }
        }
    }
	zmq_socket.close();
	//zmq_context.close();
	zmq_ctx_destroy(&zmq_context);

	std::cout << __func__ << "exit" << count << std::endl;
}

int main() {
    s_catch_signals ();
    run = true;
    zmq::context_t zmq_context(1);
    zmq::socket_t zmq_socket(zmq_context, ZMQ_PUB);
    zmq_socket.bind(ZMQ_URL);
	int i32Val = 0;
    zmq::socket_t killer_socket(zmq_context, ZMQ_PAIR); // This socket is used to terminate the loop on a signal
    killer_socket.bind("ipc://killmebaby");
	killer_socket.setsockopt(ZMQ_LINGER, &i32Val, sizeof i32Val);
	zmq_socket.setsockopt(ZMQ_LINGER, &i32Val, sizeof i32Val);
	std::cout << __func__ << "1" << std::endl;
    std::thread t_sub1(startSubscriber1, std::ref(killer_socket));
	std::cout << __func__ << "2" << std::endl;
    std::thread t_sub2(startSubscriber2, std::ref(killer_socket));
	std::cout << __func__ << "3" << std::endl;
    sleep(1); // Slow joiner in ZMQ PUB/SUB pattern
    std::thread t_pub1(startPublisher1, std::ref(zmq_socket));
	std::cout << __func__ << "4" << std::endl;
    std::thread t_pub2(startPublisher2, std::ref(zmq_socket));
	std::cout << __func__ << "5" << std::endl;
    t_pub1.join();
	std::cout << __func__ << "6" << std::endl;
    t_pub2.join();
	std::cout << __func__ << "7" << std::endl;
    run = false;
	//stopEverything();
    t_sub1.join();
	std::cout << __func__ << "8" << std::endl;
    t_sub2.join();
	std::cout << __func__ << "9" << std::endl;
	zmq_socket.close();
	//zmq_context.close();
	zmq_ctx_destroy(&zmq_context);
}