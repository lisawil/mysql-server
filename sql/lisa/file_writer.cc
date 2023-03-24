#include <sql/lisa/file_writer.h>

#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>

int FileWriter::write_to_debug(unsigned char* to_dump){
        std::ofstream fout;
        std::string filename = "pinned_hashes.csv";
        printf("from write \n");
        fout.open(filename, std::ios::app);
        assert (!fout.fail( ));     
            fout<<std::string(reinterpret_cast<char*>(to_dump))<<",1,0x83566674cba1407d,0xffbbbfadeccc2ed8,0x78a62a43a1627d3a,0x9433caaba78cd703,0x9ea21e9e5bafb6ea"<<std::endl;
        fout.close( );
        assert(!fout.fail( ));
        return 0;
    } 