#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <ctime>
#include <cstdlib>

void findFirstSeq(std::string,int,std::string&);
void lowerString(std::string&);
void printMap(std::map<std::string,int>);
void printMap(std::map<std::string,std::vector<char>>);
void createMarkovData(std::string,int,std::map<std::string,std::vector<char>>&);
void generateMarkovText(std::string,std::map<std::string,std::vector<char>>,std::string&);

int main(){
    //customer enters name of file
    std::string FILE_NAME;
    int MARKOV;
    std::vector<char> SYMBOL_VECTOR;    
    std::string TEXT;

    while(1){
        //customer inputs name of file
        std::cout << "Enter file name : ";
        std::cin >> FILE_NAME;
        std::ifstream TEXT_FILE(FILE_NAME+".txt");
        if(TEXT_FILE.is_open()){
            //do something and break
            //enter markov number, range 1-10;
            do {
                std::cout << "Enter Markov number(1-10) : ";
                std::cin >> MARKOV;
            } while(MARKOV < 1 || MARKOV > 10);
                        
            getline(TEXT_FILE,TEXT);//get whole text from file
            //lowerString(TEXT);//lowers upper cases  
            //count probability of symbols corresponding to MARKOV
            std::string FIRST_SEQUENCE;    
            findFirstSeq(TEXT,MARKOV,FIRST_SEQUENCE);//find sequence with largest probability
            std::map<std::string,std::vector<char>> MARKOV_DATA;
            createMarkovData(TEXT,MARKOV,MARKOV_DATA);//creates markov data structure, key is markov sequence, value is symbols after it
            //generate markov text
            std::string MARKOV_TEXT;
            generateMarkovText(FIRST_SEQUENCE,MARKOV_DATA,MARKOV_TEXT);

            break;
        }
    }    

    return 0;
}

//find sequence with largest probability
void findFirstSeq(std::string text,int markov,std::string& first_seq){
    std::map<std::string,int> SEQUENCE_AND_PROBABILITY;//map for saving sequences with corresponding prob.
    std::string SEQUENCE;      
    for(int i = 0; i < text.size(); i ++){
        SEQUENCE = text.substr(i,markov);
        if(SEQUENCE_AND_PROBABILITY.find(SEQUENCE) == SEQUENCE_AND_PROBABILITY.end()){
            for(int j = 0; j < text.size(); j ++){
                if(SEQUENCE == text.substr(j,markov)){
                    SEQUENCE_AND_PROBABILITY[SEQUENCE] += 1;
                }
            }
        }        
    }        
    //find sequence with highest probability
    int max = 0;
    for(const auto& i : SEQUENCE_AND_PROBABILITY){        
        if(i.second > max){
            //std::cout << "ASd";
            max = i.second;
            first_seq = i.first;            
        }        
    }
    
}

void lowerString(std::string& s){
    for(int i = 0; i < s.size(); i ++){
        if(s[i] >= 65 && s[i] <= 90){
            s[i] = tolower(s[i]);
        }        
    }
}

void printMap(std::map<std::string,int> map){
    for(const auto& i : map){
        std::cout << i.first << " - " << i.second << "\n";        
    }
}

void printMap(std::map<std::string,std::vector<char>> map){
    for(const auto& i : map){
        std::cout << i.first << " - ";
        for(int j = 0; j < i.second.size(); j ++){
            std::cout << i.second[j];
        }
        std::cout << "\n";        
    }
}

void createMarkovData(std::string text,int markov,std::map<std::string,std::vector<char>>& markovdata){
    std::string SEQUENCE;
    std::vector<char> markovsymbols;      
    for(int i = 0; i < text.size(); i ++){
        SEQUENCE = text.substr(i,markov);
        if(markovdata.find(SEQUENCE) == markovdata.end()){
            for(int j = 0; j < text.size(); j ++){
                if(SEQUENCE == text.substr(j,markov) && j+markov < text.size()){
                    markovsymbols.push_back(text[j+markov]);    
                }
            }
            markovdata[SEQUENCE] = markovsymbols;
            markovsymbols.clear();
        }        
    }
    //printMap(markovdata);  
}

void generateMarkovText(std::string sequence,std::map<std::string,std::vector<char>> markovdata,std::string& markovtext){
    char nextsymbol;
    std::vector<char> v;
    markovtext.append(sequence);
    for(int i = 0; i < 2000; i ++){        
        //add next symbol from markovdata randomly
        v = markovdata[sequence];
        if(v.size() == 0){
            break;
        }
        nextsymbol = v[rand()%v.size()];
        markovtext.push_back(nextsymbol);
        sequence.erase(sequence.begin());//erase first element
        sequence.push_back(nextsymbol);
    }
    std::cout << markovtext;
}
