# To test strict C ANSI compliance
CC = g++
AR = ar
LIB= -lstdc++

# This allow you to write "make PURE=purify demo1"
# or "make PURE=quantify lib2"
CCPURE = $(PURE) $(CC)

#Include directories
CFLAGS += -IInclude

CFLAGS += -O6
#CFLAGS += -g 
# CFLAGS += -DALPHA
# CFLAGS += -DDEBUG

# Flags for GCC
CFLAGS += -Wall
# CFLAGS += -fhandle-exceptions

COMMONSRCS =  PhoFile/Phoneme.cpp PhoFile/PhonemePlus.cpp PhoFile/PitchPoint.cpp PhoFile/LPitchPoint.cpp PhoFile/LPhonemePlus.cpp Letter2Phone/Feature.cpp Letter2Phone/DecisionTree.cpp Letter2Phone/Letter2Phone.cpp Letter2Phone/Letter2PhoneLR.cpp Letter2Phone/Letter2PhoneRL.cpp Engine/Speak.cpp Engine/SpeakFrench.cpp Engine/SpeakAmerican.cpp Engine/SpeakArabic.cpp Engine/Dictionary.cpp Engine/ZPhoneme.cpp Engine/VpError.cpp 

COMMONCHDRS = 
BINSRCS =  $(COMMONSRCS)
BINDIR = Bin
BINOBJS = $(BINSRCS:%.cpp=Bin/%.o)

MBRDICOSRCS = UNIX/Mbrdico.cpp
MBRDICOBINOBJS = $(MBRDICOSRCS:%.cpp=Bin/%.o)

MBRCARRIERSRCS = UNIX/Carrier.cpp
MBRCARRIERBINOBJS =  $(MBRCARRIERSRCS:%.cpp=Bin/%.o)

mbrdico: install  $(BINOBJS) $(MBRDICOBINOBJS)
	$(CCPURE) $(CFLAGS) -o ../BINARY/mbrdico.$(OSTYPE) $(BINOBJS) $(MBRDICOBINOBJS)  $(LIB) 
	@echo "------------------------"
	@echo "The binary is in ../BINARY/mbrdico.$(OSTYPE)"
	@echo "Try something like ../BINARY/mbrdico.$(OSTYPE) ../BINARY/american.ini"

carrier:  install  $(BINOBJS) $(MBRCARRIERBINOBJS)
	$(CCPURE) $(CFLAGS) -o ../BINARY/carrier.$(OSTYPE) $(BINOBJS) $(MBRCARRIERBINOBJS)  $(LIB) 
	@echo "------------------------"
	@echo "The binary is in ../BINARY/carrier.$(OSTYPE)"
	@echo "Try something like ../BINARY/carrier.$(OSTYPE) ../BINARY/french.ini ../DATA/carrier_fr.pho"

test:  Bin/Letter2Phone/test.o Bin/Engine/VpError.o Bin/Letter2Phone/Feature.o Bin/Letter2Phone/DecisionTree.o
	$(CCPURE) $(CFLAGS) -o Bin/test Bin/Letter2Phone/test.o Bin/Engine/VpError.o Bin/Letter2Phone/Feature.o Bin/Letter2Phone/DecisionTree.o $(LIB) 
	@echo "------------------------"
	@echo "The binary is in Bin/test"
	@echo "Try something like Bin/test ../DATA/fr.tree"


$(BINDIR)/%.o: %.cpp
	$(CCPURE) $(CFLAGS) -o $@ -c $<

clean:
	\rm -f mbrdico.a core demo* TAGS $(BINOBJS) 
	\rm -rf VISUALC++/*/debug VISUALC++/*/release
	\rm -rf VISUALC++/debug VISUALC++/release
	\rm -f VISUALC++/*/*.ncb VISUALC++/*/*.opt VISUALC++/*/*.plg VISUALC++/*/*.sb VISUALC++/*/*.aps 
	\rm -f VISUALC++/*.ncb VISUALC++/*.opt VISUALC++/*.plg VISUALC++/*.sb VISUALC++/*.aps 

spotless: clean net
	\rm -rf Bin 

tags:
	etags */*{cpp,hpp}

net:
	\rm -f *~ */*~

# to create the compilation directory, if necessary
install: 
	if [ ! -d Bin ]; then \
	mkdir Bin Bin/Engine Bin/PhoFile Bin/Letter2Phone Bin/UNIX ;\
	fi

sauve: spotless
	cd ..; gtar cvfz SAUVE/synth$(VERSION).tgz synth$(VERSION)/
