#include <iostream>
#include <assert.h>
#include "BMSUtils.h"
using namespace std;

int main() {
    class BMS * BMS_obj = new BMS(DEUTSCH,FAHRENHEIT);
    
    assert(BMS_obj->isBatteryOK(44,22,0.7) == true);
    assert(BMS_obj->isBatteryOK(85,20,0.8) == false);
    assert(BMS_obj->isBatteryOK(40,83,0.9) == false);
    assert(BMS_obj->isBatteryOK(25,30,0.5) == true);
    assert(BMS_obj->isBatteryOK(2,23,0.5) == true);
    
}
