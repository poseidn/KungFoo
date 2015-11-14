=====================
  KungFoo Barracuda
===================== 

Android & Desktop arcade game for the masses !

[![Build Status](https://travis-ci.org/poseidn/KungFoo.svg?branch=master)](https://travis-ci.org/poseidn/KungFoo)

https://travis-ci.org/poseidn/KungFoo


== Build & Run on Linux =

```
./distributeAssets.sh
cd build
cmake ../src/
make -j4
cd DescentGame
./DescentGame
```

== Android compile ==

```
./distributeAssets.sh
cd build_android/
./get_externals.sh
android update project --path  .
ant release
```

