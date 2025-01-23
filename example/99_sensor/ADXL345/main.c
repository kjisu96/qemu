#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>

#include "ADXL345.h"

int main() {


    void *handle = dlopen("./ADXL345.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    void (*dl_initSensor)();
    Response (*dl_genStart)();    
    Response (*dl_genStop)();
    Response (*dl_devAddr)();    
    Response (*dl_regAddr)();
    Response (*dl_setReg)();
    uint8_t (*dl_getReg)();

    *(void **)(&dl_initSensor) = dlsym(handle, "initSensor");
    *(void **)(&dl_genStart) = dlsym(handle, "genStart");
    *(void **)(&dl_genStop) = dlsym(handle, "genStop");
    *(void **)(&dl_devAddr) = dlsym(handle, "devAddr");
    *(void **)(&dl_regAddr) = dlsym(handle, "regAddr");
    *(void **)(&dl_setReg) = dlsym(handle, "setReg");
    *(void **)(&dl_getReg) = dlsym(handle, "getReg");

    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Error: %s\n", error);
        dlclose(handle);
        return 1;
    }

    /*************************/
    // Variables
    /*************************/
    uint8_t recv;
    uint16_t acc[3] = {0};

    /*************************/
    // Sensor Object Declaration
    // @ stm32_xxx_realize_callback
    // xxx = I/F name (ex. i2c)
    /*************************/
    Sensor _ADXL345;
    dl_initSensor(&_ADXL345, "data.txt");

    /*************************/
    // I2C Start Signal Generation
    // @ I2C_SR1 pre-read callback at ST_START
    /*************************/
    if( dl_genStart(&_ADXL345) ) {
        printf("success: I2C Start\n");
    } else {
        printf("Error: I2C Start\n");
    }

    /*************************/
    // I2C Slave Device Address
    // @ I2C_SR1 pre-read callback at ST_DEV_ADDR
    /*************************/
    if( dl_devAddr(&_ADXL345, 0xE4) ) {
        printf("success: Device Address - 0x%X\n", 0xE4);
    } else {
        printf("Error: Device Address - 0x%X\n", 0xE4);
    }
    if( dl_devAddr(&_ADXL345, 0xE5) ) {
        printf("success: Device Address - 0x%X\n", 0xE5);
    } else {
        printf("Error: Device Address - 0x%X\n", 0xE5);
    }    

    /*************************/
    // I2C Register Address
    // @ I2C_SR1 pre-read callback at ST_REG_ADDR
    /*************************/
    if( dl_regAddr(&_ADXL345, 0x44) ) {
        printf("success: Register Address - 0x%X\n", 0x44);
    } else {
        printf("Error: Register Address - 0x%X\n", 0x44);
    }
    if( dl_regAddr(&_ADXL345, 0x1E) ) {
        printf("success: Register Address - 0x%X\n", 0x1E);
    } else {
        printf("Error: Register Address - 0x%X\n", 0x1E);
    }

    /*************************/
    // I2C Register Write
    // @ I2C_SR1 pre-read callback at ST_WR_DATA
    /*************************/
    if( dl_setReg(&_ADXL345, 0x11) ) {
        printf("success: Set Register Value - 0x%X\n", 0x11);
    } else {
        printf("Error: Set Register Value - 0x%X\n", 0x11);
    }

    /*************************/
    // I2C Register Read
    // @ I2C_SR1 pre-read callback at ST_RD_DATA
    /*************************/
    if( dl_regAddr(&_ADXL345, 0x1E) ) {
        printf("success: Register Address - 0x%X\n", 0x1E);
    } else {
        printf("Error: Register Address - 0x%X\n", 0x1E);
    }
    recv = dl_getReg(&_ADXL345);
    if( recv == 0x11 ) {
        printf("success: Get Register Value - 0x%X\n", recv);
    } else {
        printf("Error: Get Register Value - 0x%X\n", recv);
    }

    /*************************/
    // I2C Stop Signal Generation
    // @ I2C_SR1 pre-read callback at ST_STOP
    /*************************/
    if( dl_genStop(&_ADXL345) ) {
        printf("success: I2C Stop\n");
    } else {
        printf("Error: I2C Stop\n");
    }

    /******************************************************/
    // Multiple Register Read/Write
    /******************************************************/
    Registers reg_addr_arr[7] = {0x1E, 0x1F, 0x20, 0x2C, 0x2D, 0x31, 0x38};
    uint8_t data_arr[7] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};
    for(int i=0; i < 7; i++) {
        if( dl_regAddr(&_ADXL345, reg_addr_arr[i]) ) {
            printf("success: Register Address - 0x%X\n", reg_addr_arr[i]);
        } else {
            printf("Error: Register Address - 0x%X\n", reg_addr_arr[i]);
        }
        if( dl_setReg(&_ADXL345, data_arr[i]) ) {
            printf("success: Set Register Value - 0x%X\n", data_arr[i]);
        } else {
            printf("Error: Set Register Value - 0x%X\n", data_arr[i]);
        }
    }

    for(int i=0; i < 7; i++) {
        if( dl_regAddr(&_ADXL345, reg_addr_arr[i]) ) {
            printf("success: Register Address - 0x%X\n", reg_addr_arr[i]);
        } else {
            printf("Error: Register Address - 0x%X\n", reg_addr_arr[i]);
        }
        recv = dl_getReg(&_ADXL345);
        if( recv == data_arr[i] ) {
            printf("success: Get Register Value - 0x%X\n", recv);
        } else {
            printf("Error: Expected Register Value - 0x%X, but 0x%X\n", data_arr[i], recv);
        }
    }

    puts("\n\n===========================");
    dl_regAddr(&_ADXL345, Xdata0);
    acc[0] = dl_getReg(&_ADXL345);
    dl_regAddr(&_ADXL345, Xdata1);
    acc[0] |= dl_getReg(&_ADXL345) << 8;
    dl_regAddr(&_ADXL345, Ydata0);
    acc[1] = dl_getReg(&_ADXL345);
    dl_regAddr(&_ADXL345, Ydata1);
    acc[1] |= dl_getReg(&_ADXL345) << 8;
    dl_regAddr(&_ADXL345, Zdata0);
    acc[2] = dl_getReg(&_ADXL345);
    dl_regAddr(&_ADXL345, Zdata1);
    acc[2] |= dl_getReg(&_ADXL345) << 8;

    for(int i=0; i < 3; i++) {
        printf("acc[%d] = %d \n", i, acc[i]);
    }
    puts("===========================");


    dlclose(handle);

    return 0;
}
