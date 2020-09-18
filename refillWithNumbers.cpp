#include <iostream>
#include <fstream>

#include <cmath>
#include <ctime>

/*

    ESTE PROGRAMA CREA UN ARCHIVO txt CON UNA CANTIDAD ESPECIFICA DE NUMEROS ALEATORIOS


*/
void fill_File ();
int randomInteger(int low,  int high);


int main () {
    
    srand(int (time(NULL)));

    fill_File();

    return 0;
}




void fill_File () {
     std::ofstream writeFile;
    //create a file named Example.txt
    //int the current directory

    //open file
    //this creates the file if it doesn't 
    //already exist
    writeFile.open("Numbers50000.txt");
    
   

  
    // writeFile <<"linea1\n";
    //  writeFile <<"linea2";

     for (int i =0; i<50000 ; i++) {
         //std::cout << randomInteger(0,  10000 ) <<"\n" ;
         writeFile << randomInteger(0,  50000 ) << "\n";
     }
       // close the file stream
    writeFile.close(); 
    
}


int randomInteger(int low,  int high) {

   // initRandomSeed();

    double d = rand() / (double (RAND_MAX) + 1 );
    double s = d * (double(high) -  low +1);

    return int( floor(low + s) );

}
