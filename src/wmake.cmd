if "%1" EQU "rebuild" rd /s /q out
if "%1" EQU "clean" rd /s /q out
if "%1" NEQ "clean" make -j img