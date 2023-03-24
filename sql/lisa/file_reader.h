#include <string>

struct AccessPath;

class FileReader{
    public:
        static void ReadPinContextFromFile(unsigned char* digest, 
                                           std::string sub_plan_token, 
                                           AccessPath *path); 
        

};