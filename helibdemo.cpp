#include <helib/helib.h>
#include <helib/binaryArith.h>
#include <helib/intraSlot.h>
#include <NTL/BasicThreadPool.h>
#include <vector>

using namespace std;
using namespace helib;

int main() {
  
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

cout << *context.getM();

return 0;
}
/* 
  context.printout();

  cout << "Security level: " << context.securityLevel() << endl;

  //creates secret key from context
  helib::SecKey secret_key(context);

  // generate sec key
    secret_key.GenSecKey();

    secret_key.genRecryptData();

  //set secret key, SecKey is subclass of pubkey
    const helib::PubKey& public_key = secret_key;

    const helib::EncryptedArray& ea = context.getEA();

    //build unpack slot encoding??
     std::vector<helib::zzX> unpackSlotEncoding;
    buildUnpackSlotEncoding(unpackSlotEncoding, ea);

    //Get the number of slot (phi(m)).
    long nslots = ea.size();
    cout << "Number of slots: " << nslots << endl;

    /* IMPORTANT
    We want to gen numbers, encrypt them with
     Helib using the BGV cryptosystem  make a calculation with Helibs, binary arithmetic
    funcs. and then decrypt with Helib

    each bit of a binary number is encoded into a ciphertext,
    for 16 bit binary nums you get

    b1 = 0,0,0,0,...,0
    b2 = 1,1,1,1,...,1 
    b3 = 1,1,1,1,...,1

    which is 110b or 6

    each position in the array can also be a different binary number

    b1 = 0,1,
    b2 = 1,0,
    b3 = 0,1
    */

long bitSize = 16;
long outSize = 2*bitSize;
long a_data = NTL::RandomBits_long(bitSize);
long b_data = NTL::RandomBits_long(bitSize);
long c_data = NTL::RandomBits_long(bitSize);

cout << "Pre-encryption data:" << endl;
cout << "a = " << a_data << endl;
cout << "b = " << b_data << endl;
cout << "c = " << c_data << endl;

//use to populate vectors
helib::Ctxt scratch(public_key);

std::vector<helib::Ctxt> encrypted_a(bitSize, scratch);
  std::vector<helib::Ctxt> encrypted_b(bitSize, scratch);
  std::vector<helib::Ctxt> encrypted_c(bitSize, scratch);

  //encrypt data in binary rep

  for(long i = 0 ;i< bitSize; i++){
    vector<long> a_vec(ea.size());
    vector<long> b_vec(ea.size());
    vector<long> c_vec(ea.size());
    //bitshift right by i with And operator against 1
    for(auto& slot: a_vec)
      slot = (a_data >> i) & 1;

    for(auto& slot: b_vec)
      slot = (a_data >> i) & 1;

    for(auto& slot: c_vec)
      slot = (a_data >> i) & 1;

    ea.encrypt(encrypted_a[i], public_key, a_vec);
    ea.encrypt(encrypted_b[i], public_key, b_vec);
    ea.encrypt(encrypted_c[i], public_key, c_vec);
  }


//cout << "Value of encrypted a:  " << encrypted_a.at(0)<< endl;
//  cout << "Value of encrypted b:  " << encrypted_b[0]<< endl;
//cout << "Value of encrypted c:  " << encrypted_c[0]<< endl;

vector<helib::Ctxt> enc_prod;
helib::CtPtrs_vectorCt product_wrapper(enc_prod);
helib::multTwoNumbers( product_wrapper, helib::CtPtrs_vectorCt(encrypted_a), helib::CtPtrs_vectorCt(encrypted_b),
  false, //right hand side twos complement, unsigned or signed
  outSize, // limit of bits in output 2^5
  &unpackSlotEncoding // used for bootstrapping dont worry about it
);

vector<long> decrypted_prod;
 */

  

  



}
