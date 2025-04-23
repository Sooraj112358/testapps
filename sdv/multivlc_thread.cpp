#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include <vlc/vlc.h>

#define STATS_EVERY_NSECS    2
#define STREAM_PATH "rtsp://admin:Aveiro35@13.94.243.51:7706/proxyStreamer_profile_1"

static std::vector<std::string> streams;
static int32_t g_duration = -1;
static int32_t streamNo;

void * threadFunc(void * arg)
{
    //libvlc_instance_t * inst = libvlc_new (0, NULL);
    const char* argv[] = { "--no-audio" };
    libvlc_instance_t * inst = libvlc_new (1, argv);
 
    libvlc_media_t* media = NULL;
    libvlc_media_player_t *vlc_player = NULL;
    char* stream = (char *) arg;
    char *pos;
    if ((pos=strchr(stream, '\n')) != NULL)
        *pos = '\0';
    char fname[100];
    streamNo++;
    sprintf(fname, "result-stream%d.txt", streamNo);
    FILE *fp = fopen(fname, "w+");
    printf("Going to open %s\n",stream);
    fprintf(fp, "Going to open %s\n", stream);
    sync();
    if(inst)
    {
#ifdef LOCAL
        media = libvlc_media_new_path (inst, stream);
#else
        media = libvlc_media_new_location(inst, stream);
#endif
    	if(media)
    	{
            vlc_player = libvlc_media_player_new_from_media(media);
            libvlc_media_player_play(vlc_player); //this line will play the video and audio
    	}
    }
    else
    {
        fprintf(fp, "failed to instantiate\n");
    }

    if(media)
    {
        int dur = (g_duration == -1) ? INT32_MAX : g_duration;
        while(dur > 0)
        {
            // Get stats from media
            libvlc_media_stats_t stats;
            int stat =  libvlc_media_get_stats(media, &stats);

            fprintf(fp, "read_bytes=%d, input_bitrate=%f demux_read_bytes=%d demux_bitrate=%f demux_corrupted=%d demux_discontinuity=%d\n decoded_video=%d decoded_audio=%d displayed_pictures=%d lost_pictures=%d played_abuffers=%d lost_abuffers=%d\n",
                            stats.i_read_bytes, stats.f_input_bitrate, stats.i_demux_read_bytes, stats.f_demux_bitrate, stats.i_demux_corrupted, stats.i_demux_discontinuity,
                            stats.i_decoded_video, stats.i_decoded_audio, stats.i_displayed_pictures, stats.i_lost_pictures, stats.i_played_abuffers, stats.i_lost_abuffers);

            sleep(STATS_EVERY_NSECS);
        dur -=  STATS_EVERY_NSECS;
        }
        libvlc_media_player_release(vlc_player);
        libvlc_media_release(media);
        libvlc_release(inst);
    }
    else
    {
        fprintf(fp, "failed to open %s\n", stream);
    }
    fclose(fp);

}

static int populateStreams(char *filename)
{
    FILE *fp = NULL;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("failed to open %s\n", filename);
        return -1;
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s\n", line);
    streams.push_back(line);
    }
    return 0;
}

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " option(s)\n"
              << "Options:\n"
              << "\t-h,--help\t\t\tShow this help message\n"
              << "\t-s,--stream stream_file_path\tFile containting the streams to be analysed\n"
              << "\t-d,--duration\t\t\tTime duration in seconds for which streams need to be analysed\n"
              << std::endl;
}

static int parseArguments(int argc, char *argv[])
{
    /* Read params */
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help"))
        {
            show_usage(argv[0]);
            return -1;
        }
        else if ((arg == "-s") || (arg == "--streams"))
        {
            if (i + 1 < argc)
            { // Make sure we aren't at the end of argv!
                if(populateStreams(argv[++i])) // Increment 'i' so we don't get the argument as the next argv[i].
                {
                    return -1;
                }
            }
            else
            { // Uh-oh, there was no argument to the destination option.
                std::cerr << "-s | --streams option requires one argument." << std::endl;
                return -1;
            }
        }
        else if ((arg == "-d") || (arg == "--duration"))
        {
            if (i + 1 < argc)
            { // Make sure we aren't at the end of argv!
                g_duration = atoi(argv[++i]); // Increment 'i' so we don't get the argument as the next argv[i].
            }
            else
            { // Uh-oh, there was no argument to the destination option.
                std::cerr << "-d | --duration option requires one argument." << std::endl;
                return -1;
            }
        }
        else
        {
            std::cerr << "option" << argv[i] << " is not supported." << std::endl;
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    // Thread id
    std::vector<pthread_t> threadIdList;
 
    if(argc <=1 || parseArguments(argc, argv))
    {
        return EXIT_FAILURE;
    }
#if 1
    for(auto &stream : streams)
    {
        pthread_t threadId;
        // Create a thread that will call function threadFunc() as thread function. Also
        // pass the pointer to thread id object. This API will set the thread id in this passed argument.
        int err = pthread_create(&threadId, NULL, &threadFunc, (void*)stream.c_str());
 
        // Check if thread is created sucessfully
        if (err)
        {
            std::cout << "Thread creation failed : " << strerror(err);
            return err;
        }
        else
        {
            std::cout << "Thread1 Created with ID : " << threadId << std::endl;
            threadIdList.push_back(threadId);
        }
    }
 
    for(auto &threadId : threadIdList)
    {
        int err = pthread_join(threadId, NULL);
        // check if joining is sucessful
        if (err)
        {
            std::cout << "Failed to join Thread : " << strerror(err) << std::endl;
            return err;
        }
    }
#endif 
    std::cout << "Exiting Main" << std::endl;
 
    return 0;
}
