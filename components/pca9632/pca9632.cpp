#include "pca9632.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pca9632 {

static const char *const TAG = "pca9632";

void PCA9632Component::setup() {
  // Initialize like your Arduino code:
  // MODE1 = 0x00
  // LEDOUT = 0xAA => 0b10101010 (each LEDn controlled by PWMn)
  //
  // MODE2 can be left default; set to 0x00 for simplicity.
  uint8_t mode1 = 0x00;
  uint8_t mode2 = 0x00;
  uint8_t ledout = 0xAA;

  if (this->write_register(REG_MODE1, &mode1, 1) != i2c::NO_ERROR) {
    ESP_LOGW(TAG, "Failed to write MODE1");
    return;
  }
  (void) this->write_register(REG_MODE2, &mode2, 1);
  if (this->write_register(REG_LEDOUT, &ledout, 1) != i2c::NO_ERROR) {
    ESP_LOGW(TAG, "Failed to write LEDOUT");
    return;
  }

  // Set all PWM channels to 0
  for (uint8_t ch = 0; ch < 4; ch++) {
    this->set_pwm(ch, 0);
  }

  initialized{true};
}

void PCA9632Component::dump_config() {
  ESP_LOGCONFIG(TAG, "PCA9632:");
  LOG_I2C_DEVICE(this);
  ESP_LOGCONFIG(TAG, "  Initialized: %s", this->initialized ? "yes" : "no");
}

void PCA9632Component::set_pwm(uint8_t channel, uint8_t value) {
  if (channel > 3) return;
  if (this->pwm_cache[channel] == value) return;

  uint8_t reg = REG_PWM0 + channel;
  if (this->write_register(reg, &value, 1) != i2c::NO_ERROR) {
    ESP_LOGW(TAG, "Failed to write PWM%u", channel);
    return;
  }
  this->pwm_cache[channel] = value;
}

void PCA9632Output::write_state(float state) {
  // state is expected 0.0..1.0
  if (state < 0.0f) state = 0.0f;
  if (state > 1.0f) state = 1.0f;

  uint8_t pwm = (uint8_t) lroundf(state * 255.0f);
  this->parent->set_pwm(this->channel_, pwm);
}

}
}
