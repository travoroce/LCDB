plateforme = ''
ifeq ($(OS),Windows_NT)
	plateforme = win32
	archi = windows
	MV = move
	#RM = del /F
	RM = rm -rf
	CP = copy
	D_PRO = ./
	EXE = Test.exe
	COMP = g++ -g -Wfatal-errors -O2
	LINK = g++ -g -Wfatal-errors
    
	COMP_FLAGS += -I"$(D_PRO)inc/" -I"$(D_PRO)ext/Box2D_v2.2.1/"
	COMP_FLAGS += -I"$(D_PRO)inc/" -I"c:/program files/thor/include/"
	COMP_FLAGS += -I"$(D_PRO)inc/" -I"c:/program files/SFML/include/"
	COMP_FLAGS += -std=c++0x
    
	LINK_FLAGS += -I"$(D_PRO)/"
	LINK_FLAGS += -L"c:/program files/SFML/thor/"
	LINK_FLAGS += -L"c:/program files/SFML/lib/"
	LINK_FLAGS += -L"$(D_PRO)"

else
	plateforme = linux
	archi = unix
	MV = mv
	RM = rm -f
	CP = cp
	D_PRO = $(PWD)/
	EXE = Test
	COMP = g++ -g -Wfatal-errors
	LINK = g++ -g -Wfatal-errors
    
	COMP_FLAGS = -I/usr/include/ -I/usr/local/include/ -I$(D_PRO)inc/ 
	COMP_FLAGS = -std=c++0x -fPIC
    
	LINK_FLAGS = -L/usr/lib/ -L/usr/local/lib/ -L$(D_PRO)
endif

D_SRC = $(D_PRO)src/
D_LIB = $(D_PRO)lib/$(plateforme)/
D_BIN = $(D_PRO)bin/$(plateforme)/

SOURCES	 = $(wildcard $(D_SRC)*.cpp) 

OBJETS        = $(SOURCES:.cpp=.o)


ifeq ($(archi),windows)
	LIBS     =  -lBox2D -lthor -lsfml-graphics -lsfml-window -lsfml-system -lopengl32
else
	LIBS     = 
endif


all: $(EXE)

	@echo Compilation terminée!
$(EXE): $(OBJETS)
	$(LINK) $(OBJETS) $(LIBS) $(LIBS_OTE) $(LINK_FLAGS) -o $@

.cpp.o:
	$(COMP) $(COMP_FLAGS) -c $< -o $@
    
install:
ifeq ($(archi),windows)
	$(CP) $(EXE) bin\$(plateforme)\$(EXE)
else
	$(CP) $(EXE) $(D_BIN)$(EXE)
endif

clean:
ifeq ($(archi),windows)
	DEL /S src\*.o
else
	$(RM) $(OBJETS)
endif
	$(RM) $(EXE)

cleanall:
ifeq ($(archi),windows)
	$(RM) /S src\*.o
	# $(RM) $(OBJETS) $(OBJETS_OTE) $(OBJETS_OUTILS)
else
	$(RM) $(OBJETS) $(OBJETS_OTE) $(OBJETS_OUTILS)
endif
	$(RM) $(EXE) 
    
rebuild: cleanall all

remove:
ifeq ($(archi),windows)

else
	$(RM) $(OBJETS) $(OBJETS_OTE) $(OBJETS_OUTILS)
endif
	$(RM) $(EXE)
    
info:
	@echo $(OBJETS)
