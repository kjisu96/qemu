#ifndef ADXL345_H
#define ADXL345_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

// Logging levels
typedef enum LogLevel {
    LOG_LEVEL_WARNING,
    LOG_LEVEL_NOISY,
    LOG_LEVEL_QUIET
} LogLevel;

// ACK, NACK responses
typedef enum Response {
    ACK = true,
    NACK = false
} Response;

// ADXL345 I2C slave address
#define ADXL345_ADDRESS 0xE5
#define MAX_FIFO_DEPTH  32
#define NUM_REGISTERS   0x39

#define LOG_LEVEL LOG_LEVEL_QUIET

// Enum for Registers
typedef enum {
    DeviceID = 0x00,
    // 0x01 to 0x1C are reserved
    // TapThreshold = 0x1D,
    Xoffset = 0x1E,
    Yoffset = 0x1F,
    Zoffset = 0x20,
    // TapDuration = 0x21,
    // TapLatency = 0x22,
    // TapWindow = 0x23,
    // ActivityThreshold = 0x24,
    // InactivityThreshold = 0x25,
    // InactivityTime = 0x26,
    // AxisEnableControlForActivityAndInactivityDetection = 0x27,
    // FreeFallThreshold = 0x28,
    // FreeFallTime = 0x29,
    // AxisControlForSingleTapDoubleTap = 0x2A,
    // SourceOfSingleTapDoubleTap = 0x2B,
    DataRateAndPowerModeControl = 0x2C,
    PowerSavingFeaturesControl = 0x2D,
    // InterruptEnableControl = 0x2E,
    // InterruptMappingControl = 0x2F,
    // SourceOfInterrupts = 0x30,
    DataFormatControl = 0x31,
    Xdata0 = 0x32,
    Xdata1 = 0x33,
    Ydata0 = 0x34,
    Ydata1 = 0x35,
    Zdata0 = 0x36,
    Zdata1 = 0x37,
    FifoControl = 0x38,
    FifoStatus = 0x39
} Registers;

// Enum for Range
typedef enum {
    G2  = 0,
    G4  = 1,
    G8  = 2,
    G16 = 3
} Range;

// Enum for Range
typedef enum {
    BYPASS  = 0,
    FIFO  = 1,      // TODO
    STREAM  = 2,    // TODO
    TRIGGER = 3     // TODO
} FifoMode;

// Struct for Sample
typedef struct {
    int16_t X;
    int16_t Y;
    int16_t Z;
} Sample;

// Node for Sample Queue
typedef struct SampleNode {
    Sample sample;
    struct SampleNode* next;
} SampleNode;

// Sample Queue
typedef struct SampleQueue {
    SampleNode* front;
    SampleNode* rear;
    int count;
} SampleQueue;


// Struct for ADXL345 peripheral
typedef struct ADXL345 {
    SampleQueue samplesFifo;
    Range range;
    Registers lastRegister;
    Sample currentSample;
    FILE* file;

    /* Registers */
    uint8_t regs[NUM_REGISTERS];
    uint8_t _xOffset;
    uint8_t _yOffset;
    uint8_t _zOffset;
    uint16_t _outputDataRate;
    bool _isMeasurementEnabled;
    Range _range;
    FifoMode _fifoMode;
} Sensor;


// Function prototypes
void Log(LogLevel level, const char* format, ...);

void initSensor(Sensor* dev, const char* path);
void resetSensor(Sensor* dev);

//////////////////////////////////////////////////////
// TODO
// Sensor API
//////////////////////////////////////////////////////
Response genStart(Sensor* dev);
Response genStop(Sensor* dev);
Response devAddr(Sensor* dev, uint8_t dev_addr);
Response regAddr(Sensor* dev, Registers reg_addr);
Response setReg(Sensor* dev, uint8_t data);
uint8_t getReg(Sensor* dev);
//////////////////////////////////////////////////////

void get_sample_from_file(Sensor* dev, Sample* sample);
void get_sample_from_equation(Sensor* dev, Sample* sample);

// for ADXL345 FIFO
void init_queue(SampleQueue* queue);
bool enqueue(SampleQueue* queue, Sample sample);
bool dequeue(SampleQueue* queue, Sample* sample);
bool peek(SampleQueue* queue, Sample* sample);
void clear_queue(SampleQueue* queue);


#endif // ADXL345_H
