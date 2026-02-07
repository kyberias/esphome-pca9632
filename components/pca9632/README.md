# ESPHome PCA9632 external component

Exposes PCA9632 PWM channels as ESPHome float outputs (0..1).
Use these outputs with ESPHome light platforms (rgb, monochromatic, etc.)

Example RGB:

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/kyberias/esphome-pca9632
      ref: main
    components: [ pca9632 ]

i2c:

pca9632:
  - id: led_driver
    address: 0x60

output:
  - platform: pca9632
    id: led_r
    pca9632_id: led_driver
    channel: 0
  - platform: pca9632
    id: led_b
    pca9632_id: led_driver
    channel: 1
  - platform: pca9632
    id: led_g
    pca9632_id: led_driver
    channel: 2

light:
  - platform: rgb
    name: "Status LED"
    red: led_r
    green: led_g
    blue: led_b
