copy "..\src\main\cpp\VirtualDeviceWrapper.h" "..\build\VirtualDeviceWrapper.h"
copy "..\src\main\cpp\VirtualDeviceWrapper.cpp" "..\build\VirtualDeviceWrapper.cpp"
copy "..\src\main\cpp\SimulatorFMRxTx.h" "..\build\SimulatorFMRxTx.h"
copy "..\src\main\cpp\SimulatorFMRxTx.cpp" "..\build\SimulatorFMRxTx.cpp"
copy "..\src\main\cpp\SimulatorBluetoothRxTx.h" "..\build\SimulatorBluetoothRxTx.h"
copy "..\src\main\cpp\SimulatorBluetoothRxTx.cpp" "..\build\SimulatorBluetoothRxTx.cpp"
copy "..\src\main\cpp\ChirpFMRxTx.h" "..\build\ChirpFMRxTx.h"
copy "..\src\main\cpp\ChirpBluetoothRxTx.h" "..\build\ChirpBluetoothRxTx.h"
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cd ../build/
cl -I"C:\Program Files\Java\jdk1.8.0_211\include" -I"C:\Program Files\Java\jdk1.8.0_211\include\win32" -LD ./VirtualDeviceWrapper.cpp ./SimulatorFMRxTx.cpp ./SimulatorBluetoothRxTx.cpp -FeVirtualDeviceWrapper.dll
copy VirtualDeviceWrapper.dll ..\src\main\resources\VirtualDeviceWrapper.dll