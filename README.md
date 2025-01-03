# uart_prog
Programmer spi flash 25xx, i2c eeprom 24xx and microwire eeprom 93xx on arduino.

Проект позволяет сделать из arduino nano/uno (а при желании - из любого микроконтроллера, имеющего на борту UART,SPI,I2C и хотя бы 1Кб ОЗУ) программатор SPI-Flash 25-й серии, I2C-EEPROM 24-й серии и Microwire EEPROM 93-й серии. Программируемые микросхемы можно подключать прямо к ножкам ардуины проводами (для 24хх еепром, необходимо подтянуть линии SCL, SDA к плюсу питания) см. схему подключения:

![scheme](https://github.com/AndrejChoo/uart_prog/blob/main/hardware/Schematic_UART_Prog_2024-11-25.png)

Программа для ПК написана на C# для Windows и переписана на Qt для Linux и Windows. Она имеет графическую оболочку, что значительно упрощает работу. Внешний вид программы:
![soft](https://github.com/AndrejChoo/uart_prog/blob/main/software/soft.png)

При работе на Linux потребуется установить некоторые пакеты Qt (qserialport, qt-base, возможно ещё какие-нибудь, можно проверить при запуске из терминала), также возможно потребуется предоставить права доступа для /dev/ttyUSB0 (chmod a+rw /dev/ttyUSB0). На Ubuntu возможны проблемы с ch340 USB-UART-преобразователем, он может конфликтовать с пакетом brltty, его можно удалить.

Скорость работы программатора с обоими типами ЕЕПРОМ достаточно высокая, чтение занимает секунды для самого ёмкого чипа 24С256, а вот скорость работы с флешками 25хх сильно ограничена UART-ом, чтение одного Мегабайта может занимать от 1,5 минут (исключение - микроконтроллеры с аппаратным USB и обменом по CDC, в этом случае чтение 1 Мегабайта занимает несколько секунд). 
В списке поддерживаемых SPI-Flash 25-й серии указаны только флешки компании Winbond, но так как многие флешки разных производителей программируются однотипно, просто выбираем из списка флешку соответствующего объёма. В данной версии прошивки будут корректно работать флешки до 8 Мегабайт включительно (с трёхбайтной адресацией до w25q64 включительно), w25q128 и более я не проверял, да и время работы с такой флешкой будет неадекватное.
Касаемо моделей еепром обоих типов - в списке представлены универсальные модели без учёта производителя.

В папке "source" находятся исходные коды проекта для atmega328p, написанные под avr-gcc. Проект можно легко переписать под любой другой микроконтроллер. Для этого необходимо переписать функции инициализации периферии (GPIO, USART, SPI, I2C) и реализовать прерывание по приёму байта по USART. 

HEX-файл прошивки в папке "firmware" скомпилирован для atmega328p (arduino nano/uno), работающей от кварца на 16MHz. Плату ардуино можно прошить через встроенный USB с помощью программы "ArduinoUploader" и ей подобным.

Также добавлены скомпиллированные прошивки ещё для некоторых плат/микроконтроллеров как распространённых, так и экзотических (эти прошивки толком не проверялись, некоторые функции могут работать некорректно!). Все прошивки снабжены инструкцией по подключению программируемых чипов. 

 
