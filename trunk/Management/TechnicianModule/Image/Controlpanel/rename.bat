@echo off
setlocal EnableDelayedExpansion
set a=1
for /f "delims=" %%a in ('dir /W /B *.png') do (
  for /f "delims=_ tokens=1,2*" %%i in ("%%a") do (
    if not "%%j"=="" (
        echo "[%%a] => [%%j]"
        rename %%a %%j
    )
  )
)
echo ÖØÃüÃûÍê±Ï
echo. & pause