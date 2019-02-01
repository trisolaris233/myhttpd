#include <zlib.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>

#define MOD_GZIP_ZLIB_WINDOWSIZE 15
#define MOD_GZIP_ZLIB_CFACTOR    9
#define MOD_GZIP_ZLIB_BSIZE      8096

namespace tri {

/** Compress a STL string using zlib with given compression level and return
 * the binary data. */
std::string CompressGzip(const std::string& str,
                             int compressionlevel)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (deflateInit2(&zs, 
                     compressionlevel,
                     Z_DEFLATED,
                     MOD_GZIP_ZLIB_WINDOWSIZE + 16, 
                     MOD_GZIP_ZLIB_CFACTOR,
                     Z_DEFAULT_STRATEGY) != Z_OK
    ) {
        return std::string();
    }

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();           // set the z_stream's input

    int ret;
    char outbuffer[32768];
    std::string outstring;

    // retrieve the compressed bytes blockwise
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = deflate(&zs, Z_FINISH);

        if (outstring.size() < zs.total_out) {
            // append the block to the output string
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
    }

    return outstring;
}

}