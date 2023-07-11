#ifndef RPN_HPP
#define RPN_HPP


#include <stack>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <cstring>
#include <cctype>

class RPN{
    public:
        RPN();
        RPN(int argc, char **args);
        ~RPN();
        RPN(const RPN &);
        RPN&operator=(const RPN &);

        class Error : public std::exception {
            public :
		        virtual const char *what(void) const throw(){return "Error";};
	    };

    private:
        int _argc;
        std::stack<long long> _res;
        bool isValidArg(char * arg);
        bool isValidOper(char * arg);
        long long calculate(long long elem1, long long elem2, std::string token);
        void process(char **args, int original_argc);

};
#endif