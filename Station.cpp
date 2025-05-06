#include <iostream>
#include <vector>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace seneca
{
    // Static members to keep track of the maximum field width and generate unique IDs
    size_t Station::m_widthField{ 0 };
    size_t Station::id_generator{ 0 };

    // Default constructor for Station
    Station::Station()
    {
    }

    // Constructor that initializes a Station object from a record string
    Station::Station(const std::string& record)
    {
        id_generator++;  // Increment the ID generator for each new station
        Utilities util;
        bool more = true;
        size_t pos = 0u;
        std::vector<std::string> tokens;

        // Extract tokens from the record string using Utilities
        while (more)
        {
            if (tokens.size() == 3 && m_widthField < util.getFieldWidth())
            {
                m_widthField = util.getFieldWidth();  // Update the maximum field width if necessary
            }
            tokens.push_back(util.extractToken(record, pos, more));
        }

        // Initialize station attributes from tokens
        m_id = id_generator;
        m_name = tokens[0];
        m_serial = std::stoi(tokens[1]);
        m_stock = std::stoi(tokens[2]);
        m_desc = tokens[3];
    }

    // Destructor for Station
    Station::~Station()
    {
    }

    // Get the name of the item at the station
    const std::string& Station::getItemName() const
    {
        return m_name;
    }

    // Get the next serial number and increment it
    size_t Station::getNextSerialNumber()
    {
        return m_serial++;
    }

    // Get the current stock quantity
    size_t Station::getQuantity() const
    {
        return m_stock;
    }

    // Decrease the stock quantity by one, if possible
    void Station::updateQuantity()
    {
        if (m_stock > 0)
        {
            m_stock--;
        }
    }

    // Display the station's information
    void Station::display(std::ostream& os, bool full) const
    {
        os << std::right << std::setfill('0') << std::setw(3) << m_id << " | "
           << std::left << std::setfill(' ') << std::setw(m_widthField) << m_name << " | "
           << std::right << std::setfill('0') << std::setw(6) << m_serial << " | ";

        if (full)
        {
            os << std::right << std::setfill(' ') << std::setw(4) << m_stock << " | " << m_desc;
        }
        os << std::endl;
    }
}