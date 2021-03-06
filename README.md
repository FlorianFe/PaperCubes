
<p align="center">
  <img alt="Icon" src="https://florianfe.github.io/screenshots/PaperCubes/icon.png">
  <h1 align="center">🏡🖨 PaperCubes</h1>
  <p align="center">
A desktop app which converts your minecraft <a href="https://madelinemiller.dev/blog/use-schematics-worldedit/">.schematic</a> files <br>you got from <a href="https://github.com/EngineHub/WorldEdit">worldedit</a> to blueprints for papercraft. <br><br>
  <a href="http://forthebadge.com"><img alt="forthebadge" src="http://forthebadge.com/images/badges/built-with-love.svg"></a>
  <a href="http://forthebadge.com"><img alt="forthebadge" src="http://forthebadge.com/images/badges/uses-js.svg"></a>
  <a href="http://forthebadge.com"><img alt="forthebadge" src="http://forthebadge.com/images/badges/made-with-c-plus-plus.svg"></a>
  </p>
</p>


<br>

## 🚀 How to use?
1. 🏡 You need an installed Minecraft Version
2. 🏗 You need to install the Minecraft mod Worldedit
3. 🔨 Start Minecraft and build something amazing 
4. 💾 *//Copy* what you built and *//schematic save* it
5. 🌴 Download a Texturepack
6. 💿 Start this desktop app
7. 🏝 Drop schematic file and texturepack in it
8. 🌟 Let the Program do its magic
9. 🖨 Print out the blueprints
10. 🏘 Make amazing minecraft builds in real!

## ⚠️ Important

- PaperCubes is still in BETA. Errors may occur. When you found one, please open an issue for me
- Currently works only for schematic files which are taken from minecraft versions smaller than v1.13.0. Versions that are very old won't work eighter. The version of the texturepack should match the minecraft version of the schematic file for best results
- Loading times can be very long depending on the size of the schematic

## 📝 Source Code
In order to use this source code you need to have Node.js, Git and Bower installed globally. After that you have to follow the steps below. 

<b>Only for Windows (as admin)</b>
```bash
npm install --global --production windows-build-tools
npm config set msvs_version 2015 --global
```

<b>For all platforms</b>
```bash
# Clone this repository
git clone https://github.com/florianfe/PaperCubes
# Go into the repository
cd PaperCubes
# Install npm dependencies
npm install
# Install bower dependencies
bower install
# Compile C++ sources
npm run-script compile
# Run the app in test mode
npm start
# build application for release
[sudo] npm run-script dist
```

## 🖼 Preview

![screenshot 1](https://florianfe.github.io/screenshots/PaperCubes/screenshot%201.png)
![screenshot 2](https://florianfe.github.io/screenshots/PaperCubes/screenshot%202.png)
![screenshot 3](https://florianfe.github.io/screenshots/PaperCubes/screenshot%203.png)
![screenshot 4](https://florianfe.github.io/screenshots/PaperCubes/screenshot%204.png)
![screenshot 5](https://florianfe.github.io/screenshots/PaperCubes/screenshot%206.png)

## 💾 Download

<table align="center">
  <tr>
    <th>Platform</th>
    <th>Version</th>
    <th>Download</td>
  </tr>
  <tr>
    <td>Mac</td>
    <td>1.3.0 BETA</td>
    <td><a href="https://github.com/FlorianFe/PaperCubes/releases/download/v1.3.0-beta/PaperCubes.dmg">Download</a></td>
  </tr>
  <tr>
    <td>Windows</td>
    <td>1.3.0 BETA</td>
    <td><a href="https://github.com/FlorianFe/PaperCubes/releases/download/v1.3.0-beta/PaperCubes.exe">Download</a></td>
  </tr>
  <tr>
    <td>Linux (.deb)</td>
    <td>1.3.0 BETA</td>
    <td><a href="https://github.com/FlorianFe/PaperCubes/releases/download/v1.3.0-beta/PaperCubes_amd64.deb">Download</a></td>
  </tr>
</table>

## 🗒 Note
- This Project was inspired by [Orthogami](https://github.com/mikolalysenko/orthogami) (made by mikolalysenko).
- The Texture Pack <i>Pixel Perfection</i> ([Link](http://www.minecraftforum.net/forums/mapping-and-modding-java-edition/resource-packs/1242533-pixel-perfection-now-with-polar-bears-1-11)) which is used for the Screenshots was made by <i>Hugh "XSSheep" Rutland</i>.

## 📖 License
[![forthebadge](http://forthebadge.com/images/badges/cc-nc.svg)](https://creativecommons.org/licenses/by-nc/3.0/)
