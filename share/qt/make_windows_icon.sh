#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/Blank.ico

convert ../../src/qt/res/icons/Blank-16.png ../../src/qt/res/icons/Blank-32.png ../../src/qt/res/icons/Blank-48.png ${ICON_DST}
