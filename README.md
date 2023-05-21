# GameEngine-D7049E

A game engine made for the course D7049E

Game Idea: https://docs.google.com/presentation/d/1Z2hof-B_RoKc35boVmnQ2V3aLZmK3KcpWsClogI6ZcY/edit?usp=sharing

## Compilation
### Arch linux
```
pacman -S ogre
git clone https://github.com/fabdan-8/GameEngine-D7049E
cd GameEngine-D7049E
mkdir build && cd build && cmake .. && make
```
For now we only create a 0_main executable as a test, this is subject to change.
```
./0_main
```

### Windows
This is most likely a lot more complicated than it needs to be, but I (Erik) haven't found a better way yet.
1. [Download sdk](https://dl.cloudsmith.io/public/ogrecave/ogre/raw/versions/v13.6.4/ogre-sdk-v13.6.4-msvc141-x64.zip)
2. Extract sdk to the location of `C:\projects\ogre-bsrh7\build\sdk`. So below this folder should be: `bin`, `CMake`, `Docs` etc. (The location is **REQUIRED**, otherwise the plugins won't load, this might be fixable)
3. Add environment variables (preferrably system wide though I'm unsure if all of these are needed) 
   - `CMAKE_MODULE_PATH` to `C:\projects\ogre-bsrh7\build\sdk`
   - `CMAKE_PREFIX_PATH` to `C:\projects\ogre-bsrh7\build\sdk\CMake`
   - `OGRE_DIR` to `C:\projects\ogre-bsrh7\build\sdk`
4. Install Visual Studio and required packages (I don't know which ones they are, c++ ones at least)
5. Run developer console (press start and search `Developer Command Prompt for VS <version>`)
6. Clone repo `git clone https://github.com/fabdan-8/GameEngine-D7049E`
7. Building:
  ```
  mkdir build && cd build
  cmake -A x64 ..
  msbuild /P:Configuration=Release ALL_BUILD.vcxproj
  ```
  This should give a new Release folder which includes 0_main.exe
  
8. Now it should be possible to run 0_main.exe
