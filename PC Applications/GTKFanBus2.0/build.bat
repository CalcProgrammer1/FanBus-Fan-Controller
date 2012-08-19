pkg-config gtkmm-2.4 --cflags --libs > C:\pkg-config-temp.txt
set /p PKG_CONFIG_OUTPUT= < C:\pkg-config-temp.txt

i686-w64-mingw32-g++ *.cpp -o gtkfanbus-2.0 %PKG_CONFIG_OUTPUT%