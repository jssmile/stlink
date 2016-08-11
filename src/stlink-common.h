/*
 * File:   stlink-common.h
 * Bulk import from stlink-hw.h
 *
 * This should contain all the common top level stlink interfaces, regardless
 * of how the backend does the work....
 */

#ifndef STLINK_COMMON_H
#define STLINK_COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

    // Max data transfer size.
    // 6kB = max mem32_read block, 8kB sram
    //#define Q_BUF_LEN	96
#define Q_BUF_LEN			(1024 * 100)

    // st-link vendor cmd's
#define USB_ST_VID			0x0483
#define USB_STLINK_PID			0x3744
#define USB_STLINK_32L_PID		0x3748
#define USB_STLINK_NUCLEO_PID	0x374b

    // STLINK_DEBUG_RESETSYS, etc:
#define STLINK_OK			0x80
#define STLINK_FALSE			0x81
#define STLINK_CORE_RUNNING		0x80
#define STLINK_CORE_HALTED		0x81
#define STLINK_CORE_STAT_UNKNOWN	-1

#define STLINK_GET_VERSION		0xf1
#define STLINK_GET_CURRENT_MODE	0xf5
#define STLINK_GET_TARGET_VOLTAGE	0xF7

#define STLINK_DEBUG_COMMAND		0xF2
#define STLINK_DFU_COMMAND		0xF3
#define STLINK_DFU_EXIT		0x07
    // enter dfu could be 0x08?

    // STLINK_GET_CURRENT_MODE
#define STLINK_DEV_DFU_MODE		0x00
#define STLINK_DEV_MASS_MODE		0x01
#define STLINK_DEV_DEBUG_MODE		0x02
#define STLINK_DEV_UNKNOWN_MODE	-1

    // jtag mode cmds
#define STLINK_DEBUG_ENTER		0x20
#define STLINK_DEBUG_EXIT		0x21
#define STLINK_DEBUG_READCOREID	0x22
#define STLINK_DEBUG_GETSTATUS		0x01
#define STLINK_DEBUG_FORCEDEBUG	0x02
#define STLINK_DEBUG_RESETSYS		0x03
#define STLINK_DEBUG_READALLREGS	0x04
#define STLINK_DEBUG_READREG		0x05
#define STLINK_DEBUG_WRITEREG		0x06
#define STLINK_DEBUG_READMEM_32BIT	0x07
#define STLINK_DEBUG_WRITEMEM_32BIT	0x08
#define STLINK_DEBUG_RUNCORE		0x09
#define STLINK_DEBUG_STEPCORE		0x0a
#define STLINK_DEBUG_SETFP		0x0b
#define STLINK_DEBUG_WRITEMEM_8BIT	0x0d
#define STLINK_DEBUG_CLEARFP		0x0e
#define STLINK_DEBUG_WRITEDEBUGREG	0x0f
#define STLINK_DEBUG_ENTER_SWD		0xa3
#define STLINK_DEBUG_ENTER_JTAG	0x00

    // TODO - possible poor names...
#define STLINK_SWD_ENTER 0x30
#define STLINK_SWD_READCOREID 0x32  // TBD
#define STLINK_JTAG_WRITEDEBUG_32BIT 0x35
#define STLINK_JTAG_READDEBUG_32BIT 0x36
#define STLINK_JTAG_DRIVE_NRST 0x3c
#define STLINK_JTAG_DRIVE_NRST 0x3c

    // cortex m3 technical reference manual
#define CM3_REG_CPUID 0xE000ED00
#define CM3_REG_FP_CTRL 0xE0002000
#define CM3_REG_FP_COMP0 0xE0002008

    /* cortex core ids */
    // TODO clean this up...
#define STM32VL_CORE_ID 0x1ba01477
#define STM32L_CORE_ID 0x2ba01477
#define STM32F3_CORE_ID 0x2ba01477
#define STM32F4_CORE_ID 0x2ba01477
#define STM32F0_CORE_ID 0xbb11477
#define CORE_M3_R1 0x1BA00477
#define CORE_M3_R2 0x4BA00477
#define CORE_M4_R0 0x2BA01477

    /*
     * Chip IDs are explained in the appropriate programming manual for the
     * DBGMCU_IDCODE register (0xE0042000)
     */
    // stm32 chipids, only lower 12 bits..
#define STM32_CHIPID_F1_MEDIUM      0x410
#define STM32_CHIPID_F2             0x411
#define STM32_CHIPID_F1_LOW         0x412
#define STM32_CHIPID_F4             0x413
#define STM32_CHIPID_F1_HIGH        0x414
#define STM32_CHIPID_L4             0x415       /* Seen on L4x6 (RM0351) */
#define STM32_CHIPID_L1_MEDIUM      0x416
#define STM32_CHIPID_L0             0x417
#define STM32_CHIPID_F1_CONN        0x418
#define STM32_CHIPID_F4_HD          0x419
#define STM32_CHIPID_F1_VL_MEDIUM_LOW 0x420

#define STM32_CHIPID_F446           0x421
#define STM32_CHIPID_F3             0x422
#define STM32_CHIPID_F4_LP          0x423

#define STM32_CHIPID_F411RE         0x431

#define STM32_CHIPID_L1_MEDIUM_PLUS 0x427
#define STM32_CHIPID_F1_VL_HIGH     0x428
#define STM32_CHIPID_L1_CAT2        0x429

#define STM32_CHIPID_F1_XL          0x430

#define STM32_CHIPID_F37x           0x432
#define STM32_CHIPID_F4_DE          0x433
#define STM32_CHIPID_F4_DE          0x433

#define STM32_CHIPID_F4_DSI         0x434

#define STM32_CHIPID_L1_HIGH        0x436
#define STM32_CHIPID_L152_RE        0x437
#define STM32_CHIPID_F334           0x438

#define STM32_CHIPID_F3_SMALL       0x439
#define STM32_CHIPID_F0             0x440
#define STM32_CHIPID_F09X           0x442
#define STM32_CHIPID_F0_SMALL       0x444

#define STM32_CHIPID_F04            0x445

#define STM32_CHIPID_F303_HIGH      0x446

#define STM32_CHIPID_F0_CAN         0x448

#define STM32_CHIPID_F7             0x449

    /*
     * 0x436 is actually assigned to some L1 chips that are called "Medium-Plus"
     * and some that are called "High".  0x427 is assigned to the other "Medium-
     * plus" chips.  To make it a bit simpler we just call 427 MEDIUM_PLUS and
     * 0x436 HIGH.
     */

    // Constant STM32 memory map figures
#define STM32_FLASH_BASE 0x08000000
#define STM32_SRAM_BASE 0x20000000

    /* Cortex™-M3 Technical Reference Manual */
    /* Debug Halting Control and Status Register */
#define DHCSR 0xe000edf0
#define DCRSR 0xe000edf4
#define DCRDR 0xe000edf8
#define DBGKEY 0xa05f0000

    /* Enough space to hold both a V2 command or a V1 command packaged as generic scsi*/
#define C_BUF_LEN 32

    enum flash_type {
        FLASH_TYPE_UNKNOWN = 0,
        FLASH_TYPE_F0,
        FLASH_TYPE_L0,
        FLASH_TYPE_F4,
        FLASH_TYPE_L4,
    };

    typedef struct chip_params_ {
        uint32_t chip_id;
        char* description;
		enum flash_type flash_type;
        uint32_t flash_size_reg;
        uint32_t flash_pagesize;
        uint32_t sram_size;
        uint32_t bootrom_base, bootrom_size;
    } chip_params_t;


    // These maps are from a combination of the Programming Manuals, and
    // also the Reference manuals.  (flash size reg is normally in ref man)
    static const chip_params_t devices[] = {
        {
            //RM0385 and DS10916 document was used to find these paramaters
            .chip_id = STM32_CHIPID_F7,
            .description = "F7 device",
            .flash_type = FLASH_TYPE_F4,
            .flash_size_reg = 0x1ff0f442,      // section 41.2
            .flash_pagesize = 0x800,           // No flash pages
            .sram_size = 0x50000,              // "SRAM" byte size in hex from DS Fig 18
            .bootrom_base = 0x00100000,        // "System memory" starting address from DS Fig 18
            .bootrom_size = 0xEDC0             // "System memory" byte size in hex from DS Fig 18
        },
        { // table 2, PM0063
            .chip_id = STM32_CHIPID_F1_MEDIUM,
            .description = "F1 Medium-density device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7e0,
            .flash_pagesize = 0x400,
            .sram_size = 0x5000,
            .bootrom_base = 0x1ffff000,
            .bootrom_size = 0x800
        },
        {  // table 1, PM0059
            .chip_id = STM32_CHIPID_F2,
            .description = "F2 device",
            .flash_type = FLASH_TYPE_F4,
            .flash_size_reg = 0x1fff7a22, /* As in RM0033 Rev 5*/
            .flash_pagesize = 0x20000,
            .sram_size = 0x20000,
            .bootrom_base = 0x1fff0000,
            .bootrom_size = 0x7800
        },
        { // PM0063
            .chip_id = STM32_CHIPID_F1_LOW,
            .description = "F1 Low-density device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7e0,
            .flash_pagesize = 0x400,
            .sram_size = 0x2800,
            .bootrom_base = 0x1ffff000,
            .bootrom_size = 0x800
        },
        {
            .chip_id = STM32_CHIPID_F4,
            .description = "F4 device",
            .flash_type = FLASH_TYPE_F4,
            .flash_size_reg = 0x1FFF7A22,  /* As in rm0090 since Rev 2*/
            .flash_pagesize = 0x4000,
            .sram_size = 0x30000,
            .bootrom_base = 0x1fff0000,
            .bootrom_size = 0x7800
        },
        {
            .chip_id = STM32_CHIPID_F4_DSI,
            .description = "F46x and F47x device",
            .flash_type = FLASH_TYPE_F4,
            .flash_size_reg = 0x1FFF7A22,  /* As in rm0090 since Rev 2*/
            .flash_pagesize = 0x4000,
            .sram_size = 0x40000,
            .bootrom_base = 0x1fff0000,
            .bootrom_size = 0x7800
        },
        {
            .chip_id = STM32_CHIPID_F4_HD,
            .description = "F42x and F43x device",
            .flash_type = FLASH_TYPE_F4,
            .flash_size_reg = 0x1FFF7A22,  /* As in rm0090 since Rev 2*/
            .flash_pagesize = 0x4000,
            .sram_size = 0x40000,
            .bootrom_base = 0x1fff0000,
            .bootrom_size = 0x7800
        },
        {
            .chip_id = STM32_CHIPID_F4_LP,
            .description = "F4 device (low power)",
            .flash_type = FLASH_TYPE_F4,
            .flash_size_reg = 0x1FFF7A22,
            .flash_pagesize = 0x4000,
            .sram_size = 0x10000,
            .bootrom_base = 0x1fff0000,
            .bootrom_size = 0x7800
        },
        {
            .chip_id = STM32_CHIPID_F411RE,
            .description = "F4 device (low power) - stm32f411re",
            .flash_type = FLASH_TYPE_F4,
            .flash_size_reg = 0x1FFF7A22,
            .flash_pagesize = 0x4000,
            .sram_size = 0x20000,
            .bootrom_base = 0x1fff0000,
            .bootrom_size = 0x7800
        },
        {
            .chip_id = STM32_CHIPID_F4_DE,
            .description = "F4 device (Dynamic Efficency)",
            .flash_type = FLASH_TYPE_F4,
            .flash_size_reg = 0x1FFF7A22,
            .flash_pagesize = 0x4000,
            .sram_size = 0x18000,
            .bootrom_base = 0x1fff0000,
            .bootrom_size = 0x7800
        },
        {
            .chip_id = STM32_CHIPID_F1_HIGH,
            .description = "F1 High-density device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7e0,
            .flash_pagesize = 0x800,
            .sram_size = 0x10000,
            .bootrom_base = 0x1ffff000,
            .bootrom_size = 0x800
        },
        {
            // This ignores the EEPROM! (and uses the page erase size,
            // not the sector write protection...)
            .chip_id = STM32_CHIPID_L1_MEDIUM,
            .description = "L1 Med-density device",
            .flash_type = FLASH_TYPE_L0,
            .flash_size_reg = 0x1ff8004c,
            .flash_pagesize = 0x100,
            .sram_size = 0x4000,
            .bootrom_base = 0x1ff00000,
            .bootrom_size = 0x1000
        },
        {
            .chip_id = STM32_CHIPID_L1_CAT2,
            .description = "L1 Cat.2 device",
            .flash_type = FLASH_TYPE_L0,
            .flash_size_reg = 0x1ff8004c,
            .flash_pagesize = 0x100,
            .sram_size = 0x8000,
            .bootrom_base = 0x1ff00000,
            .bootrom_size = 0x1000
        },
        {
            .chip_id = STM32_CHIPID_L1_MEDIUM_PLUS,
            .description = "L1 Medium-Plus-density device",
            .flash_type = FLASH_TYPE_L0,
            .flash_size_reg = 0x1ff800cc,
            .flash_pagesize = 0x100,
            .sram_size = 0x8000,/*Not completely clear if there are some with 48K*/
            .bootrom_base = 0x1ff00000,
            .bootrom_size = 0x1000
        },
        {
            .chip_id = STM32_CHIPID_L1_HIGH,
            .description = "L1 High-density device",
            .flash_type = FLASH_TYPE_L0,
            .flash_size_reg = 0x1ff800cc,
            .flash_pagesize = 0x100,
            .sram_size = 0xC000, /*Not completely clear if there are some with 32K*/
            .bootrom_base = 0x1ff00000,
            .bootrom_size = 0x1000
        },
        {
            .chip_id = STM32_CHIPID_L152_RE,
            .description = "L152RE",
            .flash_type = FLASH_TYPE_L0,
            .flash_size_reg = 0x1ff800cc,
            .flash_pagesize = 0x100,
            .sram_size = 0x14000, /*Not completely clear if there are some with 32K*/
            .bootrom_base = 0x1ff00000,
            .bootrom_size = 0x1000
        },
        {
            .chip_id = STM32_CHIPID_F1_CONN,
            .description = "F1 Connectivity line device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7e0,
            .flash_pagesize = 0x800,
            .sram_size = 0x10000,
            .bootrom_base = 0x1fffb000,
            .bootrom_size = 0x4800
        },
        {//Low and Medium density VL have same chipid. RM0041 25.6.1
            .chip_id = STM32_CHIPID_F1_VL_MEDIUM_LOW,
            .description = "F1 Medium/Low-density Value Line device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7e0,
            .flash_pagesize = 0x400,
            .sram_size = 0x2000,//0x1000 for low density devices
            .bootrom_base = 0x1ffff000,
            .bootrom_size = 0x800
        },
        {
            // STM32F446x family. Support based on DM00135183.pdf (RM0390) document.
            .chip_id = STM32_CHIPID_F446,
            .description = "F446 device",
            .flash_type = FLASH_TYPE_F4,
            .flash_size_reg = 0x1fff7a22,
            .flash_pagesize = 0x20000,
            .sram_size = 0x20000,
            .bootrom_base = 0x1fff0000,
            .bootrom_size = 0x7800
        },
        {
            // This is STK32F303VCT6 device from STM32 F3 Discovery board.
            // Support based on DM00043574.pdf (RM0316) document.
            .chip_id = STM32_CHIPID_F3,
            .description = "F3 device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7cc,
            .flash_pagesize = 0x800,
            .sram_size = 0xa000,
            .bootrom_base = 0x1ffff000,
            .bootrom_size = 0x800
        },
        {
            // This is STK32F373VCT6 device from STM32 F373 eval board
            // Support based on 303 above (37x and 30x have same memory map)
            .chip_id = STM32_CHIPID_F37x,
            .description = "F3 device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7cc,
            .flash_pagesize = 0x800,
            .sram_size = 0xa000,
            .bootrom_base = 0x1ffff000,
            .bootrom_size = 0x800
        },
        {
            .chip_id = STM32_CHIPID_F1_VL_HIGH,
            .description = "F1 High-density value line device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7e0,
            .flash_pagesize = 0x800,
            .sram_size = 0x8000,
            .bootrom_base = 0x1ffff000,
            .bootrom_size = 0x800
        },
        {
            .chip_id = STM32_CHIPID_F1_XL,
            .description = "F1 XL-density device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7e0,
            .flash_pagesize = 0x800,
            .sram_size = 0x18000,
            .bootrom_base = 0x1fffe000,
            .bootrom_size = 0x1800
        },
        {
            //Use this as an example for mapping future chips:
            //RM0091 document was used to find these paramaters
            .chip_id = STM32_CHIPID_F0_CAN,
            .description = "F07x device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7cc,      // "Flash size data register" (pg735)
            .flash_pagesize = 0x800,           // Page sizes listed in Table 4
            .sram_size = 0x4000,               // "SRAM" byte size in hex from Table 2
            .bootrom_base = 0x1fffC800,                // "System memory" starting address from Table 2
            .bootrom_size = 0x3000             // "System memory" byte size in hex from Table 2
        },
        {
            //Use this as an example for mapping future chips:
            //RM0091 document was used to find these paramaters
            .chip_id = STM32_CHIPID_F0,
            .description = "F0 device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7cc,	// "Flash size data register" (pg735)
            .flash_pagesize = 0x400,		// Page sizes listed in Table 4
            .sram_size = 0x2000,		// "SRAM" byte size in hex from Table 2
            .bootrom_base = 0x1fffec00,		// "System memory" starting address from Table 2
            .bootrom_size = 0xC00 		// "System memory" byte size in hex from Table 2
        },
	{
            .chip_id = STM32_CHIPID_F09X,
            .description = "F09X device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7cc,	// "Flash size data register" (pg735)
            .flash_pagesize = 0x800,		// Page sizes listed in Table 4 (pg 56)
            .sram_size = 0x8000,		// "SRAM" byte size in hex from Table 2 (pg 50)
            .bootrom_base = 0x1fffd800,		// "System memory" starting address from Table 2
            .bootrom_size = 0x2000 		// "System memory" byte size in hex from Table 2
        },
        {
            //Use this as an example for mapping future chips:
            //RM0091 document was used to find these paramaters
            .chip_id = STM32_CHIPID_F04,
            .description = "F04x device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7cc,	// "Flash size data register" (pg735)
            .flash_pagesize = 0x400,		// Page sizes listed in Table 4
            .sram_size = 0x1800,		// "SRAM" byte size in hex from Table 2
            .bootrom_base = 0x1fffec00,		// "System memory" starting address from Table 2
            .bootrom_size = 0xC00 		// "System memory" byte size in hex from Table 2
        },
        {
            //Use this as an example for mapping future chips:
            //RM0091 document was used to find these paramaters
            .chip_id = STM32_CHIPID_F0_SMALL,
            .description = "F0 small device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7cc,	// "Flash size data register" (pg735)
            .flash_pagesize = 0x400,		// Page sizes listed in Table 4
            .sram_size = 0x1000,		// "SRAM" byte size in hex from Table 2
            .bootrom_base = 0x1fffec00,		// "System memory" starting address from Table 2
            .bootrom_size = 0xC00 		// "System memory" byte size in hex from Table 2
        },
        {
            // STM32F30x
            .chip_id = STM32_CHIPID_F3_SMALL,
            .description = "F3 small device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7cc,
            .flash_pagesize = 0x800,
            .sram_size = 0xa000,
            .bootrom_base = 0x1fffd800,
            .bootrom_size = 0x2000
        },
        {
            // STM32L0x
            // RM0367,RM0377 documents was used to find these parameters
            .chip_id = STM32_CHIPID_L0,
            .description = "L0x3 device",
            .flash_type = FLASH_TYPE_L0,
            .flash_size_reg = 0x1ff8007c,
            .flash_pagesize = 0x80,
            .sram_size = 0x2000,
            .bootrom_base = 0x1ff0000,
            .bootrom_size = 0x1000
        },
        {
            // STM32F334
            // RM0364 document was used to find these parameters
            .chip_id = STM32_CHIPID_F334,
            .description = "F334 device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7cc,
            .flash_pagesize = 0x800,
            .sram_size = 0x3000,
            .bootrom_base = 0x1fffd800,
            .bootrom_size = 0x2000
        },
        {
            // This is STK32F303RET6 device from STM32 F3 Nucelo board.
            // Support based on DM00043574.pdf (RM0316) document rev 5.
            .chip_id = STM32_CHIPID_F303_HIGH,
            .description = "F303 high density device",
            .flash_type = FLASH_TYPE_F0,
            .flash_size_reg = 0x1ffff7cc,    // 34.2.1 Flash size data register
            .flash_pagesize = 0x800,         // 4.2.1 Flash memory organization
            .sram_size = 0x10000,            // 3.3 Embedded SRAM
            .bootrom_base = 0x1fffd800,      // 3.3.2 / Table 4 System Memory
            .bootrom_size = 0x2000
        },
        {
            // STM32L4x6
            // From RM0351.
            .chip_id = STM32_CHIPID_L4,
            .description = "L4 device",
            .flash_type = FLASH_TYPE_L4,
            .flash_size_reg = 0x1fff75e0,    // "Flash size data register" (sec 45.2, page 1671)
            .flash_pagesize = 0x800,         // 2K (sec 3.2, page 78; also appears in sec 3.3.1 and tables 4-6 on pages 79-81)
            // SRAM1 is "up to" 96k in the standard Cortex-M memory map;
            // SRAM2 is 32k mapped at at 0x10000000 (sec 2.3, page 73 for
            // sizes; table 2, page 74 for SRAM2 location)
            .sram_size = 0x18000,
            .bootrom_base = 0x1fff0000,      // Tables 4-6, pages 80-81 (Bank 1 system memory)
            .bootrom_size = 0x7000           // 28k (per bank), same source as base
        },

 };


    typedef struct {
        uint32_t r[16];
        uint32_t s[32];
        uint32_t xpsr;
        uint32_t main_sp;
        uint32_t process_sp;
        uint32_t rw;
        uint32_t rw2;
        uint8_t control;
        uint8_t faultmask;
        uint8_t basepri;
        uint8_t primask;
        uint32_t fpscr;
    } reg;

    typedef uint32_t stm32_addr_t;

    typedef struct _cortex_m3_cpuid_ {
        uint16_t implementer_id;
        uint16_t variant;
        uint16_t part;
        uint8_t revision;
    } cortex_m3_cpuid_t;

    typedef struct stlink_version_ {
        uint32_t stlink_v;
        uint32_t jtag_v;
        uint32_t swim_v;
        uint32_t st_vid;
        uint32_t stlink_pid;
    } stlink_version_t;

    typedef struct flash_loader {
        stm32_addr_t loader_addr; /* loader sram adddr */
        stm32_addr_t buf_addr; /* buffer sram address */
    } flash_loader_t;

    enum transport_type {
        TRANSPORT_TYPE_ZERO = 0,
        TRANSPORT_TYPE_LIBSG,
        TRANSPORT_TYPE_LIBUSB,
        TRANSPORT_TYPE_INVALID
    };

    typedef struct _stlink stlink_t;

    typedef struct _stlink_backend {
        void (*close) (stlink_t * sl);
        int (*exit_debug_mode) (stlink_t * sl);
        int (*enter_swd_mode) (stlink_t * sl);
        int (*enter_jtag_mode) (stlink_t * stl);
        int (*exit_dfu_mode) (stlink_t * stl);
        int (*core_id) (stlink_t * stl);
        int (*reset) (stlink_t * stl);
        int (*jtag_reset) (stlink_t * stl, int value);
        int (*run) (stlink_t * stl);
        int (*status) (stlink_t * stl);
        int (*version) (stlink_t *sl);
        int (*read_debug32) (stlink_t *sl, uint32_t addr, uint32_t *data);
        int (*read_mem32) (stlink_t *sl, uint32_t addr, uint16_t len);
        int (*write_debug32) (stlink_t *sl, uint32_t addr, uint32_t data);
        int (*write_mem32) (stlink_t *sl, uint32_t addr, uint16_t len);
        int (*write_mem8) (stlink_t *sl, uint32_t addr, uint16_t len);
        int (*read_all_regs) (stlink_t *sl, reg * regp);
        int (*read_reg) (stlink_t *sl, int r_idx, reg * regp);
        int (*read_all_unsupported_regs) (stlink_t *sl, reg *regp);
        int (*read_unsupported_reg) (stlink_t *sl, int r_idx, reg *regp);
        int (*write_unsupported_reg) (stlink_t *sl, uint32_t value, int idx, reg *regp);
        int (*write_reg) (stlink_t *sl, uint32_t reg, int idx);
        int (*step) (stlink_t * stl);
        int (*current_mode) (stlink_t * stl);
        int (*force_debug) (stlink_t *sl);
        int32_t (*target_voltage) (stlink_t *sl);
    } stlink_backend_t;

    struct _stlink {
        struct _stlink_backend *backend;
        void *backend_data;

        // Room for the command header
        unsigned char c_buf[C_BUF_LEN];
        // Data transferred from or to device
        unsigned char q_buf[Q_BUF_LEN];
        int q_len;

        // transport layer verboseness: 0 for no debug info, 10 for lots
        int verbose;
        uint32_t core_id;
        uint32_t chip_id;
        int core_stat;

#define STM32_FLASH_PGSZ 1024
#define STM32L_FLASH_PGSZ 256

#define STM32F4_FLASH_PGSZ 16384
#define STM32F4_FLASH_SIZE (128 * 1024 * 8)

        enum flash_type flash_type;
        stm32_addr_t flash_base;
        size_t flash_size;
        size_t flash_pgsz;

        /* sram settings */
#define STM32_SRAM_SIZE (8 * 1024)
#define STM32L_SRAM_SIZE (16 * 1024)
        stm32_addr_t sram_base;
        size_t sram_size;

        // bootloader
        stm32_addr_t sys_base;
        size_t sys_size;

        struct stlink_version_ version;
    };

    //stlink_t* stlink_quirk_open(const char *dev_name, const int verbose);

    // delegated functions...
    int stlink_enter_swd_mode(stlink_t *sl);
    int stlink_enter_jtag_mode(stlink_t *sl);
    int stlink_exit_debug_mode(stlink_t *sl);
    int stlink_exit_dfu_mode(stlink_t *sl);
    void stlink_close(stlink_t *sl);
    int stlink_core_id(stlink_t *sl);
    int stlink_reset(stlink_t *sl);
    int stlink_jtag_reset(stlink_t *sl, int value);
    int stlink_run(stlink_t *sl);
    int stlink_status(stlink_t *sl);
    int stlink_version(stlink_t *sl);
    int stlink_read_debug32(stlink_t *sl, uint32_t addr, uint32_t *data);
    int stlink_read_mem32(stlink_t *sl, uint32_t addr, uint16_t len);
    int stlink_write_debug32(stlink_t *sl, uint32_t addr, uint32_t data);
    int stlink_write_mem32(stlink_t *sl, uint32_t addr, uint16_t len);
    int stlink_write_mem8(stlink_t *sl, uint32_t addr, uint16_t len);
    int stlink_read_all_regs(stlink_t *sl, reg *regp);
    int stlink_read_all_unsupported_regs(stlink_t *sl, reg *regp);
    int stlink_read_reg(stlink_t *sl, int r_idx, reg *regp);
    int stlink_read_unsupported_reg(stlink_t *sl, int r_idx, reg *regp);
    int stlink_write_unsupported_reg(stlink_t *sl, uint32_t value, int r_idx, reg *regp);
    int stlink_write_reg(stlink_t *sl, uint32_t reg, int idx);
    int stlink_step(stlink_t *sl);
    int stlink_current_mode(stlink_t *sl);
    int stlink_force_debug(stlink_t *sl);
    int stlink_target_voltage(stlink_t *sl);


    // unprocessed
    int stlink_erase_flash_mass(stlink_t* sl);
    int stlink_write_flash(stlink_t* sl, stm32_addr_t address, uint8_t* data, uint32_t length, uint8_t eraseonly);
    int stlink_fwrite_flash(stlink_t *sl, const char* path, stm32_addr_t addr);
    int stlink_fwrite_sram(stlink_t *sl, const char* path, stm32_addr_t addr);
    int stlink_verify_write_flash(stlink_t *sl, stm32_addr_t address, uint8_t *data, uint32_t length);

    // PUBLIC
    int stlink_chip_id(stlink_t *sl, uint32_t *chip_id);
    int stlink_cpu_id(stlink_t *sl, cortex_m3_cpuid_t *cpuid);

    // privates, publics, the rest....
    // TODO sort what is private, and what is not
    int stlink_erase_flash_page(stlink_t* sl, stm32_addr_t flashaddr);
    uint32_t stlink_calculate_pagesize(stlink_t *sl, uint32_t flashaddr);
    uint16_t read_uint16(const unsigned char *c, const int pt);
    void stlink_core_stat(stlink_t *sl);
    void stlink_print_data(stlink_t *sl);
    unsigned int is_bigendian(void);
    uint32_t read_uint32(const unsigned char *c, const int pt);
    void write_uint32(unsigned char* buf, uint32_t ui);
    void write_uint16(unsigned char* buf, uint16_t ui);
    unsigned int is_core_halted(stlink_t *sl);
    int write_buffer_to_sram(stlink_t *sl, flash_loader_t* fl, const uint8_t* buf, size_t size);
    int write_loader_to_sram(stlink_t *sl, stm32_addr_t* addr, size_t* size);
    int stlink_fread(stlink_t* sl, const char* path, stm32_addr_t addr, size_t size);
    int run_flash_loader(stlink_t *sl, flash_loader_t* fl, stm32_addr_t target, const uint8_t* buf, size_t size);
    int stlink_load_device_params(stlink_t *sl);



#include "stlink-sg.h"
#include "stlink-usb.h"



#ifdef	__cplusplus
}
#endif

#endif	/* STLINK_COMMON_H */
