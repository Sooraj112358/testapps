#ifdef _MSC_VER
#include <boost/config/compiler/visualc.hpp>
#endif
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

std::string json_input = "{\"header\":{\"utc_time\": \"11\",\"ewv\": \"15ce6067-e37f-444a-ac12-48a325b7cb4484d7eb83224\",\"topic\": \"15ce6067-e37f-444a-ac12-48a325b7cb45\"}}";
//std::string json_input = "{\"header\":{\"utc_time\": \"11\",\"ewv\": \"15ce6067-e37f-444a-ac12-48a325b7cb45\/484d7eb83224\",\"topic\": \"15ce6067-e37f-444a-ac12-48a325b7cb45\"}}";
		/*{
			"utc_time": "11",
			"ewv": "15ce6067-e37f-444a-ac12-48a325b7cb45\/484d7eb83224",
			"topic": "\/aievent\/15ce6067-e37f-444a-ac12-48a325b7cb45\/484d7eb83224\/0"
		}*/

int main()
{
    try
    {
        std::stringstream ss;
        // send your JSON above to the parser below, but populate ss first
		ss << json_input;

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
		
#if 0
         auto a = pt.get<std::string>("header.utc_time");
         auto b = pt.get<std::string>("header.ewv");
         auto c = pt.get<std::string>("header.topic");
		 std::cout << "utc_time:" << a << "ewv:" << b << "topic:" << c << std::endl;
		for (boost::property_tree::ptree::value_type &val :  pt.get_child("header"))
		{
			std::cout << "first:" << val.first << "second:" << val.second.data() << std::endl;
		}
#else
         auto d = pt.get_child("header");
		 if(!d.empty())
		 {
         auto a = d.get<std::string>("utc_time");
         auto b = d.get<std::string>("ewv");
         auto c = d.get<std::string>("topic");
		 std::cout << "utc_time:" << a << "ewv:" << b << "topic:" << c << std::endl;
		 }
		 else
		 {
			 std::cout << "child header not found" << std::endl;
		 }
#endif
        /*BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("particles.electron"))
        {
            assert(v.first.empty()); // array elements have no names
            std::cout << v.second.data() << std::endl;
            // etc
        }*/
        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_FAILURE;
}