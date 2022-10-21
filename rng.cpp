#include <iostream>
#include <random>
#include <string>

using namespace std;

  class int_LotteryGen {

  public:

  int_LotteryGen(int amt, int lo, int hi) : gen(random_device{}()),distr(lo,hi) {
    number_gen(amt,lo,hi);
  }

  int_LotteryGen(){
  
  }



      vector<string> number_gen(int amount, int low, int high){
        winning_comb.resize(0);
        for(int i=0;i<amount;i++){
          winning_comb.push_back((to_string(distr(gen))));
        }

        return this->winning_comb;
      }

      vector<string> winning_comb;

  private:
    mt19937 gen;
    uniform_int_distribution<> distr;


  };



 
int main(){

int_LotteryGen lotto(10,0,99);
cout <<lotto.winning_comb.size() <<endl; 

return 0;
}