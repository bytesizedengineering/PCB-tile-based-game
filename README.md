# PCB Tile Based Board Game 

![Project Image](assets/project-image.png)  
*Whoever completes the longest path wins! But beware of collisions!*  

## 🚀 Overview  
When Zach is not knee-deep in circuits and code, you can probably find him around a table covered in board games. For a long time now, a little project has been brewing in the back of his mind, designing a board game from the ground up, but not just any board game. Zach wants to create a tile-based game where the tiles electronically interact with each other the moment they snap together. It was featured on the Digkey [YouTube channel](https://www.youtube.com/@digikey) in [this video](#).  

## 📂 Repository Structure  
```
📁 mechanical_design/   # 3D models (Fusion 360, STLs, STEP files)
📁 electrical_design/   # KiCad PCB and schematic files
📁 firmware/            # Arduino, ESP, or other firmware code
📁 docs/                # PDFs, images, and additional documentation
```

## 🔩 Mechanical Design  
You can access the latest Fusion 360 model here:  
[🔗 View 3D Model in Fusion 360](https://a360.co/4kI0F6f)

## 🏗️ Build Instructions  

### 🖨️ 3D Printing  
- **Recommended Material**: PLA/PETG  
- **Layer Height**: 0.2mm  
- **Supports**: No  

### 🔌 Electronics  
- **Microcontroller**: ATTiny3217  
- **Power Supply**: 5V  
- **PCB Fabrication**: Gerber files included in `electrical_design/` 

### 💾 Firmware Upload  
You can upload code to the ATtiny3217 using the [Adafruit UPDI Friend](https://learn.adafruit.com/adafruit-updi-friend). Here's a quick setup guide for the Arduino IDE:

🧰 What You Need
- Adafruit UPDI Friend
- Arduino IDE
- ATtiny3217 board
- USB-C cable
1. Install MegaTinyCore
2. Select the Board
3. Connect the UPDI Friend
4. Select the Serial Port
5. Upload Code

## 🛒 Bill of Materials (BOM)  
| Part            | Description                                 | Purchase Link                                     |
| --------------- | ------------------------------------------- | ------------------------------------------------- |
| Microcontroller | ATtiny3217                                  | [DigiKey](https://www.digikey.com/short/wtvwb0pv) |
| Connector       | Magnetic Connector Pair                     | [DigiKey](https://www.digikey.com/short/tv5t94mz) |
| Capacitor       | 0.1 µF Ceramic Capacitor                    |                                                   |
| LED             | Addressable Reverse-Mount RGB LED           | [DigiKey](https://www.digikey.com/short/zhvb3bff) |
| PCB             | Custom-designed                             |                                                   |


## 🎥 Video & More Info  
📺 Watch the full build video: [YouTube Video](#)  

## 📝 License  
This project is licensed under the **GNU General Public License v3.0**.  
You can read the full text in the [`LICENSE`](LICENSE) file or at [gnu.org](https://www.gnu.org/licenses/gpl-3.0.html).  

## ❤️ Support  
- Found this helpful? Consider supporting me on [Patreon](https://www.patreon.com/ByteSizedEngineering) or [YouTube Memberships](https://www.youtube.com/@ByteSizedEngineering/join).  
- Follow me on [YouTube](https://www.youtube.com/@ByteSizedEngineering), [Instagram](https://www.instagram.com/bytesizedengineering/), and [GitHub](https://github.com/bytesizedengineering). 

