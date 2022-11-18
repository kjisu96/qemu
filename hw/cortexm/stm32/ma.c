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

#include <hw/cortexm/stm32/ma.h>
#include <hw/cortexm/stm32/mcu.h>
#include <hw/cortexm/helper.h>
#include <hw/cortexm/svd.h>

// ----- Generated code -------------------------------------------------------
//
// ----- 8< ----- 8< -----  8< ----- 8< ----- 8< ----- 8< ----- 8< -----

// DO NOT EDIT! Automatically generated!
static void stm32f40x_ma_create_objects(Object *obj, JSON_Object *svd, const char *name)
{
    STM32MAState *state = STM32_MA_STATE(obj);

    JSON_Object *periph = svd_get_peripheral_by_name(svd, name);
    svd_add_peripheral_properties_and_children(obj, periph, svd);

    // Registers. 
    state->u.f4.reg.ma_cr = cm_object_get_child_by_name(obj, "CR");
    state->u.f4.reg.ma_input = cm_object_get_child_by_name(obj, "INPUT");
    state->u.f4.reg.ma_weight = cm_object_get_child_by_name(obj, "WEIGHT");
    state->u.f4.reg.ma_output = cm_object_get_child_by_name(obj, "OUTPUT");
   
    // SR bitfields.
    state->u.f4.fld.ma_cr.acc_en = cm_object_get_child_by_name(state->u.f4.reg.ma_cr, "ACC_EN"); 

    // CR1 bitfields.
    state->u.f4.fld.ma_input.input = cm_object_get_child_by_name(state->u.f4.reg.ma_input, "ACC_INPUT"); 

    // CR2 bitfields.
    state->u.f4.fld.ma_weight.weight = cm_object_get_child_by_name(state->u.f4.reg.ma_weight, "ACC_WEIGHT"); 

    state->u.f4.fld.ma_output.output = cm_object_get_child_by_name(state->u.f4.reg.ma_output, "ACC_OUTPUT"); 
}

// ----- 8< ----- 8< -----  8< ----- 8< ----- 8< ----- 8< ----- 8< -----

// ----- Private --------------------------------------------------------------

#if 0
static peripheral_register_t stm32_ma_xxx_pre_write_callback(Object *reg,
        Object *periph, uint32_t addr, uint32_t offset, unsigned size,
        peripheral_register_t value, peripheral_register_t full_value)
{
    STM32MAState *state = STM32_MA_STATE(periph);

    peripheral_register_t prev_value = peripheral_register_get_raw_prev_value(reg);

    // TODO: Add code to adjust the value (like applying some masks,
    // for example prevent setting interrupts not enabled).
    // Also process cleared/set by write 1/0 bits.
    // The returned value will be stored in the register value.

    return full_value;
}

static void stm32_ma_xxx_post_write_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size,
        peripheral_register_t value, peripheral_register_t full_value)
{
    STM32MAState *state = STM32_MA_STATE(periph);

    peripheral_register_t prev_value = peripheral_register_get_raw_prev_value(reg);
    // The new register value is full_value, the old one is prev_value.

    // TODO: Add code to send the value to the consumer.
}

static peripheral_register_t stm32_ma_xxx_pre_read_callback(Object *reg,
        Object *periph, uint32_t addr, uint32_t offset, unsigned size)
{
    STM32MAState *state = STM32_MA_STATE(periph);

    peripheral_register_t value = 0;

    // Add code to get the value from the producer, and return it.

    // This value, possibly masked, will be stored in the register
    // and returned when the register is read.
    return value;
}

static void stm32_ma_xxx_post_read_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size)
{
    STM32MAState *state = STM32_MA_STATE(periph);

    peripheral_register_t value = peripheral_register_get_raw_value(reg);

    // TODO: add code to perform the post read actions, like clearing some bits.
}
#endif

// ----------------------------------------------------------------------------

// TODO: remove this if the peripheral is always enabled.
// static bool stm32_ma_is_enabled(Object *obj)
// {
//     STM32MAState *state = STM32_MA_STATE(obj);

//     if (register_bitfield_is_non_zero(state->enabling_bit)) {
//         return true; // Positive logic, bit == 1 means enabled.
//     }

//     // Not enabled
//     return false;
// }

// bool flag_acc_en = false;

static void stm32_ma_set_acc_en_irqs(STM32MAState *state, uint32_t old_cr,
        uint32_t new_cr)
{

    
    
    uint8_t model, dmac, mem_r, mem_w, stride;
    uint16_t w_col, w_row, i_col, i_row;
    bool issyn;

    // Compute pins that changed value.
    uint32_t changed = old_cr ^ new_cr;

    // Filter changed pins that are outputs - do not touch input pins.
    // Bit 0: ACC_EN
    uint32_t changed_out = changed & (1<<0);

    if (changed_out) {

        FILE* fp_input;
        FILE* fp_weight;
        FILE* fp_receive;
        FILE* fp_output;
        fp_input = fopen("/home/jskwon/HDD/PROJECT/2018-09-08_JSKWON/04_development/2022-11-04_MA_in_the_Loop_Framework/05_qemu_stm32_peri_add_test/2_qemu_speech_final/params/input.d", "w");
        fp_weight = fopen("/home/jskwon/HDD/PROJECT/2018-09-08_JSKWON/04_development/2022-11-04_MA_in_the_Loop_Framework/05_qemu_stm32_peri_add_test/2_qemu_speech_final/params/weight.d", "w");
        fp_receive = fopen("/home/jskwon/HDD/PROJECT/2018-09-08_JSKWON/04_development/2022-11-04_MA_in_the_Loop_Framework/05_qemu_stm32_peri_add_test/2_qemu_speech_final/params/receive.d", "w");


        // MA_INPUT register
        Object *ma_input = state->u.f4.reg.ma_input;
        // MA_WEIGHT register
        Object *ma_weight = state->u.f4.reg.ma_weight;

        // MA_CR register
        Object *ma_cr = state->u.f4.reg.ma_cr;
        uint32_t rst_value = new_cr & 0x0;

        issyn  = (peripheral_register_get_raw_value(ma_cr) & 0x40000000) >> 30;
        model  = (peripheral_register_get_raw_value(ma_cr) & 0x80000000) >> 31;
        dmac   = (peripheral_register_get_raw_value(ma_cr) & 0x7F000000) >> 24;
        mem_r  = (peripheral_register_get_raw_value(ma_cr) & 0x00FF0000) >> 16;
        mem_w  = (peripheral_register_get_raw_value(ma_cr) & 0x0000FF00) >>  8;
        stride = (peripheral_register_get_raw_value(ma_cr) & 0x000000FE) >>  1;
        fprintf(fp_receive, "%d\n%d\n%d\n%d\n", dmac, mem_r, mem_w, model);
        if( model ) {   // CNN
            w_col = (peripheral_register_get_raw_value(ma_weight) & 0xFFFF0000) >> 16;
            w_row = (peripheral_register_get_raw_value(ma_weight) & 0x0000FFFF) >>  0;
            i_col = (peripheral_register_get_raw_value(ma_input ) & 0xFFFF0000) >> 16;
            i_row = (peripheral_register_get_raw_value(ma_input ) & 0x0000FFFF) >>  0;
            fprintf(fp_receive, "%d\n%d\n%d\n%d\n%d\n", i_col, i_row, w_col, w_row, stride);

            for(int i = 0; i < i_col; i++) {
                for(int j = 0; j < i_row; j++) {
                    fprintf(fp_input, "%d ", rand()%10);
                }
                fprintf(fp_input, "\n");
            }

        } else {        // FC
            w_col = (peripheral_register_get_raw_value(ma_weight) & 0xFFFF0000) >> 16;
            w_row = (peripheral_register_get_raw_value(ma_weight) & 0x0000FFFF) >>  0;
            fprintf(fp_receive, "%d\n%d\n", w_col, w_row);

            for(int i = 0; i < w_row; i++) {
                fprintf(fp_input, "%d ", rand()%10);
            }
        }

        for(int i = 0; i < w_col; i++) {
            for(int j = 0; j < w_row; j++) {
                fprintf(fp_weight, "%d ", rand()%10);
            }
            fprintf(fp_weight, "\n");
        }

        // reset ADC1_CR2 SWSTART bit
        peripheral_register_write_value(ma_cr, rst_value);
        printf("=== MA_CR register %x --> %x \n", new_cr, rst_value);
        

        fclose(fp_input);
        fclose(fp_weight);
        fclose(fp_receive);


        system("/home/jskwon/HDD/PROJECT/2018-09-08_JSKWON/04_development/2022-11-04_MA_in_the_Loop_Framework/05_qemu_stm32_peri_add_test/2_qemu_speech_final/scripts/run_exp.exp");

        // handle received output.d
        fp_output = fopen("/home/jskwon/HDD/PROJECT/2018-09-08_JSKWON/04_development/2022-11-04_MA_in_the_Loop_Framework/05_qemu_stm32_peri_add_test/2_qemu_speech_final/params/output.d", "r");


        static int clk_sum = 0, area = 0;
        static int acc_en_cnt = 0;
        int temp;
        acc_en_cnt++;
        if( model ) {   // CNN
            int o_col = (i_col - w_col)/stride + 1;
            int o_row = (i_row - w_row)/stride + 1;
            for(int i = 0; i < o_col*o_row;i++) {
                fscanf(fp_output, "%d\n", &temp);
            }
            fscanf(fp_output, "%d\n", &temp);
            printf("\n[CLOCK %d] %d (delta: %d)\n", acc_en_cnt, clk_sum+temp, temp);
            clk_sum += temp;
        } else {        // FC
            for(int i = 0; i < w_col;i++) {
                fscanf(fp_output, "%d\n", &temp);
            }
            fscanf(fp_output, "%d\n", &temp);
            printf("\n[CLOCK %d] %d (delta: %d)\n", acc_en_cnt, clk_sum+temp, temp);
            clk_sum += temp;           
        }
        if( issyn ) {
            fscanf(fp_output, "%d\n", &temp);
            area += temp;     
            printf("\n[AREA] %d\n", area);
        }
        
        fclose(fp_output);
    }

}

static void stm32f4_ma_output_post_read_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size)
{
    STM32MAState *state = STM32_MA_STATE(periph);

    Object *ma_output = state->u.f4.reg.ma_output;
    assert(ma_output);

    uint16_t output_value = (uint16_t)(rand()%100) + 1;

    peripheral_register_write_value(ma_output, output_value);

    // printf("=== Enter MA_OUTPUT Read Callback \n");
    // printf("=== MA_OUTPUT register --> %lx \n", output_value);
}


static void stm32f4_ma_cr_post_write_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size,
        peripheral_register_t value, peripheral_register_t full_value)
{
    STM32MAState *state = STM32_MA_STATE(periph);

    Object *ma_cr = state->u.f4.reg.ma_cr;
    assert(ma_cr);

    uint32_t prev_value = peripheral_register_get_raw_prev_value(ma_cr);

    printf("=== Enter MA_CR_EN interrupt \n");
    printf("=== MA_CR ACC_EN register %x --> %lx \n", prev_value, full_value);

    // 'value' may be have any size, use full_word.
    stm32_ma_set_acc_en_irqs(state, prev_value, full_value);
}

/*
static void stm32f4_ma_output_post_write_callback(Object *reg, Object *periph,
        uint32_t addr, uint32_t offset, unsigned size,
        peripheral_register_t value, peripheral_register_t full_value)
{
    STM32MAState *state = STM32_MA_STATE(periph);

    Object *ma_output = state->u.f4.reg.ma_output;
    assert(ma_output);

    uint32_t prev_value = peripheral_register_get_raw_prev_value(ma_output);

    printf("=== Enter MA_OUTPUT interrupt \n");
    printf("=== MA_OUTPUT register %x --> %lx \n", prev_value, full_value);

    // 'value' may be have any size, use full_word.
}
*/



static void stm32_ma_instance_init_callback(Object *obj)
{
    qemu_log_function_name();

    STM32MAState *state = STM32_MA_STATE(obj);

    // Capabilities are not yet available.

    cm_object_property_add_int(obj, "port-index",
            (const int *) &state->port_index);
    state->port_index = STM32_PORT_MA_UNDEFINED;

    // TODO: remove this if the peripheral is always enabled.
    // state->enabling_bit = NULL;
    
    // TODO: Add code to initialise all members.
}

static void stm32_ma_realize_callback(DeviceState *dev, Error **errp)
{
    qemu_log_function_name();

    // Call parent realize().
    if (!cm_device_parent_realize(dev, errp, TYPE_STM32_MA)) {
        return;
    }

    STM32MCUState *mcu = stm32_mcu_get();
    CortexMState *cm_state = CORTEXM_MCU_STATE(mcu);

    STM32MAState *state = STM32_MA_STATE(dev);
    // First thing first: get capabilities from MCU, needed everywhere.
    state->capabilities = mcu->capabilities;

    // Also keep a local pointer, to access them easier.
    const STM32Capabilities *capabilities = state->capabilities;
    assert(capabilities != NULL);

    Object *obj = OBJECT(dev);

    const char *periph_name = "MA";

    svd_set_peripheral_address_block(cm_state->svd_json, periph_name, obj);
    peripheral_create_memory_region(obj);

    cm_object_property_set_int(obj, 4, "register-size-bytes");
    cm_object_property_set_bool(obj, true, "is-little-endian");

    // TODO: remove this if the peripheral is always enabled.
    // char enabling_bit_name[STM32_RCC_SIZEOF_ENABLING_BITFIELD];

    switch (capabilities->family) {
    case STM32_FAMILY_F4:

        if (capabilities->f4.is_40x ) {

            stm32f40x_ma_create_objects(obj, cm_state->svd_json, periph_name);

            // TODO: add actions.
            // cm_object_property_set_str(state->u.f4.fld.xxx.fff, "GGG", "follows");
            // cm_object_property_set_str(state->u.f4.fld.xxx.fff, "GGG", "cleared-by");

            // TODO: add callbacks.
            // peripheral_register_set_pre_read(state->f4.reg.xxx, &stm32_ma_xxx_pre_read_callback);
            // peripheral_register_set_post_read(state->f4.reg.xxx, &stm32_ma_xxx_post_read_callback);
            // peripheral_register_set_pre_read(state->f4.reg.xxx, &stm32_ma_xxx_pret_read_callback);
            // peripheral_register_set_post_write(state->f4.reg.xxx, &stm32_ma_xxx_post_write_callback);
            peripheral_register_set_post_write(state->u.f4.reg.ma_cr, &stm32f4_ma_cr_post_write_callback);
            // peripheral_register_set_post_write(state->u.f4.reg.ma_output, &stm32f4_ma_output_post_write_callback);

            peripheral_register_set_post_read(state->u.f4.reg.ma_output, &stm32f4_ma_output_post_read_callback);

            // TODO: add interrupts.

           // TODO: remove this if the peripheral is always enabled.
        //    snprintf(enabling_bit_name, sizeof(enabling_bit_name) - 1,
        //         DEVICE_PATH_STM32_RCC "/AHB1ENR/MA%dEN",
        //         1 + state->port_index - STM32_PORT_MA1);

            printf("[INFO] MA enable \n");
        } else {
            assert(false);
        }

        break;

    default:
        assert(false);
        break;
    }

    // TODO: remove this if the peripheral is always enabled.
    // state->enabling_bit = OBJECT(cm_device_by_name(enabling_bit_name));

    peripheral_prepare_registers(obj);
}

static void stm32_ma_reset_callback(DeviceState *dev)
{
    qemu_log_function_name();

    // Call parent reset(); this will reset all children registers.
    cm_device_parent_reset(dev, TYPE_STM32_MA);
}

static void stm32_ma_class_init_callback(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = stm32_ma_reset_callback;
    dc->realize = stm32_ma_realize_callback;

    // TODO: remove this if the peripheral is always enabled.
    //PeripheralClass *per_class = PERIPHERAL_CLASS(klass);
    //per_class->is_enabled = stm32_ma_is_enabled;
}

static const TypeInfo stm32_ma_type_info = {
    .name = TYPE_STM32_MA,
    .parent = TYPE_STM32_MA_PARENT,
    .instance_init = stm32_ma_instance_init_callback,
    .instance_size = sizeof(STM32MAState),
    .class_init = stm32_ma_class_init_callback,
    .class_size = sizeof(STM32MAClass) };

static void stm32_ma_register_types(void)
{
    type_register_static(&stm32_ma_type_info);
}

type_init(stm32_ma_register_types);

// ----------------------------------------------------------------------------
