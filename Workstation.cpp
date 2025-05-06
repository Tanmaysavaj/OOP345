#include <iostream>
#include "Workstation.h"

namespace seneca
{
    // Constructor for Workstation that initializes it using a record string
    Workstation::Workstation(const std::string& src) : Station(src)
    { }

    // Fill the first order in the queue if it requires an item from this workstation
    void Workstation::fill(std::ostream& os)
    {
        if (!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
        }
    }

    // Attempt to move the first order in the queue to the next station or to the completed/incomplete queue
    bool Workstation::attemptToMoveOrder()
    {
        bool result = false;

        // Check if the order is filled for this item or if the station is out of stock
        if (!m_orders.empty() && (m_orders.front().isItemFilled(getItemName()) || !getQuantity()))
        {
            if (m_pNextStation)
            {
                // Move the order to the next station
                *m_pNextStation += std::move(m_orders.front());
            }
            else
            {
                // Move the order to the completed or incomplete queue
                if (m_orders.front().isOrderFilled())
                {
                    g_completed.push_back(std::move(m_orders.front()));
                }
                else
                {
                    g_incomplete.push_back(std::move(m_orders.front()));
                }
            }
            m_orders.pop_front();  // Remove the order from the current queue
            result = true;
        }

        return result;
    }

    // Set the next station in the production line
    void Workstation::setNextStation(Workstation* station)
    {
        m_pNextStation = station;
    }

    // Get the next station in the production line
    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    // Display the current workstation and its next station
    void Workstation::display(std::ostream& os) const
    {
        os << getItemName() << " --> " 
           << (m_pNextStation != nullptr ? m_pNextStation->getItemName() : "End of Line") << '\n';
    }

    // Add a new order to the workstation's queue
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}