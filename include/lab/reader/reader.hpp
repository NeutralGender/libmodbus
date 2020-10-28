#pragma once

#include <filesystem>

namespace lab::reader
{

namespace fs = std::filesystem;

template <typename T>
class reader_t
{
public:
    reader_t(T& reader):
            reader(reader)
    {}

    ~reader_t()
    {}

    [[nodiscard]]
    bool open(const fs::path filepath)
    { return reader.open(filepath); }

    [[nodiscard]]
    auto read()
    { return reader.read(); }

protected:

private:
    T& reader;
};

} // namespace lab::reader
