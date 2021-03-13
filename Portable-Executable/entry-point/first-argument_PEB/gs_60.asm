_TEXT  SEGMENT

PUBLIC get_gs_60

get_gs_60 PROC

    mov rax, qword ptr gs:[60h]
    ret

get_gs_60 ENDP

_TEXT  ENDS
END
