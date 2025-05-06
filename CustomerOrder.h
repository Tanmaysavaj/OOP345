#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "Station.h"

namespace seneca
{
    // The CustomerOrder class manages customer orders, including items and their fulfillment status
    class CustomerOrder {
    private:
        // Nested Item structure to represent each item in the order
        struct Item {
            std::string m_itemName;  // Name of the item
            size_t m_serialNumber{ 0 };  // Serial number of the item
            bool m_isFilled{ false };  // Fulfillment status of the item

            // Constructor to initialize an Item with a name
            Item(const std::string& src) : m_itemName(src) {}
        };

        std::string m_name;  // Customer's name
        std::string m_product;  // Product name
        size_t m_cntItem{ 0 };  // Number of items in the order
        Item** m_lstItem{ nullptr };  // Array of pointers to Item objects
        static size_t m_widthField;  // Static member to track the maximum field width for display

    public:
        // Default constructor
        CustomerOrder() {};

        // Constructor that initializes a CustomerOrder from a record string
        CustomerOrder(const std::string& record);

        // Copy constructor (deleted by throwing an error in the implementation)
        CustomerOrder(const CustomerOrder& src);

        // Copy assignment operator is deleted to prevent copying
        CustomerOrder& operator=(const CustomerOrder& src) = delete;

        // Move constructor
        CustomerOrder(CustomerOrder&& src) noexcept;

        // Move assignment operator
        CustomerOrder& operator=(CustomerOrder&& src) noexcept;

        // Destructor to clean up dynamically allocated memory
        ~CustomerOrder();

        // Check if the entire order is filled
        bool isOrderFilled() const;

        // Check if a specific item is filled
        bool isItemFilled(const std::string& itemName) const;

        // Attempt to fill an item from a station
        void fillItem(Station& station, std::ostream& os);

        // Display the order details
        void display(std::ostream& os) const;
    };
}

#endif // SENECA_CUSTOMERORDER_H