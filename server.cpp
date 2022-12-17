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
#include <thread>
#include "header_f/helib_func.hpp"
#include "header_f/csv.h"





#include <helib/intraSlot.h>




using boost::asio::ip::tcp;

//pad up to 10 digits in string length use for sending msg sizes
//input is the length of the payload in string form 
std::string padZeroes(std::string value){
  std::stringstream ss;
  
  ss << std::setfill('0') << std::setw(20) << value;
  std::string padded_num =ss.str();
  std::cout << "Size of msg: " <<padded_num<< std::endl;
  return padded_num;
}

int main(){
  // boilerplate code and encrypting test val////////////////////////////////////////////////
   srand(3454);
    

  long p= 2;
  long m = 4095;
  long r = 1;
  long c = 2;
  long bits = 500;
  std::vector<long> mvec = {7,5,9,13};
  std::vector<long> gens = {2341,3277,911};
  std::vector<long> ords = {6,4,6};

  helib::Context hel_context = helib::ContextBuilder<helib::BGV>()
  .m(m)
  .p(p)
  .r(r)
  .gens(gens)
  .ords(ords)
  .bits(bits)
  .c(c)
  .mvec(mvec)
  .bootstrappable(true)
  .build();

  

  helib::SecKey secret_key(hel_context);
  // Generate the secret key
  secret_key.GenSecKey();
  std::cout << "Generating key-switching matrices..." << std::endl;
  // Compute key-switching matrices that we need
  helib::addSome1DMatrices(secret_key);

  //upcasting pub
  const helib::PubKey& public_key = secret_key;
 

  // Get the EncryptedArray of the context
  const helib::EncryptedArray& ea = hel_context.getEA();
  std::vector<helib::zzX> unpackSlotEncoding;
  helib::buildUnpackSlotEncoding(unpackSlotEncoding, ea);
  // Get the number of slot (phi(m))
  long nslots = ea.size();
  std::cout << "Number of slots: " << nslots << std::endl;





/////////////////////////////////////////////////////////////////////////


  boost::asio::io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(),1337));
  tcp::socket socket(io_context);
  acceptor.accept(socket);
    
    for(int i=0;i<5;i++){
      //try sending operation, message length and then message
    std::string oper = "print";
    
    
    boost::asio::write(socket, boost::asio::buffer(oper));
    
  
    //send public key to client
    
    boost::asio::streambuf key_sb;
    
    std::ostream output(&key_sb);
    public_key.writeTo(output);
    std::string msgSize = std::to_string(key_sb.data().size());

    //sending len
    std::string msg_len = padZeroes(msgSize);
    boost::asio::write(socket, boost::asio::buffer(msg_len));

  // sending key
   
    boost::asio::write(socket, key_sb.data());


  }



}

//server for handout of public keys and matching to lottery key
class helib_tcp_server{
  public:
  helib_tcp_server(boost::asio::io_context& io_context) :
      io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(),1337)){
        start_accept();
  }

  private:
    void start_accept(){
      tcp_connection::pointer new_conn = tcp_connection::create(io_context_);

      acceptor_.async_accept(new_conn -> socket(),boost::bind(&helib_tcp_server::handle_accept, this, new_conn, boost::asio::placeholders::error));
    }

    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& err){
      if(!err){
        //genera
        new_connection -> start();
      }

      start_accept();
    }

boost::asio::io_context& io_context_;
tcp::acceptor acceptor_;  
std::vector<helib::PubKey> clientKeys;

};

class tcp_connection : public boost::enable_shared_from_this<tcp_connection> {
  public:
  typedef std::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_context& io_context){

    auto ptr = pointer(new tcp_connection(io_context));
    tcp_connection::clientCons.push_back(ptr);
  }

  tcp::socket& socket(){
    return socket_;
  }

  void start(helib::PubKey& handout_key){
    boost::asio::streambuf key_sb;
    
    std::ostream output(&key_sb);
    handout_key.writeTo(output);
    std::string msgSize = std::to_string(key_sb.data().size());

    //sending len
    std::string msg_len = padZeroes(msgSize);
    boost::asio::write(socket, boost::asio::buffer(msg_len));

  // sending key
   
    boost::asio::write(socket, key_sb.data());
    
    
  }

  private:
    tcp_connection(boost::asio::io_context& io_context) : socket_(io_context) {    }

    void handle_write(const boost::system::error_code& err, size_t len){

    }

    tcp::socket socket_;
    static std::vector<pointer> clientCons;
};



 




 
   //g++ -o -g server server.cpp -L include/boost -lpthread to compile

  



