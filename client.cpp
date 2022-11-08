#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <time.h>
#include <string>
#include <algorithm>

#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <helib/JsonWrapper.h>
#include <helib/helib.h>

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



//1: save, 2: load
//return 1 on success, 0 on  fail









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

  // Create a vector of long with nslots elements
  helib::Ptxt<helib::BGV> ptxt(hel_context);

    


    for(int i=0;i<ptxt.size();i++){
        ptxt[i] = test[i];
    }


    helib::Ctxt ctxt(public_key);

    public_key.Encrypt(ctxt, ptxt);
 

    
    
    boost::asio::streambuf strBuf;
    std::ostream outStr(&strBuf);
    
    
    outStr << "con";
    //public_key.writeTo(outStr);
    hel_context.writeTo(outStr); 
    outStr<< "#";


  /* std::ofstream outPublicKeyFile;
  outPublicKeyFile.open("pkc.json", std::ios::out);
  if (outPublicKeyFile.is_open()) {
    // Write the public key to a file
    public_key.writeToJSON(outPublicKeyFile);
    // Close the ofstream
    outPublicKeyFile.close(); 
  } else {
    throw std::runtime_error("Could not open file 'pk.json'.");
  }
    */

    //send context, public key, and then vector

    try{
    boost::asio::io_context io_ctx;
    tcp::resolver resolver(io_ctx);

    //how you resolve an arbitrary ip_addr
    tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "1337");


    tcp::socket socket(io_ctx);

    boost::asio::connect(socket, endpoints);
    boost::system::error_code err;
    //boost::asio::buffer
    size_t len = boost::asio::write(socket, boost::asio::buffer(strBuf.data()), err);

    std::cout << "size of message: " << len << std::endl;
    
   

    //send pubkey
    boost::asio::streambuf streBuf;
    std::ostream outStre(&streBuf);
    
    
    outStre << "pub";
    public_key.writeToJSON(outStre);
    
    outStre<< "#";

    std::ofstream outPublicKeyFile;
  outPublicKeyFile.open("pk_client.json", std::ios::out);
  if (outPublicKeyFile.is_open()) {
    // Write the secret key to a file
    public_key.writeToJSON(outPublicKeyFile);
    // Close the ofstream
    outPublicKeyFile.close();
  } else {
    throw std::runtime_error("Could not open file 'pk_client.json'.");
  }

    
    len = boost::asio::write(socket, boost::asio::buffer(streBuf.data()), err);
    std::cout << "length of public key: " << len << std::endl;

    for(;;){}

    //send encrypted vector
    
    }
    catch(std::exception& e) {
        std::cout<< e.what() << std::endl;
    }
    
    std::cout <<"end of client" << std::endl;
    return 0;

    }
