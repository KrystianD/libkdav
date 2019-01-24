#ifndef __KDAVFRAME_H__
#define __KDAVFRAME_H__

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace kdav
{
	class KDAVFrame
	{
		AVFrame* pFrame;

	public:
		KDAVFrame()
		{
			pFrame = av_frame_alloc();
		}
		~KDAVFrame()
		{
			av_frame_free(&pFrame);
		}

		int getWidth() const { return pFrame->width; }
		int getHeight() const { return pFrame->height; }

		uint8_t** getData() const { return pFrame->data; }

		AVFrame* getPtr() const { return pFrame; }

	private:
		KDAVFrame(const KDAVFrame&) = delete;
	};
}

#endif
