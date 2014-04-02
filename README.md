EasyXInput
----------
This is a lightweight framework that has been designed to make working with XInput in C++ simpler, and, as a result, easier. While most people would not consider working with XInput to be difficult, it can easily get tedious and verbose. EasyXInput aims to remove all the boilerplate code required to use XInput-enabled devices.

How to Use
----------
Using EasyXInput only requires including the _\<easyx/easyx.hpp\>_ header file and linking the XInput library. The _\<xinput.h\>_ header only needs to be included if the preprocessor definitions of the button names are to be used. EasyXInput defines its own names for all buttons, but these are simply shortcuts that give the exact same values as the ones defined in _\<xinput.h\>_ are verbose. In other words the EASYX_A definition, for example, will give XINPUT_GAMEPAD_A. All of the EasyXInput preprocessor definitions can be found in the _\<easyx/easyx.hpp\>_ header.

Example
----------
```cpp
#include <stdio.h>
#include <easyx\easyx.hpp>

int main() {
    easyx::Event event;
    
    while (true) {
        easyx::update();
        while (easyx::poll(&event)) {
            switch (event.type) {
            case EASYX_EVENT_CONNECT:
                printf("Gamepad #%d Detected\n", event.gamepad);
                break;
            case EASYX_EVENT_DISCONNECT:
                printf("Gamepad #%d Lost\n", event.gamepad);
                break;
            }
        }
    }
}
```

Documentation
----------
Full documentation on how to use the framework can be found on [the wiki](https://github.com/TylerOBrien/EasyXInput/wiki).
