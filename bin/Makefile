# -----------------------------------------------------------------------------
#
#                              M A K E F I L E
#
# zum Uebungsbetriebssystem Co-Stubs der Lehrveranstaltung
# 'Betriebssysteme 1' an der BTU-Cottbus im SS11
# -----------------------------------------------------------------------------
#
# Folgende Make-Targets sind m�glich
#
# depend 	: �berpr�ft alle Abh�ngigkeiten und schreibt diese in eine Datei
# system.img 	: erstellt das Speicherabbild des Betriebssystems
# bootdisk.img	: erstellt das Speicherabbild des Betriebssystem + Bootcode
# bootdisk	: kopiert das bootf�hig Speicherabbild auf Diskette
# clean		: l�scht alle generierten Dateien
#
# -----------------------------------------------------------------------------
#LINUX and CYGWIN so far
GENSYS = $(shell uname)

INITFINI = lib/finit.cc

# Liste der Quelltexte:
# (Beim Hinzufuegen neuer Module erweitern!)
# Achtung!!!! Hinter dem backslash am Zeilenende darf *kein* Zeichen stehen!!
# Die letzte Zeile bekommt kein backslash!!!


STARTUP_S = \
	boot/startup.asm

MACHINE_S = \
	cpu/cpu.asm \
	io/ports.asm \
	thread/switchContext.asm \

SYSTEM_C = \
	lib/tools.c


SYSTEM_CC = \
	$(INITFINI) \
	device/CgaChannel.cc \
	device/CgaScreen.cc \
	device/Clock.cc \
	device/CodeTable.cc \
	device/Keyboard.cc \
	device/PIC.cc \
	device/PIT.cc \
	interrupts/Gate.cc \
	interrupts/InterruptGuardian.cc \
	interrupts/PageFaultGate.cc \
	interrupts/PanicGate.cc \
	interrupts/SpuriousGate.cc \
	io/PrintStream.cc \
	lib/Queue.cc \
	sync/KernelSemaphore.cc \
	sync/Monitor.cc \
	system/Console.cc \
	thread/Activity.cc \
	thread/ActivityScheduler.cc \
	thread/Coroutine.cc \
	thread/Scheduler.cc \
	tools/Calc.cc \
	tools/Interp.cc \
	tools/Scanner.cc \
	user/Hello.cc \
	user/Init.cc \
	mainMonitor.cc \
	
	
	


##############################################################################

STARTUP_SOURCE = $(addprefix ../machine/,$(STARTUP_S))
MACHINE_SOURCES = $(addprefix ../machine/,$(MACHINE_S))
SYSTEM_SOURCES = $(addprefix ../src/,$(SYSTEM_CC))
SYSTEM_C_SOURCES = $(addprefix ../src/,$(SYSTEM_C))

SOURCES = $(MACHINE_SOURCES) $(SYSTEM_SOURCES) $(SYSTEM_C_SOURCES)

FIRST_OBJECT = $(notdir $(STARTUP_SOURCE:.asm=.o))

OBJECTS = $(patsubst %.asm,%.o,$(patsubst %.c,%.o,$(patsubst %.cc,%.o,$(notdir $(SOURCES))) ))

VPATH = $(dir $(SOURCES) $(STARTUP_SOURCE) )

INCLUDES = -I../include \
	-I../machine

DEPENDENCIES_FILE = Dependencies.mk

##############################################################################

# Einstellungen in Abhaengigkeit vom Generierungssystem:
#
#    AS:          Zu benutzender Assembler
#    CC/CXX:       Zu benutzender C/C++-Compiler.
#    LD:           Zu benutzender Linker.
#    LDLIBS:       Dazuzulinkende Bibliotheken
#    LDHEAD:       Am Anfang zu linkende Dateien
#    LDTAIL:       Am Ende zu linkende Dateien
ifeq ($(GENSYS), Linux)

AS = nasm
CC = gcc
CXX = g++
# CXX = clang++
LD = ld
OBJCOPY = objcopy

ASFLAGS = -DLINUX -f elf32
CFLAGS = -c -m32 -fno-stack-protector -DLINUX -Wall -fno-exceptions $(INCLUDES)
CXXFLAGS = -c -m32 -fno-stack-protector -DLINUX -Wall -fno-rtti -fno-exceptions $(INCLUDES)
LDFLAGS = -melf_i386 -e get_protected -T ../machine/linux.ls -o system
LDHEAD = $(shell $(CXX) -m32 --print-file-name=crti.o && \
	   $(CXX) -m32 --print-file-name=crtbegin.o)
LDTAIL = $(shell $(CXX) -m32 --print-file-name=crtend.o && \
	   $(CXX) -m32 --print-file-name=crtn.o)

endif

# -------------------------------------------------------------------------
# Die Targets f�r die Kompilierung

%.o : %.asm
	$(AS) $(ASFLAGS) -o $@ $<

%.bin : %.asm
	$(AS) -f bin -o $@ $<

%.o : %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

# Linken des Systems
system : $(FIRST_OBJECT) $(OBJECTS)
	$(LD)  $(LDFLAGS) $(FIRST_OBJECT) $(LDHEAD) $(OBJECTS) $(LDTAIL)

bootdisk: system
	cp system isodir/boot/costubs.elf
	grub-mkrescue -d /usr/lib/grub/i386-pc -o costubs.iso isodir


# Bekanntmachen von Targets die keine Abh�ngigkeiten haben
.PHONY: clean depend

depend:
	@echo "" > $(DEPENDENCIES_FILE)
ifneq ($(strip $(SYSTEM_SOURCES)),)
	$(CXX) $(CXXFLAGS) -MM $(SYSTEM_SOURCES) >> $(DEPENDENCIES_FILE)
endif

# debug: start qemu with gdb stub, wait for a moment, start gdb and attach it
debug: ASFLAGS += -g
debug: CFLAGS += -g
debug: CXXFLAGS += -g
debug: system
	qemu-system-i386 -kernel system -s -S & sleep 1 && gdb system -x gdb.script

clean:
	@rm -f *.o
	@rm -f isodir/boot/costubs.elf
	@rm -f costubs.iso
	@rm -f bochsout.txt
	@rm -f system
	@rm -f $(DEPENDENCIES_FILE)

# erstellt die Datei mit den Abh�ngigkeiten
$(DEPENDENCIES_FILE):
	touch $(DEPENDENCIES_FILE)
	$(MAKE) depend

# einbinden der Datei mit den aktuellen Abh�ngigkeiten
sinclude $(DEPENDENCIES_FILE)

