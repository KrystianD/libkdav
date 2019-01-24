#ifndef __KDAVPARSER_H__
#define __KDAVPARSER_H__

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include <KDAVCodecContext.h>

namespace kdav
{
	class KDAVParser
	{
		AVCodecParserContext* pParser;

	public:
		KDAVParser(AVCodecParserContext* pParser) : pParser(pParser) {}
		~KDAVParser()
		{
			av_parser_close(pParser);
		}

		int parse(KDAVCodecContext* codecCtx, void* inData, int inPos, int inLength, uint8_t*& frameData, int& frameLength)
		{
			// uint8_t*& _frameData = (uint8_t*&)frameData;
			uint8_t* _inData = (uint8_t*)inData + inPos;
			return av_parser_parse2(pParser, codecCtx->getPtr(), &frameData, &frameLength, _inData, inLength, 0, 0, AV_NOPTS_VALUE);
		}

		AVCodecParserContext* getPtr() const { return pParser; }

		static KDAVParser* createH264Parser()
		{
			AVCodecParserContext* pParser = av_parser_init(AV_CODEC_ID_H264);
			if (pParser == NULL) {
				fprintf(stderr, "Unsupported codec!\n");
				return 0;
			}
			return new KDAVParser(pParser);
		}

	private:
		KDAVParser(const KDAVParser&) = delete;
	};
}

#endif
