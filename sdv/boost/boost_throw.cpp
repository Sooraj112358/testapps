#include <iostream>
#include <boost/exception_ptr.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/errinfo_errno.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <errno.h>

struct file_read_error: virtual boost::exception { };

void do_work() //throws cloning-enabled boost::exceptions
{
	std::cout << "Hello Universe!" << std::endl;
    //throw /*boost::enable_current_exception(file_read_error()) <<*/ boost::errinfo_errno(2);
	BOOST_THROW_EXCEPTION(std::runtime_error( "Unspecified runtime error" ));
}

void worker_thread( boost::exception_ptr & error )
{

    try
    {
        do_work();
        error = boost::exception_ptr();
    }

    catch(...)
    {
        error = boost::current_exception();
		std::cerr << "Error2" << '\n';
		boost::rethrow_exception(error);
    }
}

void work()
{
    boost::exception_ptr error;
    boost::thread t( boost::bind(worker_thread,boost::ref(error)) );
    t.join();
    if( error )
        boost::rethrow_exception(error);
}
	
int main()
{
    boost::exception_ptr error;
    try
    {
        //work();
		worker_thread(error);
        error = boost::exception_ptr();
    }
    catch( std::exception const & x )
    {
        std::cerr << boost::diagnostic_information( x ) << std::endl;
    }
    catch(...)
    {
        error = boost::current_exception();
		std::cout << "errno" << error << std::endl;
		std::cerr << "Error1" << '\n';
    }
}