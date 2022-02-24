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

TEST_CASE("check the breach type and alert selected target")
{
 BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "OKAYA"};
 REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -99) == 0);
 REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,22) == 0);
}
  
TEST_CASE("selection of target for breach alert")
{
REQUIRE(selectTarget(TO_CONTROLLER,NORMAL)==0);
REQUIRE(selectTarget(TO_EMAIL,TOO_LOW)==0);
REQUIRE(selectTarget(TO_CONTROLLER,TOO_HIGH)==0);
REQUIRE(selectTarget(TO_EMAIL,TOO_HIGH)==0);
}

TEST_CASE("check and print alert to controller")
{
REQUIRE(sendToController(TOO_LOW)==0);
REQUIRE(sendToController(TOO_HIGH)==0);
}

TEST_CASE("check and print alert to mail")
{
REQUIRE(sendToEmail(TOO_LOW)==0);
REQUIRE(sendToEmail(TOO_HIGH)==0);
}
