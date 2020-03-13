echo off
cls

:inicio
	color 06
	echo.Compiling files...
	gcc mainTeste.c EstruturaVetores.c -o programa
	rem gcc main.c EstruturaVetores.c -o programa

	pause
	
	IF NOT %ERRORLEVEL%==0 (
		GOTO Done
	)

	echo.Running program...
	Start "-" "programa.exe"

:Done
