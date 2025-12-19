# conf_lib

Простая библиотека на C++ для чтения INI-файлов.

## Использование
Просто берете `conf_lib.hpp` и переносите в проект

```cpp
#include "conf_lib.hpp"

conf_lib::CONFIG cfg;
cfg.open("config.ini");

auto section = cfg["section_name"];
std::string val = std::get<std::string>(section["key"]);
```

Поддерживаемый формат:

```
[section]
key = value
; комментарий
```

## Лицензия
GNU GPL