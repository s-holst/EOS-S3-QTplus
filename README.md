# Get Started With SparkFun QuickLogic Thing Plus - EOS S3

Do you want to play with the QuickLogic EOS S3 MCU + eFPGA SoC on the new Thing+ board from SparkFun? Are you tired of poor PDF documentation and confusing SDKs? This project might be something for you.

The goal of this project is to document registers and functions of the SoC and the board in a VSCode friendly way and to provide bare-bones startup code for tinkering.
There are no references to any SDKs or libraries other than the stock [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads). There is no build system other than a simple Makefile. The code is kept as simple, small, and clear as possible.

To get started, have the toolchain installed, type `make`, and load the compiled `main.elf` to the device via JLink or other means. The main program reads the accelerometer via I2C and sends its data via UART on pads 44 and 45.

It is also very much a work-in-progress. For now, only the most basic definitions are included. I'll be adding information as a learn more about this device. Feel free to send me PRs for the parts you care about.

## Links

* [SparkFun Product Page](https://www.sparkfun.com/products/17273)
  * [Hookup Guide](https://learn.sparkfun.com/tutorials/quicklogic-thing-plus-eos-s3-hookup-guide)
* [QuickLogic SDK with FreeRTOS](https://github.com/QuickLogic-Corp/qorc-sdk)



