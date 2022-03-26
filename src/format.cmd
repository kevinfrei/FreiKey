for /F "usebackq" %%D in (`git ls-files *.cpp *.ino *.h ^| findstr /vc:"libs/"`) do clang-format -i %%~D
