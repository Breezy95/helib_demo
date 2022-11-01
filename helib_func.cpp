//implement easy string/num  encrpytion
//implement string matching
#include <iostream>
#include <helib/helib.h>
#include <helib/EncryptedArray.h>
#include <NTL/BasicThreadPool.h>
#include <vector>

helib::Context* contextSupplier(){
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
}
//supply_context?
int main(){
  std::vector<int> test = {0,1,2,3,4,5,6,68,8,9};
  helib::Context* context = contextSupplier();


    helib::SecKey secretkey(*context);
    secretkey.GenSecKey();

    const helib::PubKey& publicKey = secretkey;

    helib::PtxtArray p0(*context, test);
    helib::Ctxt c0(publicKey);

    p0.encrypt(c0);

    helib::Ctxt c1 = c0;
    c1 *=2.0;


     // First, we construct a new PtxtArray pp3.
  helib::PtxtArray pp3(*context);

  // Next, we decrypt c3, storing the plaintext in p3:
  pp3.decrypt(c1, secretkey);

  // Finally, we store the PtxtArray p3 into a standard vector v3:
  std::vector<double> v3;
  pp3.store(v3);

 std::cout<< v3[0];
    
   return 0; 
}


//encryption of list of int values
//helib::Ctxt encrypt_int_values(std::vector<int>*, helib::Context* con){

//}

//check for other parameters that may be needed, like context
bool string_match_ctxts(helib::Ctxt *a, helib::Ctxt *b){
return true;
}



