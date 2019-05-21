/* Entry Point */
ENTRY(_start)

/* define heap and stack size */
__HEAP_SIZE            = 0 ;
__STACK_SIZE           = 4096 ;

SRAM_SIZE =  384K;    
/* Define SRAM Base Address */
SRAM_BASE_ADDR = 0x40000000;

/* Define CPU0 Local Data SRAM Allocation */
LOCALDMEM_SIZE = 64K;
/* Define CPU0 Local Data SRAM Base Address */
LOCALDMEM_BASE_ADDR = 0x50800000;
    
/*MEMORY
{ */

/* the default memory assign as below commented, it can be used for appliction project */

/*
   flash_rchw : org = 0x00FA0000,   len = 0x4
    cpu0_reset_vec : org = 0x00FA0004,   len = 0x4 
    
    m_text :	org = 0x1000000, len = 2048K  
    m_data :	org = 0x40000000,   len = 384K
    
    local_dmem  : org = 0x50800000,   len = 64K   
    
*/

    /*16 KB low flash memory block 2 (boot location 0) from 0x00F98000 to 0x00F9BFFF*/  
    /*16 KB low flash memory block 3 (boot location 1) from 0x00F9C000 to 0x00F9FFFF*/
    /* use the low flash memory block 2 and 3(32KB in total) as bootloader area */
    
    /*flash_rchw : org = 0x00F98000,   len = 0x4
    cpu0_reset_vec : org = 0x00F98004,   len = 0x4 */
    
    /*m_text :	org = 0x00F99000, len = 28K  */  /*code flash for bootloader interrupt vector table, startup and boot codes*/
    
    /*m_data :	org = 0x40000000,   len = 384K */ /*system SRAM*/
    
    /*local_dmem  : org = 0x50800000,   len = 64K *//*CPU core data tightly coupled memory*/ 
    
    
MEMORY
{   
    /*64 KB low flash memory for bootloader block 3 (boot location 2) from 0x00FA0000 to 0x00FAFFFF*/  
    
    flash_rchw : org = 0x00FA0000,   len = 0x4
    cpu0_reset_vec : org = 0x00FA0004,   len = 0x4
    
    m_text :	org = 0x00FA1000, len = 32K    /*code flash for bootloader interrupt vector table, startup and boot codes*/
    
    m_data :	org = 0x40000000,   len = 384K  /*system SRAM*/
    
    local_dmem  : org = 0x50800000,   len = 64K /*CPU core data tightly coupled memory*/
            
}

SECTIONS
{
    .rchw   : 
    {
        KEEP(*(.rchw))
    } > flash_rchw

    .cpu0_reset_vector  : 
    {
        KEEP(*(.cpu0_reset_vector))
    } > cpu0_reset_vec

    .startup : ALIGN(0x400)
    {
    __start = . ;
    	*(.startup)
    } > m_text
    
    .core_exceptions_table   : ALIGN(4096)
    {
      __IVPR_VALUE = . ;
      KEEP(*(.core_exceptions_table))
    } > m_text

    .intc_vector_table   : ALIGN(4096)
    {
      KEEP(*(.intc_vector_table))
    } > m_text
      
    .text : 
    {
      *(.text.startup)
      *(.text)      
      *(.text.*)
      KEEP (*(.init))
      KEEP (*(.fini))            
      . = ALIGN(16);
    } > m_text
      
    .ctors :
    {
      __CTOR_LIST__ = .;
      /* gcc uses crtbegin.o to find the start of
         the constructors, so we make sure it is
         first.  Because this is a wildcard, it
         doesn't matter if the user does not
         actually link against crtbegin.o; the
         linker won't look for a file to match a
         wildcard.  The wildcard also means that it
         doesn't matter which directory crtbegin.o
         is in.  */
      KEEP (*crtbegin.o(.ctors))
      KEEP (*crtbegin?.o(.ctors))
      /* We don't want to include the .ctor section from
         from the crtend.o file until after the sorted ctors.
         The .ctor section from the crtend file contains the
         end of ctors marker and it must be last */
      KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors))
      KEEP (*(SORT(.ctors.*)))
      KEEP (*(.ctors))
      __CTOR_END__ = .;
    } > m_text

    .dtors :
    {
      __DTOR_LIST__ = .;
      KEEP (*crtbegin.o(.dtors))
      KEEP (*crtbegin?.o(.dtors))
      KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors))
      KEEP (*(SORT(.dtors.*)))
      KEEP (*(.dtors))
      __DTOR_END__ = .;
    } > m_text
        
    .preinit_array :
    {
      PROVIDE_HIDDEN (__preinit_array_start = .);
      KEEP (*(.preinit_array*))
      PROVIDE_HIDDEN (__preinit_array_end = .);
    } > m_text

    .init_array :
    {
      PROVIDE_HIDDEN (__init_array_start = .);
      KEEP (*(SORT(.init_array.*)))
      KEEP (*(.init_array*))
      PROVIDE_HIDDEN (__init_array_end = .);
    } > m_text

    .fini_array :
    {
      PROVIDE_HIDDEN (__fini_array_start = .);
      KEEP (*(SORT(.fini_array.*)))
      KEEP (*(.fini_array*))
      PROVIDE_HIDDEN (__fini_array_end = .);
    } > m_text
          
    .rodata :
    {
      *(.rodata)
      *(.rodata.*)
    } > m_text
    
    .eh_frame_hdr : { *(.eh_frame_hdr) } > m_text
    .eh_frame     : { KEEP (*(.eh_frame)) } > m_text
    
	.data   : 
	{
	  *(.data)
	  *(.data.*)
	}  > m_data AT>m_text
    
    .sdata2  :
	{  
	  *(.sdata2)
	  *(.sdata2.*)
	} > m_data AT>m_text

	.sbss2    (NOLOAD)   :
	{
      /* _SDA2_BASE_ = .; */ 
	  *(.sbss2)
	  *(.sbss2.*)
	} > m_data
    
    .sdata  :
	{
	  *(.sdata)
	  *(.sdata.*)
	} > m_data AT>m_text
    
	.bss   (NOLOAD)  :
	{
	  __BSS_START = .;
	  *(.sbss)
	  *(.sbss.*)	
      *(.bss)
      *(.bss.*)
      *(COMMON)
      __BSS_END = .;
    } > m_data
    
    .stack (NOLOAD) : ALIGN(16) 
    {
      __HEAP = . ;
      PROVIDE (_end = . );
      PROVIDE (end = . );      
      . += __HEAP_SIZE ;
      __HEAP_END = . ;
      _stack_end = . ;
      . +=  __STACK_SIZE ;
      _stack_addr = . ;
      __SP_INIT = . ;
      . += 4;
    } > local_dmem
 
/*-------- LABELS USED IN CODE -------------------------------*/
        
/* Labels for Copying Initialised Data from Flash to RAM */
__DATA_SRAM_ADDR  = ADDR(.data);
__SDATA_SRAM_ADDR = ADDR(.sdata);

__DATA_SIZE   = SIZEOF(.data);
__SDATA_SIZE  = SIZEOF(.sdata);

__DATA_ROM_ADDR  = LOADADDR(.data);
__SDATA_ROM_ADDR = LOADADDR(.sdata);
   
/* Labels Used for Initialising SRAM ECC */
__SRAM_SIZE = SRAM_SIZE;
__SRAM_BASE_ADDR = SRAM_BASE_ADDR;

__LOCAL_DMEM_SIZE = LOCALDMEM_SIZE;
__LOCAL_DMEM_BASE_ADDR = LOCALDMEM_BASE_ADDR;

__BSS_SIZE    = __BSS_END - __BSS_START;    
      
}



