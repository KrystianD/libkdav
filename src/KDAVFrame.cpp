#include "KDAVFrame.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

namespace kdav
{
KDAVFrame::KDAVFrame()
		: pFrame(AVFramePtr(av_frame_alloc(), [](AVFrame* ptr) { av_frame_free(&ptr); }))
{
}

std::vector<int> KDAVFrame::getLineSizes() const
{
	return std::vector<int>(pFrame->linesize, pFrame->linesize + AV_NUM_DATA_POINTERS);
}

int KDAVFrame::getWidth() const { return pFrame->width; }
int KDAVFrame::getHeight() const { return pFrame->height; }

uint8_t* const* KDAVFrame::getData() const { return pFrame->data; }
}
