#include <KDAVCodec.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace kdav
{
std::shared_ptr<KDAVCodec> KDAVCodec::createH264Codec()
{
	AVCodec* pCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
	if (pCodec == nullptr)
		throw std::runtime_error("Unsupported codec");
	return std::make_shared<KDAVCodec>(pCodec);
}
std::shared_ptr<KDAVCodec> KDAVCodec::findCodecByName(const std::string& name)
{
	AVCodec* pCodec = avcodec_find_decoder_by_name(name.c_str());
	if (pCodec == nullptr)
		throw std::runtime_error("Unsupported codec");
	return std::make_shared<KDAVCodec>(pCodec);
}
}
