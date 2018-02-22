NAME = lem_in_java_graph
BIN_FOLDER = bin/
DOC_FOLDER = doc/
DEP = "deps/gs-core-1.3.jar"
DEPS_FOLDER = ".:"$(DEP)

MAIN_PATH = "src/Main"
MAIN_PATH_MANIFEST = "src.Main"

MANIFEST = "MANIFEST.MF"
JAR = $(NAME).jar

all : dep
	@mkdir -p $(BIN_FOLDER)
	@javac -cp $(DEPS_FOLDER) -d $(BIN_FOLDER) $(MAIN_PATH).java
	@echo "Main-Class: "$(MAIN_PATH_MANIFEST) > $(MANIFEST)
	@echo "Class-Path: "$(DEP) >> $(MANIFEST)
	@jar -cvmf $(MANIFEST) $(JAR) -C $(BIN_FOLDER) ./

run:
	@java -jar $(JAR)

clean:
	@rm -rf $(BIN_FOLDER)
	@rm -rf $(DOC_FOLDER)
	@rm -rf $(MANIFEST)

fclean: clean
	@rm -rf $(JAR)

re: fclean all

dep:
	@test -e $(DEP) || (mkdir -p deps && curl https://data.graphstream-project.org/pub/1.x/nightly-build/last/gs-core-1.3-SNAPSHOT-last.jar -o $(DEP))
