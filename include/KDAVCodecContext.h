#pragma once

#include <memory>
#include <functional>

#include "KDAV.h"
#include "KDAVParserFrame.h"

class AVCodecContext;

namespace kdav
{
class KDAVCodec;

class KDAVFrame;

typedef std::unique_ptr<AVCodecContext, std::function<void(AVCodecContext*)>> AVCodecContextPtr;

class KDAVCodecContext
{
	std::shared_ptr<KDAVCodec> codec;

	AVCodecContextPtr pCodecCtx;

public:
	KDAVCodecContext(std::shared_ptr<KDAVCodec> codec, AVCodecContextPtr& pCodecCtx)
			: codec(std::move(codec)), pCodecCtx(std::move(pCodecCtx)) {}

	void setSize(int width, int height);

	void setPixelFormat(KDPixelFormat format);

	int getWidth() const;
	int getHeight() const;

	void open();

	void decode(const KDAVParserFrame& parserFrame, KDAVFrame& frame, bool& frameFinished);
	void decode(const void* data, int length, KDAVFrame& frame, bool& frameFinished);

	AVCodecContext* getPtr() const { return pCodecCtx.get(); }

	static std::shared_ptr<KDAVCodecContext> create(std::shared_ptr<KDAVCodec>& codec);
};
}
