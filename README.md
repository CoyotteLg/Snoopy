# Snoopy
Little LEDs controler for a static Snoopy plane

Read a servo pulse width and activates LEDs according to 
```
  |            LEDs ON               |             LEDs OFF             |   LED1 & LED2 ON, LED3 Blink    |       
  |----------------------------------|----------------------------------|---------------------------------|
1000 ms                       ON_PULSE_WIDTH       1500 ms       BLINK_PULSE_WIDTH                     2000 ms
```
In blink, LED 3 is flashing while LED1 and LED2 are ON  
Flash duration is ajusted by the pulse lenght : The more close to 2000ms, the longer the LED is ON
