;; Power Program
;; C = A^B
;; R0 = A, R1 = B, R7 = C

			.CODE
			.ADDR 0x0000

			CONST R7, #1	; Set C to 1


LOOP		CMPI R1, #0	; Compare B to 0
			BRnz END        ; if (B<=0) Branch to END

			MOD R7, R7, R0	; C = C*A
			ADD R1, R1, #-1	; B = B-1

			BRnzp LOOP	; Go back to beginning of loop

END			NOP
