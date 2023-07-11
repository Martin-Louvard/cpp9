#include "RPN.hpp"

RPN::RPN(void){
    std::cerr << "RPN must be initialized with argc and argv !" << std::endl;
}

RPN::RPN(int argc, char **args){
    if(argc > 2)
        _argc = argc - 1;
    else
    {
        std::string str(args[1]);
        _argc = 0;
        for (size_t i = 0; i < str.length(); i++)
            if (!std::isspace(str[i]))
                _argc++;
    }
    process(args + 1, argc);
}

RPN::~RPN(void){}

RPN::RPN(const RPN & R){
    *this = R;
}

RPN& RPN::operator=(const RPN & R){
    _argc = R._argc;
    _res = R._res;
    return *this;
}

bool RPN::isValidOper(char *arg){
    char c_arg;
    if (strlen(arg) != 1)
        return false;
    c_arg = arg[0];
    switch (c_arg)
    {
        case '+':
            return true;
        case '-':
            return true;
        case '*':
            return true;
        case '/':
            return true;
        default:
            return false;
    }
}

bool RPN::isValidArg(char *arg){
    char c_arg;
    if (strlen(arg) != 1)
        return false;
    c_arg = arg[0];
    switch (c_arg)
    {
        case '0':
            return true;
        case '1':
            return true;
        case '2':
            return true;
        case '3':
            return true;
        case '4':
            return true;
        case '5':
            return true;
        case '6':
            return true;
        case '7':
            return true;
        case '8':
            return true;
        case '9':
            return true;
        default:
            return false;
    }
}

void RPN::process(char **args, int original_argc){
    long long calc, elem1, elem2;
    char * arg;
    for (int i = 0; i < _argc; i++)
    {
        if (original_argc == 2 && i == 0)
            arg = std::strtok(args[0], " ");
        else if (original_argc == 2 && i > 0)
            arg = std::strtok(NULL, " ");
        else
            arg = args[i];
        if (isValidArg(arg))
            _res.push(atol(arg));
        else if (isValidOper(arg) && _res.size() >= 2)
        {
            elem1 = _res.top();
            _res.pop();
            elem2 = _res.top();
            _res.pop();
            calc = calculate(elem2, elem1, arg);
            _res.push(calc);
        }
        else
            throw Error();
    }

    //output result
    if (_res.size() != 1)
        throw Error();
    std::cout << _res.top() << std::endl;
}

long long RPN::calculate(long long elem1, long long elem2, std::string token)
{
    switch (token[0])
    {
        case '+':
            return (elem1 + elem2);
        case '-':
            return (elem1 - elem2);
        case '*':
            return (elem1 * elem2);
        case '/':
        {
            if (elem2 == 0)
            {
                std::cerr << "Cannot divide by 0" << std::endl;
                throw Error();
            }
            return (elem1 / elem2);
        }
        default:
            throw Error();
    }
}