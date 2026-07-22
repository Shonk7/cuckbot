# sumo bot (quick scaffold)

threw this together from an old project and cleaned it up a little.

should be a decent starting point but no guarantees it'll just work. also i have no idea if the pinouts below are actually right so definitely double check them before uploading.

## files

* `sumo_bot.ino` - main code for the bot

## hardware

this was written for:

* cytron mdd3a motor driver
* 2x hc-sr04 ultrasonic sensors
* 1x tcrt5000 line sensor
* arduino compatible board

## pin map

pretty sure this is what i used but don't trust it blindly.

### motor driver

* `M1_PWM` -> D5
* `M1_DIR` -> D4
* `M2_PWM` -> D6
* `M2_DIR` -> D7

### ultrasonic sensors

* left: `TRIG_L` -> D8, `ECHO_L` -> D9
* right: `TRIG_R` -> D10, `ECHO_R` -> D11

### line sensor

* `LINE` -> A0

might be different depending on whether you're using the analog or digital output.

## what it does

* if it sees the edge, it'll back up then turn.
* if both ultrasonics see something, it'll drive straight at it.
* if only the left sees something, it'll turn left.
* if only the right sees something, it'll turn right.
* if it doesn't see anything it'll just spin looking for an opponent.

## things you'll probably want to change

* `SPEED`
* `TURN_SPEED`
* `DETECT_CM`
* `LINE_DIGITAL`
* `LINE_THRESHOLD` (if using analog mode)

## notes

* there's a `delay(5000)` at the start for comp rules.
* if the edge detection is backwards just flip the `HIGH/LOW` check in `onEdge()`.
* you'll probably have to mess around with the timings in `backThenTurn()` depending on your bot.

## upload

1. open `sumo_bot.ino`
2. pick the right board and port
3. upload it
4. test it with the wheels off the ground first unless you want it launching itself across the room.
