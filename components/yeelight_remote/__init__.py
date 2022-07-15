import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import uart
from esphome.const import CONF_ID

DEPENDENCIES = ['uart']

yeelight_ns = cg.esphome_ns.namespace('yeelight_remote')

YeelightRemote = yeelight_ns.class_('YeelightRemote', cg.Component, uart.UARTDevice)

CONF_ON_PRESS = "on_press"
CONF_ON_LEFT = "on_left"
CONF_ON_RIGHT = "on_right"
CONF_ON_PRESS_LEFT = "on_press_left"
CONF_ON_PRESS_RIGHT = "on_press_right"


CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(YeelightRemote),
    cv.Optional(CONF_ON_PRESS): automation.validate_automation(single=True),
    cv.Optional(CONF_ON_LEFT): automation.validate_automation(single=True),
    cv.Optional(CONF_ON_RIGHT): automation.validate_automation(single=True),
    cv.Optional(CONF_ON_PRESS_LEFT): automation.validate_automation(single=True),
    cv.Optional(CONF_ON_PRESS_RIGHT): automation.validate_automation(single=True),
}).extend(uart.UART_DEVICE_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_ON_PRESS in config:
        await automation.build_automation(
            var.get_press_trigger(), [], config[CONF_ON_PRESS]
        )
    if CONF_ON_LEFT in config:
        await automation.build_automation(
            var.get_left_trigger(), [], config[CONF_ON_LEFT]
        )
    if CONF_ON_RIGHT in config:
        await automation.build_automation(
            var.get_right_trigger(), [], config[CONF_ON_RIGHT]
        )
    if CONF_ON_PRESS_LEFT in config:
        await automation.build_automation(
            var.get_press_left_trigger(), [], config[CONF_ON_PRESS_LEFT]
        )
    if CONF_ON_PRESS_RIGHT in config:
        await automation.build_automation(
            var.get_press_right_trigger(), [], config[CONF_ON_PRESS_RIGHT]
        )
        

