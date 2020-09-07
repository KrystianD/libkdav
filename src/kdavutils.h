#pragma once

extern "C" {
#include <libavutil/pixfmt.h>
}

#include "KDAV.h"

namespace kdav
{
static AVPixelFormat PixelFormatToLibAV(KDPixelFormat format)
{
	switch (format) {
		case KDPixelFormat::YUV420P:
			return AV_PIX_FMT_YUV420P;
		default:
			return (AVPixelFormat)0;
	}
}
}
