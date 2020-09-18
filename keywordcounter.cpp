#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <cctype>

/*

    ESTE PROGRAMA EL NUMERO DE OCURRENCIAS DE UNA keyword o PALABRA RECERVADA DE C++
    EN UN ARCHIVO DE CODIGO FUENTE. USANDO COMO REFERNCIA EL ARCHIVO keywords.txt

*/

std::string GetLine();

/*
    Function : OpenUserFile(ifstream& ,fileStream);
    Usage : OpenUserFile(myStream);
    --------------------------------------------------------------
    Prompts the user for a filename until a valid filename.
    is entered, then set fileStream to read from that file.

*/
void OpenUserFile(std::ifstream& filestream);




/*

    Function : GetFileContent (ifstream& file);
    Usage:  string content = GetFileContents(ifstream& file)
    --------------------------------------------------------------
    Returns a string containing the contents of the file passed in as a parameter.

*/
std::string GetFileContents(std::ifstream& file);



/*

    Function : GenerateKeywordReport(string text)
    Usage: map<string, size_t> keywords = GenerateKeywordReport(contents);
    -----------------------------------------------------------------------
    Returns a map from keyword to the frequency at which those keywords
    appear in the input text string.  Keywords not contained in the text
    will not appear in the map
    
*/
std::map<std::string, size_t> GenerateKeywordReport(std::string contents);



/*
    PreprocessString: Accepts as input a string by reference, then
    replaces all punctuation characters in that string with space character.
    For this we will use ispunct function, wich take a character, then returns whether is
    or not a punctuation character. Unfortunately, ispunct treats underscores as puntuation, 
    wich cause problems for some reserved words (for example, static_cast) , so we'll need to special case it.

*/
void PreprocessString(std::string& text);




int main () {

    std::cout << "-> keyword counter apps\n";

    /* Prompt the user for a valid file and open it as a stream */
    std::ifstream input;
    OpenUserFile(input);



    /* Generate the report base on the contents of the file */
    std::map <std::string, size_t> report = GenerateKeywordReport(GetFileContents(input));



    /* Print a sumary */
    for (std::map<std::string, size_t>::iterator itr = report.begin() ;
        itr != report.end();
        itr++) 
    {
        std::cout << " Keyword " << std::setw (12) << itr->first << " occured " << itr->second << " times " << std::endl;

    }


} // End Main




void OpenUserFile(std::ifstream& input) {

    while (true) {

        std::cout<< "Enter filename: ";
        std::string filename = GetLine();
        
        input.open(filename.c_str());
        if(input.is_open()) return;

        std::cout << "Sorry, I can't find the file " << filename << std::endl;
        input.clear();

    }

}


std::string GetFileContents (std::ifstream& input) {
    /* String wich will hold the file contents */
    std::string result;

    /* Kepp reading a line of the file until no data remains */
    std::string line;
    while (getline(input, line)) {
        result += line + "\n";  // Add the newline character; getline removes it
    }


    return result;
}// End GetFileContents


std::set<std::string> LoadKeywords() {
    
    std::ifstream input ("keywords.txt");
    std::set<std::string> result;

    /*
        Keep reading strings out of the file until we cannot read any more. 
        After reading each string,  store it in the result set.
        We can either use getline or the stream extraction operator here,  
        but the stream extraction operator is a bit more general.

    */

    std::string keyword;
    while (input >> keyword) {
        result.insert(keyword);
    }
    return result;
}



void PreprocessString(std::string& text) {
    for (size_t k=0 ; k<text.size();  ++k) {
        if (std::ispunct(text[k])  &&  text[k] !='_' ) {
            text[k] = ' '; // replace it with a space
        }
    }
}


std::map<std::string, size_t> GenerateKeywordReport (std::string fileContents) {
    
    /* Load the set of keywords from disk */
    std::set<std::string> keywords = LoadKeywords();

    PreprocessString(fileContents);

    /* Populate a stringstream with the file contents */
    std::stringstream tokenizer;
    tokenizer << fileContents;

    /* Loop over the words in the file, building up the report */
    std::map<std::string, size_t> result;

    std::string word;
    while (tokenizer>> word){
        if (keywords.count(word)) {
            ++result[word];
        }
    }
    return result;
}

std::string GetLine(){

    std::string result ;
    getline (std::cin, result);
    return result;
}