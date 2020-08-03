[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# SPI Driver asynchronous - multi instance

This example demonstrates how to use multiple instances of the SPI driver in asynchronous mode to communicate with multiple EEPROMs

## Description

This example writes and reads data to and from two separate EEPROM connected over two different SPI bus by using multi instance feature of the driver. The example also demonstrates how to setup two different EEPROM transfers at different baud rates.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/core_apps_pic32mx) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/driver/spi/async/spi_multi_instance/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| pic32mx470_curiosity.X | MPLABX project for [Curiosity PIC32MX470 Development Board](https://www.microchip.com/Developmenttools/ProductDetails/dm320103) |
|||

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| pic32mx470_curiosity.X | [Curiosity PIC32MX470 Development Board](https://www.microchip.com/Developmenttools/ProductDetails/dm320103) |
|||

- To run the demo, the following additional hardware are required:
    - Two [EEPROM 4 Click](https://www.mikroe.com/eeprom-4-click) boards

### Setting up [Curiosity PIC32MX470 Development Board](https://www.microchip.com/Developmenttools/ProductDetails/dm320103)

- Connect mini USB cable to the 'Debug USB' connector(J3) on the board to the computer
- Install two [EEPROM 4 Click](https://www.mikroe.com/eeprom-4-click) boards on to the two mikroBUS sockets(J5 & J10) of [Curiosity PIC32MX470 Development Board](https://www.microchip.com/Developmenttools/ProductDetails/dm320103)
- **Note:** Ensure that the series resistors on the mikroBUS headers are of value 0 Ohms

## Running the Application

1. Build and program the application using its IDE
2. The LED is turned ON when the data read from the EEPROMs matches with the data written to the EEPROMs 

Refer to the following table for LED name:

| Board | LED Name |
| ----- | -------- |
|  [Curiosity PIC32MX470 Development Board](https://www.microchip.com/Developmenttools/ProductDetails/dm320103) | LED1 |
|||