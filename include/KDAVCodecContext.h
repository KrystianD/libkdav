#ifndef __KDAVCODECCONTEXT_H__
#define __KDAVCODECCONTEXT_H__

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include "KDAV.h"
#include "KDAVCodec.h"
#include "KDAVFrame.h"

namespace kdav
{
	class KDAVCodecContext
	{
		KDAVCodec* codec;
		AVCodecContext* pCodecCtx;
		bool opened;

	public:
		KDAVCodecContext(KDAVCodec* codec, AVCodecContext* pCodecCtx)
						: codec(codec), pCodecCtx(pCodecCtx), opened(false)
		{
		}

		~KDAVCodecContext()
		{
			if (opened)
				avcodec_close(pCodecCtx);
			avcodec_free_context(&pCodecCtx);
		}

		void setSize(int width, int height)
		{
			pCodecCtx->width = width;
			pCodecCtx->height = height;
		}

		void setPixelFormat(KDPixelFormat format)
		{
			pCodecCtx->pix_fmt = PixelFormatToLibAV(format);
		}

		int getWidth() const { return pCodecCtx->width; }
		int getHeight() const { return pCodecCtx->height; }

		bool open()
		{
			AVDictionary* codec_options = 0;
			// av_dict_set(&codec_options, "preset", "ultrafast", 0);
			// av_dict_set( &codec_options, "AnyCodecParameter", "Value", 0 );

			// if (avcodec_open2(pCodecCtx, codec->getPtr(), &codec_options) < 0) {
			if (avcodec_open2(pCodecCtx, codec->getPtr(), 0) < 0) {
				fprintf(stderr, "open!! codec!\n");
				return false;
			}
			opened = true;
			return true;
		}

		int decode(void* data, int length, KDAVFrame* frame, bool& frameFinished)
		{
			AVPacket p;
			av_init_packet(&p);
			p.pts = AV_NOPTS_VALUE;
			p.dts = AV_NOPTS_VALUE;
			p.data = (uint8_t*)data;
			p.size = length;

			int res;
// #if LIBAVCODEC_VERSION_MAJOR >= 57
			// res = avcodec_send_packet(pCodecCtx, &p);
			// if (res < 0)
			// return -1;

			// res = avcodec_receive_frame(pCodecCtx, frame->getPtr());
			// if (res < 0)
			// return -1;
// #else
			int hasFrame;
			res = avcodec_decode_video2(pCodecCtx, frame->getPtr(), &hasFrame, &p);
			frameFinished = hasFrame != 0;
// #endif

			return res;
		}

		AVCodecContext* getPtr() const { return pCodecCtx; }

		static KDAVCodecContext* create(KDAVCodec* codec)
		{
			AVCodec* pCodec = codec->getPtr();
			AVCodecContext* pCodecCtx = avcodec_alloc_context3(pCodec);
			// avcodec_get_context_defaults3(pCodecCtx, pCodec);

			// if (pCodec->capabilities & CODEC_CAP_TRUNCATED)
			// pCodecCtx->flags = CODEC_FLAG_TRUNCATED ;//| CODEC_FLAG_LOW_DELAY;
			// pCodecCtx->flags2 = CODEC_FLAG2_CHUNKS;
			// pCodecCtx->flags2 = CODEC_FLAG2_FAST;
			// pCodecCtx->flags |= CODEC_FLAG_EMU_EDGE;


			// pCodecCtx->pix_fmt = PIX_FMT_YUV420P ;
			// pCodecCtx->skip_frame = AVDISCARD_DEFAULT ;
			// pCodecCtx->error_concealment = FF_EC_GUESS_MVS | FF_EC_DEBLOCK ;
			// pCodecCtx->skip_loop_filter = AVDISCARD_DEFAULT ;
			// pCodecCtx->workaround_bugs = FF_BUG_AUTODETECT ;
			// pCodecCtx->coder_type = AVMEDIA_TYPE_VIDEO ;
			// pCodecCtx->codec_id = AV_CODEC_ID_H264 ;
			// pCodecCtx->skip_idct = AVDISCARD_DEFAULT ;

			return new KDAVCodecContext(codec, pCodecCtx);
		}

	private:
		KDAVCodecContext(const KDAVCodecContext&) = delete;
	};
}

#endif
