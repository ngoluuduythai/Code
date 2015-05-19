# 
#  GNUmake (use gmake)
#
#~ !for NhanX laptop with gfortran compiler
#~ FC	= gfortran
FC	= f77
CXX	= g++
C= gcc
LINKER	= $(CXX)
#------------------------------------------------
#~ !if use f77/g77 compiler
#~ ADD_LIB		=  -lg2c
#~ !for NhanX laptop with gfortran compiler
#~ ADD_LIB		= -lgfortran
#~ !for lapthsl5e computer with f77 compiler
ADD_LIB		= -L/usr/lib/gcc/x86_64-redhat-linux/3.4.6 -lg2c
#~ !for lapthsl5e computer with gfortran compiler
#~ ADD_LIB		= -L/usr/lib/gcc/x86_64-redhat-linux/4.1.2 -lgfortran
#~ FFLAGS	   = -O0
#~ CXXFLAGS	= -O
#------------------------------------------------
%.o : %.cc
	$(CXX) -c $<
%.o : %.c
	$(C) -c $<
%.o : %.f
	$(FC) -c $<
#------------------------------------------------
MODULE_tail = nclinhWrap.o nclinhfw.o Cteq6Pdf-2010.o
MODULE =  nvegas.o   Amp2_math.o   $(MODULE_tail) 
LDFLAGS = -lm $(ADD_LIB)	
#------------------------------------------------
find_pdf: Cteq6Pdf-2010.o
	$(LINKER) -o $@.exe $@.c $^ $(LDFLAGS)
	$@.exe
PDFs_test1 PDFs_test2 PDFs_test3 PDFs_Amp_cdot \
	PDFs_Sig_hat PDFs_Amp_hat PDFs_develop: $(MODULE)
	$(LINKER) -o run.exe $@.cpp $^ $(LDFLAGS)
	./run.exe
#------------------------------------------------
clean:	
	rm *.o *.mod *.exe
