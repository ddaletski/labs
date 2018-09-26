SRC_DIR=src
TARGET=Main

COMPILER_ARGS=-cp . -d .
JAVAC=javac ${COMPILER_ARGS}

.PHONY: all build clean run

all: build

build: ${TARGET}

run: build
	java -jar ${TARGET}.jar

clean: 
	rm *.class *.jar

BoolVector.class: ${SRC_DIR}/BoolVector.java
	${JAVAC} $^

Main.class: ${SRC_DIR}/Main.java BoolVector.class
	${JAVAC} $<

${TARGET}: Manifest.txt Main.class BoolVector.class
	jar -cvfm $@.jar $^
