#ifndef __KDAVCODEC_H__
#define __KDAVCODEC_H__

#include <string>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace kdav
{
	class KDAVCodec
	{
		AVCodec* pCodec;

	public:
		KDAVCodec(AVCodec* pCodec) : pCodec(pCodec) {}
		~KDAVCodec()
		{

		}

		static KDAVCodec* createH264Codec()
		{
			AVCodec* pCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
			if (pCodec == NULL) {
				fprintf(stderr, "Unsupported codec!\n");
				return 0;
			}
			return new KDAVCodec(pCodec);
		}
		static KDAVCodec* findCodecByName(const std::string& name)
		{
			AVCodec* pCodec = avcodec_find_decoder_by_name(name.c_str());
			if (pCodec == NULL) {
				fprintf(stderr, "Unsupported codec!\n");
				return 0;
			}
			return new KDAVCodec(pCodec);
		}

		AVCodec* getPtr() const { return pCodec; }

	private:
		KDAVCodec(const KDAVCodec&) = delete;
	};
}

#endif
