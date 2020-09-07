#pragma once

#include <vector>
#include <memory>
#include <functional>

class AVFrame;

namespace kdav
{
typedef std::unique_ptr<AVFrame, std::function<void(AVFrame*)>> AVFramePtr;

class KDAVFrame
{
	AVFramePtr pFrame;

public:
	explicit KDAVFrame();

	std::vector<int> getLineSizes() const;

	int getWidth() const;
	int getHeight() const;

	uint8_t* const* getData() const;

	AVFrame* getPtr() const { return pFrame.get(); }
};
}
