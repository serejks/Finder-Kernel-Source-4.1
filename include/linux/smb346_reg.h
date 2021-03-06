#ifndef __SMB346_REGISTER_H
#define __SMB346_REGISTER_H

/*charge current register configuration 00h*/
#define CHARGE_CURRENT_REGISTER     0x00
//unsigned char    charge_current_config;

#ifdef CHARGE_CURRENT_REGISTER
#define FAST_CHARGE_CURRENT_350MA    0x0<<5
#define FAST_CHARGE_CURRENT_450MA    0x1<<5
#define FAST_CHARGE_CURRENT_600MA    0x2<<5
#define FAST_CHARGE_CURRENT_750MA    0x3<<5
#define FAST_CHARGE_CURRENT_900MA    0x4<<5
#define FAST_CHARGE_CURRENT_1000MA    0x5<<5
#define FAST_CHARGE_CURRENT_1100MA    0x6<<5
#define FAST_CHARGE_CURRENT_1250MA    0x7<<5

#define PRE_CHARGE_CURRENT_50MA    00000000B
#define PRE_CHARGE_CURRENT_75MA    00001000B
#define PRE_CHARGE_CURRENT_100MA    00010000B
#define PRE_CHARGE_CURRENT_125MA    00011000B

#define TERMINATION_CURRENT_37P5MA    0x0
#define TERMINATION_CURRENT_50MA    0x1
#define TERMINATION_CURRENT_100MA    0x2
#define TERMINATION_CURRENT_150MA    0x3
#define TERMINATION_CURRENT_200MA    0x4
#define TERMINATION_CURRENT_250MA    0x5
#define TERMINATION_CURRENT_500MA    0x6
#define TERMINATION_CURRENT_600MA    0x7
#endif

/*input current limit register configuration 01h*/
#define INPUT_CURRENT_LIMIT_REGISTER    0x01

#ifdef INPUT_CURRENT_LIMIT_REGISTER
#define DCIN_INPUT_CURRENT_LIMIT_300MA    0x0<<5
#define DCIN_INPUT_CURRENT_LIMIT_500MA    0x1<<5
#define DCIN_INPUT_CURRENT_LIMIT_700MA    0x2<<5
#define DCIN_INPUT_CURRENT_LIMIT_900MA    0x3<<5
#define DCIN_INPUT_CURRENT_LIMIT_1200MA    0x4<<5
#define DCIN_INPUT_CURRENT_LIMIT_1500MA    0x5<<5
#define DCIN_INPUT_CURRENT_LIMIT_1800MA    0x6<<5
#define DCIN_INPUT_CURRENT_LIMIT_2000MA    0x7<<5
#define DCIN_INPUT_CURRENT_LIMIT_2200MA    0x8<<5
#define DCIN_INPUT_CURRENT_LIMIT_2500MA    0x9<<5

#define USBIN_INPUT_CURRENT_LIMIT_300MA    0x0
#define USBIN_INPUT_CURRENT_LIMIT_500MA    0x1
#define USBIN_INPUT_CURRENT_LIMIT_700MA    0x2
#define USBIN_INPUT_CURRENT_LIMIT_900MA    0x3
#define USBIN_INPUT_CURRENT_LIMIT_1200MA    0x4
#define USBIN_INPUT_CURRENT_LIMIT_1500MA    0x5
#define USBIN_INPUT_CURRENT_LIMIT_1800MA    0x6
#define USBIN_INPUT_CURRENT_LIMIT_2000MA    0x7
#define USBIN_INPUT_CURRENT_LIMIT_2200MA    0x8
#define USBIN_INPUT_CURRENT_LIMIT_2500MA    0x9

#define USBIN_INPUT_CURRENT_LIMIT_MASK    0xff
#define USBIN_DCIN_INPUT_CURRENT_LIMIT_MASK    0xff

#define USBIN_DCIN_INPUT_CURRENT_900MA    0x33
#define USBIN_DCIN_INPUT_CURRENT_500MA    0x11
#define USBIN_DCIN_INPUT_CURRENT_700MA    0x22
#define USBIN_DCIN_INPUT_CURRENT_300MA    0x00

#endif

/*various function register configuration 02h*/
#define VARIOUS_FUNCTION_REGISTER    0x02

#ifdef VARIOUS_FUNCTION_REGISTER
#define INPUT_TO_SYSTEM_FET_ON_OFF_CONTROLLED_BY_SUSP_PIN    0x0<<7
#define INPUT_TO_SYSTEM_FET_ON_OFF_CONTROLLED_BY_REGISTER    0x1<<7

#define MAX_SYSTEM_EQUAL_VFLT_ADD_0P1V    0x0<<5
#define MAX_SYSTEM_EQUAL_VFLT_ADD_0P2V    0x1<<5

#define AUTOMATIC_INPUT_CURRENT_LIMIT_DISABLED    0x0<<4
#define AUTOMATIC_INPUT_CURRENT_LIMIT_ENABLED    0x1<<4

#define AUTOMATIC_INPUT_CURRENT_LIMIT_DETECTION_THRESHOLD_4P25V    0x0<<3
#define AUTOMATIC_INPUT_CURRENT_LIMIT_DETECTION_THRESHOLD_4P50V    0x1<<3
#define AUTOMATIC_INPUT_CURRENT_LIMIT_DETECTION_THRESHOLD    0x1<<3


#define INPUT_SOUCE_PRIORITY_DCIN    0x0<<2
#define INPUT_SOUCE_PRIORITY_USBIN    0x1<<2

#define BATTERY_OV_NOT_END_CHARGE_CYCLE    0x0<<1
#define BATTERY_OV_END_CHARGE_CYCLE    0x1<<1

#define VCHG_FUNCTION_DISABLED    0x0
#define VCHG_FUNCTION_ENABLED    0x1
#endif

/*float votage register configuration 03h*/
#define FLOAT_VOTAGE_REGISTER    0x03

#ifdef FLOAT_VOTAGE_REGISTER
#define PRE_CHARGE_TO_FAST_CHARGE_VOTAGE_THRESTOLD_2P4V    00000000B
#define PRE_CHARGE_TO_FAST_CHARGE_VOTAGE_THRESTOLD_2P6V    01000000B
#define PRE_CHARGE_TO_FAST_CHARGE_VOTAGE_THRESTOLD_2P8V    10000000B
#define PRE_CHARGE_TO_FAST_CHARGE_VOTAGE_THRESTOLD_3P0V    11000000B

#define FLOAT_VOTAGE_3500MV    00000000B
#define FLOAT_VOTAGE_3520MV    00000001B
#define FLOAT_VOTAGE_3540MV    00000010B
#define FLOAT_VOTAGE_3560MV    00000011B
#define FLOAT_VOTAGE_3580MV    00000100B

#define FLOAT_VOTAGE_3600MV    00000101B
#define FLOAT_VOTAGE_3620MV    00000110B
#define FLOAT_VOTAGE_3640MV    00000111B
#define FLOAT_VOTAGE_3660MV    00001000B
#define FLOAT_VOTAGE_3680MV    00001001B

#define FLOAT_VOTAGE_3700MV    00001010B
#define FLOAT_VOTAGE_3720MV    00001011B
#define FLOAT_VOTAGE_3740MV    00001100B
#define FLOAT_VOTAGE_3760MV    00001101B
#define FLOAT_VOTAGE_3780MV    00001110B

#define FLOAT_VOTAGE_3800MV    00001111B
#define FLOAT_VOTAGE_3820MV    00010000B
#define FLOAT_VOTAGE_3840MV    00010001B
#define FLOAT_VOTAGE_3860MV    00010010B
#define FLOAT_VOTAGE_3880MV    00010011B

#define FLOAT_VOTAGE_3900MV    00010100B
#define FLOAT_VOTAGE_3920MV    00010101B
#define FLOAT_VOTAGE_3940MV    00010110B
#define FLOAT_VOTAGE_3960MV    00010111B
#define FLOAT_VOTAGE_3980MV    00011000B

#define FLOAT_VOTAGE_4000MV    0x19
#define FLOAT_VOTAGE_4020MV    00011010B
#define FLOAT_VOTAGE_4040MV    00011011B
#define FLOAT_VOTAGE_4060MV    00011100B
#define FLOAT_VOTAGE_4080MV    00011101B

#define FLOAT_VOTAGE_4100MV    0x1e
#define FLOAT_VOTAGE_4120MV    00011111B
#define FLOAT_VOTAGE_4140MV    00100000B
#define FLOAT_VOTAGE_4160MV    00100001B
#define FLOAT_VOTAGE_4180MV    00100010B

#define FLOAT_VOTAGE_4200MV    0x23
#define FLOAT_VOTAGE_4220MV    0x24
#define FLOAT_VOTAGE_4240MV    00100101B
#define FLOAT_VOTAGE_4260MV    00100110B
#define FLOAT_VOTAGE_4280MV    00100111B

#define FLOAT_VOTAGE_4300MV    00101000B
#define FLOAT_VOTAGE_4320MV    00101001B
#define FLOAT_VOTAGE_4340MV    00101010B
#define FLOAT_VOTAGE_4360MV    00101011B
#define FLOAT_VOTAGE_4380MV    00101100B

#define FLOAT_VOTAGE_4400MV    00101101B
#define FLOAT_VOTAGE_4420MV    00101110B
#define FLOAT_VOTAGE_4440MV    00101111B
#define FLOAT_VOTAGE_4460MV    00110000B
#define FLOAT_VOTAGE_4480MV    00110001B

#define FLOAT_VOTAGE_4500MV    0x32 //00110010B

#define FLOAT_VOTAGE_MASK    0x3f
#endif

/*charge control register configuration 04h*/
#define CHARGE_CONTROL_REGISTER    0x04

#ifdef CHARGE_CONTROL_REGISTER
#define AUTOMATIC_RECHARGE_DISABLED    0x1<<7
#define AUTOMATIC_RECHARGE_ENABLED    0x0<<7

#define ALLOWED_TO_END_A_CHARGE_CYCLE    00000000B
#define NOT_ALLOWED_TO_END_A_CHARGE_CYCLE    01000000B

#define  BATTERY_MISSING_DETECTION_DISABLED   00000000B
#define  BATTERY_MISSING_DETECTION_VIA_BMD_EVERY_3SECS   00010000B
#define  BATTERY_MISSING_DETECTION_VIA_BMD   00100000B
#define  BATTERY_MISSING_DETECTION_VIA_THERM_IO   00110000B

#define  AUTO_RECHARGE_THRESHOLD_50MV  00000000B
#define  AUTO_RECHARGE_THRESHOLD_100MV  00001000B

#define  AUTO_POWER_SOURCE_DETECTION_DISABLED  00000000B
#define  AUTO_POWER_SOURCE_DETECTION_ENABLED  00000100B

#define  NC_CHARGER_DETECTION_VIA_APSD_DISABLED    00000000B
#define  NC_CHARGER_DETECTION_VIA_APSD_ENABLED    00000010B

#define SECONDARY_PRIMARY_INPUT_IN_OVLO_NOT_ACCEPTED    00000000B
#define SECONDARY_PRIMARY_INPUT_IN_OVLO_ACCEPTED    00000001B
#endif

/*STAT and timer control register 05h */
#define STAT_AND_TIMER_CONTROL_REGISTER    0x05

#ifdef STAT_AND_TIMER_CONTROL_REGISTER
#define STAT_OUTPUT_POLARITY_ACTIVE_LOW    00000000B
#define STAT_OUTPUT_POLARITY_ACTIVE_HIGH    10000000B

#define STAT_OUTPUT_MODE_INDICATES_CHARGING_STATE    00000000B
#define STAT_OUTPUT_MODE_USB_FAIL    01000000B

#define STAT_OUTPUT_CTL_ENABLED    00000000B
#define STAT_OUTPUT_CTL_DISABLED    00100000B

#define NC_CHARGER_INPUT_CURRENT_LIMIT_100MA    00000000B
#define NC_CHARGER_INPUT_CURRENT_LIMIT_HC_SETTING    00010000B

#define COMPLETE_CHARGE_TIMEOUT_382MIN    00000000B
#define COMPLETE_CHARGE_TIMEOUT_764MIN    00000100B
#define COMPLETE_CHARGE_TIMEOUT_1527MIN    00001000B
#define COMPLETE_CHARGE_TIMEOUT_DISABLED    00001100B

#define PRE_CHARGE_TIMEOUT_48MIN    00000000B
#define PRE_CHARGE_TIMEOUT_95MIN    00000001B
#define PRE_CHARGE_TIMEOUT_191MIN    00000010B
#define PRE_CHARGE_TIMEOUT_DISABLED    00000011B
#endif

/*pin and  enable control register 06h */
#define PIN_AND_ENABLE_CONTROL_REGISTER    0x06

#ifdef PIN_AND_ENABLE_CONTROL_REGISTER
#define LED_BLINKING_FUNCTION_DISABLED    00000000B
#define LED_BLINKING_FUNCTION_ENABLED    10000000B

#define I2C_CONTROL_0_TO_DISABLE_CHARGER    0x0<<5
#define I2C_CONTROL_0_TO_ENABLE_CHARGER    0x1<<5
#define PIN_CONTROL_ACTIVE_HIGH    0x2<<5
#define PIN_CONTROL_ACTIVE_LOW    0x3<<5

#define USB51HC_REGISTER_CONTROL    00000000B
#define USB51HC_PIN_CONTROL    00010000B

#define USB51HC_TRI_STATE_INPUT    00000000B
#define USB51HC_DUAL_STATE_INPUT    00001000B

#define CHARGE_ERROR_DONOT_TRIGGER_IRQ    00001000B
#define CHARGE_ERROR_TRIGGER_IRQ    00000100B

#define APSD_DONE_DONOT_TRIGGER_IRQ    00000000B
#define APSD_DONE_TRIGGER_IRQ    00000010B

#define DCIN_INPUT_PRE_BIAS_DISABLED    00000000B
#define DCIN_INPUT_PRE_BIAS_ENABLED    00000001B
#endif

/*therm and system control register 07h */
#define THERM_AND_SYSTEM_CONTROL_REGISTER    0x07

#ifdef THERM_AND_SYSTEM_CONTROL_REGISTER
#define SYSTEM_TRACKING_VOLTAGE__VBATT_ADD_100MV    0x0<<7
#define SYSTEM_TRACKING_VOLTAGE__VBATT_ADD_200MV    0x1<<7

#define MIN_SYSTEM_VOLTAGE__3P15V_OR_3P45V    0x0<<6
#define MIN_SYSTEM_VOLTAGE__3P60V_OR_3P75V    0x1<<6

#define THERM_MONITOR_SELECTION__USBIN_SUPPLY    0x0<<5
#define THERM_MONITOR_SELECTION__VDDCAP_SUPPLY    0x1<<5

#define THERMISTER_MONITOR_ENABLED    0x0<<4
#define THERMISTER_MONITOR_DISABLED    0x1<<4

#define SOFT_COLD_TEMP_LIMIT__NO_RESPONSE    0x0<<2
#define SOFT_COLD_TEMP_LIMIT__CHARGE_CURRENT_COMPENSATION    0x1<<2
#define SOFT_COLD_TEMP_LIMIT__FLOAT_VOLTAGE_COMPENSATION    0x2<<2
#define SOFT_COLD_TEMP_LIMIT__CHARGE_CURRENT_AND_FLOAT_VOLTAGE_COMPENSATION   0x3<<2

#define SOFT_HOT_TEMP_LIMIT__NO_RESPONSE    0x0
#define SOFT_HOT_TEMP_LIMIT__CHARGE_CURRENT_COMPENSATION    0x1
#define SOFT_HOT_TEMP_LIMIT__FLOAT_VOLTAGE_COMPENSATION    0x2
#define SOFT_HOT_TEMP_LIMIT__CHARGE_CURRENT_AND_FLOAT_VOLTAGE_COMPENSATION    0x3
#endif

/*SYSOK and USB3.0 control register 08h */
#define SYSOK_AND_USB3P0_CONTROL_REGISTER    0x08

#ifdef SYSOK_AND_USB3P0_CONTROL_REGISTER
#define SYSOK_OUTPUT__INOK_OPERATION    00000000B
#define SYSOK_OUTPUT__SYSOK_OPERATION_OPTION_A    01000000B
#define SYSOK_OUTPUT__SYSOK_OPERATION_OPTION_B    10000000B
#define SYSOK_OUTPUT__CHG_DET_N_OPERATION    11000000B

#define USB2P0_INPUT_CURRENT_LIMIT    00000000B
#define USB3P0_INPUT_CURRENT_LIMIT    00100000B

#define FLOAT_VOLTAGE_COMPENSATION__VFLT_SUB_60MV    00000000B
#define FLOAT_VOLTAGE_COMPENSATION__VFLT_SUB_120MV    00001000B
#define FLOAT_VOLTAGE_COMPENSATION__VFLT_SUB_180MV    00010000B
#define FLOAT_VOLTAGE_COMPENSATION__VFLT_SUB_240MV    00011000B

#define CHARGEING_SUSPEND_WHEN_BATTERY_TEMPERATURE_OUT_LIMIT    00000000B
#define CHARGEING_NOT_SUSPEND_WHEN_BATTERY_TEMPERATURE_OUT_LIMIT    00000100B

#define PRE_CHARGE_TO_FAST_CHARGE_THRESHOLD_ENABLED    00000000B
#define PRE_CHARGE_TO_FAST_CHARGE_THRESHOLD_DISABLED    00000010B

#define INOK_POLARITY_ACTIVE_LOW    00000000B
#define INOK_POLARITY_ACTIVE_HIGH    00000001B
#endif

/*other control A register 09h */
#define OTHER_CONTROL_REGISTER    0x09

#ifdef OTHER_CONTROL_REGISTER
#define RID_DISABLED__OTG_I2C_CONTROL    00000000B
#define RID_DISABLED__OTG_PIN_CONTROL    01000000B
#define RID_ENABLED__OTG_I2C_CONTROL    10000000B
#define RID_ENABLED__OTG_PIN_CONTROL    11000000B

#define OTG_PIN_POLARITY_ACTIVE_HIGH    00000000B
#define OTG_PIN_POLARITY_ACTIVE_LOW    00100000B

#define MIN_SYSTEM_VOLTAGE__3P45V_OR_3P60V    00000000B
#define MIN_SYSTEM_VOLTAGE__3P15V_OR_3P75V    00010000B

#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__DISABLED    00000000B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__2P50V    00000001B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__2P60V    00000010B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__2P70V    00000011B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__2P80V    00000100B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__2P90V    00000101B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__3P00V    00000110B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__3P10V    00000111B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__3P70V    00001000B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__2P88V    00001001B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__3P25V    00001100B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__3P35V    000001101B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__3P46V    00001110B
#define LOW_BATTERY_SYSOK_VOLTAGE_THRESHOLD__3P58V    00001111B
#endif

/*OTG TLIM and THERM control register 0Ah */
#define OTG_TIIM_AND_THERM_CONTROL_REGISTER    0x0A

#ifdef OTG_TIIM_AND_THERM_CONTROL_REGISTER
#define CHARGE_CURRENT_COMPENSATION__125MA    00000000B
#define CHARGE_CURRENT_COMPENSATION__350MA    01000000B
#define CHARGE_CURRENT_COMPENSATION__450MA    10000000B
#define CHARGE_CURRENT_COMPENSATION__600MA    11000000B

#define DIGITAL_THERMAL_REGULATION_TEMPERATURE_THRESHOLD_100C    00000000B
#define DIGITAL_THERMAL_REGULATION_TEMPERATURE_THRESHOLD_110C    00010000B
#define DIGITAL_THERMAL_REGULATION_TEMPERATURE_THRESHOLD_120C    00100000B
#define DIGITAL_THERMAL_REGULATION_TEMPERATURE_THRESHOLD_130C    00110000B

#define OTG_CURRENT_LIMIT_AT_USBIN__100MA    00000000B
#define OTG_CURRENT_LIMIT_AT_USBIN__250MA    00000100B
#define OTG_CURRENT_LIMIT_AT_USBIN__500MA    00001000B
#define OTG_CURRENT_LIMIT_AT_USBIN__750MA    00001100B

#define OTG_BATTERY_UVLO_THRESHOLD__2P7V    00000000B
#define OTG_BATTERY_UVLO_THRESHOLD__2P9V    00000001B
#define OTG_BATTERY_UVLO_THRESHOLD__3P1V    00000010B
#define OTG_BATTERY_UVLO_THRESHOLD__3P3V    00000011B
#endif

/*HARD/SOFT limit cell temperature  monitor register 0Bh */
#define HARD_SOFT_LIMIT_CELL_TERMPERATURE_MONITOR_REGISTER    0x0B


/*FAULT interrupt register 0Ch */
#define FAULT_INTERRUPT_REGISTER    0x0C

#ifdef FAULT_INTERRUPT_REGISTER
#define TEMPERATURE_OUTSIDE_COLD_OR_HOT_HARD_LIMIT_INTERRUPT    10000000B
#define TEMPERATURE_OUTSIDE_COLD_OR_HOT_SOFT_LIMIT_INTERRUPT    01000000B

#define OTG_BATTERY_FAIL_INTERRUPT    00100000B
#define OTG_OVER_CURRENT_LIMIT_INTERRUPT    00010000B

#define DCIN_OR_USB_OVER_VOLTAGE_INTERRUPT    00001000B
#define DCIN_OR_USB_UNDER_VOLTAGE_INTERRUPT    00000100B

#define AICL_COMPLETE_INTERRUPT    00000010B
#define INTERMAL_OVER_TEMPERATURE_INTERRUPT    00000001B
#endif

/*STATUS interrupt register 0Dh */
#define STATUS_INTERRUPT_REGISTER    0x0D

#ifdef STATUS_INTERRUPT_REGISTER
#define DISABLE_INTERRUPT    0x0
#define CHARGE_TIMEOUT_INTERRUPT    10000000B
#define OTG_INSERT_REMOVE_INTERRUPT    01000000B
#define BATTERY_OVER_VOLTAGE_INTERRUPT    00100000B
#define TERMINATION_OR_TAPER_CHARGING_INTERRUPT    00010000B
#define FAST_CHARGING_INTERRUPT    0x8
#define INOK_INTERRUPT    00000100B
#define MISSING_BATTERY_INTERRUPT    00000010B
#define LOW_BATTERY_INTERRUPT    00000001B
#endif

/*I2C BUS/SLAVE ADDR register 0Eh */
#define I2C_BUS_SLAVE_ADDRESS_REGISTER    0x0E

#ifdef I2C_BUS_SLAVE_ADDRESS_REGISTER
#define I2C_SLAVE_ADDRESS_0000    00000000B
#define I2C_SLAVE_ADDRESS_0001    00010000B
#define I2C_SLAVE_ADDRESS_0010    00100000B
#define I2C_SLAVE_ADDRESS_0011    00110000B
#define I2C_SLAVE_ADDRESS_0100    01000000B
#define I2C_SLAVE_ADDRESS_0101    01010000B 
#define I2C_SLAVE_ADDRESS_0110    01100000B
#define I2C_SLAVE_ADDRESS_0111    01110000B
#define I2C_SLAVE_ADDRESS_1000    10000000B
#define I2C_SLAVE_ADDRESS_1001    10010000B
#define I2C_SLAVE_ADDRESS_1010    10100000B
#define I2C_SLAVE_ADDRESS_1011    10110000B
#define I2C_SLAVE_ADDRESS_1100    11000000B
#define I2C_SLAVE_ADDRESS_1101    11010000B
#define I2C_SLAVE_ADDRESS_1110    11100000B
#define I2C_SLAVE_ADDRESS_1111    11110000B

#define I2C_BUS_ADDRESS_0000    00000000B
#define I2C_BUS_ADDRESS_0001    00000010B
#define I2C_BUS_ADDRESS_0010    00000100B
#define I2C_BUS_ADDRESS_0011    00000110B
#define I2C_BUS_ADDRESS_0100    00001000B
#define I2C_BUS_ADDRESS_0101    00001010B 
#define I2C_BUS_ADDRESS_0110    00001100B
#define I2C_BUS_ADDRESS_0111    00001110B

#define PREVERN_VOLATILE_WRITES    00000000B
#define ALLOW_VOLATILE_WRITES    00000001B
#endif

/*command  register a 30h */
#define COMMAND_REGISTER_A    0x30

#ifdef COMMAND_REGISTER_A
#define PREVERN_VOLATILE_WRITES_TO_CONFIG_REGISTERS    0x0<<7
#define ALLOW_VOLATILE_WRITES_TO_CONFIG_REGISTERS     0x1<<7

#define FORCE_PRE_CHARGE_CURRENT_SETTING    00000000B
#define ALLOW_FAST_CHARGE_CURRENT_SETTING    01000000B

#define ITHERM_PER_CONFIG_SETTING    00000000B
#define ITHERM_ENABLED    00100000B

#define OTG_DISABLED    00000000B
#define OTG_ENABLED    00010000B

#define BATTERY_TO_SYSTEM_INTERNAL_ALGORITHM    00000000B
#define TURN_OFF_BATTERY_TO_SYSTEM_FET    00001000B

#define SUSPEND_MODE_DISABLED    0x0
#define SUSPEND_MODE_ENABLED    0x1<<2

#define CHARGING_DISABLED    0x0
#define CHARGEING_ENABLED    0x2

#define STAT_OUTPUT_ENABLED    00000000B
#define STAT_OUTPUT_DISABLED    00000001B
#endif

/*command  register b 31h */
#define COMMAND_REGISTER_B    0x31

#ifdef COMMAND_REGISTER_B
#define POWER_ON_RESET_NO_EFFECT    0x0
#define POWER_ON_RESET_RESET    0x1<<7

#define USB_MODE__USB1    00000000B
#define USB_MODE__USB5    00000010B

#define USB_MODE    00000000B
#define HC_MODE    00000001B
#endif

/*command  register c 33h */
#define COMMAND_REGISTER_C    0x33


/*interrupt register a 35h READ ONLY*/
#define INTERRUPT_REGISTER_A    0x35

#ifdef INTERRUPT_REGISTER_A
#define HOT_TEMPERATURE_HARD_LIMIT_IRQ    0x1<<7
#define HOT_TEMPERATURE_HARD_LIMIT_STATUS    0x1<<6

#define COLD_TEMPERATURE_HARD_LIMIT_IRQ    0x1<<5
#define COLD_TEMPERATURE_HARD_LIMIT_STATUS   0x1<<4

#define HOT_TEMPERATURE_SOFT_LIMIT_IRQ    0x1<<3
#define HOT_TEMPERATURE_SOFT_LIMIT_STATUS    0x1<<2

#define COLD_TEMPERATURE_SOFT_LIMIT_IRQ    0x1<<1
#define COLD_TEMPERATURE_SOFT_LIMIT_STATUS    0x1
#endif

/*interrupt status register b 36h READ ONLY*/
#define INTERRUPT_REGISTER_B    0x36

#ifdef INTERRUPT_REGISTER_B
#define BATTERY_OVER_VOLTAGE_CONDITION_IRQ    0x1<<7
#define BATTERY_OVER_VOLTAGE_STATUS    0x1<<6

#define MISSING_BATTERY_IRQ    0x1<<5
#define MISSING_BATTERY_STATUS   0x1<<4

#define LOW_BATTERY_VOLTAGE_IRQ    0x1<<3
#define LOW_BATTERY_VOLTAGE_STATUS    0x1<<2

#define PRE_TO_FAST_CHARGE_BATTERY_VOLTAGE_IRQ    0x1<<1
#define PRE_TO_FAST_CHARGE_BATTERY_VOLTAGE_STATUS    0x1
#endif

/*interrupt status register c 37h READ ONLY*/
#define INTERRUPT_REGISTER_C    0x37

#ifdef INTERRUPT_REGISTER_C
#define INTERNAL_TEMPERATURE_LIMIT_IRQ    0x1<<7
#define INTERNAL_TEMPERATURE_LIMIT_STATUS    0x1<<6

#define RE_CHARGE_BATTERY_THRESHOLD_IRQ    0x1<<5
#define RE_CHARGE_BATTERY_THRESHOLD_STATUS    0x1<<4

#define TAPER_CHARGE_MODE_IRQ    0x1<<3
#define TAPER_CHARGE_MODE_STATUS    0x1<<2

#define TERMINATION_CHARGING_CURRENT_HIT_IRQ    0x1<<1
#define TERMINATION_CHARGING_CURRENT_HIT_STATUS    0x1
#endif

/*interrupt status register d 38h READ ONLY*/
#define INTERRUPT_REGISTER_D    0x38

#ifdef INTERRUPT_REGISTER_D
#define APSD_COMPLETED_IRQ    0x1<<7
#define APSD_COMPLETED_STATUS    0x1<<6

#define AICL_COMPLETED_IRQ    0x1<<5
#define AICL_COMPLETED_STATUS    0x1<<4

#define COMPLETE_CHARGE_TIMEOUT_IRQ    0x1<<3
#define COMPLETE_CHARGE_TIMEOUT_STATUS    0x1<<2

#define PRE_CHARGE_TIMEOUT_IRQ    0x1<<1
#define PRE_CHARGE_TIMEOUT_STATUS    0x1
#endif

/*interrupt status register e 39h READ ONLY*/
#define INTERRUPT_REGISTER_E    0x39

#ifdef INTERRUPT_REGISTER_E
#define DCIN_OVER_VOLTAGE_IRQ    0x1<<7
#define DCIN_OVER_VOLTAGE_STATUS    0x1<<6

#define DCIN_UNDER_VOLTAGE_IRQ    0x1<<5
#define DCIN_UNDER_VOLTAGE_STATUS    0x1<<4

#define USBIN_OVER_VOLTAGE_IRQ    0x1<<3
#define USBIN_OVER_VOLTAGE_STATUS    0x1<<2

#define USBIN_UNDER_VOLTAGE_IRQ    0x1<<1
#define USBIN_UNDER_VOLTAGE_STATUS    0x1
#endif

/*interrupt status register f 3ah */
#define INTERRUPT_REGISTER_F    0x3A

#ifdef INTERRUPT_REGISTER_F
#define OTG_OVER_CURRENT_LIMIT_IRQ    0x1<<7
#define OTG_OVER_CURRENT_LIMIT_STATUS    0x1<<6

#define OTG_BATTERY_UNDER_VOLTAGE_IRQ    0x1<<5
#define OTG_BATTERY_UNDER_VOLTAGE_STATUS    0x1<<4

#define OTG_DETECTION_IRQ    0x1<<3
#define OTG_DETECTION_STATUS    0x1<<2

#define POWER_OK_IRQ    0x1<<1
#define POWER_OK_STATUS    0x1
#endif

/*status register a 3bh */
#define STATUS_REGISTER_A    0x3B

#ifdef STATUS_REGISTER_A
#define THERMAL_REGULATION    00000000B
#define NO_THERMAL_REGULATION    10000000B

#define NO_THERMAL_SOFT_LIMIT_REGULATION    00000000B
#define THERMAL_SOFT_LIMIT_REGULATION    01000000B

#define ACTUAL_FLOAT_VOLTAGE_3P50V    00000000B
#define ACTUAL_FLOAT_VOLTAGE_3P52V    00000001B
#define ACTUAL_FLOAT_VOLTAGE_3P54V    00000010B
#define ACTUAL_FLOAT_VOLTAGE_3P56V    00000011B
#define ACTUAL_FLOAT_VOLTAGE_3P58V    00000100B

#define ACTUAL_FLOAT_VOLTAGE_3P60V    00000101B
#define ACTUAL_FLOAT_VOLTAGE_3P62V    00000110B
#define ACTUAL_FLOAT_VOLTAGE_3P64V    00000111B
#define ACTUAL_FLOAT_VOLTAGE_3P66V    00001000B
#define ACTUAL_FLOAT_VOLTAGE_3P68V    00001001B

#define ACTUAL_FLOAT_VOLTAGE_3P70V    00001010B
#define ACTUAL_FLOAT_VOLTAGE_3P72V    00001011B
#define ACTUAL_FLOAT_VOLTAGE_3P74V    00001100B
#define ACTUAL_FLOAT_VOLTAGE_3P76V    00001101B
#define ACTUAL_FLOAT_VOLTAGE_3P78V    00001110B

#define ACTUAL_FLOAT_VOLTAGE_3P80V    00001111B
#define ACTUAL_FLOAT_VOLTAGE_3P82V    00010000B
#define ACTUAL_FLOAT_VOLTAGE_3P84V    00010001B
#define ACTUAL_FLOAT_VOLTAGE_3P86V    00010010B
#define ACTUAL_FLOAT_VOLTAGE_3P88V    00010011B

#define ACTUAL_FLOAT_VOLTAGE_3P90V    00010100B
#define ACTUAL_FLOAT_VOLTAGE_3P92V    00010101B
#define ACTUAL_FLOAT_VOLTAGE_3P94V    00010110B
#define ACTUAL_FLOAT_VOLTAGE_3P96V    00010111B
#define ACTUAL_FLOAT_VOLTAGE_3P98V    00011000B

#define ACTUAL_FLOAT_VOLTAGE_4P00V    00011001B
#define ACTUAL_FLOAT_VOLTAGE_4P02V    00011010B
#define ACTUAL_FLOAT_VOLTAGE_4P04V    00011011B
#define ACTUAL_FLOAT_VOLTAGE_4P06V    00011100B
#define ACTUAL_FLOAT_VOLTAGE_4P08V    00011101B

#define ACTUAL_FLOAT_VOLTAGE_4P10V    00011110B
#define ACTUAL_FLOAT_VOLTAGE_4P12V    00011111B
#define ACTUAL_FLOAT_VOLTAGE_4P14V    00100000B
#define ACTUAL_FLOAT_VOLTAGE_4P16V    00100001B
#define ACTUAL_FLOAT_VOLTAGE_4P18V    00100010B

#define ACTUAL_FLOAT_VOLTAGE_4P20V    00100011B
#define ACTUAL_FLOAT_VOLTAGE_4P22V    00100100B
#define ACTUAL_FLOAT_VOLTAGE_4P24V    00100101B
#define ACTUAL_FLOAT_VOLTAGE_4P26V    00100110B
#define ACTUAL_FLOAT_VOLTAGE_4P28V    00100111B

#define ACTUAL_FLOAT_VOLTAGE_4P30V    00101000B
#define ACTUAL_FLOAT_VOLTAGE_4P32V    00101001B
#define ACTUAL_FLOAT_VOLTAGE_4P34V    00101010B
#define ACTUAL_FLOAT_VOLTAGE_4P36V    00101011B
#define ACTUAL_FLOAT_VOLTAGE_4P38V    00101100B

#define ACTUAL_FLOAT_VOLTAGE_4P40V    00101101B
#define ACTUAL_FLOAT_VOLTAGE_4P42V    00101110B
#define ACTUAL_FLOAT_VOLTAGE_4P44V    00101111B
#define ACTUAL_FLOAT_VOLTAGE_4P46V    00110000B
#define ACTUAL_FLOAT_VOLTAGE_4P48V    00110001B

#define ACTUAL_FLOAT_VOLTAGE_4P50V    00110010B
#endif

/*status register b 3ch */
#define STATUS_REGISTER_B    0x3C

#ifdef STATUS_REGISTER_B
#define USB_SUSPEND_MODE__NOT_ACTIVE    0x0
#define USB_SUSPEND_MODE__ACTIVE    0x1<<7

#define ACTUAL_CHARGE_CURRENT__100MA    00000000B
#define ACTUAL_CHARGE_CURRENT__150MA    00001000B
#define ACTUAL_CHARGE_CURRENT__200MA    00010000B
#define ACTUAL_CHARGE_CURRENT__250MA    00011000B
#define ACTUAL_CHARGE_CURRENT__700MA    00100000B
#define ACTUAL_CHARGE_CURRENT__900MA    00100001B
#define ACTUAL_CHARGE_CURRENT__1200MA    00100010B
#define ACTUAL_CHARGE_CURRENT__1500MA    00100011B
#define ACTUAL_CHARGE_CURRENT__1800MA    00100100B
#define ACTUAL_CHARGE_CURRENT__2000MA    00100101B
#define ACTUAL_CHARGE_CURRENT__2200MA    00100110B
#define ACTUAL_CHARGE_CURRENT__2500MA    00100111B
#endif

/*status register c 3dh READ ONLY*/
#define STATUS_REGISTER_C    0x3D

#ifdef STATUS_REGISTER_C
#define CHARGE_ERROR_DOES_NOT_ASSERT_AN_IRQ_SIGNAL    00000000B
#define CHARGE_ERROR_ASSERT_AN_IRQ_SIGNAL    10000000B

#define NO_CHARGE_ERROR    00000000B
#define CHARGE_ERROR    01000000B

#define NO_CHARGE_CYCLE_SINCE_CHARGING_FIRST_ENABLED    00000000B
#define HAVE_CHARGE_CYCLE_SINCE_CHARGING_FIRST_ENABLED    00100000B

#define BATTERY_VOLTAGE_MORE_THAN_2P1V    00000000B
#define BATTERY_VOLTAGE_LESS_THAN_2P1V    00010000B

#define CHARGER_NOT_IN_HOLD_OFF_STATUS    00000000B
#define CHARGER_IN_HOLD_OFF_STATUS    00001000B

#define CHARGE_STATUS__NO_CHARGING    0x0<<1
#define CHARGE_STATUS__PRE_CHARGING    0x1<<1
#define CHARGE_STATUS__FAST_CHARGING    0x2<<1
#define CHARGE_STATUS__TAPER_CHARGING    0x3<<1

#define CHARGE_DISABLED    00000000B
#define CHARGE_ENABLED    00000001B
#endif

/*status register d 3eh */
#define STATUS_REGISTER_D    0x3E

#ifdef STATUS_REGISTER_D
#define RID_STATUS__NOT_DONE    00000000B
#define RID_STATUS__DONE    10000000B

#define ACA_STATUS__RID_A    00000000B
#define ACA_STATUS__RID_B    00010000B
#define ACA_STATUS__RID_C    00100000B
#define ACA_STATUS__RID_FLOATING    00110000B
#define ACA_STATUS__RID_NOT_USED    01000000B

#define APSD_STATUS__NOT_COMPLETED    00000000B
#define APSD_STATUS__COMPLETED    00001000B

#define APSD_RESULTS__NOT_RUN    00000000B
#define APSD_RESULTS__CHARGE_DOWNSTREAM_PORT    00000001B
#define APSD_RESULTS__DEDICATE_CHARGE_PORT    00000010B
#define APSD_RESULTS__OTHER_CHARGE_PORT    00000011B
#define APSD_RESULTS__STANDARD_DOWNSTREAM_PORT    00000100B
#define APSD_RESULTS__ACA_CHARGE    00000101B
#define APSD_RESULTS__TBD    00000110B
#endif

/*status register e 3fh */
#define STATUS_REGISTER_E    0x3F

#ifdef STATUS_REGISTER_E
#define USBIN_INPUT_NOT_IN_USE    00000000B
#define USBIN_INPUT_IN_USE    10000000B

#define USB5_1_HC_MODE__HC_MODE    00000000B
#define USB5_1_HC_MODE__USB1_MODE    00100000B
#define USB5_1_HC_MODE__USB5_MODE    01000000B
#define USB5_1_HC_MODE__NA    01100000B

#define AICL_STATUS__NOT_COMPLETED    0x0<<4
#define AICL_STATUS__COMPLETED    0x1<<4
#define DCIN_IN_USE	0x1<<7

#define AICL_RESULTS__300MA    0x0
#define AICL_RESULTS__500MA    0x1
#define AICL_RESULTS__700MA    0x2
#define AICL_RESULTS__900MA    0x3
#define AICL_RESULTS__1200MA    0x4
#define AICL_RESULTS__1500MA    0x5
#define AICL_RESULTS__1800MA    0x6
#define AICL_RESULTS__2000MA    0x7
#define AICL_RESULTS__2200MA    0x8
#define AICL_RESULTS__2500MA    0x9

#define AICL_RESULTS__MASK    0xf
#endif

#endif

