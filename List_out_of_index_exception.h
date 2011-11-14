#ifndef LIST_OUT_OF_INDEX_EXCEPTION_H_
#define LIST_OUT_OF_INDEX_EXCEPTION_H_

#include <stdexcept>
#include <string>

class List_out_of_index_exception : public std::runtime_error {
public:
  List_out_of_index_exception (const std::string& message =""):std::runtime_error(message) {};
};

#endif // end LIST_OUT_OF_INDEX_EXCEPTION_H_
