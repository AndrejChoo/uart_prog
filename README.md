# uart_prog
Programmer spi flash 25xx, i2c eeprom 24xx and microwire eeprom 93xx on arduino.

Проект позволяет сделать из arduino nano/uno (а при желании - из любого микроконтроллера, имеющего на борту UART,SPI,I2C и хотя бы 1Кб ОЗУ) программатор SPI-Flash 25-й серии, I2C-EEPROM 24-й серии и Microwire EEPROM 93-й серии. Программируемые микросхемы можно подключать прямо к ножкам ардуины проводами (для 24хх еепром, необходимо подтянуть линии SCL, SDA к плюсу питания) см. схему подключения:

![scheme](https://github.com/AndrejChoo/uart_prog/blob/main/hardware/Schematic_UART_Prog_2024-11-25.png)

Программа для ПК написана на C# для Windows и переписана на Qt для Linux и Windows. Она имеет графическую оболочку, что значительно упрощает работу. Внешний вид программы:
![soft](https://github.com/AndrejChoo/uart_prog/blob/main/software/soft.png)


 
