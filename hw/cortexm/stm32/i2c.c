/*
 * STM32 - I2C (Inter-integrated circuit) emulation.
 *
 * Copyright (c) 2016 Liviu Ionescu.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <hw/cortexm/stm32/i2c.h>
#include <hw/cortexm/stm32/mcu.h>
#include <hw/cortexm/helper.h>
#include <hw/cortexm/svd.h>

#define DEBUG

typedef enum {
    ST_IDLE,
    ST_START,
    ST_DEV_ADDR,
    ST_REG_ADDR,
    ST_WR_DATA,
    ST_RD_DATA,
    ST_STOP,
    ST_NACK = 0xFF,
} i2c_fsm_t;

typedef enum {
    OP_WRITE = 0,  
    OP_READ = 1,
} i2c_op_t;

// ----- Generated code -------------------------------------------------------
//
// ----- 8< ----- 8< -----  8< ----- 8< ----- 8< ----- 8< ----- 8< -----

// DO NOT EDIT! Automatically generated!
static void stm32f40x_i2c_create_objects(Object *obj, JSON_Object *svd, const char *name)
{
    STM32I2CState *state = STM32_I2C_STATE(obj);

    JSON_Object *periph = svd_get_peripheral_by_name(svd, name);
    svd_add_peripheral_properties_and_children(obj, periph, svd);

    // Registers. 
    state->u.f4.reg.cr1 = cm_object_get_child_by_name(obj, "CR1");
    state->u.f4.reg.cr2 = cm_object_get_child_by_name(obj, "CR2");
    state->u.f4.reg.oar1 = cm_object_get_child_by_name(obj, "OAR1");
    state->u.f4.reg.oar2 = cm_object_get_child_by_name(obj, "OAR2");
    state->u.f4.reg.dr = cm_object_get_child_by_name(obj, "DR");
    state->u.f4.reg.sr1 = cm_object_get_child_by_name(obj, "SR1");
    state->u.f4.reg.sr2 = cm_object_get_child_by_name(obj, "SR2");
    state->u.f4.reg.ccr = cm_object_get_child_by_name(obj, "CCR");
    state->u.f4.reg.trise = cm_object_get_child_by_name(obj, "TRISE");
    
    
    // CR1 bitfields.
    state->u.f4.fld.cr1.pe = cm_object_get_child_by_name(state->u.f4.reg.cr1, "PE"); 
    state->u.f4.fld.cr1.smbus = cm_object_get_child_by_name(state->u.f4.reg.cr1, "SMBUS"); 
    state->u.f4.fld.cr1.smbtype = cm_object_get_child_by_name(state->u.f4.reg.cr1, "SMBTYPE"); 
    state->u.f4.fld.cr1.enarp = cm_object_get_child_by_name(state->u.f4.reg.cr1, "ENARP"); 
    state->u.f4.fld.cr1.enpec = cm_object_get_child_by_name(state->u.f4.reg.cr1, "ENPEC"); 
    state->u.f4.fld.cr1.engc = cm_object_get_child_by_name(state->u.f4.reg.cr1, "ENGC"); 
    state->u.f4.fld.cr1.nostretch = cm_object_get_child_by_name(state->u.f4.reg.cr1, "NOSTRETCH"); 
    state->u.f4.fld.cr1.start = cm_object_get_child_by_name(state->u.f4.reg.cr1, "START"); 
    state->u.f4.fld.cr1.stop = cm_object_get_child_by_name(state->u.f4.reg.cr1, "STOP"); 
    state->u.f4.fld.cr1.ack = cm_object_get_child_by_name(state->u.f4.reg.cr1, "ACK"); 
    state->u.f4.fld.cr1.pos = cm_object_get_child_by_name(state->u.f4.reg.cr1, "POS"); 
    state->u.f4.fld.cr1.pec = cm_object_get_child_by_name(state->u.f4.reg.cr1, "PEC"); 
    state->u.f4.fld.cr1.alert = cm_object_get_child_by_name(state->u.f4.reg.cr1, "ALERT"); 
    state->u.f4.fld.cr1.swrst = cm_object_get_child_by_name(state->u.f4.reg.cr1, "SWRST");  
    
    // CR2 bitfields.
    state->u.f4.fld.cr2.freq = cm_object_get_child_by_name(state->u.f4.reg.cr2, "FREQ"); 
    state->u.f4.fld.cr2.iterren = cm_object_get_child_by_name(state->u.f4.reg.cr2, "ITERREN"); 
    state->u.f4.fld.cr2.itevten = cm_object_get_child_by_name(state->u.f4.reg.cr2, "ITEVTEN"); 
    state->u.f4.fld.cr2.itbufen = cm_object_get_child_by_name(state->u.f4.reg.cr2, "ITBUFEN"); 
    state->u.f4.fld.cr2.dmaen = cm_object_get_child_by_name(state->u.f4.reg.cr2, "DMAEN"); 
    state->u.f4.fld.cr2.last = cm_object_get_child_by_name(state->u.f4.reg.cr2, "LAST");  
    
    // OAR1 bitfields.
    state->u.f4.fld.oar1.add0 = cm_object_get_child_by_name(state->u.f4.reg.oar1, "ADD0"); 
    state->u.f4.fld.oar1.add7 = cm_object_get_child_by_name(state->u.f4.reg.oar1, "ADD7"); 
    state->u.f4.fld.oar1.add10 = cm_object_get_child_by_name(state->u.f4.reg.oar1, "ADD10"); 
    state->u.f4.fld.oar1.addmode = cm_object_get_child_by_name(state->u.f4.reg.oar1, "ADDMODE");  
    
    // OAR2 bitfields.
    state->u.f4.fld.oar2.endual = cm_object_get_child_by_name(state->u.f4.reg.oar2, "ENDUAL"); 
    state->u.f4.fld.oar2.add2 = cm_object_get_child_by_name(state->u.f4.reg.oar2, "ADD2");  
    
    // DR bitfields.
    state->u.f4.fld.dr.dr = cm_object_get_child_by_name(state->u.f4.reg.dr, "DR");  
    
    // SR1 bitfields.
    state->u.f4.fld.sr1.sb = cm_object_get_child_by_name(state->u.f4.reg.sr1, "SB"); 
    state->u.f4.fld.sr1.addr = cm_object_get_child_by_name(state->u.f4.reg.sr1, "ADDR"); 
    state->u.f4.fld.sr1.btf = cm_object_get_child_by_name(state->u.f4.reg.sr1, "BTF"); 
    state->u.f4.fld.sr1.add10 = cm_object_get_child_by_name(state->u.f4.reg.sr1, "ADD10"); 
    state->u.f4.fld.sr1.stopf = cm_object_get_child_by_name(state->u.f4.reg.sr1, "STOPF"); 
    state->u.f4.fld.sr1.rxne = cm_object_get_child_by_name(state->u.f4.reg.sr1, "RxNE"); 
    state->u.f4.fld.sr1.txe = cm_object_get_child_by_name(state->u.f4.reg.sr1, "TxE"); 
    state->u.f4.fld.sr1.berr = cm_object_get_child_by_name(state->u.f4.reg.sr1, "BERR"); 
    state->u.f4.fld.sr1.arlo = cm_object_get_child_by_name(state->u.f4.reg.sr1, "ARLO"); 
    state->u.f4.fld.sr1.af = cm_object_get_child_by_name(state->u.f4.reg.sr1, "AF"); 
    state->u.f4.fld.sr1.ovr = cm_object_get_child_by_name(state->u.f4.reg.sr1, "OVR"); 
    state->u.f4.fld.sr1.pecerr = cm_object_get_child_by_name(state->u.f4.reg.sr1, "PECERR"); 
    state->u.f4.fld.sr1.timeout = cm_object_get_child_by_name(state->u.f4.reg.sr1, "TIMEOUT"); 
    state->u.f4.fld.sr1.smbalert = cm_object_get_child_by_name(state->u.f4.reg.sr1, "SMBALERT");  
    
    // SR2 bitfields.
    state->u.f4.fld.sr2.msl = cm_object_get_child_by_name(state->u.f4.reg.sr2, "MSL"); 
    state->u.f4.fld.sr2.busy = cm_object_get_child_by_name(state->u.f4.reg.sr2, "BUSY"); 
    state->u.f4.fld.sr2.tra = cm_object_get_child_by_name(state->u.f4.reg.sr2, "TRA"); 
    state->u.f4.fld.sr2.gencall = cm_object_get_child_by_name(state->u.f4.reg.sr2, "GENCALL"); 
    state->u.f4.fld.sr2.smbdefault = cm_object_get_child_by_name(state->u.f4.reg.sr2, "SMBDEFAULT"); 
    state->u.f4.fld.sr2.smbhost = cm_object_get_child_by_name(state->u.f4.reg.sr2, "SMBHOST"); 
    state->u.f4.fld.sr2.dualf = cm_object_get_child_by_name(state->u.f4.reg.sr2, "DUALF"); 
    state->u.f4.fld.sr2.pec = cm_object_get_child_by_name(state->u.f4.reg.sr2, "PEC");  
    
    // CCR bitfields.
    state->u.f4.fld.ccr.ccr = cm_object_get_child_by_name(state->u.f4.reg.ccr, "CCR"); 
    state->u.f4.fld.ccr.duty = cm_object_get_child_by_name(state->u.f4.reg.ccr, "DUTY"); 
    state->u.f4.fld.ccr.f_s = cm_object_get_child_by_name(state->u.f4.reg.ccr, "F_S");  
    
    // TRISE bitfields.
    state->u.f4.fld.trise.trise = cm_object_get_child_by_name(state->u.f4.reg.trise, "TRISE");  
}

// ----- 8< ----- 8< -----  8< ----- 8< ----- 8< ----- 8< ----- 8< -----

// ----- Private --------------------------------------------------------------

#if 0
static peripheral_register_t stm32_i2c_xxx_pre_write_callback(Object *reg,
        Object *periph, uint32_t addr, uint32_t offset, unsigned size,
        peripheral_register_t value, peripheral_register_t full_value)
{
    STM32I2CState *state = STM32_I2C_STATE(periph);

    peripheral_register_t prev_value = peripheral_register_get_raw_prev_value(reg);

    // TODO: Add code to adjust the value (like applying some masks,
    // for example prevent setting interrupts not enabled).
    // Also process cleared/set by write 1/0 bits.
    // The returned value will be stored in the register value.

    return full_value;
}

static void stm32_i2c_xxx_post_write_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size,
        peripheral_register_t value, peripheral_register_t full_value)
{
    STM32I2CState *state = STM32_I2C_STATE(periph);

    peripheral_register_t prev_value = peripheral_register_get_raw_prev_value(reg);
    // The new register value is full_value, the old one is prev_value.

    // TODO: Add code to send the value to the consumer.
}

static peripheral_register_t stm32_i2c_xxx_pre_read_callback(Object *reg,
        Object *periph, uint32_t addr, uint32_t offset, unsigned size)
{
    STM32I2CState *state = STM32_I2C_STATE(periph);

    peripheral_register_t value = 0;

    // Add code to get the value from the producer, and return it.

    // This value, possibly masked, will be stored in the register
    // and returned when the register is read.
    return value;
}

static void stm32_i2c_xxx_post_read_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size)
{
    STM32I2CState *state = STM32_I2C_STATE(periph);

    peripheral_register_t value = peripheral_register_get_raw_value(reg);

    // TODO: add code to perform the post read actions, like clearing some bits.
}
#endif

i2c_fsm_t i2c_fsm = ST_IDLE;
i2c_op_t  i2c_op = OP_WRITE;

static void stm32_i2c_dr_post_read_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size)
{
    STM32I2CState *state = STM32_I2C_STATE(periph);

    peripheral_register_t value = peripheral_register_get_raw_value(reg);

    switch( i2c_fsm ) {
        case ST_RD_DATA:
            peripheral_register_and_raw_value(state->u.f4.reg.dr, 0);
#ifdef DEBUG
            uint32_t dr = peripheral_register_get_raw_value(state->u.f4.reg.dr);
            printf("[DBG] clear I2C_DR = 0x%08x \n", dr);
#endif        
            break;
    }
}

static void stm32_i2c_dr_post_write_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size,
        peripheral_register_t value, peripheral_register_t full_value)
{
    STM32I2CState *state = STM32_I2C_STATE(periph);

    peripheral_register_t prev_value = peripheral_register_get_raw_prev_value(reg);
    // The new register value is full_value, the old one is prev_value.

#ifdef DEBUG
    puts("\n\n[DBG] stm32_i2c_dr_post_write_callback ");
#endif  

    usleep(I2C_SLEEP_mDELAY);
    switch( i2c_fsm ) {
        case ST_START:
            if( full_value != 0 ) {
                printf("[INFO] I2C Device Address = 0x%2X \n", full_value>>1);
                printf("[INFO] Next state is ST_DEV_ADDR \n");
                i2c_fsm = ST_DEV_ADDR;
            }
            break;
        case ST_DEV_ADDR:
            if( full_value != 0 ) {
                printf("[INFO] I2C Register = 0x%2X \n", full_value);
                printf("[INFO] Next state is ST_REG_ADDR \n");
                i2c_fsm = ST_REG_ADDR;
            }
            break;
        case ST_REG_ADDR:
            if( full_value != 0 ) {
                printf("[INFO] I2C Write Data = 0x%2X \n", full_value);
                printf("[INFO] Next state is ST_WR_DATA \n");
                i2c_fsm = ST_WR_DATA;
            } 
            break;            
        default:
            break;
    }

}

static void stm32_i2c_cr1_post_write_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size,
        peripheral_register_t value, peripheral_register_t full_value)
{
    STM32I2CState *state = STM32_I2C_STATE(periph);

    peripheral_register_t prev_value = peripheral_register_get_raw_prev_value(reg);
    // The new register value is full_value, the old one is prev_value.

#ifdef DEBUG
    puts("\n\n[DBG] stm32_i2c_cr1_post_write_callback ");
#endif  

    uint32_t sr1 = peripheral_register_get_raw_value(state->u.f4.reg.sr1);

    usleep(I2C_SLEEP_mDELAY);
    switch( i2c_fsm ) {
        case ST_IDLE:
            if( full_value & I2C_CR1_START ) {
                peripheral_register_or_raw_value(state->u.f4.reg.sr1, I2C_SR1_SB);
                sr1 = peripheral_register_get_raw_value(state->u.f4.reg.sr1);
                printf("[DBG] write I2C_SR1_SB = 0x%08x \n", sr1);

                printf("[INFO] Next state is ST_START \n");
                i2c_fsm = ST_START;
            }
            break;
        case ST_WR_DATA:
            if( full_value & I2C_CR1_STOP ) {
                printf("[INFO] Next state is ST_STOP \n");
                i2c_fsm = ST_STOP;
            }
            break;
        case ST_REG_ADDR:
            if( full_value & I2C_CR1_START ) {
                printf("[INFO] I2C Start Again for Receive \n");

                peripheral_register_or_raw_value(state->u.f4.reg.sr1, I2C_SR1_SB);
                sr1 = peripheral_register_get_raw_value(state->u.f4.reg.sr1);
                printf("[DBG] write I2C_SR1_SB = 0x%08x \n", sr1);

                printf("[INFO] Next state is ST_START (dummy) \n");
                i2c_fsm = ST_START;
            }
            break;
        case ST_RD_DATA:
            if( full_value & I2C_CR1_STOP ) {
                printf("[INFO] Next state is ST_STOP \n");
                i2c_fsm = ST_STOP;
            }
            break;
        default:
            break;
    }

}

static void stm32_i2c_sr1_post_read_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size)
{
    STM32I2CState *state = STM32_I2C_STATE(periph);

    peripheral_register_t value = peripheral_register_get_raw_value(reg);

    uint32_t sr1 = peripheral_register_get_raw_value(state->u.f4.reg.sr1);
    uint32_t dr = peripheral_register_get_raw_value(state->u.f4.reg.dr);

#ifdef DEBUG
    puts("\n\n[DBG] stm32_i2c_sr1_post_read_callback ");
#endif 

    // TODO: add code to perform the post read actions, like clearing some bits.
    usleep(I2C_SLEEP_mDELAY);
    switch( i2c_fsm ) {
        case ST_START:
            peripheral_register_and_raw_value(state->u.f4.reg.sr1, ~I2C_SR1_SB);
            sr1 = peripheral_register_get_raw_value(state->u.f4.reg.sr1);
#ifdef DEBUG
            printf("[DBG] clear I2C_SR1_SB = 0x%08x \n", sr1);
#endif
            break;
        case ST_DEV_ADDR:
            peripheral_register_and_raw_value(state->u.f4.reg.sr1, ~I2C_SR1_ADDR);
#ifdef DEBUG
            sr1 = peripheral_register_get_raw_value(state->u.f4.reg.sr1);
            printf("[DBG] clear I2C_SR1_ADDR = 0x%08x \n", sr1);
#endif
            if( i2c_op == OP_READ ) {
                printf("[INFO] Next state is ST_RD_DATA \n");
                i2c_fsm = ST_RD_DATA;
            }
            break;        
        case ST_REG_ADDR:
            peripheral_register_and_raw_value(state->u.f4.reg.sr1, ~I2C_SR1_BTF);
#ifdef DEBUG
            sr1 = peripheral_register_get_raw_value(state->u.f4.reg.sr1);
            printf("[DBG] clear I2C_SR1_BTF = 0x%08x \n", sr1);
#endif
            break;      
        case ST_WR_DATA:
            peripheral_register_and_raw_value(state->u.f4.reg.sr1, ~I2C_SR1_BTF);
#ifdef DEBUG
            sr1 = peripheral_register_get_raw_value(state->u.f4.reg.sr1);
            printf("[DBG] clear I2C_SR1_BTF = 0x%08x \n", sr1);
#endif
            break;
        case ST_RD_DATA:
            peripheral_register_and_raw_value(state->u.f4.reg.sr1, ~I2C_SR1_RXNE);
#ifdef DEBUG
            sr1 = peripheral_register_get_raw_value(state->u.f4.reg.sr1);
            printf("[DBG] clear I2C_SR1_RXNE = 0x%08x \n", sr1);
#endif        
            break;
        default:
            break;
    }
}

static peripheral_register_t stm32_i2c_sr1_pre_read_callback(Object *reg,
        Object *periph, uint32_t addr, uint32_t offset, unsigned size)
{
    STM32I2CState *state = STM32_I2C_STATE(periph);

    peripheral_register_t value = 0;

    // Add code to get the value from the producer, and return it.
    uint32_t sr1 = peripheral_register_get_raw_value(state->u.f4.reg.sr1);
    uint32_t sr2 = peripheral_register_get_raw_value(state->u.f4.reg.sr2);
    uint32_t cr1 = peripheral_register_get_raw_value(state->u.f4.reg.cr1);
    uint32_t dr = peripheral_register_get_raw_value(state->u.f4.reg.dr);

#ifdef DEBUG
    puts("\n\n[DBG] stm32_i2c_sr1_pre_read_callback ");
    // printf("[DBG] I2C_SR1  = 0x%08x \n", sr1);
    // printf("[DBG] I2C_CR1  = 0x%08x \n", cr1);
    // printf("[DBG] I2C_DR  = 0x%08x \n", dr);
    // printf("[DBG] i2c_fsm = %d \n", i2c_fsm);
#endif    


    // jskwon
    switch( i2c_fsm ) {
        case ST_START:
#ifdef DEBUG
            printf("[DBG] Current state is ST_START \n");
            printf("[DBG] I2C_CR1 = 0x%08x \n", cr1);
#endif
            if( cr1 & I2C_CR1_START ) {
                /*
                    Sensor API
                    -> genStart();
                */
                usleep(I2C_SLEEP_mDELAY);

                peripheral_register_and_raw_value(state->u.f4.reg.cr1, ~I2C_CR1_START);
#ifdef DEBUG
                cr1 = peripheral_register_get_raw_value(state->u.f4.reg.cr1);
                printf("[DBG] clear I2C_CR1_START = 0x%08x \n", cr1);
#endif 
                return sr1;
            }
            break;
        case ST_DEV_ADDR:
#ifdef DEBUG
            printf("[DBG] Current state is ST_DEV_ADDR \n");
            printf("[DBG] I2C_DR  = 0x%08x \n", dr);
#endif
            if( (dr != 0) ) {
                printf("[INFO] I2C Device Address = 0x%2X \n", dr>>1);

                if( dr & 1 ) {  // Read
                    i2c_op = OP_READ;
                    printf("[INFO] I2C Read Operation \n");
                } else {        // Write
                    i2c_op = OP_WRITE;
                    printf("[INFO] I2C Write Operation \n");
                }

                /*
                    Sensor API
                    -> devAddr();
                */
                usleep(I2C_SLEEP_mDELAY);

                // if I2C_DR is not empty -> clear
                peripheral_register_and_raw_value(state->u.f4.reg.dr, 0);
#ifdef DEBUG
                dr = peripheral_register_get_raw_value(state->u.f4.reg.dr);
                printf("[DBG] clear I2C_DR = 0x%08x \n", dr);
#endif
                return sr1 | I2C_SR1_ADDR;
            }
            break;
        case ST_REG_ADDR:
#ifdef DEBUG
            printf("[DBG] Current state is ST_REG_ADDR \n");
            printf("[DBG] I2C_DR  = 0x%08x \n", dr);
#endif
            if( (dr != 0) ) {
                printf("[INFO] I2C Register = 0x%2X \n", dr);
                
                /*
                    Sensor API
                    -> regAddr();
                */
                usleep(I2C_SLEEP_mDELAY);

                // if I2C_DR is not empty -> clear
                peripheral_register_and_raw_value(state->u.f4.reg.dr, 0);
#ifdef DEBUG
                dr = peripheral_register_get_raw_value(state->u.f4.reg.dr);
                printf("[DBG] clear I2C_DR = 0x%08x \n", dr);
#endif
                return sr1 | I2C_SR1_BTF;
            }
            break;
        case ST_WR_DATA:
#ifdef DEBUG
            printf("[DBG] Current state is ST_WR_DATA \n");
            printf("[DBG] I2C_DR  = 0x%08x \n", dr);
#endif
            if( (dr != 0) ) {
                printf("[INFO] I2C Write Data = 0x%2X \n", dr);
                
                /*
                    Sensor API
                    -> setReg();
                */
                usleep(I2C_SLEEP_mDELAY);

                // if I2C_DR is not empty -> clear
                peripheral_register_and_raw_value(state->u.f4.reg.dr, 0);
#ifdef DEBUG
                dr = peripheral_register_get_raw_value(state->u.f4.reg.dr);
                printf("[DBG] clear I2C_DR = 0x%08x \n", dr);
#endif
                return sr1 | I2C_SR1_BTF;
            }
            break;
        case ST_RD_DATA:
            if( i2c_op == OP_READ ) {
                /*
                    Sensor API
                    -> getReg();
                    peripheral_register_and_raw_value(state->u.f4.reg.dr, getReg());
                */
                peripheral_register_or_raw_value(state->u.f4.reg.dr, 'a');
#ifdef DEBUG
                dr = peripheral_register_get_raw_value(state->u.f4.reg.dr);
                printf("[DBG] Received I2C_DR = 0x%08x \n", dr);
#endif

                usleep(I2C_SLEEP_mDELAY);
                return sr1 | I2C_SR1_RXNE;
            }        
            break;
        default:
            break;
    }


    // This value, possibly masked, will be stored in the register
    // and returned when the register is read.
    return sr1;
}

static void stm32_i2c_sr2_post_read_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size)
{
    STM32I2CState *state = STM32_I2C_STATE(periph);
    peripheral_register_t value = peripheral_register_get_raw_value(reg);

#ifdef DEBUG
    puts("\n\n[DBG] stm32_i2c_sr2_post_read_callback ");
#endif 
    uint32_t sr2 = peripheral_register_get_raw_value(state->u.f4.reg.sr2);

    usleep(I2C_SLEEP_mDELAY);
    switch( i2c_fsm ) {
        case ST_STOP:
            peripheral_register_and_raw_value(state->u.f4.reg.sr2, ~I2C_SR2_BUSY);
#ifdef DEBUG
            sr2 = peripheral_register_get_raw_value(state->u.f4.reg.sr2);
            printf("[DBG] clear I2C_SR2_BUSY = 0x%08x \n", sr2);
#endif
            printf("[INFO] Next state is ST_IDLE \n");
            i2c_fsm = ST_IDLE;
            break;
        default:
            break;
    }
}

static peripheral_register_t stm32_i2c_sr2_pre_read_callback(Object *reg,
        Object *periph, uint32_t addr, uint32_t offset, unsigned size)
{
    STM32I2CState *state = STM32_I2C_STATE(periph);
    peripheral_register_t value = 0;

    // Add code to get the value from the producer, and return it.
    uint32_t cr1 = peripheral_register_get_raw_value(state->u.f4.reg.cr1);
    uint32_t sr2 = peripheral_register_get_raw_value(state->u.f4.reg.sr2);

#ifdef DEBUG
    puts("\n\n[DBG] stm32_i2c_sr2_pre_read_callback ");
#endif 

    switch( i2c_fsm ) {
        case ST_START:
        case ST_DEV_ADDR:
        case ST_REG_ADDR:
        case ST_WR_DATA:
        case ST_RD_DATA:
            return sr2 | I2C_SR2_BUSY;
        case ST_STOP:
#ifdef DEBUG
            printf("[DBG] Current state is ST_STOP \n");
            printf("[DBG] I2C_CR1 = 0x%08x \n", cr1);
#endif
            if( cr1 & I2C_CR1_STOP ) {
                /*
                    Sensor API
                    -> genStop();
                */
                usleep(I2C_SLEEP_mDELAY);

                peripheral_register_and_raw_value(state->u.f4.reg.cr1, ~I2C_CR1_STOP);
#ifdef DEBUG
                cr1 = peripheral_register_get_raw_value(state->u.f4.reg.cr1);
                printf("[DBG] clear I2C_CR1_STOP = 0x%08x \n", cr1);
#endif 
                return sr2;
            }
            break;
        default:
            return sr2;
    }    

    // This value, possibly masked, will be stored in the register
    // and returned when the register is read.
    return sr2;
}

// ----------------------------------------------------------------------------

// jskwon
Object* stm32_i2c_create(Object *parent, stm32_i2c_index_t index)
{
    if ((int) index >= STM32_PORT_I2C_UNDEFINED) {
        hw_error("Cannot assign I2C %d: QEMU supports only %d ports\n",
                1 + index - STM32_PORT_I2C1, STM32_PORT_I2C_UNDEFINED);
    }

    char child_name[10];
    snprintf(child_name, sizeof(child_name) - 1, "I2C%d",
            1 + index - STM32_PORT_I2C1);
    // Passing a local string is ok.
    Object *i2c = cm_object_new(parent, child_name,
    TYPE_STM32_I2C);

    object_property_set_int(i2c, index, "port-index", NULL);

    cm_object_realize(i2c);

    return i2c;
}

// TODO: remove this if the peripheral is always enabled.
static bool stm32_i2c_is_enabled(Object *obj)
{
    STM32I2CState *state = STM32_I2C_STATE(obj);

    if (register_bitfield_is_non_zero(state->enabling_bit)) {
        return true; // Positive logic, bit == 1 means enabled.
    }

    // Not enabled
    return false;
}

static void stm32_i2c_instance_init_callback(Object *obj)
{
    qemu_log_function_name();

    STM32I2CState *state = STM32_I2C_STATE(obj);

    // Capabilities are not yet available.

    cm_object_property_add_int(obj, "port-index",
            (const int *) &state->port_index);
    state->port_index = STM32_PORT_I2C_UNDEFINED;

    // TODO: remove this if the peripheral is always enabled.
    state->enabling_bit = NULL;
    
    // TODO: Add code to initialise all members.
}

static void stm32_i2c_realize_callback(DeviceState *dev, Error **errp)
{
    qemu_log_function_name();

    // Call parent realize().
    if (!cm_device_parent_realize(dev, errp, TYPE_STM32_I2C)) {
        return;
    }

    STM32MCUState *mcu = stm32_mcu_get();
    CortexMState *cm_state = CORTEXM_MCU_STATE(mcu);

    STM32I2CState *state = STM32_I2C_STATE(dev);
    // First thing first: get capabilities from MCU, needed everywhere.
    state->capabilities = mcu->capabilities;

    // Also keep a local pointer, to access them easier.
    const STM32Capabilities *capabilities = state->capabilities;
    assert(capabilities != NULL);

    Object *obj = OBJECT(dev);

    // const char *periph_name = "I2C1";
    char periph_name[10];
    snprintf(periph_name, sizeof(periph_name) - 1, "I2C%d",
            1 + state->port_index - STM32_PORT_I2C1);    

    svd_set_peripheral_address_block(cm_state->svd_json, periph_name, obj);
    peripheral_create_memory_region(obj);

    // jskwon
    cm_object_property_set_int(obj, 4, "register-size-bytes");
    cm_object_property_set_bool(obj, true, "is-little-endian");


    // TODO: remove this if the peripheral is always enabled.
    char enabling_bit_name[STM32_RCC_SIZEOF_ENABLING_BITFIELD];

    switch (capabilities->family) {
    case STM32_FAMILY_F4:

        if (capabilities->f4.is_40x ) {

            stm32f40x_i2c_create_objects(obj, cm_state->svd_json, periph_name);

            // TODO: add actions.
            // cm_object_property_set_str(state->u.f4.fld.xxx.fff, "GGG", "follows");
            // cm_object_property_set_str(state->u.f4.fld.xxx.fff, "GGG", "cleared-by");


            // state->u.f4.reg.ccr;
            // state->u.f4.reg.cr1;
            // state->u.f4.reg.cr2;
            // state->u.f4.reg.dr;
            // state->u.f4.reg.oar1;
            // state->u.f4.reg.oar2;
            // state->u.f4.reg.sr1;
            // state->u.f4.reg.sr2;
            // state->u.f4.reg.trise;



            // TODO: add callbacks.
            // peripheral_register_set_pre_read(state->f4.reg.xxx, &stm32_i2c_xxx_pre_read_callback);
            // peripheral_register_set_post_read(state->f4.reg.xxx, &stm32_i2c_xxx_post_read_callback);
            // peripheral_register_set_pre_read(state->f4.reg.xxx, &stm32_i2c_xxx_pret_read_callback);

            peripheral_register_set_post_write(state->u.f4.reg.cr1, 
                &stm32_i2c_cr1_post_write_callback);

            peripheral_register_set_post_write(state->u.f4.reg.dr, 
                &stm32_i2c_dr_post_write_callback);
            peripheral_register_set_post_read(state->u.f4.reg.dr, 
                &stm32_i2c_dr_post_read_callback);                

            peripheral_register_set_pre_read(state->u.f4.reg.sr1, 
                &stm32_i2c_sr1_pre_read_callback);
            peripheral_register_set_post_read(state->u.f4.reg.sr1, 
                &stm32_i2c_sr1_post_read_callback);

            peripheral_register_set_pre_read(state->u.f4.reg.sr2,
                &stm32_i2c_sr2_pre_read_callback);                
            peripheral_register_set_post_read(state->u.f4.reg.sr2, 
                &stm32_i2c_sr2_post_read_callback);
               

            // TODO: add interrupts.

            // TODO: remove this if the peripheral is always enabled.
            snprintf(enabling_bit_name, sizeof(enabling_bit_name) - 1,
                DEVICE_PATH_STM32_RCC "/APB1ENR/I2C%dEN",
                1 + state->port_index - STM32_PORT_I2C1);






            // void *handle = dlopen("/home/jskwon/HDD/PROJECT/2018-09-08_JSKWON/02_research_note/2025/2025-01-02_QT6/02_SRC/02_open_qt6_dll_template/lib2025-01-02_interface_config.so", RTLD_LAZY);
            // if (!handle) {
            //     fprintf(stderr, "Error: %s\n", dlerror());
            //     return 1;
            // }

            // void (*my_function)();
            // *(void **)(&my_function) = dlsym(handle, "main");
            // char *error = dlerror();
            // if (error != NULL) {
            //     fprintf(stderr, "Error: %s\n", error);
            //     dlclose(handle);
            // }

            // my_function();

            // dlclose(handle);



        } else {
            assert(false);
        }

        break;

    default:
        assert(false);
        break;
    }

    // TODO: remove this if the peripheral is always enabled.
    state->enabling_bit = OBJECT(cm_device_by_name(enabling_bit_name));

    peripheral_prepare_registers(obj);

    printf("[INFO] I2C ENTER \n");
}

static void stm32_i2c_reset_callback(DeviceState *dev)
{
    qemu_log_function_name();

    // Call parent reset(); this will reset all children registers.
    cm_device_parent_reset(dev, TYPE_STM32_I2C);
}

static void stm32_i2c_class_init_callback(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = stm32_i2c_reset_callback;
    dc->realize = stm32_i2c_realize_callback;

    // TODO: remove this if the peripheral is always enabled.
    PeripheralClass *per_class = PERIPHERAL_CLASS(klass);
    per_class->is_enabled = stm32_i2c_is_enabled;
}

static const TypeInfo stm32_i2c_type_info = {
    .name = TYPE_STM32_I2C,
    .parent = TYPE_STM32_I2C_PARENT,
    .instance_init = stm32_i2c_instance_init_callback,
    .instance_size = sizeof(STM32I2CState),
    .class_init = stm32_i2c_class_init_callback,
    .class_size = sizeof(STM32I2CClass) };

static void stm32_i2c_register_types(void)
{
    type_register_static(&stm32_i2c_type_info);
}

type_init(stm32_i2c_register_types);

// ----------------------------------------------------------------------------
