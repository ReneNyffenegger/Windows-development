cl   /nologo /GS- /c entry-point.c
ml64 /nologo      /c gs_60.asm

link /nologo /entry:entryPoint /nodefaultlib /subsystem:console /machine:x64 entry-point.obj gs_60.obj kernel32.lib user32.lib /out:entry-point.exe
