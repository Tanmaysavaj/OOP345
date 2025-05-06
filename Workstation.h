#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <string>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace seneca
{
    // External declarations for global deques managing order states
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    // The Workstation class represents a station in the production line that processes customer orders
    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders;  // Queue of customer orders at this workstation
        Workstation* m_pNextStation{ nullptr };  // Pointer to the next workstation in the line

    public:
        // Constructor that initializes a Workstation from a record string
        Workstation(const std::string& src);

        // Default destructor
        ~Workstation() = default;

        // Fill the first order in the queue if it requires an item from this workstation
        void fill(std::ostream& os);

        // Attempt to move the first order in the queue to the next station or to the completed/incomplete queue
        bool attemptToMoveOrder();

        // Set the next station in the production line
        void setNextStation(Workstation* station);

        // Get the next station in the production line
        Workstation* getNextStation() const;

        // Display the current workstation and its next station
        void display(std::ostream& os) const;

        // Add a new order to the workstation's queue
        Workstation& operator+=(CustomerOrder&& newOrder);
    };
}

#endif // SENECA_WORKSTATION_H