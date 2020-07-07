/*
  it-IT.h - localization for Italian - Italy for Tasmota

  Copyright (C) 2020 Gennaro Tortone - some mods by Antonio Fragola

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _LANGUAGE_IT_IT_H_
#define _LANGUAGE_IT_IT_H_

/*************************** ATTENTION *******************************\
 *
 * Due to memory constraints only UTF-8 is supported.
 * To save code space keep text as short as possible.
 * Time and Date provided by SDK can not be localized (yet).
 * Use online command StateText to translate ON, OFF, HOLD and TOGGLE.
 * Use online command Prefix to translate cmnd, stat and tele.
 *
 * Updated until v6.0.0a
\*********************************************************************/

#define LANGUAGE_MODULE_NAME         // Enable to display "Module Generic" (ie Spanish), Disable to display "Generic Module" (ie English)

#define LANGUAGE_LCID 1040
// HTML (ISO 639-1) Language Code
#define D_HTML_LANGUAGE "it"

// "2017-03-07T11:08:02" - ISO8601:2004
#define D_YEAR_MONTH_SEPARATOR "-"
#define D_MONTH_DAY_SEPARATOR "-"
#define D_DATE_TIME_SEPARATOR "T"
#define D_HOUR_MINUTE_SEPARATOR ":"
#define D_MINUTE_SECOND_SEPARATOR ":"

#define D_DAY3LIST "DomLunMarMerGioVenSab"
#define D_MONTH3LIST "GenFebMarAprMagGiuLugAgoSetOttNovDic"

// Non JSON decimal separator
#define D_DECIMAL_SEPARATOR "."

// Common
#define D_ADMIN "Admin"
#define D_AIR_QUALITY "Qualità dell'aria"
#define D_AP "AP"                    // Access Point
#define D_AS "come"
#define D_AUTO "AUTO"
#define D_BATT "Batt"                // Short for Battery
#define D_BLINK "Lampeggia"
#define D_BLINKOFF "Lampeggia OFF"
#define D_BOOT_COUNT "Numero boot"
#define D_BRIGHTLIGHT "Luminoso"
#define D_BSSID "BSSId"
#define D_BUTTON "Pulsante"
#define D_BY "di"                    // Written by me
#define D_BYTES "Byte"
#define D_CELSIUS "Celsius"
#define D_CHANNEL "Canale"
#define D_CO2 "CO2"
#define D_CODE "codice"                // Button code
#define D_COLDLIGHT "Fredda"
#define D_COMMAND "Comando"
#define D_CONNECTED "Connesso"
#define D_CORS_DOMAIN "Dominio CORS"
#define D_COUNT "Conteggio"
#define D_COUNTER "Contatore"
#define D_CT_POWER "Alimentazione CT"
#define D_CURRENT "Corrente"          // As in Voltage and Current
#define D_DATA "Dati"
#define D_DARKLIGHT "Scuro"
#define D_DEBUG "Debug"
#define D_DEWPOINT "Punto rugiada" //
#define D_DISABLED "Disabilitato/a"
#define D_DISTANCE "Distanza"
#define D_DNS_SERVER "Server DNS"
#define D_DONE "Completato"
#define D_DST_TIME "DST"
#define D_ECO2 "eCO₂"
#define D_EMULATION "Tipo emulazione"
#define D_ENABLED "Abilitato"
#define D_ERASE "Cancella"
#define D_ERROR "Errore"
#define D_FAHRENHEIT "Fahrenheit"
#define D_FAILED "Fallito"
#define D_FALLBACK "Riserva"
#define D_FALLBACK_TOPIC "Topic Riserva"
#define D_FALSE "Falso"
#define D_FILE "File"
#define D_FLOW_RATE "Flusso dati"
#define D_FREE_MEMORY "Memoria libera"
#define D_PSR_MAX_MEMORY "PS-RAM - Memoria"
#define D_PSR_FREE_MEMORY "PS-RAM - Memoria libera"
#define D_FREQUENCY "Frequenza"
#define D_GAS "Gas"
#define D_GATEWAY "Gateway"
#define D_GROUP "Gruppo"
#define D_HOST "Host"
#define D_HOSTNAME "Nome host"
#define D_HUMIDITY "Umidità"
#define D_ILLUMINANCE "Illuminazione"
#define D_IMMEDIATE "immediato"      // Button immediate
#define D_INDEX "Indice"
#define D_INFO "Info"
#define D_INFRARED "Infrarosso"
#define D_INITIALIZED "Inizializzato"
#define D_IP_ADDRESS "Indirizzo IP"
#define D_LIGHT "Luce"
#define D_LWT "LWT"
#define D_LQI "LQI"                  // Zigbee Link Quality Index
#define D_MODULE "Modulo"
#define D_MOISTURE "Umidità"
#define D_MQTT "MQTT"
#define D_MULTI_PRESS "multi-pressione"
#define D_NOISE "Rumore"
#define D_NONE "Nessuno"
#define D_OFF "OFF"
#define D_OFFLINE "Offline"
#define D_OK "OK"
#define D_ON "ON"
#define D_ONLINE "Online"
#define D_PASSWORD "Password"
#define D_PORT "Porta"
#define D_POWER_FACTOR "Fattore di potenza"
#define D_POWERUSAGE "Potenza"
#define D_POWERUSAGE_ACTIVE "Potenza attiva"
#define D_POWERUSAGE_APPARENT "Potenza apparente"
#define D_POWERUSAGE_REACTIVE "Potenza reattiva"
#define D_PRESSURE "Pressione"
#define D_PRESSUREATSEALEVEL "Pressione al livello del mare"
#define D_PROGRAM_FLASH_SIZE "Dimensione flash"
#define D_PROGRAM_SIZE "Dimensione programma"
#define D_PROJECT "Progetto"
#define D_RAIN "Pioggia"
#define D_RANGE "Intervallo"
#define D_RECEIVED "Ricevuto"
#define D_RESTART "Riavvia"
#define D_RESTARTING "Riavvio"
#define D_RESTART_REASON "Causa riavvio"
#define D_RESTORE "ripristino"
#define D_RETAINED "salvato"
#define D_RULE "Regola"
#define D_SAVE "Salva"
#define D_SENSOR "Sensore"
#define D_SSID "SSID"
#define D_START "Esegui"
#define D_STD_TIME "STD"
#define D_STOP "Stop"
#define D_SUBNET_MASK "Maschera sottorete"
#define D_SUBSCRIBE_TO "Abbonati a"
#define D_UNSUBSCRIBE_FROM "Rimuovi abbonamento da"
#define D_SUCCESSFUL "Completato"
#define D_SUNRISE "Alba"
#define D_SUNSET "Tramonto"
#define D_TEMPERATURE "Temperatura"
#define D_TO "a"
#define D_TOGGLE "ON/OFF"
#define D_TOPIC "Topic"
#define D_TOTAL_USAGE "Uso totale"
#define D_TRANSMIT "Trasmesso"
#define D_TRUE "Vero"
#define D_TVOC "TVOC"
#define D_UPGRADE "aggiornamento"
#define D_UPLOAD "Caricamento"
#define D_UPTIME "Tempo accensione"
#define D_USER "Utente"
#define D_UTC_TIME "UTC"
#define D_UV_INDEX "Indice UV"
#define D_UV_INDEX_1 "Basso"
#define D_UV_INDEX_2 "Medio"
#define D_UV_INDEX_3 "Alto"
#define D_UV_INDEX_4 "Pericolo"
#define D_UV_INDEX_5 "BurnL1/2"
#define D_UV_INDEX_6 "BurnL3"
#define D_UV_INDEX_7 "OoR"         // Out of Range
#define D_UV_LEVEL "Livello UV"
#define D_UV_POWER "Intensità UV"
#define D_VERSION "Versione"
#define D_VOLTAGE "Tensione"
#define D_WEIGHT "Peso"
#define D_WARMLIGHT "Calda"
#define D_WEB_SERVER "Server web"

// tasmota.ino
#define D_WARNING_MINIMAL_VERSION "ATTENZIONE Questa versione non supporta il salvataggio delle impostazioni"
#define D_LEVEL_10 "livello 1-0"
#define D_LEVEL_01 "livello 0-1"
#define D_SERIAL_LOGGING_DISABLED "Registro attività seriale disabilitato"
#define D_SYSLOG_LOGGING_REENABLED "Syslog ri-abilitato"

#define D_SET_BAUDRATE_TO "Imposta baudrate"
#define D_RECEIVED_TOPIC "Topic Ricevuto"
#define D_DATA_SIZE "Dimensione dati"
#define D_ANALOG_INPUT "Ingresso analogico"

// support.ino
#define D_OSWATCH "osWatch"
#define D_BLOCKED_LOOP "Ciclo bloccato"
#define D_WPS_FAILED_WITH_STATUS "WPSconfig fallito con stato"
#define D_ACTIVE_FOR_3_MINUTES "Attivo per 3 minuti"
#define D_FAILED_TO_START "Avvio fallito"
#define D_PATCH_ISSUE_2186 "Patch problema 2186"
#define D_CONNECTING_TO_AP "Connessione ad AP"
#define D_IN_MODE "In modalità"
#define D_CONNECT_FAILED_NO_IP_ADDRESS "Connessione fallita - indirizzo IP non ricevuto"
#define D_CONNECT_FAILED_AP_NOT_REACHED "Connessione fallita - AP non raggiungibile"
#define D_CONNECT_FAILED_WRONG_PASSWORD "Connessione fallita"
#define D_CONNECT_FAILED_AP_TIMEOUT "Connessione fallita - timeout AP"
#define D_ATTEMPTING_CONNECTION "Tentativo di connessione..."
#define D_CHECKING_CONNECTION "Controllo connessione..."
#define D_QUERY_DONE "Query eseguita. Servizio MQTT trovato"
#define D_MQTT_SERVICE_FOUND "Servizio MQTT trovato in"
#define D_FOUND_AT "trovato in"
#define D_SYSLOG_HOST_NOT_FOUND "Host Syslog non trovato"

// settings.ino
#define D_SAVED_TO_FLASH_AT "Salvato nella flash in"
#define D_LOADED_FROM_FLASH_AT "Caricato dalla flash da"
#define D_USE_DEFAULTS "Usa valori predefiniti"
#define D_ERASED_SECTOR "Settore cancellato"

// xdrv_02_webserver.ino
#define D_NOSCRIPT "Per usare Tasmota abilita JavaScript"
#define D_MINIMAL_FIRMWARE_PLEASE_UPGRADE "FFirmware MINIMALE<br>Effettua aggiornamento"
#define D_WEBSERVER_ACTIVE_ON "Server web attivo in"
#define D_WITH_IP_ADDRESS "con indirizzo IP"
#define D_WEBSERVER_STOPPED "Server web arrestato"
#define D_FILE_NOT_FOUND "File non trovato"
#define D_REDIRECTED "Redirezione al captive portal"
#define D_WIFIMANAGER_SET_ACCESSPOINT_AND_STATION "Impostazione Wifimanager come Access Point e Station"
#define D_WIFIMANAGER_SET_ACCESSPOINT "Impostazione Wifimanager come Access Point"
#define D_TRYING_TO_CONNECT "Tentativo connessione dispositivo alla rete"

#define D_RESTART_IN "Riavvio tra"
#define D_SECONDS "secondi"
#define D_DEVICE_WILL_RESTART "Il dispositivo verrà riavviato tra pochi secondi"
#define D_BUTTON_TOGGLE "ON/OFF"
#define D_CONFIGURATION "Impostazioni"
#define D_INFORMATION "Informazioni"
#define D_FIRMWARE_UPGRADE "Aggiorna firmware"
#define D_CONSOLE "Console"
#define D_CONFIRM_RESTART "Conferma riavvio"

#define D_CONFIGURE_MODULE "Modulo"
#define D_CONFIGURE_WIFI "Rete WiFi"
#define D_CONFIGURE_MQTT "MQTT"
#define D_CONFIGURE_DOMOTICZ "Domoticz"
#define D_CONFIGURE_LOGGING "Livelli registri"
#define D_CONFIGURE_OTHER "Altre impostazioni"
#define D_CONFIRM_RESET_CONFIGURATION "Conferma ripristino impostazioni"
#define D_RESET_CONFIGURATION "Ripristino impostazioni"
#define D_BACKUP_CONFIGURATION "Backup impostazioni"
#define D_RESTORE_CONFIGURATION "Ripristino impostazioni"
#define D_MAIN_MENU "Menu principale"

#define D_MODULE_PARAMETERS "Parametri modulo"
#define D_MODULE_TYPE "Tipo modulo"
#define D_PULLUP_ENABLE "Nessun pulsante/switch pull-up"
#define D_ADC "ADC"
#define D_GPIO "GPIO"
#define D_SERIAL_IN "Seriale - IN"
#define D_SERIAL_OUT "Seriale - OUT"

#define D_WIFI_PARAMETERS "Parametri WiFi"
#define D_SCAN_FOR_WIFI_NETWORKS "Scansione reti WiFi"
#define D_SCAN_DONE "Scansione completata"
#define D_NO_NETWORKS_FOUND "Nessuna rete trovata"
#define D_REFRESH_TO_SCAN_AGAIN "Aggiorna per nuova scansione"
#define D_DUPLICATE_ACCESSPOINT "Access Point duplicato"
#define D_SKIPPING_LOW_QUALITY "Ignorato a causa di bassa qualità"
#define D_RSSI "RSSI"
#define D_WEP "WEP"
#define D_WPA_PSK "WPA PSK"
#define D_WPA2_PSK "WPA2 PSK"
#define D_AP1_SSID "AP1 - SSID"
#define D_AP1_PASSWORD "AP1 - Password"
#define D_AP2_SSID "AP2 - SSID"
#define D_AP2_PASSWORD "AP2 - Password"

#define D_MQTT_PARAMETERS "Parametri MQTT"
#define D_CLIENT "Client"
#define D_FULL_TOPIC "Full topic"

#define D_LOGGING_PARAMETERS "Livelli registri eventi"
#define D_SERIAL_LOG_LEVEL "Livello registro seriale"
#define D_MQTT_LOG_LEVEL "Livello registro MQTT"
#define D_WEB_LOG_LEVEL "Livello registro web"
#define D_SYS_LOG_LEVEL "Livello registro Sys"
#define D_MORE_DEBUG "Debug aggiuntivo"
#define D_SYSLOG_HOST "Host Syslog"
#define D_SYSLOG_PORT "Porta Syslog"
#define D_TELEMETRY_PERIOD "Periodo telemetria"

#define D_OTHER_PARAMETERS "Altri parametri"
#define D_TEMPLATE "Modello"
#define D_ACTIVATE "Attiva"
#define D_DEVICE_NAME "Nome dispositivo"
#define D_WEB_ADMIN_PASSWORD "Password amministratore web"
#define D_MQTT_ENABLE "Abilita MQTT"
#define D_FRIENDLY_NAME "Nome amichevole"
#define D_BELKIN_WEMO "Belkin WeMo"
#define D_HUE_BRIDGE "Bridge Hue"
#define D_SINGLE_DEVICE "dispositivo singolo"
#define D_MULTI_DEVICE "dispositivo multiplo"

#define D_CONFIGURE_TEMPLATE "Modello"
#define D_TEMPLATE_PARAMETERS "Parametri modello"
#define D_TEMPLATE_NAME "Nome"
#define D_BASE_TYPE "Basato su"
#define D_TEMPLATE_FLAGS "Opzioni"

#define D_SAVE_CONFIGURATION "Salva impostazioni"
#define D_CONFIGURATION_SAVED "Impostazioni salvate"
#define D_CONFIGURATION_RESET "Impostazioni ripristinate"

#define D_PROGRAM_VERSION "Versione programma"
#define D_BUILD_DATE_AND_TIME "Data/ora compilazione"
#define D_CORE_AND_SDK_VERSION "Versione core/SDK"
#define D_FLASH_WRITE_COUNT "Numero scritture flash"
#define D_MAC_ADDRESS "Indirizzo MAC"
#define D_MQTT_HOST "Host MQTT"
#define D_MQTT_PORT "Porta MQTT"
#define D_MQTT_CLIENT "Client MQTT"
#define D_MQTT_USER "Utente MQTT"
#define D_MQTT_TOPIC "Topic MQTT"
#define D_MQTT_GROUP_TOPIC "Gruppo topic MQTT"
#define D_MQTT_FULL_TOPIC "Full topic MQTT"
#define D_MDNS_DISCOVERY "Ricerca mDNS"
#define D_MDNS_ADVERTISE "Notifica mDNS"
#define D_ESP_CHIP_ID "ID chip ESP"
#define D_FLASH_CHIP_ID "ID chip flash"
#define D_FLASH_CHIP_SIZE "Dimensione flash"
#define D_FREE_PROGRAM_SPACE "Memoria libera programma"

#define D_UPGRADE_BY_WEBSERVER "Aggiornamento via server web"
#define D_OTA_URL "URL OTA"
#define D_START_UPGRADE "Esegui aggiornamento"
#define D_UPGRADE_BY_FILE_UPLOAD "Aggiornamento tramite file locale"
#define D_UPLOAD_STARTED "Caricamento..."
#define D_UPGRADE_STARTED "Aggiornamento..."
#define D_UPLOAD_DONE "Caricamento completato"
#define D_UPLOAD_ERR_1 "Nessun file selezionato"
#define D_UPLOAD_ERR_2 "Spazio insufficiente"
#define D_UPLOAD_ERR_3 "Magic byte non corrispondente a 0xE9"
#define D_UPLOAD_ERR_4 "Dimensione memoria programma maggiore della dimensione reale della flash"
#define D_UPLOAD_ERR_5 "Errore comparazione buffer upload"
#define D_UPLOAD_ERR_6 "Invio fallito. Abilita registrazione logging 3"
#define D_UPLOAD_ERR_7 "Upload annullato"
#define D_UPLOAD_ERR_8 "File non valido"
#define D_UPLOAD_ERR_9 "File troppo grande"
#define D_UPLOAD_ERR_10 "Inizializzazione chip RF fallita"
#define D_UPLOAD_ERR_11 "Cancellazione chip RF fallita"
#define D_UPLOAD_ERR_12 "Scrittura chip RF fallita"
#define D_UPLOAD_ERR_13 "Decodifica firmware RF fallita"
#define D_UPLOAD_ERR_14 "Non compatibile"
#define D_UPLOAD_ERROR_CODE "Codice errore upload"

#define D_ENTER_COMMAND "Inserisci comando"
#define D_ENABLE_WEBLOG_FOR_RESPONSE "Abilita weblog 2 se è attesa una risposta"
#define D_NEED_USER_AND_PASSWORD "Richiesto utente=<username>&password=<password>"

// xdrv_01_mqtt.ino
#define D_FINGERPRINT "Verifica chiave TLS..."
#define D_TLS_CONNECT_FAILED_TO "Connessione TLS fallita a"
#define D_RETRY_IN "Nuovo tentativo in"
#define D_VERIFIED "Verificato tramite chiave"
#define D_INSECURE "Connessione non sicura a causa di chiave non valida"
#define D_CONNECT_FAILED_TO "Connessione fallita a"

// xplg_wemohue.ino
#define D_MULTICAST_DISABLED "Multicast disabilitato"
#define D_MULTICAST_REJOINED "Multicast (ri)associato"
#define D_MULTICAST_JOIN_FAILED "Associazione multicast fallita"
#define D_FAILED_TO_SEND_RESPONSE "Invio risposta fallito"

#define D_WEMO "WeMo"
#define D_WEMO_BASIC_EVENT "Evento base WeMo"
#define D_WEMO_EVENT_SERVICE "Servizio eventi WeMo"
#define D_WEMO_META_SERVICE "Servizio meta WeMo"
#define D_WEMO_SETUP "Impostazione WeMo"
#define D_RESPONSE_SENT "Risposta inviata"

#define D_HUE "Hue"
#define D_HUE_BRIDGE_SETUP "Impostazione Hue"
#define D_HUE_API_NOT_IMPLEMENTED "API Hue non implementata"
#define D_HUE_API "API Hue"
#define D_HUE_POST_ARGS "POST argomenti Hue"
#define D_3_RESPONSE_PACKETS_SENT "3 pacchetti di risposta inviati"

// xdrv_07_domoticz.ino
#define D_DOMOTICZ_PARAMETERS "Parametri Domoticz"
#define D_DOMOTICZ_IDX "Idx"
#define D_DOMOTICZ_KEY_IDX "Idx - chiave"
#define D_DOMOTICZ_SWITCH_IDX "Idx - switch"
#define D_DOMOTICZ_SENSOR_IDX "Idx - sensore"
  #define D_DOMOTICZ_TEMP "Temp"
  #define D_DOMOTICZ_TEMP_HUM "Temp,Umd"
  #define D_DOMOTICZ_TEMP_HUM_BARO "Temp,Umd,Baro"
  #define D_DOMOTICZ_POWER_ENERGY "Alim,Energia"
  #define D_DOMOTICZ_ILLUMINANCE "Illuminazione"
  #define D_DOMOTICZ_COUNT "Cont/PM1"
  #define D_DOMOTICZ_VOLTAGE "Tensione/PM2.5"
  #define D_DOMOTICZ_CURRENT "Corrente/PM10"
  #define D_DOMOTICZ_AIRQUALITY "Qualità aria"
  #define D_DOMOTICZ_P1_SMART_METER "P1SmartMeter"
#define D_DOMOTICZ_UPDATE_TIMER "Intervallo aggiornamento"

// xdrv_09_timers.ino
#define D_CONFIGURE_TIMER "Timer"
#define D_TIMER_PARAMETERS "Parametri timer"
#define D_TIMER_ENABLE "Abilita timer"
#define D_TIMER_ARM "Attiva"
#define D_TIMER_TIME "Ora"
#define D_TIMER_DAYS "Giorni"
#define D_TIMER_REPEAT "Ripeti"
#define D_TIMER_OUTPUT "Output"
#define D_TIMER_ACTION "Azione"

// xdrv_10_knx.ino
#define D_CONFIGURE_KNX "KNX"
#define D_KNX_PARAMETERS "Parametri KNX"
#define D_KNX_GENERAL_CONFIG "Generale"
#define D_KNX_PHYSICAL_ADDRESS "Indirizzo fisico"
#define D_KNX_PHYSICAL_ADDRESS_NOTE "(deve essere univoco nella rete KNX )"
#define D_KNX_ENABLE "Abilita KNX"
#define D_KNX_GROUP_ADDRESS_TO_WRITE "Dati da inviare al gruppo di indirizzi"
#define D_ADD "Aggiungi"
#define D_DELETE "Elimina"
#define D_REPLY "Rispondi"
#define D_KNX_GROUP_ADDRESS_TO_READ "Gruppo di indirizzi da cui ricevere dati"
#define D_RECEIVED_FROM "Ricevuto da"
#define D_KNX_COMMAND_WRITE "Scrivi"
#define D_KNX_COMMAND_READ "Leggi"
#define D_KNX_COMMAND_OTHER "Altro"
#define D_SENT_TO "invia a"
#define D_KNX_WARNING "L'indirizzo del gruppo ( 0 / 0 / 0 ) è riservato e non può essere usato."
#define D_KNX_ENHANCEMENT "Miglioramento comunicazione"
#define D_KNX_TX_SLOT "KNX - TX"
#define D_KNX_RX_SLOT "KNX - RX"
#define D_KNX_TX_SCENE "Scena - TX"
#define D_KNX_RX_SCENE "Scena - RX"

// xdrv_03_energy.ino
#define D_ENERGY_TODAY "Energia - oggi"
#define D_ENERGY_YESTERDAY "Energia  - ieri"
#define D_ENERGY_TOTAL "Energia - totale"

// xdrv_27_shutter.ino
#define D_OPEN "Apri"
#define D_CLOSE "Chiudi"
#define D_DOMOTICZ_SHUTTER "Serranda"

// xdrv_28_pcf8574.ino
#define D_CONFIGURE_PCF8574 "PCF8574"
#define D_PCF8574_PARAMETERS "Parametri PCF8574"
#define D_INVERT_PORTS "Inverti porte"
#define D_DEVICE "Dispositivo"
#define D_DEVICE_INPUT "Input"
#define D_DEVICE_OUTPUT "Output"

// xsns_05_ds18b20.ino
#define D_SENSOR_BUSY "Sensore occupato"
#define D_SENSOR_CRC_ERROR "Errore CRC sensore"
#define D_SENSORS_FOUND "Sensori trovati"

// xsns_06_dht.ino
#define D_TIMEOUT_WAITING_FOR "Timeout attesa per"
#define D_START_SIGNAL_LOW "inizio segnale basso"
#define D_START_SIGNAL_HIGH "inizio segnale alto"
#define D_PULSE "impulso"
#define D_CHECKSUM_FAILURE "Checksum fallito"

// xsns_07_sht1x.ino
#define D_SENSOR_DID_NOT_ACK_COMMAND "Il sensore non ha eseguito il comando ACK"
#define D_SHT1X_FOUND "Trovato SHT1X"

// xsns_18_pms5003.ino
#define D_STANDARD_CONCENTRATION "CF-1 PM"     // Standard Particle CF-1 Particle Matter
#define D_ENVIRONMENTAL_CONCENTRATION "PM"     // Environmetal Particle Matter
#define D_PARTICALS_BEYOND "Particelle"

// xsns_27_apds9960.ino
#define D_GESTURE "Gesto"
#define D_COLOR_RED "Rosso"
#define D_COLOR_GREEN "Verde"
#define D_COLOR_BLUE "Blu"
#define D_CCT "CCT"
#define D_PROXIMITY "Vicinanza"

// xsns_32_mpu6050.ino
#define D_AX_AXIS "Accelerazione asse X"
#define D_AY_AXIS "Accelerazione asse Y"
#define D_AZ_AXIS "Accelerazione asse Z"
#define D_GX_AXIS "Giroscopio asse X"
#define D_GY_AXIS "Giroscopio asse Y"
#define D_GZ_AXIS "Giroscopio asse Z"

// xsns_34_hx711.ino
#define D_HX_CAL_REMOVE "Rimuovi peso"
#define D_HX_CAL_REFERENCE "Carica riferimento peso"
#define D_HX_CAL_DONE "Calibrato"
#define D_HX_CAL_FAIL "Calibrazione fallita"
#define D_RESET_HX711 "Ripristino scala"
#define D_CONFIGURE_HX711 "Scala"
#define D_HX711_PARAMETERS "Parametri scala"
#define D_ITEM_WEIGHT "Peso oggetto"
#define D_REFERENCE_WEIGHT "Peso di riferimento"
#define D_CALIBRATE "Calibrato"
#define D_CALIBRATION "Calibrazione"

//xsns_35_tx20.ino
#define D_TX20_WIND_DIRECTION "Direzione vento"
#define D_TX20_WIND_SPEED "Velocità vento"
#define D_TX20_WIND_SPEED_MIN "Velocità minima vento"
#define D_TX20_WIND_SPEED_MAX "Velocità massima vento"
#define D_TX20_NORTH "N"
#define D_TX20_EAST "E"
#define D_TX20_SOUTH "S"
#define D_TX20_WEST "O"

// xsns_53_sml.ino
#define D_TPWRIN "Energia totale IN"
#define D_TPWROUT "Energia totale OUT"
#define D_TPWRCURR "Corrente IN/OUT"
#define D_TPWRCURR1 "Corrente IN p1"
#define D_TPWRCURR2 "Corrente IN p2"
#define D_TPWRCURR3 "Corrente IN p3"
#define D_Strom_L1 "Corrente L1"
#define D_Strom_L2 "Corrente L2"
#define D_Strom_L3 "Corrente L3"
#define D_Spannung_L1 "Tensione L1"
#define D_Spannung_L2 "Tensione L2"
#define D_Spannung_L3 "Tensione L3"
#define D_METERNR "Meter_number"
#define D_METERSID "ID servizio"
#define D_GasIN "Contatore"
#define D_H2oIN "Contatore"
#define D_StL1L2L3 "Corrente L1+L2+L3"
#define D_SpL1L2L3 "Tensione L1+L2+L3/3"

// tasmota_template.h - keep them as short as possible to be able to fit them in GUI drop down box
#define D_SENSOR_NONE          "Nessuno"
#define D_SENSOR_USER          "User"
#define D_SENSOR_DHT11         "DHT11"
#define D_SENSOR_AM2301        "AM2301"
#define D_SENSOR_SI7021        "SI7021"
#define D_SENSOR_DS18X20       "DS18x20"
#define D_SENSOR_I2C_SCL       "I2C SCL"
#define D_SENSOR_I2C_SDA       "I2C SDA"
#define D_SENSOR_WS2812        "WS2812"
#define D_SENSOR_DFR562        "Riproduttore MP3"
#define D_SENSOR_IRSEND        "IR - TX"
#define D_SENSOR_SWITCH        "Switch"          // Suffix "1"
#define D_SENSOR_BUTTON        "Pulsante"        // Suffix "1"
#define D_SENSOR_RELAY         "Relè"            // Suffix "1i"
#define D_SENSOR_LED           "Led"             // Suffix "1i"
#define D_SENSOR_LED_LINK      "Led - Lampeggio" // Suffix "i"
#define D_SENSOR_PWM           "PWM"             // Suffix "1"
#define D_SENSOR_COUNTER       "Contatore"       // Suffix "1"
#define D_SENSOR_IRRECV        "IR - RX"
#define D_SENSOR_MHZ_RX        "MHZ - RX"
#define D_SENSOR_MHZ_TX        "MHZ - TX"
#define D_SENSOR_PZEM004_RX    "PZEM004 - RX"
#define D_SENSOR_PZEM016_RX    "PZEM016 - RX"
#define D_SENSOR_PZEM017_RX    "PZEM017 - RX"
#define D_SENSOR_PZEM0XX_TX    "PZEM0XX - TX"
#define D_SENSOR_SAIR_RX       "SAir - RX"
#define D_SENSOR_SAIR_TX       "SAir - TX"
#define D_SENSOR_SPI_CS        "SPI - CS"
#define D_SENSOR_SPI_DC        "SPI - DC"
#define D_SENSOR_SPI_MISO      "SPI - MISO"
#define D_SENSOR_SPI_MOSI      "SPI - MOSI"
#define D_SENSOR_SPI_CLK       "SPI - CLK"
#define D_SENSOR_BACKLIGHT     "Retroilluminazione"
#define D_SENSOR_PMS5003_TX    "PMS5003 - TX"
#define D_SENSOR_PMS5003_RX    "PMS5003 - RX"
#define D_SENSOR_SDS0X1_RX     "SDS0X1 - RX"
#define D_SENSOR_SDS0X1_TX     "SDS0X1 - TX"
#define D_SENSOR_HPMA_RX       "HPMA  - RX"
#define D_SENSOR_HPMA_TX       "HPMA - TX"
#define D_SENSOR_SBR_RX        "SerBr - RX"
#define D_SENSOR_SBR_TX        "SerBr - TX"
#define D_SENSOR_SR04_TRIG     "SR04 Tri - TX"
#define D_SENSOR_SR04_ECHO     "SR04 Ech - RX"
#define D_SENSOR_SDM120_TX     "SDMx20 - TX"
#define D_SENSOR_SDM120_RX     "SDMx20 - RX"
#define D_SENSOR_SDM630_TX     "SDM630 - TX"
#define D_SENSOR_SDM630_RX     "SDM630 - RX"
#define D_SENSOR_TM1638_CLK    "TM16 - CLK"
#define D_SENSOR_TM1638_DIO    "TM16 - DIO"
#define D_SENSOR_TM1638_STB    "TM16 - STB"
#define D_SENSOR_HX711_SCK     "HX711 - SCK"
#define D_SENSOR_HX711_DAT     "HX711 - DAT"
#define D_SENSOR_TX2X_TX       "TX2x"
#define D_SENSOR_RFSEND        "RF - TX"
#define D_SENSOR_RFRECV        "RF - RX"
#define D_SENSOR_TUYA_TX       "Tuya - TX"
#define D_SENSOR_TUYA_RX       "Tuya - RX"
#define D_SENSOR_MGC3130_XFER  "MGC3130 - XFR"
#define D_SENSOR_MGC3130_RESET "MGC3130 - RST"
#define D_SENSOR_SSPI_MISO     "SSPI - MISO"
#define D_SENSOR_SSPI_MOSI     "SSPI - MOSI"
#define D_SENSOR_SSPI_SCLK     "SSPI - SCLK"
#define D_SENSOR_SSPI_CS       "SSPI - CS"
#define D_SENSOR_SSPI_DC       "SSPI - DC"
#define D_SENSOR_RF_SENSOR     "Sensore RF"
#define D_SENSOR_AZ_RX         "AZ - RX"
#define D_SENSOR_AZ_TX         "AZ - TX"
#define D_SENSOR_MAX31855_CS   "MX31855 - CS"
#define D_SENSOR_MAX31855_CLK  "MX31855 - CLK"
#define D_SENSOR_MAX31855_DO   "MX31855 - DO"
#define D_SENSOR_NRG_SEL       "HLWBL - SEL"  // Suffix "i"
#define D_SENSOR_NRG_CF1       "HLWBL - CF1"
#define D_SENSOR_HLW_CF        "HLW8012 - CF"
#define D_SENSOR_HJL_CF        "BL0937 - CF"
#define D_SENSOR_MCP39F5_TX    "MCP39F5 - TX"
#define D_SENSOR_MCP39F5_RX    "MCP39F5 - RX"
#define D_SENSOR_MCP39F5_RST   "MCP39F5 Rst"
#define D_SENSOR_CSE7766_TX    "CSE7766 - TX"
#define D_SENSOR_CSE7766_RX    "CSE7766 - RX"
#define D_SENSOR_PN532_TX      "PN532 - TX"
#define D_SENSOR_PN532_RX      "PN532 - RX"
#define D_SENSOR_SM16716_CLK   "SM16716 - CLK"
#define D_SENSOR_SM16716_DAT   "SM16716 - DAT"
#define D_SENSOR_SM16716_POWER "SM16716 - PWR"
#define D_SENSOR_MY92X1_DI     "MY92x1 - DI"
#define D_SENSOR_MY92X1_DCKI   "MY92x1 - DCKI"
#define D_SENSOR_ARIRFRCV      "IR ALux - RCV"
#define D_SENSOR_ARIRFSEL      "IR ALux - SEL"
#define D_SENSOR_TXD           "Seriale - TX"
#define D_SENSOR_RXD           "Seriale - RX"
#define D_SENSOR_ROTARY        "Rotary"     // Suffix "1A"
#define D_SENSOR_HRE_CLOCK     "HRE - Clock"
#define D_SENSOR_HRE_DATA      "HRE - Dati"
#define D_SENSOR_ADE7953_IRQ   "ADE7953 - IRQ"
#define D_SENSOR_BUZZER        "Cicalino"
#define D_SENSOR_OLED_RESET    "Ripristino OLED"
#define D_SENSOR_ZIGBEE_TXD    "Zigbee - TX"
#define D_SENSOR_ZIGBEE_RXD    "Zigbee - RX"
#define D_SENSOR_SOLAXX1_TX    "SolaxX1 - TX"
#define D_SENSOR_SOLAXX1_RX    "SolaxX1- RX"
#define D_SENSOR_IBEACON_TX    "iBeacon - TX"
#define D_SENSOR_IBEACON_RX    "iBeacon - RX"
#define D_SENSOR_RDM6300_RX    "RDM6300 - RX"
#define D_SENSOR_CC1101_CS     "CC1101 - CS"
#define D_SENSOR_A4988_DIR     "A4988 - DIR"
#define D_SENSOR_A4988_STP     "A4988 - STP"
#define D_SENSOR_A4988_ENA     "A4988 - ENA"
#define D_SENSOR_A4988_MS1     "A4988 - MS1"
#define D_SENSOR_A4988_MS2     "A4988 - MS2"
#define D_SENSOR_A4988_MS3     "A4988 - MS3"
#define D_SENSOR_DDS2382_TX    "DDS238-2 - TX"
#define D_SENSOR_DDS2382_RX    "DDS238-2 - RX"
#define D_SENSOR_DDSU666_TX    "DDSU666 - TX"
#define D_SENSOR_DDSU666_RX    "DDSU666 - RX"
#define D_SENSOR_SM2135_CLK    "SM2135 - CLK"
#define D_SENSOR_SM2135_DAT    "SM2135 - DATI"
#define D_SENSOR_DEEPSLEEP     "Deep sleep"
#define D_SENSOR_EXS_ENABLE    "EXS - Abilita"
#define D_SENSOR_CLIENT_TX     "Client - TX"
#define D_SENSOR_CLIENT_RX     "Client - RX"
#define D_SENSOR_CLIENT_RESET  "Client - RST"
#define D_SENSOR_GPS_RX        "GPS - RX"
#define D_SENSOR_GPS_TX        "GPS - TX"
#define D_SENSOR_HM10_RX       "HM10 - RX"
#define D_SENSOR_HM10_TX       "HM10 - TX"
#define D_SENSOR_LE01MR_RX     "LE-01MR - RX"
#define D_SENSOR_LE01MR_TX     "LE-01MR - TX"
#define D_SENSOR_BL0940_RX     "BL0940 - RX"
#define D_SENSOR_CC1101_GDO0   "CC1101 - GDO0"
#define D_SENSOR_CC1101_GDO2   "CC1101 - GDO2"
#define D_SENSOR_HRXL_RX       "HRXL - RX"
#define D_SENSOR_ELECTRIQ_MOODL "MOODL - TX"
#define D_SENSOR_AS3935         "AS3935"
#define D_SENSOR_WINDMETER_SPEED "Velocità vento"
#define D_SENSOR_TELEINFO_RX    "TInfo Rx"
#define D_SENSOR_TELEINFO_ENABLE "TInfo EN"
#define D_SENSOR_LMT01_PULSE   "LMT01 Pulse"
#define D_GPIO_WEBCAM_PWDN     "CAM_PWDN"
#define D_GPIO_WEBCAM_RESET    "CAM_RESET"
#define D_GPIO_WEBCAM_XCLK     "CAM_XCLK"
#define D_GPIO_WEBCAM_SIOD     "CAM_SIOD"
#define D_GPIO_WEBCAM_SIOC     "CAM_SIOC"
#define D_GPIO_WEBCAM_DATA     "CAM_DATA"
#define D_GPIO_WEBCAM_VSYNC    "CAM_VSYNC"
#define D_GPIO_WEBCAM_HREF     "CAM_HREF"
#define D_GPIO_WEBCAM_PCLK     "CAM_PCLK"
#define D_GPIO_WEBCAM_PSCLK    "CAM_PSCLK"
#define D_GPIO_WEBCAM_HSD      "CAM_HSD"
#define D_GPIO_WEBCAM_PSRCS    "CAM_PSRCS"
#define D_SENSOR_ETH_PHY_POWER "ETH POWER"
#define D_SENSOR_ETH_PHY_MDC   "ETH MDC"
#define D_SENSOR_ETH_PHY_MDIO  "ETH MDIO"
#define D_SENSOR_TCP_TXD       "TCP - TX"
#define D_SENSOR_TCP_RXD       "TCP - RX"
#define D_SENSOR_IEM3000_TX    "iEM3000 - TX"
#define D_SENSOR_IEM3000_RX    "iEM3000 - RX"
#define D_SENSOR_GSD_DIR     "GSD DIR"
#define D_SENSOR_GSD_STP     "GSD STP"
#define D_SENSOR_GSD_ENA     "GSD ENA"
#define D_SENSOR_GSD_ENA_INV "GSD ENA INV"
#define D_SENSOR_GSD_MS1     "GSD MS1"
#define D_SENSOR_GSD_MS2     "GSD MS2"
#define D_SENSOR_GSD_MS3     "GSD MS3"
#define D_SENSOR_GSD_UART_TX "GSD UART TX"
#define D_SENSOR_GSD_UART_RX "GSD UART RX"

// Units
#define D_UNIT_AMPERE "A"
#define D_UNIT_CELSIUS "C"
#define D_UNIT_CENTIMETER "cm"
#define D_UNIT_DEGREE "°"
#define D_UNIT_FAHRENHEIT "F"
#define D_UNIT_HERTZ "Hz"
#define D_UNIT_HOUR "o"
#define D_UNIT_GALLONS "gal"
#define D_UNIT_GALLONS_PER_MIN "g/m"
#define D_UNIT_INCREMENTS "inc"
#define D_UNIT_KELVIN "K"
#define D_UNIT_KILOMETER "km"
#define D_UNIT_KILOGRAM "kg"
#define D_UNIT_KILOMETER_PER_HOUR "km/h"  // or "km/h"
#define D_UNIT_KILOOHM "kΩ"
#define D_UNIT_KILOWATTHOUR "kWh"
#define D_UNIT_LUX "lx"
#define D_UNIT_MICROGRAM_PER_CUBIC_METER "µg/m³"
#define D_UNIT_MICROMETER "µm"
#define D_UNIT_MICROSECOND "µs"
#define D_UNIT_MILLIAMPERE "mA"
#define D_UNIT_MILLIMETER "mm"
#define D_UNIT_MILLIMETER_MERCURY "mmHg"
#define D_UNIT_MILLISECOND "ms"
#define D_UNIT_MINUTE "Min"
#define D_UNIT_PARTS_PER_BILLION "ppb"
#define D_UNIT_PARTS_PER_DECILITER "ppd"
#define D_UNIT_PARTS_PER_MILLION "ppm"
#define D_UNIT_PERCENT "%%"
#define D_UNIT_PRESSURE "hPa"
#define D_UNIT_SECOND "sec"
#define D_UNIT_SECTORS "settori"
#define D_UNIT_VA "VA"
#define D_UNIT_VAR "VAr"
#define D_UNIT_VOLT "V"
#define D_UNIT_WATT "W"
#define D_UNIT_WATTHOUR "Wh"
#define D_UNIT_WATT_METER_QUADRAT "W/m²"

//SDM220, SDM120, LE01MR
#define D_PHASE_ANGLE     "Angolo Fase"
#define D_IMPORT_ACTIVE   "Potenza attiva importata"
#define D_EXPORT_ACTIVE   "Potenza attiva esportata"
#define D_IMPORT_REACTIVE "Potenza reattiva importata"
#define D_EXPORT_REACTIVE "Potenza reattiva esportata"
#define D_TOTAL_REACTIVE  "Potenza reattiva totale"
#define D_UNIT_KWARH      "kVArh"
#define D_UNIT_ANGLE      "°"
#define D_TOTAL_ACTIVE    "Potenza attiva totale"

//SOLAXX1
#define D_PV1_VOLTAGE     "PV1 - Voltaggio"
#define D_PV1_CURRENT     "PV1 - Corrente"
#define D_PV1_POWER       "PV1 - Energia"
#define D_PV2_VOLTAGE     "PV2 - Voltaggio"
#define D_PV2_CURRENT     "PV2 - Corrente"
#define D_PV2_POWER       "PV2 - Energia"
#define D_SOLAR_POWER     "Energia solare"
#define D_INVERTER_POWER  "Energia inverter"
#define D_STATUS          "Stato"
#define D_WAITING         "In attesa"
#define D_CHECKING        "Controllo"
#define D_WORKING         "Attivo"
#define D_FAILURE         "Errore"
#define D_SOLAX_ERROR_0   "Nessun codice errore"
#define D_SOLAX_ERROR_1   "Griglia errore persa"
#define D_SOLAX_ERROR_2   "Griglia errore tensione"
#define D_SOLAX_ERROR_3   "Griglia errore frequenza"
#define D_SOLAX_ERROR_4   "Errore tensione PV"
#define D_SOLAX_ERROR_5   "Errore isolamento"
#define D_SOLAX_ERROR_6   "Errore temperatura eccessiva"
#define D_SOLAX_ERROR_7   "Errore ventilatore"
#define D_SOLAX_ERROR_8   "Altro errore dispositivo"

//xdrv_10_scripter.ino
#define D_CONFIGURE_SCRIPT     "Modifica script"
#define D_SCRIPT               "modifica script"
#define D_SDCARD_UPLOAD        "upload file"
#define D_SDCARD_DIR           "cartella scheda SD"
#define D_UPL_DONE             "Completato"
#define D_SCRIPT_CHARS_LEFT    "caratteri rimanenti"
#define D_SCRIPT_CHARS_NO_MORE "nessun altro carattere"
#define D_SCRIPT_DOWNLOAD      "Download"
#define D_SCRIPT_ENABLE        "abilita script"
#define D_SCRIPT_UPLOAD        "Carica"
#define D_SCRIPT_UPLOAD_FILES  "Carica file"

//xsns_67_as3935.ino
#define D_AS3935_GAIN "guadagno:"
#define D_AS3935_ENERGY "energia:"
#define D_AS3935_DISTANCE "distanza:"
#define D_AS3935_DISTURBER "disturbatore:"
#define D_AS3935_VRMS "µVrms:"
#define D_AS3935_APRX "apross.:"
#define D_AS3935_AWAY "lontano"
#define D_AS3935_LIGHT "illuminazione"
#define D_AS3935_OUT "illuminazione fuori intervallo"
#define D_AS3935_NOT "distanza non determinata"
#define D_AS3935_ABOVE "illuminazione ambientale"
#define D_AS3935_NOISE "rilevato rumore"
#define D_AS3935_DISTDET "rilevato disturbatore"
#define D_AS3935_INTNOEV "Interrupt senza evento!"
#define D_AS3935_NOMESS "in ascolto..."
#define D_AS3935_ON "ON"
#define D_AS3935_OFF "OFF"
#define D_AS3935_INDOORS "Interno"
#define D_AS3935_OUTDOORS "Esterno"
#define D_AS3935_CAL_FAIL "calibrazione fallita"
#define D_AS3935_CAL_OK "calibrazione impostata a:"

//xsns_68_opentherm.ino
#define D_SENSOR_BOILER_OT_RX   "OpenTherm - RX"
#define D_SENSOR_BOILER_OT_TX   "OpenTherm - TX"

#endif  // _LANGUAGE_IT_IT_H_
