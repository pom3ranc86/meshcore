#pragma once

// MUST define pins BEFORE including ESP32Board.h (which uses P_LORA_DIO_1 in inline methods)

// HT-RA62-C3 SX1262 LoRa module pin definitions (ESP32-C3)
#define P_LORA_NSS    13  // P1.13 45
#define P_LORA_DIO_1  11  // P0.10 10
#define P_LORA_RESET  10  // P0.09 9
#define P_LORA_BUSY   16  // P0.29 29
#define P_LORA_MISO   15  // P0.02 2
#define P_LORA_SCLK   12  // P1.11 43
#define P_LORA_MOSI   14  // P1.15 47

#define SX126X_POWER_EN 21  // P0.13 13
#define SX126X_RXEN 1      // P0.17
#define SX126X_TXEN RADIOLIB_NC
#define SX126X_DIO2_AS_RF_SWITCH  true
#define SX126X_DIO3_TCXO_VOLTAGE (1.8f)

#define PIN_VBAT_READ 17
#define ADC_MULTIPLIER (1.758f)

#define PIN_USER_BTN  9   // Boot button on ESP32-C3

#include <Arduino.h>
#include <helpers/ESP32Board.h>

class HTRA62C3Board : public ESP32Board {
public:
  HTRA62C3Board() : ESP32Board() {}

  void begin() {
    ESP32Board::begin();
  }

  uint16_t getBattMilliVolts() override {
    #ifdef PIN_VBAT_READ
    analogReadResolution(12);
    uint32_t raw = 0;
    for (int i = 0; i < 4; i++) {
      raw += analogReadMilliVolts(PIN_VBAT_READ);
    }
    raw = raw / 4;
    return (ADC_MULTIPLIER * raw);
    #else
    return 0;
    #endif
  }

  const char* getManufacturerName() const override {
    return "ESP32-C3 + HT-RA62-C3";
  }

  void powerOff() override {
    esp_deep_sleep_start();
  }
};
