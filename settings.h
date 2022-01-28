#pragma once

#include <QJsonObject>
#include <QString>
#include <QFile>
#include <QSaveFile>
#include <QJsonDocument>

#include <iostream>

#include "settingscommon.h"

namespace togg {
class SETTINGS_MANAGER_EXPORT SettingsManager
{
    template<typename T>
    struct ReturnTypeTag
    {
    };

public:
    explicit SettingsManager(const QString &file);
    ~SettingsManager() = default;

    template<class T>
    bool save(const T &data) const
    {
        QSaveFile saveFile(m_fileName + QString(".json"));
        if (!saveFile.open(QIODevice::WriteOnly)) {
            std::cerr << "[SettingsManager][Save Settings] Couldn't open save file: " << m_fileName.toStdString()
                      << "\n";
            return false;
        }

        QJsonObject settingsObject;
        settingsObject = write(data);
        saveFile.write(QJsonDocument(settingsObject).toJson());
        saveFile.flush();
        saveFile.commit();

        return true;
    }

    template<class T>
    bool read(T &data) const
    {
        QFile loadFile(m_fileName + QString(".json"));

        if (!loadFile.open(QIODevice::ReadOnly)) {
            std::cerr << "[SettingsManager][Read Settings] Couldn't open file : " << m_fileName.toStdString() << "\n";
            return false;
        }

        const auto saveData = loadFile.readAll();
        QJsonParseError errorPtr {};
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &errorPtr));
        if (loadDoc.isNull()) {
            std::cerr << "Parse JSON failed: " + errorPtr.errorString().toStdString();
            return false;
        }
        const auto loadObject = loadDoc.object();

        ReturnTypeTag<T> dispatcher;
        data = read(loadObject, dispatcher);

        return true;
    }

public:
    template<typename T>
    T read(const QJsonObject &json, ReturnTypeTag<T>) const
    {
        return read(json, ReturnTypeTag<T> {});
    }

private slots:
    static TripData readTripData(const QJsonObject &json);

private:
    QString m_fileName {};

    static QJsonObject write(const SettingsData &data);
    static QJsonObject write(const StoredData &data);
    static QJsonObject write(const TripData &data);
    static QJsonObject write(const UiSettings &data);

    static SettingsData read(const QJsonObject &json, ReturnTypeTag<SettingsData>);
    static StoredData read(const QJsonObject &json, ReturnTypeTag<StoredData>);
    static TripData read(const QJsonObject &json, ReturnTypeTag<TripData>);
    static UiSettings read(const QJsonObject &json, ReturnTypeTag<UiSettings>);

    static UiSettings readUiSettings(const QJsonObject &json);
    static uint64_t readOdometer(const QJsonObject &json);
    static Language readLanguageSetting(const QJsonObject &json);

    static QJsonObject writeLanguageSetting(const QString &language);
    static QJsonObject writeOdometer(const QString &odometer);
};
}

