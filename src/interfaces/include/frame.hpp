#pragma once

#include <vector>
#include "blob.hpp"
#include "channel.hpp"

#include <image.hpp>

namespace soda {

struct ChannelData {
    chan_ptr chan;
    Image threshold;
    std::vector<Blob> blobs;
};

struct Frame
{
    Image img;
    std::vector<ChannelData> data;
};

} // namespace soda
