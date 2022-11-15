/*
 * STM32 - MA (Analog-to-digital converter) emulation.
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

#ifndef STM32_MA_H_
#define STM32_MA_H_

#include "qemu/osdep.h"

#include <hw/cortexm/peripheral.h>
#include <hw/cortexm/stm32/capabilities.h>

// ----------------------------------------------------------------------------

#define DEVICE_PATH_STM32_MA DEVICE_PATH_STM32 "MA"

// ----------------------------------------------------------------------------

// Note: the "port-index" property has type "int".
typedef enum {
    // TODO: keep this list in ascending order.
    STM32_PORT_MA1,
    STM32_PORT_MA2,
    STM32_PORT_MA3,
    STM32_PORT_MA_UNDEFINED = 0xFF,
} stm32_ma_index_t;

// ----------------------------------------------------------------------------

#define TYPE_STM32_MA TYPE_STM32_PREFIX "ma" TYPE_PERIPHERAL_SUFFIX

// ----------------------------------------------------------------------------

// Parent definitions.
#define TYPE_STM32_MA_PARENT TYPE_PERIPHERAL
typedef PeripheralClass STM32MAParentClass;
typedef PeripheralState STM32MAParentState;

// ----------------------------------------------------------------------------

// Class definitions.
#define STM32_MA_GET_CLASS(obj) \
    OBJECT_GET_CLASS(STM32MAClass, (obj), TYPE_STM32_MA)
#define STM32_MA_CLASS(klass) \
    OBJECT_CLASS_CHECK(STM32MAClass, (klass), TYPE_STM32_MA)

typedef struct {
    // private: 
    STM32MAParentClass parent_class;
    // public: 

    // None, so far.
} STM32MAClass;

// ----------------------------------------------------------------------------

// Instance definitions.
#define STM32_MA_STATE(obj) \
    OBJECT_CHECK(STM32MAState, (obj), TYPE_STM32_MA)

typedef struct {
    // private:
    STM32MAParentState parent_obj;
    // public:

    const STM32Capabilities *capabilities;

    // TODO: remove this if the peripheral is always enabled.
    // Points to the bitfield that enables the peripheral.
    Object *enabling_bit;

    // Remove it if there is only one port
    stm32_ma_index_t port_index;

    union {
      // ----- 8< ----- 8< -----  8< ----- 8< ----- 8< ----- 8< ----- 8< -----

      // DO NOT REMOVE FIELDS! Automatically generated!
      // Merge fields from different family members.
      struct {
        // F4 MA (Analog-to-digital converter) registers.
        struct { 
          Object *ma_cr;         // 0x0 (Status register) 
          Object *ma_input;   // 0x4 (Control register 1) 
          Object *ma_weight;  // 0x8 (Control register 2) 
          Object *ma_output;  // 0xC (Sample time register 1) 
        } reg;

        struct { 
          
          // CR (Control register) bitfields.
          struct { 
            Object *acc_en; // [0:0] Analog watchdog flag 
          } ma_cr; 
          
          // CR1 (Control register 1) bitfields.
          struct { 
            Object *input; // [0:4] Analog watchdog channel select bits 
          } ma_input; 
          
          // CR2 (Control register 2) bitfields.
          struct { 
            Object *weight; // [0:0] A/D Converter ON / OFF 
          } ma_weight; 
          
          // SMPR1 (Sample time register 1) bitfields.
          struct { 
            Object *output; // [0:31] Sample time bits  
          } ma_output; 
          
        } fld;
      } f4;

      // ----- 8< ----- 8< -----  8< ----- 8< ----- 8< ----- 8< ----- 8< -----
    } u;

} STM32MAState;

// ----------------------------------------------------------------------------

#endif /* STM32_MA_H_ */
