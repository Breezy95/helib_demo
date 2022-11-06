#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <string_view>
#include <boost/enable_shared_from_this.hpp>

#include <helib/helib.h>



using boost::asio::ip::tcp;

std::string curr_time(){

    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}



void print(const boost::system::error_code& /*e*/, boost::asio::steady_timer* t, int* count)
{
  if(*count <5){
    std::cout<< "Hello" <<std::endl;
    *count ++;
    t ->expires_at(t -> expiry() + boost::asio::chrono::seconds(1));
    t->async_wait(boost::bind(print,boost::asio::placeholders::error, t, count));
  }
}

std::string buffer_to_string(const boost::asio::streambuf &buffer){
  using boost::asio::buffers_begin;
  
  auto bufs = buffer.data();
  std::string result(buffers_begin(bufs), buffers_begin(bufs) + buffer.size());
  return result;

}




 

int main()
{
   size_t len;

   try{
    boost::asio::io_context io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 1337));

    
      tcp::socket sock(io);
      acceptor.accept(sock);
      
      //this is the byte buffer
      
      //boost::array<char, 128UL> buf;
      //boost::system::error_code error;


      boost::asio::streambuf read_buffer;
      boost::asio::streambuf::mutable_buffers_type mut_read_buffer = read_buffer.prepare(592);
      size_t len =sock.receive(mut_read_buffer);
      read_buffer.commit(len);

      std::istream inpStr(&read_buffer);
      
    

      //if (error)
       // throw boost::system::system_error(error); // Some other error.
     std::cout << "bytes transferred: " << len << std::endl;
     
     
     
     helib::Context serv_context = helib::Context::readFrom(inpStr);

     serv_context.printout();
     
    
  }
   catch( std::exception& e){
    std::cerr << e.what() << std::endl;
   }


 
  return 0;
}

 
   //g++ -o -g server server.cpp -L include/boost -lpthread to compile

  



