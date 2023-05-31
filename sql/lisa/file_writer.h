#ifndef FILE_WRITER_H
#define FILE_WRITER_H 1
#include "sql/sql_class.h"
class FileWriter{
    public:
        static int write_to_log(std::chrono::duration<double> optimize_time, std::chrono::duration<double> execute_time, std::chrono::duration<double> sum_time, THD *thd); 
        static int explain_log_helper(std::string hashes);
};


#endif  // FILE_WRITER_H
