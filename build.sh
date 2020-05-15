# g++ -o a2 debug_*.cpp dbg.cpp -g -Wno-write-strings
rm imgui.ini
# g++ -o test test3_2.cpp test3.cpp -g
# g++ -o test1 test.cpp -g
# g++ -o test2 test2.cpp -g
g++ -o a src/gl/gl.cpp src/imgui/imgui*.cpp src/signal*.cpp src/process*.cpp src/debug*.cpp src/app.cpp -Isrc/gl -Isrc/imgui -lSDL2main -lSDL2 -lX11 -lGLU -lGL -lXext -DIMGUI_IMPL_OPENGL_LOADER_CUSTOM="\"gl.h\"" -g -Wno-write-strings -Wno-format
