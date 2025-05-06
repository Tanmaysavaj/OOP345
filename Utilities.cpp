#include <iostream>
#include <sstream>
#include <algorithm>
#include "Utilities.h"

namespace seneca
{
    // Static member to store the delimiter used for token extraction
    char Utilities::m_delimiter{};

    // Set the field width for the current object
    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    // Get the field width for the current object
    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    // Extract a token from a string starting at next_pos, updating next_pos and more
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        // Find the position of the next delimiter
        size_t find = str.find(m_delimiter, next_pos);

        // Check if the delimiter is at the current position, indicating no token
        if (find == next_pos)
        {
            more = false;
            throw "No token until delimiter";
        }

        // Extract the token from the string
        std::string token = str.substr(next_pos, find - next_pos);
        next_pos = find + 1;

        // Determine if there are more tokens to extract
        if (find == std::string::npos)
        {
            more = false;
        }
        else 
        {
            if (!token.empty()) more = true;
        }

        // Trim leading and trailing spaces from the token
        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);

        // Update the field width if the token is longer than the current width
        m_widthField = (m_widthField < token.size()) ? token.size() : m_widthField;

        return token;
    }

    // Set the delimiter for token extraction
    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    // Get the current delimiter for token extraction
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
}