#ifndef fingerprint_sensor_H_INCLUDED
#define fingerprint_sensor_H_INCLUDED


#include <inttypes.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "IO_Macros.h"
#include "fingerprint_sensor_settings.h"



// -----Auxillary Data------------//

#define __execution_complete                     0x00
#define __error_in_data_package                  0x01
#define __no_finger_on_sensor					 0x02
#define __fail_to_enroll						 0x03
#define __fail_to_generate_disorderly			 0x06
#define __fail_to_generate_small                 0x07
#define __no_match								 0x08
#define __finger_not_found						 0x09
#define __fail_combine_char_files				 0x0A
#define __adress_not_in_lib						 0x0B
#define __error_reading_template                 0x0C
#define __error_uploading_template				 0x0D
#define __bad_packet							 0x0E
#define __error_uploading_image                  0x0F
#define __delete_template_failure                0x10
#define __lib_clear_failure                      0x11
#define __image_failure                          0x15
#define __flash_error							 0x18
#define __error_not_defined						 0x19
#define __invalid_register                       0x1A
#define __bad_register_configuration             0x1B
#define __wrong_notepad_page                     0x1C
#define __com_port_failure                       0x1D


/* Prototypes */
void packet_generator();
void FP_setup();
uint16_t FP_shake_hands();
void FP_enroll_finger();
void FP_store_finger(uint32_t address);
void FP_finger_search(uint32_t address);
void FP_remove_finger(uint32_t address);
void FP_clear_library();
uint32_t Address();
uint32_t DATA();
uint8_t PID();
uint16_t LENGTH();
uint16_t CheckSum();
 




#endif