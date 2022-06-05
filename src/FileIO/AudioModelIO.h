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
// Created by Ghost Gloomy on 2020/8/27.
//

#ifndef LESSAMPLER_AUDIOMODELIO_H
#define LESSAMPLER_AUDIOMODELIO_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <parameterio.h>
#include <cstring>
#include "AudioModel/lessAudioModel.h"

class AudioModelIO {
public:
    // TODO Using filesystem instead of string
    AudioModelIO(const std::string &Path, lessAudioModel audioModel);

    explicit AudioModelIO(const std::string &Path);

    ~AudioModelIO();

    [[maybe_unused]] void SetFilePath(const std::string &Path);

    [[maybe_unused]] void SetAudioModel(lessAudioModel audioModel);

    [[maybe_unused]] std::string GetFilePath();

    [[maybe_unused]] lessAudioModel GetAudioModel();

    void SaveAudioModel();

    lessAudioModel ReadAudioModel();

private:
    lessAudioModel _audioModel{};
    std::filesystem::path RootFilePath{};
    std::filesystem::path F0FilePath{};
    std::filesystem::path SPFilePath{};
    std::filesystem::path APFilePath{};

protected:
    const std::string F0FileExt = "lessaudiof0";
    const std::string SPFileExt = "lessaudiosp";
    const std::string APFileExt = "lessaudioap";
    const char F0LengthHeader[5] = {'F', '0', 'L', ' ', '\0'};            // number of samples (int)
    const char FramePeridoHeader[5] = {'F', 'P', ' ', ' ', '\0'};         // frame perido (double)
    const char FFTSizeHeader[5] = {'F', 'F', 'T', ' ', '\0'};             // FFT size (int)
    const char FSHeader[5] = {'F', 'S', ' ', ' ', '\0'};                  // frame per sample (int)
    const char F0Header[5] = {'5', '4', '0', '0', '\0'};                  // F0
    const char SPHeader[5] = {'5', '4', '0', '1', '\0'};                  // SP
    const char APHeader[5] = {'5', '4', '0', '2', '\0'};                  // AP

private:
    void WriteAudioContent();

    void ReadAudioContent();

    void GenerateFilePath();

private: // Writer
    void WriteF0();

    void WriteSP();

    void WriteAP();

private: // Reader
    void ReadF0();

    void ReadSP();

    void ReadAP();

private:
    static void WriteOneParameter(FILE *fp, const char *text, double parameter, int size);

    static void LoadParameters(FILE *fp, int *f0_length, int *fft_size);

    static int CheckHeader(FILE *fp, const char *text);
};


#endif //LESSAMPLER_AUDIOMODELIO_H