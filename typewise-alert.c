#include "typewise-alert.h"
#include <stdio.h>

const char *BreachMessage[] = {"Hi, the battery temperature is NORMAL!\n", "Hi, the temperature is TOO LOW\n", "Hi, the temperature is TOO HIGH\n"};

TemperatureLimit limitCategory[COOLING_TYPE]={
{PASSIVE_COOLING_LOWER_LIM,PASSIVE_COOLING_UPPER_LIM}, 
{HI_ACTIVE_COOLING_LOWER_LIM,HI_ACTIVE_COOLING_UPPER_LIM},
{MED_ACTIVE_COOLING_LOWER_LIM,MED_ACTIVE_COOLING_UPPER_LIM}
};

/* check the input value and return breach type  */
BreachType inferBreach(CoolingType coolingType, double temperatureInC) 
{
 if(temperatureInC < limitCategory[coolingType].lowerLimit) 
  {
    return TOO_LOW;
  }
  if(temperatureInC > limitCategory[coolingType].upperLimit) 
  {
    return TOO_HIGH;
  }
    return NORMAL;
}

int checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
BreachType breachType = inferBreach(batteryChar.coolingType, temperatureInC);
return selectTarget(alertTarget,breachType);
}

/* Alert target selection */
int selectTarget(AlertTarget alertTarget,BreachType breachType)
{
	if(alertTarget == TO_CONTROLLER)
	{
    return sendToController(breachType);
	}
    return sendToEmail(breachType);
}

int sendToController(BreachType breachType) {
const unsigned short header = 0xfeed;
printf("%x : %x\n", header, breachType);
return 0;
}

int sendToEmail(BreachType breachType) {
const char* recipient = "a.b@c.com";
printf("To: %s\n", recipient);
printf("%s\n",BreachMessage[breachType]);
return 0;
}
