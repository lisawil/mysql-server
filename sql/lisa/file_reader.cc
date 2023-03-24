#include <sql/lisa/file_reader.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <regex>
#include <vector>
#include <string>
#include "sql/join_optimizer/access_path.h"


void FileReader::ReadPinContextFromFile(unsigned char* digest, 
                                        std::string sub_plan_token,  
                                        AccessPath *path){

    std::string fileName = "pinned_hashes.csv";
    // Open input file
    std::ifstream file(fileName);

    const std::regex separator{ "," };

    // Check, if it could be opened.
    if (!file) {
        //if not, then show error message
        std::cerr << "File could not be opened: " << fileName << std::endl;
    }
    else {
        // File could be opened. Now we want to read line by line
        std::string line{};

        // Read the complete file
        bool pinned = false;
        while (getline(file, line)) {

            // Split string into parts
            std::vector part(std::sregex_token_iterator(line.begin(), line.end(), separator, -1), {});
            if(part[0] == std::string(reinterpret_cast<char*>(digest)))
                {
                    pinned = true;
                    for(unsigned int i = 2; i < part.size(); i++){
                    if (sub_plan_token == part[i])
                        {
                            path->pinned.pinned = true;
                            path->pinned.pin_number = std::stoi(part[1]);
                            path->pinned.final_plan = (i+1 == part.size());

                            printf("subplan is hypergraph pinned! \n");
                            file.close();
                            assert(!file.fail());
                            return;
                        }
                    }
                }
        }
        if(!pinned){
            current_thd->hash_pinned = false;
        }
    }
    file.close();
    return;

} 