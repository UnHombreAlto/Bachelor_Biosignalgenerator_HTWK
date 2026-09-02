#pragma once
#include "config.h"

// ================= MUX-Steuerung =================


inline void initMuxPins() {
  pinMode(MUX_S0_PIN, OUTPUT);
  pinMode(MUX_S1_PIN, OUTPUT);
  pinMode(MUX_S2_PIN, OUTPUT);
  pinMode(MUX_S3_PIN, OUTPUT);
}

inline void applyMuxChannel() {
  uint8_t ch = selectedMuxChannel & 0x0F;

  digitalWrite(MUX_S0_PIN, (ch & 0x01) ? HIGH : LOW);
  digitalWrite(MUX_S1_PIN, (ch & 0x02) ? HIGH : LOW);
  digitalWrite(MUX_S2_PIN, (ch & 0x04) ? HIGH : LOW);
  digitalWrite(MUX_S3_PIN, (ch & 0x08) ? HIGH : LOW);
}

inline void setMuxChannel(uint8_t channel) {
  if (channel > MUX_CHANNEL_MAX) channel = MUX_CHANNEL_MAX;
  selectedMuxChannel = channel;
  applyMuxChannel();
}

inline void changeMuxChannel(int8_t delta) {
  int16_t next = (int16_t)selectedMuxChannel + (int16_t)delta;

  if (next < MUX_CHANNEL_MIN) next = MUX_CHANNEL_MAX;
  if (next > MUX_CHANNEL_MAX) next = MUX_CHANNEL_MIN;

  setMuxChannel((uint8_t)next);
}
