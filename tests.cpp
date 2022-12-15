#include <iostream>
#include <helib/helib.h>
#include <helib/assertions.h>
#include <cassert>


int main(){

helib::Context* client_con;
helib::Context* server_con;

std::cout << "reading  context files: " << std::endl;
    //context test
 std::ifstream inContextFile;
  inContextFile.open("client_context.json", std::ios::in);
  if (inContextFile.is_open()) {
    // Read in the context from the file
    client_con = helib::Context::readPtrFromJSON(inContextFile);
    inContextFile.close();
  } else {
    throw std::runtime_error("Could not open file 'client_context.json'.");
  } 

  

std::ifstream inContextFile2;
  inContextFile.open("server_context.json", std::ios::in);
  if (inContextFile.is_open()) {
    // Read in the context from the file
    server_con = helib::Context::readPtrFromJSON(inContextFile);
    inContextFile.close();
  } else {
    throw std::runtime_error("Could not open file 'server_context.json'.");
  } 
  
 
  

  std::cout << "reading public keys: " << std::endl;


    //public key tests
    helib::PubKey* client_pubkey;
    helib::PubKey* server_pubkey;

    std::ifstream inpubkeyFile;
    helib::PubKey test(*client_con);
  inpubkeyFile.open("client_pubkey.json", std::ios::in);
  if (inpubkeyFile.is_open()) {
    // Read in the context from the file
     test.readJSON(inpubkeyFile);
     client_pubkey = &test;
    inpubkeyFile.close();
  } else {
    throw std::runtime_error("Could not open file 'client_context.json'.");
  }




  std::ifstream servpubkeyFile;
  servpubkeyFile.open("server_pubkey.json", std::ios::in);
  helib::PubKey deserializedPubkey(*server_con);
  if (servpubkeyFile.is_open()) {
    // Read in the context from the file
     deserializedPubkey.readJSON(servpubkeyFile);
        
        server_pubkey = &deserializedPubkey;
        
    servpubkeyFile.close();
  } else {
    throw std::runtime_error("Could not open file 'client_context.json'.");
  } 



std::cout << "reading ctxts"<< std::endl; 

    //ctxts
    helib::Ctxt* client_ctxt;
    helib::Ctxt* serv_ctxt;
    std::ifstream servCtxtFile, clCtxtFile;
    helib::Ctxt cl_ctxt(*client_pubkey);
    helib::Ctxt server_ctxt(*server_pubkey);

    
  clCtxtFile.open("client_ctxt.json", std::ios::in);
  if (clCtxtFile.is_open()) {
    // Read in the ctxt from the file
    cl_ctxt.readFromJSON(clCtxtFile, *client_pubkey);
    client_ctxt = &cl_ctxt;
    
    
    
    clCtxtFile.close();
  } else {
    throw std::runtime_error("Could not open file 'client_ctxt.json'.");




    servCtxtFile.open("server_ctxt.json", std::ios::in);
  if (servCtxtFile.is_open()) {
    // Read in the ctxt from the file
    server_ctxt.readFromJSON(servCtxtFile, *server_pubkey);
    serv_ctxt = &server_ctxt;

    servCtxtFile.close();
  } else {
    throw std::runtime_error("Could not open file 'server_ctxt.json'.");

  } 



    
}


//test if server and client objects are the same in this case
 helib::assertEq(client_pubkey->getContext(),server_pubkey->getContext(),"client and server public keys are not equal");
 helib::assertEq(*client_con,*server_con,"client and server context are not equal");
 std::cout << cl_ctxt << std::endl << server_ctxt;
 


 //test if server context is equal to the context of other server objects



 //test if client context is equal to the context of other client objects


 


  
}