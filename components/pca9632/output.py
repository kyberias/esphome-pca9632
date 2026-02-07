import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID

from . import pca9632_ns, PCA9632Component

CONF_PCA9632_ID = "pca9632_id"
CONF_CHANNEL = "channel"

PCA9632Output = pca9632_ns.class_("PCA9632Output", output.FloatOutput)

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(PCA9632Output),
        cv.Required(CONF_PCA9632_ID): cv.use_id(PCA9632Component),
        cv.Required(CONF_CHANNEL): cv.int_range(min=0, max=3),
    }
)

async def to_code(config):
    hub = await cg.get_variable(config[CONF_PCA9632_ID])
    var = cg.new_Pvariable(config[CONF_ID], hub, config[CONF_CHANNEL])
    await output.register_output(var, config)
