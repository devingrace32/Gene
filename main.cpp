#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
void openFiles(std::ifstream &infile, std::ofstream &outfile, std::ifstream &genesPerCluster);
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);

int main() {
    std::ifstream infile;
    std::ifstream genePerCluster;
    std::ofstream outfile;
    openFiles(infile, outfile, genePerCluster);
    int cluster;
    int numGenes;
    //map of gene cluster and num genes per cluster
    typedef std::map<int,int> clusterMap;
    clusterMap gpc;
    while(genePerCluster.peek() != EOF ){
        genePerCluster>>cluster;
        genePerCluster >> numGenes;
        gpc[cluster]= numGenes;
    }
    //read in GAO ortholog cluster file line by line
    //for each line, each cluster is separated by space
    //make an array for each line.
    //then loop through every element of the array
    //count how many times that element shows up in the array
    //find according cluster num element in map.
    //divide the times that element shows up by the num element
    std::string line;
    std::vector<std::string> orthos (10);

    while(std::getline(infile,line)){
        std::getline(infile,line);  //have line for 1 afumi cluster in line
        split(line, orthos, ' '); //line is split at spaces and put into vector orthos
        size_t i = 0;
        for(std::vector<std::string>::iterator it = orthos.begin(); it != orthos.end(); it++){
            int cnt = std::count(orthos.begin(), orthos.end(), *it);
            int clusterr = stoi(orthos[i]);
            std::cout<< cnt / gpc[clusterr];
            i++;
        }
        std::cout<<std::endl;
    }
}
// open input and output files
// pre: user is prepared to enter file names at the keyboard
// post: files have been opened
void openFiles(std::ifstream &infile, std::ofstream &outfile,std::ifstream &genePerCluster ) {

    // open input data file
    std::string inFileName;
    std::cout << "Enter the name of the input file: ";
    std::cin >> inFileName;
    infile.open(inFileName);
    if (infile.fail()) {
        std::cout << "Error opening input data file" << std::endl;
        std::cout << "press enter to exit";
        std::cin.get();
        std::cin.get();
        exit(1);
    }


    std::string inFileName1;
    std::cout << "Enter the name of the input file: ";
    std::cin >> inFileName1;
    genePerCluster.open(inFileName1);
    if (genePerCluster.fail()) {
        std::cout << "Error opening input data file" << std::endl;
        std::cout << "press enter to exit";
        std::cin.get();
        std::cin.get();
        exit(1);
    }
    // open output data file
    std::string outFileName;
    std::cout << "Enter the name of the output file: ";
    std::cin >> outFileName;
    outfile.open(outFileName);
    if (outfile.fail()) {
        std::cout << "Error opening output data file" << std::endl;
        std::cout << "press enter to exit";
        std::cin.get();
        std::cin.get();
        exit(1);
    }

}

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}