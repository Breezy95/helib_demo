#include <iostream>
#include <ctime>
#include <string>
#include <vector>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <string_view>
#include <boost/enable_shared_from_this.hpp>

#include <helib/helib.h>

#include "header_f/helib_func.hpp"
#include "header_f/csv.h"


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




class tcp_connection
  : public boost::enable_shared_from_this<tcp_connection>{
    public:

    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io_context){
      return pointer( new tcp_connection(io_context));
    }

    tcp::socket& socket(){
      return socket_;
    }

    void start(){
      //serv_context_ = contextSupplier();
      
      
      boost::asio::async_write(socket_, boost::asio::buffer(time), boost::bind(&tcp_connection::handle_write, shared_from_this(),
      boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
     //boost::asio::async_read_until(socket_,)
    }

    private:
      tcp_connection(boost::asio::io_context& io_context) : socket_(io_context){ }

      void handle_write(const boost::system::error_code& , size_t){ }


    //helib::Context* serv_context_;
    std::string time = "Server connected at " +curr_time();
    tcp::socket socket_;

  };

/* void tcp_server::operation(std::string oper,){
  switch oper:
    case "con":
      break;
} */



class tcp_server{
  public:
    tcp_server(boost::asio::io_context& io_context) : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), 1337)){
      
      start_accept();
    }

    void operation(){};

  private:
  void start_accept()
  {
    tcp_connection::pointer new_connection =
      tcp_connection::create(io_context_);

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
  }

  void handle_accept(tcp_connection::pointer new_connection,
      const boost::system::error_code& error){
    if (!error)
    {
      new_connection->start();
    }

    start_accept();
  }

  void handle_read(const boost::system::error_code& error, size_t bytes_transferred){
    //1st bytes will be for operation, and length of
    bytes_transferred -=3;
    boost::asio::streambuf::mutable_buffers_type mut_read_buffer = sbuf_.prepare(3);
    sbuf_.commit(3);
    std::istream inpStr(&sbuf_);
    std::string operation;
    inpStr >> operation;

    std::cout << operation << std::endl;

  }

  void handle_write(){ 

  }
  bool need_con_;
  boost::asio::streambuf sbuf_;
  boost::asio::io_context& io_context_;
  tcp::acceptor acceptor_;
  helib::Context* server_con;
  


}; 


std::vector<std::vector<int>> loadKey(){
  std::vector<std::vector<int>> ans;
  std::vector<std::string> lines;
  try{
    std::string line;
    io::LineReader lr("server_files/key.txt");
}
catch(std::exception& e){}

return ans;

}




 

int main(){

  std::vector<int> key = {1,2,3,4,5,6,7,8,9,10};


   size_t len;
   helib::Context* server_con;
   helib::PubKey* public_key;
   try{
    boost::asio::io_context io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 1337));

    
      tcp::socket sock(io);
      acceptor.accept(sock);
      
      //this is the byte buffer
      
      //boost::array<char, 128UL> buf;
      //boost::system::error_code error;

    for(int i=0;i<4;i++){
      boost::asio::streambuf read_buffer;
     
      //get msg size
      
    
      std::cout<< "BEGIN LOOP <<" <<std::endl;
      
      boost::asio::streambuf::mutable_buffers_type mut_read_buffer = read_buffer.prepare(3);


      size_t len = sock.receive(mut_read_buffer);
      
      
      read_buffer.commit(len);

      std::istream inpStr(&read_buffer);

      std::string s;
      //get operation into string
      inpStr >> s;

      std::cout << s << std::endl;
      std::cout <<"size of read_buffer: " <<read_buffer.size() << std::endl;
      
      
       
      if(s.compare("con") == 0){
        //read in size of msg
      boost::asio::streambuf size_header;
      boost::asio::streambuf::mutable_buffers_type mut_read_buffer_cmd = size_header.prepare(10);
      len = sock.receive(mut_read_buffer_cmd);
      size_header.commit(len);
      std::istream sizeStr(&size_header);
      int pay_size;
      sizeStr >> pay_size;
      //int size = stoi(pay_size);
      std::istream conStr(&size_header);

      //read in msg of the byte amt of size variable
      mut_read_buffer_cmd = size_header.prepare(pay_size);
      len = sock.receive(mut_read_buffer_cmd);
      size_header.commit(len);
      std::cout << "length of msg is : " << len << std::endl;
      server_con = helib::Context::readPtrFrom(conStr);
      server_con->printout();
      std::cout << "Success! "<< std::endl;
        
      }

      if(s.compare("pub") == 0){
        boost::asio::streambuf size_header;
        boost::asio::streambuf::mutable_buffers_type mut_read_buffer_cmd = size_header.prepare(10);

      //read in size of msg
      len = sock.receive(mut_read_buffer_cmd);
      size_header.commit(len);
      std::istream sizeStr(&size_header);
      int pay_size;
      sizeStr >> pay_size;
      
      
      std::cout << "size of public key msg: " << len << std::endl;
      std::cout << "size in size msg: " << pay_size << std::endl;
      std::cout << "size of mut_buf" <<mut_read_buffer_cmd.size()<< std::endl;
      //read in msg 
      std::istream pubStr(&size_header);
      mut_read_buffer_cmd = size_header.prepare(pay_size); 
      len = boost::asio::read(sock,mut_read_buffer_cmd);
      size_header.commit(len);
      std::cout << "size of mut_buf" <<mut_read_buffer_cmd.size()<< std::endl;
      std::cout << "length of msg is : " << len << std::endl;
      
      std::cout << "PUBKEY FROM CONNECTION\n" << std::endl;       
      helib::PubKey temp_pub(*server_con);
      temp_pub.readFrom(pubStr,*server_con);
      public_key = &temp_pub;
      public_key ->getContext().printout();

      std::cout << "Success! "<< std::endl;    
        }

      
      if(s.compare("vec") == 0){
        
        std::cout << "Encrypted vector" << std::endl;
        

        //len = sock.receive( boost::asio::buffer(buf));
        std::cout << "size of buffer msg: " << len << std::endl;

        
 
        }




      

      
      
    }
      
    

      //if (error)
       // throw boost::system::system_error(error); // Some other error.
    
     
     
     
     //helib::Context serv_context = helib::Context::readFrom(inpStr);

     //serv_context.printout();
     
    
  }
   catch( std::exception& e){

    std::cerr << e.what() << std::endl;
   }

 
  return 0;
}



 
   //g++ -o -g server server.cpp -L include/boost -lpthread to compile

  



