#include <sql/lisa/file_reader.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <regex>
#include <vector>
#include <string>
#include "sql/join_optimizer/access_path.h"
#include <unordered_map>


void FileReader::ReadPinContextFromFile(){

    std::string fileName = "hashes.csv";
    // Open input file
    std::ifstream file(fileName);

    const std::regex separator{ "," };

    // Check, if it could be opened.
    if (!file) {
        //if not, then show error message
        std::cerr << "File could not be opened: " << fileName << std::endl;
    }
    else {

        std::unordered_map<std::string, std::unordered_map<std::string, int>*> temp;
        // File could be opened. Now we want to read line by line
        std::string line{};

        // Read the complete file
        //bool pinned = false;
        while (getline(file, line)) {
             std::unordered_map<std::string, int>* temp_inner= new std::unordered_map<std::string, int>;
            // Split string into parts
            std::vector part(std::sregex_token_iterator(line.begin(), line.end(), separator, -1), {});
                for(unsigned int i = 2; i < part.size(); i++){
                    temp_inner->insert(std::make_pair<std::string,int>(std::string(part[i]),std::stoi(part[1])));
                }
                if (temp.find(std::string(part[0])) != temp.end())
                {
                    temp.at(std::string(part[0]))->insert(temp_inner->begin(), temp_inner->end());
                }else{
                    temp.insert(std::make_pair<std::string,std::unordered_map<std::string, int>*>(std::string(part[0]), std::move(temp_inner)));
                }
                    
        }
        using std::swap;
        swap(current_thd->subplan_token_map, temp);
    
    file.close();
    return;
    }

} 