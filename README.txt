Pour pouvoir apporter des modifications au code il faut
- aller dans le logiciel de programmation Arduino
- Cliquer sur file puis preferences ensuite additional boards manager URLs 
et rentrer le lien suivant dans la boite de dialogue qui s'est ouverte :

https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json

- Ensuite ajouter à l'aide du library manager à gauche de l'écran les libraires

esp32_bluepad32, PS4_Controller et ESP32Servo

- Ensuite s'assurer d'ouvrir le circuit et déconnecter la batterie

- Brancher la puce ESP32 à l'ordinateur à l'aide d'un cable USB2.0
(il est important de s'assurer que le cable en question puisse transmettre des données et non pas que de la batterie
sans quoi le code ne s'ajoutera pas a la puce)

- Sélectionner comme board (en haut de l'écran) ESP32-WROOM-DA Module

- Envoyer le code
