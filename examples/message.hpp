#pragma once

#include <vector>
#include <examples/example.pb.h>

std::vector<uint8_t> encode_message(const Message& message);
Message decode_message(const std::vector<uint8_t>& data);
