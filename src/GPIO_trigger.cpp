#include "duckscript.hpp"
#include "GPIO_trigger.hpp"
 
GpioTrigger::GpioTrigger()
{
    debugln("GpioTrigger::GpioTrigger");
}


void GpioTrigger::begin(int ledpNum)
{
    int f;
    debugf("GpioTrigger::begin %d\n", ledpNum);
    GpioTrigger::ledpinNum=ledpNum;
    for(f=0;f< gpio_pins_len ;f++)
    {
        if (ledpNum != gpio_pins[f] )
        {
         pinMode(gpio_pins[f],INPUT_PULLUP);
        }
    }
    for(f=0;f< gpio_pins_len ;f++)
    {
        pinstate[f]=digitalRead(gpio_pins[f]);
    } 
}

void GpioTrigger::update() 
{
    int f;
    for(f=0;f< gpio_pins_len ;f++)
    {
        if (GpioTrigger::ledpinNum != gpio_pins[f] )
        {
            if(pinstate[f]!=digitalRead(gpio_pins[f]))
            {
                pinstate[f]=digitalRead(gpio_pins[f]);
                debugf("Pin %d %d",gpio_pins[f],pinstate[f]);
                char filename[10];
                if(pinstate[f]==0)   
                    sprintf(filename,"/gpiolow%d",gpio_pins[f]);
                    else
                    sprintf(filename,"/gpiohi%d",gpio_pins[f]);
                duckscripts_run(filename);
            }
        }  
    } 
}
