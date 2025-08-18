setlocal enabledelayedexpansion
set "sources="

for /r %%i in (*.c) do (
   set "sources=!sources! "%%i""
)

gcc -g %sources% -o cbuilder.exe