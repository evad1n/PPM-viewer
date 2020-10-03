# # header files come after
# # first target is default, just call ">> make"
# # to call specific target call ">> make <target_name>"

# # target: dependencies
# # <tab>command to build

# NAME=ppm_menu
# CFLAGS=g++ -std=c++11

# # OFILES=$(wildcard *.o) 


# all: $(NAME)

# $(NAME): PPM.o ppm_menu.o image_menu.o ColorTable.o NumberGrid.o ThreadedGrid.o ComplexFractal.o JuliaSet.o MandelbrotSet.o
# 	$(CFLAGS) -pthread -o $(NAME) PPM.o ppm_menu.o image_menu.o ColorTable.o NumberGrid.o ThreadedGrid.o ComplexFractal.o JuliaSet.o MandelbrotSet.o

# PPM.o: PPM.cpp PPM.h
# 	$(CFLAGS) -c PPM.cpp

# ppm_menu.o: ppm_menu.cpp image_menu.h
# 	$(CFLAGS) -c ppm_menu.cpp

# image_menu.o: image_menu.cpp image_menu.h
# 	$(CFLAGS) -c image_menu.cpp

# ColorTable.o: ColorTable.cpp ColorTable.h
# 	$(CFLAGS) -c ColorTable.cpp

# NumberGrid.o: NumberGrid.cpp PPM.h
# 	$(CFLAGS) -c NumberGrid.cpp

# ThreadedGrid.o: ThreadedGrid.cpp ThreadedGrid.h
# 	$(CFLAGS) -c ThreadedGrid.cpp

# ComplexFractal.o: ComplexFractal.cpp ThreadedGrid.h
# 	$(CFLAGS) -c ComplexFractal.cpp

# JuliaSet.o: JuliaSet.cpp ComplexFractal.h
# 	$(CFLAGS) -c JuliaSet.cpp

# MandelbrotSet.o: MandelbrotSet.cpp ComplexFractal.h
# 	$(CFLAGS) -c MandelbrotSet.cpp

# run: $(NAME)
# 	./$(NAME)   

# clean:
# 	rm -f $(NAME) *.o *.ppm


# # Debugging

# # -g for debugging
# # gdb ./program
# # run
# # break {function}
# # next
# # print {variable}
# # list 
# # quit

# # For moving grind to git repo
# # cp *.h *.cpp ../../cs-3005-project-spring-2020-evad1n/src

# # For moving git repo to grind
# # cp *.h *.cpp ../../CS-3005/cs3005_assignment_name/
# # Then remove ppm_menu so it doesn't call image menu after make test
# # rm ppm_menu.*

TARGETS := glut_main ppm_menu
BOTH_OBJECTS := image_menu.o PPM.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o MyApp.o
GUI_OBJECTS := glut_main.o app.o gl_draw.o glut_callback.o $(BOTH_OBJECTS)
TEXT_OBJECTS := ppm_menu.o $(BOTH_OBJECTS)
CXXFLAGS := -Wall -Werror -std=c++11
LDFLAGS := -lglut -lGLU -lGL -lpthread
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
# OS X specific options
LDFLAGS := -framework OpenGL -framework GLUT -lpthread
CXXFLAGS := $(CXXFLAGS) -Wno-deprecated
endif

all: $(TARGETS)

glut_main: $(GUI_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ppm_menu: $(TEXT_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

######################################
# automatic dependency generation
#
DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))
#
#
######################################

######################################
#
#
clean:
	-rm -f $(TARGETS)
	-rm -f *.o
	-rm -f *~ .*~
	-rm -rf $(DEPDIR)
#
#
######################################

test.mp4:
	ffmpeg -r 3 -i gui_image_%04d.ppm $@

# Local Variables:
# mode:makefile
# End: