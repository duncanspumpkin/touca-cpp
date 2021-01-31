/**
 * Copyright 2018-2020 Pejman Ghorbanzade. All rights reserved.
 */

#pragma once

#include "weasel/devkit/filesystem.hpp"
#include "weasel/devkit/utils.hpp"

struct TmpFile {
    TmpFile()
        : path(make_temp_path())
    {
    }

    void write(const std::string& content) const
    {
        std::ofstream ofs(path);
        ofs << content;
        ofs.close();
    }

    ~TmpFile()
    {
        if (weasel::filesystem::exists(path)) {
            weasel::filesystem::remove_all(path);
        }
    }

    const weasel::path path;

private:
    std::string make_temp_path() const
    {
        const auto filename = weasel::format("weasel_{}", std::rand());
        auto out = weasel::filesystem::temp_directory_path();
        return (out / filename).string();
    }
};
