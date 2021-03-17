#include <iostream>
#include <assert.h>
#include "BMSUtils.h"


Parameter::Parameter(Language Lang, float min_value, float max_value, string name)
{
    min_threshold = min_value;
    max_threshold = max_value;
    parameter_name = name;
    tolerance = max_threshold * 0.05 ;
    if(Lang == ENGLISH){

        error_msg = "Out of range";
        warning_msg = "Close to warning range";

    }
    else if(Lang == DEUTSCH){
        error_msg = "Außer Reichweite";
        warning_msg = "In der Nähe des Warnbereichs";
    }
}

bool Parameter :: check_min(float value){
    if(value>=min_threshold)
    {
        if(value <= min_threshold + tolerance)
            cout << parameter_name << " - "<< warning_msg <<endl;
        return true;
    }
    else
    {
        cout << parameter_name << " - "<< error_msg <<endl;
        return false;
             
    }
       
 
};

bool Parameter ::  check_max(float value){

    if(value<=max_threshold)
        {
            if(value >= max_threshold - tolerance)
                cout << parameter_name << " - "<< warning_msg <<endl;
            return true;
        }
        else
        {
                cout << parameter_name << " - "<< error_msg <<endl;
                return false;
        }

};

bool Parameter::check_threshold(float value){

    return (check_min(value) &&  check_max(value));
};

void temperature::Conversion (float unit){

    if (unit == FAHRENHEIT){
         min_threshold = (min_threshold - 32)*5/9;
         max_threshold = (max_threshold - 32)*5/9;
    }

};

temperature::temperature(Language Lang, float min_value, float max_value, string name ,UnitType unit) 
: Parameter (Lang, min_value, max_value, name ) 
{
    Conversion(unit);
};


StateOfCharge :: StateOfCharge(Language Lang, float min_value, float max_value, string name) : Parameter( Lang, min_value, max_value, name ){};




ChargeRate :: ChargeRate(Language Lang, float min_value, float max_value, string name) : Parameter( Lang, min_value, max_value, name ){};


BMS::BMS(Language Lang, UnitType temperature_unit)
{
    if(Lang == ENGLISH)
    {
        temperatureObj = new temperature(Lang, MIN_TEMP_THRESHOLD, MAX_TEMP_THRESHOLD,"Temperature",temperature_unit);
        stateOfChargeObj = new StateOfCharge(Lang, MIN_STATE_OF_CHARGE, MAX_STATE_OF_CHARGE,"StateOfCharge");
        chargeObjRate = new ChargeRate(Lang, MIN_CHARGE_RATE, MAX_CHARGE_RATE,"ChargeRate");
    }
        temperatureObj = new temperature(Lang, MIN_TEMP_THRESHOLD, MAX_TEMP_THRESHOLD,"Temperatur",temperature_unit);
        stateOfChargeObj = new StateOfCharge(Lang, MIN_STATE_OF_CHARGE, MAX_STATE_OF_CHARGE,"Ladezustand");
        chargeObjRate = new ChargeRate(Lang, MIN_CHARGE_RATE, MAX_CHARGE_RATE,"Ladestrom");
    }
};

bool BMS::isBatteryOK(float temperature, float SOC, float charge_rate)
{
    return( temperatureObj->check_threshold(temperature) &&
            stateOfChargeObj->check_threshold(SOC) &&
            chargeObjRate->check_threshold(charge_rate));
}
