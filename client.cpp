#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <time.h>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>

#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <helib/JsonWrapper.h>
#include <helib/helib.h>
#include <helib/binaryArith.h>
#include <helib/intraSlot.h>

#include "helib/binio.h"
#include "header_f/json.hpp"
#include "header_f/helib_func.hpp"


#include <fstream>
using namespace std;
using json = ::nlohmann::json;
using boost::asio::ip::tcp;




void number_placement(string* val){
        for(int i=0;i<10;i++){
            cout <<"Number " << i+1 << ": ";
            string inp;

            cin >> inp;


            try{
            stoi(inp);
            //just convert int back to string
            }
            catch(...){
                cout << "Invalid input" << endl;
                i--;
                continue;
            }
            val[i] = inp;
            }
    }



struct slow_print{
    string stream;
    long int delay;
};

ostream& operator<<(ostream& output, const slow_print& str){
    for( const auto& chr : str.stream){
        output << chr << flush;
        this_thread::sleep_for(chrono::milliseconds(str.delay));
    }
    return output;
}

string trim_front(string& original, char trimmed_char){
    int front =0;

    if(*original.cbegin() != trimmed_char){
        return original;
    }

    for(auto iter=original.cbegin();iter != original.cend()-1;iter++){
        cout << "iter value: " << *iter<<endl;
        
        if(*iter == trimmed_char){
                front = original.cbegin() - iter;
        }
        if(*iter+1 != *iter ){
            break;
        }
        }

    return original.substr(front);
}

string* selectionLoop(string* val){
    bool check = true;

    while(check){
        
        number_placement(val);   
        cout << "You're numbers are ";
        for(int i=0;i<10;i++)
            cout << val[i]<< " ";

        cout << "\nWould you like to submit these numbers? \n\t 1. Yes \t 2. No\n";
        string final_inp;
        cin >> final_inp;
        std::transform(final_inp.begin(),final_inp.end(), final_inp.begin(), 
        [](unsigned char c){ return tolower(c); });
        
        while(check){
        if(final_inp.compare("yes") == 0 || final_inp.compare("1") == 0){
            check = false;
        }
        else if(final_inp.compare("no") == 0 || final_inp.compare("2") == 0){
            break;
        }
        else{
            cout <<"Invalid Input! Please type Yes or No"<<endl;
            cin >> final_inp;

            std::transform(final_inp.begin(),final_inp.end(), final_inp.begin(), 
        [](unsigned char c){ return tolower(c); });
            }
        }
    }

    return val;

}

vector<int> convertInputs(string* input){
    vector<int> output;
    for(int i=0;i<10;i++){
        output.push_back(stoi(*input));
        input++;
    }
    return output;

    
}



void send_command(std::string& cmd, boost::asio::ip::tcp::socket& sock, boost::asio::streambuf& sbuf){
    std::ostream output(&sbuf);

    output << cmd;
    std::cout<< "command is: " << cmd << std::endl;

    size_t len = boost::asio::write(sock, sbuf.data());
    sbuf.consume(len);
    
    
    std::cout << "size of cmd msg is: " << len << std::endl;
   
    
    std::cout << "size of streambuf: " << sbuf.size() << std::endl;   
}

size_t send_con_payload(boost::asio::ip::tcp::socket& sock, boost::asio::streambuf& sbuf, helib::Context* payload ){

    std::ostream output(&sbuf);
    boost::asio::streambuf temp_buf;
    std::ostream temp(&temp_buf);
    payload->writeTo(temp);
    uint32_t size = temp_buf.size();
    std::stringstream ss;
    ss << std::setw(10) << std::setfill('0') << size;
    std::string s = ss.str();


    output << s;

    size_t pay_len = sock.send(sbuf.data());
    sbuf.consume(pay_len);
    //std::cout <<"size of payload length: " <<pay_len << std::endl;
    //std::cout << "size of payload: " << pay_len << std::endl;
    payload -> writeTo(output);
    pay_len = sock.send(sbuf.data());
    sbuf.consume(pay_len);

    //std::cout << "size of msg: " << pay_len << std::endl;
    //std::cout << "size of streambuf: " << sbuf.size() << std::endl;

    
    return size;
}

size_t send_key_payload(boost::asio::ip::tcp::socket& sock, boost::asio::streambuf& sbuf, helib::PubKey pubkey){
    
    std::ostream output(&sbuf);
    boost::asio::streambuf temp_buf;
    std::ostream temp(&temp_buf);
    pubkey.writeTo(temp);
    uint32_t size = temp_buf.data().size();
    std::stringstream ss;
    ss << std::setw(10) << std::setfill('0') << size;
    std::string s = ss.str();
    
    std::cout << "size of payload: " << size << std::endl;
    output << s;

    size_t pay_len = sock.send(sbuf.data());
    sbuf.consume(pay_len);
    //std::cout <<"size of key payload byte length: " <<pay_len << std::endl;

    pubkey.writeTo(output);
    pay_len = boost::asio::write(sock,temp_buf,boost::asio::transfer_all());
    //sbuf.consume(pay_len);
    
    std::cout << "size of msg: " << pay_len << std::endl;
    std::cout << "size of streambuf: " << temp_buf.size() << std::endl;



    return pay_len;
}

size_t send_values(boost::asio::ip::tcp::socket& sock, boost::asio::streambuf& sbuf, helib::Ctxt ctxt){

    
return 1;  
}









int main(){

    srand(3454);
    

    

    vector<int> test = {0,1,2,3,4,5,6,68,8,9};

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

  // Get the number of slot (phi(m))
  long nslots = ea.size();
  std::cout << "Number of slots: " << nslots << std::endl;

  
  helib::Ptxt<helib::BGV> ptxt(hel_context);

   for (int i = 0; i < test.size(); i++) {
    ptxt[i] = test[i];
  }

   


   helib::Ctxt ctxt(public_key);

    public_key.Encrypt(ctxt, ptxt);

    


    //send context, public key, and then vector

    try{
    boost::asio::io_context io_ctx;
    tcp::resolver resolver(io_ctx);

    //how you resolve an arbitrary ip_addr
    tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "1337");


    tcp::socket socket(io_ctx);

    boost::asio::connect(socket, endpoints);
    boost::system::error_code err;

    boost::asio::streambuf strBuf;
    std::ostream outStr(&strBuf);
    std::string con = "con";
    
    send_command(con, socket,strBuf);

    send_con_payload(socket, strBuf, &hel_context);

    std::string pub = "pub";
    send_command(pub, socket, strBuf);

    send_key_payload(socket, strBuf, public_key);
    
    /*
    size_t len = boost::asio::write(socket, boost::asio::buffer(strBuf.data()), err);

    std::cout << "size of message: " << len << std::endl;
    
     boost::asio::streambuf vecBuf;
    std::ostream vecStr(&vecBuf);
    
    vecStr << "vec";
    //vecStr << "#";
    ctxt.writeToJSON(vecStr);
    vecStr << "#";

    len = boost::asio::write(socket, boost::asio::buffer(vecBuf.data()));

    std::cout << "byte length of test vector: " << len << std::endl;

    //send pubkey
    boost::asio::streambuf streBuf;
    std::ostream outStre(&streBuf);
    
    
    outStre << "pub";
    public_key.writeToJSON(outStre);
    
    outStre<< "#";


    
    len = boost::asio::write(socket, boost::asio::buffer(streBuf.data()), err);
    std::cout << "length of public key: " << len << std::endl;

    

    

     */

    for(;;){}

    //send encrypted vector
    
    }
    catch(std::exception& e) {
        std::cout<< e.what() << std::endl;
    }
    
    std::cout <<"end of client" << std::endl;
   
    return 0;

    }




   
