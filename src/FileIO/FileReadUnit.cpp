/*
 * Copyright (c) 2022. YuzukiTsuru <GloomyGhost@GloomyGhost.com>.
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License v3.0 as published by
 *  the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * You should have received a copy of the GNU Lesser General Public License v3.0
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

//
// @Author Ghost Gloomy on 2020/1/26.
//

#include "FileReadUnit.h"

#include <iostream>

#if (defined (__WIN32__) || defined (_WIN32)) && !defined (__MINGW32__)
#pragma warning(disable : 4996)
#endif

size_t FileReadUnit::GetAudioLength(const char *filename) {
    SNDFILE *sf;
    SF_INFO info;
    info.format = 0;
    sf = sf_open(filename, SFM_READ, &info);
    if (sf == nullptr) {
        std::cerr << "Failed to open the file." << std::endl;
        exit(-1);
    }
    size_t len = info.frames;
    return len;
}

int FileReadUnit::WavRead(const char *FilePath, double *output) {
    SNDFILE *sf;
    SF_INFO info;
    info.format = 0;
    sf = sf_open(FilePath, SFM_READ, &info);
    if (sf == nullptr) {
        std::cerr << "Failed to open the file." << std::endl;
        exit(-1);
    }
    sf_count_t f = info.frames;
    int c = info.channels;
    if (c > 1) {
        std::cerr << "Can't read stereo file for lessampler." << std::endl;
        exit(-1);
    }
    auto num_items = f * c;
    auto buf = new double[num_items];
    sf_count_t num = sf_read_double(sf, buf, num_items);
    sf_close(sf);
    for (int i = 0; i < num; i += c) {
        for (int j = 0; j < c; ++j) {
            if ((i + j) < f) {
                output[i + j] = buf[i + j];
            }
        }
    }
    delete[] buf;
    return info.samplerate;
}
