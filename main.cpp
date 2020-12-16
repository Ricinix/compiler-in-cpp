#include "util/Log.h"
#include "util/IoUtil.h"

int main(int argc, char *argv[]) {
    IoUtil ioUtil("");
    Log::info(ioUtil);
    Log::info("hello info");
    Log::warm("hello warm");
    Log::error("hello error");
    return 0;
}
