EasyXInput
----------
This is a lightweight framework that has been designed to make working with XInput in C++ simpler, and, as a result, easier. While most people would not consider working with XInput to be difficult, it can easily get tedious and verbose. EasyXInput aims to remove all the boilerplate code required to use XInput-enabled devices.

How to Use
----------
Download the header files from the _release_ directory and include them in your project.  
Link to  ```XInput.lib``` as well as ```EasyXInput.lib```, also found in the _release_ directory.  
Then simply include ```<easyx/easy.hpp>``` to use the framework.

Example
----------
```cpp
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
