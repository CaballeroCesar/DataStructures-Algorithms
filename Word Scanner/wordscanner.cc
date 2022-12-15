/* 	Cesar Caballero
	z1944013	
	CS340 - 2
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <utility>

void get_words(std::map<std::string, int>& m);
void print_words(const std::map<std::string, int>& m);
void clean_entry(const std::string& og_word, std::string& clean_word);

int main()
{
    std::string input; 
    std::map<std::string, int> m;

    get_words(m); //calling get_words function to parse input and clean words
    print_words(m); //print output with function

    return 0;
}

/**
 * @brief collect all of words from input separated by parsing to be cleaned
 * 
 * @param m = map where cleaned words get stored
 */
void get_words(std::map<std::string, int>& m)
{
    std::string input; 
    while(std::getline(std::cin, input)) //collect all words from input and store them into input variable
    {
        std::string delimiter = " ";
        size_t beginning = 0;
        size_t pos = 0;
        std::string word; //original parsed words
        std::string clean_word; //after cleaning words they are stored into clean_word

        //separating words using space as the delimiter to put all words into map
        while((beginning = input.find_first_not_of(delimiter,pos)) != std::string::npos)
        {
            pos = input.find_first_of(delimiter,beginning+1);
            word = input.substr(beginning, pos-beginning);

            clean_entry(word,clean_word); //call clean_entry() function to clean the words stored in "word" and then store them into clean_word after cleaninig
            m[clean_word]++; // add all words that have been cleaned into map
        }
    }
}

/**
 * @brief function cleans a word that has non alphanumeric characters and removes them as well as making all of word lowercase
 * 
 * @param og_word = original word before being cleaned
 * @param clean_word = word that consists of only alphanumeric and lower case characters
 */
void clean_entry(const std::string& og_word, std::string& clean_word)
{
    auto index = std::find_if(og_word.begin(),og_word.end(),[](const char &c){return isalnum(c);}); // check if a character is alphanumeric, storing index of first alphanumeric character
    auto indexAfter = std::find_if(index,og_word.end(),[](const char &c){return !isalnum(c);}); // check if a character is NOT alphanumeric, storing index of index after non alphanumeric character

    std::string word(index,indexAfter); //word is cleaned based off indexes, store into a new string 
    clean_word = word; //set clean_word passed through function equal to word that was cleaned
   
    std::for_each(clean_word.begin(), clean_word.end(), [](char &c){c = tolower(c);}); //after word has been cleaned, convert upper case letters to lower case
}

/**
 * @brief Print output with proper formatting
 * 
 * @param m is the map where clean words are stored
 */
void print_words(const std::map<std::string, int>& m)
{
    //given variables to format output
    int NO_ITEMS = 4;
    int ITEM_WORD_WIDTH = 14;
    int ITEM_COUNT_WIDTH = 3;

    int counter = 0; //counter to know when 4 items have been printed to start a new line
    int wc = 0; // number of words

    for(auto it = m.begin(); it != m.end(); it++) //iterate through map
    {
        //start a new line once 4 words have been printed per line
        if(counter == NO_ITEMS)
        {
            counter = 0; //reset counter after new line has started
            std::cout << std::endl;
        }

        std::cout << std::setw(ITEM_WORD_WIDTH) << std::left << (*it).first << ":" << std::setw(ITEM_COUNT_WIDTH) << (*it).second << ""; // print words and numbers with proper format
        wc += (*it).second; //add to word count
        counter++; // increment counter 
    }

    //print word coiunt in input and output stream with correct formatting
    std::cout << std::endl; 
    std::cout << "number of words in input stream   :" << wc << std::endl; 
    std::cout << "number of words in output stream  :" << m.size() << std::endl << std::endl; 
}