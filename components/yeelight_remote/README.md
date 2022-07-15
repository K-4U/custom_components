# Yeelight remote component

This component provides support for the Yeelight YLTD001/YTLD003 remote.
To be used in conjunction with https://github.com/dckiller51/esphome-yeelight-led-screen-light-bar

Todo:
- Double press

Example:
```yaml
uart:
  - id: remote_bus
    baud_rate: 4800
    rx_pin: GPIO2

yeelight_remote:
  on_press:
    - light.toggle: light1
  on_left:
    then:
	  - light.dim_relative:
	    id: light1
		relative_brightness: -5%
  on_right:
    then:
	  - light.dim_relative:
	    id: light1
		relative_brightness: 5%
  on_press_left:
	- 
  on_press_right:
	- 
```
