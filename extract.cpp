#include <iostream>


void foo(){

    //unsigned long call_id = reinterpret_cast<unsigned long>(__builtin_extract_return_addr(__builtin_return_address(0)));
    unsigned long call_id = reinterpret_cast<unsigned long>(_ReturnAddress());
   
    std::cout << call_id << std::endl;


}
int main(){

for(int i =0 ; i < 5 ; i++){
foo();

foo();

}

}
