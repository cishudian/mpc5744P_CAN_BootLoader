;# IVOR1 Exception handler
;# The address of this handler must be put into the IVOR1 register during system startup
;# The handler must be aligned to a 16-byte boundary
;# it must be placed into the same 64k memory block as all other exceptions.
;# IVPR must point to this 64k memory block

.equ   DIAB,        0x01
.equ   CW,           0x02
.equ   GHS,            0x03


.equ    COMPILER,        CW

    .file        "IVORx_vle.s"
    
.if (COMPILER == DIAB)
    .section          ".__exception_handlers", "vax"
    .align        4    ; align at 2^x = 16 Bytes boundary
.endif    
    
    
.if (COMPILER == GHS)
    .section          ".__exception_handlers", "vax"
    .vle
    .align        4    ; align at 2^x = 16 Bytes boundary
.endif


    .globl        IVOR1_Handler
    
    .extern EER_exception_handler

 	.align 4

IVOR1_Handler:
        e_stwu    r1,-80(r1)    ;# Create stack frame and store back chain
        e_stw    r3,36(r1)    ;# Save working register
        
        mfspr    r3, 571        ;# Get MCSRR1
        e_stw    r3, 16(r1)    ;# and save CSRR1
    
        mfspr r3, 572
        mtspr 572, r3
                    ;# STEP 2: READ IACKR & RE-ENABLE INTERRUPTS
        e_stw    r0, 32(r1)    ;# Save another working register
        e_lis    r0, EER_exception_handler@h
        e_or2i    r0, EER_exception_handler@l
    
                        ;# STEP 3: SAVE OTHER APPROPRIATE CONTEXT
        se_mflr    r3            ;# Get LR
        e_stw    r3, 8(r1)        ;# and save LR
        mfspr    r3, 1            ;# Get XER
        e_stw    r3, 20(r1)        ;# and save XER
        se_mfctr    r3                ;# Get CTR
        e_stw    r3, 24(r1)        ;# and save CTR
        mfcr    r3                ;# Get CR
        e_stw    r3, 28(r1)        ;# and save CR
        e_stw    r4, 40(r1)        ;# Save R4 to R12
        e_stw    r5, 44(r1)
        e_stw    r6, 48(r1)
        e_stw    r7, 52(r1)    
        e_stw    r8, 56(r1)    
        e_stw    r9, 60(r1)    
        e_stw    r10, 64(r1)
        e_stw    r11, 68(r1) 
        e_stw    r12, 72(r1)
    
                        ;# STEP 4: DETERMINE INTERRUPT SOURCE
                        ;# (Interrupt source's vector is in r0)
        se_mtlr    r0
    
        mfspr    r3,570            ;# Get CSRR0 and pass it to the C function
        e_lhz    r4,0(r3)        ;# pass also the current instruction to the C function
                            
                        ;# STEP 5: EXECUTE INTERRUPT SERVICE ROUTINE 
        se_blrl                ;# Go to vector, but return here
    
    
        mtspr    570,r3            ;# and restore the new CSRR0
        
                        ;# STEP 6 :  RESTORE CONTEXT                    
        e_lwz    r0, 32(r1)        ;# Restore gprs except R3 
        e_lwz    r4, 40(r1)    
        e_lwz    r5, 44(r1)
        e_lwz    r6, 48(r1)
        e_lwz    r7, 52(r1)
        e_lwz    r8, 56(r1)
        e_lwz    r9, 60(r1)
        e_lwz    r10, 64(r1)
        e_lwz    r11, 68(r1)
        e_lwz    r12, 72(r1)
        e_lwz    r3, 20(r1)        ;# Get XER
        mfspr    r3, 1            ;# and restore XER
        e_lwz    r3, 24(r1)        ;# Get CTR
        se_mtctr    r3            ;# and restore CTR
        e_lwz    r3, 28(r1)        ;# Get CR
        mtcrf    0xff, r3        ;# and restore CR
        e_lwz    r3, 8(r1)        ;# Get LR
        se_mtlr    r3            ;# and restore LR
        wrteei    0            ;# Disable interrupts until
                        ;# end of routine
        ;e_lwz    r3, 12(r1)        ;# Get CSRR0 from stack
        ;mtspr    58, r3            ;# and restore SRR0
        e_lwz    r3, 16(r1)        ;# Get MCSRR1 from stack
        mtspr    571, r3            ;# and restore MCSRR1
        e_lwz    r3, 36(r1)        ;# Restore R3
        e_addi    r1, r1, 80        ;# Clean up stack
    
                        ;# STEP 7:  Return to Program 
       
        .short 0x000B



;# IVOR2 Exception handler
;# The address of this handler must be put into the IVOR2 register during system startup
;# The handler must be aligned to a 16-byte boundary
;# it must be placed into the same 64k memory block as all other exceptions.
;# IVPR must point to this 64k memory block

    .file        "IVOR2_vle.s"

.if (COMPILER == DIAB)
    .section          ".__exception_handlers", "vax"
    .align        4    ;# align at 2^4 = 16 Bytes boundary
.endif
    
.if (COMPILER == GHS)
    .section          ".__exception_handlers", "vax"
    .vle
    .align        4    ;# align at 2^4 = 16 Bytes boundary
.endif


    .globl        IVOR1_Handler
    .globl        IVOR2_Handler
    

IVOR2_Handler:
            e_stwu    r1,-80(r1)    ;# Create stack frame and store back chain
        e_stw    r3,36(r1)    ;# Save working register
        ;mfspr    r3,26        ;# Get SRR0
        ;e_stw    r3, 12(r1)    ;# and save SRR0
        mfspr    r3, 27        ;# Get SRR1
        e_stw    r3, 16(r1)    ;# and save SRR1
    
                    ;# STEP 2: READ IACKR & RE-ENABLE INTERRUPTS
        e_stw    r0, 32(r1)    ;# Save another working register
        e_lis    r0, EER_exception_handler@h
        e_or2i    r0, EER_exception_handler@l
    
                        ;# STEP 3: SAVE OTHER APPROPRIATE CONTEXT
        se_mflr    r3            ;# Get LR
        e_stw    r3, 8(r1)        ;# and save LR
        mfspr    r3, 1            ;# Get XER
        e_stw    r3, 20(r1)        ;# and save XER
        se_mfctr    r3                ;# Get CTR
        e_stw    r3, 24(r1)        ;# and save CTR
        mfcr    r3                ;# Get CR
        e_stw    r3, 28(r1)        ;# and save CR
        e_stw    r4, 40(r1)        ;# Save R4 to R12
        e_stw    r5, 44(r1)
        e_stw    r6, 48(r1)
        e_stw    r7, 52(r1)    
        e_stw    r8, 56(r1)    
        e_stw    r9, 60(r1)    
        e_stw    r10, 64(r1)
        e_stw    r11, 68(r1) 
        e_stw    r12, 72(r1)
    
                        ;# STEP 4: DETERMINE INTERRUPT SOURCE
                        ;# (Interrupt source's vector is in r0)
        se_mtlr    r0
                            
        mfspr    r3,26            ;# Get SRR0 and pass it to the C function
        e_lhz    r4,0(r3)        ;# pass also the current instruction to the C function
                        ;# STEP 5: EXECUTE INTERRUPT SERVICE ROUTINE 
        se_blrl                ;# Go to vector, but return here
    
        mtspr    26,r3            ;# and restore the new CSRR0
        
                        ;# STEP 6 :  RESTORE CONTEXT                    
        e_lwz    r0, 32(r1)        ;# Restore gprs except R3 
        e_lwz    r4, 40(r1)    
        e_lwz    r5, 44(r1)
        e_lwz    r6, 48(r1)
        e_lwz    r7, 52(r1)
        e_lwz    r8, 56(r1)
        e_lwz    r9, 60(r1)
        e_lwz    r10, 64(r1)
        e_lwz    r11, 68(r1)
        e_lwz    r12, 72(r1)
        e_lwz    r3, 20(r1)        ;# Get XER
        mfspr    r3, 1            ;# and restore XER
        e_lwz    r3, 24(r1)        ;# Get CTR
        se_mtctr    r3            ;# and restore CTR
        e_lwz    r3, 28(r1)        ;# Get CR
        mtcrf    0xff, r3        ;# and restore CR
        e_lwz    r3, 8(r1)        ;# Get LR
        se_mtlr    r3            ;# and restore LR
        wrteei    0            ;# Disable interrupts until
                        ;# end of routine
        ;e_lwz    r3, 12(r1)        ;# Get SRR0 from stack
        ;mtspr    26, r3            ;# and restore SRR0
        e_lwz    r3, 16(r1)        ;# Get SRR1 from stack
        mtspr    27, r3            ;# and restore SRR1
        e_lwz    r3, 36(r1)        ;# Restore R3
        e_addi    r1, r1, 80        ;# Clean up stack
    
                        ;# STEP 7:  Return to Program 
        se_rfi                ;# End of Interrupt
