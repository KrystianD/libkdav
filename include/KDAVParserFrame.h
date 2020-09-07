#pragma once

class AVCodecParserContext;

namespace kdav
{
class KDAVParser;

class KDAVParserFrame
{
private:
	uint8_t* data; // allocated internally by av_parser
	int size;

public:
	KDAVParserFrame() : data(nullptr), size(0) {}

	const void* getData() const { return data; }
	int getSize() const { return size; }

	friend class KDAVParser;
};
}
