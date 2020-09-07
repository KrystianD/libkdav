#include "KDAV.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

namespace kdav
{
void KDAV::init()
{
#ifndef FF_API_NEXT
	av_register_all();
	avcodec_register_all();
#endif
}
}
