//implement easy string/num  encrpytion
//implement string matching
#include <iostream>
#include <helib/helib.h>

#include <NTL/BasicThreadPool.h>
#include <vector>
#include "header_f/helib_func.hpp"

/* helib::Context* contextSupplier(){
long p= 2;
  long m = 4095;
  long r = 1;
  long c = 2;
  long bits = 500;
  std::vector<long> mvec = {7,5,9,13};
  std::vector<long> gens = {2341,3277,911};
  std::vector<long> ords = {6,4,6};

  helib::Context* context = helib::ContextBuilder<helib::BGV>()
  .m(m)
  .p(p)
  .r(r)
  .gens(gens)
  .ords(ords)
  .bits(bits)
  .c(c)
  .mvec(mvec)
  .bootstrappable(true)
  .buildPtr();

  return context;
} */
//supply_context?
int main(){
  std::vector<int> test = {0,1,2,3,4,5,6,68,8,9};

  helib::Context* context = helib_func::contextSupplier();

  

    
   return 0; 
}


//encryption of list of int values
//helib::Ctxt encrypt_int_values(std::vector<int>*, helib::Context* con){

//}

//check for other parameters that may be needed, like context
/* bool string_match_ctxts(helib::Ctxt *a, helib::Ctxt *b){
return true;
} */




