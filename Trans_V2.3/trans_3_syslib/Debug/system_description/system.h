/* system.h
 *
 * Machine generated for a CPU named "cpu_0" as defined in:
 * G:\Quartus\transfer_new\TRANS_3.ptf
 *
 * Generated: 2015-04-11 16:52:05.487
 *
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/*

DO NOT MODIFY THIS FILE

   Changing this file will have subtle consequences
   which will almost certainly lead to a nonfunctioning
   system. If you do modify this file, be aware that your
   changes will be overwritten and lost when this file
   is generated again.

DO NOT MODIFY THIS FILE

*/

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2003 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
*                                                                             *
******************************************************************************/

/*
 * system configuration
 *
 */

#define ALT_SYSTEM_NAME "TRANS_3"
#define ALT_CPU_NAME "cpu_0"
#define ALT_CPU_ARCHITECTURE "altera_nios2"
#define ALT_DEVICE_FAMILY "CYCLONEIII"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN_BASE 0x01002180
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_PRESENT
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT_BASE 0x01002180
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_PRESENT
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDERR_BASE 0x01002180
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_PRESENT
#define ALT_CPU_FREQ 50000000
#define ALT_IRQ_BASE NULL
#define ALT_LEGACY_INTERRUPT_API_PRESENT

/*
 * processor configuration
 *
 */

#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_BIG_ENDIAN 0
#define NIOS2_INTERRUPT_CONTROLLER_ID 0

#define NIOS2_ICACHE_SIZE 2048
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_FLUSHDA_SUPPORTED

#define NIOS2_EXCEPTION_ADDR 0x00800020
#define NIOS2_RESET_ADDR 0x01001800
#define NIOS2_BREAK_ADDR 0x01001020

#define NIOS2_HAS_DEBUG_STUB

#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0

/*
 * A define for each class of peripheral
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_EPCS_FLASH_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_UART
#define __ALTERA_AVALON_SYSID
#define __ALTERA_AVALON_TIMER

/*
 * jtag_uart_0 configuration
 *
 */

#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_BASE 0x01002180
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_IRQ 0
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_READ_CHAR_STREAM ""
#define JTAG_UART_0_SHOWASCII 1
#define JTAG_UART_0_RELATIVEPATH 0
#define JTAG_UART_0_READ_LE 0
#define JTAG_UART_0_WRITE_LE 0
#define JTAG_UART_0_ALTERA_SHOW_UNRELEASED_JTAG_UART_FEATURES 0
#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart

/*
 * sdram_0 configuration
 *
 */

#define SDRAM_0_NAME "/dev/sdram_0"
#define SDRAM_0_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_0_BASE 0x00800000
#define SDRAM_0_SPAN 8388608
#define SDRAM_0_REGISTER_DATA_IN 1
#define SDRAM_0_SIM_MODEL_BASE 1
#define SDRAM_0_SDRAM_DATA_WIDTH 16
#define SDRAM_0_SDRAM_ADDR_WIDTH 12
#define SDRAM_0_SDRAM_ROW_WIDTH 12
#define SDRAM_0_SDRAM_COL_WIDTH 8
#define SDRAM_0_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_0_SDRAM_NUM_BANKS 4
#define SDRAM_0_REFRESH_PERIOD 15.625
#define SDRAM_0_POWERUP_DELAY 100.0
#define SDRAM_0_CAS_LATENCY 3
#define SDRAM_0_T_RFC 70.0
#define SDRAM_0_T_RP 20.0
#define SDRAM_0_T_MRD 3
#define SDRAM_0_T_RCD 20.0
#define SDRAM_0_T_AC 5.5
#define SDRAM_0_T_WR 14.0
#define SDRAM_0_INIT_REFRESH_COMMANDS 2
#define SDRAM_0_INIT_NOP_DELAY 0.0
#define SDRAM_0_SHARED_DATA 0
#define SDRAM_0_SDRAM_BANK_WIDTH 2
#define SDRAM_0_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_0_STARVATION_INDICATOR 0
#define SDRAM_0_IS_INITIALIZED 1
#define ALT_MODULE_CLASS_sdram_0 altera_avalon_new_sdram_controller

/*
 * epcs_flash_controller_0 configuration
 *
 */

#define EPCS_FLASH_CONTROLLER_0_NAME "/dev/epcs_flash_controller_0"
#define EPCS_FLASH_CONTROLLER_0_TYPE "altera_avalon_epcs_flash_controller"
#define EPCS_FLASH_CONTROLLER_0_BASE 0x01001800
#define EPCS_FLASH_CONTROLLER_0_SPAN 2048
#define EPCS_FLASH_CONTROLLER_0_IRQ 1
#define EPCS_FLASH_CONTROLLER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define EPCS_FLASH_CONTROLLER_0_DATABITS 8
#define EPCS_FLASH_CONTROLLER_0_TARGETCLOCK 20
#define EPCS_FLASH_CONTROLLER_0_CLOCKUNITS "MHz"
#define EPCS_FLASH_CONTROLLER_0_CLOCKMULT 1000000
#define EPCS_FLASH_CONTROLLER_0_NUMSLAVES 1
#define EPCS_FLASH_CONTROLLER_0_ISMASTER 1
#define EPCS_FLASH_CONTROLLER_0_CLOCKPOLARITY 0
#define EPCS_FLASH_CONTROLLER_0_CLOCKPHASE 0
#define EPCS_FLASH_CONTROLLER_0_LSBFIRST 0
#define EPCS_FLASH_CONTROLLER_0_EXTRADELAY 0
#define EPCS_FLASH_CONTROLLER_0_TARGETSSDELAY 100
#define EPCS_FLASH_CONTROLLER_0_DELAYUNITS "us"
#define EPCS_FLASH_CONTROLLER_0_DELAYMULT "1e-006"
#define EPCS_FLASH_CONTROLLER_0_PREFIX "epcs_"
#define EPCS_FLASH_CONTROLLER_0_REGISTER_OFFSET 0x400
#define EPCS_FLASH_CONTROLLER_0_IGNORE_LEGACY_CHECK 1
#define EPCS_FLASH_CONTROLLER_0_USE_ASMI_ATOM 0
#define EPCS_FLASH_CONTROLLER_0_CLOCKUNIT "kHz"
#define EPCS_FLASH_CONTROLLER_0_DELAYUNIT "us"
#define EPCS_FLASH_CONTROLLER_0_DISABLEAVALONFLOWCONTROL 0
#define EPCS_FLASH_CONTROLLER_0_INSERT_SYNC 0
#define EPCS_FLASH_CONTROLLER_0_SYNC_REG_DEPTH 2
#define ALT_MODULE_CLASS_epcs_flash_controller_0 altera_avalon_epcs_flash_controller

/*
 * pio_c1_ce configuration
 *
 */

#define PIO_C1_CE_NAME "/dev/pio_c1_ce"
#define PIO_C1_CE_TYPE "altera_avalon_pio"
#define PIO_C1_CE_BASE 0x01002060
#define PIO_C1_CE_SPAN 16
#define PIO_C1_CE_DO_TEST_BENCH_WIRING 0
#define PIO_C1_CE_DRIVEN_SIM_VALUE 0
#define PIO_C1_CE_HAS_TRI 0
#define PIO_C1_CE_HAS_OUT 1
#define PIO_C1_CE_HAS_IN 0
#define PIO_C1_CE_CAPTURE 0
#define PIO_C1_CE_DATA_WIDTH 1
#define PIO_C1_CE_RESET_VALUE 0
#define PIO_C1_CE_EDGE_TYPE "NONE"
#define PIO_C1_CE_IRQ_TYPE "NONE"
#define PIO_C1_CE_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_C1_CE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_C1_CE_FREQ 50000000
#define ALT_MODULE_CLASS_pio_c1_ce altera_avalon_pio

/*
 * pio_c1_clk configuration
 *
 */

#define PIO_C1_CLK_NAME "/dev/pio_c1_clk"
#define PIO_C1_CLK_TYPE "altera_avalon_pio"
#define PIO_C1_CLK_BASE 0x01002070
#define PIO_C1_CLK_SPAN 16
#define PIO_C1_CLK_DO_TEST_BENCH_WIRING 0
#define PIO_C1_CLK_DRIVEN_SIM_VALUE 0
#define PIO_C1_CLK_HAS_TRI 0
#define PIO_C1_CLK_HAS_OUT 1
#define PIO_C1_CLK_HAS_IN 0
#define PIO_C1_CLK_CAPTURE 0
#define PIO_C1_CLK_DATA_WIDTH 1
#define PIO_C1_CLK_RESET_VALUE 0
#define PIO_C1_CLK_EDGE_TYPE "NONE"
#define PIO_C1_CLK_IRQ_TYPE "NONE"
#define PIO_C1_CLK_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_C1_CLK_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_C1_CLK_FREQ 50000000
#define ALT_MODULE_CLASS_pio_c1_clk altera_avalon_pio

/*
 * pio_c2_ce configuration
 *
 */

#define PIO_C2_CE_NAME "/dev/pio_c2_ce"
#define PIO_C2_CE_TYPE "altera_avalon_pio"
#define PIO_C2_CE_BASE 0x01002080
#define PIO_C2_CE_SPAN 16
#define PIO_C2_CE_DO_TEST_BENCH_WIRING 0
#define PIO_C2_CE_DRIVEN_SIM_VALUE 0
#define PIO_C2_CE_HAS_TRI 0
#define PIO_C2_CE_HAS_OUT 1
#define PIO_C2_CE_HAS_IN 0
#define PIO_C2_CE_CAPTURE 0
#define PIO_C2_CE_DATA_WIDTH 1
#define PIO_C2_CE_RESET_VALUE 0
#define PIO_C2_CE_EDGE_TYPE "NONE"
#define PIO_C2_CE_IRQ_TYPE "NONE"
#define PIO_C2_CE_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_C2_CE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_C2_CE_FREQ 50000000
#define ALT_MODULE_CLASS_pio_c2_ce altera_avalon_pio

/*
 * pio_c2_clk configuration
 *
 */

#define PIO_C2_CLK_NAME "/dev/pio_c2_clk"
#define PIO_C2_CLK_TYPE "altera_avalon_pio"
#define PIO_C2_CLK_BASE 0x01002090
#define PIO_C2_CLK_SPAN 16
#define PIO_C2_CLK_DO_TEST_BENCH_WIRING 0
#define PIO_C2_CLK_DRIVEN_SIM_VALUE 0
#define PIO_C2_CLK_HAS_TRI 0
#define PIO_C2_CLK_HAS_OUT 1
#define PIO_C2_CLK_HAS_IN 0
#define PIO_C2_CLK_CAPTURE 0
#define PIO_C2_CLK_DATA_WIDTH 1
#define PIO_C2_CLK_RESET_VALUE 0
#define PIO_C2_CLK_EDGE_TYPE "NONE"
#define PIO_C2_CLK_IRQ_TYPE "NONE"
#define PIO_C2_CLK_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_C2_CLK_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_C2_CLK_FREQ 50000000
#define ALT_MODULE_CLASS_pio_c2_clk altera_avalon_pio

/*
 * pio_c1_dr configuration
 *
 */

#define PIO_C1_DR_NAME "/dev/pio_c1_dr"
#define PIO_C1_DR_TYPE "altera_avalon_pio"
#define PIO_C1_DR_BASE 0x010020a0
#define PIO_C1_DR_SPAN 16
#define PIO_C1_DR_IRQ 2
#define PIO_C1_DR_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_C1_DR_DO_TEST_BENCH_WIRING 0
#define PIO_C1_DR_DRIVEN_SIM_VALUE 0
#define PIO_C1_DR_HAS_TRI 0
#define PIO_C1_DR_HAS_OUT 0
#define PIO_C1_DR_HAS_IN 1
#define PIO_C1_DR_CAPTURE 1
#define PIO_C1_DR_DATA_WIDTH 1
#define PIO_C1_DR_RESET_VALUE 0
#define PIO_C1_DR_EDGE_TYPE "RISING"
#define PIO_C1_DR_IRQ_TYPE "EDGE"
#define PIO_C1_DR_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_C1_DR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_C1_DR_FREQ 50000000
#define ALT_MODULE_CLASS_pio_c1_dr altera_avalon_pio

/*
 * pio_c2_dr configuration
 *
 */

#define PIO_C2_DR_NAME "/dev/pio_c2_dr"
#define PIO_C2_DR_TYPE "altera_avalon_pio"
#define PIO_C2_DR_BASE 0x010020b0
#define PIO_C2_DR_SPAN 16
#define PIO_C2_DR_IRQ 3
#define PIO_C2_DR_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_C2_DR_DO_TEST_BENCH_WIRING 0
#define PIO_C2_DR_DRIVEN_SIM_VALUE 0
#define PIO_C2_DR_HAS_TRI 0
#define PIO_C2_DR_HAS_OUT 0
#define PIO_C2_DR_HAS_IN 1
#define PIO_C2_DR_CAPTURE 1
#define PIO_C2_DR_DATA_WIDTH 1
#define PIO_C2_DR_RESET_VALUE 0
#define PIO_C2_DR_EDGE_TYPE "RISING"
#define PIO_C2_DR_IRQ_TYPE "EDGE"
#define PIO_C2_DR_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_C2_DR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_C2_DR_FREQ 50000000
#define ALT_MODULE_CLASS_pio_c2_dr altera_avalon_pio

/*
 * pio_c1_data configuration
 *
 */

#define PIO_C1_DATA_NAME "/dev/pio_c1_data"
#define PIO_C1_DATA_TYPE "altera_avalon_pio"
#define PIO_C1_DATA_BASE 0x010020c0
#define PIO_C1_DATA_SPAN 16
#define PIO_C1_DATA_DO_TEST_BENCH_WIRING 0
#define PIO_C1_DATA_DRIVEN_SIM_VALUE 0
#define PIO_C1_DATA_HAS_TRI 1
#define PIO_C1_DATA_HAS_OUT 0
#define PIO_C1_DATA_HAS_IN 0
#define PIO_C1_DATA_CAPTURE 0
#define PIO_C1_DATA_DATA_WIDTH 1
#define PIO_C1_DATA_RESET_VALUE 0
#define PIO_C1_DATA_EDGE_TYPE "NONE"
#define PIO_C1_DATA_IRQ_TYPE "NONE"
#define PIO_C1_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_C1_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_C1_DATA_FREQ 50000000
#define ALT_MODULE_CLASS_pio_c1_data altera_avalon_pio

/*
 * pio_c2_data configuration
 *
 */

#define PIO_C2_DATA_NAME "/dev/pio_c2_data"
#define PIO_C2_DATA_TYPE "altera_avalon_pio"
#define PIO_C2_DATA_BASE 0x010020d0
#define PIO_C2_DATA_SPAN 16
#define PIO_C2_DATA_DO_TEST_BENCH_WIRING 0
#define PIO_C2_DATA_DRIVEN_SIM_VALUE 0
#define PIO_C2_DATA_HAS_TRI 1
#define PIO_C2_DATA_HAS_OUT 0
#define PIO_C2_DATA_HAS_IN 0
#define PIO_C2_DATA_CAPTURE 0
#define PIO_C2_DATA_DATA_WIDTH 1
#define PIO_C2_DATA_RESET_VALUE 0
#define PIO_C2_DATA_EDGE_TYPE "NONE"
#define PIO_C2_DATA_IRQ_TYPE "NONE"
#define PIO_C2_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_C2_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_C2_DATA_FREQ 50000000
#define ALT_MODULE_CLASS_pio_c2_data altera_avalon_pio

/*
 * pio_c1_cs configuration
 *
 */

#define PIO_C1_CS_NAME "/dev/pio_c1_cs"
#define PIO_C1_CS_TYPE "altera_avalon_pio"
#define PIO_C1_CS_BASE 0x010020e0
#define PIO_C1_CS_SPAN 16
#define PIO_C1_CS_DO_TEST_BENCH_WIRING 0
#define PIO_C1_CS_DRIVEN_SIM_VALUE 0
#define PIO_C1_CS_HAS_TRI 0
#define PIO_C1_CS_HAS_OUT 1
#define PIO_C1_CS_HAS_IN 0
#define PIO_C1_CS_CAPTURE 0
#define PIO_C1_CS_DATA_WIDTH 1
#define PIO_C1_CS_RESET_VALUE 0
#define PIO_C1_CS_EDGE_TYPE "NONE"
#define PIO_C1_CS_IRQ_TYPE "NONE"
#define PIO_C1_CS_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_C1_CS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_C1_CS_FREQ 50000000
#define ALT_MODULE_CLASS_pio_c1_cs altera_avalon_pio

/*
 * pio_c2_cs configuration
 *
 */

#define PIO_C2_CS_NAME "/dev/pio_c2_cs"
#define PIO_C2_CS_TYPE "altera_avalon_pio"
#define PIO_C2_CS_BASE 0x010020f0
#define PIO_C2_CS_SPAN 16
#define PIO_C2_CS_DO_TEST_BENCH_WIRING 0
#define PIO_C2_CS_DRIVEN_SIM_VALUE 0
#define PIO_C2_CS_HAS_TRI 0
#define PIO_C2_CS_HAS_OUT 1
#define PIO_C2_CS_HAS_IN 0
#define PIO_C2_CS_CAPTURE 0
#define PIO_C2_CS_DATA_WIDTH 1
#define PIO_C2_CS_RESET_VALUE 0
#define PIO_C2_CS_EDGE_TYPE "NONE"
#define PIO_C2_CS_IRQ_TYPE "NONE"
#define PIO_C2_CS_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_C2_CS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_C2_CS_FREQ 50000000
#define ALT_MODULE_CLASS_pio_c2_cs altera_avalon_pio

/*
 * uart_usb configuration
 *
 */

#define UART_USB_NAME "/dev/uart_usb"
#define UART_USB_TYPE "altera_avalon_uart"
#define UART_USB_BASE 0x01002000
#define UART_USB_SPAN 32
#define UART_USB_IRQ 4
#define UART_USB_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_USB_BAUD 115200
#define UART_USB_DATA_BITS 8
#define UART_USB_FIXED_BAUD 1
#define UART_USB_PARITY 'N'
#define UART_USB_STOP_BITS 1
#define UART_USB_SYNC_REG_DEPTH 2
#define UART_USB_USE_CTS_RTS 0
#define UART_USB_USE_EOP_REGISTER 0
#define UART_USB_SIM_TRUE_BAUD 0
#define UART_USB_SIM_CHAR_STREAM ""
#define UART_USB_RELATIVEPATH 0
#define UART_USB_FREQ 50000000
#define ALT_MODULE_CLASS_uart_usb altera_avalon_uart

/*
 * sysid configuration
 *
 */

#define SYSID_NAME "/dev/sysid"
#define SYSID_TYPE "altera_avalon_sysid"
#define SYSID_BASE 0x01002188
#define SYSID_SPAN 8
#define SYSID_ID 364094772u
#define SYSID_TIMESTAMP 1426599870u
#define SYSID_REGENERATE_VALUES 0
#define ALT_MODULE_CLASS_sysid altera_avalon_sysid

/*
 * pio_led1 configuration
 *
 */

#define PIO_LED1_NAME "/dev/pio_led1"
#define PIO_LED1_TYPE "altera_avalon_pio"
#define PIO_LED1_BASE 0x01002100
#define PIO_LED1_SPAN 16
#define PIO_LED1_DO_TEST_BENCH_WIRING 0
#define PIO_LED1_DRIVEN_SIM_VALUE 0
#define PIO_LED1_HAS_TRI 0
#define PIO_LED1_HAS_OUT 1
#define PIO_LED1_HAS_IN 0
#define PIO_LED1_CAPTURE 0
#define PIO_LED1_DATA_WIDTH 1
#define PIO_LED1_RESET_VALUE 1
#define PIO_LED1_EDGE_TYPE "NONE"
#define PIO_LED1_IRQ_TYPE "NONE"
#define PIO_LED1_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_LED1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_LED1_FREQ 50000000
#define ALT_MODULE_CLASS_pio_led1 altera_avalon_pio

/*
 * pio_led2 configuration
 *
 */

#define PIO_LED2_NAME "/dev/pio_led2"
#define PIO_LED2_TYPE "altera_avalon_pio"
#define PIO_LED2_BASE 0x01002110
#define PIO_LED2_SPAN 16
#define PIO_LED2_DO_TEST_BENCH_WIRING 0
#define PIO_LED2_DRIVEN_SIM_VALUE 0
#define PIO_LED2_HAS_TRI 0
#define PIO_LED2_HAS_OUT 1
#define PIO_LED2_HAS_IN 0
#define PIO_LED2_CAPTURE 0
#define PIO_LED2_DATA_WIDTH 1
#define PIO_LED2_RESET_VALUE 1
#define PIO_LED2_EDGE_TYPE "NONE"
#define PIO_LED2_IRQ_TYPE "NONE"
#define PIO_LED2_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_LED2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_LED2_FREQ 50000000
#define ALT_MODULE_CLASS_pio_led2 altera_avalon_pio

/*
 * pio_led3 configuration
 *
 */

#define PIO_LED3_NAME "/dev/pio_led3"
#define PIO_LED3_TYPE "altera_avalon_pio"
#define PIO_LED3_BASE 0x01002120
#define PIO_LED3_SPAN 16
#define PIO_LED3_DO_TEST_BENCH_WIRING 0
#define PIO_LED3_DRIVEN_SIM_VALUE 0
#define PIO_LED3_HAS_TRI 0
#define PIO_LED3_HAS_OUT 1
#define PIO_LED3_HAS_IN 0
#define PIO_LED3_CAPTURE 0
#define PIO_LED3_DATA_WIDTH 1
#define PIO_LED3_RESET_VALUE 1
#define PIO_LED3_EDGE_TYPE "NONE"
#define PIO_LED3_IRQ_TYPE "NONE"
#define PIO_LED3_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_LED3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_LED3_FREQ 50000000
#define ALT_MODULE_CLASS_pio_led3 altera_avalon_pio

/*
 * pio_clk_24 configuration
 *
 */

#define PIO_CLK_24_NAME "/dev/pio_clk_24"
#define PIO_CLK_24_TYPE "altera_avalon_pio"
#define PIO_CLK_24_BASE 0x01002130
#define PIO_CLK_24_SPAN 16
#define PIO_CLK_24_DO_TEST_BENCH_WIRING 0
#define PIO_CLK_24_DRIVEN_SIM_VALUE 0
#define PIO_CLK_24_HAS_TRI 0
#define PIO_CLK_24_HAS_OUT 1
#define PIO_CLK_24_HAS_IN 0
#define PIO_CLK_24_CAPTURE 0
#define PIO_CLK_24_DATA_WIDTH 1
#define PIO_CLK_24_RESET_VALUE 0
#define PIO_CLK_24_EDGE_TYPE "NONE"
#define PIO_CLK_24_IRQ_TYPE "NONE"
#define PIO_CLK_24_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_CLK_24_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_CLK_24_FREQ 50000000
#define ALT_MODULE_CLASS_pio_clk_24 altera_avalon_pio

/*
 * pio_data_24 configuration
 *
 */

#define PIO_DATA_24_NAME "/dev/pio_data_24"
#define PIO_DATA_24_TYPE "altera_avalon_pio"
#define PIO_DATA_24_BASE 0x01002140
#define PIO_DATA_24_SPAN 16
#define PIO_DATA_24_DO_TEST_BENCH_WIRING 0
#define PIO_DATA_24_DRIVEN_SIM_VALUE 0
#define PIO_DATA_24_HAS_TRI 1
#define PIO_DATA_24_HAS_OUT 0
#define PIO_DATA_24_HAS_IN 0
#define PIO_DATA_24_CAPTURE 0
#define PIO_DATA_24_DATA_WIDTH 1
#define PIO_DATA_24_RESET_VALUE 0
#define PIO_DATA_24_EDGE_TYPE "NONE"
#define PIO_DATA_24_IRQ_TYPE "NONE"
#define PIO_DATA_24_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_DATA_24_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_DATA_24_FREQ 50000000
#define ALT_MODULE_CLASS_pio_data_24 altera_avalon_pio

/*
 * pio_scl_9557 configuration
 *
 */

#define PIO_SCL_9557_NAME "/dev/pio_scl_9557"
#define PIO_SCL_9557_TYPE "altera_avalon_pio"
#define PIO_SCL_9557_BASE 0x01002150
#define PIO_SCL_9557_SPAN 16
#define PIO_SCL_9557_DO_TEST_BENCH_WIRING 0
#define PIO_SCL_9557_DRIVEN_SIM_VALUE 0
#define PIO_SCL_9557_HAS_TRI 0
#define PIO_SCL_9557_HAS_OUT 1
#define PIO_SCL_9557_HAS_IN 0
#define PIO_SCL_9557_CAPTURE 0
#define PIO_SCL_9557_DATA_WIDTH 1
#define PIO_SCL_9557_RESET_VALUE 0
#define PIO_SCL_9557_EDGE_TYPE "NONE"
#define PIO_SCL_9557_IRQ_TYPE "NONE"
#define PIO_SCL_9557_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_SCL_9557_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_SCL_9557_FREQ 50000000
#define ALT_MODULE_CLASS_pio_scl_9557 altera_avalon_pio

/*
 * pio_sda_9557 configuration
 *
 */

#define PIO_SDA_9557_NAME "/dev/pio_sda_9557"
#define PIO_SDA_9557_TYPE "altera_avalon_pio"
#define PIO_SDA_9557_BASE 0x01002160
#define PIO_SDA_9557_SPAN 16
#define PIO_SDA_9557_DO_TEST_BENCH_WIRING 0
#define PIO_SDA_9557_DRIVEN_SIM_VALUE 0
#define PIO_SDA_9557_HAS_TRI 1
#define PIO_SDA_9557_HAS_OUT 0
#define PIO_SDA_9557_HAS_IN 0
#define PIO_SDA_9557_CAPTURE 0
#define PIO_SDA_9557_DATA_WIDTH 1
#define PIO_SDA_9557_RESET_VALUE 0
#define PIO_SDA_9557_EDGE_TYPE "NONE"
#define PIO_SDA_9557_IRQ_TYPE "NONE"
#define PIO_SDA_9557_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_SDA_9557_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_SDA_9557_FREQ 50000000
#define ALT_MODULE_CLASS_pio_sda_9557 altera_avalon_pio

/*
 * pio_reset_9557 configuration
 *
 */

#define PIO_RESET_9557_NAME "/dev/pio_reset_9557"
#define PIO_RESET_9557_TYPE "altera_avalon_pio"
#define PIO_RESET_9557_BASE 0x01002170
#define PIO_RESET_9557_SPAN 16
#define PIO_RESET_9557_DO_TEST_BENCH_WIRING 0
#define PIO_RESET_9557_DRIVEN_SIM_VALUE 0
#define PIO_RESET_9557_HAS_TRI 0
#define PIO_RESET_9557_HAS_OUT 1
#define PIO_RESET_9557_HAS_IN 0
#define PIO_RESET_9557_CAPTURE 0
#define PIO_RESET_9557_DATA_WIDTH 1
#define PIO_RESET_9557_RESET_VALUE 0
#define PIO_RESET_9557_EDGE_TYPE "NONE"
#define PIO_RESET_9557_IRQ_TYPE "NONE"
#define PIO_RESET_9557_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_RESET_9557_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_RESET_9557_FREQ 50000000
#define ALT_MODULE_CLASS_pio_reset_9557 altera_avalon_pio

/*
 * timer_watchdog configuration
 *
 */

#define TIMER_WATCHDOG_NAME "/dev/timer_watchdog"
#define TIMER_WATCHDOG_TYPE "altera_avalon_timer"
#define TIMER_WATCHDOG_BASE 0x01002020
#define TIMER_WATCHDOG_SPAN 32
#define TIMER_WATCHDOG_IRQ 5
#define TIMER_WATCHDOG_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_WATCHDOG_ALWAYS_RUN 1
#define TIMER_WATCHDOG_FIXED_PERIOD 1
#define TIMER_WATCHDOG_SNAPSHOT 0
#define TIMER_WATCHDOG_PERIOD 500
#define TIMER_WATCHDOG_PERIOD_UNITS "ms"
#define TIMER_WATCHDOG_RESET_OUTPUT 1
#define TIMER_WATCHDOG_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_WATCHDOG_LOAD_VALUE 24999999
#define TIMER_WATCHDOG_COUNTER_SIZE 32
#define TIMER_WATCHDOG_MULT 0.0010
#define TIMER_WATCHDOG_TICKS_PER_SEC 2
#define TIMER_WATCHDOG_FREQ 50000000
#define ALT_MODULE_CLASS_timer_watchdog altera_avalon_timer

/*
 * timer_0 configuration
 *
 */

#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_TYPE "altera_avalon_timer"
#define TIMER_0_BASE 0x01002040
#define TIMER_0_SPAN 32
#define TIMER_0_IRQ 6
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_LOAD_VALUE 49999
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_MULT 0.0010
#define TIMER_0_TICKS_PER_SEC 1000
#define TIMER_0_FREQ 50000000
#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer

/*
 * system library configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER_WATCHDOG
#define ALT_TIMESTAMP_CLK none

/*
 * Devices associated with code sections.
 *
 */

#define ALT_TEXT_DEVICE       SDRAM_0
#define ALT_RODATA_DEVICE     SDRAM_0
#define ALT_RWDATA_DEVICE     SDRAM_0
#define ALT_EXCEPTIONS_DEVICE SDRAM_0
#define ALT_RESET_DEVICE      EPCS_FLASH_CONTROLLER_0


#endif /* __SYSTEM_H_ */
