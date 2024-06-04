#include <Arduino.h>


// Define states
typedef enum
{
    SAFE_LOCKED,
    LEVEL1_UNLOCKED,
    LEVEL2_UNLOCKED,
    LEVEL3_UNLOCKED,
    SAFE_OPEN,
}State_t;

// Define transition events
typedef enum
{
    INPUT1_ACCEPTED,
    INPUT2_ACCEPTED,
    INPUT3_ACCEPTED,
    INPUT_REFSUED,
    OPED_DOOR,
    CLOSE_DOOR,
}Event_t;

// Create global variables
State_t state = SAFE_LOCKED;


// Declare prototypes
void state_machine(Event_t event);


void setup() 
{

}

void loop() 
{

}


/*
void state_machine(Event_t event)
{
  switch(state)
  {
    case SAFE_LOCKED:
      if()
      {

      }
      break;
    case LEVEL1_UNLOCKED:
      if()
      {

      }
      break;
    case LEVEL2_UNLOCKED:
      if()
      {

      }
      break;
    case LEVEL3_UNLOCKED:
      if()
      {

      }
      break;
    case SAFE_OPEN:
      if()
      {

      }
      break;
  }
}
*/