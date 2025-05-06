#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include <string>
#include "Workstation.h"

namespace seneca
{
    // The LineManager class manages the sequence of workstations in a production line
    class LineManager
    {
        std::vector<Workstation*> m_activeLine;  // Vector of pointers to workstations in the active line
        size_t m_cntCustomerOrder;  // Total number of customer orders to process
        Workstation* m_firstStation;  // Pointer to the first workstation in the line

    public:
        // Constructor that initializes the LineManager with a configuration file and a list of stations
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);

        // Reorder the stations to reflect the correct sequence
        void reorderStations();

        // Run one iteration of the production line
        bool run(std::ostream& os);

        // Display the current state of the production line
        void display(std::ostream& os) const;
    };
}

#endif // SENECA_LINEMANAGER_H