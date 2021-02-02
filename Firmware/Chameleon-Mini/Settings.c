/*
 * Settings.c
 *
 *  Created on: 20.03.2013
 *      Author: skuser
 *
 *  ChangeLog
 *    2019-09-22    Willok    A special configuration has been added, which has no storage space and can only be used as a reader mode
 *
 */

#include "Settings.h"
#include <avr/eeprom.h>
#include "Configuration.h"
#include "Log.h"
#include "Memory.h"
#include "LEDHook.h"
#include "Terminal/CommandLine.h"

#include "System.h"

SettingsType GlobalSettings;
SettingsType EEMEM StoredSettings = {
    .ActiveSettingIdx = SETTING_TO_INDEX(DEFAULT_SETTING),
    .ActiveSettingPtr = &GlobalSettings.Settings[SETTING_TO_INDEX(DEFAULT_SETTING)],

    .Settings = {
        [0 ...(SETTINGS_COUNT - 1)] =	{
            .Configuration = DEFAULT_CONFIGURATION,
            .ButtonActions = {
                [BUTTON_L_PRESS_SHORT] = DEFAULT_LBUTTON_ACTION, [BUTTON_L_PRESS_SHORT] = DEFAULT_LBUTTON_ACTION,
                [BUTTON_L_PRESS_LONG]  = DEFAULT_LBUTTON_ACTION_LONG, [BUTTON_L_PRESS_LONG]  = DEFAULT_LBUTTON_ACTION_LONG,
                [BUTTON_R_PRESS_SHORT] = DEFAULT_RBUTTON_ACTION, [BUTTON_R_PRESS_SHORT] = DEFAULT_RBUTTON_ACTION,
                [BUTTON_R_PRESS_LONG]  = DEFAULT_RBUTTON_ACTION_LONG, [BUTTON_R_PRESS_LONG]  = DEFAULT_RBUTTON_ACTION_LONG
            },
            .LogMode = DEFAULT_LOG_MODE,
            .LEDRedFunction = DEFAULT_RED_LED_ACTION,
            .LEDGreenFunction = DEFAULT_GREEN_LED_ACTION,
            .PendingTaskTimeout = DEFAULT_PENDING_TASK_TIMEOUT,
            .ReaderThreshold = DEFAULT_READER_THRESHOLD,
            .bSakMode = 0,
        }
#ifdef CONFIG_ISO14443A_READER_SUPPORT
        ,
        //    In the last configuration, there is no storage space. This is used as the card reader mode only
        [SETTINGS_COUNT] =
        {
            .Configuration = CONFIG_ISO14443A_READER,
            .ButtonActions = {
                [BUTTON_L_PRESS_SHORT] = DEFAULT_LBUTTON_ACTION, [BUTTON_R_PRESS_SHORT] = DEFAULT_RBUTTON_ACTION,
                [BUTTON_L_PRESS_LONG]  = DEFAULT_LBUTTON_ACTION_LONG, [BUTTON_R_PRESS_LONG]  = DEFAULT_RBUTTON_ACTION_LONG
            },
            .LogMode = DEFAULT_LOG_MODE,
            .LEDRedFunction = DEFAULT_RED_LED_ACTION,
            .LEDGreenFunction = DEFAULT_GREEN_LED_ACTION,
            .PendingTaskTimeout = DEFAULT_PENDING_TASK_TIMEOUT,
            .ReaderThreshold = DEFAULT_READER_THRESHOLD,
            .bSakMode = 0,
        }
#endif
    }
};

void SettingsLoad(void) {
    ReadEEPBlock((uint16_t) &StoredSettings, &GlobalSettings, sizeof(SettingsType));

    if (GlobalSettings.ActiveSettingIdx > SETTINGS_COUNT || GlobalSettings.ActiveSettingPtr !=  &GlobalSettings.Settings[GlobalSettings.ActiveSettingIdx]) {
        GlobalSettings.ActiveSettingIdx = SETTINGS_COUNT;
        GlobalSettings.ActiveSettingPtr = &GlobalSettings.Settings[SETTINGS_COUNT];

        for (int i = 0; i <= SETTINGS_COUNT; i++) {
            GlobalSettings.Settings[i].Configuration = CONFIG_NONE;
            GlobalSettings.Settings[i].ButtonActions[BUTTON_L_PRESS_SHORT] = DEFAULT_LBUTTON_ACTION;
            GlobalSettings.Settings[i].ButtonActions[BUTTON_R_PRESS_SHORT] = DEFAULT_RBUTTON_ACTION;
            GlobalSettings.Settings[i].ButtonActions[BUTTON_L_PRESS_LONG]  = DEFAULT_LBUTTON_ACTION_LONG;
            GlobalSettings.Settings[i].ButtonActions[BUTTON_R_PRESS_LONG]  = DEFAULT_RBUTTON_ACTION_LONG;
            GlobalSettings.Settings[i].LogMode = DEFAULT_LOG_MODE;
            GlobalSettings.Settings[i].LEDRedFunction = DEFAULT_RED_LED_ACTION;
            GlobalSettings.Settings[i].LEDGreenFunction = DEFAULT_GREEN_LED_ACTION;
            GlobalSettings.Settings[i].PendingTaskTimeout = DEFAULT_PENDING_TASK_TIMEOUT;
            GlobalSettings.Settings[i].ReaderThreshold = DEFAULT_READER_THRESHOLD;
        }
#ifdef CONFIG_ISO14443A_READER_SUPPORT
        GlobalSettings.Settings[SETTINGS_COUNT].Configuration = CONFIG_ISO14443A_READER;
#endif

        SettingsSave();
    }
}

void SettingsSave(void) {
#if ENABLE_EEPROM_SETTINGS
    WriteEEPBlock((uint16_t) &StoredSettings, &GlobalSettings, sizeof(SettingsType));
#endif
}

void SettingsCycle(uint8_t bAdd) {
    uint8_t SettingIdx = GlobalSettings.ActiveSettingIdx;

    for (uint8_t i = SETTINGS_COUNT; i > 0; i--) {
        if (SettingIdx >= SETTINGS_COUNT) {
            SettingIdx = 0;
            i++;
        } else {
            if (bAdd)
                SettingIdx = (SettingIdx + 1) % SETTINGS_COUNT;
            else
                SettingIdx = (SettingIdx + SETTINGS_COUNT - 1) % SETTINGS_COUNT;
        }
        if (GlobalSettings.Settings[SettingIdx].Configuration != CONFIG_NONE) {
            SettingsSetActiveById(INDEX_TO_SETTING(SettingIdx));
            break;
        }
    }
}

bool SettingsSetActiveById(uint8_t Setting) {
    uint8_t cSetting = Setting + '0';
    LogEntry(LOG_INFO_SETTING_SET, &cSetting, 1);

    if ((Setting >= SETTINGS_FIRST) && (Setting <= (SETTINGS_LAST + 1))) {
        uint8_t SettingIdx = SETTING_TO_INDEX(Setting);

        /* Break potentially pending timeout task (manual timeout) */
        CommandLinePendingTaskBreak();

        if (SettingIdx != GlobalSettings.ActiveSettingIdx) {
            /* Store current memory contents permanently */
            MemoryStore();

            GlobalSettings.ActiveSettingIdx = SettingIdx;
            GlobalSettings.ActiveSettingPtr =
                &GlobalSettings.Settings[SettingIdx];

            /* Settings have changed. Progress changes through system */
            ConfigurationSetById(GlobalSettings.ActiveSettingPtr->Configuration);
            LogSetModeById(GlobalSettings.ActiveSettingPtr->LogMode);

            /* Recall new memory contents ( ApplicationInitFunc() will be called again )*/
            MemoryRecall();

            SETTING_UPDATE(GlobalSettings.ActiveSettingIdx);
            SETTING_UPDATE(GlobalSettings.ActiveSettingPtr);
        }

        /* Notify LED. blink according to current setting */
        LEDHook(LED_SETTING_CHANGE, LED_BLINK + SettingIdx);

        return true;
    } else {
        return false;
    }
}

uint8_t SettingsGetActiveById(void) {
    return INDEX_TO_SETTING(GlobalSettings.ActiveSettingIdx);
}

void SettingsGetActiveByName(char *SettingOut, uint16_t BufferSize) {
    SettingOut[0] = SettingsGetActiveById() + '0';
    SettingOut[1] = '\0';
}

bool SettingsSetActiveByName(const char *Setting) {
    uint8_t SettingNr = Setting[0] - '0';

    if (Setting[1] == '\0') {
//        LogEntry(LOG_INFO_SETTING_SET, Setting, 1);
        return SettingsSetActiveById(SettingNr);
    } else {
        return false;
    }
}

