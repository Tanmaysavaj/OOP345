#include <iostream>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace seneca
{
    // Global deques to manage the state of customer orders
    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    // Constructor for LineManager that initializes the production line from a file
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
        std::ifstream input(file);
        std::string line;
        std::string current, next;
        Utilities util;
        bool more = true;
        size_t pos = 0;

        if (input)
        {
            // Read each line from the file to set up the workstation sequence
            while (std::getline(input, line))
            {
                current = util.extractToken(line, pos, more);
                next = more ? util.extractToken(line, pos, more) : "";

                // Find the current station in the list of stations
                auto station = std::find_if(stations.begin(), stations.end(), [current](const Workstation* s)
                    {
                        return s->getItemName() == current;
                    });

                // If a next station is specified, set it as the next station for the current one
                if (station != stations.end() && !next.empty())
                {
                    auto nextStation = std::find_if(stations.begin(), stations.end(), [next](const Workstation* s)
                        {
                            return s->getItemName() == next;
                        });
                    if (nextStation != stations.end())
                    {
                        (*station)->setNextStation(*nextStation);
                    }
                }

                // Add the current station to the active line
                m_activeLine.push_back(*station);
            }

            // Determine the first station in the line
            auto firstStation = std::find_if(stations.begin(), stations.end(), [&](const Workstation* s1)
                {
                    return std::none_of(stations.begin(), stations.end(), [&](const Workstation* s2)
                        {
                            return s1 == s2->getNextStation();
                        });
                });

            m_firstStation = *firstStation;
            m_cntCustomerOrder = g_pending.size();
        }
    }

    // Reorder the stations to reflect the correct sequence
    void LineManager::reorderStations()
    {
        std::vector<Workstation*> newLine;
        newLine.push_back(m_firstStation);
        int i = 0;

        // Follow the chain of next stations to reorder
        while (newLine[i]->getNextStation() != nullptr)
        {
            newLine.push_back(newLine[i]->getNextStation());
            i++;
        }
        m_activeLine = newLine;
    }

    // Run one iteration of the production line
    bool LineManager::run(std::ostream& os)
    {
        static int CNT{ 1 };

        os << "Line Manager Iteration: " << CNT++ << std::endl;

        // Move the first pending order to the first station
        if (!g_pending.empty())
        {
            *m_firstStation += std::move(g_pending.front());
            g_pending.erase(g_pending.begin());
        }

        // Fill orders at each workstation
        for (auto& work : m_activeLine)
        {
            work->fill(os);
        }

        // Attempt to move orders to the next station
        for (auto& work : m_activeLine)
        {
            work->attemptToMoveOrder();
        }

        // Check if all orders are processed
        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }

    // Display the current state of the production line
    void LineManager::display(std::ostream& os) const
    {
        for (size_t i = 0; i < m_activeLine.size(); i++)
        {
            m_activeLine[i]->display(os);
        }
    }
}