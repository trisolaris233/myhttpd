#include <string>
#include <zlib.h>

namespace tri {
    std::string CompressGzip(const std::string& str,int compressionlevel = Z_BEST_COMPRESSION);

}