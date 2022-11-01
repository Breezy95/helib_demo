#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <time.h>
#include <string>
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/array.hpp>
//#include <helib/helib.h>

using namespace std;
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


int main(){

    srand(3454);
    int random = rand()* 1000000;

    /* cout << slow_print{"It is the year 2134. Abject poverty, political infighting and self-preservation politics \n have lead to apathy and disillusionment in the public space.",100};
    cout << slow_print{"   \n", 1000};
    cout << slow_print{"You are another citizen, and like every other citizen with no path to economic upheaval", 100};
    cout << slow_print{". . .\n", 500};
    cout << slow_print{"You play a fools game.", 100} << slow_print{"\n",1500} << 
    slow_print{"The Lottery\n", 100};
    
    
    cout << slow_print{"Hello citizen #" + to_string(random) + " of district 20\n",50}; */
    

    //cout << "enter 10 numbers for your monthly lottery session from 0 to 99. Order WILL matter!\n";
    //string val[10];
    //string* choices = selectionLoop(val);
    
    
    //now encrypt ints
    //0 - 99 in binary is 0b0 - 0b1100011, maximum bit size is 7

    vector<int> test = {0,1,2,3,4,5,6,68,8,9};

    
    try{
    boost::asio::io_context io_ctx;
    tcp::resolver resolver(io_ctx);

    //how you resolve an arbitrary ip_addr
    tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "1337");


    tcp::socket socket(io_ctx);

    boost::asio::connect(socket, endpoints);
    boost::system::error_code err;
    size_t len = boost::asio::write(socket, boost::asio::buffer(test), err);
    
    }
    catch(std::exception& e) {
        std::cout<< e.what() << std::endl;
    }
    
     
    return 0;

}