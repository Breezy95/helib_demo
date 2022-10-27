#include <iostream>
#include <random>
#include <string>
#include <fstream>


using namespace std;

  class int_LotteryGen {

  public:

  int_LotteryGen(){}
  
  int_LotteryGen(int amt, int lo, int hi) : gen(random_device{}()),distr(lo,hi) {
    number_gen(amt,lo,hi);
  }

  

      void clear(){
        winning_comb.resize(0);
      }



      vector<string> number_gen(int amount, int low, int high){
        
        for(int i=0;i<amount;i++){
          winning_comb.push_back((to_string(distr(gen))));
        }

        return this->winning_comb;
      }

/* 
      void save_current(){
        if(winning_comb.size() == 0)
          number_gen(10,0,99);
        std::ofstream outdata;

        try{
        outdata.open("current_key_list");
        winn
        }
        catch(std::exception& e){
          cout << e.what() << endl;
        }
         
        
        }

        
      
      

      void save_to_file(std::string, int lines = 1){

      }

 */      vector<string> winning_comb;

  private:
    mt19937 gen;
    uniform_int_distribution<> distr;


  };



 