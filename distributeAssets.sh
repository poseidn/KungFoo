#!/bin/bash
rm -rf build/DescentGame/images 
rm -rf build/DescentGame/levels
rm -rf build/DescentGame/scripts 
rm -rf build/DescentGame/sounds
mkdir -p build/DescentGame/
cp -rv ingame_assets/* build/DescentGame/

#android is a bit more tricky
rm build_android/assets/images/*
rm build_android/assets/levels/*
rm build_android/assets/scripts/*
rm build_android/res/raw/*

mkdir -p build_android/assets/images/
mkdir -p build_android/assets/levels/
mkdir -p build_android/res/raw/
cp -rv ingame_assets/images/*.png build_android/assets/images/
cp -rv ingame_assets/levels/*.xml build_android/assets/levels/
#cp -rv ingame_assets/scripts/*.lua build_android/assets/scripts/
cp -rv ingame_assets/sounds/*.ogg build_android/res/raw/

#downscale android
# don't do this, looks ugly on Nexus 4
#mogrify -resize 50% build_android/assets/images/*.png

