:: MAIN WRAPPER FILES
copy "..\src\main\cpp\VirtualDeviceWrapper.h" "..\build\VirtualDeviceWrapper.h"
copy "..\src\main\cpp\VirtualDeviceWrapper.cpp" "..\build\VirtualDeviceWrapper.cpp"

:: RF RxTx FILES
copy "..\src\main\cpp\ChirpFMRxTx.h" "..\build\ChirpFMRxTx.h"
copy "..\src\main\cpp\ChirpFMRxTx.cpp" "..\build\ChirpFMRxTx.cpp"
copy "..\src\main\cpp\SimulatorFMRxTx.h" "..\build\SimulatorFMRxTx.h"
copy "..\src\main\cpp\SimulatorFMRxTx.cpp" "..\build\SimulatorFMRxTx.cpp"

:: BLE RxTx FILES
copy "..\src\main\cpp\ChirpBluetoothRxTx.h" "..\build\ChirpBluetoothRxTx.h"
copy "..\src\main\cpp\ChirpBluetoothRxTx.cpp" "..\build\ChirpBluetoothRxTx.cpp"
copy "..\src\main\cpp\SimulatorBluetoothRxTx.h" "..\build\SimulatorBluetoothRxTx.h"
copy "..\src\main\cpp\SimulatorBluetoothRxTx.cpp" "..\build\SimulatorBluetoothRxTx.cpp"

:: ROUTING FILES
copy "..\src\main\cpp\ChirpRouting.h" "..\build\ChirpRouting.h"
copy "..\src\main\cpp\ChirpRouting.cpp" "..\build\ChirpRouting.cpp"

:: BLUETOOTH PACKET FILES
copy "..\src\main\cpp\ChirpBluetoothPacket.h" "..\build\ChirpBluetoothPacket.h"
copy "..\src\main\cpp\ChirpBluetoothPacket.cpp" "..\build\ChirpBluetoothPacket.cpp"

:: RADIO PACKET FILES
copy "..\src\main\cpp\ChirpRadioPacket.h" "..\build\ChirpRadioPacket.h"
copy "..\src\main\cpp\ChirpRadioPacket.cpp" "..\build\ChirpRadioPacket.cpp"

:: UTIL FILES
copy "..\src\main\cpp\utils.h" "..\build\utils.h"
copy "..\src\main\cpp\utils.cpp" "..\build\utils.cpp"

:: OPEN AND RUN VS COMPILER
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cd ../build/
cl -I"C:\Program Files\Java\jdk1.8.0_211\include" -I"C:\Program Files\Java\jdk1.8.0_211\include\win32" -LD ./VirtualDeviceWrapper.cpp ./ChirpFMRxTx.cpp ./SimulatorFMRxTx.cpp ./ChirpBluetoothRxTx.cpp ./SimulatorBluetoothRxTx.cpp ./ChirpRadioPacket.cpp ./ChirpBluetoothPacket.cpp ./ChirpRouting.cpp ./utils.cpp  -FeVirtualDeviceWrapper.dll

:: COPY OUT DLL TO RESOURCE DIR
copy VirtualDeviceWrapper.dll ..\src\main\resources\VirtualDeviceWrapper.dll