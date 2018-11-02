# EasyXInput
...

# How to Use
...

# Example
```cpp
#include "easyx/easyx.hpp"

#include <iostream>

int main() {
  easyx::prepare();

  for (;;) {
    easyx::update();

    if (easyx::button(easyx::PLAYER_1, easyx::A) & easyx::DOWN) {
      printf("'A' pressed.\n");
    } else if (easyx::button(easyx::PLAYER_1, easyx::A) & easyx::RELEASED) {
      printf("'A' released.\n");
    }
  }
}
```
