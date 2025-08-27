@echo off
setlocal

:: Carpetas
set SRC_DIR=src
set BUILD_DIR=build
set INCLUDE_PROJECT=include
set RAYLIB_INCLUDE=include
set RAYLIB_LIB=lib

:: Crear carpeta build si no existe
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

:: -----------------------------
:: Compilar tu proyecto usando raylib.a
:: -----------------------------
g++ -std=c++17 -O2 ^
    -I"%INCLUDE_PROJECT%" ^
    -I"%RAYLIB_INCLUDE%" ^
    %SRC_DIR%\*.cpp ^
    "%RAYLIB_LIB%\libraylib.a" ^
    -lopengl32 -lgdi32 -lwinmm -luser32 -lkernel32 -lm ^
    -o %BUILD_DIR%\MiJuego.exe

if %ERRORLEVEL% equ 0 (
    echo Compilacion exitosa. Ejecutable en %BUILD_DIR%\MiJuego.exe
) else (
    echo Hubo errores en la compilacion.
)

pause
