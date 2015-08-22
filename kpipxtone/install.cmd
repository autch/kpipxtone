set DEST="c:\usr\local\kbmedia player\plugins\autch\kpipxtone"
if not exist %DEST% mkdir %DEST%
copy ..\%1\kpipxtone.kpi %DEST% /y
copy pxtone_include\pxtoneWin32.dll %DEST% /y
copy ..\kpipxtone.txt %DEST% /y
if exist ..\%1\*.pdb copy ..\%1\*.pdb %DEST% /y
