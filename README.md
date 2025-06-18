# 🧼 Arduino Hand Wash Timer

An Arduino-based hygiene reminder system that encourages proper 30-second hand washing with interactive feedback. Triggered by an IR sensor, it guides users through the process using a countdown timer, LCD messages, LEDs, buzzer tones, and a musical reward at the end.


## 🚀 Features

- 🖐️ IR Sensor Activation
  – Starts the countdown when motion is detected  
- ⏲️ 30-Second Timer
  – Displays real-time countdown on a 16x2 LCD  
- 💡 LED Progress Cues
  – Red, yellow, green, and blue LEDs mark milestones (20s, 15s, 5s)  
- 🔊 Auditory Feedback
  – Buzzer beeps at every second and plays a victory melody upon completion  
- 📟 Dynamic LCD Messages
  – Shows encouragement like "Almost There!" or "Getting Closer!" based on remaining time  
- ♻️ Auto Reset
  – Restarts system after finishing a cycle for repeated use


## 🛠 Technologies & Components Used

- Arduino Uno
- C++  
- IR Proximity Sensor  
- 16x2 LCD (I2C)  
- Red, Yellow, Green, Blue LEDs  
- Buzzer  
- Breadboard, jumper wires, resistors
