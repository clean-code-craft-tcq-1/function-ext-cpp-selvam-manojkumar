#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

#define MIN_TEMP_THRESHOLD			0
#define MAX_TEMP_THRESHOLD			45
#define MIN_STATE_OF_CHARGE			20
#define MAX_STATE_OF_CHARGE			80
#define MAX_CHARGE_RATE				0.8
#define MIN_CHARGE_RATE             0

/* 
*
* add supported languges here
*
*/
typedef enum {
    ENGLISH,
    DEUTSCH
} Language;
/* 
*
* units for temperature added here
*
*/
typedef enum {
    CELCIUS,
    FAHRENHEIT
} UnitType;

string pramameter_name_english[] = {"Temperature" , "SOC" , "Charge Rate" };
string pramameter_name_deutch[] =  {"Temperatur" , "Ladezustand" , "Laderate" };


/*
* Parent class for parameters which can inherit the common metheods
*/

class Parameter{
    public:
        float min_threshold;
        float max_threshold;
        float tolerance;
        string parameter_name;
        string error_msg;
        string warning_msg;
        Parameter(Language Lang, float min_value, float max_value, string name);
        bool check_threshold(float value);
        bool check_min(float value);
        bool check_max(float value);
};



class temperature : public Parameter{
    
    public:
        temperature(Language Lang, float min_value, float max_value, string name ,UnitType unit);
        void Conversion(float unit);
};


class StateOfCharge : public Parameter{

    public:
        StateOfCharge(Language Lang, float min_value, float max_value, string name);
};


class ChargeRate : public Parameter{
    public:
        ChargeRate(Language Lang, float min_value, float max_value, string name);

};

/*
* class which encapsulate all the params needed by a battery management system
*/

class BMS {
    public: 
       Parameter * temperatureObj;
       Parameter * stateOfChargeObj;
       Parameter * chargeObjRate; 
       BMS(Language Lang, UnitType temperature_unit);
       bool isBatteryOK(float temperature, float SOC, float charge_rate);
};

