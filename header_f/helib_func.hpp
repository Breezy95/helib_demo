#include <iostream>

#include <vector>


#ifndef helib_func
#define helib_func

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

bool string_match_ctxts(helib::Ctxt *a, helib::Ctxt *b){
return true;
}

helib::Ctxt encrypt_int_values(std::vector<int>& vec, helib::Ptxt<helib::BGV> ptxt ,helib::PubKey pub){
  for(auto iter = vec.cbegin();iter != vec.cend();iter++){
      ptxt[iter - vec.cbegin()] = *iter;
  }

  helib::Ctxt ctxt(pub);
  pub.Encrypt(ctxt, ptxt);
  
  return ctxt;
}

#endif
