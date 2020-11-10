@mkdir build
@pushd build

cmake ..
cmake --build . --config Release

@popd