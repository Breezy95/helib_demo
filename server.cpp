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
#include "helib_fun"



using boost::asio::ip::tcp;

std::string curr_time(){

    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}
/* 
class tcp_connection : public boost::enable_shared_from_this<tcp_connection> {

  public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io_context){
      return pointer(new tcp_connection(io_context));
    }

    tcp::socket& socket(){
      return socket_;
    }


    void start(){
      message_ = curr_time();

      boost::asio::async_write(socket_, boost::asio::buffer(message_), 
      boost::bind(&tcp_connection::handle_write, shared_from_this()));
    }

  private:
    tcp_connection(boost::asio::io_context& io_context) 
    : socket_(io_context)
    {
    }

    void handle_write()
    {
      

    }

    tcp::socket socket_;
    std::string message_;
};

class tcp_server{

  public:
  tcp_server(boost::asio::io_context& io_context) : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(),13)){
    
    start_accept();
  }

  private:

    void start_accept(){

      tcp_connection::pointer new_conn = tcp_connection::create(io_context_);

      acceptor_.async_accept(new_conn -> socket(), boost::bind(&tcp_server::handle_accept, this, new_conn, boost::asio::placeholders::error));
    }

    void handle_accept(tcp_connection::pointer new_conn, const boost::system::error_code& error){
      
      if(!error){
        new_conn -> start();
      }

      start_accept();
    }

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};


 */




void print(const boost::system::error_code& /*e*/, boost::asio::steady_timer* t, int* count)
{
  if(*count <5){
    std::cout<< "Hello" <<std::endl;
    *count ++;
    t ->expires_at(t -> expiry() + boost::asio::chrono::seconds(1));
    t->async_wait(boost::bind(print,boost::asio::placeholders::error, t, count));
  }
}
 

int main()
{
   
   try{
    boost::asio::io_context io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 1337));

    for(;;){
      tcp::socket sock(io);
      acceptor.accept(sock);
      
      boost::array<int, 10> buf;
      boost::system::error_code error;

      size_t len = sock.read_some(boost::asio::buffer(buf), error);
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

     std::cout<< "buffer message has size of: " <<buf.size() << std::endl;
     std::cout << "these are the entries" <<std::endl;
     for(int i=0;i<buf.size();i++){
      std::cout << "entry num: "<< i << " " << buf[i]<< std::endl;
     }
    }
  }
   catch( std::exception& e){
    std::cerr << e.what() << std::endl;
   }
 
  return 0;
}
  /* try{
    
    boost::asio::io_context io_context;
    tcp_server server(io_context);
    io_context.run();
  }
  catch(std::exception& e){
    std::cerr << e.what() <<std::endl;
  }
  
  return 0; */


    /*  synchronous server 
   try{
    boost::asio::io_context io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 1337));

    for(;;){
        tcp::socket socket(io);
        acceptor.accept(socket);
        std::string current_time = curr_time();
        boost::system::error_code ignored_err;

        boost::asio::write(socket, boost::asio::buffer(current_time),ignored_err);
    }   
   }
   catch( std::exception& e){
    std::cerr << e.what() << std::endl;
   }
 */
   //g++ -o server_test server.cpp -L include/boost -lpthread to compile

  



