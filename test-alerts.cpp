#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") 
{
REQUIRE(inferBreach(PASSIVE_COOLING, -20)== TOO_LOW);
REQUIRE(inferBreach(PASSIVE_COOLING, 0)== NORMAL);
REQUIRE(inferBreach(PASSIVE_COOLING, 38)== TOO_HIGH);
REQUIRE(inferBreach(HI_ACTIVE_COOLING, -15)== TOO_LOW);
REQUIRE(inferBreach(HI_ACTIVE_COOLING, 6)== NORMAL);
REQUIRE(inferBreach(HI_ACTIVE_COOLING, 60 )== TOO_HIGH);
REQUIRE(inferBreach(MED_ACTIVE_COOLING, -1)== TOO_LOW);
REQUIRE(inferBreach(MED_ACTIVE_COOLING, 20)== NORMAL);
REQUIRE(inferBreach(MED_ACTIVE_COOLING, 46)== TOO_HIGH);
}

TEST_CASE("check the breach type and alert selected target - 1")
{
 BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "OKAYA"};
 REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -9) == 0);
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,-9) == 0);
 REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 1) == 0);
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,1) == 0);
 REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 42) == 0);
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,42) == 0);
}
TEST_CASE("check the breach type and alert selected target - 2")
{
 BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "OKAYA"};
 REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -20) == 0);
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,-70) == 0);
 REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 15) == 0);
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,15) == 0);
 REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 55) == 0);
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,55) == 0);
}
TEST_CASE("check the breach type and alert selected target - 3")
{
 BatteryCharacter batteryChar = {PASSIVE_COOLING, "OKAYA"};
 REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -1) == 0);
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,-1) == 0);
 REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 20) == 0);
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,20) == 0);
 REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 36) == 0);
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,36) == 0);
}
  
TEST_CASE("selection of target for breach alert")
{
REQUIRE(selectTarget(TO_CONTROLLER,TOO_LOW)==0);
REQUIRE(selectTarget(TO_EMAIL,TOO_LOW)==0);
REQUIRE(selectTarget(TO_CONTROLLER,TOO_HIGH)==0);
REQUIRE(selectTarget(TO_EMAIL,TOO_HIGH)==0);
REQUIRE(selectTarget(TO_CONTROLLER,NORMAL)==0);
REQUIRE(selectTarget(TO_EMAIL,NORMAL)==0);
}

TEST_CASE("check and print alert to controller")
{
REQUIRE(sendToController(TOO_LOW)==0);
REQUIRE(sendToController(TOO_HIGH)==0);
REQUIRE(sendToController(NORMAL)==0);
}

TEST_CASE("check and print alert to mail")
{
REQUIRE(sendToEmail(TOO_LOW)==0);
REQUIRE(sendToEmail(TOO_HIGH)==0);
REQUIRE(sendToEmail(NORMAL)==0);
}
