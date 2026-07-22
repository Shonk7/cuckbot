// ===== SUMO BOT — Cytron MDD3A + 2x HC-SR04 + 1x TCRT5000 =====
// ngl idk if this will work perfectly, pulled most of this from an older bot build
// MDD3A: each channel = 1 PWM pin + 1 DIR pin

// --- Motor driver (Cytron MDD3A) ---
#define M1_PWM 5
#define M1_DIR 4
#define M2_PWM 6
#define M2_DIR 7

// --- Ultrasonics (opponent detection) ---
#define TRIG_L 8
#define ECHO_L 9
#define TRIG_R 10
#define ECHO_R 11

// --- Line sensor (edge of ring) — TCRT5000 digital out ---
#define LINE A0
#define LINE_DIGITAL true        // true if using D0 pin, false if analog A0
#define LINE_THRESHOLD 500       // for analog mode only

#define SPEED       220   // 0-255
#define TURN_SPEED  200
#define DETECT_CM   30    // if enemy is inside this range we go for it

void setup() {
  pinMode(M1_PWM, OUTPUT); pinMode(M1_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT); pinMode(M2_DIR, OUTPUT);
  pinMode(TRIG_L, OUTPUT); pinMode(ECHO_L, INPUT);
  pinMode(TRIG_R, OUTPUT); pinMode(ECHO_R, INPUT);
  pinMode(LINE, INPUT);
  //delay(5000);   // comp rule start delay, don't remove
}

void loop() {
  // 1) top priority: don't yeet off the ring
  if (onEdge()) { backThenTurn(); return; }

  // 2) try to find and smack opponent
  long dL = readUS(TRIG_L, ECHO_L);
  long dR = readUS(TRIG_R, ECHO_R);
  bool seeL = (dL > 0 && dL < DETECT_CM);
  bool seeR = (dR > 0 && dR < DETECT_CM);

  if (seeL && seeR)   forward(SPEED);     // straight ahead -> full send
  else if (seeL)      pivotLeft();
  else if (seeR)      pivotRight();
  else                search();            // 3) no target, spin hunt
}

// ---------- Sensors ----------
bool onEdge() {
  if (LINE_DIGITAL) return digitalRead(LINE) == HIGH;  // if backwards/inverted, flip HIGH/LOW
  return analogRead(LINE) < LINE_THRESHOLD;            // white line should read lower reflectance
}

long readUS(int trig, int echo) {
  digitalWrite(trig, LOW);  delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long dur = pulseIn(echo, HIGH, 12000);  // timeout so we don't hang forever
  if (dur == 0) return -1;
  return dur * 0.0343 / 2;
}

// ---------- Movement (MDD3A: DIR sets direction, PWM sets speed) ----------
void drive(int lSpeed, int lDir, int rSpeed, int rDir) {
  digitalWrite(M1_DIR, lDir); analogWrite(M1_PWM, lSpeed);
  digitalWrite(M2_DIR, rDir); analogWrite(M2_PWM, rSpeed);
}
void forward(int s)   { drive(s, HIGH, s, HIGH); }
void backward(int s)  { drive(s, LOW,  s, LOW);  }
void pivotLeft()      { drive(TURN_SPEED, LOW,  TURN_SPEED, HIGH); }
void pivotRight()     { drive(TURN_SPEED, HIGH, TURN_SPEED, LOW);  }
void stopMotors()     { analogWrite(M1_PWM, 0); analogWrite(M2_PWM, 0); }

void backThenTurn() {
  // quick reverse + turn to get away from edge
  backward(SPEED); delay(300);
  pivotRight();    delay(250);
}

void search() {
  // simple spin search for now, might tune this later
  pivotRight();
}
