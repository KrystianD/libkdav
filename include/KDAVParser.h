#pragma once

#include <memory>
#include <functional>

class AVCodecParserContext;

namespace kdav
{
typedef std::unique_ptr<AVCodecParserContext, std::function<void(AVCodecParserContext*)>> AVCodecParserContextPtr;

class KDAVCodecContext;

class KDAVParserFrame;

class KDAVParser
{
	AVCodecParserContextPtr pParser;

public:
	explicit KDAVParser(AVCodecParserContextPtr& pParser) : pParser(std::move(pParser)) {}

	void parse(std::shared_ptr<KDAVCodecContext>& codecCtx, void* inData, int inPos, int inLength, KDAVParserFrame& frame, int& consumedBytes);

	AVCodecParserContext* getPtr() const { return pParser.get(); }

	static std::shared_ptr<KDAVParser> createH264Parser();
};
}
