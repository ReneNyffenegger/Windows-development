all: unicode.exe ansi.exe

unicode.exe: unicode.obj
	@link /nologo unicode.obj user32.lib /OUT:unicode.exe

ansi.exe: ansi.obj
	@link /nologo ansi.obj    user32.lib /OUT:ansi.exe 

unicode.obj: prog.c Makefile
	@cl /nologo /W3 /DUNICODE /D_UNICODE /c prog.c /Founicode.obj

ansi.obj: prog.c Makefile
	@cl /nologo /W3                      /c prog.c /Foansi.obj

clean:
	@del *exe *.obj
