#ifndef GET_ERROR_DESCRIPTION_HPP
#define GET_ERROR_DESCRIPTION_HPP

#ifndef ERROR_STRING_SIZE
#define ERROR_STRING_SIZE 30
#endif // !ERROR_STRING_SIZE

#include <string>

bool getErrorDescription(unsigned char errorCode);

#endif // !GET_ERROR_DESCRIPTION_HPP