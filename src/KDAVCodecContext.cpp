#include "KDAVCodecContext.h"

extern "C" {
#include <libavcodec/avcodec.h>
}

#include "KDAVCodec.h"
#include "KDAVFrame.h"
#include "kdavutils.h"

namespace kdav
{
void KDAVCodecContext::setSize(int width, int height)
{
	pCodecCtx->width = width;
	pCodecCtx->height = height;
}

void KDAVCodecContext::setPixelFormat(KDPixelFormat format)
{
	pCodecCtx->pix_fmt = PixelFormatToLibAV(format);
}

int KDAVCodecContext::getWidth() const { return pCodecCtx->width; }
int KDAVCodecContext::getHeight() const { return pCodecCtx->height; }

void KDAVCodecContext::open()
{
	if (avcodec_open2(pCodecCtx.get(), codec->getPtr(), nullptr) < 0)
		throw std::runtime_error("Unable to open codec");
}

void KDAVCodecContext::decode(const KDAVParserFrame& parserFrame, KDAVFrame& frame, bool& frameFinished)
{
	return decode(parserFrame.getData(), parserFrame.getSize(), frame, frameFinished);
}
void KDAVCodecContext::decode(const void* data, int length, KDAVFrame& frame, bool& frameFinished)
{
	AVPacket p;
	av_init_packet(&p);
	p.pts = AV_NOPTS_VALUE;
	p.dts = AV_NOPTS_VALUE;
	p.data = (uint8_t*)data;
	p.size = length;

	int res;
#if LIBAVCODEC_VERSION_MAJOR >= 57
	res = avcodec_send_packet(pCodecCtx.get(), &p);
	if (res < 0)
		throw std::runtime_error("Unable to send packet");

	res = avcodec_receive_frame(pCodecCtx.get(), frame.getPtr());
	switch (res) {
		case 0:
			frameFinished = true;
			return;
		case AVERROR(EAGAIN):
			frameFinished = false;
			return;
		default:
			throw std::runtime_error("Unable to receive frame");
	}
#else
	int hasFrame;
	res = avcodec_decode_video2(pCodecCtx.get(), frame.getPtr(), &hasFrame, &p);
	if (res < 0)
		throw std::runtime_error("Unable to decode frame");
	frameFinished = hasFrame != 0;
#endif
}

std::shared_ptr<KDAVCodecContext> KDAVCodecContext::create(std::shared_ptr<KDAVCodec>& codec)
{
	AVCodec* pCodec = codec->getPtr();
	AVCodecContext* codecCtx = avcodec_alloc_context3(pCodec);

	AVCodecContextPtr parserCtxPtr(codecCtx, [](AVCodecContext* ptr) {
		avcodec_free_context(&ptr);
	});

	return std::make_shared<KDAVCodecContext>(codec, parserCtxPtr);
}
}
