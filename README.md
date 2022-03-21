# STM32 Embedded Project reference
Complete embedded C\C++ code for STM32 microcontrollers.
The idea behind this project is to have a complete reference to build an embedded project based on the ARM GNU toolchain starting from complete scratch. All the files have been written from scratch and are fully documented in order to be easily reused in the future as fast refresh reference.

This project contains a complete embedded application: 

- Boostrap\startup.c file
- Memory layout\Linker script
- Peripheral drivers + demos
- Build system\Make file
- *Python tools for scripting and miscellaneous* (to implement)

The project contain also the configuration files to:
- Use **Visual Studio Code** as main IDE for editing source files.
- Use **Eclipse MCU** as main IDE to debug your application.

Details on configuration are reported in the following sections.

## How to use
This project can be used as the harness to build up a fully customazible project on STM32 microcrontroller from scratch.
#### Compile a project
To build a project enter the main source directory and run the following command:
* Define the `$(ROOT)` variable in *makefile* defining the path to your toolchain. 
*You can use a toolchain reported in the [Toolchain](https://github.com/lzzzam/Toolchain) repository.* 
* Define the `$(TARGET)` variable in the *makefile* selecting a file in *test* directory.
* Add paths to include or source files in the `$(INC)` and `$(SRC)` *makefile*'s variables if necessary.
* Enter the *src* directory and run `make` command.

#### Debug a project
To debug a project with Eclipse MCU:
```
**Pre-requisites**
*Setup the debug environment following the instructions reported in the dedicated section.*
```

After installation and setup of Eclipse MCU, open your project and:
* Right-click on the project directory
* Select *Debug as > Debug Configurations*
* Create a new **GDB Segger J-Link Debugging** session:
  - *Main Tab*: insert *Project* name + *your_target.elf* file as C\C++ application to debug.
  - *Debugger Tab*: ![Debugger Tab configuration](Img/readme/eclipse_mcu_debug_debugger_tab.png?raw=true "Debugger Tab")
  
  Insert STM32F303RE as device name and select SWD\JTAG interface.

  **IMPORTANT**
  Select as *GDB Client* the *arm-none-eabi-gdb* binary from the same toolchain of the *arm-none-eabi-gcc* compiler.
  

  - *Startup/Source/Common Tabs*: leave default configuration
  - *SVD Path*: insert the file under `STM32F303RE/Conf/STM32F303.svd`
  - Apply and start debug session.

## Setup environment
#### Setup Visual Studio Code 

#### Setup Eclipse MCU as IDE for debugging
#### Hardware setup
