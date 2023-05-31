#include <sql/lisa/file_writer.h>

#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <chrono>
#include "sql/sql_class.h"

int FileWriter::write_to_log(std::chrono::duration<double> optimize_time, std::chrono::duration<double> execute_time, std::chrono::duration<double> sum_time, THD *thd){
        std::ofstream fout;
        std::string filename = "experiment_log.csv";
        printf("from write \n");
        fout.open(filename, std::ios::app);
        assert (!fout.fail( ));     
            fout<< optimize_time.count() <<","<< 
            execute_time.count() <<","<< 
            sum_time.count() <<"," <<
            thd->statement_digest_text<<std::endl;
        fout.close( );
        assert(!fout.fail( ));
        return 0;
    } 

int FileWriter::explain_log_helper(std::string hashes){
        std::ofstream fout;
        std::string filename = "explain_log.csv";
        fout.open(filename, std::ios::app);
        assert (!fout.fail( ));     
            fout<< hashes<<std::endl;
        fout.close( );
        assert(!fout.fail( ));
        return 0;
    }