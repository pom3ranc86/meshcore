#pragma once

// MUST define pins BEFORE including ESP32Board.h (which uses P_LORA_DIO_1 in inline methods)

// E220-900M22S SX1262 LoRa module pin definitions (ESP32-C3)
#define P_LORA_NSS    8   // CS
#define P_LORA_DIO_1  1   // DIO1 / IRQ
#define P_LORA_RESET  2   // Reset
#define P_LORA_BUSY   3   // Busy
#define P_LORA_MISO   5   // SPI MISO
#define P_LORA_SCLK   6   // SPI SCK
#define P_LORA_MOSI   7   // SPI MOSI

#define SX126X_POWER_EN RADIOLIB_NC
#define SX126X_RXEN RADIOLIB_NC
#define SX126X_TXEN RADIOLIB_NC
#define SX126X_DIO2_AS_RF_SWITCH  true
#define SX126X_DIO3_TCXO_VOLTAGE (1.8f)

#define PIN_VBAT_READ 4
#define ADC_MULTIPLIER (2.0f)

#define PIN_USER_BTN  9   // Boot button on ESP32-C3

#include <Arduino.h>
#include <helpers/ESP32Board.h>

class ESP32C3Board : public ESP32Board {
public:
  ESP32C3Board() : ESP32Board() {}

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
    return "ESP32-C3 + E220-900M22S";
  }

  void powerOff() override {
    esp_deep_sleep_start();
  }
};