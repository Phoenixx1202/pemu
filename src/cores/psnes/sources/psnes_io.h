//
// Created by cpasjuste on 03/04/2020.
//

#ifndef PEMU_PSNES_IO_H
#define PEMU_PSNES_IO_H

namespace c2d {
    class PSNESIo : public c2d::C2DIo {
    public:
        PSNESIo() : C2DIo() {
            C2DIo::create(PSNESIo::getDataPath());
            C2DIo::create(PSNESIo::getDataPath() + "roms");
            C2DIo::create(PSNESIo::getDataPath() + "configs");
            C2DIo::create(PSNESIo::getDataPath() + "saves");
        }

#ifdef __PS4__
        std::string getDataPath() override {
            return "/data/psnes/";
        }
#endif
    };
}

#endif //PEMU_PSNES_IO_H
