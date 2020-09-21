SparkFun Particle Sensor SN-GCJA5 Arduino Library
========================================

![SparkFun Panasonic SN-GCJA5 Particle Sensor](https://cdn.sparkfun.com//assets/parts/1/6/0/9/3/17123-Particle_Sensor_-_SN-GCJA5-01.jpg)

[*SparkFun Panasonic SN-GCJA5 Particle Sensor (SPX-17123)*](https://www.sparkfun.com/products/17123)

The Panasonic SN-GCJA5 is a highly accurate and easy to use particle matter detector. Great for detecting PM1.0, PM2.5, and PM10 sized particles. The only downside to this device is that it requires 5V (presumably to run the fan) but 3.3V for the I2C interface pins. We recommend connecting the sensor to a 3.3V micro such as the [SparkFun BlackBoard](https://www.sparkfun.com/products/16282) set to 3.3V.

Note: The SN-GCJA5 also supports a 9600bps serial interface but this library is only written for the I2C interface. If anyone would like to expand the library to accept serial as well, we would welcome the PR!

## Repository Contents

- **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE.
- **/src** - Source files for the library (.cpp, .h).
- **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE.
- **library.properties** - General library properties for the Arduino package manager.

## Products That Use This Library

- [Particle Sensor - SN-GCJA5 (SPX-17123)](https://www.sparkfun.com/products/17123)

## Documentation

- **[Installing an Arduino Library Guide](https://learn.sparkfun.com/tutorials/installing-an-arduino-library)** - Basic information on how to install an Arduino library.

## License Information

This product is _**open source**_!

Please use, reuse, and modify these files as you see fit.
Please maintain the attribution and release anything derivative under the same license.

Distributed as-is; no warranty is given.
