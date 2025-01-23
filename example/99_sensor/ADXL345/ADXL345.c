#include "ADXL345.h"


// Logging function
void Log(LogLevel level, const char* format, ...) {
    va_list args;
    va_start(args, format);
    if( level == LOG_LEVEL_QUIET ) {
        return;
    } else if( level == LOG_LEVEL_WARNING ) {
        printf("WARNING: ");
    } else if( level == LOG_LEVEL_NOISY ) {
        printf("NOISY: ");
    }
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

// Initialize the queue
void init_queue(SampleQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
}

// Enqueue a sample
bool enqueue(SampleQueue* queue, Sample sample) {
    if(queue->count == MAX_FIFO_DEPTH) {
        Log(LOG_LEVEL, "FIFO is full, dropping sample");
        return false;
    }
    SampleNode* node = (SampleNode*)malloc(sizeof(SampleNode));
    node->sample = sample;
    node->next = NULL;
    if(queue->rear == NULL) {
        queue->front = node;
        queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->count++;

    return true;
}

// Dequeue a sample. Returns TRUE if successful, FALSE otherwise.
bool dequeue(SampleQueue* queue, Sample* sample) {
    if(queue->front == NULL) {
        Log(LOG_LEVEL, "FIFO is empty, no samples to dequeue");
        return false;
    }
    SampleNode* temp = queue->front;
    *sample = temp->sample;
    queue->front = queue->front->next;
    if(queue->front == NULL)
        queue->rear = NULL;
    free(temp);
    queue->count--;

    return true;
}

// Peek at the front sample. Returns 1 if successful, 0 otherwise.
bool peek(SampleQueue* queue, Sample* sample) {
    if(queue->front == NULL) {
        Log(LOG_LEVEL, "FIFO is empty, no samples to peek");
        return false;
    }
    *sample = queue->front->sample;

    return true;
}

// Clear the queue
void clear_queue(SampleQueue* queue) {
    SampleNode* current = queue->front;
    while(current != NULL) {
        SampleNode* temp = current;
        current = current->next;
        free(temp);
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
}

// Initialize the ADXL345 device
void initSensor(Sensor* dev, const char* path) {
    init_queue( &(dev->samplesFifo) );
    dev->range = G2;
    dev->lastRegister = 0;
    dev->currentSample.X = 0;
    dev->currentSample.Y = 0;
    dev->currentSample.Z = 0;

    dev->file = fopen(path, "r");
    if(dev->file == NULL) {
        Log(LOG_LEVEL_WARNING, "There was a problem when reading samples file: Cannot open file");
    }
    dev->regs[DeviceID] = ADXL345_ADDRESS;
    for(int i = 1; i < NUM_REGISTERS; i++) {
        dev->regs[i] = 0;
    }
    dev->_xOffset = 0;
    dev->_yOffset = 0;
    dev->_zOffset = 0;
    dev->_outputDataRate = 100;
    dev->_isMeasurementEnabled = true;
    dev->_range = G2;
}

// Reset the ADXL345 device
void resetSensor(Sensor* dev) {
    dev->range = G2;
    dev->lastRegister = 0;
    dev->currentSample.X = 0;
    dev->currentSample.Y = 0;
    dev->currentSample.Z = 0;
    fclose(dev->file);
    for(int i = 1; i < NUM_REGISTERS; i++) {
        dev->regs[i] = 0;
    }    
    dev->_xOffset = 0;
    dev->_yOffset = 0;
    dev->_zOffset = 0;
    dev->_outputDataRate = 100;
    dev->_isMeasurementEnabled = true;
    dev->_range = G2;
    dev->_fifoMode = FIFO;
    clear_queue( &(dev->samplesFifo) );
}

// Generate start signal
Response genStart(Sensor* dev) {
    Log(LOG_LEVEL, "Generating I2C start signal");
    // TODO check I2C SFR physical configurations (speed, etc.)
    return ACK;
}

// Generate stop signal
Response genStop(Sensor* dev) {
    Log(LOG_LEVEL, "Generating I2C stop signal");
    // TODO check I2C SFR physical configurations (speed, etc.)
    return ACK;
}

// Check I2C Slave Device Address
Response devAddr(Sensor* dev, uint8_t dev_addr) {
    Log(LOG_LEVEL, "Checking I2C slave device address");

    if( dev_addr != dev->regs[DeviceID] ) {
        Log(LOG_LEVEL_WARNING, "Invalid device address: 0x%X", dev_addr);
        Log(LOG_LEVEL_WARNING, "Expected device address: 0x%X", dev->regs[DeviceID]);
        return NACK;
    } else {
        Log(LOG_LEVEL, "Device address is correct: 0x%X", dev_addr);
        return ACK;
    }
}

// Receive sensor register address
Response regAddr(Sensor* dev, Registers reg_addr) {
    Log(LOG_LEVEL, "Receiving register address: 0x%X", reg_addr);
    if( reg_addr > NUM_REGISTERS ) {
        Log(LOG_LEVEL_WARNING, "Invalid register address: 0x%X", reg_addr);
        return NACK;
    } else {
        dev->lastRegister = reg_addr;
        Log(LOG_LEVEL, "Setting register ID to 0x%X - %d", dev->lastRegister, dev->lastRegister);
        return ACK;
    }
}

// Write data to the device
Response setReg(Sensor* dev, uint8_t data) {
    Log(LOG_LEVEL, "Write data 0x%2X to Reg ID 0x%2X", data, dev->lastRegister);

    switch(dev->lastRegister) {
        case Xoffset:
            dev->regs[Xoffset] = data;
            dev->_xOffset = data;
            break;
        case Yoffset:
            dev->regs[Yoffset] = data;
            dev->_yOffset = data;
            break;
        case Zoffset:
            dev->regs[Zoffset] = data;
            dev->_zOffset = data;
            break;
        case DataRateAndPowerModeControl:
            dev->regs[DataRateAndPowerModeControl] = data;
            switch (data & 0xF)
            {
            case 0xF:
                dev->_outputDataRate = 3200;
                break;
            case 0xE:
                dev->_outputDataRate = 1600;
                break;
            case 0xD:
                dev->_outputDataRate = 800;
                break;
            case 0xC:
                dev->_outputDataRate = 400;
                break;
            case 0xB:
                dev->_outputDataRate = 200;
                break;
            case 0xA:
                dev->_outputDataRate = 100;
                break;
            case 0x9:
                dev->_outputDataRate = 50;
                break;
            case 0x8:
                dev->_outputDataRate = 25;
                break;
            default:
                Log(LOG_LEVEL_WARNING, "Invalid data rate value: 0x%X", data & 0xF);
                dev->_outputDataRate = 100;
                break;
            }
            break;
        case PowerSavingFeaturesControl:
            dev->regs[PowerSavingFeaturesControl] = data;
            dev->_isMeasurementEnabled = (data & 0x8) ? true : false;
            break;
        case DataFormatControl:
            dev->regs[DataFormatControl] = data;
            switch (data & 0x3) {
                case 0x0:
                    dev->range = G2;
                    break;
                case 0x1:
                    dev->range = G4;
                    break;
                case 0x2:
                    dev->range = G8;
                    break;
                case 0x3:
                    dev->range = G16;
                    break;
                default:
                    Log(LOG_LEVEL_WARNING, "Invalid range value: 0x%X", data & 0x3);
                    dev->range = G2;
                    break;
            }
            break;
        case FifoControl:
            dev->regs[FifoControl] = data;
            switch (data & 0xC0) {
                case 0x00:
                    dev->_fifoMode = BYPASS;
                    break;
                case 0x40:
                    dev->_fifoMode = FIFO;
                    init_queue( &(dev->samplesFifo) );
                    break;
                case 0x80:
                    dev->_fifoMode = STREAM;
                    break;
                case 0xC0:
                    dev->_fifoMode = TRIGGER;
                    break;
                default:
                    Log(LOG_LEVEL_WARNING, "Invalid FIFO mode value: 0x%X", data & 0x3);
                    dev->_fifoMode = BYPASS;
                    break;
            }
            break;
        default:
            Log(LOG_LEVEL_WARNING, "Writing to an unsupported or not-yet-implemented register: 0x%X - %d", dev->lastRegister, dev->lastRegister);
            return NACK;
            break;
    }
    return ACK;
}

// Read data from the device
uint8_t getReg(Sensor* dev) {
    uint8_t result;
    static bool x0_read_flag = true;
    static bool x1_read_flag = true;
    static bool y0_read_flag = true;
    static bool y1_read_flag = true;
    static bool z0_read_flag = true;
    static bool z1_read_flag = true;

    Log(LOG_LEVEL, "Reading from register 0x%X - %d", dev->lastRegister, dev->lastRegister);

    if( x0_read_flag && x1_read_flag && 
        y0_read_flag && y1_read_flag && 
        z0_read_flag && z1_read_flag && 
        (dev->lastRegister == Xdata0 || dev->lastRegister == Xdata1 || 
         dev->lastRegister == Ydata0 || dev->lastRegister == Ydata1 || 
         dev->lastRegister == Zdata0 || dev->lastRegister == Zdata1) ) 
    {
        x0_read_flag = false;
        x1_read_flag = false;
        y0_read_flag = false;
        y1_read_flag = false;
        z0_read_flag = false;
        z1_read_flag = false;    
        switch (dev->_fifoMode) {
            case BYPASS:
                // 1) read from file
                get_sample_from_file(dev, &(dev->currentSample) );
                // 2) calculate from equation      
                break;
            case FIFO:
                // if( !dequeue( &(dev->samplesFifo), &(dev->currentSample) ) ) {
                //     dev->currentSample.X = 0;
                //     dev->currentSample.Y = 0;
                //     dev->currentSample.Z = 0;
                //     Log(LOG_LEVEL, "Reading from Xdata0 register, but there are no samples");
                // }
                // break;
            default:
                Log(LOG_LEVEL_WARNING, "Reading from an unsupported or not-yet-implemented FIFO mode: %d", dev->_fifoMode);
                dev->currentSample.X = 0;
                dev->currentSample.Y = 0;
                dev->currentSample.Z = 0;  
                break;
        }
        dev->regs[Xdata0] = (uint8_t)(dev->currentSample.X & 0xFF);
        dev->regs[Xdata1] = (uint8_t)(dev->currentSample.X >> 8);
        dev->regs[Ydata0] = (uint8_t)(dev->currentSample.Y & 0xFF);
        dev->regs[Ydata1] = (uint8_t)(dev->currentSample.Y >> 8);
        dev->regs[Zdata0] = (uint8_t)(dev->currentSample.Z & 0xFF);
        dev->regs[Zdata1] = (uint8_t)(dev->currentSample.Z >> 8);    
        Log(LOG_LEVEL_NOISY, "Reading from data register, sample: [%d, %d, %d]", dev->currentSample.X, dev->currentSample.Y, dev->currentSample.Z);
    }

    switch (dev->lastRegister) {
        case DeviceID:     
        case Xoffset:
        case Yoffset:
        case Zoffset:
        case DataRateAndPowerModeControl:
        case PowerSavingFeaturesControl:
        case DataFormatControl:
        case FifoControl:
        case FifoStatus:
            result = dev->regs[dev->lastRegister];
            break;        
        case Xdata0:
            x0_read_flag = true;
            result = dev->regs[Xdata0];
            break;
        case Xdata1:
            x1_read_flag = true;
            result = dev->regs[Xdata1];
            break;
        case Ydata0:
            y0_read_flag = true;
            result = dev->regs[Ydata0];
            break;
        case Ydata1:
            y1_read_flag = true;
            result = dev->regs[Ydata1];
            break;
        case Zdata0:
            z0_read_flag = true;
            result = dev->regs[Zdata0];
            break;
        case Zdata1:
            z1_read_flag = true;
            result = dev->regs[Zdata1];
            break;            
        default:
            Log(LOG_LEVEL_WARNING, "Reading from an unsupported or not-yet-implemented register: 0x%X", dev->lastRegister);
            result = 0;
            break;
    }

    // PrettyPrintCollection equivalent
    // printf("Read result: [");
    // for(int i = 0; i < count; i++) {
    //     printf("0x%X", result[i]);
    //     if(i < count -1) printf(", ");
    // }
    // printf("]\n");

    return result;
}

// Parse samples from a file
void get_sample_from_file(Sensor* dev, Sample* sample) {
    char line[30];
    char* token;
    int x, y, z;
    static int lineNumber = 0;

    if( fgets(line, sizeof(line), dev->file) == NULL ) {
        Log(LOG_LEVEL_WARNING, "No more samples to read from file, rewinding file");
        rewind(dev->file);
        lineNumber = 0;
        fgets(line, sizeof(line), dev->file);
    }

    token = strtok(line, " ");
    if(token == NULL || sscanf(token, "%d", &x) != 1) {
        Log(LOG_LEVEL_WARNING, "Wrong data file format at line %d: %s", lineNumber, line);
        fclose(dev->file);
        return;
    }
    token = strtok(NULL, " ");
    if(token == NULL || sscanf(token, "%d", &y) != 1) {
        Log(LOG_LEVEL_WARNING, "Wrong data file format at line %d: %s", lineNumber, line);
        fclose(dev->file);
        return;
    }
    token = strtok(NULL, " ");
    if(token == NULL || sscanf(token, "%d", &z) != 1) {
        Log(LOG_LEVEL_WARNING, "Wrong data file format at line %d: %s", lineNumber, line);
        fclose(dev->file);
        return;
    }
    sample->X = x;
    sample->Y = y;
    sample->Z = z;
    return;
}

// Feed sample from an equation
void get_sample_from_equation(Sensor* dev, Sample* sample) {
    // TODO
    sample->X = 0;
    sample->Y = 0;
    sample->Z = 0;
    return;
}
