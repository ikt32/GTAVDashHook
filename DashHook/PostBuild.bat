if not exist ..\pkg\NUL mkdir ..\pkg
copy %1.h ..\pkg /Y
copy bin\%1.dll ..\pkg /Y
copy bin\%1.lib ..\pkg /Y
