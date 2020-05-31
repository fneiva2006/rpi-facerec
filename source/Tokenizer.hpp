/*
    File Name: Tokenizer.hpp
    Author(s): Unknown
    Edited in July 2016

    This file is a string tokenizer tool used on the Face Detection & Recognition System.
    The System was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//Header file
class Tokenizer
{
    public:
        static const std::string DELIMITERS;
        Tokenizer(const std::string& str);
        Tokenizer(const std::string& str, const std::string& delimiters);
        bool NextToken();
        bool NextToken(const std::string& delimiters);
        const std::string GetToken() const;
        void Reset();
    protected:
        size_t m_offset;
        const std::string m_string;
        std::string m_token;
        std::string m_delimiters;
};

