for /F "usebackq" %%D in (`git ls-files *.cpp *.ino *.h ^| findstr /vc:"libs/" ^| findstr /vc:"oldstuff"`) do clang-format -i %%~D
