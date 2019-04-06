#This will call the makefile inside of subdirectory /src/
# Please go to subdirectory /src/makefile where you will find instructions for all objects and executables, this makefile is simply a link to that one.
all:
	+$(MAKE) -C src
test:
	@echo "use make test-comm instead since no currently integrated gui"

test-gui:
	@echo "No gui available in Alpha Release"

test-comm:	
	@echo "To run the examples, first start the server in one terminal,"
	@echo "then start the client in another."
	@echo
	@echo "For example:"
	@echo "crystalcove# server 10000"
	@echo "crystalcove# client crystalcove 10000"
	@echo
	@echo "For a succesful login use these credentials:"
	@echo "Username: GUY"
	@echo "Password: ace"



clean:
	rm -f bin/server src/server
	rm -f bin/client src/client
	rm -f src/*.o
	rm Chat_Beta_src.tar.gz
tar:
	tar -cvzf Chat_Beta_src.tar.gz ../Chat_Beta_src
