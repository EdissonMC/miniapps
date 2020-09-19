#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <fstream>


#include<cctype>



/*
    THIS PROGRAMM IMPLEMENT THE wordLadder_finder. 
    A WORD LADDER IS A CONNECTION FROM ONE WORD TO ANOTHER FORMED BY CHANGING 
    ONE LETTER AT A TIME WITH THE CONSTRAINT THAT AT EACH STEP THE 
    SEQUENCE OF LETTERS STILL FORMS A VALID WORD.
    FOR EXAMPLE , HERE IS A WORD LADDER CONNECTING "code" TO "data".

    1.  code -> cade -> cate -> date -> data
    2.  work -> fork -> form -> foam -> flam -> lay -> play
    3.  sleep -> sheep -> sheen -> shewn -> shawn -> sharn -> share -> sware -> aware -> awake

    THIS ITS THE VERSION_2 IMPLEMENTATION IMPROVEMT THE PERFORMANCE USIN PRIORITY-QUEUE 

    //  angel-level 1.82561 seg [ angel,anger,auger,luger,leger,lever,level, ]   
    //  sleep-sharn 1.1477  seg [ sleep,sheep,sheen,shewn,shawn,sharn, ] 
    //  work-flam   0.90234 seg [ work,fork,form,foam,flam, ] 
    //  sleep-sware 2.52802 seg [ sleep,sweep,sweel,swell,swill,swirl,swire,sware, ] 
    //  work-play   3.37488 seg [ work,pork,pory,poxy,pixy,pioy,ploy,play, ]


*/



void showVector(std::vector<std::string > &vec);

template<typename T> 
bool mutarPalabra(std::string wordTarget, std::set<std::string> dictionary, T& queueLadders ,  std::vector<std::string > &currentVector,std::set<std::string> & wordVisited) ;

void compararLastWord();


template<typename T> 
void print_queue(T& q) {

    while(!q.empty()) {
        
        std::vector <std::string> myVector= q.top();
        q.pop();

         std::cout<< "{ ";
           for(std::vector <std::string>::iterator itr = myVector.begin();
                            itr != myVector.end() ;
                            ++itr){
                            
                          std::cout <<*itr<<" ";

            }
            std::cout<< " }\n";
    }

    std::cout << '\n';

}




int main() {

        //  std::string fileName = "dictionarySimple.txt";
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


    //  angel-level 1.82561 seg [ angel,anger,auger,luger,leger,lever,level, ]   
    //  sleep-sharn 1.1477  seg [ sleep,sheep,sheen,shewn,shawn,sharn, ] 
    //  work-flam   0.90234 seg [ work,fork,form,foam,flam, ] 
    //  sleep-sware 2.52802 seg [ sleep,sweep,sweel,swell,swill,swirl,swire,sware, ] 
    //  work-play   3.37488 seg [ work,pork,pory,poxy,pixy,pioy,ploy,play, ]
    //  whole-blame 2.89844 seg [ whole,whale,shale,shave,slave,clave,clame,blame, ]
    //  zoolater-agaroses  -No se encontro escalera-

    //  DEFINING THE START AND TARGET
        std::string wordStart    = "angel"; 
        std::string wordTarget   = "level";



    //  USING LAMBDA TO COMPARE TWO VECTORES.
    //  THIS FUNCTION COMPARE LAST WORD IN EVERY VECTOR WITH  THE TARGET WORD
    //  CHECKING EVERY LETTER AND COUNTING THE LETTER THAT MAKE MATCH 
    //  THIS COUNTING LET THE PRIORITY-QUEUE ORGANIZE ALL THE VECTORS
        auto cmp = [wordTarget] ( std::vector<std::string>  vectorLeft, std::vector<std::string>  vectorRight) { 

            //  RECOVERING LAST WORD IN THE VECTORLEFT
                auto itr1 = vectorLeft.end() - 1;
                std::string word1 = *itr1;

            //  RECOVERING LAST WORD IN THE VECTORRIGHT    
                auto itr2 = vectorRight.end() - 1;
                std::string word2 = *itr2;

            //  COMPARING THE LAST WORD WITH TARGETWORD
                int contadorLeft=0;
                for (int i =0 ; i < word1.length(); i++) {
                    if(word1[i] == wordTarget[i]) {
                        contadorLeft++;
                    }
                }

            //  COMPARING THE LAST WORD WITH TARGETWORD
                int contadorRight=0;
                for (int i =0 ; i < word2.length(); i++) {
                    if(word2[i] == wordTarget[i]) {
                        contadorRight++;
                    }
                }

            //  std::cout <<"contadorLeft = "<<contadorLeft <<"  contadorRight = " << contadorRight  << "\n";

            //  RUNING THE COMPARATION
                return (contadorLeft ) < (contadorRight ); //^ 1

        };
        //  END USING LAMBDA TO COMPARE TWO VECTORES.
        



    //  CREATING A QUEUE FOR STORE LADDERS 
        std::priority_queue< std::vector<std::string>,
                            std::vector< std::vector<std::string> >,
                            decltype(cmp)  >     queueLadders(cmp);



    //  DEFINING VECTOR WITH wordStart   
        std::vector<std::string > vectorIncial{wordStart};


    //  PUSHING THE STARTED VECTOR
        queueLadders.push(vectorIncial);


     //  DEFINING VARIABLE FOR KNOW IF THE MUTATION MATH WITH OR NOT THE wordTarget
        bool resultMutation = false;  


    //  DEFINING A SET FOR STORE NODES ALLREADY VISITED    
        std::set<std::string> wordVisited;


    //  STARTING THE CLOCK FOR CHECK THE TIME, FOR THE ALGORITHM
        int tstart = clock();



    //  TRACKING ALL THE PRIORITY-QUEUE
        while (!queueLadders.empty()) 
        {   
                
                //  GET THE VECTOR THAT ITS IN FRONT OF THE VECTOR 
                    std::vector<std::string > tmpVector = queueLadders.top();
                
                //  ELIMINAMOS EL VECTOR DE LA QUEUE    
                    queueLadders.pop(); 


                //  MUTAMOS LA ULTIMA PALABRA QUE SE ENCUENTRE EN EL VECTOR
                    resultMutation = mutarPalabra(wordTarget, dictionary, queueLadders , tmpVector,  wordVisited);
                    

                //  CHEKING IF THE MUTATION MAKE MATCH WITH wordTarget    
                    if(resultMutation){

                         std::cout <<  "Encontro la escalera";
                         break;   
                    }

                    std::cout<<"\nsiguiente vector en la queue ->\n";
                   
        }
    //  END TRACKING ALL THE PRIORITY-QUEUE



    //  SHOWING THE TIME ELAPSED AFTER APPLY MERGE SORT
        int endTime = clock();
        double etime = (tstart - endTime) / (double) CLOCKS_PER_SEC;
        std::cout << "\nTIME ELAPSED : " << etime ;



    //  CHECKING AGAIN IF THE MUTATION MAKE MATCH WITH wordTarget OR GET EMPTY THE QUEUE
        if(resultMutation) {
                
            //  RECOVERY THE SUCCESS VECTOR     
                std::vector<std::string > vectorResult = queueLadders.top();

            //  SHOWING THAT VECTOR ON SCREEN    
                showVector(vectorResult);
                
        }else{

            std::cout<<"no se encontro escalera"<<"\n";
        }

        
    return 0;

}
// END MAIN()




template<typename T> 
bool mutarPalabra(std::string wordTarget, std::set<std::string> dictionary, T& queueLadders ,  std::vector<std::string > &currentVector,std::set<std::string> & wordVisited) {  

    //  SETTING WHOLE ABECEDARIO
        std::string abcedario = "abcdefghijklmnopqrstuvwxyz";

    //  GETTING THE LAST WORD IN THE CURRENTVECTOR (currentLadder), WHICH REPRESENT THE LAS NODE VISITED FOR THAT ROUTE
        auto iterador = currentVector.end() - 1;
        std::string word = *iterador;
        std::string wordTmp = word;



        std::cout<< "\n\n\n<------------VAMOS A MUTAR LA PALABRA ---------------->\n" ;
        std::cout<< "<--------------------- " << word << "----------------------->\n\n\n";

        std::string result="";

    
    //  THIS LOOP GOES THROUGH EVERY LETTER IN THE WORD TO MUTATION
        for (int p =0 ; p < word.length() ; p++) {  // word letters Loop
        

        //  THIS LOOP GOES THROUGH EVERY LETTER IN ABECEDARIO
            for (int i =0 ; i < abcedario.length(); i++) {  // abecedario Loop
            
                
                wordTmp[p] = abcedario[i] ; // mutamos la word
                
               
                //  CHECK IF THE WORD MUTATED EXIST IN THE DICTIONARY OR THIS WORD NOT WAS ALLREADY WAS VISITED
                    if( dictionary.count(wordTmp)  && word != wordTmp   &&   !wordVisited.count(wordTmp) ) {  


                        //  CREATE A NEW VECTOR WITH THE SAME INFORMATION OF THE CURRENT VECTOR
                            std::vector<std::string> tmpVector = currentVector;  
                        
                        //  ADDING THE VALIDATED WORD TO THE NEW VECTOR
                            tmpVector.push_back(wordTmp);   

                        //  ADDING THE NEW VECTOR TO QUEUE_LADDER
                            queueLadders.push(tmpVector);   

                        //  ADDING THE WORD TO THE GENERAL SET 
                            wordVisited.insert(wordTmp);

                        // std::cout <<  wordTmp << " - YES - "<< "\n";

                        // showVector(tmpVector);

                        //  CHECK IF THE MUTATED WORD MAKE MATCH WITH THE wordTarget
                            if (wordTmp == wordTarget) {

                                std::cout <<"encontramos el objetivo : " << wordTmp <<"\n";
                                
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



    // ADDING A VECTOR TO A QUEUE
        // std::vector<std::string> vector2{"lapiz", "lata"};
        // queueLadders.push(vector2);

     // ADDING A VECTOR TO A QUEUE
        // std::vector<std::string> vector1{"cato", "pato"};
        // queueLadders.push(vector1);

    // ADDING A VECTOR TO A QUEUE
        // std::vector<std::string> vector3{"carro", "tato"};
        // queueLadders.push(vector3);