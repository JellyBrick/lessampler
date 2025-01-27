/*
 * Copyright (c) 2022. YuzukiTsuru <GloomyGhost@GloomyGhost.com>.
 * lessampler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License v3.0 as published by
 *  the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * You should have received a copy of the GNU Lesser General Public License v3.0
 * along with lessampler. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LESSAMPLER_PITCHBENDDECODER_H
#define LESSAMPLER_PITCHBENDDECODER_H

#include <iostream>

class PitchBendDecoder {
public:
    explicit PitchBendDecoder(std::string &str, int count);

    ~PitchBendDecoder();

    int *getPitchBend();

private:
    std::string pitch = {};
    int count = 0, pitch_length = 0;

    int *pitch_bend = nullptr;

    static int GetDataFromUTAU64(char i);

    void PitchBendDecode();
};


#endif //LESSAMPLER_PITCHBENDDECODER_H
