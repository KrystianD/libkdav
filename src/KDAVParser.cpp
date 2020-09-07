#include "KDAVParser.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include "KDAVCodecContext.h"

namespace kdav
{
void KDAVParser::parse(std::shared_ptr<KDAVCodecContext>& codecCtx, void* inData, int inPos, int inLength, KDAVParserFrame& frame,
                       int& consumedBytes)
{
	uint8_t* _inData = (uint8_t*)inData + inPos;
	int res = av_parser_parse2(pParser.get(), codecCtx->getPtr(), &frame.data, &frame.size, _inData, inLength, 0, 0, AV_NOPTS_VALUE);
	if (res < 0)
		throw std::runtime_error("Unable to parse buffer");
	consumedBytes = res;
}

std::shared_ptr<KDAVParser> KDAVParser::createH264Parser()
{
	AVCodecParserContext* parserCtx = av_parser_init(AV_CODEC_ID_H264);
	if (parserCtx == nullptr)
		throw std::runtime_error("Unsupported codec");

	AVCodecParserContextPtr parserCtxPtr(parserCtx, av_parser_close);

	return std::make_shared<KDAVParser>(parserCtxPtr);
}
}
