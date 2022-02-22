#include "typewise-alert.h"
#include <stdio.h>


/* check the input value and return the required cooling type  */
BreachType inferBreach(CoolingType coolingType, double temperatureInC) 
{
 if(temperatureInC < limit[coolingType].lowerLimit) 
  {
    return TOO_LOW;
  }
  if(temperatureInC > limit[coolingType].upperLimit) 
  {
    return TOO_HIGH;
  }
  return NORMAL;
}

/* Alert target selection  */
char *BreachMessage[] = {"Hi, battery temperature is Ok\n", "Hi, the temperature is too low\n", "Hi, the temperature is too high\n"};

BreachType checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
BreachType breachType = inferBreach(batteryChar.coolingType, temperatureInC);
char Target1 = (alertTarget == TO_CONTROLLER) ? sendToController(breachType) : sendToEmail(breachType);
char Target2 = (alertTarget == TO_EMAIL) ? sendToEmail(breachType) : sendToController(breachType);
char Target = Target1 | Target2;
return Target;
}

int sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

int sendToEmail(BreachType breachType) {
const char* recipient = "a.b@c.com";
printf("To: %s\n", recipient);
printf("%s\n",BreachMessage[breachType]);
}



 



