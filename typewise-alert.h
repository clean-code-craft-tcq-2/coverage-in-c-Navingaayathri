#pragma once

#define PASSIVE_COOLING_LOWER_LIM 0
#define PASSIVE_COOLING_UPPER_LIM 35
#define HI_ACTIVE_COOLING_LOWER_LIM 0
#define HI_ACTIVE_COOLING_UPPER_LIM 45
#define MED_ACTIVE_COOLING_LOWER_LIM 0
#define MED_ACTIVE_COOLING_UPPER_LIM 40

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

typedef struct 
{
  int lowerLimit;
  int upperLimit;
}TemperatureLimit;

BreachType inferBreach(CoolingType coolingType, double temperatureInC);
extern int checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC); 
extern int selectTarget(AlertTarget alertTarget,BreachType breachType);
extern int sendToController(BreachType breachType);
extern int sendToEmail(BreachType breachType);
