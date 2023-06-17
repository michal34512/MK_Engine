PowerShell -NoProfile -ExecutionPolicy Bypass -Command "(gci -include *.cpp,*.h -recurse | select-string .).Count"
pause