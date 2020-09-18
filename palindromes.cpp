#include <iostream>
#include <string>
#include <algorithm> 
#include <iterator> 

#include<sstream>
#include<vector>


//#include<algorithm>

bool IsPalindromeWay1(std::string input) {
    for(int k = 0; k < (input.size() ) ; ++k) {

        int punteroFinal = input.length() -k-1;
        std::cout << k <<" "<< input[k]<< " " << input[punteroFinal] <<std::endl;

        if( input[k] != input[punteroFinal] ) {
            return false;
        } 
            
    }
        
    return true;
}


bool IsPalindromeWay2(std::string input) {

    std::string reversed = input; 
    std::reverse ( input.begin(),   input.end() ); 
    return reversed == input;

}

bool IsNotAlpha(char ch) {
        return !isalpha(ch);
}

bool IsPalindromeWay3(std::string input) {

    input.erase(  remove_if(input.begin(),    input.end(),    IsNotAlpha  )   , input.end());

    transform(input.begin(), input.end(), input.begin(), ::toupper);

    return std::equal(input.begin(),  input.begin() + input.size() / 2,  input.rbegin());
}





 bool IsNotAlphaOrSpace(char ch) {
        return !isalpha(ch) && !isspace(ch);
}
 
bool IsWordPalindrome(std::string input) {
    
    input.erase(std::remove_if(input.begin(), input.end(), IsNotAlphaOrSpace), input.end());
    
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    
    std::stringstream tokenizer(input);
    std::vector<std::string> tokens;

    std::string token;
    tokens.insert(tokens.begin(),   
                 std::istream_iterator<std::string>(tokenizer), 
                 std::istream_iterator<std::string>());

    // while(tokenizer >> token){
    //     tokens.push_back(token);
    // }
        
    return equal(tokens.begin(), tokens.begin() + tokens.size() / 2, tokens.rbegin());
}




int main() {

    // std::cout << IsPalindromeWay1 ("partytrap") ;

    //std::cout << IsPalindromeWay2 ("partytrap") ;

    std::cout << IsPalindromeWay3 ("partytrap") ;
    return 0;
}
