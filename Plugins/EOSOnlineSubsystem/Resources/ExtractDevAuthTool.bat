@echo off
echo Extracting Developer Authentication Tool from the SDK...
echo Located in: %*
cd /D %*
powershell -ExecutionPolicy Bypass -File "%~dp0\ExtractDevAuthTool.ps1"