#include <iostream>
#include <set>

std::set<char>  setFromString(std::string str);

void ejemplo1 () {
    
    std::set<char> mySet(setFromString("abcdefghijklmnopqrstuvwxyz") );

    char wordTest[] ="prueba";
    std::string wordTestString  ="tito";
    
    for(auto itr = mySet.begin() ; itr != mySet.end() ; itr++)  {
      
       wordTest[0]= *itr;
    //     std::cout << wordTest <<"\n";
        wordTestString[0]=*itr;
        std::cout << wordTestString <<"\n";

    }
}

void ejemplo2() {

    std::string abcedario = "abcdefghijklmnopqrstuvwxyz";

    std::string word= "data";
    std::string wordTmp = word;
    for (int p =0 ; p < word.length() ; p++){
     
        
         for (int i =0 ; i < abcedario.length(); i++) {
           
            wordTmp[p] = abcedario[i] ;
            std::cout <<  wordTmp <<"\n";

        }
        wordTmp = word;
        std::cout<< "---------------" <<"\n";
    }

       
       
    

}


int main (){

    ejemplo2();


}




std::set<char>  setFromString(std::string str) {

    std::set<char> mySet;
    for (int i =0 ; i < str.length(); i++) {
        mySet.insert(str[i]);
    }
    return mySet;
}


