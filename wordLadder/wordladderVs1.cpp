#include <iostream>
#include <set>
#include <fstream>
#include <queue>

// ESTAS LIBRERIAS SON PRESINDIBLES
#include <ctime>   // ESTA ES PARA CALCULAR EL TIEMPO TRANSCURRIDO


/*
    THIS PROGRAMM IMPLEMENT THE wordLadder_finder. 
    A WORD LADDER IS A CONNECTION FROM ONE WORD TO ANOTHER FORMED BY CHANGING 
    ONE LETTER AT A TIME WITH THE CONSTRAINT THAT AT EACH STEP THE 
    SEQUENCE OF LETTERS STILL FORMS A VALID WORD.
    FOR EXAMPLE , HERE IS A WORD LADDER CONNECTING "code" TO "data".

    1.  code -> cade -> cate -> date -> data
    2.  work -> fork -> form -> foam -> flam -> lay -> play
    3.  sleep -> sheep -> sheen -> shewn -> shawn -> sharn -> share -> sware -> aware -> awake

    THIS ITS THE VERSION_1 VERY EARLY IMPLEMENTATION WITHOUT ANY IMPROVEMT IN PERFORMANCE

    //  work-play  ESTUDIAR
    //  sleep-sware  219.161 seg   [ sleep,steep,steen,stern,starn,stare,sware, ]
    //  angel-level  14.7172 seg   [ angel,anger,auger,luger,leger,lever,level, ]
    //  sleep-sharn  62.5573 seg   [ sleep,sheep,sheen,shewn,shawn,sharn, ]
    //  work-flam    113.849 seg   [ work,fork,form,foam,flam, ]


*/

bool mutarPalabra(std::string wordTarget, std::set<std::string> dictionary, std::queue< std::vector<std::string> >& queueLadders ,  std::vector<std::string > &currentVector,std::set<std::string> & wordVisited);
void showVector(std::vector<std::string > &vec);


int main () {

   

    // std::string fileName = "dictionarySimple.txt";
    std::string fileName = "dictionary.txt";
    std::ifstream fileStream;

    //  OPENING THE FILE
        fileStream.open(fileName);

    //  CHEK OPEN ERRORS
        if(fileStream.fail()){
                std::cout <<"the file can't OPEN"<< "\n" ;
                return -1;
        }

    //  LOAD THE DATA, INTO A SET
        std::string linea="";
        std::set<std::string> dictionary;
        
        while(fileStream >> linea) {

            dictionary.insert(linea);

        }

       
    //  CREATING A QUEUE FOR STORE LADDERS 
        std::queue< std::vector<std::string> > queueLadders;

    //  work-play  ESTUDIAR
    
    //  sleep-sware  219.161 seg   [ sleep,steep,steen,stern,starn,stare,sware, ]
    //  angel-level  14.7172 seg   [ angel,anger,auger,luger,leger,lever,level, ]
    //  sleep-sharn  62.5573 seg   [ sleep,sheep,sheen,shewn,shawn,sharn, ]
    //  work-flam    113.849 seg   [ work,fork,form,foam,flam, ]


    //  DEFINING THE START AND TARGET
        std::string wordStart    = "love";
        std::string wordTarget   = "baby";
        

    //  DEFINING VECTOR WITH wordStart   
        std::vector<std::string > vectorIncial{wordStart};

    //  PUSHING THE STARTED VECTOR
        queueLadders.push(vectorIncial);

    //  DEFINING VARIABLE FOR KNOW IF THE MUTATION MATH WITH OR NOT THE wordTarget
        bool resultMutation = false;  

    //  DEFINING A SET FOR STORE NODES ALLREADY VISITED    
        std::set<std::string> wordVisited;

    int tstart = clock();

    //  TRACKING ALL THE QUE
        while (!queueLadders.empty()) 
        {   
                
                //  GET THE VECTOR THAT ITS IN FRONT OF THE VECTOR 
                    std::vector<std::string > tmpVector = queueLadders.front();
               
                //  MUTAMOS LA ULTIMA PALABRA QUE SE ENCUENTRE EN EL VECTOR
                   resultMutation = mutarPalabra(wordTarget, dictionary, queueLadders , tmpVector,  wordVisited);
                    
                //  CHEKING IF THE MUTATION MAKE MATCH WITH wordTarget    
                    if(resultMutation){

                         std::cout <<  "Encontro la escalera";
                         break;   
                    }

                //  ELIMINAMOS EL VECTOR DE LA QUEUE
                    queueLadders.pop(); 

        }

    //  SHOWING THE TIME ELAPSED AFTER APPLY MERGE SORT
        int endTime = clock();
        double etime = (tstart - endTime) / (double) CLOCKS_PER_SEC;
        std::cout << "TIME ELAPSED : "<< etime ;


    //  CHECKING AGAIN IF THE MUTATION MAKE MATCH WITH wordTarget OR GET EMPTY THE QUEUE
        if(resultMutation) {
                
            //  RECOVERY THE SUCCESS VECTOR     
                std::vector<std::string > vectorResult = queueLadders.back();

            //  SHOWING THAT VECTOR ON SCREEN    
                showVector(vectorResult);
                
        }else{

            std::cout<<"no se encontro escalera"<<"\n";
        }

               




        //  std::cout <<"word ladder \n";
    return 0;
}






bool mutarPalabra(std::string wordTarget, std::set<std::string> dictionary, std::queue< std::vector<std::string> >& queueLadders ,  std::vector<std::string > &currentVector,std::set<std::string> & wordVisited) {
   
    //  SETTING WHOLE ABECEDARIO
        std::string abcedario = "abcdefghijklmnopqrstuvwxyz";

    //  GETTING THE LAST WORD IN THE CURRENTVECTOR (currentLadder), WHICH REPRESENT THE LAS NODE VISITED FOR THAT ROUTE
        auto iterador = currentVector.end() - 1;
        std::string word = *iterador;
        std::string wordTmp = word;



    std::cout<< "\n\n\n<------------VAMOS A MUTAR LA PALABRA ---------------->\n" ;
    std::cout<< "<--------------------- " << word << "----------------------->\n\n\n";

    std::string result="";


    for (int p =0 ; p < word.length() ; p++){  // word letters Loop
     
        
         for (int i =0 ; i < abcedario.length(); i++) {  // abecedario Loop
           

            wordTmp[p] = abcedario[i] ; // mutamos la word

            if( dictionary.count(wordTmp)  && word != wordTmp   &&   !wordVisited.count(wordTmp) ) {  // check if exists in the dictionary

               
                std::vector<std::string> tmpVector = currentVector;  // create a new vector with tha same information of the current vector

               
                

                tmpVector.push_back(wordTmp);   // adding the validated word to the new vector

                queueLadders.push(tmpVector);   // adding the new vector to queueLadder
                
                // std::vector<std::string > vectorResult = queueLadders.front();
                // std::vector<std::string > vectorResult = queueLadders.back();
                // showVector(vectorResult);

                wordVisited.insert(wordTmp);

                // std::cout <<  wordTmp << " - YES - "<< "\n";

                 

                if (wordTmp == wordTarget) {

                    
                    
                    // std::cout <<"encontramos el objetivo : " << wordTmp <<"\n";
                     
                    return true;
                   
                }

            }
            // else{
            //   std::cout <<  wordTmp <<  "\n";
            // }
                   
        
        }// End for abecedario Loop

        //  RESET THE TEMPORARY wordTemp    
            wordTmp = word;



    }// End for word letters Loop


     return false;
}




void showVector(std::vector<std::string > &vec) {

     std::cout << "\n\n Tamano del vector " << vec.size()  << "\n ";

                std::cout << "[ ";

                for(auto itr = vec.begin();  itr<vec.end();  itr++) {
                    std::cout << *itr << ',' ; 
                }

                std::cout << " ] " ;//<< '\t'

}