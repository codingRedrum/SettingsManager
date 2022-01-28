#include "settings.h"

namespace togg {

namespace {
const QString odometerKeyword = "odometer";
const QString storedDataKeyword = "storedData";
const QString languageKeyword = "language";
const QString languageSettingKeyword = "languageSetting";
const QString tripDataKeyword = "tripData";
const QString trip1DistanceKeyword = "trip1Distance";
const QString trip1TravelTimeKeyword = "trip1TravelTime";
const QString trip2DistanceKeyword = "trip2Distance";
const QString trip2TravelTimeKeyword = "trip2TravelTime";
const QString uiSettingsKeyword = "uiSettings";
const QString recuperationLevelKeyword = "recuperationLevel";
const QString infotainmentBrightnessLevelKeyword = "infotainmentBrightnessLevel";
const QString clusterBrightnessLevelKeyword = "clusterBrightnessLevel";
const QString cameraGuidelinesOverlayEnabledKeyword = "cameraGuidelinesOverlayEnabled";
const QString eBtZReqKeyword = "eBtZReq";
}

SettingsManager::SettingsManager(const QString &file)
    : m_fileName(file)
{
}

QJsonObject SettingsManager::write(const SettingsData &data)
{
    const auto language = (data.language == Language::EN_GB) ? QString("English") : QString("Turkish");

    return QJsonObject { { languageSettingKeyword, writeLanguageSetting(language) } };
}

QJsonObject SettingsManager::write(const StoredData &data)
{
    const auto odometer = QString::number(data.odometer);

    return QJsonObject { { storedDataKeyword, writeOdometer(odometer) } };
}

SettingsData SettingsManager::read(const QJsonObject &json, ReturnTypeTag<SettingsData>)
{
    SettingsData result {};
    if (json[languageSettingKeyword].isObject()) {
        result.language = readLanguageSetting(json[languageSettingKeyword].toObject());
    }
    return result;
}

StoredData SettingsManager::read(const QJsonObject &json, ReturnTypeTag<StoredData>)
{
    StoredData result {};

    if (json[storedDataKeyword].isObject()) {
        result.odometer = readOdometer(json[storedDataKeyword].toObject());
    }
    return result;
}

QJsonObject SettingsManager::writeLanguageSetting(const QString &language)
{
    return QJsonObject { { languageKeyword, language } };
}

QJsonObject SettingsManager::writeOdometer(const QString &odometer)
{
    return QJsonObject { { odometerKeyword, odometer } };
}

uint64_t SettingsManager::readOdometer(const QJsonObject &json)
{
    if (json[odometerKeyword].isString()) {
        QString odometer = json[odometerKeyword].toString();
        return odometer.toInt();
    }
    return 0;
}

Language SettingsManager::readLanguageSetting(const QJsonObject &json)
{
    if (json[languageKeyword].isString()) {
        QString lang = json[languageKeyword].toString();
        return lang == QString("English") ? Language::EN_GB : Language::TR;
    }
    return Language::EN_GB;
}

TripData SettingsManager::read(const QJsonObject &json, ReturnTypeTag<TripData>)
{
    TripData result {};
    if (json[tripDataKeyword].isObject()) {
        result = readTripData(json[tripDataKeyword].toObject());
    }
    return result;
}

QJsonObject SettingsManager::write(const UiSettings &data)
{
    QJsonObject jsonObject {};
    jsonObject[recuperationLevelKeyword] = data.recuperationLevel;
    jsonObject[infotainmentBrightnessLevelKeyword] = data.infotainmentBrightnessLevel;
    jsonObject[clusterBrightnessLevelKeyword] = data.clusterBrightnessLevel;
    jsonObject[cameraGuidelinesOverlayEnabledKeyword] = data.cameraGuidelinesOverlayEnabled;
    jsonObject[eBtZReqKeyword] = data.eBtZReq;

    return QJsonObject { { uiSettingsKeyword, jsonObject } };
}

UiSettings SettingsManager::read(const QJsonObject &json, ReturnTypeTag<UiSettings>)
{
    UiSettings result {};

    if (json[uiSettingsKeyword].isObject()) {
        result = readUiSettings(json[uiSettingsKeyword].toObject());
    }

    return result;
}

UiSettings SettingsManager::readUiSettings(const QJsonObject &json)
{
    UiSettings result {};
    if (json[recuperationLevelKeyword].isDouble()) {
        result.recuperationLevel = json[recuperationLevelKeyword].toInt();
    }
    if (json[infotainmentBrightnessLevelKeyword].isDouble()) {
        result.infotainmentBrightnessLevel = json[infotainmentBrightnessLevelKeyword].toInt();
    }
    if (json[clusterBrightnessLevelKeyword].isDouble()) {
        result.clusterBrightnessLevel = json[clusterBrightnessLevelKeyword].toInt();
    }
    if (json[cameraGuidelinesOverlayEnabledKeyword].isBool()) {
        result.cameraGuidelinesOverlayEnabled = json[cameraGuidelinesOverlayEnabledKeyword].toBool();
    }
    if (json[eBtZReqKeyword].isBool()) {
        result.eBtZReq = json[eBtZReqKeyword].toBool();
    }
    return result;
}

QJsonObject SettingsManager::write(const TripData &data)
{
    return QJsonObject { { tripDataKeyword,
                           QJsonObject { { trip1DistanceKeyword, static_cast<qint64>(data.trip1Distance) },
                                         { trip1TravelTimeKeyword, static_cast<qint64>(data.trip1TravelTime) },
                                         { trip2DistanceKeyword, static_cast<qint64>(data.trip2Distance) },
                                         { trip2TravelTimeKeyword, static_cast<qint64>(data.trip2TravelTime) } } } };
}

TripData SettingsManager::readTripData(const QJsonObject &json)
{
    TripData result {};
    if (json[trip1DistanceKeyword].isDouble()) {
        result.trip1Distance = json[trip1DistanceKeyword].toInt();
    }
    if (json[trip1TravelTimeKeyword].isDouble()) {
        result.trip1TravelTime = json[trip1TravelTimeKeyword].toInt();
    }
    if (json[trip2DistanceKeyword].isDouble()) {
        result.trip2Distance = json[trip2DistanceKeyword].toInt();
    }
    if (json[trip2TravelTimeKeyword].isDouble()) {
        result.trip2TravelTime = json[trip2TravelTimeKeyword].toInt();
    }
    return result;
}
}

