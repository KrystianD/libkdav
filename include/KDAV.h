#ifndef __KDAV_H__
#define __KDAV_H__

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace kdav
{
	enum class KDPixelFormat
	{
		YUV420P = 0,
	};

	class KDAV
	{
	public:
		static void init()
		{
			av_register_all();
			avcodec_register_all();
		}
	};

	AVPixelFormat PixelFormatToLibAV(KDPixelFormat format)
	{
		switch (format) {
			case KDPixelFormat::YUV420P:
				return AV_PIX_FMT_YUV420P;
			default:
				return (AVPixelFormat)0;
		}
	}
}

#endif
