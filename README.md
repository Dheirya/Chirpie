# Chirpie
A Tamagotchi-style virtual companion that encourages healthy habits.

## Overview
**Chirpie** is a small virtual pet bird designed to motivate positive habits. Similar to a Tamagotchi, Chirpie has happiness and health meters that decrease over time. To keep Chirpie healthy and happy, users must complete real-life tasks such as cleaning, practicing mindfulness, or studying. Completing habits earns coins, which can be used to interact with Chirpie, including feeding, playing, and even dispensing M&Ms as rewards.

## Features
- **Virtual Companion**: Tracks happiness and health in real-time.
- **Habit Tracking**: Earn coins by completing personal or predefined healthy habits.
- **Interactive Gameplay**: Use coins to feed and play with Chirpie.
- **Study and Focus Mode**: Earn coins based on focused time or study sessions.
- **M&M Dispenser**: Reinforce positive behavior with a physical reward.
- **Customizable**: Habits and interactions can be personalized through the code.

## Hardware
Chirpie is built using:
- Arduino Uno microcontroller
- 2.8" TFT touchscreen
- 3D printed design in [CAD](https://cad.onshape.com/documents/94edd148011d3fedb0c75dae/w/326ec27714b0a8ae1ea4fcca/e/cfe7abb62cdbd7dbb95e723f)

## Software
The software is written in **C** and **C++** and runs on the Arduino platform. Core components include:
- `CHIRPIE.ino`: Main Arduino sketch
- `constants.h`: Configuration values
- `graphics.h`: Graphics for the TFT display

## License
This project is licensed under the MIT License. See [LICENSE](https://raw.githubusercontent.com/Dheirya/Chirpie/refs/heads/main/LICENSE) for details.
