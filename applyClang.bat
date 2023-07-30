cd src
for /r %%t in (*.cpp *.h *.c *.hpp) do clang-format -i "%%t"
cd ..