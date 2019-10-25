// Remember to add comments to your code
#pragma once
#include <vector>
#include <queue>

// Event class used for DES simulation
class Event {
public:
    // enum of possible Event types
    enum Type {Process_Arrival, CPU_Burst_Completion, IO_Burst_Completion, Timer_Expiration};

    // The type of an event
    Type type;
    // Time stamp (in unit of ms) when the event happens 
    int time;
    // ID of the process to which this event belongs
    int procID;

    // constructors
    Event();
    Event(int _procID, Type _type, int _time);
};

// Compare Event according to their time stamp
class EventCompare {
public:
    bool operator() (const Event& e1, const Event& e2) {
        return (e1.time > e2.time);
    }

};

// Class alias of Event Queue
using EventQueue = std::priority_queue<Event, std::vector<Event>, EventCompare>;
