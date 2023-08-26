# Home Automation System

<p align="center">
  <img src="https://github.com/onkar69483/Home-Automation/assets/61963755/72ba3bcf-4b2f-4d3c-96f5-eaba40ae24f1">
</p>

## Introduction

The Home Automation System is designed to create a smart home environment by automating household tasks and enhancing security. This project utilizes microcontrollers, sensors, and cloud services to provide convenience, energy efficiency, and remote control capabilities.

## Features

- **Fire Sensor:** Detects fire occurrences and triggers alerts for safety.
- **Intruder Detection:** Notifies unauthorized access and prevents intrusions.
- **Convenience:** Automates electronic devices and appliances for enhanced comfort.
- **Remote Access:** Control and monitor devices remotely via Google Assistant or Alexa.
- **Energy Efficiency:** Optimizes energy consumption by intelligently managing device usage.

## Development Tools

- [sinric.pro](https://sinric.pro): IoT cloud platform.
- Microcontroller: ESP8266 for device control and communication.
- Sensors: Ultrasonic, infrared, and flame sensors.
- Actuators: Motors, LEDs, and buzzers.
- Virtual Assistants: Google Assistant and Alexa for voice control.

## System Requirements

- Microcontroller with C compiler.
- Network access for connecting devices.
- WiFi network for cloud services.
- Mobile device with Google Assistant or Alexa for remote voice control.

## Setup and Usage

1. Clone the repository to your local machine.
2. Modify configuration files with your device IDs and credentials.
3. Build the circuit based on the provided diagram.
4. Upload HomeAutomation.ino to the microcontroller.
5. Connect the microcontroller to your WiFi network.
6. Control lights and fans using voice commands via Google Assistant or Alexa.

## Uploading the Main Code (HomeAutomation.ino)

The `HomeAutomation.ino` file contains the main code for the project. This code needs to be uploaded to the NodeMCU ESP8266 board using the Arduino IDE or another compatible platform. Here are the steps:

1. Open the Arduino IDE.
2. Go to **File > Open** and navigate to the location where you cloned the repository.
3. Select the `HomeAutomation.ino` file and click **Open**.
4. Make sure you have the necessary board selected in **Tools > Board**. For NodeMCU ESP8266, select **NodeMCU 1.0 (ESP-12E Module)**.
5. Choose the appropriate port from **Tools > Port** (usually a COM port for Windows or /dev/ttyUSB for Linux).
6. Click the **Upload** button (right arrow icon) to compile and upload the code to the board.
7. Monitor the upload progress in the bottom console of the Arduino IDE.

## Editing the Circuit (SmartHomeIot.fzz)

The `SmartHomeIot.fzz` file is a Fritzing project file containing the circuit diagram. You can use Fritzing software to open and modify the circuit diagram according to your needs. Fritzing is an open-source tool for creating and sharing electronic designs.

1. Download and install [Fritzing](https://fritzing.org/download/).
2. Open Fritzing.
3. Go to **File > Open** and navigate to the location where you cloned the repository.
4. Select the `SmartHomeIot.fzz` file to open the circuit diagram.
5. Modify the circuit as desired using the Fritzing interface.
6. Save your modifications.

## Voice Commands

- **Google Assistant:** "Hey Google, turn on the lights."
- **Google Assistant:** "Hey Google, turn off the fan."
- **Alexa:** "Alexa, turn on the fan."

## Prototype Model

<p align="center">
  <img src="https://github.com/onkar69483/Home-Automation/assets/61963755/da23b82a-2be0-4974-8ac8-edda8be51d3e.jpg" alt="Prototype Model">
</p>

## Circuit Diagram

<p align="center">
  <img src="https://github.com/onkar69483/Home-Automation/assets/61963755/4c838521-95ef-452d-8c63-05b6e49f6554">
</p>

## Circuit on Breadboard

<p align="center">
  <img src="https://github.com/onkar69483/Home-Automation/assets/61963755/fb716918-5ad9-43fb-b8a8-9b5c5a482d2b.jpg" alt="Circuit on Breadboard">
</p>

## Future Scope

1. **Cost Efficiency:** Energy-efficient devices for longer lifespans and reduced bills.
2. **AI Integration:** Incorporating AI for enhanced customization and control.
3. **Smart Integrations:** Google Home integration for improved user experience.
4. **Real-time Updates:** Real-time data exchange for weather, traffic, and appliances.

## License

This project is licensed under the [MIT License](LICENSE).

- [HomeAutomation.ino](https://github.com/onkar69483/Home-Automation/blob/master/HomeAutomation.ino)
- [SmartHomeIot.fzz](https://github.com/onkar69483/Home-Automation/blob/master/SmartHomeIot.fzz)

---

Contributions are welcome! Feel free to open issues or submit pull requests. For questions, contact: onkar69483@gmail.com.
