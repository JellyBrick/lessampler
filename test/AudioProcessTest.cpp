// Copyright (c) 2022. YuzukiTsuru <GloomyGhost@GloomyGhost.com>.
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

//
// Created by gloom on 2022/5/20.
//

#include "FileIO/AudioModelIO.h"
#include "AudioModel/AudioModel.h"
#include "ConfigUnit/lessConfigure.h"
#include "AudioProcess/AudioProcess.h"
#include "libUTAU/libUTAU.h"

#include "../lib/World/tools/audioio.h"


int main(int argc, char *argv[]) {
    std::string FileName;

    if (argc < 2) {
        FileName = "../../test/vaiueo2d.wav";
    } else {
        FileName = argv[1];
    }
    // Open wav File

    int x_length = GetAudioLength(FileName.c_str());
    if (x_length <= 0) {
        if (x_length == 0)
            std::cerr << "error: File \"" << FileName << "\" not found" << std::endl;
        else
            std::cerr << "error: File \"" << FileName << "\" is not a .wav format" << std::endl;
        return EXIT_FAILURE;
    }
    auto *x = new double[x_length];

    // wavread() must be called after GetAudioLength().
    int fs, nbit;
    wavread(FileName.c_str(), &fs, &nbit, x);

    lessConfigure configure{};

    AudioModel audioModel(x, x_length, fs, configure);

    auto less_i = audioModel.GetAudioModel();

    UTAUPara utauPara;
    UTAUFlags utauFlags;

    AduioProcess aduioProcess(less_i, utauPara, utauFlags);
}