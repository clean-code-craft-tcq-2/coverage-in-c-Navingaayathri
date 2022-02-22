#pragma once

#define PASSIVE_COOLING_LOWER_LIM 0
#define PASSIVE_COOLING_UPPER_LIM 35
#define HI_ACTIVE_COOLING_LOWER_LIM 0
#define HI_ACTIVE_COOLING_UPPER_LIM 45
#define MED_ACTIVE_COOLING_LOWER_LIM 0
#define MED_ACTIVE_COOLING_UPPER_LIM 35


typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
  COOLING_TYPE
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

struct TemperatureLimit
{
  int lowerLimit;
  int upperLimit;
};

struct TemperatureLimit limit[COOLING_TYPE];

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

/* structure for cooling type limits  */
struct TemperatureLimit limit[COOLING_TYPE]={
{PASSIVE_COOLING_LOWER_LIM,PASSIVE_COOLING_UPPER_LIM}, 
{HI_ACTIVE_COOLING_LOWER_LIM,HI_ACTIVE_COOLING_UPPER_LIM},
{MED_ACTIVE_COOLING_LOWER_LIM,MED_ACTIVE_COOLING_UPPER_LIM}
};
