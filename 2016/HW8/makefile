JFLAGS = -g
JC = javac

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	BigramDyn.java \
        BigramMap.java \
        Pair.java \
	myException.java \
        _mainTester.java 


default: classes
	
classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
