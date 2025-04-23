#include <iostream>
#include <sstream>

using namespace std;

static std::string getOnvifURL()
{
    stringstream ssout;

    ssout << "http://" << "10.11.11.13" << ":" << 1113 << "/device/onvif_service";

    return ssout.str();
}

static std::string getRtspURL()
{
    std::stringstream ssout;

    ssout << "rtsp://" << "10.11.11.13" << ":" << 1113 << "/proxyStreamer_profile_h264_1";

    return ssout.str();
}

int main()
{
	cout << getOnvifURL() << std::endl;
	cout << getRtspURL() << std::endl;
}