copy "..\src\main\cpp\VirtualDeviceWrapper.h" "..\build\VirtualDeviceWrapper.h"
copy "..\src\main\cpp\VirtualDeviceWrapper.cpp" "..\build\VirtualDeviceWrapper.cpp"
copy "..\src\main\cpp\SimulatorLib.h" "..\build\SimulatorLib.h"
copy "..\src\main\cpp\SimulatorLib.cpp" "..\build\SimulatorLib.cpp"
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cd ../build/
cl -I"C:\Program Files\Java\jdk1.8.0_211\include" -I"C:\Program Files\Java\jdk1.8.0_211\include\win32" -LD ./VirtualDeviceWrapper.cpp ./SimulatorLib.cpp -FeVirtualDeviceWrapper.dll
copy VirtualDeviceWrapper.dll ..\src\main\resources\VirtualDeviceWrapper.dll