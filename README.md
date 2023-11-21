# RMT Sandbos

Code to FAFO esp-ifd v5.1/Arduino Core 3.0 RMT functionality

## Notes
* using `uint64_t` does not work. waveform goes batshit.

## Getting Started

### Dependencies

* ESP-IDF is required.

### Installing

* ESP-IDF
    * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/
    * (Make sure you choose v5.1, not 'latest')

* RMTSandbox
    * git clone locally
    ````
    cd RMTSanbox
    mkdir -p components && \
    cd components && \
    git clone https://github.com/espressif/arduino-esp32.git arduino && \
    cd arduino && \
    git submodule update --init --recursive && \
    cd ../..
    ```````
    * Select your MCU and serial port
    * manually edit your `sdkconfig` file:
        * Find: `CONFIG_FREERTOS_HZ=100`
        * Replace with: `CONFIG_FREERTOS_HZ=1000`
    * Run `idf.py menuconfig` or click gear icon at bootom
    

### Executing program

* How to run the program
* Step-by-step bullets
```
code blocks for commands
```

## Help

Any advise for common problems or issues.
```
command to run if program contains helper info
```

## Authors

Contributors names and contact info

[Jason M. Schwefel](jason.schwefel78@gmail.com)


## Version History


* 0.1
    * Initial Release

## License

This project is licensed under the GPL License - see the LICENSE.md file for details
