#include "util/gzip.h"

#include <zlib.h>

#define CHUNK 16384

int gzip_def(FILE *src, FILE *dst, int level)
{
    int ret, flush;
    unsigned int have;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    z_stream zs = { .zalloc = Z_NULL, .zfree = Z_NULL, .opaque = Z_NULL };
    ret = deflateInit2(&zs, level, Z_DEFLATED, 31, 8, Z_DEFAULT_STRATEGY);
    if (ret != Z_OK) return ret;

    do {
        zs.avail_in = fread(in, 1, CHUNK, src);
        if (ferror(src)) {
            deflateEnd(&zs);
            return Z_ERRNO;
        }

        flush = feof(src) ? Z_FINISH : Z_NO_FLUSH;
        zs.next_in = in;

        do {
            zs.avail_out = CHUNK;
            zs.next_out = out;
            ret = deflate(&zs, flush);
            have = CHUNK - zs.avail_out;
            if (fwrite(out, 1, have, dst) != have || ferror(dst)) {
                deflateEnd(&zs);
                return Z_ERRNO;
            }
        } while (zs.avail_out == 0);
    } while (flush != Z_FINISH);

    deflateEnd(&zs);
    return Z_OK;
}

int gzip_inf(FILE *src, FILE *dst)
{
    int ret;
    unsigned int have;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    z_stream zs = {
        .zalloc = Z_NULL, .zfree = Z_NULL, .opaque = Z_NULL,
        .avail_in = 0, .next_in = Z_NULL
    };
    ret = inflateInit2(&zs, 31);
    if (ret != Z_OK) {
        inflateEnd(&zs);
        return Z_ERRNO;
    }

    do {
        zs.avail_in = fread(in, 1, CHUNK, src);
        if (ferror(src)) {
            inflateEnd(&zs);
            return Z_ERRNO;
        }

        if (zs.avail_in == 0) break;
        zs.next_in = in;

        do {
            zs.avail_out = CHUNK;
            zs.next_out = out;
            ret = inflate(&zs, Z_NO_FLUSH);
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&zs);
                return ret;
            }

            have = CHUNK - zs.avail_out;
            if (fwrite(out, 1, have, dst) != have || ferror(dst)) {
                inflateEnd(&zs);
                return Z_ERRNO;
            }
        } while (zs.avail_out == 0);
    } while (ret != Z_STREAM_END);

    inflateEnd(&zs);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int gzip_c(int code)
{
    if (code == Z_OK) return 0;

    fputs("gzip: ", stderr);
    switch (code) {
    case Z_ERRNO:
        fputs("error during processing\n", stderr);
        break;
    case Z_DATA_ERROR:
        fputs("invalid or incomplete deflate data\n", stderr);
        break;
    case Z_MEM_ERROR:
        fputs("out of memory\n", stderr);
        break;
    case Z_VERSION_ERROR:
        fputs("zlib version mismatch\n", stderr);
        break;
    }

    return 1;
}
