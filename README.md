# ArduinoUnoR3-MelziLCD-Control
Opensource Pinouts and Code to independently control the LCD shipped with the Melzi Boards for Monoprice Di3 and Wanhao printers. Developed by working with ChatGPT4.
Written utilizing the Encoder and U8g2 Libraries.

Custom Pinout: 

    1: LCD CS --------------------------------- D10 (Digital)

    2: Encoder B ------------------------------- D3 (Digital)
    
    3: LCD Data ---------------------------------- D11 (MOSI)
    
    4: Encoder A ------------------------------- D2 (Digital)
    
    5: LCD SCLK ----------------------------------- D13 (SCK)
    
    6: Encoder Button -------------------------- D4 (Digital)
    
    7: ESTOP ----------------------------------- D5 (Digital)
    
    8: Beeper -------------------------------------- D6 (PWM)
    
    9: 5V ------------------------------------------------ 5V
    
    10: GND ---------------------------------------------- GND

Knowledge Sources:

Interfacing with the Wanhao i3 LCD: 
https://reprap.org/forum/read.php?415,873380

How Do I Configure Pinouts For A LCD: 
https://reprap.org/forum/read.php?415,885957