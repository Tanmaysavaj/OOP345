#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

namespace seneca
{
    // The Utilities class provides utility functions for handling strings and tokens
    class Utilities
    {
        size_t m_widthField{ 1 };  // Field width for the current object
        static char m_delimiter;   // Static member to store the delimiter for token extraction

    public:
        // Sets the field width of the current object to the value of parameter newWidth
        void setFieldWidth(size_t newWidth);

        // Returns the field width of the current object
        size_t getFieldWidth() const;

        // Extracts a token from string str starting at next_pos, updating next_pos and more
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

        // Sets the delimiter for this class to the character received
        static void setDelimiter(char newDelimiter);

        // Returns the delimiter for this class
        static char getDelimiter();
    };
}

#endif // SENECA_UTILITIES_H