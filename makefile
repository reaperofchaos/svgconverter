# change application name here (executable output name)
TARGET=XMLParser
TESTTARGET=Test_XMLParser
LIBTARGET=libxmlparser.so
ARCHIVELIBTARGET=libxmlparser.a
# compiler
CC=g++
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall -Wextra -Werror
#src directory
SRCDIR=src
#object directoy
CPPVERSION=-std=c++17
LIBFLAGS=-fPIC
OBJDIR=obj
#Libraries
GTEST = /usr/local/lib/libgtest.a
LIBRARYPATH=-L/Users/jacobconner/Desktop/typescriptParser/libs
TOKENIZER=-ltokenizer
#Folder with header files
INCLUDES=-I include
#target directory

CCFLAGS=$(DEBUG) ${CPPVERSION} $(OPT) $(WARN) -pipe ${INCLUDES}

LIBCCFLAGS=$(DEBUG) ${LIBFLAGS} ${CPPVERSION} $(OPT) $(WARN) ${INCLUDES}
# linker
LD=g++
LDFLAGS=-lstdc++

LIBLDFLAGS=-lstdc++ -shared -W1,-soname,${LIBTARGET}

STATICLIBOBJ=$(OBJDIR)/CharType.o \
$(OBJDIR)/ComponentBuilder.o \
$(OBJDIR)/TokenHandlers.o \
$(OBJDIR)/Symbol.o \
$(OBJDIR)/Component.o \
$(OBJDIR)/Primitive.o \
$(OBJDIR)/PropHandlers.o \
$(OBJDIR)/PrimitiveHandlers.o \
$(OBJDIR)/ElementHandlers.o \
$(OBJDIR)/PrimitiveBuilder.o \
$(OBJDIR)/ElementBuilder.o \
$(OBJDIR)/Element.o \
$(OBJDIR)/Prop.o \
$(OBJDIR)/ComponentUtilities.o \
$(OBJDIR)/CharacterUtilities.o \
$(OBJDIR)/TokenizerUtilities.o \
$(OBJDIR)/Writer.o \
$(OBJDIR)/Node.o

OBJS=$(OBJDIR)/main.o\
$(OBJDIR)/ComponentBuilder.o \
$(OBJDIR)/TokenHandlers.o \
$(OBJDIR)/Component.o \
$(OBJDIR)/Primitive.o \
$(OBJDIR)/PropHandlers.o \
$(OBJDIR)/PrimitiveHandlers.o \
$(OBJDIR)/ElementHandlers.o \
$(OBJDIR)/PrimitiveBuilder.o \
$(OBJDIR)/ElementBuilder.o \
$(OBJDIR)/Element.o \
$(OBJDIR)/Prop.o \
$(OBJDIR)/ComponentUtilities.o \
$(OBJDIR)/CharacterUtilities.o \
$(OBJDIR)/Writer.o \
$(OBJDIR)/Node.o

LIBOBJS=$(OBJDIR)/LComponentBuilder.o \
$(OBJDIR)/LTokenHandlers.o \
$(OBJDIR)/LComponent.o \
$(OBJDIR)/LPrimitive.o \
$(OBJDIR)/LPropHandlers.o \
$(OBJDIR)/LPrimitiveHandlers.o \
$(OBJDIR)/LElementHandlers.o \
$(OBJDIR)/LPrimitiveBuilder.o \
$(OBJDIR)/LElementBuilder.o \
$(OBJDIR)/LElement.o \
$(OBJDIR)/LProp.o \
$(OBJDIR)/LComponentUtilities.o \
$(OBJDIR)/LCharacterUtilities.o \
$(OBJDIR)/LWriter.o \
$(OBJDIR)/LNode.o


all: $(OBJS)
	$(LD) ${LIBRARYPATH} -o $(TARGET) $(OBJS)  $(LDFLAGS) ${TOKENIZER}

lib: $(LIBOBJS)
	$(LD) ${LIBRARYPATH}  $(LIBLDFLAGS) -o $(LIBTARGET) $(LIBOBJS) -lc ${TOKENIZER}

staticLib: $(STATICLIBOBJ)
	ar rcs $(ARCHIVELIBTARGET) $(STATICLIBOBJ)

$(OBJDIR)/Prop.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Types/Prop.cpp -o $(OBJDIR)/Prop.o

$(OBJDIR)/Element.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Types/Element.cpp -o $(OBJDIR)/Element.o

$(OBJDIR)/ElementBuilder.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Builders/ElementBuilder.cpp -o $(OBJDIR)/ElementBuilder.o

$(OBJDIR)/PrimitiveBuilder.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Builders/PrimitiveBuilder.cpp -o $(OBJDIR)/PrimitiveBuilder.o

$(OBJDIR)/CharacterUtilities.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Utils/CharacterUtilities.cpp -o $(OBJDIR)/CharacterUtilities.o

$(OBJDIR)/ComponentUtilities.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Utils/ComponentUtilities.cpp -o $(OBJDIR)/ComponentUtilities.o

$(OBJDIR)/TokenizerUtilities.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Utils/TokenizerUtilities.cpp -o $(OBJDIR)/TokenizerUtilities.o

$(OBJDIR)/PropHandlers.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Handlers/PropHandlers.cpp -o $(OBJDIR)/PropHandlers.o

$(OBJDIR)/ElementHandlers.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Handlers/ElementHandlers.cpp -o $(OBJDIR)/ElementHandlers.o

$(OBJDIR)/PrimitiveHandlers.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Handlers/PrimitiveHandlers.cpp -o $(OBJDIR)/PrimitiveHandlers.o

$(OBJDIR)/Primitive.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Types/Primitive.cpp -o $(OBJDIR)/Primitive.o

$(OBJDIR)/Component.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Types/Component.cpp -o $(OBJDIR)/Component.o

$(OBJDIR)/TokenHandlers.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Handlers/TokenHandlers.cpp -o $(OBJDIR)/TokenHandlers.o

$(OBJDIR)/Writer.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Writer.cpp -o $(OBJDIR)/Writer.o

$(OBJDIR)/Node.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Types/Node.cpp -o $(OBJDIR)/Node.o

$(OBJDIR)/ComponentBuilder.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Builders/ComponentBuilder.cpp -o $(OBJDIR)/ComponentBuilder.o

$(OBJDIR)/main.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

##Library variants
$(OBJDIR)/LProp.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Types/Prop.cpp -o $(OBJDIR)/LProp.o

$(OBJDIR)/LElement.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Types/Element.cpp -o $(OBJDIR)/LElement.o

$(OBJDIR)/LElementBuilder.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Builders/ElementBuilder.cpp -o $(OBJDIR)/LElementBuilder.o

$(OBJDIR)/LPrimitiveBuilder.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Builders/PrimitiveBuilder.cpp -o $(OBJDIR)/LPrimitiveBuilder.o

$(OBJDIR)/LCharacterUtilities.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Utils/CharacterUtilities.cpp -o $(OBJDIR)/LCharacterUtilities.o

$(OBJDIR)/LComponentUtilities.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Utils/ComponentUtilities.cpp -o $(OBJDIR)/LComponentUtilities.o

$(OBJDIR)/LPropHandlers.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Handlers/PropHandlers.cpp -o $(OBJDIR)/LPropHandlers.o

$(OBJDIR)/LElementHandlers.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Handlers/ElementHandlers.cpp -o $(OBJDIR)/LElementHandlers.o

$(OBJDIR)/LPrimitiveHandlers.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Handlers/PrimitiveHandlers.cpp -o $(OBJDIR)/LPrimitiveHandlers.o

$(OBJDIR)/LPrimitive.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Types/Primitive.cpp -o $(OBJDIR)/LPrimitive.o

$(OBJDIR)/LComponent.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Types/Component.cpp -o $(OBJDIR)/LComponent.o

$(OBJDIR)/LTokenHandlers.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Handlers/TokenHandlers.cpp -o $(OBJDIR)/LTokenHandlers.o

$(OBJDIR)/LWriter.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Writer.cpp -o $(OBJDIR)/LWriter.o

$(OBJDIR)/LNode.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Types/Node.cpp -o $(OBJDIR)/LNode.o

$(OBJDIR)/LComponentBuilder.o:
	$(CC) -c $(LIBCCFLAGS) $(SRCDIR)/Builders/ComponentBuilder.cpp -o $(OBJDIR)/LComponentBuilder.o

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET) $(LIBTARGET) $(ARCHIVELIBTARGET)