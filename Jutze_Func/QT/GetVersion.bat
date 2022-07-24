FOR /F "tokens=*" %%x IN ('git describe --tag') DO (SET VAR=%%x)
echo #define BUILD_VERSION "%VAR%" > .\version.data
echo #define APP_VERSION %VAR% >> .\version.data
comp .\version.data .\version.h /M
IF NOT 0 EQU %ERRORLEVEL% COPY .\version.data version.h