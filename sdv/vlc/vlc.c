#include <unistd.h>
#include <vlc/vlc.h>

#define LOCAL

#ifdef LOCAL
#define STREAM_PATH "/home/sooraj/test/vlc/samplevideo.mp4"
#else
#define STREAM_PATH "rtsp://admin:Aveiro35@13.94.243.51:7704/proxyStreamer_profile_1"
#endif

int main()
{
    libvlc_instance_t * inst = libvlc_new (0, NULL);
    libvlc_media_t* media = NULL;
    libvlc_media_player_t *vlc_player = NULL;
    if(inst)
    {
#ifdef LOCAL
        media = libvlc_media_new_path (inst, STREAM_PATH);
#else
	    media = libvlc_media_new_location(inst, STREAM_PATH);
#endif
	    vlc_player = libvlc_media_player_new_from_media(media);
        libvlc_media_player_play(vlc_player); //this line will play the video and audio
    }
    else
    {
	printf("failed to instantiate\n");
    }

    if(media)
    {
	while(1)
	{
	    // Get stats from media
	    libvlc_media_stats_t stats;
	    int stat =  libvlc_media_get_stats(media, &stats);

	    // Obtain stats one by one
	    int read_bytes = stats.i_read_bytes;
	    float input_bitrate = stats.f_input_bitrate;
	    int demux_read_bytes = stats.i_demux_read_bytes;
	    float demux_bitrate = stats.f_demux_bitrate;
	    int demux_corrupted = stats.i_demux_corrupted;
	    int demux_discontinuity = stats.i_demux_discontinuity;
	    int decoded_video = stats.i_decoded_video;

	    printf("read_bytes=%d, input_bitrate=%f demux_read_bytes=%d demux_bitrate=%f demux_corrupted=%d demux_discontinuity=%d decoded_video=%d\n",
			    read_bytes, input_bitrate, demux_read_bytes, demux_bitrate, demux_corrupted, demux_discontinuity, decoded_video);
	    sleep(2);
	}
        libvlc_media_player_release(vlc_player);
        libvlc_media_release(media);
        libvlc_release(inst);
    }
    else
    {
	printf("failed to open %s\n", STREAM_PATH);
    }
}