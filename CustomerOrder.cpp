#include <iostream>
#include <iomanip>
#include <vector>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"

namespace seneca
{
    // Static member to keep track of the maximum field width for display purposes
    size_t CustomerOrder::m_widthField{};

    // Constructor that initializes a CustomerOrder object from a record string
    CustomerOrder::CustomerOrder(const std::string& record)
    {
        Utilities util;
        bool more = true;
        size_t pos = 0u;
        std::vector<std::string> tokens;

        // Extract tokens from the record string using Utilities
        while (more)
        {
            tokens.push_back(util.extractToken(record, pos, more));
        }

        // Update the maximum field width if necessary
        if (m_widthField < util.getFieldWidth())
        {
            m_widthField = util.getFieldWidth();
        }

        // Assign the first two tokens to name and product
        m_name = tokens[0];
        m_product = tokens[1];

        // If there are more tokens, they represent items
        if (tokens.size() > 2)
        {
            m_cntItem = tokens.size() - 2;
            m_lstItem = new Item * [m_cntItem];

            // Create Item objects for each item token
            for (size_t i = 0; i < m_cntItem; i++)
            {
                m_lstItem[i] = new Item(tokens[i + 2]);
            }
        }
        else
        {
            m_cntItem = 0;
            m_lstItem = nullptr;
        }
    }

    // Copy constructor is deleted by throwing an error
    CustomerOrder::CustomerOrder(const CustomerOrder& src)
    {
        throw "Error";
    }

    // Move constructor
    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
    {
        *this = std::move(src);
    }

    // Move assignment operator
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
    {
        if (this != &src)
        {
            // Clean up existing resources
            for (size_t i = 0; i < m_cntItem; i++)
            {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            // Transfer ownership of resources
            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            // Reset source object
            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0u;
            src.m_lstItem = nullptr;
        }

        return *this;
    }

    // Destructor to clean up dynamically allocated memory
    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    // Check if all items in the order are filled
    bool CustomerOrder::isOrderFilled() const
    {
        bool result = true;

        for (size_t i = 0; i < m_cntItem && result; i++)
        {
            if (m_lstItem[i]->m_isFilled == false) 
            {
                result = false;
            }
        }

        return result;
    }

    // Check if a specific item is filled
    bool CustomerOrder::isItemFilled(const std::string& itemName) const
    {
        bool result = true;

        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == itemName) 
            {
                if (!m_lstItem[i]->m_isFilled)
                {
                    result = false;
                }
            }
        }

        return result;
    }

    // Attempt to fill an item from a station
    void CustomerOrder::fillItem(Station& station, std::ostream& os)
    {
        bool done = false;

        for (size_t i = 0; i < m_cntItem && !done; i++)
        {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled)
            {
                if (station.getQuantity())
                {
                    // Fill the item if the station has enough quantity
                    m_lstItem[i]->m_isFilled = true;
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
                    done = true;
                }
                else
                {
                    // Log if unable to fill due to insufficient quantity
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
                }
            }
        }
    }

    // Display the order details
    void CustomerOrder::display(std::ostream& os) const
    {
        os << m_name << " - " << m_product << std::endl;
        
        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << std::right << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << "] " 
               << std::left << std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName 
               << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}