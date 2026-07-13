# DirView

[![MIT License](https://img.shields.io/github/license/N3WC0DER/dirview)](LICENSE)
[![Latest Release](https://img.shields.io/github/v/release/N3WC0DER/dirview)](https://github.com/N3WC0DER/dirview/releases)
[![Build Status](https://img.shields.io/github/actions/workflow/status/N3WC0DER/dirview/ci.yml)](https://github.com)
[![Issues Open](https://img.shields.io/github/issues/N3WC0DER/dirview)](https://github.com/N3WC0DER/dirview/issues)
![Stars](https://img.shields.io/github/stars/N3WC0DER/dirview)

DirView — это легковесная графическая утилита для Linux, предназначенная для быстрого и удобного отображения структуры директорий в виде дерева с возможностью фильтрации.

[**FOR ASTRA**](ASTRA.md)

## Особенности

* Быстрый рендеринг: Высокая скорость работы даже на больших структурах данных.
* Удобная фильтрация: Исключение файлов и папок.
* Можно рассчитать размер папки.

## Требования
Для сборки и запуска утилиты вам понадобятся:

* GCC или Clang с поддержкой стандарта C++17
* CMake 3.15+
* Qt 5.15+

## Установка
.deb пакеты доступны в разделе Releases.

### Сборка из исходников

```bash
git clone https://github.com/N3WC0DER/dirview.git
cd dirview
cmake --build build --config Release
sudo cmake --install build --config Release
```

## Лицензия

Этот проект распространяется под лицензией MIT. Подробности можно найти в файле LICENSE.

Если вы хотите развить проект, пожалуйста, напишите мне в Issues или создайте Pull Request. Буду рад любой помощи в улучшении функционала!

