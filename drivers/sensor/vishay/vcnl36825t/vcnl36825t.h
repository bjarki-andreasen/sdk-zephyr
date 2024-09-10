/*
 * Copyright (c) 2024 Juliane Schulze, deveritec GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_VCNL36825T_VCNL36825T_H_
#define ZEPHYR_DRIVERS_SENSOR_VCNL36825T_VCNL36825T_H_

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

#define VCNL36825T_REG_PS_CONF1		0x00
#define VCNL36825T_REG_PS_CONF2		0x03
#define VCNL36825T_REG_PS_CONF3		0x04
#define VCNL36825T_REG_PS_THDL		0x05
#define VCNL36825T_REG_PS_THDH		0x06
#define VCNL36825T_REG_PS_CANC		0x07
#define VCNL36825T_REG_PS_CONF4		0x08
#define VCNL36825T_REG_PS_DATA		0xF8
#define VCNL36825T_REG_INT_FLAG		0xF9
#define VCNL36825T_REG_DEV_ID		0xFA
#define VCNL36825T_REG_PS_AC_DATA	0xFB

/* default values */
#define VCNL36825T_CONF1_DEFAULT	0x0001
#define VCNL36825T_CONF2_DEFAULT	0x0000
#define VCNL36825T_CONF3_DEFAULT	0x0000
#define VCNL36825T_THDL_DEFAULT		0x0000
#define VCNL36825T_THDH_DEFAULT		0x0000
#define VCNL36825T_CANC_DEFAULT		0x0000
#define VCNL36825T_CONF4_DEFAULT	0x0000

/* PS_CONF1 */
#define VCNL36825T_PS_ON_POS	1
#define VCNL36825T_PS_CAL_POS	7

#define VCNL36825T_PS_ON_MSK	GENMASK(1, 1)

#define VCNL36825T_PS_ON	(1 << VCNL36825T_PS_ON_POS)
#define VCNL36825T_PS_OFF	(0 << VCNL36825T_PS_ON_POS)

#define VCNL36825T_PS_CAL	(1 << VCNL36825T_PS_CAL_POS)

/* PS_CONF2 */
#define VCNL36825T_PS_ST_POS		0
#define VCNL36825T_PS_PS_SMART_PERS_POS	1
#define VCNL36825T_PS_INT_POS		2
#define VCNL36825T_PS_PERS_POS		4
#define VCNL36825T_PS_PERIOD_POS	6
#define VCNL36825T_PS_HG_POS		10
#define VCNL36825T_PS_ITB_POS		11
#define VCNL36825T_PS_MPS_POS		12
#define VCNL36825T_PS_IT_POS		14

#define VCNL36825T_PS_ST_MSK	GENMASK(0, 0)

#define VCNL36825T_PS_ST_START	(0 << VCNL36825T_PS_ST_POS)
#define VCNL36825T_PS_ST_STOP	(1 << VCNL36825T_PS_ST_POS)

#define VCNL36825T_PS_SMART_PERS_DISABLED	(0 << VCNL36825T_PS_PS_SMART_PERS_POS)
#define VCNL36825T_PS_SMART_PERS_ENABLED	(1 << VCNL36825T_PS_PS_SMART_PERS_POS)

#define VCNL36825T_PS_INT_DISABLE		(0 << VCNL36825T_PS_INT_POS)
#define VCNL36825T_PS_INT_THDH_PERS_LATCHED	(1 << VCNL36825T_PS_INT_POS)
#define VCNL36825T_PS_INT_THDH_FIRST_LATCHED	(2 << VCNL36825T_PS_INT_POS)
#define VCNL36825T_PS_INT_ENABLED		(3 << VCNL36825T_PS_INT_POS)

#define VCNL36825T_PS_PERS_1	(0 << VCNL36825T_PS_PERS_POS)
#define VCNL36825T_PS_PERS_2	(1 << VCNL36825T_PS_PERS_POS)
#define VCNL36825T_PS_PERS_3	(2 << VCNL36825T_PS_PERS_POS)
#define VCNL36825T_PS_PERS_4	(3 << VCNL36825T_PS_PERS_POS)

#define VCNL36825T_PS_PERIOD_10MS	(0 << VCNL36825T_PS_PERIOD_POS)
#define VCNL36825T_PS_PERIOD_20MS	(1 << VCNL36825T_PS_PERIOD_POS)
#define VCNL36825T_PS_PERIOD_40MS	(2 << VCNL36825T_PS_PERIOD_POS)
#define VCNL36825T_PS_PERIOD_80MS	(3 << VCNL36825T_PS_PERIOD_POS)

#define VCNL36825T_PS_HG_LOW	(0 << VCNL36825T_PS_HG_POS)
#define VCNL36825T_PS_HG_HIGH	(1 << VCNL36825T_PS_HG_POS)

#define VCNL36825T_PS_ITB_25us	(0 << VCNL36825T_PS_ITB_POS)
#define VCNL36825T_PS_ITB_50us	(1 << VCNL36825T_PS_ITB_POS)

#define VCNL36825T_MPS_PULSES_1	(0 << VCNL36825T_PS_MPS_POS)
#define VCNL36825T_MPS_PULSES_2	(1 << VCNL36825T_PS_MPS_POS)
#define VCNL36825T_MPS_PULSES_4	(2 << VCNL36825T_PS_MPS_POS)
#define VCNL36825T_MPS_PULSES_8	(4 << VCNL36825T_PS_MPS_POS)

#define VCNL36825T_PS_IT_1T	(0 << VCNL36825T_PS_IT_POS)
#define VCNL36825T_PS_IT_2T	(1 << VCNL36825T_PS_IT_POS)
#define VCNL36825T_PS_IT_4T	(2 << VCNL36825T_PS_IT_POS)
#define VCNL36825T_PS_IT_8T	(3 << VCNL36825T_PS_IT_POS)

/* PS_CONF3 */
#define VCNL36825T_PS_SP_INT_POS	2
#define VCNL36825T_PS_FORCENUM_POS	4
#define VCNL36825T_PS_TRIG_POS		5
#define VCNL36825T_PS_AF_POS		6
#define VCNL36825T_PS_I_VCSEL_POS	8
#define VCNL36825T_PS_HD_POS		12
#define VCNL36825T_PS_SC_POS		13

#define VCNL36825T_PS_TRIG_MSK	GENMASK(5, 5)
#define VCNL36825T_PS_AF_MSK	GENMASK(6, 6)

#define VCNL36825T_PS_SP_INT_DISABLED	(0 << VCNL36825T_PS_SP_INT_POS)
#define VCNL36825T_PS_SP_INT_ENABLED	(1 << VCNL36825T_PS_SP_INT_POS)

#define VCNL36825T_PS_FORCENUM_ONE_CYCLE	(0 << VCNL36825T_PS_FORCENUM_POS)
#define VCNL36825T_PS_FORCENUM_TWO_CYCLES	(1 << VCNL36825T_PS_FORCENUM_POS)

#define VCNL36825T_PS_TRIG_NONE	(0 << VCNL36825T_PS_TRIG_POS)
#define VCNL36825T_PS_TRIG_ONCE	(1 << VCNL36825T_PS_TRIG_POS)

#define VCNL36825T_PS_AF_AUTO	(0 << VCNL36825T_PS_AF_POS)
#define VCNL36825T_PS_AF_FORCE	(1 << VCNL36825T_PS_AF_POS)

#define VCNL36825T_PS_I_VCSEL_10MA	(2 << VCNL36825T_PS_I_VCSEL_POS)
#define VCNL36825T_PS_I_VCSEL_12MA	(3 << VCNL36825T_PS_I_VCSEL_POS)
#define VCNL36825T_PS_I_VCSEL_14MA	(4 << VCNL36825T_PS_I_VCSEL_POS)
#define VCNL36825T_PS_I_VCSEL_16MA	(5 << VCNL36825T_PS_I_VCSEL_POS)
#define VCNL36825T_PS_I_VCSEL_18MA	(6 << VCNL36825T_PS_I_VCSEL_POS)
#define VCNL36825T_PS_I_VCSEL_20MA	(7 << VCNL36825T_PS_I_VCSEL_POS)

#define VCNL36825T_PS_HD_12BIT	(0 << VCNL36825T_PS_HD_POS)
#define VCNL36825T_PS_HD_16BIT	(1 << VCNL36825T_PS_HD_POS)

#define VCNL36825T_PS_SC_DISABLED	(0 << VCNL36825T_PS_SC_POS)
#define VCNL36825T_PS_SC_ENABLED	(7 << VCNL36825T_PS_SC_POS)

/* PS CONF4 */
#define VCNL36825T_PS_AC_INT_POS	0
#define VCNL36825T_PS_AC_TRIG_POS	2
#define VCNL36825T_PS_AC_POS		3
#define VCNL36825T_PS_AC_NUM_POS	4
#define VCNL36825T_PS_AC_PERIOD_POS	6
#define VCNL36825T_PS_LPEN_POS		8
#define VCNL36825T_PS_LPPER_POS		9

#define VCNL36825T_PS_LPEN_MSK	GENMASK(8, 8)

#define VCNL36825T_PS_AC_INT_DISABLED	(0 << VCNL36825T_PS_AC_INT_POS)
#define VCNL36825T_PS_AC_INT_ENABLED	(1 << VCNL36825T_PS_AC_INT_POS)

#define VCNL36825T_PS_AC_TRIG_DISABLED	(0 << VCNL36825T_PS_AC_TRIG_POS)
#define VCNL36825T_PS_AC_TRIG_ONCE	(1 << VCNL36825T_PS_AC_TRIG_POS)

#define VCNL36825T_PS_AC_DISABLED	(0 << VCNL36825T_PS_AC_POS)
#define VCNL36825T_PS_AC_ENABLED	(1 << VCNL36825T_PS_AC_POS)

#define VCNL36825T_PS_AC_NUM_1	(0 << VCNL36825T_PS_AC_NUM_POS)
#define VCNL36825T_PS_AC_NUM_2	(1 << VCNL36825T_PS_AC_NUM_POS)
#define VCNL36825T_PS_AC_NUM_4	(2 << VCNL36825T_PS_AC_NUM_POS)
#define VCNL36825T_PS_AC_NUM_8	(3 << VCNL36825T_PS_AC_NUM_POS)

#define VCNL36825T_PS_AC_PERIOD_3MS	(0 << VCNL36825T_PS_AC_PERIOD_POS)
#define VCNL36825T_PS_AC_PERIOD_6MS	(1 << VCNL36825T_PS_AC_PERIOD_POS)
#define VCNL36825T_PS_AC_PERIOD_12MS	(2 << VCNL36825T_PS_AC_PERIOD_POS)
#define VCNL36825T_PS_AC_PERIOD_24MS	(3 << VCNL36825T_PS_AC_PERIOD_POS)

#define VCNL36825T_PS_LPEN_DISABLED	(0 << VCNL36825T_PS_LPEN_POS)
#define VCNL36825T_PS_LPEN_ENABLED	(1 << VCNL36825T_PS_LPEN_POS)

#define VCNL36825T_PS_LPPER_40MS	(0 << VCNL36825T_PS_LPPER_POS)
#define VCNL36825T_PS_LPPER_80MS	(1 << VCNL36825T_PS_LPPER_POS)
#define VCNL36825T_PS_LPPER_160MS	(2 << VCNL36825T_PS_LPPER_POS)
#define VCNL36825T_PS_LPPER_320MS	(3 << VCNL36825T_PS_LPPER_POS)

/* PS_DATA */
#define VCNL36825T_PS_DATA_L_POS	0
#define VCNL36825T_PS_DATA_H_POS	8

#define VCNL36825T_PS_DATA_L_MSK	GENMASK(7, 0)
#define VCNL36825T_PS_DATA_H_MSK	GENMASK(11, 8)
#define VCNL36825T_OS_DATA_MSK		(VCNL36825T_PS_DATA_L_MSK | VCNL36825T_PS_DATA_H_MSK)

/* INT_FLAG */
#define VCNL36825T_PS_IF_AWAY_POS	8
#define VCNL36825T_PS_IF_CLOSE_POS	9
#define VCNL36825T_PS_SPFLAG_POS	12
#define VCNL36825T_PS_ACFLAG_POS	13

#define VCNL36825T_PS_IF_AWAY_MSK	GENMASK(8, 8)
#define VCNL36825T_PS_IF_CLOSE_MSK	GENMASK(9, 9)
#define VCNL36825T_PS_SPFLAG_MSK	GENMASK(12, 12)
#define VCNL36825T_PS_ACFLAG_MSK	GENMASK(13, 13)

/* ID */
#define VCNL36825T_ID_POS		0
#define VCNL36825T_VERSION_CODE_POS	8

#define VCNL36825T_ID_MSK		GENMASK(7, 0)
#define VCNL36825T_VERSION_CODE_MSK	GENMASK(11, 8)

#define VCNL36825T_DEVICE_ID	0b00100110

/* PS_AC_DATA */
#define VCNL36825T_AC_DATA_L_POS	0
#define VCNL36825T_AC_DATA_H_POS	8
#define VCNL36825T_AC_SUN_POS		14
#define VCNL36825T_AC_BUSY_POS		15

#define VCNL36825T_AC_DATA_L_MSK	GENMASK(7, 0)
#define VCNL36825T_AC_DATA_H_MSK	GENMASK(11, 8)
#define VCNL36825T_AC_SUN_MSK		GENMASK(14, 14)
#define VCNL36825T_AC_BUSY_MSK		GENMASK(15, 15)

#define VCNL36825T_PS_PERIOD_VALUE_MAX_MS	80
#define VCNL36825T_PS_LPPER_VALUE_MIN_MS	40

/* see application note "Designing the VCNL36825T Into an Application": power up takes 2500 us */
#define VCNL36825T_POWER_UP_US	2500

#define VCNL36825T_FORCED_FACTOR_TIME_TO_TRIGGER	0.5
#define VCNL36825T_FORCED_FACTOR_DC_KILL_AMBIENT	3
#define VCNL36825T_FORCED_FACTOR_MEASUREMENT		1
#define VCNL36825T_FORCED_FACTOR_SHUTDOWN		1
#define VCNL36825T_FORCED_FACTOR_SCALE		10
#define VCNL36825T_FORCED_FACTOR_SUM                                                               \
	((VCNL36825T_FORCED_FACTOR_TIME_TO_TRIGGER + VCNL36825T_FORCED_FACTOR_DC_KILL_AMBIENT +    \
	  VCNL36825T_FORCED_FACTOR_MEASUREMENT + VCNL36825T_FORCED_FACTOR_SHUTDOWN) *              \
	 VCNL36825T_FORCED_FACTOR_SCALE)

enum vcnl36825t_operation_mode {
	VCNL36825T_OPERATION_MODE_AUTO,
	VCNL36825T_OPERATION_MODE_FORCE,
};

enum vcnl36825t_measurement_period {
	VCNL36825T_MEAS_PERIOD_10MS,
	VCNL36825T_MEAS_PERIOD_20MS,
	VCNL36825T_MEAS_PERIOD_40MS,
	VCNL36825T_MEAS_PERIOD_80MS,
	VCNL36825T_MEAS_PERIOD_160MS,
	VCNL36825T_MEAS_PERIOD_320MS,
};

enum vcnl36825t_proximity_integration_time {
	VCNL36825T_PROXIMITY_INTEGRATION_1T,
	VCNL36825T_PROXIMITY_INTEGRATION_2T,
	VCNL36825T_PROXIMITY_INTEGRATION_4T,
	VCNL36825T_PROXIMITY_INTEGRATION_8T,
};

enum vcnl36825t_proximity_integration_duration {
	VCNL36825T_PROXIMITY_INTEGRATION_DURATION_25us,
	VCNL36825T_PROXIMITY_INTEGRATION_DURATION_50us,
};

enum vcnl36825t_multi_pulse {
	VCNL38652T_MULTI_PULSE_1,
	VCNL38652T_MULTI_PULSE_2,
	VCNL38652T_MULTI_PULSE_4,
	VCNL38652T_MULTI_PULSE_8,
};

enum vcnl38625t_laser_current {
	VCNL36825T_LASER_CURRENT_10MS,
	VCNL36825T_LASER_CURRENT_12MS,
	VCNL36825T_LASER_CURRENT_14MS,
	VCNL36825T_LASER_CURRENT_16MS,
	VCNL36825T_LASER_CURRENT_18MS,
	VCNL36825T_LASER_CURRENT_20MS,
};

struct vcnl36825t_config {
	struct i2c_dt_spec i2c;

	enum vcnl36825t_operation_mode operation_mode;

	enum vcnl36825t_measurement_period period;
	enum vcnl36825t_proximity_integration_time proximity_it;
	enum vcnl36825t_proximity_integration_duration proximity_itb;
	enum vcnl36825t_multi_pulse multi_pulse;

	bool low_power;
	bool high_gain;

	enum vcnl38625t_laser_current laser_current;
	bool high_dynamic_output;
	bool sunlight_cancellation;
};

struct vcnl36825t_data {
	uint16_t proximity;

	int meas_timeout_us; /** wait time for finished measurement for "forced" operation mode */
};

#endif
