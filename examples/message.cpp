#include "message.hpp"

std::vector<uint8_t> encode_message(const Message& message) {
    std::vector<uint8_t> result;
    result.resize(message.ByteSizeLong());
    message.SerializeToArray(result.data(), result.size());
    return result;
}

Message decode_message(const std::vector<uint8_t>& data) {
    Message message;
    message.ParseFromArray(data.data(), data.size());
    return message;
}
