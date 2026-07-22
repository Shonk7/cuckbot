# Sumo Bot (quick scaffold)

threw this together from a past project and cleaned it up a bit.
not promising it's perfect out of the box, but it's a solid base.

## Files
- `sumo_bot.ino` - main control loop for the sumo bot

## Hardware this is set up for
- Cytron MDD3A motor driver
- 2x HC-SR04 ultrasonic sensors (left + right)
- 1x TCRT5000 line sensor (ring edge detect)
- Arduino-compatible board

## Pin map
### Motor driver (MDD3A)
- `M1_PWM` -> D5
- `M1_DIR` -> D4
- `M2_PWM` -> D6
- `M2_DIR` -> D7

### Ultrasonic sensors
- Left: `TRIG_L` D8, `ECHO_L` D9
- Right: `TRIG_R` D10, `ECHO_R` D11

### Line sensor
- `LINE` -> A0 (or digital out pin from module, depending how wired)

## Behavior
1. **Edge safety first**
   - If line sensor sees edge, bot backs up then turns.
2. **Opponent detect + attack**
   - Uses both ultrasonics.
   - If both see target: drive forward.
   - If only left sees target: pivot left.
   - If only right sees target: pivot right.
3. **Search mode**
   - If no target, spin right to hunt.

## Tunables in code
- `SPEED`
- `TURN_SPEED`
- `DETECT_CM`
- `LINE_DIGITAL`
- `LINE_THRESHOLD` (only for analog mode)

## Notes before match day
- There's a built-in `delay(5000)` start delay for comp rules.
- If edge detect feels inverted, flip the `HIGH/LOW` check in `onEdge()`.
- You will probably want to tune delay timings in `backThenTurn()` for your chassis.

## Upload
1. Open `sumo_bot.ino` in Arduino IDE.
2. Select your board + port.
3. Upload.
4. Test with wheels off ground first (seriously).
