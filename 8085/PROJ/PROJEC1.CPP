	mvi c,00
	mvi a,98
	mvi b,ab
	add b
	jm next
	inr c
next:   sta 0100
	mov a,c
end:    sta 0110
	jm tact        ;the comment
	mov a,b
tact:   mov c,d
	mvi a,30
next:   mvi b,20
	mov a,d
	jm tact
       jm next
    ori 5
   mvi d,20
end: lxi h,0034