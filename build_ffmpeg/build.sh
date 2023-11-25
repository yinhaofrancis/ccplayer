mkdir out
bash compile-ios.sh arm64
bash compile-ios.sh x86_64
bash lipo_lib.sh

