#pragma once

#include <string>
#include <memory>

class AVCodec;

namespace kdav
{
class KDAVCodec
{
	AVCodec* pCodec;

public:
	explicit KDAVCodec(AVCodec* pCodec) : pCodec(pCodec) {}

	static std::shared_ptr<KDAVCodec> createH264Codec();
	static std::shared_ptr<KDAVCodec> findCodecByName(const std::string& name);

	AVCodec* getPtr() const { return pCodec; }
};
}
