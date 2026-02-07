#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace pca9632 {

class PCA9632Component : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;

  void set_pwm(uint8_t channel, uint8_t value);

 protected:
  uint8_t pwm_cache[4] = {0, 0, 0, 0};
  bool initialized{false};

  // PCA9632 registers
  static constexpr uint8_t REG_MODE1  = 0x00;
  static constexpr uint8_t REG_MODE2  = 0x01;
  static constexpr uint8_t REG_PWM0   = 0x02; // PWM0..PWM3 consecutive
  static constexpr uint8_t REG_GRPPWM = 0x06;
  static constexpr uint8_t REG_GRPFREQ= 0x07;
  static constexpr uint8_t REG_LEDOUT = 0x08;
};

class PCA9632Output : public output::FloatOutput {
 public:
  PCA9632Output(PCA9632Component *parent, uint8_t channel) : parent(parent), channel(channel) {}
  void write_state(float state) override;

 protected:
  PCA9632Component *parent;
  uint8_t channel;
};

}  // namespace pca9632
}  // namespace esphome
