#include "event.h"

Event::Event()
{
  procID = 0;
  type = Process_Arrival;
  time = 0;
}

Event::Event(int _procID, Type _type, int _time)
{
  procID = _procID;
  type = _type;
  time = _time;
}
