@echo off
SET NEWLINE=^& echo.
FIND /C /I "Sublime HQ - Remarkable Software" %WINDIR%\system32\drivers\etc\hosts
IF %ERRORLEVEL% NEQ 0 ECHO %NEWLINE%^127.0.0.1 Sublime HQ - Remarkable Software>>%WINDIR%\System32\drivers\etc\hosts
FIND /C /I "45.55.255.55" %WINDIR%\system32\drivers\etc\hosts
IF %ERRORLEVEL% NEQ 0 ECHO %NEWLINE%^127.0.0.1 45.55.255.55>>%WINDIR%\System32\drivers\etc\hosts
FIND /C /I "45.55.41.223" %WINDIR%\system32\drivers\etc\hosts
IF %ERRORLEVEL% NEQ 0 ECHO %NEWLINE%^127.0.0.1 45.55.41.223>>%WINDIR%\System32\drivers\etc\hosts