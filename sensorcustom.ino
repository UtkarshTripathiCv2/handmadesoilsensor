// --- PIN DEFINITIONS ---
// SYSTEM 1: The Rover Wheels
const int wheelPower = 5;    
const int wheelRead  = A0;   

// SYSTEM 2: The HW-080 Probe (Direct Connect)
const int probePower = 7;    
const int probeRead  = A1;   

// --- CALIBRATION (Adjusted for 1k Resistor) ---
// Since both use 1k resistors, their values will be similar (Low)
// 0 = Dry Air
// ~150 = Water (Adjust this based on your tes MNting!)
const int dryVal = 0;   
const int wetVal = 170; 

void setup() {
  Serial.begin(9600);
  
  pinMode(wheelPower, OUTPUT);
  pinMode(wheelRead, INPUT);
  
  pinMode(probePower, OUTPUT); 
  Serial.println("--- DUAL SENSOR TEST: Wheels vs Probe ---");
  delay(1000);
}

void loop() {
  // --- READ WHEELS ---
  digitalWrite(wheelPower, HIGH);
  delay(10);
  int wheelRaw = analogRead(wheelRead);
  digitalWrite(wheelPower, LOW);
  
  // --- READ PROBE ---
  digitalWrite(probePower, HIGH);
  delay(10);
  int probeRaw = analogRead(probeRead);
  digitalWrite(probePower, LOW);
  
  // --- CONVERT TO % ---
  int wheelPct = map(wheelRaw, dryVal, wetVal, 0, 100);
  int probePct = map(probeRaw, dryVal, wetVal, 0, 100);
  
  // Clamp values (0-100)
  wheelPct = constrain(wheelPct, 0, 100);
  probePct = constrain(probePct, 0, 100);
  
  // --- DISPLAY ---
  Serial.print("Hand Made Soil Moisture Sensor : ");
  Serial.print(wheelRaw);
  Serial.print(" (");
  Serial.print(wheelPct);
  Serial.print("%)");
  
  Serial.print("   ||   Soil Moisture Sensor: ");
  Serial.print(probeRaw);
  Serial.print(" (");
  Serial.print(probePct);
  Serial.println("%)");
  
  delay(1000);
}
