#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>

namespace seneca
{
    // The Station class represents a station in a production line, managing items and their quantities
    class Station
    {
        int m_id{};  // Unique identifier for the station
        std::string m_name{};  // Name of the item at the station
        std::string m_desc{};  // Description of the item
        unsigned int m_serial{};  // Serial number for items produced at this station
        size_t m_stock{};  // Current stock quantity of the item

        static size_t m_widthField;  // Static member to track the maximum field width for display
        static size_t id_generator;  // Static member to generate unique IDs for stations

    public:
        // Default constructor
        Station();

        // Constructor that initializes a Station from a record string
        Station(const std::string& record);

        // Virtual destructor
        virtual ~Station();

        // Returns the name of the current Station object
        const std::string& getItemName() const;

        // Returns the next serial number to be used on the assembly line and increments m_serial
        size_t getNextSerialNumber();

        // Returns the remaining quantity of items in the Station object
        size_t getQuantity() const;

        // Subtracts 1 from the available quantity; should not drop below 0
        void updateQuantity();

        // Inserts information about the current object into stream os
        void display(std::ostream& os, bool full) const;
    };
}

#endif // SENECA_STATION_H