/*
 * GStreamer
 *
 * Copyright (C) 201 Collabora Ltd.
 *   Author: Youness Alaoui <youness.alaoui@collabora.co.uk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#ifndef __GST_UVC_H264_SRC_H__
#define __GST_UVC_H264_SRC_H__

#include <gst/gst.h>
#include "uvc_h264.h"

#include <gst/basecamerabinsrc/gstbasecamerasrc.h>

G_BEGIN_DECLS
#define GST_TYPE_UVC_H264_SRC                   \
  (gst_uvc_h264_src_get_type())
#define GST_UVC_H264_SRC(obj)                                           \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_UVC_H264_SRC, GstUvcH264Src))
#define GST_UVC_H264_SRC_CLASS(klass)                                   \
  (G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_UVC_H264_SRC, GstUvcH264SrcClass))
#define GST_IS_UVC_H264_SRC(obj)                                \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_UVC_H264_SRC))
#define GST_IS_UVC_H264_SRC_CLASS(klass)                        \
  (G_TYPE_CHECK_CLASS_TYPE((klass), GST_TYPE_UVC_H264_SRC))
    GType gst_uvc_h264_src_get_type (void);

typedef struct _GstUvcH264Src GstUvcH264Src;
typedef struct _GstUvcH264SrcClass GstUvcH264SrcClass;

enum GstVideoRecordingStatus {
  GST_VIDEO_RECORDING_STATUS_DONE,
  GST_VIDEO_RECORDING_STATUS_STARTING,
  GST_VIDEO_RECORDING_STATUS_RUNNING,
  GST_VIDEO_RECORDING_STATUS_FINISHING
};

enum  {
  QP_ALL_FRAMES = 0,
  QP_I_FRAME,
  QP_P_FRAME,
  QP_B_FRAME,
  QP_FRAMES
};

/**
 * GstUcH264Src:
 *
 */
struct _GstUvcH264Src
{
  GstBaseCameraSrc parent;

  GstPad *vfsrc;
  GstPad *imgsrc;
  GstPad *vidsrc;

  /* source elements */
  GstElement *v4l2_src;
  GstElement *mjpg_demux;
  GstElement *jpeg_dec;
  int v4l2_fd;

  GstPadEventFunction srcpad_event_func;

  gboolean auto_start;

  /* When restarting the source */
  gboolean drop_newseg;

  /* Static controls */
  guint32 initial_bitrate;
  guint16 slice_units;
  UvcH264SliceMode slice_mode;
  guint16 iframe_period;
  UvcH264UsageType usage_type;
  UvcH264StreamFormat stream_format;
  UvcH264Entropy entropy;
  gboolean enable_sei;
  guint8 num_reorder_frames;
  gboolean preview_flipped;

  /* Dynamic controls */
  UvcH264RateControl rate_control;
  gboolean fixed_framerate;
  guint8 level_idc;
  guint32 peak_bitrate;
  guint32 average_bitrate;
  gint8 min_qp[QP_FRAMES];
  gint8 max_qp[QP_FRAMES];
};


/**
 * GstUvcH264SrcClass:
 *
 */
struct _GstUvcH264SrcClass
{
  GstBaseCameraSrcClass parent;
};


#endif /* __GST_UVC_H264_SRC_H__ */
