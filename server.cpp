#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <string_view>
#include <boost/enable_shared_from_this.hpp>

#include <helib/helib.h>
#include <helib/Ctxt.h>

#include "header_f/helib_func.hpp"
#include "header_f/csv.h"


using boost::asio::ip::tcp;

//pad up to 
std::string padZeroes(std::string value){
  std::stringstream ss;
  
  ss << std::setfill('0') << std::setw(10) << size(value);
  std::string padded_num =ss.str();
  return padded_num;
}

int main(){
  boost::asio::io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(),1337));
  tcp::socket socket(io_context);
  acceptor.accept(socket);
    
    for(int i=0;i<5;i++){
      //try sending operation, message length and then message
    std::string oper = "print";
    
    boost::asio::write(socket, boost::asio::buffer(oper));
    
    std::string msg = "Hello World:";

    std::string msg_len = padZeroes(msg);
    boost::asio::write(socket, boost::asio::buffer(msg_len));


    boost::asio::write(socket, boost::asio::buffer(msg));

    //send public key to client
  }



}

//now create multithreaded server
//start with public key handouts and client management




 




 
   //g++ -o -g server server.cpp -L include/boost -lpthread to compile

  



