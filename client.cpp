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

    //pubkey.writeTo(output);
    pay_len = boost::asio::write(sock,temp_buf,boost::asio::transfer_all());
    sbuf.consume(pay_len);
    
    std::cout << "size of msg: " << pay_len << std::endl;
    std::cout << "size of streambuf: " << temp_buf.size() << std::endl;

    return pay_len;
}

size_t send_values(boost::asio::ip::tcp::socket& sock, boost::asio::streambuf& sbuf, helib::Ctxt ctxt){

    std::ostream output(&sbuf); 
    boost::asio::streambuf temp_buf;
    std::ostream temp_str(&temp_buf);
    ctxt.writeToJSON(temp_str);
    int32_t size = temp_buf.size();
    
    //send value first
    std::stringstream ss;
    ss << std::setw(10) << std::setfill('0') << size;
    std::string s = ss.str();
    std::cout << "size of payload: " << s << std::endl;
    output << s;

    size_t pay_len = sock.send(sbuf.data());
     

    //send ctxt vector
    pay_len = sock.send(temp_buf.data());

    
    
    

return pay_len;  
}



int main(){

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

  std::vector<long> test = {10};
  long bitSize = 16;
  long outSize = 2* bitSize;
  long entry = test[0];


  helib::Ctxt scratch(public_key);
  std::vector<helib::Ctxt> encrypted_data(bitSize, scratch);

  for(int i =0;i<bitSize;i++){
    std::vector<long> data(ea.size());

    for (auto& slot : data){ slot = (entry >> i) & 1; }

    ea.encrypt(encrypted_data[i], public_key, data);
    }

    std::vector<long> decrypt;
    helib::CtPtrs_vectorCt result_wrapper(encrypted_data);

    helib::decryptBinaryNums(decrypt, result_wrapper, secret_key, ea);
    

    //now send data over connection
    boost::asio::io_context io_context;

    tcp::socket socket(io_context);
    boost::asio::ip::address_v4 addr({127,0,0,1});
    boost::asio::ip::tcp::endpoint endpt(addr,1337);
    socket.connect(endpt);
    boost::array<char, 128> buf;
    
        
        boost::system::error_code error;
        //oper
        try{
        size_t len = boost::asio::read(socket,boost::asio::buffer(buf),boost::asio::transfer_exactly(5) ,error);
        std::cout <<"length of message in bytes: " << len <<std::endl;
        std::cout<< "message: " << buf.data() << std::endl;
        if( error == boost::asio::error::eof){
            throw boost::asio::error::eof;
            }
        if(error){
            throw boost::system::system_error(error);
            }
        }
        catch(std::exception& e){
            std::cout << e.what() << std::endl;
            }

        //len
        try{
            boost::array<char, 128UL> s;
            size_t len = boost::asio::read(socket,boost::asio::buffer(s),boost::asio::transfer_exactly(10) ,error);
            std::cout <<"length of message in bytes: " << len <<std::endl;
        std::cout<< "message: "; std::cout.write(buf.data(),10) << std::endl;
        if( error == boost::asio::error::eof){
            throw boost::asio::error::eof;
            }
        if(error){
            throw boost::system::system_error(error);
            }
        }
        catch(std::exception& e){
            std::cout << e.what() << std::endl;
            }

        //payload
            try{
            size_t len = boost::asio::read(socket,boost::asio::buffer(buf),boost::asio::transfer_exactly(12) ,error);
            std::cout <<"length of message in bytes: " << len <<std::endl;
        std::cout<< "message: " << buf.data() << std::endl;
        if( error == boost::asio::error::eof){
            throw boost::asio::error::eof;
            }
        if(error){
            throw boost::system::system_error(error);
            }
        }
        catch(std::exception& e){
            std::cout << e.what() << std::endl;
            }

        //send bytestream of helib file
        
        

    
    
    
    

    


  



  
  


   
    return 0;

    }




   
