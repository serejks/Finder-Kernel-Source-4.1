/* Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "msm_sensor.h"
#include "msm.h"
#include "msm_ispif.h"
#include "msm_camera_i2c_mux.h"
/* OPPO 2012-10-10 yxq added begin for voltage supply */
#ifdef CONFIG_VENDOR_EDIT
#include <linux/regulator/consumer.h>
#include <mach/vreg.h>
#endif
/* OPPO 2012-10-10 yxq added end */

/* OPPO 2012-10-29 liuwd Delete */
#if 0
/* OPPO 2012-08-06 yxq added begin for debug */
#undef CDBG
#define CAMERA_DRIVER_DBG 1
#if CAMERA_DRIVER_DBG
#define CDBG(fmt, args...) printk(KERN_INFO "msm_sensor.c: " fmt, ##args)
#else
#define CDBG(fmt, args...) do{}while(0)
#endif
/* OPPO 2012-8-06 yxq added end */
#endif
/* OPPO 2012-10-29 liuwd Delete end */

/*=============================================================*/
int32_t msm_sensor_adjust_frame_lines(struct msm_sensor_ctrl_t *s_ctrl,
	uint16_t res)
{
	uint16_t cur_line = 0;
	uint16_t exp_fl_lines = 0;

	CDBG("%s: E --- res = %d\n", __func__, res);
	if (s_ctrl->sensor_exp_gain_info) {
		if (s_ctrl->prev_gain && s_ctrl->prev_line &&
			s_ctrl->func_tbl->sensor_write_exp_gain)
			s_ctrl->func_tbl->sensor_write_exp_gain(
				s_ctrl,
				s_ctrl->prev_gain,
				s_ctrl->prev_line);

		msm_camera_i2c_read(s_ctrl->sensor_i2c_client,
			s_ctrl->sensor_exp_gain_info->coarse_int_time_addr,
			&cur_line,
			MSM_CAMERA_I2C_WORD_DATA);
		exp_fl_lines = cur_line +
			s_ctrl->sensor_exp_gain_info->vert_offset;
		if (exp_fl_lines > s_ctrl->msm_sensor_reg->
			output_settings[res].frame_length_lines)
			msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
				s_ctrl->sensor_output_reg_addr->
				frame_length_lines,
				exp_fl_lines,
				MSM_CAMERA_I2C_WORD_DATA);
		CDBG("%s cur_fl_lines %d, exp_fl_lines %d\n", __func__,
			s_ctrl->msm_sensor_reg->
			output_settings[res].frame_length_lines,
			exp_fl_lines);
	}
	CDBG("%s: X\n", __func__);
	return 0;
}

int32_t msm_sensor_write_init_settings(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc;

	CDBG("%s: E\n", __func__);
	rc = msm_sensor_write_all_conf_array(
		s_ctrl->sensor_i2c_client,
		s_ctrl->msm_sensor_reg->init_settings,
		s_ctrl->msm_sensor_reg->init_size);
	CDBG("%s: X\n", __func__);
	return rc;
}

int32_t msm_sensor_write_res_settings(struct msm_sensor_ctrl_t *s_ctrl,
	uint16_t res)
{
	int32_t rc;

	CDBG("%s: E --- res = %d\n", __func__, res);
	rc = msm_sensor_write_conf_array(
		s_ctrl->sensor_i2c_client,
		s_ctrl->msm_sensor_reg->mode_settings, res);
	/* Qualcomm Release */
	if (rc < 0)
		return rc;

/* OPPO 2012-08-07 yxq modified begin for debug */
#ifndef CONFIG_VENDOR_EDIT
	/* Qualcomm Release */
	rc = msm_sensor_write_output_settings(s_ctrl, res);
	if (rc < 0)
		return rc;
#else
	if (s_ctrl->sensor_id_info->sensor_id_reg_addr != 0x0040)
		{
			rc = msm_sensor_write_output_settings(s_ctrl, res);
			if (rc < 0)
				return rc;
		}
#endif
/* OPPO 2012-08-07 yxq modified end */
	if (s_ctrl->func_tbl->sensor_adjust_frame_lines)
		rc = s_ctrl->func_tbl->sensor_adjust_frame_lines(s_ctrl, res);
	CDBG("%s: X\n", __func__);

	return rc;
}

int32_t msm_sensor_write_output_settings(struct msm_sensor_ctrl_t *s_ctrl,
	uint16_t res)
{
	int32_t rc = -EFAULT;
	struct msm_camera_i2c_reg_conf dim_settings[] = {
		{s_ctrl->sensor_output_reg_addr->x_output,
			s_ctrl->msm_sensor_reg->
			output_settings[res].x_output},
		{s_ctrl->sensor_output_reg_addr->y_output,
			s_ctrl->msm_sensor_reg->
			output_settings[res].y_output},
		{s_ctrl->sensor_output_reg_addr->line_length_pclk,
			s_ctrl->msm_sensor_reg->
			output_settings[res].line_length_pclk},
		{s_ctrl->sensor_output_reg_addr->frame_length_lines,
			s_ctrl->msm_sensor_reg->
			output_settings[res].frame_length_lines},
	};

	CDBG("%s: E --- res = %d\n", __func__, res);
	rc = msm_camera_i2c_write_tbl(s_ctrl->sensor_i2c_client, dim_settings,
		ARRAY_SIZE(dim_settings), MSM_CAMERA_I2C_WORD_DATA);
	CDBG("%s: X\n", __func__);
	return rc;
}

void msm_sensor_start_stream(struct msm_sensor_ctrl_t *s_ctrl)
{
	CDBG("%s: E\n", __func__);
	msm_camera_i2c_write_tbl(
		s_ctrl->sensor_i2c_client,
		s_ctrl->msm_sensor_reg->start_stream_conf,
		s_ctrl->msm_sensor_reg->start_stream_conf_size,
		s_ctrl->msm_sensor_reg->default_data_type);
	CDBG("%s: X\n", __func__);
}

void msm_sensor_stop_stream(struct msm_sensor_ctrl_t *s_ctrl)
{
	CDBG("%s: E\n", __func__);
	msm_camera_i2c_write_tbl(
		s_ctrl->sensor_i2c_client,
		s_ctrl->msm_sensor_reg->stop_stream_conf,
		s_ctrl->msm_sensor_reg->stop_stream_conf_size,
		s_ctrl->msm_sensor_reg->default_data_type);
	CDBG("%s: X\n", __func__);
}

void msm_sensor_group_hold_on(struct msm_sensor_ctrl_t *s_ctrl)
{
	CDBG("%s: E\n", __func__);
	msm_camera_i2c_write_tbl(
		s_ctrl->sensor_i2c_client,
		s_ctrl->msm_sensor_reg->group_hold_on_conf,
		s_ctrl->msm_sensor_reg->group_hold_on_conf_size,
		s_ctrl->msm_sensor_reg->default_data_type);
	CDBG("%s: X\n", __func__);
}

void msm_sensor_group_hold_off(struct msm_sensor_ctrl_t *s_ctrl)
{
	CDBG("%s: E\n", __func__);
	msm_camera_i2c_write_tbl(
		s_ctrl->sensor_i2c_client,
		s_ctrl->msm_sensor_reg->group_hold_off_conf,
		s_ctrl->msm_sensor_reg->group_hold_off_conf_size,
		s_ctrl->msm_sensor_reg->default_data_type);
	CDBG("%s: X\n", __func__);
}

int32_t msm_sensor_set_fps(struct msm_sensor_ctrl_t *s_ctrl,
						struct fps_cfg *fps)
{
	s_ctrl->fps_divider = fps->fps_div;
	CDBG("%s: s_ctrl->fps_divider=%d\n", __func__, fps->fps_div);
	return 0;
}

int32_t msm_sensor_write_exp_gain1(struct msm_sensor_ctrl_t *s_ctrl,
		uint16_t gain, uint32_t line)
{
	uint32_t fl_lines;
	uint8_t offset;

	CDBG("%s: E---gain=%d, line=%d\n", __func__, gain, line);
	fl_lines = s_ctrl->curr_frame_length_lines;
	fl_lines = (fl_lines * s_ctrl->fps_divider) / Q10;
	offset = s_ctrl->sensor_exp_gain_info->vert_offset;
	if (line > (fl_lines - offset))
		fl_lines = line + offset;

	CDBG("%s: fl_lines=%d, line=%d, gain=%d\n", __func__, fl_lines, line, gain);
	s_ctrl->func_tbl->sensor_group_hold_on(s_ctrl);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		s_ctrl->sensor_output_reg_addr->frame_length_lines, fl_lines,
		MSM_CAMERA_I2C_WORD_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		s_ctrl->sensor_exp_gain_info->coarse_int_time_addr, line,
		MSM_CAMERA_I2C_WORD_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		s_ctrl->sensor_exp_gain_info->global_gain_addr, gain,
		MSM_CAMERA_I2C_WORD_DATA);
	s_ctrl->func_tbl->sensor_group_hold_off(s_ctrl);
	CDBG("%s: X\n", __func__);
	return 0;
}

int32_t msm_sensor_write_exp_gain2(struct msm_sensor_ctrl_t *s_ctrl,
		uint16_t gain, uint32_t line)
{
	uint32_t fl_lines, ll_pclk, ll_ratio;
	uint8_t offset;
	fl_lines = s_ctrl->curr_frame_length_lines * s_ctrl->fps_divider / Q10;
	ll_pclk = s_ctrl->curr_line_length_pclk;
	offset = s_ctrl->sensor_exp_gain_info->vert_offset;
	if (line > (fl_lines - offset)) {
		ll_ratio = (line * Q10) / (fl_lines - offset);
		ll_pclk = ll_pclk * ll_ratio / Q10;
		line = fl_lines - offset;
	}

	s_ctrl->func_tbl->sensor_group_hold_on(s_ctrl);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		s_ctrl->sensor_output_reg_addr->line_length_pclk, ll_pclk,
		MSM_CAMERA_I2C_WORD_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		s_ctrl->sensor_exp_gain_info->coarse_int_time_addr, line,
		MSM_CAMERA_I2C_WORD_DATA);
	msm_camera_i2c_write(s_ctrl->sensor_i2c_client,
		s_ctrl->sensor_exp_gain_info->global_gain_addr, gain,
		MSM_CAMERA_I2C_WORD_DATA);
	s_ctrl->func_tbl->sensor_group_hold_off(s_ctrl);
	return 0;
}

int32_t msm_sensor_setting1(struct msm_sensor_ctrl_t *s_ctrl,
			int update_type, int res)
{
	int32_t rc = 0;
	static int csi_config;

	s_ctrl->func_tbl->sensor_stop_stream(s_ctrl);
	msleep(30);
	if (update_type == MSM_SENSOR_REG_INIT) {
		CDBG("Register INIT\n");
		s_ctrl->curr_csi_params = NULL;
		msm_sensor_enable_debugfs(s_ctrl);
		msm_sensor_write_init_settings(s_ctrl);
		csi_config = 0;
	} else if (update_type == MSM_SENSOR_UPDATE_PERIODIC) {
		CDBG("PERIODIC : %d\n", res);
		msm_sensor_write_conf_array(
			s_ctrl->sensor_i2c_client,
			s_ctrl->msm_sensor_reg->mode_settings, res);
		msleep(30);
		if (!csi_config) {
			s_ctrl->curr_csic_params = s_ctrl->csic_params[res];
			CDBG("CSI config in progress\n");
			v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
				NOTIFY_CSIC_CFG,
				s_ctrl->curr_csic_params);
			CDBG("CSI config is done\n");
			mb();
			msleep(30);
			csi_config = 1;
		}
		v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
			NOTIFY_PCLK_CHANGE,
			&s_ctrl->sensordata->pdata->ioclk.vfe_clk_rate);

		s_ctrl->func_tbl->sensor_start_stream(s_ctrl);
		msleep(50);
	}
	return rc;
}

/* OPPO 2012-10-16 yxq added begin for debug */
#ifdef CONFIG_VENDOR_EDIT
int32_t s5k8aay_sensor_setting1(struct msm_sensor_ctrl_t *s_ctrl,
			int update_type, int res)
{
	int32_t rc = 0;
	static int csi_config;

	CDBG("%s: E---update_type=%d, res=%d\n", __func__, update_type, res);
	s_ctrl->func_tbl->sensor_stop_stream(s_ctrl);
	msleep(30);
	if (update_type == MSM_SENSOR_REG_INIT) {
		CDBG("Register INIT\n");
		s_ctrl->curr_csi_params = NULL;
		msm_sensor_enable_debugfs(s_ctrl);
		msm_sensor_write_init_settings(s_ctrl);
		csi_config = 0;
	} else if (update_type == MSM_SENSOR_UPDATE_PERIODIC) {
		CDBG("PERIODIC : %d\n", res);
		msm_sensor_write_conf_array(
			s_ctrl->sensor_i2c_client,
			s_ctrl->msm_sensor_reg->mode_settings, res);
		//msleep(30);
		if (!csi_config) {
			s_ctrl->curr_csic_params = s_ctrl->csic_params[res];
			CDBG("CSI config in progress\n");
			v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
				NOTIFY_CSIC_CFG,
				s_ctrl->curr_csic_params);
			CDBG("CSI config is done\n");
			mb();
			//msleep(30);
			msleep(20);
			csi_config = 1;
		}
		v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
			NOTIFY_PCLK_CHANGE,
			&s_ctrl->sensordata->pdata->ioclk.vfe_clk_rate);

		s_ctrl->func_tbl->sensor_start_stream(s_ctrl);
		msleep(30);
	}
	CDBG("%s: X\n", __func__);
	return rc;
}
#endif
/* OPPO 2012-10-16 yxq added end */

int32_t msm_sensor_setting(struct msm_sensor_ctrl_t *s_ctrl,
			int update_type, int res)
{
	int32_t rc = 0;

	CDBG("%s: E---update_type=%d, res=%d\n", __func__, update_type, res);
	s_ctrl->func_tbl->sensor_stop_stream(s_ctrl);
	msleep(30);
	if (update_type == MSM_SENSOR_REG_INIT) {
		s_ctrl->curr_csi_params = NULL;
		msm_sensor_enable_debugfs(s_ctrl);
		msm_sensor_write_init_settings(s_ctrl);
	} else if (update_type == MSM_SENSOR_UPDATE_PERIODIC) {
		msm_sensor_write_res_settings(s_ctrl, res);
		if (s_ctrl->curr_csi_params != s_ctrl->csi_params[res]) {
			s_ctrl->curr_csi_params = s_ctrl->csi_params[res];
			s_ctrl->curr_csi_params->csid_params.lane_assign =
				s_ctrl->sensordata->sensor_platform_info->
				csi_lane_params->csi_lane_assign;
			s_ctrl->curr_csi_params->csiphy_params.lane_mask =
				s_ctrl->sensordata->sensor_platform_info->
				csi_lane_params->csi_lane_mask;
			v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
				NOTIFY_CSID_CFG,
				&s_ctrl->curr_csi_params->csid_params);
			mb();
			v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
				NOTIFY_CSIPHY_CFG,
				&s_ctrl->curr_csi_params->csiphy_params);
			mb();
			msleep(20);
		}

		v4l2_subdev_notify(&s_ctrl->sensor_v4l2_subdev,
			NOTIFY_PCLK_CHANGE, &s_ctrl->msm_sensor_reg->
			output_settings[res].op_pixel_clk);
		s_ctrl->func_tbl->sensor_start_stream(s_ctrl);
		msleep(30);
	}
	CDBG("%s: X\n", __func__);
	return rc;
}

int32_t msm_sensor_set_sensor_mode(struct msm_sensor_ctrl_t *s_ctrl,
	int mode, int res)
{
	int32_t rc = 0;

	CDBG("%s: E---mode=%d, res=%d\n", __func__, mode, res);
	if (s_ctrl->curr_res != res) {
		s_ctrl->curr_frame_length_lines =
			s_ctrl->msm_sensor_reg->
			output_settings[res].frame_length_lines;

		s_ctrl->curr_line_length_pclk =
			s_ctrl->msm_sensor_reg->
			output_settings[res].line_length_pclk;
		/* Qualcomm Release */
		if (s_ctrl->is_csic ||
			!s_ctrl->sensordata->csi_if)
			rc = s_ctrl->func_tbl->sensor_csi_setting(s_ctrl,
				MSM_SENSOR_UPDATE_PERIODIC, res);
		else
			rc = s_ctrl->func_tbl->sensor_setting(s_ctrl,
				MSM_SENSOR_UPDATE_PERIODIC, res);
		if (rc < 0)
			return rc;
		s_ctrl->curr_res = res;
	}
	CDBG("%s: X\n", __func__);

	return rc;
}

int32_t msm_sensor_mode_init(struct msm_sensor_ctrl_t *s_ctrl,
			int mode, struct sensor_init_cfg *init_info)
{
	int32_t rc = 0;
	s_ctrl->fps_divider = Q10;
	s_ctrl->cam_mode = MSM_SENSOR_MODE_INVALID;

	CDBG("%s: E---mode=%d\n", __func__, mode);
/* OPPO 2012-10-11 yxq added begin for null point */
#ifdef CONFIG_VENDOR_EDIT
	CDBG("%s: s_ctrl->cam_mode=%d", __func__, s_ctrl->cam_mode);
	CDBG("%s: s_ctrl->is_csic=%d", __func__, s_ctrl->is_csic);
	CDBG("%s: s_ctrl->sensordata->csi_if=%d", __func__, s_ctrl->sensordata->csi_if);
#endif
/* OPPO 2012-10-11 yxq added end */
	if (mode != s_ctrl->cam_mode) {
		s_ctrl->curr_res = MSM_SENSOR_INVALID_RES;
		s_ctrl->cam_mode = mode;

		if (s_ctrl->is_csic ||
			!s_ctrl->sensordata->csi_if)
			rc = s_ctrl->func_tbl->sensor_csi_setting(s_ctrl,
				MSM_SENSOR_REG_INIT, 0);
		else
			rc = s_ctrl->func_tbl->sensor_setting(s_ctrl,
				MSM_SENSOR_REG_INIT, 0);
	}
	CDBG("%s: X\n", __func__);
	return rc;
}

int32_t msm_sensor_get_output_info(struct msm_sensor_ctrl_t *s_ctrl,
		struct sensor_output_info_t *sensor_output_info)
{
	int rc = 0;

	CDBG("%s: E\n", __func__);
	sensor_output_info->num_info = s_ctrl->msm_sensor_reg->num_conf;
	if (copy_to_user((void *)sensor_output_info->output_info,
		s_ctrl->msm_sensor_reg->output_settings,
		sizeof(struct msm_sensor_output_info_t) *
		s_ctrl->msm_sensor_reg->num_conf))
		rc = -EFAULT;
	CDBG("%s: X\n", __func__);

	return rc;
}

int32_t msm_sensor_release(struct msm_sensor_ctrl_t *s_ctrl)
{
	long fps = 0;
	uint32_t delay = 0;

	CDBG("%s: E\n", __func__);
	s_ctrl->func_tbl->sensor_stop_stream(s_ctrl);
	if (s_ctrl->curr_res != MSM_SENSOR_INVALID_RES) {
		fps = s_ctrl->msm_sensor_reg->
			output_settings[s_ctrl->curr_res].vt_pixel_clk /
			s_ctrl->curr_frame_length_lines /
			s_ctrl->curr_line_length_pclk;
		delay = 1000 / fps;
		CDBG("%s fps = %ld, delay = %d\n", __func__, fps, delay);
		msleep(delay);
	}
	CDBG("%s: X\n", __func__);
	return 0;
}

long msm_sensor_subdev_ioctl(struct v4l2_subdev *sd,
			unsigned int cmd, void *arg)
{
	struct msm_sensor_ctrl_t *s_ctrl = get_sctrl(sd);
	void __user *argp = (void __user *)arg;

	CDBG("%s: E---cmd=%d\n", __func__, cmd);
	switch (cmd) {
	case VIDIOC_MSM_SENSOR_CFG:
		return s_ctrl->func_tbl->sensor_config(s_ctrl, argp);
	case VIDIOC_MSM_SENSOR_RELEASE:
		return msm_sensor_release(s_ctrl);
	case VIDIOC_MSM_SENSOR_CSID_INFO: {
		struct msm_sensor_csi_info *csi_info =
			(struct msm_sensor_csi_info *)arg;
		s_ctrl->csid_version = csi_info->csid_version;
		s_ctrl->is_csic = csi_info->is_csic;
		CDBG("%s: csid_version=%d, is_csic=%d\n", __func__, s_ctrl->csid_version, s_ctrl->is_csic);
		return 0;
	}
	default:
		return -ENOIOCTLCMD;
	}
	CDBG("%s: X\n", __func__);
}

int32_t msm_sensor_get_csi_params(struct msm_sensor_ctrl_t *s_ctrl,
		struct csi_lane_params_t *sensor_output_info)
{
	CDBG("%s: E\n", __func__);
	sensor_output_info->csi_lane_assign = s_ctrl->sensordata->
		sensor_platform_info->csi_lane_params->csi_lane_assign;
	sensor_output_info->csi_lane_mask = s_ctrl->sensordata->
		sensor_platform_info->csi_lane_params->csi_lane_mask;
	sensor_output_info->csi_if = s_ctrl->sensordata->csi_if;
	sensor_output_info->csid_core = s_ctrl->sensordata->
			pdata[0].csid_core;
	sensor_output_info->csid_version = s_ctrl->csid_version;
	CDBG("%s: X\n", __func__);
	return 0;
}

int32_t msm_sensor_config(struct msm_sensor_ctrl_t *s_ctrl, void __user *argp)
{
	struct sensor_cfg_data cdata;
	long   rc = 0;
	if (copy_from_user(&cdata,
		(void *)argp,
		sizeof(struct sensor_cfg_data)))
		return -EFAULT;
	mutex_lock(s_ctrl->msm_sensor_mutex);
	CDBG("%s: E---cfgtype = %d\n", __func__, cdata.cfgtype);
		switch (cdata.cfgtype) {
		case CFG_SET_FPS:
		case CFG_SET_PICT_FPS:
			if (s_ctrl->func_tbl->
			sensor_set_fps == NULL) {
				rc = -EFAULT;
				break;
			}
			rc = s_ctrl->func_tbl->
				sensor_set_fps(
				s_ctrl,
				&(cdata.cfg.fps));
			break;

		case CFG_SET_EXP_GAIN:
			if (s_ctrl->func_tbl->
			sensor_write_exp_gain == NULL) {
				rc = -EFAULT;
				break;
			}
			rc =
				s_ctrl->func_tbl->
				sensor_write_exp_gain(
					s_ctrl,
					cdata.cfg.exp_gain.gain,
					cdata.cfg.exp_gain.line);
			s_ctrl->prev_gain = cdata.cfg.exp_gain.gain;
			s_ctrl->prev_line = cdata.cfg.exp_gain.line;
			break;

		case CFG_SET_PICT_EXP_GAIN:
			if (s_ctrl->func_tbl->
			sensor_write_snapshot_exp_gain == NULL) {
				rc = -EFAULT;
				break;
			}
			rc =
				s_ctrl->func_tbl->
				sensor_write_snapshot_exp_gain(
					s_ctrl,
					cdata.cfg.exp_gain.gain,
					cdata.cfg.exp_gain.line);
			break;

		case CFG_SET_MODE:
			if (s_ctrl->func_tbl->
			sensor_set_sensor_mode == NULL) {
				rc = -EFAULT;
				break;
			}
			rc = s_ctrl->func_tbl->
				sensor_set_sensor_mode(
					s_ctrl,
					cdata.mode,
					cdata.rs);
			break;

		case CFG_SET_EFFECT:
			break;

		case CFG_SENSOR_INIT:
			if (s_ctrl->func_tbl->
			sensor_mode_init == NULL) {
				rc = -EFAULT;
				break;
			}
			rc = s_ctrl->func_tbl->
				sensor_mode_init(
				s_ctrl,
				cdata.mode,
				&(cdata.cfg.init_info));
			break;

		case CFG_GET_OUTPUT_INFO:
			if (s_ctrl->func_tbl->
			sensor_get_output_info == NULL) {
				rc = -EFAULT;
				break;
			}
			rc = s_ctrl->func_tbl->
				sensor_get_output_info(
				s_ctrl,
				&cdata.cfg.output_info);

			if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
				rc = -EFAULT;
			break;

		case CFG_START_STREAM:
			if (s_ctrl->func_tbl->sensor_start_stream == NULL) {
				rc = -EFAULT;
				break;
			}
			s_ctrl->func_tbl->sensor_start_stream(s_ctrl);
			break;

		case CFG_STOP_STREAM:
			if (s_ctrl->func_tbl->sensor_stop_stream == NULL) {
				rc = -EFAULT;
				break;
			}
			s_ctrl->func_tbl->sensor_stop_stream(s_ctrl);
			break;

		case CFG_GET_CSI_PARAMS:
			if (s_ctrl->func_tbl->sensor_get_csi_params == NULL) {
				rc = -EFAULT;
				break;
			}
			rc = s_ctrl->func_tbl->sensor_get_csi_params(
				s_ctrl,
				&cdata.cfg.csi_lane_params);

			if (copy_to_user((void *)argp,
				&cdata,
				sizeof(struct sensor_cfg_data)))
				rc = -EFAULT;
			break;

		default:
			rc = -EFAULT;
			break;
		}

	mutex_unlock(s_ctrl->msm_sensor_mutex);
	CDBG("%s: X\n", __func__);

	return rc;
}

static struct msm_cam_clk_info cam_clk_info[] = {
	{"cam_clk", MSM_SENSOR_MCLK_24HZ},
};

int32_t msm_sensor_enable_i2c_mux(struct msm_camera_i2c_conf *i2c_conf)
{
	struct v4l2_subdev *i2c_mux_sd =
		dev_get_drvdata(&i2c_conf->mux_dev->dev);
	v4l2_subdev_call(i2c_mux_sd, core, ioctl,
		VIDIOC_MSM_I2C_MUX_INIT, NULL);
	v4l2_subdev_call(i2c_mux_sd, core, ioctl,
		VIDIOC_MSM_I2C_MUX_CFG, (void *)&i2c_conf->i2c_mux_mode);
	return 0;
}

int32_t msm_sensor_disable_i2c_mux(struct msm_camera_i2c_conf *i2c_conf)
{
	struct v4l2_subdev *i2c_mux_sd =
		dev_get_drvdata(&i2c_conf->mux_dev->dev);
	v4l2_subdev_call(i2c_mux_sd, core, ioctl,
				VIDIOC_MSM_I2C_MUX_RELEASE, NULL);
	return 0;
}

int32_t msm_sensor_power_up(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;
	struct msm_camera_sensor_info *data = s_ctrl->sensordata;
	CDBG("%s: %d\n", __func__, __LINE__);
	s_ctrl->reg_ptr = kzalloc(sizeof(struct regulator *)
			* data->sensor_platform_info->num_vreg, GFP_KERNEL);
	if (!s_ctrl->reg_ptr) {
		pr_err("%s: could not allocate mem for regulators\n",
			__func__);
		return -ENOMEM;
	}

	rc = msm_camera_request_gpio_table(data, 1);
	if (rc < 0) {
		pr_err("%s: request gpio failed\n", __func__);
		goto request_gpio_failed;
	}

	rc = msm_camera_config_vreg(&s_ctrl->sensor_i2c_client->client->dev,
			s_ctrl->sensordata->sensor_platform_info->cam_vreg,
			s_ctrl->sensordata->sensor_platform_info->num_vreg,
			s_ctrl->reg_ptr, 1);
	if (rc < 0) {
		pr_err("%s: regulator on failed\n", __func__);
		goto config_vreg_failed;
	}

	rc = msm_camera_enable_vreg(&s_ctrl->sensor_i2c_client->client->dev,
			s_ctrl->sensordata->sensor_platform_info->cam_vreg,
			s_ctrl->sensordata->sensor_platform_info->num_vreg,
			s_ctrl->reg_ptr, 1);
	if (rc < 0) {
		pr_err("%s: enable regulator failed\n", __func__);
		goto enable_vreg_failed;
	}

	rc = msm_camera_config_gpio_table(data, 1);
	if (rc < 0) {
		pr_err("%s: config gpio failed\n", __func__);
		goto config_gpio_failed;
	}

	if (s_ctrl->clk_rate != 0)
		cam_clk_info->clk_rate = s_ctrl->clk_rate;

	rc = msm_cam_clk_enable(&s_ctrl->sensor_i2c_client->client->dev,
		cam_clk_info, &s_ctrl->cam_clk, ARRAY_SIZE(cam_clk_info), 1);
	if (rc < 0) {
		pr_err("%s: clk enable failed\n", __func__);
		goto enable_clk_failed;
	}

	usleep_range(1000, 2000);
	if (data->sensor_platform_info->ext_power_ctrl != NULL)
		data->sensor_platform_info->ext_power_ctrl(1);

	if (data->sensor_platform_info->i2c_conf &&
		data->sensor_platform_info->i2c_conf->use_i2c_mux)
		msm_sensor_enable_i2c_mux(data->sensor_platform_info->i2c_conf);

	return rc;

enable_clk_failed:
		msm_camera_config_gpio_table(data, 0);
config_gpio_failed:
	msm_camera_enable_vreg(&s_ctrl->sensor_i2c_client->client->dev,
			s_ctrl->sensordata->sensor_platform_info->cam_vreg,
			s_ctrl->sensordata->sensor_platform_info->num_vreg,
			s_ctrl->reg_ptr, 0);

enable_vreg_failed:
	msm_camera_config_vreg(&s_ctrl->sensor_i2c_client->client->dev,
		s_ctrl->sensordata->sensor_platform_info->cam_vreg,
		s_ctrl->sensordata->sensor_platform_info->num_vreg,
		s_ctrl->reg_ptr, 0);
config_vreg_failed:
	msm_camera_request_gpio_table(data, 0);
request_gpio_failed:
	kfree(s_ctrl->reg_ptr);
	return rc;
}

int32_t msm_sensor_power_down(struct msm_sensor_ctrl_t *s_ctrl)
{
	struct msm_camera_sensor_info *data = s_ctrl->sensordata;
	CDBG("%s\n", __func__);
	if (data->sensor_platform_info->i2c_conf &&
		data->sensor_platform_info->i2c_conf->use_i2c_mux)
		msm_sensor_disable_i2c_mux(
			data->sensor_platform_info->i2c_conf);

	if (data->sensor_platform_info->ext_power_ctrl != NULL)
		data->sensor_platform_info->ext_power_ctrl(0);
	msm_cam_clk_enable(&s_ctrl->sensor_i2c_client->client->dev,
		cam_clk_info, &s_ctrl->cam_clk, ARRAY_SIZE(cam_clk_info), 0);
	msm_camera_config_gpio_table(data, 0);
	msm_camera_enable_vreg(&s_ctrl->sensor_i2c_client->client->dev,
		s_ctrl->sensordata->sensor_platform_info->cam_vreg,
		s_ctrl->sensordata->sensor_platform_info->num_vreg,
		s_ctrl->reg_ptr, 0);
	msm_camera_config_vreg(&s_ctrl->sensor_i2c_client->client->dev,
		s_ctrl->sensordata->sensor_platform_info->cam_vreg,
		s_ctrl->sensordata->sensor_platform_info->num_vreg,
		s_ctrl->reg_ptr, 0);
	msm_camera_request_gpio_table(data, 0);
	kfree(s_ctrl->reg_ptr);
	return 0;
}

/* OPPO 2012-10-10 yxq added begin for another power up pattern */
#ifdef CONFIG_VENDOR_EDIT

	static struct regulator *ldo8;
	static struct regulator *lvs0;
	static struct regulator *ldo25;
	static struct regulator *fs_vfe;
	static struct regulator *ldo4;
	static struct regulator *lvs2;
	static struct regulator *ldo1;

int32_t imx111_sensor_power_up(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;
	struct msm_camera_sensor_info *data = s_ctrl->sensordata;

	CDBG("%s: %d\n", __func__, __LINE__);
	
	// Request GPIO
	rc = msm_camera_request_gpio_table(data, 1);
	if (rc < 0) {
		pr_err("%s: request gpio failed\n", __func__);
		goto request_gpio_failed;
	}
	
	// Config voltage
	ldo8 = regulator_get(NULL, "8058_l8");
	if (IS_ERR(ldo8)) {
		pr_err("%s: VREG ldo8 get failed\n", __func__);
		ldo8 = NULL;
		goto ldo8_get_failed;
	}
	if (regulator_set_voltage(ldo8, 2700000, 2700000)) {
		pr_err("%s: VREG ldo8 set voltage failed\n",  __func__);
		goto ldo8_set_voltage_failed;
	}
	if (regulator_enable(ldo8)) {
		pr_err("%s: VREG ldo8 enable failed\n", __func__);
		goto ldo8_enable_failed;
	}

	lvs0 = regulator_get(NULL, "8058_lvs0");
	if (IS_ERR(lvs0)) {
		pr_err("%s: VREG LVS0 get failed\n", __func__);
		lvs0 = NULL;
		goto lvs0_get_failed;
	}
	if (regulator_enable(lvs0)) {
		pr_err("%s: VREG LVS0 enable failed\n", __func__);
		goto lvs0_enable_failed;
	}

	ldo25 = regulator_get(NULL, "8058_l25");
	if (IS_ERR(ldo25)) {
		pr_err("%s: VREG LDO25 get failed\n", __func__);
		ldo25 = NULL;
		goto ldo25_get_failed;
	}
	if (regulator_set_voltage(ldo25, 1200000, 1200000)) {
		pr_err("%s: VREG LDO25 set voltage failed\n",  __func__);
		goto ldo25_set_voltage_failed;
	}
	if (regulator_enable(ldo25)) {
		pr_err("%s: VREG LDO25 enable failed\n", __func__);
		goto ldo25_enable_failed;
	}
	
	fs_vfe = regulator_get(NULL, "fs_vfe");
	if (IS_ERR(fs_vfe)) {
		CDBG("%s: Regulator FS_VFE get failed %ld\n", __func__,
			PTR_ERR(fs_vfe));
		fs_vfe = NULL;
		goto fs_vfe_get_failed;
	} else if (regulator_enable(fs_vfe)) {
		CDBG("%s: Regulator FS_VFE enable failed\n", __func__);
		goto fs_vfe_enable_failed;
	}
	msleep(1);
	
	//Enable MCLK
	if (s_ctrl->clk_rate != 0)
		cam_clk_info->clk_rate = s_ctrl->clk_rate;
	rc = msm_cam_clk_enable(&s_ctrl->sensor_i2c_client->client->dev,
		cam_clk_info, &s_ctrl->cam_clk, ARRAY_SIZE(cam_clk_info), 1);
	if (rc < 0) {
		pr_err("%s: clk enable failed\n", __func__);
		goto enable_clk_failed;
	}
	msleep(1);
	
	//Config GPIO
	rc = msm_camera_config_gpio_table(data, 1);
	if (rc < 0) {
		pr_err("%s: config gpio failed\n", __func__);
		goto config_gpio_failed;
	}

	usleep_range(1000, 2000);
	if (data->sensor_platform_info->ext_power_ctrl != NULL)
		data->sensor_platform_info->ext_power_ctrl(1);

	if (data->sensor_platform_info->i2c_conf &&
		data->sensor_platform_info->i2c_conf->use_i2c_mux)
		msm_sensor_enable_i2c_mux(data->sensor_platform_info->i2c_conf);

	return rc;

config_gpio_failed:
		msm_cam_clk_enable(&s_ctrl->sensor_i2c_client->client->dev,
			cam_clk_info, &s_ctrl->cam_clk, ARRAY_SIZE(cam_clk_info), 0);
enable_clk_failed:
		regulator_disable(fs_vfe);
fs_vfe_enable_failed:
		regulator_put(fs_vfe);
fs_vfe_get_failed:
		regulator_disable(ldo25);
ldo25_enable_failed:
ldo25_set_voltage_failed:
		regulator_put(ldo25);
ldo25_get_failed:
		regulator_disable(lvs0);
lvs0_enable_failed:
		regulator_put(lvs0);
lvs0_get_failed:
		regulator_disable(ldo8);
ldo8_enable_failed:
ldo8_set_voltage_failed:
		regulator_put(ldo8);
ldo8_get_failed:
		msm_camera_request_gpio_table(data, 0);
request_gpio_failed:
		return rc;
}

int32_t imx111_sensor_power_down(struct msm_sensor_ctrl_t *s_ctrl)
{
	struct msm_camera_sensor_info *data = s_ctrl->sensordata;
	CDBG("%s\n", __func__);
	if (data->sensor_platform_info->i2c_conf &&
		data->sensor_platform_info->i2c_conf->use_i2c_mux)
		msm_sensor_disable_i2c_mux(
			data->sensor_platform_info->i2c_conf);

	if (data->sensor_platform_info->ext_power_ctrl != NULL)
		data->sensor_platform_info->ext_power_ctrl(0);
	
	// Disable MCLK
	msm_cam_clk_enable(&s_ctrl->sensor_i2c_client->client->dev,
		cam_clk_info, &s_ctrl->cam_clk, ARRAY_SIZE(cam_clk_info), 0);
	
	// Disable GPIO
	msm_camera_config_gpio_table(data, 0);
	
	// Shutdown voltage
	if (ldo8) {
		regulator_disable(ldo8);
		regulator_put(ldo8);
	}
	if (lvs0) {
		regulator_disable(lvs0);
		regulator_put(lvs0);
	}
	if (ldo25) {
		regulator_disable(ldo25);
		regulator_put(ldo25);
	}
	if (fs_vfe) {
		regulator_disable(fs_vfe);
		regulator_put(fs_vfe);
	}
	// Release GPIO
	msm_camera_request_gpio_table(data, 0);
	
	return 0;
}

int32_t s5k8aay_sensor_power_up(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;
	struct msm_camera_sensor_info *data = s_ctrl->sensordata;

	CDBG("%s: %d\n", __func__, __LINE__);

	// Request GPIO
	rc = msm_camera_request_gpio_table(data, 1);
	if (rc < 0) {
		pr_err("%s: request gpio failed\n", __func__);
		goto request_gpio_failed;
	}

	// Config voltage
	ldo4 = regulator_get(NULL, "8901_l4");
	if (IS_ERR(ldo4)) {
		pr_err("%s: VREG ldo4 get failed\n", __func__);
		ldo4 = NULL;
		goto ldo4_get_failed;
	}
	if (regulator_set_voltage(ldo4, 2850000, 2850000)) {
		pr_err("%s: VREG ldo4 set voltage failed\n",  __func__);
		goto ldo4_set_voltage_failed;
	}
	if (regulator_enable(ldo4)) {
		pr_err("%s: VREG ldo4 enable failed\n", __func__);
		goto ldo4_enable_failed;
	}

	lvs2 = regulator_get(NULL, "8901_lvs2");
	if (IS_ERR(lvs2)) {
		pr_err("%s: VREG LVS2 get failed\n", __func__);
		lvs2 = NULL;
		goto lvs2_get_failed;
	}
	if (regulator_enable(lvs2)) {
		pr_err("%s: VREG LVS2 enable failed\n", __func__);
		goto lvs2_enable_failed;
	}

	ldo1 = regulator_get(NULL, "8058_l1");
	if (IS_ERR(ldo1)) {
		pr_err("%s: VREG LDO1 get failed\n", __func__);
		ldo1 = NULL;
		goto ldo1_get_failed;
	}
	if (regulator_set_voltage(ldo1, 1200000, 1200000)) {
		pr_err("%s: VREG LDO1 set voltage failed\n",  __func__);
		goto ldo1_set_voltage_failed;
	}
	if (regulator_enable(ldo1)) {
		pr_err("%s: VREG LDO1 enable failed\n", __func__);
		goto ldo1_enable_failed;
	}

	fs_vfe = regulator_get(NULL, "fs_vfe");
	if (IS_ERR(fs_vfe)) {
		CDBG("%s: Regulator FS_VFE get failed %ld\n", __func__,
			PTR_ERR(fs_vfe));
		fs_vfe = NULL;
		goto fs_vfe_get_failed;
	} else if (regulator_enable(fs_vfe)) {
		CDBG("%s: Regulator FS_VFE enable failed\n", __func__);
		goto fs_vfe_enable_failed;
	}
	msleep(5);

	// Enable MCLK
	if (s_ctrl->clk_rate != 0)
		cam_clk_info->clk_rate = s_ctrl->clk_rate;
	rc = msm_cam_clk_enable(&s_ctrl->sensor_i2c_client->client->dev,
		cam_clk_info, &s_ctrl->cam_clk, ARRAY_SIZE(cam_clk_info), 1);
	if (rc < 0) {
		pr_err("%s: clk enable failed\n", __func__);
		goto enable_clk_failed;
	}
	CDBG("%s: s_ctrl->clk_rate is %ld\n", __func__, s_ctrl->clk_rate);
	msleep(5);

	// Config GPIO
	gpio_direction_output(45, 0);
	msleep(10);
	gpio_direction_output(45, 1);
	msleep(10);
	gpio_direction_output(72,0);
	msleep(10);
	gpio_direction_output(72,1);
	msleep(10);
	if (rc < 0) {
		pr_err("%s: config gpio failed\n", __func__);
		goto config_gpio_failed;
	}

	usleep_range(1000, 2000);
	if (data->sensor_platform_info->ext_power_ctrl != NULL)
		{
			data->sensor_platform_info->ext_power_ctrl(1);
			CDBG("data->sensor_platform_info->ext_power_ctrl != NULL\n");
		}

	if (data->sensor_platform_info->i2c_conf &&
		data->sensor_platform_info->i2c_conf->use_i2c_mux)
		{
			msm_sensor_enable_i2c_mux(data->sensor_platform_info->i2c_conf);
		}

	return rc;

config_gpio_failed:
		msm_cam_clk_enable(&s_ctrl->sensor_i2c_client->client->dev,
			cam_clk_info, &s_ctrl->cam_clk, ARRAY_SIZE(cam_clk_info), 0);
enable_clk_failed:
		regulator_disable(fs_vfe);
fs_vfe_enable_failed:
		regulator_put(fs_vfe);
fs_vfe_get_failed:
		regulator_disable(ldo1);
ldo1_enable_failed:
ldo1_set_voltage_failed:
		regulator_put(ldo25);
ldo1_get_failed:
		regulator_disable(lvs2);
lvs2_enable_failed:
		regulator_put(lvs2);
lvs2_get_failed:
		regulator_disable(ldo4);
ldo4_enable_failed:
ldo4_set_voltage_failed:
		regulator_put(ldo4);
ldo4_get_failed:
		msm_camera_request_gpio_table(data, 0);
request_gpio_failed:
		return rc;
}

int32_t s5k8aay_sensor_power_down(struct msm_sensor_ctrl_t *s_ctrl)
{
	struct msm_camera_sensor_info *data = s_ctrl->sensordata;
	CDBG("%s\n", __func__);
	if (data->sensor_platform_info->i2c_conf &&
		data->sensor_platform_info->i2c_conf->use_i2c_mux)
		msm_sensor_disable_i2c_mux(
			data->sensor_platform_info->i2c_conf);

	if (data->sensor_platform_info->ext_power_ctrl != NULL)
		data->sensor_platform_info->ext_power_ctrl(0);
	// Disable MCLK
	msm_cam_clk_enable(&s_ctrl->sensor_i2c_client->client->dev,
		cam_clk_info, &s_ctrl->cam_clk, ARRAY_SIZE(cam_clk_info), 0);

	// Disable GPIO
	gpio_set_value_cansleep(45, 0);
	msleep(10);
	gpio_set_value_cansleep(72, 0);
	msleep(10);

	// Shutdown voltage
	if (ldo4) {
		regulator_disable(ldo4);
		regulator_put(ldo4);
	}
	if (lvs2) {
		regulator_disable(lvs2);
		regulator_put(lvs2);
	}
	if (ldo1) {
		regulator_disable(ldo1);
		regulator_put(ldo1);
	}
	if (fs_vfe) {
		regulator_disable(fs_vfe);
		regulator_put(fs_vfe);
	}

	// Release GPIO
	msm_camera_request_gpio_table(data, 0);

	return 0;
}
#endif
/* OPPO 2012-10-10 yxq added end */

int32_t msm_sensor_match_id(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;
	uint16_t chipid = 0;
    uint16_t Product_eigenvalue;
    
/* OPPO 2012-08-06 yxq added begin for front camera */
#ifdef CONFIG_VENDOR_EDIT
	CDBG("msm_sensor_id_reg_addr: %x\n", s_ctrl->sensor_id_info->sensor_id_reg_addr);
	if (s_ctrl->sensor_id_info->sensor_id_reg_addr == 0x0040)
		{
			msm_camera_i2c_write(s_ctrl->sensor_i2c_client, 0x002C, 0x0000,
				MSM_CAMERA_I2C_WORD_DATA);
			msm_camera_i2c_write(s_ctrl->sensor_i2c_client, 0x002E, 0x0040,
				MSM_CAMERA_I2C_WORD_DATA);
			rc = msm_camera_i2c_read(
				s_ctrl->sensor_i2c_client,
				0x0F12, &chipid,
				MSM_CAMERA_I2C_WORD_DATA);
			CDBG("msm_sensor name: %s\n", s_ctrl->sensordata->sensor_name);
			CDBG("msm_sensor id: %x\n", chipid);
			return rc;
		}
#endif
/* OPPO 2012-08-06 yxq added end */
	rc = msm_camera_i2c_read(
			s_ctrl->sensor_i2c_client,
			s_ctrl->sensor_id_info->sensor_id_reg_addr, &chipid,
			MSM_CAMERA_I2C_WORD_DATA);
	if (rc < 0) {
		pr_err("%s: %s: read id failed\n", __func__,
			s_ctrl->sensordata->sensor_name);
		return rc;
	}

	CDBG("msm_sensor name: %s\n", s_ctrl->sensordata->sensor_name);
	CDBG("msm_sensor id: %x\n", chipid);
	if (chipid != s_ctrl->sensor_id_info->sensor_id) {
		pr_err("msm_sensor_match_id chip id doesnot match\n");
		return -ENODEV;
	}

/* OPPO 2012-10-25 liuwd add begin for vcm compatibility*/
#ifdef CONFIG_VENDOR_EDIT
/* OPPO 2013-03-07 leihui Delete begin for reason */
#if 0
    msm_camera_i2c_write(s_ctrl->sensor_i2c_client, 0x34C9 , 0x00, MSM_CAMERA_I2C_BYTE_DATA);

    rc = msm_camera_i2c_read(
       s_ctrl->sensor_i2c_client, 
       0x3500 , &Product_eigenvalue,
       MSM_CAMERA_I2C_WORD_DATA);
    
	if (rc < 0) {
		pr_err("%s: %s: read id failed\n", __func__,
			s_ctrl->sensordata->sensor_name);
    }

    printk(KERN_ERR"%s : value_h = 0x%x\n",__func__,Product_eigenvalue);

    if( 0x1113 != Product_eigenvalue)
    {
        s_ctrl->sensordata->actuator_info->cam_name = MSM_ACTUATOR_MAIN_CAM_0;
    }
#else

    msm_camera_i2c_write(s_ctrl->sensor_i2c_client, 0x34C9 , 0x00, MSM_CAMERA_I2C_BYTE_DATA);

    rc = msm_camera_i2c_read(
       s_ctrl->sensor_i2c_client, 
       0x3500 , &Product_eigenvalue,
       MSM_CAMERA_I2C_BYTE_DATA);    
	if (rc < 0) {
		pr_err("%s: %s: read id failed\n", __func__,
			s_ctrl->sensordata->sensor_name);
    }

    printk(KERN_ERR"#######%s : value_h = 0x%x\n",__func__,Product_eigenvalue);

    if( 0x25 == Product_eigenvalue)
    {
        s_ctrl->sensordata->actuator_info->cam_name = MSM_ACTUATOR_MAIN_CAM_2;
    }
    else if(0x11 == Product_eigenvalue)
    {
        s_ctrl->sensordata->actuator_info->cam_name = MSM_ACTUATOR_MAIN_CAM_1;
    }
    else
    {
        s_ctrl->sensordata->actuator_info->cam_name = MSM_ACTUATOR_MAIN_CAM_0;
    }
    
#endif
/* OPPO 2013-03-07 leihui Delete end */
#endif
/* OPPO 2012-10-25 liuwd add end */

	return rc;
}

struct msm_sensor_ctrl_t *get_sctrl(struct v4l2_subdev *sd)
{
	return container_of(sd, struct msm_sensor_ctrl_t, sensor_v4l2_subdev);
}

int32_t msm_sensor_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;
	struct msm_sensor_ctrl_t *s_ctrl;
	CDBG("%s %s_i2c_probe called\n", __func__, client->name);
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		pr_err("%s %s i2c_check_functionality failed\n",
			__func__, client->name);
		rc = -EFAULT;
		return rc;
	}

	s_ctrl = (struct msm_sensor_ctrl_t *)(id->driver_data);
	if (s_ctrl->sensor_i2c_client != NULL) {
		s_ctrl->sensor_i2c_client->client = client;
		if (s_ctrl->sensor_i2c_addr != 0)
			s_ctrl->sensor_i2c_client->client->addr =
				s_ctrl->sensor_i2c_addr;
	} else {
		pr_err("%s %s sensor_i2c_client NULL\n",
			__func__, client->name);
		rc = -EFAULT;
		return rc;
	}

	s_ctrl->sensordata = client->dev.platform_data;
	if (s_ctrl->sensordata == NULL) {
		pr_err("%s %s NULL sensor data\n", __func__, client->name);
		return -EFAULT;
	}

	rc = s_ctrl->func_tbl->sensor_power_up(s_ctrl);
	if (rc < 0) {
		pr_err("%s %s power up failed\n", __func__, client->name);
		return rc;
	}

	if (s_ctrl->func_tbl->sensor_match_id)
		rc = s_ctrl->func_tbl->sensor_match_id(s_ctrl);
	else
		rc = msm_sensor_match_id(s_ctrl);
	if (rc < 0)
		goto probe_fail;

	snprintf(s_ctrl->sensor_v4l2_subdev.name,
		sizeof(s_ctrl->sensor_v4l2_subdev.name), "%s", id->name);
	v4l2_i2c_subdev_init(&s_ctrl->sensor_v4l2_subdev, client,
		s_ctrl->sensor_v4l2_subdev_ops);

	msm_sensor_register(&s_ctrl->sensor_v4l2_subdev);
	goto power_down;
probe_fail:
	pr_err("%s %s_i2c_probe failed\n", __func__, client->name);
power_down:
	if (rc > 0)
		rc = 0;
	s_ctrl->func_tbl->sensor_power_down(s_ctrl);
	return rc;
}

int32_t msm_sensor_power(struct v4l2_subdev *sd, int on)
{
	int rc = 0;
	struct msm_sensor_ctrl_t *s_ctrl = get_sctrl(sd);

	CDBG("%s: E---on=%d\n", __func__, on);
	mutex_lock(s_ctrl->msm_sensor_mutex);
	if (on) {
		rc = s_ctrl->func_tbl->sensor_power_up(s_ctrl);
		if (rc < 0) {
			pr_err("%s: %s power_up failed rc = %d\n", __func__,
				s_ctrl->sensordata->sensor_name, rc);
		} else {
			if (s_ctrl->func_tbl->sensor_match_id)
				rc = s_ctrl->func_tbl->sensor_match_id(s_ctrl);
			else
				rc = msm_sensor_match_id(s_ctrl);
			if (rc < 0) {
				pr_err("%s: %s match_id failed  rc=%d\n",
					__func__,
					s_ctrl->sensordata->sensor_name, rc);
				if (s_ctrl->func_tbl->sensor_power_down(s_ctrl)
					< 0)
					pr_err("%s: %s power_down failed\n",
					__func__,
					s_ctrl->sensordata->sensor_name);
			}
		}
	} else {
		rc = s_ctrl->func_tbl->sensor_power_down(s_ctrl);
	}
	mutex_unlock(s_ctrl->msm_sensor_mutex);
	CDBG("%s: X\n", __func__);

	return rc;
}

int32_t msm_sensor_v4l2_enum_fmt(struct v4l2_subdev *sd, unsigned int index,
			   enum v4l2_mbus_pixelcode *code)
{
	struct msm_sensor_ctrl_t *s_ctrl = get_sctrl(sd);

	if ((unsigned int)index >= s_ctrl->sensor_v4l2_subdev_info_size)
		return -EINVAL;

	*code = s_ctrl->sensor_v4l2_subdev_info[index].code;
	return 0;
}

int32_t msm_sensor_v4l2_s_ctrl(struct v4l2_subdev *sd,
	struct v4l2_control *ctrl)
{
	int rc = -1, i = 0;
	struct msm_sensor_ctrl_t *s_ctrl = get_sctrl(sd);
	struct msm_sensor_v4l2_ctrl_info_t *v4l2_ctrl =
		s_ctrl->msm_sensor_v4l2_ctrl_info;

	CDBG("%s\n", __func__);
	CDBG("%d\n", ctrl->id);
	if (v4l2_ctrl == NULL)
		return rc;
	for (i = 0; i < s_ctrl->num_v4l2_ctrl; i++) {
		if (v4l2_ctrl[i].ctrl_id == ctrl->id) {
			if (v4l2_ctrl[i].s_v4l2_ctrl != NULL) {
				CDBG("\n calling msm_sensor_s_ctrl_by_enum\n");
				rc = v4l2_ctrl[i].s_v4l2_ctrl(
					s_ctrl,
					&s_ctrl->msm_sensor_v4l2_ctrl_info[i],
					ctrl->value);
			}
			break;
		}
	}

	return rc;
}

int32_t msm_sensor_v4l2_query_ctrl(
	struct v4l2_subdev *sd, struct v4l2_queryctrl *qctrl)
{
	int rc = -1, i = 0;
	struct msm_sensor_ctrl_t *s_ctrl =
		(struct msm_sensor_ctrl_t *) sd->dev_priv;

	CDBG("%s\n", __func__);
	CDBG("%s id: %d\n", __func__, qctrl->id);

	if (s_ctrl->msm_sensor_v4l2_ctrl_info == NULL)
		return rc;

	for (i = 0; i < s_ctrl->num_v4l2_ctrl; i++) {
		if (s_ctrl->msm_sensor_v4l2_ctrl_info[i].ctrl_id == qctrl->id) {
			qctrl->minimum =
				s_ctrl->msm_sensor_v4l2_ctrl_info[i].min;
			qctrl->maximum =
				s_ctrl->msm_sensor_v4l2_ctrl_info[i].max;
			qctrl->flags = 1;
			rc = 0;
			break;
		}
	}

	return rc;
}

int msm_sensor_s_ctrl_by_enum(struct msm_sensor_ctrl_t *s_ctrl,
		struct msm_sensor_v4l2_ctrl_info_t *ctrl_info, int value)
{
	int rc = 0;
	CDBG("%s enter\n", __func__);
	rc = msm_sensor_write_enum_conf_array(
		s_ctrl->sensor_i2c_client,
		ctrl_info->enum_cfg_settings, value);
	return rc;
}

static int msm_sensor_debugfs_stream_s(void *data, u64 val)
{
	struct msm_sensor_ctrl_t *s_ctrl = (struct msm_sensor_ctrl_t *) data;
	if (val)
		s_ctrl->func_tbl->sensor_start_stream(s_ctrl);
	else
		s_ctrl->func_tbl->sensor_stop_stream(s_ctrl);
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(sensor_debugfs_stream, NULL,
			msm_sensor_debugfs_stream_s, "%llu\n");

static int msm_sensor_debugfs_test_s(void *data, u64 val)
{
	CDBG("val: %llu\n", val);
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(sensor_debugfs_test, NULL,
			msm_sensor_debugfs_test_s, "%llu\n");

int msm_sensor_enable_debugfs(struct msm_sensor_ctrl_t *s_ctrl)
{
	struct dentry *debugfs_base, *sensor_dir;
	debugfs_base = debugfs_create_dir("msm_sensor", NULL);
	if (!debugfs_base)
		return -ENOMEM;

	sensor_dir = debugfs_create_dir
		(s_ctrl->sensordata->sensor_name, debugfs_base);
	if (!sensor_dir)
		return -ENOMEM;

	if (!debugfs_create_file("stream", S_IRUGO | S_IWUSR, sensor_dir,
			(void *) s_ctrl, &sensor_debugfs_stream))
		return -ENOMEM;

	if (!debugfs_create_file("test", S_IRUGO | S_IWUSR, sensor_dir,
			(void *) s_ctrl, &sensor_debugfs_test))
		return -ENOMEM;

	return 0;
}