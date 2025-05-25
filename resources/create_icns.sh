#!/bin/bash

# iconset 디렉토리 생성
mkdir -p AppIcon.iconset

# SVG를 여러 크기로 변환
for size in 16 32 64 128 256 512 1024; do
    # 기본 크기
    sips -s format png -z $size $size resources/icon.svg --out AppIcon.iconset/icon_${size}x${size}.png

    # Retina 디스플레이용 2배 크기 (해당되는 경우)
    if [ $size -le 512 ]; then
        sips -s format png -z $((size*2)) $((size*2)) resources/icon.svg --out AppIcon.iconset/icon_${size}x${size}@2x.png
    fi
done

# iconset을 .icns 파일로 변환
iconutil -c icns AppIcon.iconset

# 임시 디렉토리 삭제
rm -rf AppIcon.iconset 