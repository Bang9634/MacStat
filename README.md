# Mac Stat Monitor

macOS 시스템 모니터링 애플리케이션입니다. CPU 온도, 메모리 사용량 등의 시스템 정보를 실시간으로 표시합니다.

## 빌드 요구사항

- CMake 3.16 이상
- Qt 6
- C++17 호환 컴파일러
- macOS

## 빌드 방법

```bashc
mkdir build
cd build
cmake ..
make
```

## 실행 방법

빌드 디렉토리에서:
```bash
./mac_stat
``` 