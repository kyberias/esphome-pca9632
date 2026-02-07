
## `components/pca9632/__init__.py`
```python
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID, CONF_ADDRESS

CODEOWNERS = ["@kyberias"]
DEPENDENCIES = ["i2c"]

pca9632_ns = cg.esphome_ns.namespace("pca9632")
PCA9632Component = pca9632_ns.class_("PCA9632Component", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.declare_id(PCA9632Component),
        cv.Optional(CONF_ADDRESS, default=0x60): cv.i2c_address,
    }
).extend(i2c.i2c_device_schema(0x60))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
