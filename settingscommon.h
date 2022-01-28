#pragma once

#ifndef SETTINGS_MANAGER_STATIC
#    ifdef SETTINGS_MANAGER_LIB
#        define SETTINGS_MANAGER_EXPORT Q_DECL_EXPORT
#    else
#        define SETTINGS_MANAGER_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define SETTINGS_MANAGER_EXPORT
#endif
#include <cstdint>
namespace togg {

constexpr uint8_t defaultRecuperationLevel = 3;
constexpr uint8_t defaultCameraGuidelinesOverlayEnabled = false;

enum class Language
{
    EN_GB,
    TR
};

struct SettingsData
{
    Language language { Language::EN_GB };
};

struct StoredData
{
    uint64_t odometer { 0 };
};
constexpr unsigned int SOUND2_INTERVAL = 2000;

struct TripData
{
    uint64_t trip1Distance;
    uint64_t trip1TravelTime;

    uint64_t trip2Distance;
    uint64_t trip2TravelTime;
};

struct UiSettings
{
    // @req {Req-TOGG-F294-102, Req-TOGG-F294-102}
    uint8_t recuperationLevel { defaultRecuperationLevel };
    uint8_t infotainmentBrightnessLevel { 0b0011U };
    uint8_t clusterBrightnessLevel { 0b0110U };
    bool cameraGuidelinesOverlayEnabled { defaultCameraGuidelinesOverlayEnabled };
    // @req {Req-TOGG-F681-J_1487-102, Req-TOGG-F681-J_1487-104}
    bool eBtZReq { false };
};
}

